#ifndef _CLI_H_
#define _CLI_H_
#include <stdio.h>   
#include <string.h>
#include "stm32f2xx.h"
#include "commonDefs.h"



#define CLI_CMD_NAME_LENGTH 20
#define CLI_CMD_MAX_NUMBER 20

/* error types */
#define CLI_INVALID_CMD 0
#define CLI_NO_SPACE_FOR_NEW_COMMAND 1

typedef struct
{
	uint8_t name[CLI_CMD_NAME_LENGTH];
	void (*Callback)(void);
}CLI_Cmd_t;



void CLI_Init(void StrOut(uint8_t *),uint8_t UserInterpreter(uint8_t *) );
uint8_t CLI_AddCmd(uint8_t *CmdName, void (*cb)(void));
void CLI_RawInput(uint8_t *raw);
void CLI_Input(uint8_t c);
uint8_t CLI_Test(void);
void CLI_Output(uint8_t *str);
void CLI_OutputEnable(uint8_t en);

#endif /* _CLI_H_ */
