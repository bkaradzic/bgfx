/*
 * Copyright © 2010 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "glcpp.h"
#include "main/core.h" /* for isblank() on MSVC */

void
glcpp_error (YYLTYPE *locp, glcpp_parser_t *parser, const char *fmt, ...)
{
	va_list ap;

	parser->error = 1;
	ralloc_asprintf_rewrite_tail(&parser->info_log,
				     &parser->info_log_length,
				     "%u:%u(%u): "
				     "preprocessor error: ",
				     locp->source,
				     locp->first_line,
				     locp->first_column);
	va_start(ap, fmt);
	ralloc_vasprintf_rewrite_tail(&parser->info_log,
				      &parser->info_log_length,
				      fmt, ap);
	va_end(ap);
	ralloc_asprintf_rewrite_tail(&parser->info_log,
				     &parser->info_log_length, "\n");
}

void
glcpp_warning (YYLTYPE *locp, glcpp_parser_t *parser, const char *fmt, ...)
{
	va_list ap;

	ralloc_asprintf_rewrite_tail(&parser->info_log,
				     &parser->info_log_length,
				     "%u:%u(%u): "
				     "preprocessor warning: ",
				     locp->source,
				     locp->first_line,
				     locp->first_column);
	va_start(ap, fmt);
	ralloc_vasprintf_rewrite_tail(&parser->info_log,
				      &parser->info_log_length,
				      fmt, ap);
	va_end(ap);
	ralloc_asprintf_rewrite_tail(&parser->info_log,
				     &parser->info_log_length, "\n");
}

/* Given str, (that's expected to start with a newline terminator of some
 * sort), return a pointer to the first character in str after the newline.
 *
 * A newline terminator can be any of the following sequences:
 *
 *	"\r\n"
 *	"\n\r"
 *	"\n"
 *	"\r"
 *
 * And the longest such sequence will be skipped.
 */
static const char *
skip_newline (const char *str)
{
	const char *ret = str;

	if (ret == NULL)
		return ret;

	if (*ret == '\0')
		return ret;

	if (*ret == '\r') {
		ret++;
		if (*ret && *ret == '\n')
			ret++;
	} else if (*ret == '\n') {
		ret++;
		if (*ret && *ret == '\r')
			ret++;
	}

	return ret;
}

/* Remove any line continuation characters in the shader, (whether in
 * preprocessing directives or in GLSL code).
 */
static char *
remove_line_continuations(glcpp_parser_t *ctx, const char *shader)
{
	char *clean = ralloc_strdup(ctx, "");
	const char *backslash, *newline, *search_start;
        const char *cr, *lf;
        char newline_separator[3];
	int collapsed_newlines = 0;

	search_start = shader;

	/* Determine what flavor of newlines this shader is using. GLSL
	 * provides for 4 different possible ways to separate lines, (using
	 * one or two characters):
	 *
	 *	"\n" (line-feed, like Linux, Unix, and new Mac OS)
	 *	"\r" (carriage-return, like old Mac files)
	 *	"\r\n" (carriage-return + line-feed, like DOS files)
	 *	"\n\r" (line-feed + carriage-return, like nothing, really)
	 *
	 * This code explicitly supports a shader that uses a mixture of
	 * newline terminators and will properly handle line continuation
	 * backslashes followed by any of the above.
	 *
	 * But, since we must also insert additional newlines in the output
	 * (for any collapsed lines) we attempt to maintain consistency by
	 * examining the first encountered newline terminator, and using the
	 * same terminator for any newlines we insert.
	 */
	cr = strchr(search_start, '\r');
	lf = strchr(search_start, '\n');

	newline_separator[0] = '\n';
	newline_separator[1] = '\0';
	newline_separator[2] = '\0';

	if (cr == NULL) {
		/* Nothing to do. */
	} else if (lf == NULL) {
		newline_separator[0] = '\r';
	} else if (lf == cr + 1) {
		newline_separator[0] = '\r';
		newline_separator[1] = '\n';
	} else if (cr == lf + 1) {
		newline_separator[0] = '\n';
		newline_separator[1] = '\r';
	}

	while (true) {
		backslash = strchr(search_start, '\\');

		/* If we have previously collapsed any line-continuations,
		 * then we want to insert additional newlines at the next
		 * occurrence of a newline character to avoid changing any
		 * line numbers.
		 */
		if (collapsed_newlines) {
			cr = strchr (search_start, '\r');
			lf = strchr (search_start, '\n');
			if (cr && lf)
				newline = cr < lf ? cr : lf;
			else if (cr)
				newline = cr;
			else
				newline = lf;
			if (newline &&
			    (backslash == NULL || newline < backslash))
			{
				ralloc_strncat(&clean, shader,
					       newline - shader + 1);
				while (collapsed_newlines) {
					ralloc_strcat(&clean, newline_separator);
					collapsed_newlines--;
				}
				shader = skip_newline (newline);
				search_start = shader;
			}
		}

		search_start = backslash + 1;

		if (backslash == NULL)
			break;

		/* At each line continuation, (backslash followed by a
		 * newline), copy all preceding text to the output, then
		 * advance the shader pointer to the character after the
		 * newline.
		 */
		if (backslash[1] == '\r' || backslash[1] == '\n')
		{
			collapsed_newlines++;
			ralloc_strncat(&clean, shader, backslash - shader);
			shader = skip_newline (backslash + 1);
			search_start = shader;
		}
	}

	ralloc_strcat(&clean, shader);

	return clean;
}

int
glcpp_preprocess(void *ralloc_ctx, const char **shader, char **info_log,
	   const struct gl_extensions *extensions, struct gl_context *gl_ctx)
{
	int errors;
	glcpp_parser_t *parser = glcpp_parser_create (extensions, gl_ctx->API);

	if (! gl_ctx->Const.DisableGLSLLineContinuations)
		*shader = remove_line_continuations(parser, *shader);

	glcpp_lex_set_source_string (parser, *shader);

	glcpp_parser_parse (parser);

	if (parser->skip_stack)
		glcpp_error (&parser->skip_stack->loc, parser, "Unterminated #if\n");

	glcpp_parser_resolve_implicit_version(parser);

	ralloc_strcat(info_log, parser->info_log);

	ralloc_steal(ralloc_ctx, parser->output);
	*shader = parser->output;

	errors = parser->error;
	glcpp_parser_destroy (parser);
	return errors;
}
