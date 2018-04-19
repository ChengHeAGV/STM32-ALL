#ifndef __LED_H
#define __LED_H

#include "sys.h"



#define LED_CPU PCout(13)// PC13
#define JDQ8 PAout(8)// PC13
#define JDQ7 PAout(11)// PC13
#define JDQ6 PAout(12)// PC13
#define JDQ5 PAout(15)// PC13

#define JDQ0 PBout(7)// PC13
#define JDQ1 PBout(6)// PC13
#define JDQ2 PBout(5)// PC13
#define JDQ3 PBout(4)// PC13
#define JDQ4 PBout(3)// PC13
#define JDQ9 PBout(15)// PC13
#define JDQ10 PBout(14)// PC13
#define JDQ11 PBout(13)// PC13

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

void Init_LEDpin(void);


#endif


