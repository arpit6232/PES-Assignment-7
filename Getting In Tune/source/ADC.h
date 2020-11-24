/*
 * ADC.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Arpit Savarkar
 *
 *  @brief: Header file of ADC.c the buffer functionalities and #defines for ADC
 *
 *    Sources of Reference :
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers

  I would like to thank Howdy Pierce, Rakesh Kumar, Saket Penurkar for their
  support during this assignment.
 *
 */

#ifndef ADC_H_
#define ADC_H_

#define SYS_CLOCK		(48e6)

#define BEGIN_TPM1 TPM1->SC |= TPM_SC_CMOD(1);
#define STOP_TPM1  TPM1->SC &= ~TPM_SC_CMOD_MASK;

/*
 * Initializing the TPM1 Timer
 *
 * Parameters:
 *   sample: int Initializes the TPM Clock to the requested rate
 *
 * Returns:
 *   void
 */
void TPM1_Init_(int sample);

/*
 * ADC Initializer function to appropriate characteristics
 *
 * Parameters:
 *   void
 *
 * Returns:
 *   void
 */
void ADC_Init_();

/*
 * Buffer Setup to be retrieved at the frequency specified in the parameters
 * , 16 bits per sample
 *
 * Parameters:
 *   buffer : uint16_t* Buffer to store values
 *   sample_count: uint32_t Samples Count to transfer to buffer
 *
 * Returns:
 *   void
 */
void ADC_Buffer(uint16_t *buffer, uint32_t sample_count);


#endif /* ADC_H_ */
