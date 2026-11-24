#include "mittel.h"
#include <stdlib.h>

struct lines_t lines;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "No source file given\n");
    fprintf(stderr, "Try again like lacc <path_to_file.lac>\n");
    return EXIT_FAILURE;
  }

  int file_size = open_file(argv[1]);

  if (file_size == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  char *content_buffer = malloc((size_t)file_size + 1);

  if (content_buffer == NULL) {
    fprintf(stderr, "Failed to allocate buffer to read contents of the file\n");
    return EXIT_FAILURE;
  }

  if (read_file_to_buffer(content_buffer) == EXIT_FAILURE) {
    fprintf(stderr, "Reading the file in to a buffer failed!\n");
    free(content_buffer);
    return EXIT_FAILURE;
  }

  if (run_lexer(content_buffer, file_size) == EXIT_FAILURE) {
    fprintf(stderr, "Lexing the buffer failed!\n");
    free(content_buffer);
    return EXIT_FAILURE;
  }

  free(content_buffer);
  return EXIT_SUCCESS;
}
