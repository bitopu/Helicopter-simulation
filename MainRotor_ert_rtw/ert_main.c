/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'MainRotor'.
 *
 * Model version                  : 2.125
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Mon Apr  6 15:48:13 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>            /* This example main program uses printf/fflush */
#include "MainRotor.h"                 /* Model header file */

static RT_MODEL_MainRotor_T MainRotor_M_;
static RT_MODEL_MainRotor_T *const MainRotor_MPtr = &MainRotor_M_;/* Real-time model */
static B_MainRotor_T MainRotor_B;      /* Observable signals */

/* '<Root>/SpeedM' */
static real_T MainRotor_U_SpeedM;

/* '<Root>/CollectiveM' */
static real_T MainRotor_U_CollectiveM;

/* '<Root>/CyclicLat' */
static real_T MainRotor_U_CyclicLat;

/* '<Root>/CyclicLon' */
static real_T MainRotor_U_CyclicLon;

/* '<Root>/rho' */
static real_T MainRotor_U_rho;

/* '<Root>/wb' */
static real_T MainRotor_U_wb[3];

/* '<Root>/Vb' */
static real_T MainRotor_U_Vb[3];

/* '<Root>/Fm' */
static real_T MainRotor_Y_Fm[3];

/* '<Root>/Mm' */
static real_T MainRotor_Y_Mm[3];

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(RT_MODEL_MainRotor_T *const MainRotor_M);
void rt_OneStep(RT_MODEL_MainRotor_T *const MainRotor_M)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(MainRotor_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  MainRotor_step(MainRotor_M, MainRotor_U_SpeedM, MainRotor_U_CollectiveM,
                 MainRotor_U_CyclicLat, MainRotor_U_CyclicLon, MainRotor_U_rho,
                 MainRotor_U_wb, MainRotor_U_Vb, MainRotor_Y_Fm, MainRotor_Y_Mm);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example main function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific. This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_MainRotor_T *const MainRotor_M = MainRotor_MPtr;

  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Pack model data into RTM */
  MainRotor_M->blockIO = &MainRotor_B;

  /* Initialize model */
  MainRotor_initialize(MainRotor_M, &MainRotor_U_SpeedM,
                       &MainRotor_U_CollectiveM, &MainRotor_U_CyclicLat,
                       &MainRotor_U_CyclicLon, &MainRotor_U_rho, MainRotor_U_wb,
                       MainRotor_U_Vb, MainRotor_Y_Fm, MainRotor_Y_Mm);

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.01 seconds (base rate of the model) here.
   * The call syntax for rt_OneStep is
   *
   *  rt_OneStep(MainRotor_M);
   */
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(MainRotor_M) == (NULL)) {
    /*  Perform application tasks here */
  }

  /* Terminate model */
  MainRotor_terminate(MainRotor_M);
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
