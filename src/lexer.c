#include "mittel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void _create_tokken(struct token *t, char *word, int token_id) {

  if (strcmp(word, "ret") == 0) {
    t->tid = token_id;
    t->is_string = false;
    t->is_keyword = true;
    t->type = ret;
  }
}

static void analyze_line(char *line, int line_length) {

  char *word = malloc(line_length);
  int word_pos = 0;

  if (word == NULL) {
    fprintf(stderr, "Unable to allocate word buffer");
  }

  for (int i = 0; i < line_length; i++) {

    char c = line[i];
    char next_c = line[i + 1];

    printf("[LEXER][ANALYZE_LINE]: _cur_c: %c\n", c);
    printf("[LEXER][ANALYZE_LINE]: next_c: %c\n", next_c);

    if (c == '\0')
      break;

    if (c == ' ' && next_c == ' ') {
      printf("[LEXER][ANALYZE_LINE]: Skipping a double space\n");
      continue;
    }

    if (c == ';' && (next_c == '\n' || next_c == '\0')) {

      word[word_pos] = '\0';

      printf("[LEXER][ANALYZE_LINE]:Ending Token: %s\n", word);
      break;
    }

    if (c == ' ' && next_c != ';') {
      word[word_pos] = '\0';
      int lex_id = lines.lexeme_count;
      int token_id = lines.l[lex_id].token_count;
      struct token t = lines.l[lex_id].token_table[token_id];
      printf("[LEXER][ANALYZE_LINE]: Token: %s\n", word);

      _create_tokken(&t, word, token_id);
      lines.l[lex_id].token_table[token_id] = t;
      lines.l[lex_id].token_count++;

      word_pos = 0;
      word[word_pos] = '\0';
    }

    word[word_pos] = c;
    word_pos++;
  }

  free(word);
}

int run_lexer(char *file_stream, long file_size) {

  lines.l = malloc(INITIAL_LINES_ARRAY_SIZE * sizeof(struct lexeme));

  if (lines.l == NULL) {
    return EXIT_FAILURE;
  }

  int lb_pos = 0;
  int current_char = 0;
  char *line_buffer = malloc(file_size + 1);

  if (line_buffer == NULL) {
    fprintf(stderr, "Could not allocate a buffer");
    return EXIT_FAILURE;
  }

  while (1) {
    char c = file_stream[current_char];
    if (c == '\0') {
      char endl[2] = {'@', '\0'};
      analyze_line(endl, strlen(endl));
      break;
    }

    if (c == '\t') {
      current_char++;
      continue;
    }

    if (c == ';') {
      line_buffer[lb_pos] = c;
      lb_pos++;
      line_buffer[lb_pos] = '\0';
      analyze_line(line_buffer, strlen(line_buffer));
      lb_pos = 0;
    }

    line_buffer[lb_pos] = c;
    lb_pos++;
    current_char++;
  }

  free(line_buffer);
  return EXIT_SUCCESS;
}
