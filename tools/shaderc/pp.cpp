/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx/blob/master/LICENSE
 */

#include "pp.h"

#include <bx/allocator.h>
#include <bx/filepath.h>
#include <bx/scanner.h>
#include <bx/sort.h>

#include <tinystl/vector.h>

namespace shaderc
{
	namespace
	{
		namespace stl = tinystl;

		static constexpr uint32_t kArenaBlockSize  = 64<<10;
		static constexpr uint32_t kMaxIncludeDepth = 200;

		enum class Kind : uint8_t
		{
			Eof,
			Newline,
			Identifier,
			Number,
			String,
			Char,
			Punct,
			Placemarker,

			Count
		};

		struct HideNode
		{
			bx::StringView  name;
			const HideNode* next;
		};

		struct Token
		{
			bx::StringView  lexeme;
			SourceLocation  location;
			const HideNode* hide;
			Kind            kind;
			bool            spaceBefore;
		};

		Token makeToken(Kind _kind, const bx::StringView& _lexeme)
		{
			return
			{
				.lexeme      = _lexeme,
				.location    = SourceLocation(),
				.hide        = NULL,
				.kind        = _kind,
				.spaceBefore = false,
			};
		}

		bool isPunct(const Token& _token, const bx::StringView& _lexeme)
		{
			return true
				&& Kind::Punct == _token.kind
				&& isEqual(_token.lexeme, _lexeme)
				;
		}

		bool isIdent(const Token& _token, const bx::StringView& _lexeme)
		{
			return true
				&& Kind::Identifier == _token.kind
				&& isEqual(_token.lexeme, _lexeme)
				;
		}

		Kind classify(const bx::StringView& _text)
		{
			if (_text.isEmpty() )
			{
				return Kind::Placemarker;
			}

			const char ch = *_text.getPtr();

			if (bx::isIdentStart(ch) )
			{
				return Kind::Identifier;
			}

			if (bx::isNumeric(ch)
			|| ('.' == ch && 1 < _text.getLength() && bx::isNumeric(_text.getPtr()[1]) ) )
			{
				return Kind::Number;
			}

			return Kind::Punct;
		}

		class Arena
		{
			BX_CLASS(Arena
				, NO_DEFAULT_CTOR
				, NO_COPY
				);

		public:
			Arena(bx::AllocatorI* _allocator)
				: m_allocator(_allocator)
				, m_head(NULL)
			{
			}

			bx::AllocatorI* getAllocator() const
			{
				return m_allocator;
			}

			~Arena()
			{
				reset();
			}

			void* allocate(uint32_t _size)
			{
				_size = bx::alignUp(_size, 16);

				if (NULL == m_head
				||  m_head->size < m_head->used + _size)
				{
					const uint32_t blockSize = bx::max(_size, kArenaBlockSize);

					Block* block = (Block*)bx::alloc(m_allocator, sizeof(Block) + blockSize);
					*block =
					{
						.prev = m_head,
						.size = blockSize,
						.used = 0,
					};

					m_head = block;
				}

				void* ptr = (char*)(m_head + 1) + m_head->used;
				m_head->used += _size;

				return ptr;
			}

			template<typename Ty>
			Ty* allocate(uint32_t _num)
			{
				return (Ty*)allocate(_num * uint32_t(sizeof(Ty) ) );
			}

			bx::StringView intern(const bx::StringView& _str)
			{
				const uint32_t len = _str.getLength();

				if (0 == len)
				{
					return bx::StringView();
				}

				char* dst = allocate<char>(len);
				bx::memCopy(dst, _str.getPtr(), len);

				return bx::StringView(dst, len);
			}

			bx::StringView concat(const bx::StringView* _parts, uint32_t _num)
			{
				uint32_t total = 0;
				for (uint32_t ii = 0; ii < _num; ++ii)
				{
					total += _parts[ii].getLength();
				}

				if (0 == total)
				{
					return bx::StringView();
				}

				char* dst = allocate<char>(total);
				uint32_t offset = 0;

				for (uint32_t ii = 0; ii < _num; ++ii)
				{
					const uint32_t len = _parts[ii].getLength();
					bx::memCopy(dst + offset, _parts[ii].getPtr(), len);
					offset += len;
				}

				return bx::StringView(dst, total);
			}

			bx::StringView concat(const bx::StringView& _lhs, const bx::StringView& _rhs)
			{
				const bx::StringView parts[] = { _lhs, _rhs };
				return concat(parts, BX_COUNTOF(parts) );
			}

			void reset()
			{
				while (NULL != m_head)
				{
					Block* prev = m_head->prev;
					bx::free(m_allocator, m_head);
					m_head = prev;
				}
			}

		private:
			struct Block
			{
				Block*   prev;
				uint32_t size;
				uint32_t used;
			};

			bx::AllocatorI* m_allocator;
			Block*          m_head;
		};

		static const bx::StringLiteral s_puncts[] =
		{
			"<<=",
			">>=",
			"...",
			"##",
			"<<",
			">>",
			"<=",
			">=",
			"==",
			"!=",
			"&&",
			"||",
			"->",
			"++",
			"--",
			"+=",
			"-=",
			"*=",
			"/=",
			"%=",
			"&=",
			"|=",
			"^=",
			"::",
		};

		bool isNumberPart(char _ch)
		{
			return bx::isIdentChar(_ch)
				|| '.' == _ch
				;
		}

		class Lexer
		{
			BX_CLASS(Lexer
				, NO_DEFAULT_CTOR
				, NO_COPY
				);

		public:
			Lexer(Arena& _arena, const bx::StringView& _input, Token* _tokens, uint32_t _max)
				: m_arena(_arena)
				, m_scanner(_input)
				, m_input(_input)
				, m_tokens(_tokens)
				, m_max(_max)
				, m_num(0)
				, m_unterminatedComment(false)
			{
			}

			bool hadUnterminatedComment() const
			{
				return m_unterminatedComment;
			}

			uint32_t run()
			{
				for (;;)
				{
					const bool spaceBefore = skipSpace();

					if (m_scanner.isDone() )
					{
						break;
					}

					const uint32_t line = m_scanner.getLine();

					const bx::StringView newLine = m_scanner.accept('\n');

					if (!newLine.isEmpty() )
					{
						emit(Kind::Newline, newLine, spaceBefore, line);
						continue;
					}

					const char ch = peek();

					if (bx::isIdentStart(ch) )
					{
						const bx::StringView ident = acceptSpliced(
							  m_scanner.accept(bx::Scanner::Class::Identifier)
							, bx::isIdentChar
							, [this]() { return m_scanner.acceptWhile(bx::isIdentChar); }
							);

						emit(Kind::Identifier, ident, spaceBefore, line);
						continue;
					}

					if (bx::isNumeric(ch)
					|| ('.' == ch && bx::isNumeric(peek(1) ) ) )
					{
						const bx::StringView number = acceptSpliced(
							  acceptNumber()
							, isNumberPart
							, [this]() { return acceptNumber(); }
							);

						emit(Kind::Number, number, spaceBefore, line);
						continue;
					}

					if ('"' == ch)
					{
						emit(Kind::String, acceptQuoted('"'), spaceBefore, line);
						continue;
					}

					if ('\'' == ch)
					{
						emit(Kind::Char, acceptQuoted('\''), spaceBefore, line);
						continue;
					}

					emit(Kind::Punct, acceptPunct(), spaceBefore, line);
				}

				return m_num;
			}

		private:
			char peek(int32_t _offset = 0) const
			{
				const char* ptr = m_scanner.getCursor().getPtr() + _offset;

				return ptr < m_input.getTerm() ? *ptr : '\0';
			}

			bool skipSpace()
			{
				bool space = false;

				for (;;)
				{
					if (!m_scanner.acceptWhile(bx::isSpaceHoriz).isEmpty() )
					{
						space = true;
						continue;
					}

					if (skipLineContinuation()
					||  skipComment() )
					{
						space = true;
						continue;
					}

					break;
				}

				return space;
			}

			bool skipLineContinuation()
			{
				const bx::StringView cursor = m_scanner.getCursor();

				if (m_scanner.accept('\\').isEmpty() )
				{
					return false;
				}

				m_scanner.accept('\r');

				if (!m_scanner.accept('\n').isEmpty() )
				{
					return true;
				}

				m_scanner.seek(cursor);

				return false;
			}

