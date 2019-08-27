#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "parser_defs.h"
#include "parser_config.h"

#ifndef configEXTRA_COMMANDS
#define configEXTRA_COMMANDS(cmd,buffer) return 0
#endif

#define PRETEXTIFY(A) #A
#define TEXTIFY(a) PRETEXTIFY(a)

static void prvParamsSetDefault(void) {
	xParams.ucMagicNumber = configMAGIC_NUMBER_DEFAULT;
	xParams.ucI2cAddress = configMAGIC_NUMBER_DEFAULT << 1;
	configPARAMS_SET_DEFAULT_EXTRA();
}

void vParserInit(void) {
	configREAD_PARAMS();
	if(xParams.ucMagicNumber != configMAGIC_NUMBER_DEFAULT)
		prvParamsSetDefault();
	configINIT_EXTRA();
}

bool bParserCmd(char *cmd, char *buffer) {
	if('r' == cmd[0] && 0 == cmd[1]) {
		configEXECUTE_READ();
		sprintf(buffer, configEXECUTE_READ_PRINTF_STRING);
	} else if('i' == cmd[0] && 0 == cmd[1]) {
		sprintf(buffer, PARSER_TYPE","configVERSION);
	} else if(!strncmp("param", cmd, 5)) {
		if(cmd[5] == 0) {
			sprintf(buffer, configPARAM_STRING);
		} else if(!strncmp(",unit", cmd + 5, 6)) {
			sprintf(buffer, configPARAM_UNIT_STRING);
		}
	} else if(!strncmp("dep", cmd, 3)) {
		if(cmd[3] == 0) {
			sprintf(buffer, configDEP_STRING);
		} else if(!strncmp(",unit", cmd + 3, 6)) {
			sprintf(buffer, configDEP_UNIT_STRING);
		}
	} else if(!strncmp("name,", cmd, 5)) {
		if('?' == cmd[5]) {
			sprintf(buffer, "%s", xParams.cName);
		} else {
			sscanf(cmd + 5, "%"TEXTIFY(configNAME_LEN)"s", &xParams.cName);
			configUPDATE_PARAMS();
		}
	} else if(!strncmp("factory", cmd, 8)) {
		prvParamsSetDefault();
		configUPDATE_PARAMS();
	} else
		configEXTRA_COMMANDS(cmd,buffer);
	return 1;
}
