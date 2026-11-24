#ifndef MITTEL_H
#define MITTEL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS_PER_LEXEME 100
#define INITIAL_LINES_ARRAY_SIZE 500

enum token_type { // C keywords start with _
  ident,
  int_lit,
  str_lit,
  char_lit,
  float_lit,
  _int,
  _void,
  _char,
  _break,
  _continue,
  _case,
  _default,
  _if,
  _else,
  _switch,
  mov,   // =
  add,   // +
  sub,   // -
  mul,   // *
  _div,  // /
  loop,  // loop
  floop, // for loop
  wloop, // while loop
  rob,   // round open brackets
  rcb,   // round closing brackets
  cob,   // curly open brackets
  ccb,   // curly closing brackets
  ret,   // return
  semi,  //;
};

struct token {
  int tid;
  enum token_type type;
  bool is_keyword;
  bool is_string;
  int nvalue;
  char *svalue;
};

struct lexeme {
  int lid; // lexeme identifier
  int token_count;
  struct token token_table[MAX_TOKENS_PER_LEXEME];
  int line_n; // line number
};

struct lines_t {
  struct lexeme *l;
  int lexeme_count;
  int capacity;
};

extern struct lines_t lines;

int run_lexer(char *file_stream, long file_size);
int open_file(char *filename);
int read_file_to_buffer(char *content_buffer);

#endif
