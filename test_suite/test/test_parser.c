#include "unity.h"
#include "parser.h"

#include "mock_parser_config_test.h"

void setUP(void)
{
  
  configPARAMS_SET_DEFAULT_EXTRA(); // set cNmae
}

void tearDown(void)
{
}

char buf[100];

void test_vParserInit_ValidMagicNumber(void)
{
  configREAD_PARAMS_Expect();
  configPARAMS_SET_DEFAULT_EXTRA_Expect();
  configINIT_EXTRA_Expect();
  
  xParams.ucMagicNumber = 20;
  xParams.ucI2cAddress = 20 << 1;

  vParserInit();

  TEST_ASSERT_EQUAL(configMAGIC_NUMBER_DEFAULT, xParams.ucMagicNumber);
  TEST_ASSERT_EQUAL(configMAGIC_NUMBER_DEFAULT << 1, xParams.ucI2cAddress);
}


void test_vParserInit_NotValidMagicNumber(void)
{
  configREAD_PARAMS_Expect();
  configINIT_EXTRA_Expect();
  
  xParams.ucMagicNumber = configMAGIC_NUMBER_DEFAULT;
  xParams.ucI2cAddress = 20;

  vParserInit();

  TEST_ASSERT_EQUAL(configMAGIC_NUMBER_DEFAULT, xParams.ucMagicNumber);
  TEST_ASSERT_EQUAL(20, xParams.ucI2cAddress);
}


void test_bParserCmd_ReadCmd(void)
{
  bool ret;
  configEXECUTE_READ_Expect();
  configCONTROL_CHECK_Expect(buf);
  
  ret = bParserCmd("r", buf);

  TEST_ASSERT_EQUAL(true, ret);
  TEST_ASSERT_EQUAL_STRING(configEXECUTE_READ_PRINTF_STRING, buf);
}

void test_bParserCmd_VersionCmd(void)
{
  bool ret;
  ret = bParserCmd("i", buf);

  TEST_ASSERT_EQUAL(true, ret);
  TEST_ASSERT_EQUAL_STRING("S,0.1", buf);
}


void test_bParserCmd_ParamCmdString(void)
{
  bool ret;
  ret = bParserCmd("param", buf);

  TEST_ASSERT_EQUAL(true, ret);
  TEST_ASSERT_EQUAL_STRING(configPARAM_STRING, buf);
}

void test_bParserCmd_ParamCmdUnitString(void)
{
  bool ret;
  ret = bParserCmd("param,unit", buf);

  TEST_ASSERT_EQUAL(true, ret);
  TEST_ASSERT_EQUAL_STRING(configPARAM_UNIT_STRING, buf);
}

void test_bParserCmd_ParamCmdNameString(void)
{
  bool ret;
  ret = bParserCmd("param,name", buf);

  TEST_ASSERT_EQUAL(true, ret);
  TEST_ASSERT_EQUAL_STRING(configPARAM_NAME_STRING, buf);
}

void test_bParserCmd_ParamCmdWrongCmd(void)
{
  bool ret;
  ret = bParserCmd("param,xxx", buf);

  TEST_ASSERT_EQUAL(false, ret);
}

void test_bParserCmd_DepCmdString(void)
{
  bool ret;
  ret = bParserCmd("dep", buf);

  TEST_ASSERT_EQUAL(true, ret);
  TEST_ASSERT_EQUAL_STRING(configDEP_STRING, buf);
}

void test_bParserCmd_DepCmdUnitString(void)
{
  bool ret;
  ret = bParserCmd("dep,unit", buf);

  TEST_ASSERT_EQUAL(true, ret);
  TEST_ASSERT_EQUAL_STRING(configDEP_UNIT_STRING, buf);
}

void test_bParserCmd_DepCmdWrongCmd(void)
{
  bool ret;
  ret = bParserCmd("dep,xxx", buf);

  TEST_ASSERT_EQUAL(false, ret);
}

void test_bParserCmd_NameCmdSetGetName(void)
{
  bool ret;

  configUPDATE_PARAMS_Expect();
  
  ret = bParserCmd("name,h", buf);
  TEST_ASSERT_EQUAL(true, ret);
    
  ret = bParserCmd("name,?", buf);

  TEST_ASSERT_EQUAL(true, ret);
  TEST_ASSERT_EQUAL_STRING("h", buf);
}

void test_bParserCmd_factory(void)
{
  bool ret;

  configPARAMS_SET_DEFAULT_EXTRA_Expect();
  configUPDATE_PARAMS_Expect();
  
  /* xParams.ucMagicNumber = 0x10; */
  /* xParams.ucI2cAddress = 0x10;  */
  ret = bParserCmd("factory", buf);
  TEST_ASSERT_EQUAL(true, ret);

  TEST_ASSERT_EQUAL(configMAGIC_NUMBER_DEFAULT, xParams.ucMagicNumber);
  TEST_ASSERT_EQUAL(configMAGIC_NUMBER_DEFAULT << 1, xParams.ucI2cAddress);
}

void test_bParserCmd_ExtraCmd(void)
{
    bool ret;
    configEXTRA_COMMANDS_Expect("cal,?", buf);
    
    ret = bParserCmd("cal,?", buf); // not a standard command
    TEST_ASSERT_EQUAL(true, ret);
    
}

void test_bParserCmd_ControlGetLowCmd(void)
{
    bool ret;

    configCONTROL_GET_LOW_Expect(buf);
    
    ret = bParserCmd("c,l,?", buf);
    TEST_ASSERT_EQUAL(true, ret);
}

void test_bParserCmd_ControlGetHighCmd(void)
{
    bool ret;

    configCONTROL_GET_HIGH_Expect(buf);
    
    ret = bParserCmd("c,h,?", buf);
    TEST_ASSERT_EQUAL(true, ret);
}

void test_bParserCmd_ControlSetLowCmd(void)
{
    bool ret;

    configCONTROL_SET_LOW_Expect("123");
    
    ret = bParserCmd("c,l,123", buf);
    TEST_ASSERT_EQUAL(true, ret);
}

void test_bParserCmd_ControlSeHighCmd(void)
{
    bool ret;

    configCONTROL_SET_HIGH_Expect("123");
    
    ret = bParserCmd("c,h,123", buf);
    TEST_ASSERT_EQUAL(true, ret);
}
