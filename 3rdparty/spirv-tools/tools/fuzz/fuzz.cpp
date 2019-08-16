// Copyright (c) 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cassert>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>

#include "source/fuzz/fuzzer.h"
#include "source/fuzz/protobufs/spirvfuzz_protobufs.h"
#include "source/fuzz/replayer.h"
#include "source/fuzz/shrinker.h"
#include "source/opt/build_module.h"
#include "source/opt/ir_context.h"
#include "source/opt/log.h"
#include "source/spirv_fuzzer_options.h"
#include "source/util/string_utils.h"
#include "tools/io.h"
#include "tools/util/cli_consumer.h"

namespace {

// Check that the std::system function can actually be used.
bool CheckExecuteCommand() {
  int res = std::system(nullptr);
  return res != 0;
}

// Execute a command using the shell.
// Returns true if and only if the command's exit status was 0.
bool ExecuteCommand(const std::string& command) {
  errno = 0;
  int status = std::system(command.c_str());
  assert(errno == 0 && "failed to execute command");
  // The result returned by 'system' is implementation-defined, but is
  // usually the case that the returned value is 0 when the command's exit
  // code was 0.  We are assuming that here, and that's all we depend on.
  return status == 0;
}

// Status and actions to perform after parsing command-line arguments.
enum class FuzzActions {
  FUZZ,    // Run the fuzzer to apply transformations in a randomized fashion.
  REPLAY,  // Replay an existing sequence of transformations.
  SHRINK,  // Shrink an existing sequence of transformations with respect to an
           // interestingness function.
  STOP     // Do nothing.
};

struct FuzzStatus {
  FuzzActions action;
  int code;
};

void PrintUsage(const char* program) {
  // NOTE: Please maintain flags in lexicographical order.
  printf(
      R"(%s - Fuzzes an equivalent SPIR-V binary based on a given binary.

USAGE: %s [options] <input.spv> -o <output.spv>

The SPIR-V binary is read from <input.spv>, which must have extension .spv.  If
<input.facts> is also present, facts about the SPIR-V binary are read from this
file.

The transformed SPIR-V binary is written to <output.spv>.  Human-readable and
binary representations of the transformations that were applied are written to
<output.transformations_json> and <output.transformations>, respectively.

NOTE: The fuzzer is a work in progress.

Options (in lexicographical order):

  -h, --help
               Print this help.
  --replay
               File from which to read a sequence of transformations to replay
               (instead of fuzzing)
  --seed
               Unsigned 32-bit integer seed to control random number
               generation.
  --shrink
               File from which to read a sequence of transformations to shrink
               (instead of fuzzing)
  --shrinker-step-limit
               Unsigned 32-bit integer specifying maximum number of steps the
               shrinker will take before giving up.  Ignored unless --shrink
               is used.
  --interestingness
               Path to an interestingness function to guide shrinking: a script
               that returns 0 if and only if a given binary is interesting.
               Required if --shrink is provided; disallowed otherwise.
  --version
               Display fuzzer version information.

)",
      program, program);
}

// Message consumer for this tool.  Used to emit diagnostics during
// initialization and setup. Note that |source| and |position| are irrelevant
// here because we are still not processing a SPIR-V input file.
void FuzzDiagnostic(spv_message_level_t level, const char* /*source*/,
                    const spv_position_t& /*position*/, const char* message) {
  if (level == SPV_MSG_ERROR) {
    fprintf(stderr, "error: ");
  }
  fprintf(stderr, "%s\n", message);
}

bool EndsWithSpv(const std::string& filename) {
  std::string dot_spv = ".spv";
  return filename.length() >= dot_spv.length() &&
         0 == filename.compare(filename.length() - dot_spv.length(),
                               filename.length(), dot_spv);
}

