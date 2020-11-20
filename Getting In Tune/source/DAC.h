/*
 * DMA.h
 *
 *  Created on: Nov 13, 2020
 *      Author: root
 */

#ifndef DAC_H_
#define DAC_H_

#include "MKL25Z4.h"
#include "stdio.h"
#include "stdint.h"

/*
 * DAC Frequency
 */
#define FREQ			(48000)
/*
 * System Clock Hz
 */
#define SYS_CLOCK		(48e6)

/*
 * Initializing the DAC Subsystem
 *
 * Parameters:
 *   void
 *
 * Returns:
 *   void
 */
void DAC_Init_();


/*
 * Initializing the DMA Functionalities
 *
 * Parameters:
 *   void
 *
 * Returns:
 *   void
 */
void DMA_Init_();


/*
 * Initializing the TPM0 Functionalities
 *
 * Parameters:
 *   void
 *
 * Returns:
 *   void
 */
void TPM0_Init_();


/*
 * Function to begin and end the playback of the freuencies,
 *
 * Parameters:
 *   frq: uint16_t* - Buffer to play back
 *   cnt: uint32_t - Sample Count
 *
 * Returns:
 *   void
 */
void DAC_begin(uint16_t *frq, uint32_t cnt);

//void DAC_end();

#endif /* DAC_H_ */