			bool skipComment()
			{
				if (!m_scanner.accept("//").isEmpty() )
				{
					m_scanner.acceptUntil(bx::Scanner::Class::EndOfLine);
					return true;
				}

				if (m_scanner.accept("/*").isEmpty() )
				{
					return false;
				}

				uint32_t depth = 1;

				while (!m_scanner.isDone() )
				{
					if (!m_scanner.accept("/*").isEmpty() )
					{
						++depth;
						continue;
					}

					if (!m_scanner.accept("*/").isEmpty() )
					{
						if (0 == --depth)
						{
							break;
						}

						continue;
					}

					m_scanner.accept();
				}

				m_unterminatedComment = m_unterminatedComment || 0 != depth;

				return true;
			}

			bool spliceJoins(bool (*_isPart)(char) )
			{
				const bx::StringView cursor = m_scanner.getCursor();

				if (!skipLineContinuation() )
				{
					return false;
				}

				if (_isPart(peek() ) )
				{
					return true;
				}

				m_scanner.seek(cursor);

				return false;
			}

			template<typename AcceptFn>
			bx::StringView acceptSpliced(bx::StringView _lexeme, bool (*_isPart)(char), AcceptFn _accept)
			{
				while (spliceJoins(_isPart) )
				{
					const bx::StringView parts[] = { _lexeme, _accept() };
					_lexeme = m_arena.concat(parts, BX_COUNTOF(parts) );
				}

				return _lexeme;
			}

			void emit(
				  Kind _kind
				, const bx::StringView& _lexeme
				, bool _spaceBefore
				, uint32_t _line
				)
			{
				if (m_num >= m_max)
				{
					return;
				}

				m_tokens[m_num++] =
				{
					.lexeme      = _lexeme,
					.location    = SourceLocation(bx::StringView(), _line),
					.hide        = NULL,
					.kind        = _kind,
					.spaceBefore = _spaceBefore,
				};
			}

			bx::StringView acceptNumber()
			{
				const bx::StringView cursor = m_scanner.getCursor();

				m_scanner.accept();

				for (;;)
				{
					const char ch = peek();

					if ('e' == ch || 'E' == ch
					||  'p' == ch || 'P' == ch)
					{
						m_scanner.accept();
						m_scanner.accept('+', '-');
						continue;
					}

					if (bx::isIdentChar(ch)
					||  '.' == ch)
					{
						m_scanner.accept();
						continue;
					}

					break;
				}

				return m_scanner.between(cursor);
			}

			bx::StringView acceptQuoted(char _quote)
			{
				const bx::StringView cursor = m_scanner.getCursor();

				m_scanner.accept(_quote);

				while (!m_scanner.isDone()
				&&     m_scanner.peek('\n').isEmpty() )
				{
					if (!m_scanner.accept('\\').isEmpty() )
					{
						m_scanner.accept();
						continue;
					}

					if (!m_scanner.accept(_quote).isEmpty() )
					{
						break;
					}

					m_scanner.accept();
				}

				return m_scanner.between(cursor);
			}

			bx::StringView acceptPunct()
			{
				for (uint32_t ii = 0; ii < BX_COUNTOF(s_puncts); ++ii)
				{
					const bx::StringView punct = m_scanner.accept(s_puncts[ii]);

					if (!punct.isEmpty() )
					{
						return punct;
					}
				}

				return m_scanner.accept();
			}

			Arena&         m_arena;
			bx::Scanner    m_scanner;
			bx::StringView m_input;
			Token*         m_tokens;
			uint32_t       m_max;
			uint32_t       m_num;
			bool           m_unterminatedComment;
		};

		struct Macro
		{
			bx::StringView              name;
			stl::vector<bx::StringView> params;
			const Token*                body;
			uint32_t                    bodyNum;
			bool                        isFunction;
			bool                        isVariadic;
		};

		struct Frame
		{
			bx::StringView name;
			bx::StringView presumedName;
			const Token*   tokens;
			uint32_t       num;
			uint32_t       pos;
			int32_t        lineDelta;
			bool           isInclude;
		};

		static const bx::StringView& frameName(const Frame& _frame)
		{
			return _frame.presumedName.isEmpty()
				? _frame.name
				: _frame.presumedName
				;
		}

		static bx::StringView pathOf(const bx::FilePath& _filePath)
		{
			return _filePath.isEmpty()
				? bx::StringView()
				: bx::StringView(_filePath)
				;
		}

		struct Cond
		{
			bool active;
			bool taken;
			bool parent;
			bool seenElse;
		};

		class Worklist
		{
			BX_CLASS(Worklist
				, NO_DEFAULT_CTOR
				, NO_COPY
				);

		public:
			Worklist(const stl::vector<Token>& _tokens)
				: m_tokens(_tokens)
				, m_head(0)
			{
			}

			bool isEmpty() const
			{
				return m_head >= m_tokens.size();
			}

			const Token& getFront() const
			{
				return m_tokens[m_head];
			}

			void popFront()
			{
				++m_head;
			}

			void prepend(const stl::vector<Token>& _tokens)
			{
				const uint32_t num = uint32_t(_tokens.size() );

				if (0 == num)
				{
					return;
				}

				if (num <= m_head)
				{
					m_head -= num;

					for (uint32_t ii = 0; ii < num; ++ii)
					{
						m_tokens[m_head + ii] = _tokens[ii];
					}

					return;
				}

				stl::vector<Token> tmp;
				tmp.reserve(num + m_tokens.size() - m_head);

				for (uint32_t ii = 0; ii < num; ++ii)
				{
					tmp.push_back(_tokens[ii]);
				}

				const uint32_t numTokens = uint32_t(m_tokens.size() );

				for (uint32_t ii = m_head; ii < numTokens; ++ii)
				{
					tmp.push_back(m_tokens[ii]);
				}

				m_tokens.swap(tmp);
				m_head = 0;
			}

			const Token* begin() const
			{
				return m_tokens.data() + m_head;
			}

			const Token* end() const
			{
				return m_tokens.data() + m_tokens.size();
			}

		private:
			stl::vector<Token> m_tokens;
			uint32_t           m_head;
		};

		enum class Op : uint8_t
		{
			NotEq,
			Mod,
			BitAnd,
			LogicalAnd,
			Mul,
			Add,
			Sub,
			Div,
			Lt,
			Shl,
			LtEq,
			Eq,
			Gt,
			GtEq,
			Shr,
			BitXor,
			BitOr,
			LogicalOr,

			Count
		};

		struct OpInfo
		{
			bx::StringView lexeme;
			int32_t        precedence;

			static int32_t cmpFn(const void* _lhs, const void* _rhs)
			{
				return bx::strCmp(
					  ( (const OpInfo*)_lhs)->lexeme
					, ( (const OpInfo*)_rhs)->lexeme
					);
			}
		};

		static const OpInfo s_ops[] =
		{
			{ "!=",  6 },
			{ "%",  10 },
			{ "&",   5 },
			{ "&&",  2 },
			{ "*",  10 },
			{ "+",   9 },
			{ "-",   9 },
			{ "/",  10 },
			{ "<",   7 },
			{ "<<",  8 },
			{ "<=",  7 },
			{ "==",  6 },
			{ ">",   7 },
			{ ">=",  7 },
			{ ">>",  8 },
			{ "^",   4 },
			{ "|",   3 },
			{ "||",  1 },
		};
		static_assert(uint8_t(Op::Count) == BX_COUNTOF(s_ops), "s_ops must match Op.");

		Op findOp(const bx::StringView& _lexeme)
		{
			const int32_t idx = bx::binarySearch(_lexeme, s_ops, BX_COUNTOF(s_ops), sizeof(OpInfo), OpInfo::cmpFn);

			return 0 <= idx ? Op(idx) : Op::Count;
		}

		const OpInfo& getOpInfo(Op _op)
		{
			return s_ops[uint8_t(_op)];
		}

		int32_t toDigit(char _ch)
		{
			if (bx::isNumeric(_ch) )
			{
				return _ch - '0';
			}

			if (bx::isHexNum(_ch) )
			{
				return (bx::toLower(_ch) - 'a') + 10;
			}

			return -1;
		}
	}

	struct PreprocessorImpl
	{
		BX_CLASS(PreprocessorImpl
			, NO_DEFAULT_CTOR
			, NO_COPY
			);

		PreprocessorImpl(PreprocessorCallbackI& _callback, bx::AllocatorI* _allocator)
			: m_callback(_callback)
			, m_arena(_allocator)
			, m_out(NULL)
			, m_includeDepth(0)
			, m_outLocation(bx::StringView(), 1)
			, m_emitLine(false)
			, m_inCondition(false)
			, m_ok(true)
		{
		}

