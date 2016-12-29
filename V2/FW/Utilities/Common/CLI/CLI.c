#include "CLI.h"
#include "serial.h"

//#define CLI_TEST
//#define CLI_DEBUG

void CLI_Interpreter(uint8_t *str);
void CLI_Error(uint8_t type);

uint8_t CLI_RxBuf[255];
uint8_t CLI_RxPtr=0;

CLI_Cmd_t CLI_CmdList[CLI_CMD_MAX_NUMBER];

void (*CLI_Out)(uint8_t *)=0;
uint8_t (*CLI_UserInterpreter)(uint8_t *)=0;
uint8_t CLI_Output_Enable=1;

#if defined(CLI_DEBUG)
#define CLI_Log(x) if(CLI_Output)CLI_Output(x);
#else /* CLI_DEBUG */
#define CLI_Log(x) ;
#endif /* CLI_DEBUG */

#ifdef CLI_TEST

uint8_t CLI_Test_dummyRessource=0;
void CLI_Test_FakeCallback(void)
{
  CLI_Test_dummyRessource=1;
}

uint8_t CLI_Test(void)
{
  uint8_t i=0;
  uint8_t defaultCmd[]="fakeCmd\r\n";
  CLI_Init(Serial_SendString);
  for(i=0;i<CLI_CMD_MAX_NUMBER;i++)
  {
    if(CLI_AddCmd("fakeCmd",CLI_Test_FakeCallback))
    {
      Serial_SendString("\r\nCLI Test: FAIL");
      return 1;//those calls should complete
    }
  }
  if(CLI_AddCmd("fakeCmd",CLI_Test_FakeCallback)==0)
  {
    Serial_SendString("\r\nCLI Test: FAIL");
    return 1;//should not be able to add an extra command
  }
  for(i=0;i<CLI_CMD_MAX_NUMBER;i++)
  {
    CLI_Test_dummyRessource=0;
    CLI_CmdList[i].Callback();
    if(CLI_Test_dummyRessource!=1)
    {
      Serial_SendString("\r\nCLI Test: FAIL");
      return 1;//callback has not been able to modify the value
    }
  }
  i=0;
  CLI_Test_dummyRessource=0;
  while(defaultCmd[i]!=0)
  {
    CLI_Input(defaultCmd[i++]);
  }
  if(CLI_Test_dummyRessource!=1)
  {
    Serial_SendString("\r\nCLI Test: FAIL");
    return 1;//interpreter has not been able to call the right callback
  }
  
  Serial_SendString("\r\nCLI Test: PASS");
  return 0;
}
#endif /* CLI_TEST */

void CLI_Init(void StrOut(uint8_t *),uint8_t UserInterpreter(uint8_t *) )
{
  uint8_t i;
  CLI_Out=StrOut;
  for(i=0;i<CLI_CMD_MAX_NUMBER;i++)
  {
    CLI_CmdList[i].Callback=0;
  }
  if(UserInterpreter)
    CLI_UserInterpreter=UserInterpreter;
}

uint8_t CLI_AddCmd(uint8_t *CmdName, void (*cb)(void))
{
  uint8_t ptr=0;
  while(ptr<CLI_CMD_MAX_NUMBER)
  {
    if(CLI_CmdList[ptr].Callback==0)
    {
      CLI_CmdList[ptr].Callback=cb;
      strcpy(CLI_CmdList[ptr].name,CmdName);
      return 0;
    }
    ptr++;
  }
  CLI_Error(CLI_NO_SPACE_FOR_NEW_COMMAND);
  return 1;
}

void CLI_RawInput(uint8_t *raw)
{
  uint32_t i=0;
  do
  {
    CLI_Input(raw[i++]);
  }while(raw[i]!='\0');
  if( i>2 && (raw[i-1]!='\n') && (raw[i-2]!='\r') )
  {
    CLI_Input('\r');
    CLI_Input('\n');
  }
}

void CLI_Input(uint8_t c)
{
  CLI_RxBuf[CLI_RxPtr++]=c;
  if(CLI_RxPtr>0 && ( CLI_RxBuf[CLI_RxPtr-1]=='\n' || CLI_RxBuf[CLI_RxPtr-2]=='\r') )
  {
    if(CLI_RxPtr<=2)
    {
      CLI_Error(CLI_INVALID_CMD);
    }
    else
    {
      //CLI_RxBuf[CLI_RxPtr-1]=0;//artificially add a NULL at the end of the command
      //CLI_RxBuf[CLI_RxPtr-2]=0;//artificially add a NULL at the end of the command
      CLI_RxBuf[CLI_RxPtr]=0;//artificially add a NULL at the end of the command
      if(CLI_UserInterpreter)
      {
        if(CLI_UserInterpreter(CLI_RxBuf)) 
          CLI_Interpreter(CLI_RxBuf);//if User interpreter fails, try with built-in interpreter
      }
      else
        CLI_Interpreter(CLI_RxBuf);
    }
    CLI_RxPtr=0;
  }
  if(CLI_RxPtr>254)
    CLI_RxPtr=0;  
}

void CLI_Interpreter(uint8_t *str)
{
  uint8_t i=0;
  uint32_t len=strlen(str);
  if(str[len-1]=='\n' || str[len-1]=='\r')
    str[len-1]=0;
  if(str[len-2]=='\n' || str[len-2]=='\r')
    str[len-2]=0;
  //CLI_Log("\r\nCMD ready to be parsed");
  for(i=0;i<CLI_CMD_MAX_NUMBER;i++)
  {
    if(strcmp(str,CLI_CmdList[i].name)==0)
    {
      CLI_CmdList[i].Callback();
      CLI_Log("\r\nCLI: Cmd done");
      return;
    }
  }
  CLI_Error(CLI_INVALID_CMD);
}

void CLI_Output(uint8_t *str)
{
  if(CLI_Out && CLI_Output_Enable)
    CLI_Out(str);
}

void CLI_OutputEnable(uint8_t en)
{
  CLI_Output_Enable=en?1:0;
}
     
void CLI_Error(uint8_t type)
{
  switch(type)
  {
  case CLI_INVALID_CMD: 
    CLI_Log("\r\nCLI: Invalid command");
    break;
  case CLI_NO_SPACE_FOR_NEW_COMMAND:
    CLI_Log("\r\nCLI: No space for extra command");
    break;
  default:
    break;
  }
}