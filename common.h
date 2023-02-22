#ifndef __COMMON_H
#define __COMMON_H

/*
	Questo file contiene tutte le dichiarazioni comuni ai diversi
	file. Le variabili sono successivamente dichiarate dentro sample.c
*/

extern unsigned char led_value;

//IRQ priorities
#define PRIO_0 0U
#define PRIO_1 1U
#define PRIO_2 2U
#define PRIO_3 3U
#define PRIO_4 4U
#define PRIO_5 5U

/******************************************************************************
**                            End Of File
******************************************************************************/

#endif // __COMMON_H