		void syncLine(const SourceLocation& _location)
		{
			if (!m_emitLine
			||  0 == _location.line)
			{
				return;
			}

			if (_location.line == m_outLocation.line
			&&  isEqual(_location.file, m_outLocation.file) )
			{
				return;
			}

			const bx::FilePath filePath(_location.file);
			const bx::StringView file = pathOf(filePath);

			char tmp[bx::kMaxFilePath + 64];
			const int32_t total = bx::snprintf(tmp, BX_COUNTOF(tmp), "#line %u \"%.*s\"\n"
				, _location.line
				, file.getLength()
				, file.getPtr()
				);
			append(bx::StringView(tmp, bx::min(total, int32_t(BX_COUNTOF(tmp) ) - 1) ) );

			m_outLocation = _location;
		}

		void report(bool _isError, const bx::StringView& _message)
		{
			m_callback.message(_isError, m_location, _message);

			if (_isError)
			{
				m_ok = false;
			}
		}

		void error(const bx::StringView& _message)
		{
			report(true, _message);
		}

		void pushFrame(const bx::StringView& _name, const bx::StringView& _source, bool _isInclude)
		{
			const uint32_t max = _source.getLength() + 16;
			Token* tokens = m_arena.allocate<Token>(max + 1 /* space for token if NL at EOF is missing */);

			Lexer lexer(m_arena, _source, tokens, max);

			uint32_t num = lexer.run();

			if (0 < num)
			{
				const Token& lastToken = tokens[num-1];

				if (Kind::Newline != lastToken.kind)
				{
					tokens[num++] =
					{
						.lexeme      = "\n",
						.location    = lastToken.location,
						.hide        = NULL,
						.kind        = Kind::Newline,
						.spaceBefore = false,
					};
				}
			}

			const Frame frame =
			{
				.name         = _name,
				.presumedName = bx::StringView(),
				.tokens       = tokens,
				.num          = num,
				.pos          = 0,
				.lineDelta    = 0,
				.isInclude    = _isInclude,
			};

			m_frames.push_back(frame);

			m_location.file = _name;

			if (lexer.hadUnterminatedComment() )
			{
				m_location.line = 0;
				error("Unterminated comment");
			}
		}

		bool next(Token& _outToken)
		{
			if (!m_pending.empty() )
			{
				_outToken = m_pending.back();
				m_pending.pop_back();

				return true;
			}

			while (!m_frames.empty() )
			{
				Frame& frame = m_frames.back();

				if (frame.pos < frame.num)
				{
					_outToken = frame.tokens[frame.pos++];
					m_location = SourceLocation(frameName(frame), uint32_t(int32_t(_outToken.location.line) + frame.lineDelta) );
					_outToken.location = m_location;

					return true;
				}

				const bool wasInclude = frame.isInclude;
				m_frames.pop_back();

				if (wasInclude)
				{
					--m_includeDepth;
				}

				if (!m_frames.empty() )
				{
					m_location.file = frameName(m_frames.back() );
				}
			}

			return false;
		}

		void unget(const Token& _token)
		{
			m_pending.push_back(_token);
		}

		void readLine(stl::vector<Token>& _outTokens)
		{
			Token token;

			while (next(token) )
			{
				if (Kind::Newline == token.kind)
				{
					break;
				}

				_outTokens.push_back(token);
			}
		}

		bool readLineKeepNewline(stl::vector<Token>& _outTokens)
		{
			Token token;

			while (next(token) )
			{
				_outTokens.push_back(token);

				if (Kind::Newline == token.kind)
				{
					return true;
				}
			}

			return false;
		}

		void skipLine()
		{
			Token token;

			while (next(token) )
			{
				if (Kind::Newline == token.kind)
				{
					break;
				}
			}
		}

		bool condActive() const
		{
			return m_cond.empty() || m_cond.back().active;
		}

		const Macro* findMacro(const bx::StringView& _name) const
		{
			for (uint32_t ii = 0, num = uint32_t(m_macros.size() ); ii < num; ++ii)
			{
				if (isEqual(m_macros[ii].name, _name) )
				{
					return &m_macros[ii];
				}
			}

			return NULL;
		}

		void removeMacro(const bx::StringView& _name)
		{
			for (uint32_t ii = 0, num = uint32_t(m_macros.size() ); ii < num; ++ii)
			{
				if (isEqual(m_macros[ii].name, _name) )
				{
					m_macros.erase(m_macros.begin() + ii);
					return;
				}
			}
		}

		bool isDefined(const bx::StringView& _name) const
		{
			return false
				|| NULL != findMacro(_name)
				|| isEqual(_name, "__LINE__")
				|| isEqual(_name, "__FILE__")
				|| isEqual(_name, "__COUNTER__")
				;
		}

		bool hideContains(const HideNode* _hide, const bx::StringView& _name) const
		{
			for (const HideNode* node = _hide; NULL != node; node = node->next)
			{
				if (isEqual(node->name, _name) )
				{
					return true;
				}
			}

			return false;
		}

		const HideNode* hideAdd(const HideNode* _hide, const bx::StringView& _name)
		{
			if (hideContains(_hide, _name) )
			{
				return _hide;
			}

			HideNode* node = m_arena.allocate<HideNode>(1);
			*node =
			{
				.name = _name,
				.next = _hide,
			};

			return node;
		}

		const HideNode* hideUnion(const HideNode* _lhs, const HideNode* _rhs)
		{
			const HideNode* result = _lhs;

			for (const HideNode* node = _rhs; NULL != node; node = node->next)
			{
				result = hideAdd(result, node->name);
			}

			return result;
		}

		const HideNode* hideIntersect(const HideNode* _lhs, const HideNode* _rhs)
		{
			const HideNode* result = NULL;

			for (const HideNode* node = _lhs; NULL != node; node = node->next)
			{
				if (hideContains(_rhs, node->name) )
				{
					result = hideAdd(result, node->name);
				}
			}

			return result;
		}

		int32_t findParam(const Macro& _macro, const bx::StringView& _name) const
		{
			for (uint32_t ii = 0, num = uint32_t(_macro.params.size() ); ii < num; ++ii)
			{
				if (isEqual(_macro.params[ii], _name) )
				{
					return int32_t(ii);
				}
			}

			return -1;
		}

		bool isParam(const Macro& _macro, const Token& _token) const
		{
			if (Kind::Identifier != _token.kind)
			{
				return false;
			}

			if (_macro.isVariadic
			&&  isEqual(_token.lexeme, "__VA_ARGS__") )
			{
				return true;
			}

			return -1 != findParam(_macro, _token.lexeme);
		}

		void selectActual(
			  const Macro& _macro
			, const stl::vector<stl::vector<Token> >& _actuals
			, const bx::StringView& _name
			, stl::vector<Token>& _outTokens
			)
		{
			if (_macro.isVariadic
			&&  isEqual(_name, "__VA_ARGS__") )
			{
				const uint32_t first = uint32_t(_macro.params.size() );

				for (uint32_t ii = first, num = uint32_t(_actuals.size() ); ii < num; ++ii)
				{
					if (ii > first)
					{
						_outTokens.push_back(makeToken(Kind::Punct, ",") );
					}

					const stl::vector<Token>& actual = _actuals[ii];

					for (uint32_t jj = 0, numArg = uint32_t(actual.size() ); jj < numArg; ++jj)
					{
						_outTokens.push_back(actual[jj]);
					}
				}

				return;
			}

			const int32_t idx = findParam(_macro, _name);

			if (0 <= idx
			&&  uint32_t(idx) < _actuals.size() )
			{
				_outTokens = _actuals[idx];
			}
		}

		bx::StringView stringize(const stl::vector<Token>& _tokens)
		{
			stl::vector<char> buffer;
			buffer.push_back('"');

			for (uint32_t ii = 0, num = uint32_t(_tokens.size() ); ii < num; ++ii)
			{
				const Token& token = _tokens[ii];

				if (0 != ii
				&&  token.spaceBefore)
				{
					buffer.push_back(' ');
				}

				const bx::StringView& lexeme = token.lexeme;

				const bool escape = false
					|| Kind::String == token.kind
					|| Kind::Char   == token.kind
					;

				for (const char* ptr = lexeme.getPtr(); ptr != lexeme.getTerm(); ++ptr)
				{
					if (escape
					&&  ('"'  == *ptr
					||   '\\' == *ptr) )
					{
						buffer.push_back('\\');
					}

					buffer.push_back(*ptr);
				}
			}

			buffer.push_back('"');

			return m_arena.intern(bx::StringView(buffer.data(), int32_t(buffer.size() ) ) );
		}

