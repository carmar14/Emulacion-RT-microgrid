/*
 * File: control_terciario.c
 *
 * Code generated for Simulink model 'control_terciario'.
 *
 * Model version                  : 1.67
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Tue Dec 11 16:22:48 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "control_terciario.h"
#include "control_terciario_private.h"

/* External inputs (root inport signals with default storage) */
ExtU_control_terciario_T control_terciario_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_control_terciario_T control_terciario_Y;

/* Real-time model */
RT_MODEL_control_terciario_T control_terciario_M_;
RT_MODEL_control_terciario_T *const control_terciario_M = &control_terciario_M_;
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (control_terciario_M->Timing.TaskCounters.TID[1])++;
  if ((control_terciario_M->Timing.TaskCounters.TID[1]) > 299) {/* Sample time: [0.03s, 0.0s] */
    control_terciario_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void control_terciario_step(void)
{
  int32_T flagDelt;
  real_T rtb_MaxP;
  real_T rtb_MaxQ;
  if (control_terciario_M->Timing.TaskCounters.TID[1] == 0) {
    /* MATLAB Function: '<Root>/MATLAB Function1' incorporates:
     *  Inport: '<Root>/soc'
     */
    /*   funcion que calcula la potencia maxima que puede suministrar las fuentes */
    /*   renovables deacuerdo a la cantidad de carga que hay almancenada en la */
    /*   bateria. esta va de 0 a 100% */
    /* MATLAB Function 'MATLAB Function1': '<S3>:1' */
    /*  estoc valores que aparecen a continuacion se pusieron de manera */
    /*  arbitraria. corresponde a una persona con especialidad en la parte de */
    /*  potencia electrica determinar el verdadero algoritmo para hallar la */
    /*  potencia que deberia suministrar el nodo de energia renovable deacuerdo a */
    /*  la carga de la bateria. */
    /* '<S3>:1:15' MaxP = 0; */
    rtb_MaxP = 0.0;

    /* '<S3>:1:16' MaxQ = 0; */
    rtb_MaxQ = 0.0;

    /* '<S3>:1:18' if( SOC >= 90 ) */
    if (control_terciario_U.soc >= 90.0) {
      /* '<S3>:1:19' MaxP = 500; */
      rtb_MaxP = 500.0;

      /* '<S3>:1:20' MaxQ = 5000; */
      rtb_MaxQ = 5000.0;
    }

    /* '<S3>:1:23' if( SOC <= 90 ) */
    if (control_terciario_U.soc <= 90.0) {
      /* '<S3>:1:24' MaxP = 200; */
      rtb_MaxP = 200.0;

      /* '<S3>:1:25' MaxQ = 4000; */
      rtb_MaxQ = 4000.0;
    }

    /* '<S3>:1:28' if( SOC <= 70 ) */
    if (control_terciario_U.soc <= 70.0) {
      /* '<S3>:1:29' MaxP = 100; */
      rtb_MaxP = 100.0;

      /* '<S3>:1:30' MaxQ = 1000; */
      rtb_MaxQ = 1000.0;
    }

    /* '<S3>:1:33' if( SOC <= 60 ) */
    if (control_terciario_U.soc <= 60.0) {
      /* '<S3>:1:34' MaxP = 50; */
      rtb_MaxP = 50.0;

      /* '<S3>:1:35' MaxQ = 500; */
      rtb_MaxQ = 500.0;
    }

    /* End of MATLAB Function: '<Root>/MATLAB Function1' */

    /* Outport: '<Root>/Pb' incorporates:
     *  MATLAB Function: '<Root>/LinearProg Potencia Activa'
     */
    /* , P_e_alt_min) */
    /* MATLAB Function 'LinearProg Potencia Activa': '<S1>:1' */
    /*  P_load es la potencia que se requiere en la carga. */
    /*  P_e_alt es la potencia estimada de generacion de las energias */
    /*  alternativas */
    /*  kb y kd son los pesos de las funcion de costo. */
    /*  las salidas son las potencias optimas para bio y diesel */
    /* '<S1>:1:12' Pb=0; */
    control_terciario_Y.Pb = 0.0;

    /* Outport: '<Root>/Pd' incorporates:
     *  MATLAB Function: '<Root>/LinearProg Potencia Activa'
     */
    /* '<S1>:1:13' Pd=0; */
    control_terciario_Y.Pd = 0.0;

    /* MATLAB Function: '<Root>/LinearProg Potencia Activa' incorporates:
     *  Inport: '<Root>/Pbmax'
     *  Inport: '<Root>/Pdmax'
     *  Inport: '<Root>/Pm'
     *  Inport: '<Root>/kbP'
     *  Inport: '<Root>/kdP'
     */
    /* - P_e_alt_min % superaavit de energia alternativa. */
    /* '<S1>:1:15' D_P_e_alt = P_e_alt %- P_e_alt_min % superaavit de energia alternativa. */
    /* '<S1>:1:17' flagDelt = 0; */
    flagDelt = 0;

    /* '<S1>:1:19' if(D_P_e_alt >= P_load) */
    if (rtb_MaxP >= control_terciario_U.Pm) {
      /* '<S1>:1:20' flagDelt = 1; */
      flagDelt = 1;
    }

    /* '<S1>:1:24' if(flagDelt==0) */
    if (flagDelt == 0) {
      /* '<S1>:1:25' P_trad = P_load - D_P_e_alt; */
      rtb_MaxP = control_terciario_U.Pm - rtb_MaxP;

      /*  flag: variable que indica si tiene sentido evaluar los */
      /*  if's que se encuentran mas adelante. es decir, si flag = 0  */
      /*  despues del primer if entonces NO se le esta pidiendo al sistema */
      /*  mas potencia de la que puede generar y portante el problema de  */
      /*  optimizacion lineal tiene sentido. */
      /*  entonces  */
      /* '<S1>:1:32' flag=0; */
      /* '<S1>:1:34' if(P_trad>PdMax+PbMax) */
      if (rtb_MaxP > control_terciario_U.Pdmax + control_terciario_U.Pbmax) {
        /* Outport: '<Root>/Pd' */
        /* '<S1>:1:35' Pd=PdMax; */
        control_terciario_Y.Pd = control_terciario_U.Pdmax;

        /* Outport: '<Root>/Pb' */
        /* '<S1>:1:36' Pb=PbMax; */
        control_terciario_Y.Pb = control_terciario_U.Pbmax;

        /* '<S1>:1:37' flag=1; */
        flagDelt = 1;
      }

      /*  si ambas energias tienen el mismo factor de costo. */
      /* '<S1>:1:41' if(kd==kb && flag==0) */
      if ((control_terciario_U.kdP == control_terciario_U.kbP) && (flagDelt == 0))
      {
        /* Outport: '<Root>/Pb' */
        /* '<S1>:1:42' Pb=P_trad/2; */
        control_terciario_Y.Pb = rtb_MaxP / 2.0;

        /* Outport: '<Root>/Pd' */
        /* '<S1>:1:43' Pd=P_trad/2; */
        control_terciario_Y.Pd = rtb_MaxP / 2.0;
      }

      /*  si la energia diesel es mas cara que la biomasa. */
      /* '<S1>:1:47' if(kd>kb && flag==0) */
      if ((control_terciario_U.kdP > control_terciario_U.kbP) && (flagDelt == 0))
      {
        /* '<S1>:1:48' if(P_trad<=PbMax) */
        if (rtb_MaxP <= control_terciario_U.Pbmax) {
          /* Outport: '<Root>/Pb' */
          /* '<S1>:1:49' Pb=P_trad; */
          control_terciario_Y.Pb = rtb_MaxP;

          /* Outport: '<Root>/Pd' */
          /* '<S1>:1:50' Pd=0; */
          control_terciario_Y.Pd = 0.0;
        } else {
          /* Outport: '<Root>/Pb' */
          /* '<S1>:1:51' else */
          /* '<S1>:1:52' Pb=PbMax; */
          control_terciario_Y.Pb = control_terciario_U.Pbmax;

          /* Outport: '<Root>/Pd' */
          /* '<S1>:1:53' Pd=P_trad-PbMax; */
          control_terciario_Y.Pd = rtb_MaxP - control_terciario_U.Pbmax;
        }
      }

      /*  si la biomasa es mas cara que la diesel. */
      /* '<S1>:1:58' if(kd<kb && flag==0) */
      if ((control_terciario_U.kdP < control_terciario_U.kbP) && (flagDelt == 0))
      {
        /* '<S1>:1:59' if(P_trad<=PdMax) */
        if (rtb_MaxP <= control_terciario_U.Pdmax) {
          /* Outport: '<Root>/Pd' */
          /* '<S1>:1:60' Pd=P_trad; */
          control_terciario_Y.Pd = rtb_MaxP;

          /* Outport: '<Root>/Pb' */
          /* '<S1>:1:61' Pb=0; */
          control_terciario_Y.Pb = 0.0;
        } else {
          /* Outport: '<Root>/Pd' */
          /* '<S1>:1:62' else */
          /* '<S1>:1:63' Pd=PdMax; */
          control_terciario_Y.Pd = control_terciario_U.Pdmax;

          /* Outport: '<Root>/Pb' */
          /* '<S1>:1:64' Pb=P_trad-PdMax; */
          control_terciario_Y.Pb = rtb_MaxP - control_terciario_U.Pdmax;
        }
      }
    }

    /* Outport: '<Root>/Qb' incorporates:
     *  MATLAB Function: '<Root>/LinearProg Potenica Reactiva'
     */
    /* '<S1>:1:69' Pbo=Pb; */
    /* '<S1>:1:70' Pdo=Pd; */
    /*  Q_load es la potencia que se requiere en la carga. */
    /* MATLAB Function 'LinearProg Potenica Reactiva': '<S2>:1' */
    /*  Q_e_alt es la potencia estimada de generacion de las energias */
    /*  alternativas */
    /*  kb y kd son los pesos de las funcion de costo. */
    /*  las salidas son las potencias optimas para bio y diesel */
    /* '<S2>:1:12' Qb=0; */
    control_terciario_Y.Qb = 0.0;

    /* Outport: '<Root>/Qd' incorporates:
     *  MATLAB Function: '<Root>/LinearProg Potenica Reactiva'
     */
    /* '<S2>:1:13' Qd=0; */
    control_terciario_Y.Qd = 0.0;

    /* MATLAB Function: '<Root>/LinearProg Potenica Reactiva' incorporates:
     *  Gain: '<Root>/Gain17'
     *  Inport: '<Root>/Qbmax'
     *  Inport: '<Root>/Qdmax'
     *  Inport: '<Root>/Qm'
     *  Inport: '<Root>/kbQ'
     *  Inport: '<Root>/kdQ'
     */
    /* '<S2>:1:15' D_P_e_alt = Q_e_alt ; */
    /* - Q_e_alt_min % superaavit de energia alternativa. */
    /* '<S2>:1:17' flagDelt = 0; */
    flagDelt = 0;

    /* '<S2>:1:19' if(D_P_e_alt >= Q_load) */
    if (rtb_MaxQ >= -control_terciario_U.Qm) {
      /* '<S2>:1:20' flagDelt = 1; */
      flagDelt = 1;
    }

    /* '<S2>:1:24' if(flagDelt==0) */
    if (flagDelt == 0) {
      /* '<S2>:1:25' Q_trad = Q_load - D_P_e_alt; */
      rtb_MaxQ = -control_terciario_U.Qm - rtb_MaxQ;

      /*  flag: variable que indica si tiene sentido evaluar los */
      /*  if's que se encuentran mas adelante. es decir, si flag = 0  */
      /*  despues del primer if entonces NO se le esta pidiendo al sistema */
      /*  mas potencia de la que puede generar y portante el problema de  */
      /*  optimizacion lineal tiene sentido. */
      /*  entonces  */
      /* '<S2>:1:32' flag=0; */
      /* '<S2>:1:34' if(Q_trad>QdMax+QbMax) */
      if (rtb_MaxQ > control_terciario_U.Qdmax + control_terciario_U.Qbmax) {
        /* Outport: '<Root>/Qd' */
        /* '<S2>:1:35' Qd=QdMax; */
        control_terciario_Y.Qd = control_terciario_U.Qdmax;

        /* Outport: '<Root>/Qb' */
        /* '<S2>:1:36' Qb=QbMax; */
        control_terciario_Y.Qb = control_terciario_U.Qbmax;

        /* '<S2>:1:37' flag=1; */
        flagDelt = 1;
      }

      /*  si ambas energias tienen el mismo factor de costo. */
      /* '<S2>:1:41' if(kd==kb && flag==0) */
      if ((control_terciario_U.kdQ == control_terciario_U.kbQ) && (flagDelt == 0))
      {
        /* Outport: '<Root>/Qb' */
        /* '<S2>:1:42' Qb=Q_trad/2; */
        control_terciario_Y.Qb = rtb_MaxQ / 2.0;

        /* Outport: '<Root>/Qd' */
        /* '<S2>:1:43' Qd=Q_trad/2; */
        control_terciario_Y.Qd = rtb_MaxQ / 2.0;
      }

      /*  si la energia diesel es mas cara que la biomasa. */
      /* '<S2>:1:47' if(kd>kb && flag==0) */
      if ((control_terciario_U.kdQ > control_terciario_U.kbQ) && (flagDelt == 0))
      {
        /* '<S2>:1:48' if(Q_trad<=QbMax) */
        if (rtb_MaxQ <= control_terciario_U.Qbmax) {
          /* Outport: '<Root>/Qb' */
          /* '<S2>:1:49' Qb=Q_trad; */
          control_terciario_Y.Qb = rtb_MaxQ;

          /* Outport: '<Root>/Qd' */
          /* '<S2>:1:50' Qd=0; */
          control_terciario_Y.Qd = 0.0;
        } else {
          /* Outport: '<Root>/Qb' */
          /* '<S2>:1:51' else */
          /* '<S2>:1:52' Qb=QbMax; */
          control_terciario_Y.Qb = control_terciario_U.Qbmax;

          /* Outport: '<Root>/Qd' */
          /* '<S2>:1:53' Qd=Q_trad-QbMax; */
          control_terciario_Y.Qd = rtb_MaxQ - control_terciario_U.Qbmax;
        }
      }

      /*  si la biomasa es mas cara que la diesel. */
      /* '<S2>:1:58' if(kd<kb && flag==0) */
      if ((control_terciario_U.kdQ < control_terciario_U.kbQ) && (flagDelt == 0))
      {
        /* '<S2>:1:59' if(Q_trad<=QdMax) */
        if (rtb_MaxQ <= control_terciario_U.Qdmax) {
          /* Outport: '<Root>/Qd' */
          /* '<S2>:1:60' Qd=Q_trad; */
          control_terciario_Y.Qd = rtb_MaxQ;

          /* Outport: '<Root>/Qb' */
          /* '<S2>:1:61' Qb=0; */
          control_terciario_Y.Qb = 0.0;
        } else {
          /* Outport: '<Root>/Qd' */
          /* '<S2>:1:62' else */
          /* '<S2>:1:63' Qd=QdMax; */
          control_terciario_Y.Qd = control_terciario_U.Qdmax;

          /* Outport: '<Root>/Qb' */
          /* '<S2>:1:64' Qb=Q_trad-QdMax; */
          control_terciario_Y.Qb = rtb_MaxQ - control_terciario_U.Qdmax;
        }
      }
    }

    /* '<S2>:1:69' Qbo=Qb; */
    /* '<S2>:1:70' Qdo=Qd; */
  }

  rate_scheduler();
}

/* Model initialize function */
void control_terciario_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)control_terciario_M, 0,
                sizeof(RT_MODEL_control_terciario_T));

  /* external inputs */
  (void)memset((void *)&control_terciario_U, 0, sizeof(ExtU_control_terciario_T));

  /* external outputs */
  (void) memset((void *)&control_terciario_Y, 0,
                sizeof(ExtY_control_terciario_T));
}

/* Model terminate function */
void control_terciario_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
