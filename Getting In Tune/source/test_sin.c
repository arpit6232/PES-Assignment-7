/*
 * test_sin.c
 *
 *  Created on: Nov 14, 2020
 *      Author: Arpit Savarakr / arpit.savarkar@colorado.edu
 *
 *   @brief: Contains function to test if the sine data generated from fp_sine.c is within error bounds
 *
 *     Sources of Reference :
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers

  I would like to thank Howdy Pierce, Rakesh Kumar, Saket Penurkar for their
  support during this assignment.
 *
 */


#include "stdio.h"
#include "fp_sine.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "math.h"

void test_sine()
{
double act_sin;
double exp_sin;
double err;
double sum_sq = 0;
double max_err = 0;
int i= 0;
for (i=-TWO_PI; i <= TWO_PI; i++) {
exp_sin = sin( (double)i / TRIG_SCALE_FACTOR) * TRIG_SCALE_FACTOR;
act_sin = fp_sin(i);
err = act_sin - exp_sin;
if (err < 0)
err = -err;
if (err > max_err)
max_err = err;
sum_sq += err*err;
}
PRINTF("max_err=%d sum_sq=%d\n", (int)max_err, (int)sum_sq);
}
