#include "console.h"
#include "serial.h"

void (*ConsoleOutput)(uint8_t *)=0;
void console_Init(void consoleOut(uint8_t *))
{
  if(consoleOut)
    ConsoleOutput=consoleOut;
  else
    ConsoleOutput=Serial_SendString;
}

void console_log(uint8_t *str)
{
  if(ConsoleOutput)
    ConsoleOutput(str);
}



