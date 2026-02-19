#ifndef ZLEX_H
#define ZLEX_H

#include <stdbool.h>
#include <stddef.h>

typedef enum {
    TK_EOF = 0,
    TK_IDENTIFIER
} TokenType;

typedef struct {
    TokenType type;
    int line;
    int column;

    union {
        long long int_val;
        double float_val;
        char *string_val;
    } value;
} Token;

typedef struct {
    const char *src;
    size_t src_length;

    size_t pos;
    char current;

    int line;
    int column;
} ZLex;

ZLex *zlex_init(const char *src);
void zlex_free(ZLex *zlex);

char zlex_advance(ZLex *zl);
char zlex_peek(ZLex *zl);
Token *zlex_next_token(ZLex *zl);
Token *zlex_lookahead(ZLex *zl);
Token *zlex_read_identifier(ZLex *zl);

#endif