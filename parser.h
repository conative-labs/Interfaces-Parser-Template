#ifndef parser_h
#define parser_h

#include <stdbool.h>
#include <stdint.h>

void vParserInit(void);
bool bParserCmd(char *cmd, char *buffer);

#endif
