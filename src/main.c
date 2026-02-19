#include <stdlib.h>
#include <stdio.h>
#include "zlex.h"

char *read_file(char *file_name) {
    FILE *src_file = fopen(file_name, "r");

    if (src_file == NULL) {
        printf("Cannot open file: %s\n", file_name);
        return NULL;
    }

    // Get file size
    fseek(src_file, 0, SEEK_END);

    long src_size = ftell(src_file);

    fseek(src_file, 0, SEEK_SET);

    // Allocate source code buffer
    char *src_buf = (char *)malloc(src_size + 1);

    if (src_buf == NULL) {
        fclose(src_file);
        free(src_buf);
        return NULL;
    }

    // Read file
    fread(src_buf, 1, src_size, src_file);
    src_buf[src_size] = '\0';

    fclose(src_file);

    return src_buf;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>", argv[0]);
        return 1;
    }
    
    char *src = read_file(argv[1]);

    if (src == NULL) {
        fprintf(stderr, "Could not read file %s", argv[1]);
        return 1;
    }

    ZLex *zlex = zlex_init(src);

    if (zlex == NULL) {
        fprintf(stderr, "Could not initialize lexer");
        free(src);
        return 1;
    }

    while (zlex->current != '\0') {
        printf("Reading char: %c\n", zlex->current);

        Token *tk = zlex_next_token(zlex);

        if (tk != NULL) printf("Type: %d | Line: %d | Column: %d | Value: %s\n", tk->type, tk->line, tk->column, "test");

        zlex_advance(zlex);
    }

    zlex_free(zlex);
    free(src);
    
    return 0;
}