FuzzStatus ParseFlags(int argc, const char** argv, std::string* in_binary_file,
                      std::string* out_binary_file,
                      std::string* replay_transformations_file,
                      std::string* interestingness_function_file,
                      std::string* shrink_transformations_file,
                      spvtools::FuzzerOptions* fuzzer_options) {
  uint32_t positional_arg_index = 0;

  for (int argi = 1; argi < argc; ++argi) {
    const char* cur_arg = argv[argi];
    if ('-' == cur_arg[0]) {
      if (0 == strcmp(cur_arg, "--version")) {
        spvtools::Logf(FuzzDiagnostic, SPV_MSG_INFO, nullptr, {}, "%s\n",
                       spvSoftwareVersionDetailsString());
        return {FuzzActions::STOP, 0};
      } else if (0 == strcmp(cur_arg, "--help") || 0 == strcmp(cur_arg, "-h")) {
        PrintUsage(argv[0]);
        return {FuzzActions::STOP, 0};
      } else if (0 == strcmp(cur_arg, "-o")) {
        if (out_binary_file->empty() && argi + 1 < argc) {
          *out_binary_file = std::string(argv[++argi]);
        } else {
          PrintUsage(argv[0]);
          return {FuzzActions::STOP, 1};
        }
      } else if (0 == strncmp(cur_arg, "--replay=", sizeof("--replay=") - 1)) {
        const auto split_flag = spvtools::utils::SplitFlagArgs(cur_arg);
        *replay_transformations_file = std::string(split_flag.second);
      } else if (0 == strncmp(cur_arg, "--interestingness=",
                              sizeof("--interestingness=") - 1)) {
        const auto split_flag = spvtools::utils::SplitFlagArgs(cur_arg);
        *interestingness_function_file = std::string(split_flag.second);
      } else if (0 == strncmp(cur_arg, "--shrink=", sizeof("--shrink=") - 1)) {
        const auto split_flag = spvtools::utils::SplitFlagArgs(cur_arg);
        *shrink_transformations_file = std::string(split_flag.second);
      } else if (0 == strncmp(cur_arg, "--seed=", sizeof("--seed=") - 1)) {
        const auto split_flag = spvtools::utils::SplitFlagArgs(cur_arg);
        char* end = nullptr;
        errno = 0;
        const auto seed =
            static_cast<uint32_t>(strtol(split_flag.second.c_str(), &end, 10));
        assert(end != split_flag.second.c_str() && errno == 0);
        fuzzer_options->set_random_seed(seed);
      } else if (0 == strncmp(cur_arg, "--shrinker-step-limit=",
                              sizeof("--shrinker-step-limit=") - 1)) {
        const auto split_flag = spvtools::utils::SplitFlagArgs(cur_arg);
        char* end = nullptr;
        errno = 0;
        const auto step_limit =
            static_cast<uint32_t>(strtol(split_flag.second.c_str(), &end, 10));
        assert(end != split_flag.second.c_str() && errno == 0);
        fuzzer_options->set_shrinker_step_limit(step_limit);
      } else if ('\0' == cur_arg[1]) {
        // We do not support fuzzing from standard input.  We could support
        // this if there was a compelling use case.
        PrintUsage(argv[0]);
        return {FuzzActions::STOP, 0};
      }
    } else if (positional_arg_index == 0) {
      // Binary input file name
      assert(in_binary_file->empty());
      *in_binary_file = std::string(cur_arg);
      positional_arg_index++;
    } else {
      spvtools::Error(FuzzDiagnostic, nullptr, {},
                      "Too many positional arguments specified");
      return {FuzzActions::STOP, 1};
    }
  }

  if (in_binary_file->empty()) {
    spvtools::Error(FuzzDiagnostic, nullptr, {}, "No input file specified");
    return {FuzzActions::STOP, 1};
  }

  if (!EndsWithSpv(*in_binary_file)) {
    spvtools::Error(FuzzDiagnostic, nullptr, {},
                    "Input filename must have extension .spv");
    return {FuzzActions::STOP, 1};
  }

  if (out_binary_file->empty()) {
    spvtools::Error(FuzzDiagnostic, nullptr, {}, "-o required");
    return {FuzzActions::STOP, 1};
  }

  if (!EndsWithSpv(*out_binary_file)) {
    spvtools::Error(FuzzDiagnostic, nullptr, {},
                    "Output filename must have extension .spv");
    return {FuzzActions::STOP, 1};
  }

  if (!replay_transformations_file->empty()) {
    // A replay transformations file was given, thus the tool is being invoked
    // in replay mode.
    if (!shrink_transformations_file->empty()) {
      spvtools::Error(
          FuzzDiagnostic, nullptr, {},
          "The --replay and --shrink arguments are mutually exclusive.");
      return {FuzzActions::STOP, 1};
    }
    if (!interestingness_function_file->empty()) {
      spvtools::Error(FuzzDiagnostic, nullptr, {},
                      "The --replay and --interestingness arguments are "
                      "mutually exclusive.");
      return {FuzzActions::STOP, 1};
    }
    return {FuzzActions::REPLAY, 0};
  }

  if (!shrink_transformations_file->empty() ^
      !interestingness_function_file->empty()) {
    spvtools::Error(FuzzDiagnostic, nullptr, {},
                    "Both or neither of the --shrink and --interestingness "
                    "arguments must be provided.");
    return {FuzzActions::STOP, 1};
  }

  if (!shrink_transformations_file->empty()) {
    // The tool is being invoked in shrink mode.
    assert(!interestingness_function_file->empty() &&
           "An error should have been raised if --shrink but not --interesting "
           "was provided.");
    return {FuzzActions::SHRINK, 0};
  }

  return {FuzzActions::FUZZ, 0};
}

