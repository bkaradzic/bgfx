/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2017, assimp team


All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the following 
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

/** @file  Export.cpp
 *  @brief Implementation of the 'assimp export' utility
 */

#include "Main.h"

#ifndef ASSIMP_BUILD_NO_EXPORT

const char* AICMD_MSG_EXPORT_HELP_E = 
"assimp export <model> [<out>] [-f<h>] [common parameters]\n"
"\t -f<h> Specify the file format. If omitted, the output format is \n"
"\t\tderived from the file extension of the given output file  \n"
"\t[See the assimp_cmd docs for a full list of all common parameters]  \n"
;


// -----------------------------------------------------------------------------------
size_t GetMatchingFormat(const std::string& outf,bool byext=false) 
{
	for(size_t i = 0, end = globalExporter->GetExportFormatCount(); i < end; ++i) {
		const aiExportFormatDesc* const e =  globalExporter->GetExportFormatDescription(i);
		if (outf == (byext ? e->fileExtension : e->id)) {
			return i;
		}
	}
	return SIZE_MAX;
}


// -----------------------------------------------------------------------------------
int Assimp_Export(const char* const* params, unsigned int num)
{
	const char* const invalid = "assimp export: Invalid number of arguments. See \'assimp export --help\'\n";
	if (num < 1) {
		printf(invalid);
		return 1;
	}

	// --help
	if (!strcmp( params[0], "-h") || !strcmp( params[0], "--help") || !strcmp( params[0], "-?") ) {
		printf("%s",AICMD_MSG_EXPORT_HELP_E);
		return 0;
	}

	std::string in  = std::string(params[0]);
	std::string out = (num > 1 ? std::string(params[1]) : "-"), outext;

	// 
	const std::string::size_type s = out.find_last_of('.');
	if (s != std::string::npos) {
		outext = out.substr(s+1);
		out = out.substr(0,s);
	}

	// get import flags
	ImportData import;
	ProcessStandardArguments(import,params+1,num-1);

	// process other flags
	std::string outf = "";
	for (unsigned int i = (out[0] == '-' ? 1 : 2); i < num;++i)		{
		if (!params[i]) {
			continue;
		}
		if (!strncmp( params[i], "-f",2)) {
			outf = std::string(params[i]+2);
		}
		else if ( !strncmp( params[i], "--format=",9)) {
			outf = std::string(params[i]+9);
		}
	}

	std::transform(outf.begin(),outf.end(),outf.begin(),::tolower);

	// convert the output format to a format id
	size_t outfi = GetMatchingFormat(outf);
	if (outfi == SIZE_MAX) {
		if (outf.length()) {
			printf("assimp export: warning, format id \'%s\' is unknown\n",outf.c_str());
		}

		// retry to see if we know it as file extension
		outfi = GetMatchingFormat(outf,true);
		if (outfi == SIZE_MAX) {
			// retry to see if we know the file extension of the output file
			outfi = GetMatchingFormat(outext,true);

			if (outfi == SIZE_MAX) {
				// still no match -> failure
				printf("assimp export: no output format specified and I failed to guess it\n");
				return -23;
			}
		}
		else {
			outext = outf;
		}
	}
	
	// if no output file is specified, take the file name from input file
	if (out[0] == '-') {
		std::string::size_type s = in.find_last_of('.');
		if (s == std::string::npos) {
			s = in.length();
		}

		out = in.substr(0,s);
	}

	const aiExportFormatDesc* const e =  globalExporter->GetExportFormatDescription(outfi);
	printf("assimp export: select file format: \'%s\' (%s)\n",e->id,e->description);
	
	// import the  model
	const aiScene* scene = ImportModel(import,in);
	if (!scene) {
		return -39;
	}

	// derive the final file name
	out += "."+outext;

	// and call the export routine
	if(!ExportModel(scene, import, out,e->id)) {
		return -25;
	}
	printf("assimp export: wrote output file: %s\n",out.c_str());
	return 0;
}

#endif // no export
 
