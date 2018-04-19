#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define LED0 PCout(13)// PC13

#define IN0 PAin(0)// PC13
#define IN1 PAin(1)// PC13
#define IN2 PAin(4)// PC13
#define IN3 PAin(5)// PC13
#define IN4 PAin(6)// PC13
#define IN5 PAin(7)// PC13
#define IN6 PBin(0)// PC13
#define IN7 PBin(1)// PC13
#define IN8 PBin(10)// PC13
#define IN9 PBin(11)// PC13
#define IN10 PBin(12)// PC13
#define IN11 PBin(13)// PC13
void Init_LEDpin(void);


#endif


