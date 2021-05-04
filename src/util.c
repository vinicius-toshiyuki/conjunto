#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>

char *unscape(const char *str) {
  char *ret = (char *)calloc(strlen(str) * 2 + 1, sizeof(char));
  char *aux = ret;
  for (size_t i = 0; i < strlen(str); i++) {
    switch (str[i]) {
    case '\a':
      *aux++ = '\\';
      *aux++ = 'a';
      break;
    case '\b':
      *aux++ = '\\';
      *aux++ = 'b';
      break;
    case '\t':
      *aux++ = '\\';
      *aux++ = 't';
      break;
    case '\n':
      *aux++ = '\\';
      *aux++ = 'n';
      break;
    case '\v':
      *aux++ = '\\';
      *aux++ = 'v';
      break;
    case '\f':
      *aux++ = '\\';
      *aux++ = 'f';
      break;
    case '\r':
      *aux++ = '\\';
      *aux++ = 'r';
      break;
    case 29:
      *aux++ = '\\';
      *aux++ = 'e';
      break;
    case '\\':
      *aux++ = '\\';
      *aux++ = '\\';
      break;
    case '\'':
      *aux++ = '\\';
      *aux++ = '\'';
      break;
    case '"':
      *aux++ = '\\';
      *aux++ = '"';
      break;
    default:
      if (isprint(str[i])) {
        *aux++ = str[i];
      } else {
        *aux++ = '\\';
        *aux++ = 'x';
        sprintf(aux, "%02x", str[i]);
        aux += 2;
      }
      break;
    }
  }
  ret = (char *)realloc(ret, sizeof(char) * (strlen(ret) + 1));
  return ret;
}