		bx::StringView rebuild(const stl::vector<Token>& _tokens)
		{
			stl::vector<char> buffer;

			for (uint32_t ii = 0, num = uint32_t(_tokens.size() ); ii < num; ++ii)
			{
				const Token& token = _tokens[ii];

				if (0 != ii
				&&  token.spaceBefore)
				{
					buffer.push_back(' ');
				}

				const bx::StringView& lexeme = token.lexeme;

				for (const char* ptr = lexeme.getPtr(); ptr != lexeme.getTerm(); ++ptr)
				{
					buffer.push_back(*ptr);
				}
			}

			return m_arena.intern(bx::StringView(buffer.data(), int32_t(buffer.size() ) ) );
		}

		void paste(stl::vector<Token>& _inOutTokens, const Token& _rhs)
		{
			if (Kind::Placemarker == _rhs.kind)
			{
				return;
			}

			while (!_inOutTokens.empty()
			&&     Kind::Placemarker == _inOutTokens.back().kind)
			{
				_inOutTokens.pop_back();
			}

			if (_inOutTokens.empty() )
			{
				_inOutTokens.push_back(_rhs);
				return;
			}

			Token& lhs = _inOutTokens.back();

			if (Kind::Placemarker == lhs.kind)
			{
				lhs = _rhs;
				return;
			}

			const bx::StringView glued = m_arena.concat(lhs.lexeme, _rhs.lexeme);
			lhs.lexeme = glued;
			lhs.kind   = classify(glued);
		}

		bool hasVaOpt(const Token* _body, uint32_t _num) const
		{
			for (uint32_t ii = 0; ii < _num; ++ii)
			{
				if (Kind::Identifier == _body[ii].kind
				&&  isEqual(_body[ii].lexeme, "__VA_OPT__") )
				{
					return true;
				}
			}

			return false;
		}

		void expandVaOpt(const Token* _body, uint32_t _num, bool _keep, stl::vector<Token>& _outTokens)
		{
			for (uint32_t ii = 0; ii < _num; )
			{
				const Token& token = _body[ii];

				if (Kind::Identifier != token.kind
				||  !isEqual(token.lexeme, "__VA_OPT__")
				||  ii + 1 >= _num
				||  !isPunct(_body[ii+1], "(") )
				{
					_outTokens.push_back(token);
					++ii;
					continue;
				}

				uint32_t depth = 1;
				uint32_t jj    = ii + 2;

				for (; jj < _num && 0 != depth; ++jj)
				{
					if      (isPunct(_body[jj], "(") ) { ++depth; }
					else if (isPunct(_body[jj], ")") ) { --depth; }
				}

				const uint32_t first = ii + 2;
				const uint32_t last  = jj - 1;

				if (_keep
				&&  last > first)
				{
					stl::vector<Token> inner;
					expandVaOpt(_body + first, last - first, _keep, inner);

					if (!inner.empty() )
					{
						inner[0].spaceBefore = token.spaceBefore;
					}

					for (uint32_t kk = 0, numInner = uint32_t(inner.size() ); kk < numInner; ++kk)
					{
						_outTokens.push_back(inner[kk]);
					}
				}
				else
				{
					Token placemarker = makeToken(Kind::Placemarker, bx::StringView() );
					placemarker.spaceBefore = token.spaceBefore;
					_outTokens.push_back(placemarker);
				}

				ii = jj;
			}
		}

		void subst(
			  const Macro& _macro
			, const stl::vector<stl::vector<Token> >& _actuals
			, const HideNode* _hide
			, const SourceLocation& _location
			, stl::vector<Token>& _outTokens
			)
		{
			const Token* body = _macro.body;
			uint32_t     num  = _macro.bodyNum;

			stl::vector<Token> vaOptBody;

			if (_macro.isVariadic
			&&  hasVaOpt(body, num) )
			{
				stl::vector<Token> va;
				selectActual(_macro, _actuals, "__VA_ARGS__", va);

				expandVaOpt(body, num, !va.empty(), vaOptBody);

				body = vaOptBody.data();
				num  = uint32_t(vaOptBody.size() );
			}

			stl::vector<Token> result;

			for (uint32_t ii = 0; ii < num; )
			{
				const Token& token = body[ii];

				if (isPunct(token, ",")
				&&  ii + 2 < num
				&&  isPunct(body[ii+1], "##")
				&&  isParam(_macro, body[ii+2]) )
				{
					stl::vector<Token> arg;
					selectActual(_macro, _actuals, body[ii+2].lexeme, arg);

					if (!arg.empty() )
					{
						result.push_back(token);

						for (uint32_t jj = 0, numArg = uint32_t(arg.size() ); jj < numArg; ++jj)
						{
							result.push_back(arg[jj]);
						}
					}

					ii += 3;
					continue;
				}

				if (isPunct(token, "#")
				&&  ii + 1 < num
				&&  isParam(_macro, body[ii+1]) )
				{
					stl::vector<Token> arg;
					selectActual(_macro, _actuals, body[ii+1].lexeme, arg);

					result.push_back(makeToken(Kind::String, stringize(arg) ) );

					ii += 2;
					continue;
				}

				if (isPunct(token, "##")
				&&  ii + 1 < num)
				{
					const Token& rhs = body[ii+1];

					if (!isParam(_macro, rhs) )
					{
						paste(result, rhs);
					}
					else
					{
						stl::vector<Token> arg;
						selectActual(_macro, _actuals, rhs.lexeme, arg);

						if (arg.empty() )
						{
							paste(result, makeToken(Kind::Placemarker, bx::StringView() ) );
						}
						else
						{
							paste(result, arg[0]);

							for (uint32_t jj = 1, numArg = uint32_t(arg.size() ); jj < numArg; ++jj)
							{
								result.push_back(arg[jj]);
							}
						}
					}

					ii += 2;
					continue;
				}

				if (isParam(_macro, token)
				&&  ii + 1 < num
				&&  isPunct(body[ii+1], "##") )
				{
					stl::vector<Token> arg;
					selectActual(_macro, _actuals, token.lexeme, arg);

					if (arg.empty() )
					{
						result.push_back(makeToken(Kind::Placemarker, bx::StringView() ) );
					}
					else
					{
						for (uint32_t jj = 0, numArg = uint32_t(arg.size() ); jj < numArg; ++jj)
						{
							result.push_back(arg[jj]);
						}
					}

					++ii;
					continue;
				}

				if (isParam(_macro, token) )
				{
					stl::vector<Token> arg;
					selectActual(_macro, _actuals, token.lexeme, arg);

					stl::vector<Token> expanded;
					expand(arg, expanded);

					if (!expanded.empty() )
					{
						expanded[0].spaceBefore = token.spaceBefore;
					}

					for (uint32_t jj = 0, numArg = uint32_t(expanded.size() ); jj < numArg; ++jj)
					{
						result.push_back(expanded[jj]);
					}

					++ii;
					continue;
				}

				result.push_back(token);
				++ii;
			}

			for (uint32_t ii = 0, num2 = uint32_t(result.size() ); ii < num2; ++ii)
			{
				Token& token = result[ii];

				if (Kind::Placemarker == token.kind)
				{
					continue;
				}

				token.hide = hideUnion(token.hide, _hide);
				token.location = _location;
				_outTokens.push_back(token);
			}
		}

		static bool frontIsOpenParen(const Worklist& _work)
		{
			for (const Token* it = _work.begin(), *term = _work.end(); it != term; ++it)
			{
				if (Kind::Placemarker == it->kind
				||  Kind::Newline == it->kind)
				{
					continue;
				}

				return isPunct(*it, "(");
			}

			return false;
		}

		bool collectArgs(
			  Worklist& _work
			, stl::vector<stl::vector<Token> >& _outActuals
			, const HideNode*& _outCloseHide
			, uint32_t& _outSwallowedNewlines
			)
		{
			while (!_work.isEmpty()
			&&     !isPunct(_work.getFront(), "(") )
			{
				if (Kind::Newline == _work.getFront().kind)
				{
					++_outSwallowedNewlines;
				}

				_work.popFront();
			}

			if (_work.isEmpty() )
			{
				return false;
			}

			_work.popFront();

			stl::vector<Token> current;
			int32_t depth = 0;
			bool any = false;

			for (;;)
			{
				if (_work.isEmpty() )
				{
					return false;
				}

				const Token token = _work.getFront();
				_work.popFront();

				if (Kind::Newline == token.kind)
				{
					++_outSwallowedNewlines;
					continue;
				}

				if (isPunct(token, "(") )
				{
					++depth;
					current.push_back(token);
					continue;
				}

				if (isPunct(token, ")") )
				{
					if (0 == depth)
					{
						_outCloseHide = token.hide;

						if (any
						||  !current.empty() )
						{
							_outActuals.push_back(current);
						}

						return true;
					}

					--depth;
					current.push_back(token);
					continue;
				}

				if (isPunct(token, ",")
				&&  0 == depth)
				{
					_outActuals.push_back(current);
					current.clear();
					any = true;
					continue;
				}

				current.push_back(token);
			}
		}

