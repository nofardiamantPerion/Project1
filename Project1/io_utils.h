#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_
// you must have a config file, both for windows and for compiling on Linux (MAMA)
// BUT, you need to change the content of the config!
#include "config.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "Direction.h"
#include "StepAndDirection.h"
#include "configuration.h"
#include <list>

using namespace std;

void gotoxy(int x, int y);
void hideCursor();
void clear_screen();

#ifndef WINDOWS	
int _getch(void);
int _kbhit(void);
void Sleep(unsigned long);
void _itoa_s(unsigned int, char s[], unsigned int, int);
#else
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#endif

#endif