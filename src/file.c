#include "mittel.h"
#include <stdio.h>
#include <stdlib.h>

static FILE *file = NULL;
static long file_size = 0;

static int validate_f_ext(const char *filename) {

  uint16_t fn_len = strlen(filename);

  for (uint16_t i = 0; i < fn_len; i++) {
    if (filename[i] == '.') {
      uint16_t fn_rlen = fn_len - (++i);

      if (fn_rlen == 0 || fn_rlen > 3)
        break;

      // who the fuck loops over 4 elements..
      char ext[4];

      ext[0] = filename[i];
      ext[1] = filename[++i];
      ext[2] = filename[++i];
      ext[3] = '\0';

      if (strcmp(ext, "mtl") == 0) {
        return EXIT_SUCCESS;
      }
    }
  }

  return EXIT_FAILURE;
}

static FILE *open_f_read_size_f(long *out_file_size, char *filename) {
  FILE *fptr = fopen(filename, "rb");
  if (fptr == NULL) {
    perror("fopen");
    return NULL;
  }

  if (fseek(fptr, 0L, SEEK_END) != 0) {
    perror("fseek");
    fclose(fptr);
    return NULL;
  }

  long res = ftell(fptr);
  if (res == -1L) {
    perror("ftell");
    fclose(fptr);
    return NULL;
  }

  *out_file_size = res;
  rewind(fptr);
  return fptr;
}

int open_file(char *filename) {
  printf(" VALIDATING FILE FORMAT\n");
  if (validate_f_ext(filename) == EXIT_FAILURE) {
    fprintf(stderr, "File given was not a type of .lac\n");
    return EXIT_FAILURE;
  }

  printf(" FILE EXTENSION VAS MTL\n");

  printf(" OPENING THE FILE\n");
  file_size = 0;
  file = open_f_read_size_f(&file_size, filename);

  if (file_size == 0) {
    fprintf(stderr, "File was empty\n");
    return EXIT_FAILURE;
  }

  return file_size;
}

int read_file_to_buffer(char *content_buffer) {
  size_t bytes_read = fread(content_buffer, 1, (size_t)file_size, file);
  if (bytes_read != (size_t)file_size) {
    fprintf(stderr, "Failed to read the entire file\n");
    free(content_buffer);
    fclose(file);
    return EXIT_FAILURE;
  }
  content_buffer[bytes_read] = '\0';

  printf(" CLOSING FILE\n");
  fclose(file);
  return EXIT_SUCCESS;
}