		bool checkArity(const Macro& _macro, const stl::vector<stl::vector<Token> >& _actuals)
		{
			const uint32_t num    = uint32_t(_actuals.size() );
			const uint32_t params = uint32_t(_macro.params.size() );

			const uint32_t given = 0 == num && 1 == params ? 1 : num;

			if (given < params)
			{
				error("Too few arguments in macro invocation");
				return false;
			}

			if (!_macro.isVariadic
			&&  given > params)
			{
				error("Too many arguments in macro invocation");
				return false;
			}

			return true;
		}

		void expand(const stl::vector<Token>& _tokens, stl::vector<Token>& _outTokens)
		{
			Worklist work(_tokens);

			while (!work.isEmpty() )
			{
				const Token token = work.getFront();
				work.popFront();

				if (Kind::Identifier != token.kind)
				{
					if (Kind::Placemarker != token.kind)
					{
						_outTokens.push_back(token);
					}

					continue;
				}

				if (hideContains(token.hide, token.lexeme) )
				{
					_outTokens.push_back(token);
					continue;
				}

				if (m_inCondition
				&&  isEqual(token.lexeme, "defined") )
				{
					_outTokens.push_back(token);
					copyDefinedOperand(work, _outTokens);
					continue;
				}

				if (isEqual(token.lexeme, "__LINE__") )
				{
					char tmp[16];
					const int32_t len = bx::toString(tmp, BX_COUNTOF(tmp), token.location.line);

					Token line = makeToken(Kind::Number, m_arena.intern(bx::StringView(tmp, len) ) );
					line.spaceBefore = token.spaceBefore;

					_outTokens.push_back(line);
					continue;
				}

				if (isEqual(token.lexeme, "__FILE__") )
				{
					const bx::FilePath filePath(m_location.file);
					const bx::StringView parts[] = { "\"", pathOf(filePath), "\"" };
					const bx::StringView quoted = m_arena.concat(parts, BX_COUNTOF(parts) );

					Token file = makeToken(Kind::String, quoted);
					file.spaceBefore = token.spaceBefore;

					_outTokens.push_back(file);
					continue;
				}

				if (isEqual(token.lexeme, "__COUNTER__") )
				{
					char tmp[16];
					const int32_t len = bx::toString(tmp, BX_COUNTOF(tmp), m_counter++);

					Token count = makeToken(Kind::Number, m_arena.intern(bx::StringView(tmp, len) ) );
					count.spaceBefore = token.spaceBefore;

					_outTokens.push_back(count);
					continue;
				}

				const Macro* macro = findMacro(token.lexeme);

				if (NULL == macro)
				{
					_outTokens.push_back(token);
					continue;
				}

				if (!macro->isFunction)
				{
					const HideNode* hide = hideAdd(token.hide, token.lexeme);

					const stl::vector<stl::vector<Token> > noActuals;
					stl::vector<Token> replacement;
					subst(*macro, noActuals, hide, token.location, replacement);

					if (!replacement.empty() )
					{
						replacement[0].spaceBefore = token.spaceBefore;
					}

					work.prepend(replacement);
					continue;
				}

				if (!frontIsOpenParen(work) )
				{
					_outTokens.push_back(token);
					continue;
				}

				stl::vector<stl::vector<Token> > actuals;
				const HideNode* closeHide = NULL;
				uint32_t swallowedNewlines = 0;

				if (!collectArgs(work, actuals, closeHide, swallowedNewlines) )
				{
					error("Unterminated macro invocation");
					_outTokens.push_back(token);
					continue;
				}

				if (!checkArity(*macro, actuals) )
				{
					_outTokens.push_back(token);
					continue;
				}

				const HideNode* hide = hideAdd(hideIntersect(token.hide, closeHide), token.lexeme);

				stl::vector<Token> replacement;
				subst(*macro, actuals, hide, token.location, replacement);

				if (!replacement.empty() )
				{
					replacement[0].spaceBefore = token.spaceBefore;
				}

				for (uint32_t ii = 0; ii < swallowedNewlines; ++ii)
				{
					replacement.push_back(makeToken(Kind::Newline, "\n") );
				}

				work.prepend(replacement);
			}
		}

		static bool needSpace(const Token& _lhs, const Token& _rhs)
		{
			if (_lhs.lexeme.isEmpty()
			||  _rhs.lexeme.isEmpty() )
			{
				return false;
			}

			return bx::isIdentChar(_lhs.lexeme.getTerm()[-1])
				&& bx::isIdentChar(*_rhs.lexeme.getPtr() )
				;
		}

		void append(const bx::StringView& _str)
		{
			bx::write(m_out, _str.getPtr(), _str.getLength(), &m_err);
		}

		void append(char _ch)
		{
			bx::write(m_out, _ch, &m_err);
		}

		void emit(const stl::vector<Token>& _tokens, bool _atLineStart = true)
		{
			bool atLineStart = _atLineStart;
			const Token* prev = NULL;

			for (uint32_t ii = 0, num = uint32_t(_tokens.size() ); ii < num; ++ii)
			{
				const Token& token = _tokens[ii];

				if (Kind::Placemarker == token.kind)
				{
					continue;
				}

				if (Kind::Newline == token.kind)
				{
					append('\n');
					++m_outLocation.line;
					atLineStart = true;
					prev        = NULL;
					continue;
				}

				if (atLineStart)
				{
					syncLine(token.location);
				}
				else if (NULL != prev
				&&  (token.spaceBefore || needSpace(*prev, token) ) )
				{
					append(' ');
				}

				append(token.lexeme);

				atLineStart = false;
				prev        = &token;
			}
		}

		class Eval
		{
			BX_CLASS(Eval
				, NO_DEFAULT_CTOR
				, NO_COPY
				);

		public:
			struct Value
			{
				int64_t value;
				bool    isUnsigned;
			};

			Eval(PreprocessorImpl& _impl, const stl::vector<Token>& _tokens)
				: m_impl(_impl)
				, m_tokens(_tokens)
				, m_pos(0)
				, m_evaluated(true)
			{
			}

			Value parseTernary()
			{
				const Value cond = parseBinary(1);

				if (!peekPunct("?") )
				{
					return cond;
				}

				advance();

				const bool taken = 0 != cond.value;

				const Value lhs = parseUnevaluatedUnless(taken);

				if (peekPunct(":") )
				{
					advance();
				}
				else
				{
					m_impl.error("Missing ':' in #if expression");
				}

				const Value rhs = parseUnevaluatedUnless(!taken);

				Value result = taken ? lhs : rhs;
				result.isUnsigned = lhs.isUnsigned || rhs.isUnsigned;

				return result;
			}

		private:
			Value parseUnevaluatedUnless(bool _evaluated)
			{
				const bool old = m_evaluated;
				m_evaluated = m_evaluated && _evaluated;

				const Value value = parseTernary();

				m_evaluated = old;

				return value;
			}

			static Value makeValue(int64_t _value, bool _isUnsigned)
			{
				Value value;
				value.value      = _value;
				value.isUnsigned = _isUnsigned;

				return value;
			}

			const Token* peek() const
			{
				return m_pos < m_tokens.size() ? &m_tokens[m_pos] : NULL;
			}

			bool peekPunct(const bx::StringView& _lexeme) const
			{
				const Token* token = peek();

				return NULL != token
					&& isPunct(*token, _lexeme)
					;
			}

			void advance()
			{
				++m_pos;
			}

			Value parsePrimary()
			{
				const Token* token = peek();

				if (NULL == token)
				{
					m_impl.error("Unexpected end of #if expression");
					return makeValue(0, false);
				}

				if (peekPunct("(") )
				{
					advance();
					const Value value = parseTernary();

					if (peekPunct(")") )
					{
						advance();
					}
					else
					{
						m_impl.error("Missing ')' in #if expression");
					}

					return value;
				}

				if (peekPunct("!") )
				{
					advance();
					return makeValue(0 != parseUnary().value ? 0 : 1, false);
				}

				if (peekPunct("~") )
				{
					advance();
					const Value value = parseUnary();

					return makeValue(~value.value, value.isUnsigned);
				}

				if (peekPunct("-") )
				{
					advance();
					const Value value = parseUnary();

					return makeValue(int64_t(0ull - uint64_t(value.value) ), value.isUnsigned);
				}

				if (peekPunct("+") )
				{
					advance();
					return parseUnary();
				}

				if (Kind::Number == token->kind)
				{
					advance();
					return parseIntLiteral(token->lexeme);
				}

				if (Kind::Char == token->kind)
				{
					advance();
					return makeValue(parseCharLiteral(token->lexeme), false);
				}

				advance();

				return makeValue(0, false);
			}

