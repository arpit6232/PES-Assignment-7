/*
 * ADC.c
 *
 *  Created on: Nov 14, 2020
 *      Author: root
 */

#include "MKL25Z4.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "ADC.h"


/*
 * Initializing the TPM1 Timer
 *
 * Parameters:
 *   sample: int Initializes the TPM Clock to the requested rate
 *
 * Returns:
 *   void
 */
void TPM1_Init_(int sample) {

	// Clock Gating
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

	// Disable TPM for config
	TPM1->SC = 0;

    // mod and counter
	TPM1->MOD = TPM_MOD_MOD(SYS_CLOCK / sample);
	TPM1->CNT = 0;

	// Prescalar Settings
	TPM1->SC = TPM_SC_PS(0) | TPM_SC_CPWMS(0);

}


/*
 * ADC Initializer function to appropriate characteristics
 *
 * Parameters:
 *   void
 *
 * Returns:
 *   void
 */
void ADC_Init_() {
	// Gating
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

	// Shorter sample time, 16 bit single-ended
	ADC0->CFG1 = ADC_CFG1_ADLPC(0) | ADC_CFG1_ADIV(0) | ADC_CFG1_ADLSMP(0) | ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0);

	// Setting this to all default values
	ADC0->CFG2 = 0;

	// DMA initially disabled
	ADC0->SC2 = ADC_SC2_ADTRG(1) | ADC_SC2_ACFE(0) | ADC_SC2_DMAEN(0) | ADC_SC2_REFSEL(0);

	// Input Channel for DAC is the input for ADC
	ADC0->SC1[0] = ADC_SC1_AIEN(0) | ADC_SC1_DIFF(0) | ADC_SC1_ADCH(23);

	// Just some TPM1 things
	SIM->SOPT7 = SIM_SOPT7_ADC0ALTTRGEN(1) | SIM_SOPT7_ADC0TRGSEL(9);

}


/*
 * Buffer Setup and analysis for ADC
 *
 * Parameters:
 *   buffer : uint16_t* Buffer to store values
 *   sample_count: uint32_t Samples Count to transfer to buffer
 *
 * Returns:
 *   void
 */
void ADC_Buffer(uint16_t *buffer, uint32_t sample_count) {

	int i =0;
	// Begin TPM
	BEGIN_TPM1

	for (i =0; i < sample_count; i++) {
		while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
		      ;

		buffer[i] = ADC0->R[0];
	}

	// Stop Sampling
	STOP_TPM1
}
