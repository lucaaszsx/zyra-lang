#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "zlex.h"

Token *zlex_read_identifier(ZLex *zl);

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

void zlex_skip_whitespace(ZLex *zl) {
    while (zlex_is_whitespace(zlex_peek(zl))) {
        zlex_advance(zl);
    }
}

Token *next_token(ZLex *zl) {
    
}

Token *zl(ZLex *zl) {

}

Token *zlex_read(ZLex *zl) {
        
}

bool zlex_is_letter(char c) {
    return (c != '\0') && (isalpha((unsigned char) c) || c == '_');
}

bool zlex_is_digit(char c) {
    return (c != '\0') && isdigit((unsigned char) c);
}

bool zlex_is_alphanum(char c) {
    return zlex_is_letter(c) || zlex_is_digit(c);
}

bool zlex_is_whitespace(char c) {
    return c == ' ' ||
           c == '\n' ||
           c == '\t' ||
           c == '\r';
}

Token *zlex_read_identifier(ZLex *zl) {
    
}