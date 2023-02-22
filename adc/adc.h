#ifndef __ADC_H
#define __ADC_H

#include <string.h>

/* lib_adc.c */
void ADC_init (void);
void ADC_start_conversion (void);

/* IRQ_adc.c */
void ADC_IRQHandler(void);

#endif // __ADC_H