bool ParseTransformations(
    const std::string& transformations_file,
    spvtools::fuzz::protobufs::TransformationSequence* transformations) {
  std::ifstream transformations_stream;
  transformations_stream.open(transformations_file,
                              std::ios::in | std::ios::binary);
  auto parse_success =
      transformations->ParseFromIstream(&transformations_stream);
  transformations_stream.close();
  if (!parse_success) {
    spvtools::Error(FuzzDiagnostic, nullptr, {},
                    ("Error reading transformations from file '" +
                     transformations_file + "'")
                        .c_str());
    return false;
  }
  return true;
}

bool Replay(const spv_target_env& target_env,
            const std::vector<uint32_t>& binary_in,
            const spvtools::fuzz::protobufs::FactSequence& initial_facts,
            const std::string& replay_transformations_file,
            std::vector<uint32_t>* binary_out,
            spvtools::fuzz::protobufs::TransformationSequence*
                transformations_applied) {
  spvtools::fuzz::protobufs::TransformationSequence transformation_sequence;
  if (!ParseTransformations(replay_transformations_file,
                            &transformation_sequence)) {
    return false;
  }
  spvtools::fuzz::Replayer replayer(target_env);
  replayer.SetMessageConsumer(spvtools::utils::CLIMessageConsumer);
  auto replay_result_status =
      replayer.Run(binary_in, initial_facts, transformation_sequence,
                   binary_out, transformations_applied);
  return !(replay_result_status !=
           spvtools::fuzz::Replayer::ReplayerResultStatus::kComplete);
}

bool Shrink(const spv_target_env& target_env,
            spv_const_fuzzer_options fuzzer_options,
            const std::vector<uint32_t>& binary_in,
            const spvtools::fuzz::protobufs::FactSequence& initial_facts,
            const std::string& shrink_transformations_file,
            const std::string& interestingness_function_file,
            std::vector<uint32_t>* binary_out,
            spvtools::fuzz::protobufs::TransformationSequence*
                transformations_applied) {
  spvtools::fuzz::protobufs::TransformationSequence transformation_sequence;
  if (!ParseTransformations(shrink_transformations_file,
                            &transformation_sequence)) {
    return false;
  }
  spvtools::fuzz::Shrinker shrinker(target_env,
                                    fuzzer_options->shrinker_step_limit);
  shrinker.SetMessageConsumer(spvtools::utils::CLIMessageConsumer);

  spvtools::fuzz::Shrinker::InterestingnessFunction interestingness_function =
      [interestingness_function_file](std::vector<uint32_t> binary,
                                      uint32_t reductions_applied) -> bool {
    std::stringstream ss;
    ss << "temp_" << std::setw(4) << std::setfill('0') << reductions_applied
       << ".spv";
    const auto spv_file = ss.str();
    const std::string command =
        std::string(interestingness_function_file) + " " + spv_file;
    auto write_file_succeeded =
        WriteFile(spv_file.c_str(), "wb", &binary[0], binary.size());
    (void)(write_file_succeeded);
    assert(write_file_succeeded);
    return ExecuteCommand(command);
  };

  auto shrink_result_status = shrinker.Run(
      binary_in, initial_facts, transformation_sequence,
      interestingness_function, binary_out, transformations_applied);
  return spvtools::fuzz::Shrinker::ShrinkerResultStatus::kComplete ==
             shrink_result_status ||
         spvtools::fuzz::Shrinker::ShrinkerResultStatus::kStepLimitReached ==
             shrink_result_status;
}

bool Fuzz(const spv_target_env& target_env,
          const spvtools::FuzzerOptions& fuzzer_options,
          const std::vector<uint32_t>& binary_in,
          const spvtools::fuzz::protobufs::FactSequence& initial_facts,
          std::vector<uint32_t>* binary_out,
          spvtools::fuzz::protobufs::TransformationSequence*
              transformations_applied) {
  spvtools::fuzz::Fuzzer fuzzer(target_env);
  fuzzer.SetMessageConsumer(spvtools::utils::CLIMessageConsumer);
  auto fuzz_result_status = fuzzer.Run(binary_in, initial_facts, fuzzer_options,
                                       binary_out, transformations_applied);
  if (fuzz_result_status !=
      spvtools::fuzz::Fuzzer::FuzzerResultStatus::kComplete) {
    spvtools::Error(FuzzDiagnostic, nullptr, {}, "Error running fuzzer");
    return false;
  }
  return true;
}

}  // namespace