			Value parseUnary()
			{
				return parsePrimary();
			}

			Value parseBinary(int32_t _minPrec)
			{
				Value lhs = parseUnary();

				for (;;)
				{
					const Token* token = peek();

					if (NULL == token
					||  Kind::Punct != token->kind)
					{
						break;
					}

					const Op op = findOp(token->lexeme);

					if (Op::Count == op
					||  getOpInfo(op).precedence < _minPrec)
					{
						break;
					}

					advance();

					const bool shortCircuit = false
						|| (Op::LogicalAnd == op && 0 == lhs.value)
						|| (Op::LogicalOr  == op && 0 != lhs.value)
						;

					const bool old = m_evaluated;
					m_evaluated = m_evaluated && !shortCircuit;

					const Value rhs = parseBinary(getOpInfo(op).precedence + 1);

					m_evaluated = old;

					lhs = apply(op, lhs, rhs);
				}

				return lhs;
			}

			Value apply(Op _op, const Value& _lhs, const Value& _rhs)
			{
				const int32_t shift = int32_t(_rhs.value & 63);

				switch (_op)
				{
				case Op::Shl:
					return _lhs.isUnsigned
						? makeValue(int64_t(uint64_t(_lhs.value) << shift), true)
						: makeValue(_lhs.value << shift, false)
						;

				case Op::Shr:
					return _lhs.isUnsigned
						? makeValue(int64_t(uint64_t(_lhs.value) >> shift), true)
						: makeValue(_lhs.value >> shift, false)
						;

				case Op::LogicalAnd:
					return makeValue(0 != _lhs.value && 0 != _rhs.value ? 1 : 0, false);

				case Op::LogicalOr:
					return makeValue(0 != _lhs.value || 0 != _rhs.value ? 1 : 0, false);

				default:
					break;
				}

				if (_lhs.isUnsigned
				||  _rhs.isUnsigned)
				{
					return applyTyped<uint64_t>(
						  _op
						, uint64_t(_lhs.value)
						, uint64_t(_rhs.value)
						, true
						);
				}

				return applyTyped<int64_t>(_op, _lhs.value, _rhs.value, false);
			}

			template<typename Ty>
			Value applyTyped(Op _op, Ty _lhs, Ty _rhs, bool _isUnsigned)
			{
				switch (_op)
				{
				case Op::Mul:
					return makeValue(int64_t(Ty(_lhs * _rhs) ), _isUnsigned);

				case Op::Div:
					return makeValue(int64_t(Ty(0 != _rhs ? _lhs / _rhs : checkedZero() ) ), _isUnsigned);

				case Op::Mod:
					return makeValue(int64_t(Ty(0 != _rhs ? _lhs % _rhs : checkedZero() ) ), _isUnsigned);

				case Op::Add:
					return makeValue(int64_t(Ty(_lhs + _rhs) ), _isUnsigned);

				case Op::Sub:
					return makeValue(int64_t(Ty(_lhs - _rhs) ), _isUnsigned);

				case Op::BitAnd:
					return makeValue(int64_t(Ty(_lhs & _rhs) ), _isUnsigned);

				case Op::BitXor:
					return makeValue(int64_t(Ty(_lhs ^ _rhs) ), _isUnsigned);

				case Op::BitOr:
					return makeValue(int64_t(Ty(_lhs | _rhs) ), _isUnsigned);

				case Op::Lt:
					return makeValue(_lhs < _rhs ? 1 : 0, false);

				case Op::Gt:
					return makeValue(_lhs > _rhs ? 1 : 0, false);

				case Op::LtEq:
					return makeValue(_lhs <= _rhs ? 1 : 0, false);

				case Op::GtEq:
					return makeValue(_lhs >= _rhs ? 1 : 0, false);

				case Op::Eq:
					return makeValue(_lhs == _rhs ? 1 : 0, false);

				case Op::NotEq:
					return makeValue(_lhs != _rhs ? 1 : 0, false);

				default:
					BX_ASSERT(false, "Bug, _op can't be %d!", uint8_t(_op) );
					return makeValue(0, false);
				}
			}

			static Value parseIntLiteral(const bx::StringView& _text)
			{
				bx::Scanner scanner(_text);

				int32_t base = 10;

				if (!scanner.accept(bx::StringView("0x") ).isEmpty()
				||  !scanner.accept(bx::StringView("0X") ).isEmpty() )
				{
					base = 16;
				}
				else if (1 < _text.getLength()
				     &&  !scanner.accept('0').isEmpty() )
				{
					base = 8;
				}

				uint64_t value = 0;

				for (;;)
				{
					const bx::StringView next = scanner.peek();

					if (next.isEmpty() )
					{
						break;
					}

					const int32_t digit = toDigit(*next.getPtr() );

					if (0 > digit
					||  digit >= base)
					{
						break;
					}

					scanner.accept();
					value = value * base + digit;
				}

				const bx::StringView suffix = scanner.acceptAll();

				const bool isUnsigned = false
					|| !strFind(suffix, 'u').isEmpty()
					|| !strFind(suffix, 'U').isEmpty()
					;

				return makeValue(int64_t(value), isUnsigned);
			}

			static int64_t parseCharLiteral(const bx::StringView& _text)
			{
				bx::Scanner scanner(_text);

				scanner.accept('\'');

				if (scanner.accept('\\').isEmpty() )
				{
					const bx::StringView ch = scanner.accept();

					return ch.isEmpty() ? 0 : uint8_t(*ch.getPtr() );
				}

				const bx::StringView escape = scanner.accept();

				if (escape.isEmpty() )
				{
					return 0;
				}

				const char ch = *escape.getPtr();

				switch (ch)
				{
				case 'a':  return '\a';
				case 'b':  return '\b';
				case 'f':  return '\f';
				case 'n':  return '\n';
				case 'r':  return '\r';
				case 't':  return '\t';
				case 'v':  return '\v';
				case '\\': return '\\';
				case '\'': return '\'';
				case '"':  return '"';
				case '?':  return '?';

				default:
					break;
				}

				if ('x' == ch
				||  'X' == ch)
				{
					const bx::StringView digits = scanner.acceptWhile(bx::isHexNum);

					int64_t value = 0;

					for (const char* ptr = digits.getPtr(); ptr != digits.getTerm(); ++ptr)
					{
						value = value * 16 + toDigit(*ptr);
					}

					return value;
				}

				if (bx::isOctNum(ch) )
				{
					int64_t value = ch - '0';

					for (uint32_t ii = 0; ii < 2; ++ii)
					{
						const bx::StringView digit = scanner.accept(bx::isOctNum);

						if (digit.isEmpty() )
						{
							break;
						}

						value = value * 8 + (*digit.getPtr() - '0');
					}

					return value;
				}

				return uint8_t(ch);
			}

			int32_t checkedZero()
			{
				if (m_evaluated)
				{
					m_impl.error("Division by zero in #if expression");
				}

				return 0;
			}

			PreprocessorImpl&         m_impl;
			const stl::vector<Token>& m_tokens;
			uint32_t                  m_pos;
			bool                      m_evaluated;
		};

		void reduceDefined(const stl::vector<Token>& _tokens, stl::vector<Token>& _outTokens)
		{
			for (uint32_t ii = 0, num = uint32_t(_tokens.size() ); ii < num; )
			{
				const Token& token = _tokens[ii];

				if (!isIdent(token, "defined") )
				{
					_outTokens.push_back(token);
					++ii;
					continue;
				}

				uint32_t jj = ii + 1;
				bool paren = false;

				if (jj < num
				&&  isPunct(_tokens[jj], "(") )
				{
					paren = true;
					++jj;
				}

				bx::StringView name;

				if (jj < num
				&&  Kind::Identifier == _tokens[jj].kind)
				{
					name = _tokens[jj].lexeme;
					++jj;
				}
				else
				{
					error("Operator 'defined' requires an identifier");
				}

				if (paren)
				{
					if (jj < num
					&&  isPunct(_tokens[jj], ")") )
					{
						++jj;
					}
					else
					{
						error("Missing ')' after 'defined'");
					}
				}

				Token result = makeToken(Kind::Number, isDefined(name) ? "1" : "0");
				result.spaceBefore = token.spaceBefore;

				_outTokens.push_back(result);
				ii = jj;
			}
		}

