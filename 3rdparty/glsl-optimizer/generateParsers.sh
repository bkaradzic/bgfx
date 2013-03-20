#! /bin/sh
flex --nounistd -osrc/glsl/glcpp/glcpp-lex.c src/glsl/glcpp/glcpp-lex.l
flex --nounistd -osrc/glsl/glsl_lexer.cpp src/glsl/glsl_lexer.ll
bison -v -o "src/glsl/glcpp/glcpp-parse.c" -p "glcpp_parser_" --defines=src/glsl/glcpp/glcpp-parse.h src/glsl/glcpp/glcpp-parse.y
bison -v -o "src/glsl/glsl_parser.cpp" -p "_mesa_glsl_" --defines=src/glsl/glsl_parser.h src/glsl/glsl_parser.yy
