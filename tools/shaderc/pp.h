/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx/blob/master/LICENSE
 */

#ifndef BX_PP_H_HEADER_GUARD
#define BX_PP_H_HEADER_GUARD

#include <bx/filepath.h>
#include <bx/readerwriter.h>
#include <bx/string.h>

namespace bx { struct AllocatorI; }

namespace shaderc
{
	/// Position in the source being preprocessed.
	///
	struct SourceLocation
	{
		/// Default constructor.
		///
		SourceLocation()
			: line(0) {}

		/// Constructor with specific file, and line number.
		///
		SourceLocation(const bx::StringView& _file, uint32_t _line)
			: file(_file), line(_line) {}

		bx::StringView file; //!< File the location is in.
		uint32_t       line; //!< One-based line number inside `file`.
	};

	/// Host hooks for the preprocessor.
	///
	/// All file IO and diagnostics are routed through these so the engine itself never touches
	/// the filesystem and stays reentrant. One `Preprocessor` instance is one independent unit
	/// of work.
	///
	struct BX_NO_VTABLE PreprocessorCallbackI
	{
		///
		virtual ~PreprocessorCallbackI() = 0;

		/// Resolve and read `#include`.
		///
		/// @param[in]  _name Include name, without quotes or angle brackets.
		/// @param[in]  _isSystem True for `<...>`, and false for `"..."`.
		/// @param[in]  _from File holding the directive, so that quoted include can be resolved
		///   relative to it.
		/// @param[out] _writer File text is written here. Preprocessor owns the storage, and
		///   copies it out before this call returns, so nothing has to outlive the call.
		/// @param[out] _outPath Resolved path, used for dependency reporting.
		/// @param[out] _err Error, set if writing file text fails.
		///
		/// @returns True if include is resolved and read, otherwise returns false.
		///
		virtual bool include(
			  const bx::StringView& _name
			, bool _isSystem
			, const bx::StringView& _from
			, bx::WriterI* _writer
			, bx::FilePath& _outPath
			, bx::Error* _err
			) = 0;

		/// Reports file the output depends on. It's called for the main source, and for every
		/// opened include.
		///
		/// @param[in] _path Resolved path of the file.
		///
		/// @remarks Default implementation ignores dependencies.
		///
		virtual void depend(const bx::StringView& _path) = 0;

		/// Diagnostic sink.
		///
		/// @param[in] _isError True for `#error` and hard failures, and false for `#warning`.
		/// @param[in] _location Source position the diagnostic originated from.
		/// @param[in] _message Diagnostic message.
		///
		virtual void message(
			  bool _isError
			, const SourceLocation& _location
			, const bx::StringView& _message
			) = 0;
	};

	inline PreprocessorCallbackI::~PreprocessorCallbackI()
	{
	}

	/// C-style preprocessor.
	///
	/// Supports object and function macros (including variadics and `__VA_OPT__`), `#` and `##`,
	/// `#if`, `#ifdef`, `#ifndef`, `#elif`, `#elifdef`, `#elifndef`, `#else`, `#endif`,
	/// `#include`, `#line`, `#pragma once`, `#error`, `#warning`, and `__LINE__`, `__FILE__` and
	/// `__COUNTER__`. There are no trigraphs or digraphs.
	///
	class Preprocessor
	{
		BX_CLASS(Preprocessor
			, NO_DEFAULT_CTOR
			, NO_COPY
			);

	public:
		/// Constructor.
		///
		/// @param[in] _callback Host hooks. It must outlive Preprocessor.
		/// @param[in] _allocator Allocator. It must not be NULL, and it must outlive
		///   Preprocessor.
		///
		Preprocessor(PreprocessorCallbackI& _callback, bx::AllocatorI* _allocator);

		/// Destructor.
		///
		~Preprocessor();

		/// Predefine macro, mirroring `-D` command-line define.
		///
		/// @param[in] _define Macro in `NAME`, `NAME=VALUE`, or `NAME(a,b)=body` form.
		///
		void define(const bx::StringView& _define);

		/// Remove predefined, or previously defined macro.
		///
		/// @param[in] _name Macro name.
		///
		void undefine(const bx::StringView& _name);

		/// Emit `#line <line> "<file>"` directives into the output so that consumer can map the
		/// result back to the original source.
		///
		/// @param[in] _emit True to emit `#line` directives.
		///
		/// @remarks It's off by default. Directives, skipped `#if` branches, and `#include` all
		///   break 1:1 line mapping, so this is the only way to get meaningful positions, but it
		///   requires consumer to understand `#line`.
		///
		void setEmitLineDirectives(bool _emit);

		/// Preprocess source.
		///
		/// @param[in]  _name Source name, used for diagnostics and `__FILE__`.
		/// @param[in]  _source Source to preprocess.
		/// @param[out] _writer Result is written here.
		/// @param[out] _err Error, set if writing result fails.
		///
		/// @returns True on success, or false if `#error`, or hard error was reported.
		///
		bool preprocess(
			  const bx::StringView& _name
			, const bx::StringView& _source
			, bx::WriterI* _writer
			, bx::Error* _err
			);

	private:
		struct PreprocessorImpl* m_impl;
	};

} // namespace shaderc

#endif // BX_PP_H_HEADER_GUARD