		void copyDefinedOperand(Worklist& _work, stl::vector<Token>& _outTokens)
		{
			if (_work.isEmpty() )
			{
				return;
			}

			Token token = _work.getFront();

			if (isPunct(token, "(") )
			{
				_work.popFront();
				_outTokens.push_back(token);

				if (_work.isEmpty() )
				{
					return;
				}

				token = _work.getFront();
			}

			if (Kind::Identifier == token.kind)
			{
				_work.popFront();
				_outTokens.push_back(token);
			}
		}

		bool evalCondition(const stl::vector<Token>& _args)
		{
			stl::vector<Token> reduced;
			reduceDefined(_args, reduced);

			const bool oldInCondition = m_inCondition;
			m_inCondition = true;

			stl::vector<Token> expanded;
			expand(reduced, expanded);

			m_inCondition = oldInCondition;

			stl::vector<Token> settled;
			reduceDefined(expanded, settled);

			Eval eval(*this, settled);

			return 0 != eval.parseTernary().value;
		}

		void pushCond(bool _value)
		{
			const bool parent = condActive();
			const bool active = parent && _value;

			const Cond cond =
			{
				.active   = active,
				.taken    = active,
				.parent   = parent,
				.seenElse = false,
			};

			m_cond.push_back(cond);
		}

		void parseDefine(const stl::vector<Token>& _args)
		{
			if (_args.empty()
			||  Kind::Identifier != _args[0].kind)
			{
				error("Macro name missing");
				return;
			}

			Macro macro =
			{
				.name       = _args[0].lexeme,
				.params     = {},
				.body       = NULL,
				.bodyNum    = 0,
				.isFunction = false,
				.isVariadic = false,
			};

			const uint32_t num = uint32_t(_args.size() );
			uint32_t ii = 1;

			if (ii < num
			&&  isPunct(_args[ii], "(")
			&&  !_args[ii].spaceBefore)
			{
				macro.isFunction = true;
				++ii;

				bool expectParam = true;

				for (; ii < num; ++ii)
				{
					const Token& token = _args[ii];

					if (isPunct(token, ")") )
					{
						++ii;
						break;
					}

					if (isPunct(token, ",") )
					{
						expectParam = true;
						continue;
					}

					if (isPunct(token, "...") )
					{
						macro.isVariadic = true;
						expectParam = false;
						continue;
					}

					if (Kind::Identifier == token.kind
					&&  expectParam)
					{
						if (-1 != findParam(macro, token.lexeme) )
						{
							error("Duplicate macro parameter");
							return;
						}

						macro.params.push_back(token.lexeme);
						expectParam = false;
						continue;
					}

					error("Invalid macro parameter list");
					return;
				}
			}

			const uint32_t bodyNum = num - ii;

			if (0 < bodyNum)
			{
				Token* body = m_arena.allocate<Token>(bodyNum);

				for (uint32_t jj = 0; jj < bodyNum; ++jj)
				{
					body[jj] = _args[ii + jj];
				}

				body[0].spaceBefore = false;

				if (isPunct(body[0], "##")
				||  isPunct(body[bodyNum - 1], "##") )
				{
					error("'##' cannot appear at either end of a macro replacement list");
					return;
				}

				if (macro.isFunction)
				{
					for (uint32_t jj = 0; jj < bodyNum; ++jj)
					{
						if (!isPunct(body[jj], "#") )
						{
							continue;
						}

						if (jj + 1 >= bodyNum
						||  Kind::Identifier != body[jj + 1].kind
						||  (-1 == findParam(macro, body[jj + 1].lexeme)
						&&   !(macro.isVariadic && isEqual(body[jj + 1].lexeme, "__VA_ARGS__") ) ) )
						{
							error("'#' must be followed by a macro parameter");
							return;
						}
					}
				}

				for (uint32_t jj = 0; jj < bodyNum; ++jj)
				{
					if (Kind::Identifier != body[jj].kind
					||  !isEqual(body[jj].lexeme, "__VA_OPT__") )
					{
						continue;
					}

					if (!macro.isVariadic)
					{
						error("'__VA_OPT__' can only appear in a variadic macro");
						return;
					}

					if (jj + 1 >= bodyNum
					||  !isPunct(body[jj + 1], "(") )
					{
						error("'__VA_OPT__' must be followed by '('");
						return;
					}

					uint32_t depth = 1;

					for (uint32_t kk = jj + 2; kk < bodyNum && 0 != depth; ++kk)
					{
						if      (isPunct(body[kk], "(") ) { ++depth; }
						else if (isPunct(body[kk], ")") ) { --depth; }
					}

					if (0 != depth)
					{
						error("Unterminated '__VA_OPT__'");
						return;
					}
				}

				macro.body    = body;
				macro.bodyNum = bodyNum;
			}

			removeMacro(macro.name);
			m_macros.push_back(macro);
		}

		void parseUndef(const stl::vector<Token>& _args)
		{
			if (_args.empty()
			||  Kind::Identifier != _args[0].kind)
			{
				error("Macro name missing");
				return;
			}

			removeMacro(_args[0].lexeme);
		}

		void parseLine(const stl::vector<Token>& _args, const Token& _directive)
		{
			if (m_frames.empty()
			||  !isEqual(frameName(m_frames.back() ), _directive.location.file) )
			{
				return;
			}

			stl::vector<Token> expanded;
			const stl::vector<Token>* args = &_args;

			if (!_args.empty()
			&&  Kind::Number != _args[0].kind)
			{
				expand(_args, expanded);
				args = &expanded;
			}

			int32_t line;

			if (args->empty()
			||  Kind::Number != (*args)[0].kind
			||  !fromString(&line, (*args)[0].lexeme)
			||  0 > line)
			{
				error("#line expects a decimal line number");
				return;
			}

			Frame& frame = m_frames.back();

			frame.lineDelta += line - int32_t(_directive.location.line) - 1;

			if (1 < args->size() )
			{
				const Token& name = (*args)[1];

				if (Kind::String != name.kind)
				{
					error("#line expects a file name string");
					return;
				}

				frame.presumedName = m_arena.intern(
					  bx::StringView(name.lexeme.getPtr() + 1, name.lexeme.getTerm() - 1)
					);
			}
		}

		bool isPragmaOnce(const bx::StringView& _name) const
		{
			for (uint32_t ii = 0, num = uint32_t(m_pragmaOnce.size() ); ii < num; ++ii)
			{
				if (isEqual(m_pragmaOnce[ii], _name) )
				{
					return true;
				}
			}

			return false;
		}

		void markPragmaOnce()
		{
			if (m_frames.empty() )
			{
				return;
			}

			const bx::StringView& name = m_frames.back().name;

			if (!isPragmaOnce(name) )
			{
				m_pragmaOnce.push_back(m_arena.intern(name) );
			}
		}

		void doInclude(const stl::vector<Token>& _args)
		{
			if (_args.empty() )
			{
				error("Invalid #include");
				return;
			}

			bx::StringView name;
			bool isSystem = false;

			if (Kind::String == _args[0].kind)
			{
				const bx::StringView lexeme = _args[0].lexeme;

				if (2 <= lexeme.getLength() )
				{
					name.set(lexeme.getPtr() + 1, lexeme.getTerm() - 1);
				}
			}
			else if (isPunct(_args[0], "<") )
			{
				isSystem = true;

				stl::vector<Token> parts;

				for (uint32_t ii = 1, num = uint32_t(_args.size() ); ii < num; ++ii)
				{
					if (isPunct(_args[ii], ">") )
					{
						break;
					}

					parts.push_back(_args[ii]);
				}

				name = rebuild(parts);
			}
			else
			{
				stl::vector<Token> expanded;
				expand(_args, expanded);

				if (!expanded.empty()
				&&  (Kind::String == expanded[0].kind || isPunct(expanded[0], "<") ) )
				{
					doInclude(expanded);
				}
				else
				{
					error("Invalid #include");
				}

				return;
			}

			if (kMaxIncludeDepth < m_includeDepth)
			{
				error("#include nested too deeply");
				return;
			}

			bx::MemoryBlock mb(m_arena.getAllocator() );
			bx::MemoryWriter writer(&mb);
			bx::FilePath resolved;
			bx::Error err;

			if (!m_callback.include(name, isSystem, m_location.file, &writer, resolved, &err)
			||  !err.isOk() )
			{
				char tmp[1024];
				bx::snprintf(tmp, BX_COUNTOF(tmp), "Could not open include file '%.*s'"
					, name.getLength()
					, name.getPtr()
					);
				error(tmp);

				return;
			}

			const bx::StringView path = isEqual(resolved, ".") ? bx::StringView() : bx::StringView(resolved);
			m_callback.depend(path);

			const uint32_t size = uint32_t(bx::seek(&writer) );
			const bx::StringView arenaName = m_arena.intern(path.isEmpty() ? name : path);

			if (isPragmaOnce(arenaName) )
			{
				return;
			}

			const bx::StringView arenaSource = m_arena.intern(
				0 == size ? bx::StringView() : bx::StringView( (const char*)mb.more(0), int32_t(size) )
				);

			++m_includeDepth;
			pushFrame(arenaName, arenaSource, true);
		}

