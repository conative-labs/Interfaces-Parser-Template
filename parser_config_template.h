#ifndef parser_config
#define parser_config

/*REQUIRED DEFINITIONS*/
#define PARSER_TYPE PARSER_TYPE_SENSOR
#define configVERSION "0.1"
#define configMAGIC_NUMBER_DEFAULT 0xFF
#define configNAME_LEN 5
#define configDEP_STRING ""
#define configDEP_UNIT_STRING ""
#define configPARAM_STRING ""
#define configPARAM_UNIT_STRING ""
#define configPARAM_NAME_STRING ""
/*REQUIRED DEFINITIONS END*/

/*INTERNAL DATA STRUCTURE*/
static struct {
	uint8_t ucMagicNumber;
	uint8_t ucI2cAddress;
	char cName[configNAME_LEN];
	/*EXTEND ME*/
} xParams;
/*INTERNAL DATA STRUCTURE END*/

/*REQUIRED MACROS*/
#define configREAD_PARAMS() do{;}while(0)
#define configUPDATE_PARAMS() do{;}while(0)
#define configPARAMS_SET_DEFAULT_EXTRA() do{;}while(0);
#define configINIT_EXTRA() do{;}while(0)
#define configEXECUTE_READ()
#define configEXECUTE_READ_PRINTF_STRING ""
/*REQUIRED MACROS END*/

/*OPTIONAL MACROS*/
#define configEXTRA_COMMANDS(cmd,buffer) {\
	return false;\
}
/*OPTIONAL MACROS END*/

#endif
