#ifndef ZLEX_H
#define ZLEX_H

#include <stdbool.h>

typedef enum {
    TK_IDENTIFIER
} TokenType;

typedef struct {
    TokenType type;
    char *lexeme;
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
    int src_length;

    int pos;
    char current;

    int line;
    int column;
} ZLex;

ZLex *zlex_init(const char *src);
void zlex_free(ZLex *zlex);

void zlex_skip_wspace(ZLex *zlex);
char zlex_advance(ZLex *zlex);
char zlex_peek(ZLex *zlex);
Token *zlex_lookahead(ZLex *zlex);
Token *zlex_read();

bool zlex_is_letter(char c);
bool zlex_is_digit(char c);
bool zlex_is_alphanum(char c);
bool zlex_is_wspace(char c);

#endif