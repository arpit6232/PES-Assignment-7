/*
 * fp_sine.h
 *
 *  Created on: Nov 12, 2020
 *      Author: Arpit Savarakr / arpit.savarkar@colorado.edu
 *
 *   @brief Header file for fp_sine.c Initializes the Lookup Table
 *
 *     Sources of Reference :
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers

  I would like to thank Howdy Pierce, Rakesh Kumar, Saket Penurkar for their
  support during this assignment.
 *
 */

#ifndef FP_SINE_H_
#define FP_SINE_H_


#include <stdint.h>

#define TRIG_SCALE_FACTOR	(2037)
#define HALF_PI				(3200)
#define PI 					(6399)
#define TWO_PI				(12799)


/*
 * Computes sine of x within max ranges
 *
 * Parameters:
 *    x     Expressed in radians * TRIG_SCALE_FACTOR
 *
 * Returns:
 *    sin(x) * SCALE_FACTOR
 *
 */
int32_t fp_sin(int32_t x);


/*
 * Performs linear interpolation using fixed-point math
 *
 * Parameters:
 *    x       Input x value
 *    (x1, y1), (x2, y2):  First pt, Second pt
 *
 * Returns:
 *    Interpolated value
 */
int32_t interpolate(int32_t x, int32_t x1, int32_t y1, int32_t x2, int32_t y2);


/*
 * Converts from degrees (unscaled) into radians (scaled)
 *
 * Parameters:
 *    val : angle in degrees
 *
 * Returns:
 *    Radian Equivalent of degrees
 */
int32_t convert_to_radians(int val);

#endif /* FP_SINE_H_ */
