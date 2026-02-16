#include <string.h>
#include <stdlib.h>
#include "zlex.h"

ZLex *zlex_init(const char *src) {
    if (src == NULL)
        return NULL;

    ZLex *zlex = (ZLex *)malloc(sizeof(ZLex));

    if (zlex == NULL)
        return NULL;

    zlex->src = src;
    zlex->src_length = strlen(src);
    zlex->pos = 0;
    zlex->current = zlex->src[0];
    zlex->line = 1;
    zlex->column = 0;

    return zlex;
}

void zlex_free(ZLex *zlex) {
    if (zlex == NULL)
        return;

    free(zlex);
}

void zlex_skip_wspace(ZLex *zlex) {
    char c;

    #import <stdio.h>
    while (zlex_is_wspace(c = zlex_advance(zlex))) {
        printf("Skipped char: %c\n", c);
    }
}

char zlex_advance(ZLex *zlex) {
    if (zlex->pos >= zlex->src_length) return '\0';

    char c = zlex->src[zlex->pos];
    zlex->pos++;

    if (c == '\n') {
        zlex->line++;
        zlex->column = 0;
    } else zlex->column++;

    return c;
}

bool zlex_is_wspace(char c) {
    return c == ' ' ||
           c == '\n' ||
           c == '\t' ||
           c == '\r';
}