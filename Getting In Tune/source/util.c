/*
 * util.c
 *
 *  Created on: Nov 14, 2020
 *      Author: Arpit Savarkar / arpit.savarkar@colorado.edu
 *     @brief: Sets up some utility functions for ADC and DAC analysis
 *
 *       Sources of Reference :
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers

  I would like to thank Howdy Pierce, Rakesh Kumar, Saket Penurkar for their
  support during this assignment.
 *
 */


#include "util.h"
#include "autocorrelate.h"
#include "assert.h"
#include "stdio.h"
#include "stdint.h"
#include "DAC.h"
#include "fp_sine.h"
#include "fsl_debug_console.h"


/*
 * Fill a buffer with 12-bit unsigned samples, representing the
 * specified tone
 *
 * Parameters:
 *    input_freq    The frequency of the tone to be played
 *    buffer       The buffer to store the samples into
 *    size     The size of the buffer, in number of samples
 *
 * Returns:
 *    The number of samples actually computed
 *
 * This function pre-computes the samples for the given tone. Used
 * during DAC. function fills up the buffer.
 */
size_t tone_to_samples(int input_freq, uint16_t *buffer, size_t size) {

	int32_t temp;
	int i=0;
	int cycles = size / ((FREQ + (input_freq/2)) / input_freq);
	int samples = ((FREQ + (input_freq/2)) / input_freq) * cycles;

	for (i=0; i < samples; i++) {
		// Needs to be converted appropriately
		temp = fp_sin(i * TWO_PI / ((FREQ + (input_freq/2)) / input_freq) ) + TRIG_SCALE_FACTOR;
		buffer[i] = temp;
	}

	PRINTF("Generated %d samples at %d Hz; computed period=%d, observed=%d\r\n",
			samples, input_freq, ((FREQ + (input_freq/2)) / input_freq),
	  autocorrelate_detect_period(buffer, samples, 0));

   return samples;
}


/*
 * Analyzes the Input Samples
 *
 * Parameters:
 *   buffer    Buffer to analyze
 *   count    Sample Size
 *
 * Return:
 * void
 *
 */
void analysis(uint16_t *buffer, uint32_t count) {

	int i=0;
	uint32_t max=0, sum = 0;
	int min = -1;

	// Keeps to within limit
	for (i=0; i < count; i++) {
		if (buffer[i] > max) {
			max = buffer[i];
		}
		if (buffer[i] < min) {
			min = buffer[i];
		}

		sum+= buffer[i];

	}

	int temp = autocorrelate_detect_period(buffer, count, 1);
	PRINTF("min=%u max=%u avg=%u period=%d frequency=%d Hz\r\n",
	      min, max, sum / count, temp, 96000 / temp);

}
