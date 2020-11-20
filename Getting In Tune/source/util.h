/*
 * util.h
 *
 *  Created on: Nov 14, 2020
 *      Author: root
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "MKL25Z4.h"

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
size_t tone_to_samples(int input_freq, uint16_t *buffer, size_t size);


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
void analysis(uint16_t *buffer, uint32_t count);

#endif /* UTIL_H_ */