const auto kDefaultEnvironment = SPV_ENV_UNIVERSAL_1_3;

int main(int argc, const char** argv) {
  std::string in_binary_file;
  std::string out_binary_file;
  std::string replay_transformations_file;
  std::string interestingness_function_file;
  std::string shrink_transformations_file;

  spvtools::FuzzerOptions fuzzer_options;

  FuzzStatus status =
      ParseFlags(argc, argv, &in_binary_file, &out_binary_file,
                 &replay_transformations_file, &interestingness_function_file,
                 &shrink_transformations_file, &fuzzer_options);

  if (status.action == FuzzActions::STOP) {
    return status.code;
  }

  std::vector<uint32_t> binary_in;
  if (!ReadFile<uint32_t>(in_binary_file.c_str(), "rb", &binary_in)) {
    return 1;
  }

  spvtools::fuzz::protobufs::FactSequence initial_facts;
  const std::string dot_spv(".spv");
  std::string in_facts_file =
      in_binary_file.substr(0, in_binary_file.length() - dot_spv.length()) +
      ".facts";
  std::ifstream facts_input(in_facts_file);
  if (facts_input) {
    std::string facts_json_string((std::istreambuf_iterator<char>(facts_input)),
                                  std::istreambuf_iterator<char>());
    facts_input.close();
    if (google::protobuf::util::Status::OK !=
        google::protobuf::util::JsonStringToMessage(facts_json_string,
                                                    &initial_facts)) {
      spvtools::Error(FuzzDiagnostic, nullptr, {}, "Error reading facts data");
      return 1;
    }
  }

  std::vector<uint32_t> binary_out;
  spvtools::fuzz::protobufs::TransformationSequence transformations_applied;

  spv_target_env target_env = kDefaultEnvironment;

  switch (status.action) {
    case FuzzActions::FUZZ:
      if (!Fuzz(target_env, fuzzer_options, binary_in, initial_facts,
                &binary_out, &transformations_applied)) {
        return 1;
      }
      break;
    case FuzzActions::REPLAY:
      if (!Replay(target_env, binary_in, initial_facts,
                  replay_transformations_file, &binary_out,
                  &transformations_applied)) {
        return 1;
      }
      break;
    case FuzzActions::SHRINK: {
      if (!CheckExecuteCommand()) {
        std::cerr << "could not find shell interpreter for executing a command"
                  << std::endl;
        return 1;
      }
      if (!Shrink(target_env, fuzzer_options, binary_in, initial_facts,
                  shrink_transformations_file, interestingness_function_file,
                  &binary_out, &transformations_applied)) {
        return 1;
      }
    } break;
    default:
      assert(false && "Unknown fuzzer action.");
      break;
  }

  if (!WriteFile<uint32_t>(out_binary_file.c_str(), "wb", binary_out.data(),
                           binary_out.size())) {
    spvtools::Error(FuzzDiagnostic, nullptr, {}, "Error writing out binary");
    return 1;
  }

  std::string output_file_prefix =
      out_binary_file.substr(0, out_binary_file.length() - dot_spv.length());
  std::ofstream transformations_file;
  transformations_file.open(output_file_prefix + ".transformations",
                            std::ios::out | std::ios::binary);
  bool success =
      transformations_applied.SerializeToOstream(&transformations_file);
  transformations_file.close();
  if (!success) {
    spvtools::Error(FuzzDiagnostic, nullptr, {},
                    "Error writing out transformations binary");
    return 1;
  }

  std::string json_string;
  auto json_options = google::protobuf::util::JsonOptions();
  json_options.add_whitespace = true;
  auto json_generation_status = google::protobuf::util::MessageToJsonString(
      transformations_applied, &json_string, json_options);
  if (json_generation_status != google::protobuf::util::Status::OK) {
    spvtools::Error(FuzzDiagnostic, nullptr, {},
                    "Error writing out transformations in JSON format");
    return 1;
  }

  std::ofstream transformations_json_file(output_file_prefix +
                                          ".transformations_json");
  transformations_json_file << json_string;
  transformations_json_file.close();

  return 0;
}
