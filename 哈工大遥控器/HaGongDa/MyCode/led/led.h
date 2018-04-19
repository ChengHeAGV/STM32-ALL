#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define LED_CPU PAout(11)// PA11

#define YaoGan_Key PAin(3)// PC13

#define BEEP 	PBout(10)// PC13
extern void Init_LEDpin(void);

#endif


