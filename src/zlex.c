#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "zlex.h"

static bool is_letter(char c) {
    return (c != '\0') && isalpha((unsigned char) c);
}

static bool is_digit(char c) {
    return (c != '\0') && isdigit((unsigned char) c);
}

static bool is_alphanum(char c) {
    return is_letter(c) || is_digit(c);
}

static void skip_whitespace(ZLex *zl) {
    while (1) {
        char c = zl->current;

        if (
            c != ' ' &&
            c != '\n' &&
            c != '\t' &&
            c != '\t'
        ) break;
    }
}

ZLex *zlex_init(const char *src) {
    if (src == NULL) return NULL;

    ZLex *zl = (ZLex *)malloc(sizeof(ZLex));

    if (zl == NULL) return NULL;

    zl->src = src;
    zl->src_length = strlen(src);
    zl->pos = 0;
    zl->current = (zl->src_length > 0) ? zl->src[0] : '\0';
    zl->line = 1;
    zl->column = 1;

    return zl;
}

void zlex_free(ZLex *zl) {
    if (zl == NULL) return;

    free(zl);
}

char zlex_advance(ZLex *zl) {
    if (zl->pos >= zl->src_length) {
        zl->current = '\0';
        return '\0';
    }

    char c = zl->src[zl->pos++];

    if (c == '\n') {
        zl->line++;
        zl->column = 0;
    } else zl->column++;

    zl->current = zl->src[zl->pos];

    return c;
}

char zlex_peek(ZLex *zl) {
    return (zl->pos < zl->src_length)
        ? zl->src[zl->pos]
        : '\0';
}

Token *zlex_next_token(ZLex *zl) {
    skip_whitespace(zl);

    char c = zl->current;

    if (is_letter(c) || c == '_') return zlex_read_identifier(zl);

    return NULL;
}

Token *zlex_read_identifier(ZLex *zl) {
    Token *token = (Token *)malloc(sizeof(Token));

    token->type = TK_IDENTIFIER;
    token->line = zl->line;
    token->column = zl->column;

    while (is_alphanum(zlex_peek(zl))) zlex_advance(zl);

    return token;
}