/******************************************************************************
*​​Copyright​​ (C) ​​2020 ​​by ​​Arpit Savarkar
*​​Redistribution,​​ modification ​​or ​​use ​​of ​​this ​​software ​​in​​source​ ​or ​​binary
*​​forms​​ is​​ permitted​​ as​​ long​​ as​​ the​​ files​​ maintain​​ this​​ copyright.​​ Users​​ are
*​​permitted​​ to ​​modify ​​this ​​and ​​use ​​it ​​to ​​learn ​​about ​​the ​​field​​ of ​​embedded
*​​software. ​​Arpit Savarkar ​​and​ ​the ​​University ​​of ​​Colorado ​​are ​​not​ ​liable ​​for
*​​any ​​misuse ​​of ​​this ​​material.
*
******************************************************************************/
/**
 * @file Getting in Tune.c
 * @brief This file provides functions prototypes and abstractions to mathematically generate four pure tones in the form of analog signals memory access (DMA) subsystem.
 *
 * @author Arpit Savarkar
 * @date November 24 2020
 * @version 1.0

  Sources of Reference :
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers

  I would like to thank Howdy Pierce, Rakesh Kumar, Saket Penurkar for their
  support during this assignment.

*/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "fp_sine.h"
#include "ADC.h"
#include "DAC.h"
#include "autocorrelate.h"
#include "util.h"
#include "stdint.h"
#include "test_sin.h"

#define ADC_FREQ 96000
#define SIZE 1024
/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    int samples, i=0;
    uint16_t output[SIZE], input[SIZE];
    int frequencies[] = {440, 587, 659, 880};
    DAC_Init_();
    DMA_Init_();
    TPM0_Init_();
    TPM1_Init_(ADC_FREQ);
    ADC_Init_();

    PRINTF("Testing Sine function errors. Please wait...\r\n");
    test_sine();
    PRINTF("\r\n Sine error bounds Computed\r\n");


    // Infinite Loop to Run through the frequencies
    for(i = 0; i<=4; i++) {
    	if(i==4) {
			i=0;
		}
    	PRINTF("Frequency: %d Hz\r\n", frequencies[i]);
    	samples = tone_to_samples(frequencies[i], output, 1024);
    	DAC_begin(output, samples);
    	ADC_Buffer(input, 1024);
    	analysis(input, 1024);

    }
    return 0 ;
}