		void handleDirective(const stl::vector<Token>& _line)
		{
			if (_line.empty()
			||  Kind::Identifier != _line[0].kind)
			{
				return;
			}

			const bx::StringView directive = _line[0].lexeme;

			stl::vector<Token> args;
			args.assign(_line.data() + 1, _line.data() + _line.size() );

			if (isEqual(directive, "if") )
			{
				pushCond(condActive() && evalCondition(args) );
				return;
			}

			if (isEqual(directive, "ifdef")
			||  isEqual(directive, "ifndef") )
			{
				bool value = !args.empty()
					&& Kind::Identifier == args[0].kind
					&& isDefined(args[0].lexeme)
					;

				if (isEqual(directive, "ifndef") )
				{
					value = !value;
				}

				pushCond(value);
				return;
			}

			if (isEqual(directive, "elif")
			||  isEqual(directive, "elifdef")
			||  isEqual(directive, "elifndef") )
			{
				if (m_cond.empty() )
				{
					error("#elif without #if");
					return;
				}

				Cond& cond = m_cond.back();

				if (cond.seenElse)
				{
					error("#elif after #else");
					return;
				}

				if (cond.taken
				||  !cond.parent)
				{
					cond.active = false;
				}
				else
				{
					if (isEqual(directive, "elif") )
					{
						cond.active = evalCondition(args);
					}
					else
					{
						const bool defined = true
							&& !args.empty()
							&& Kind::Identifier == args[0].kind
							&& isDefined(args[0].lexeme)
							;
						cond.active = isEqual(directive, "elifdef") ? defined : !defined;
					}

					cond.taken = cond.active;
				}

				return;
			}

			if (isEqual(directive, "else") )
			{
				if (m_cond.empty() )
				{
					error("#else without #if");
					return;
				}

				Cond& cond = m_cond.back();

				if (cond.seenElse)
				{
					error("Multiple #else");
					return;
				}

				cond.seenElse = true;
				cond.active   = cond.parent && !cond.taken;
				cond.taken    = cond.taken || cond.active;

				return;
			}

			if (isEqual(directive, "endif") )
			{
				if (m_cond.empty() )
				{
					error("#endif without #if");
					return;
				}

				m_cond.pop_back();
				return;
			}

			if (!condActive() )
			{
				return;
			}

			if (isEqual(directive, "define") )
			{
				parseDefine(args);
			}
			else if (isEqual(directive, "undef") )
			{
				parseUndef(args);
			}
			else if (isEqual(directive, "include") )
			{
				doInclude(args);
			}
			else if (isEqual(directive, "error") )
			{
				report(true, rebuild(args) );
			}
			else if (isEqual(directive, "warning") )
			{
				report(false, rebuild(args) );
			}
			else if (isEqual(directive, "pragma") )
			{
				if (!args.empty()
				&&  isIdent(args[0], "once") )
				{
					markPragmaOnce();
					return;
				}

				syncLine(_line[0].location);

				append("#pragma");

				if (!args.empty() )
				{
					append(' ');
				}

				emit(args, false);

				append('\n');
				++m_outLocation.line;
			}
			else if (isEqual(directive, "line") )
			{
				parseLine(args, _line[0]);
			}
			else
			{
				char tmp[256];
				bx::snprintf(tmp, BX_COUNTOF(tmp), "Unknown directive '#%.*s'"
					, directive.getLength()
					, directive.getPtr()
					);
				report(false, tmp);
			}
		}

		bool run(const bx::StringView& _name, const bx::StringView& _source, bx::WriterI* _writer, bx::Error* _err)
		{
			BX_ASSERT(bx::isSorted(s_ops, BX_COUNTOF(s_ops), OpInfo::cmpFn), "s_ops must be sorted!");

			m_out = _writer;
			m_err.reset();
			m_ok = true;
			m_includeDepth     = 0;
			m_outLocation.line = 1;
			m_inCondition = false;
			m_counter     = 0;
			m_outLocation.file.clear();
			m_pragmaOnce.clear();

			pushFrame(m_arena.intern(_name), m_arena.intern(_source), false);

			Token token;

			while (next(token) )
			{
				if (Kind::Newline == token.kind)
				{
					if (condActive() )
					{
						append('\n');
						++m_outLocation.line;
					}

					continue;
				}

				if (isPunct(token, "#") )
				{
					stl::vector<Token> directive;
					readLine(directive);
					handleDirective(directive);

					continue;
				}

				if (!condActive() )
				{
					skipLine();
					continue;
				}

				stl::vector<Token> text;
				text.push_back(token);

				bool more = readLineKeepNewline(text);

				while (more)
				{
					Token lineStart;

					if (!next(lineStart) )
					{
						break;
					}

					if (Kind::Newline == lineStart.kind)
					{
						text.push_back(lineStart);
						continue;
					}

					if (isPunct(lineStart, "#") )
					{
						unget(lineStart);
						break;
					}

					text.push_back(lineStart);
					more = readLineKeepNewline(text);
				}

				stl::vector<Token> expanded;
				expand(text, expanded);
				emit(expanded);
			}

			if (!m_cond.empty() )
			{
				error("Unterminated #if");
			}

			m_frames.clear();
			m_arena.reset();
			m_out = NULL;

			if (!m_err.isOk() )
			{
				m_ok = false;

				if (NULL != _err)
				{
					_err->setError(m_err.get(), m_err.getMessage() );
				}
			}

			return m_ok;
		}

		void runDefine(const bx::StringView& _source)
		{
			pushFrame("<define>", _source, false);

			Token token;

			while (next(token) )
			{
				if (isPunct(token, "#") )
				{
					stl::vector<Token> directive;
					readLine(directive);
					handleDirective(directive);
				}
			}

			m_frames.clear();
		}

		PreprocessorCallbackI&      m_callback;
		Arena                       m_arena;
		stl::vector<Macro>          m_macros;
		stl::vector<Frame>          m_frames;
		stl::vector<Cond>           m_cond;
		stl::vector<Token>          m_pending;
		stl::vector<bx::StringView> m_pragmaOnce;
		bx::WriterI*                m_out;
		bx::Error                   m_err;
		SourceLocation              m_location;
		uint32_t                    m_includeDepth;

		SourceLocation              m_outLocation;
		bool                        m_emitLine;

		uint32_t                    m_counter;

		bool                        m_inCondition;
		bool                        m_ok;
	};

	Preprocessor::Preprocessor(PreprocessorCallbackI& _callback, bx::AllocatorI* _allocator)
		: m_impl(new PreprocessorImpl(_callback, _allocator) )
	{
	}

	Preprocessor::~Preprocessor()
	{
		delete m_impl;
	}

	void Preprocessor::define(const bx::StringView& _define)
	{
		bx::Scanner scanner(_define);

		bx::StringView name = scanner.acceptUntil("=");
		bx::StringView value("1");

		if (!scanner.accept('=').isEmpty() )
		{
			value = scanner.acceptAll();
		}
		else
		{
			name = scanner.acceptAll();
		}

		const bx::StringView parts[] = { "#define ", name, " ", value, "\n" };

		m_impl->runDefine(m_impl->m_arena.concat(parts, BX_COUNTOF(parts) ) );
	}

	void Preprocessor::undefine(const bx::StringView& _name)
	{
		m_impl->removeMacro(_name);
	}

	void Preprocessor::setEmitLineDirectives(bool _emit)
	{
		m_impl->m_emitLine = _emit;
	}

	bool Preprocessor::preprocess(
		  const bx::StringView& _name
		, const bx::StringView& _source
		, bx::WriterI* _writer
		, bx::Error* _err
		)
	{
		return m_impl->run(_name, _source, _writer, _err);
	}
}
