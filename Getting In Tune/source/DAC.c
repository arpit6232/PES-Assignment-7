/*
 * DMA.c
 *
 *  Created on: Nov 13, 2020
 *      Author: Arpit Savarkar / arpit.savarkar@colorado.edu
 *
 *   @brief: This module will contain the necessary configuration and runtime
code that allows you to pass your computed buffer of audio samples into the module. The
module will use the KL25Z’s DAC, TPM0, and DMA hardware to repeatedly play out the buffer
without further intervention from your main loop.

  Sources of Reference :
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers

  I would like to thank Howdy Pierce, Rakesh Kumar, Saket Penurkar for their
  support during this assignment.

 */

#include "DAC.h"
#include "MKL25Z4.h"
#include "stdio.h"
#include "string.h"

// Global Variables
static uint16_t buffer[1024];
static uint32_t count = 0;

#define DAC0_PIN 30


/*
 * Initializing the DAC Subsystem
 *
 * Parameters:
 *   void
 *
 * Returns:
 *   void
 */
void DAC_Init_() {

	// Clock Gating
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK; // DAC
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	// Pin and Port Setup
	PORTE->PCR[DAC0_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[DAC0_PIN] |= PORT_PCR_MUX(3);

	// // Not using DAC0 buffer, disable to use buffer
    DAC0->C1 = 0;
    DAC0->C2 = 0;

    // Set DAC0 to reference voltage from VDDA
    DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;

}

/*
 * Initializing the DMA Functionalities
 *
 * Parameters:
 *   void
 *
 * Returns:
 *   void
 */
void DMA_Init_() {

	//  Gate Clock
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	// Disabbling for Configuration
	DMAMUX0->CHCFG[0] = 0;

	// interrupt once done, increment src, src size: 16 bits, dest size: 16 bits, enable requests, enable DMA0
	DMA0->DMA[0].DCR = DMA_DCR_EINT_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2) | DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK;

	// NVIC Config
	NVIC_SetPriority(DMA0_IRQn, 2);
	NVIC_ClearPendingIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn);

	// Enable DMA MUX channel with TPM0 overflow as trigger
	DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_SOURCE(54);
}


/*
 * Initializing the TPM0 Functionalities
 *
 * Parameters:
 *   void
 *
 * Returns:
 *   void
 */
void TPM0_Init_() {

	// Gating
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

	// 48 Mhz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	// Begin Configuration
	TPM0->SC = 0;

	// Load the mod and counter
	TPM0->MOD = TPM_MOD_MOD(SYS_CLOCK / (SYS_CLOCK/1000));
	TPM0->CNT = 0;

	// TPM Source Configuration
	TPM0->SC = TPM_SC_PS(0) | TPM_SC_CPWMS(0) | TPM_SC_CMOD(1) | TPM_SC_DMA_MASK;
}


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
void DAC_begin(uint16_t *frq, uint32_t cnt){

	// TPM Disable
	TPM0->SC &= ~TPM_SC_CMOD_MASK;

	// For interfacing with the global count function
	count = cnt;

	// Memory copy to buffer
	memcpy(buffer, frq, cnt*2);

	// Begin Configuration
	TPM0->SC |= TPM_SC_CMOD(1);

	// Configure the src and dest registers
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) buffer);
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));

	// Number of bytes to transfer
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(count * 2);
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
}

/*
 * IRQ Handler
 */
void DMA0_IRQHandler(void)
{
	// Goddamit, have to Clear done flag in IRQ
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;

	// DMA playback
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) buffer);
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));

	// Bytes to transfer
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(count * 2);
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
}


