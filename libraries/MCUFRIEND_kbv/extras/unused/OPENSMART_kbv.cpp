// this will avoid any library editing
//
// but the sketch must use specific OPENSMART_kbv class constructor

#define USE_SPECIAL                     //SPECIAL will use the first match 
//#define USE_OPENSMART_SHIELD_PINOUT     //deprecated
//select the target board
#define USE_OPENSMART_SHIELD_PINOUT_UNO
#define USE_OPENSMART_SHIELD_PINOUT_MEGA
#define USE_OPENSMART_SHIELD_PINOUT_DUE //thanks Michel53
//select the target controllers that are not enabled by default 
#define SUPPORT_8352A                   //HX8352A
#define SUPPORT_8352B                   //HX8352B
#define SUPPORT_9225                    //RM68130

#include "OPENSMART_kbv.h"              //class declaration

#define MCUFRIEND_kbv OPENSMART_kbv     //rename the class scope 

#include "MCUFRIEND_kbv.cpp"            //same methods, but with OPENSMART_kbv class scope
