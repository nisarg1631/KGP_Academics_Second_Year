#ifndef RTW_HEADER_SigNetLabExp3code_19CS30031_acc_h_
#define RTW_HEADER_SigNetLabExp3code_19CS30031_acc_h_
#include <stddef.h>
#include <float.h>
#ifndef SigNetLabExp3code_19CS30031_acc_COMMON_INCLUDES_
#define SigNetLabExp3code_19CS30031_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "SigNetLabExp3code_19CS30031_acc_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { real_T B_4_0_0 ; real_T B_4_1_0 [ 2 ] ; real_T B_4_2_0 ;
real_T B_4_5_0 ; real_T B_4_7_0 ; real_T B_4_9_0 ; real_T B_4_10_0 ; real_T
B_4_13_0 ; real_T B_4_15_0 ; real_T B_4_17_0 ; real_T B_4_20_0 ; real_T
B_4_23_0 ; real_T B_4_25_0 ; real_T B_4_27_0 ; real_T B_4_28_0 ; real_T
B_4_31_0 ; real_T B_4_33_0 ; real_T B_4_35_0 ; real_T B_4_38_0 ; real_T
B_4_42_0 ; real_T B_4_44_0 ; real_T B_4_46_0 ; real_T B_4_49_0 ; real_T
B_4_51_0 ; real_T B_4_53_0 ; real_T B_4_55_0 ; }
B_SigNetLabExp3code_19CS30031_T ; typedef struct { real_T
Memory_PreviousInput ; real_T Memory_PreviousInput_m ; real_T
Memory_PreviousInput_a ; real_T Memory_PreviousInput_p ; real_T
StateSpace_RWORK [ 2 ] ; struct { real_T modelTStart ; } TransportDelay_RWORK
; struct { real_T modelTStart ; } TransportDelay_RWORK_m ; struct { real_T
modelTStart ; } TransportDelay_RWORK_o ; struct { real_T modelTStart ; }
TransportDelay_RWORK_g ; void * StateSpace_PWORK [ 22 ] ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; struct { void * TUbufferPtrs [
2 ] ; } TransportDelay_PWORK_m ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_e ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_n ; void * Vin_PWORK ; void * Vout_PWORK ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_j ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_c ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_h ; int_T StateSpace_IWORK [ 23 ]
; struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ;
int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct { int_T Tail ; int_T
Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_d ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_f ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_m ; char_T pad_TransportDelay_IWORK_m
[ 4 ] ; } DW_SigNetLabExp3code_19CS30031_T ; typedef struct { real_T
StateSpace_CSTATE [ 2 ] ; real_T integrator_CSTATE ; real_T
integrator_CSTATE_l ; real_T integrator_CSTATE_ls ; real_T
integrator_CSTATE_m ; } X_SigNetLabExp3code_19CS30031_T ; typedef struct {
real_T StateSpace_CSTATE [ 2 ] ; real_T integrator_CSTATE ; real_T
integrator_CSTATE_l ; real_T integrator_CSTATE_ls ; real_T
integrator_CSTATE_m ; } XDot_SigNetLabExp3code_19CS30031_T ; typedef struct {
boolean_T StateSpace_CSTATE [ 2 ] ; boolean_T integrator_CSTATE ; boolean_T
integrator_CSTATE_l ; boolean_T integrator_CSTATE_ls ; boolean_T
integrator_CSTATE_m ; } XDis_SigNetLabExp3code_19CS30031_T ; typedef struct {
real_T StateSpace_CSTATE [ 2 ] ; real_T integrator_CSTATE ; real_T
integrator_CSTATE_l ; real_T integrator_CSTATE_ls ; real_T
integrator_CSTATE_m ; } CStateAbsTol_SigNetLabExp3code_19CS30031_T ; typedef
struct { real_T StateSpace_CSTATE [ 2 ] ; real_T integrator_CSTATE ; real_T
integrator_CSTATE_l ; real_T integrator_CSTATE_ls ; real_T
integrator_CSTATE_m ; } CXPtMin_SigNetLabExp3code_19CS30031_T ; typedef
struct { real_T StateSpace_CSTATE [ 2 ] ; real_T integrator_CSTATE ; real_T
integrator_CSTATE_l ; real_T integrator_CSTATE_ls ; real_T
integrator_CSTATE_m ; } CXPtMax_SigNetLabExp3code_19CS30031_T ; struct
P_SigNetLabExp3code_19CS30031_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ;
real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 [ 2 ] ; real_T P_7 [ 36 ] ;
real_T P_8 [ 2 ] ; real_T P_9 [ 4 ] ; real_T P_10 [ 2 ] ; real_T P_11 [ 2 ] ;
real_T P_12 [ 2 ] ; real_T P_13 [ 270 ] ; real_T P_14 ; real_T P_15 ; real_T
P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ; real_T P_20 ; real_T P_21 ;
real_T P_22 ; real_T P_23 ; real_T P_24 ; real_T P_25 ; real_T P_26 ; real_T
P_27 ; real_T P_28 ; real_T P_29 ; real_T P_30 ; real_T P_31 ; real_T P_32 ;
real_T P_33 ; real_T P_34 ; real_T P_35 ; real_T P_36 ; real_T P_37 ; real_T
P_38 ; real_T P_39 ; real_T P_40 ; real_T P_41 ; real_T P_42 ; real_T P_43 ;
real_T P_44 ; real_T P_45 ; real_T P_46 ; real_T P_47 ; real_T P_48 ; real_T
P_49 ; real_T P_50 ; real_T P_51 ; real_T P_52 ; real_T P_53 ; } ; extern
P_SigNetLabExp3code_19CS30031_T SigNetLabExp3code_19CS30031_rtDefaultP ;
#endif
