#ifndef parser_config
#define parser_config

#include <stdint.h>
#include "parser_defs.h"

/*REQUIRED DEFINITIONS*/
#define PARSER_TYPE PARSER_TYPE_SENSOR
#define configVERSION "0.1"
#define configMAGIC_NUMBER_DEFAULT 0x65
#define configNAME_LEN 5
#define configDEP_STRING PARSER_CODE_TEMP
#define configDEP_UNIT_STRING PARSER_UNIT_TEMP
#define configPARAM_STRING PARSER_CODE_DO
#define configPARAM_UNIT_STRING PARSER_UNIT_DO
#define configPARAM_NAME_STRING PARSER_NAME_DO
/*REQUIRED DEFINITIONS END*/

/*INTERNAL DATA STRUCTURE*/
struct xparams {
	uint8_t ucMagicNumber;
	uint8_t ucI2cAddress;
	char cName[configNAME_LEN];
	/*EXTEND ME*/
};

struct xparams xParams;
/*INTERNAL DATA STRUCTURE END*/

/*REQUIRED MACROS*/
void configREAD_PARAMS(void);
void configUPDATE_PARAMS(void);
void configPARAMS_SET_DEFAULT_EXTRA(void);
void configINIT_EXTRA(void);
void configEXECUTE_READ(void);
#define configEXECUTE_READ_PRINTF_STRING "23.5"
void configCONTROL_CHECK(const char *values);
void configCONTROL_SET_LOW(const char *value);
void configCONTROL_SET_HIGH(const char *value);
void configCONTROL_GET_LOW(char *buffer);
void configCONTROL_GET_HIGH(char *buffer);
/*REQUIRED MACROS END*/

/*OPTIONAL MACROS*/
void configEXTRA_COMMANDS(char *cmd, char *buffer);
/*OPTIONAL MACROS END*/

#endif
