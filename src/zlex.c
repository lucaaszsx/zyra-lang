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

static void zlex_skip_whitespace(ZLex *zl) {
    while (1) {
        char c = zl->current;

        if (c == ' ' || c == '\n' || c == '\t' || c == '\r') zlex_advance(zl);
        else break;
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
    zlex_skip_whitespace(zl);

    Token *token = (Token *)(malloc(sizeof(Token)));

    if (token == NULL) return NULL;

    token->line = zl->line;
    token->column = zl->column;
    
    char c = zlex_advance(zl);

    if (c == '\0') {
        token->type = TK_EOF;
        return token;
    }

    if ((c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c == '_')) {
        while (1) {
            char n = zl->current;

            if ((n >= 'a' && n <= 'z') ||
                (n >= 'A' && n <= 'Z') ||
                (n >= '0' && n <= '9') ||
                (n == '_'))
                zlex_advance(zl);
            else
                break;
        }

        token->type = TK_IDENTIFIER;
        
        return token;
    }

    return NULL;
}