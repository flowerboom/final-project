#ifndef __KEY_H
#define __KEY_H	 

#include "LPC11xx.h"

typedef enum
{
    KEY_DOWN  =   0,         
    KEY_UP    =   1,                      

} KEY_STATUS;
extern void         key_init(void ); 
extern KEY_STATUS   key_get(void);  

#endif
