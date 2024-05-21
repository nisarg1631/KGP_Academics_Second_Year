#include <math.h>
#include "SigNetLabExp3code_19CS30031_acc.h"
#include "SigNetLabExp3code_19CS30031_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T SigNetLabExp3code_19CS30031_acc_rt_TDelayUpdateTailOrGrowBuf (
int_T * bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr ,
real_T tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * *
xBufPtr , boolean_T isfixedbuf , boolean_T istransportdelay , int_T *
maxNewBufSzPtr ) { int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = *
bufSzPtr ; real_T * tBuf = * tBufPtr ; real_T * xBuf = ( NULL ) ; int_T
numBuffer = 2 ; if ( istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ;
} testIdx = ( tail < ( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay
<= tBuf [ testIdx ] ) && ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T *
tempU ; real_T * tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T
newBufSz = bufSz + 1024 ; if ( newBufSz > * maxNewBufSzPtr ) { *
maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * ) utMalloc ( numBuffer *
newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL ) ) { return ( false )
; } tempT = tempU + newBufSz ; if ( istransportdelay ) tempX = tempT +
newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j - tail ] = tBuf [
j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j -
tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT [ j + bufSz -
tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ; if (
istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( * lastPtr
> tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail ) ; } *
tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr = newBufSz ; *
tBufPtr = tempT ; * uBufPtr = tempU ; if ( istransportdelay ) * xBufPtr =
tempX ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
SigNetLabExp3code_19CS30031_acc_rt_TDelayInterpolate ( real_T tMinusDelay ,
real_T tStart , real_T * tBuf , real_T * uBuf , int_T bufSz , int_T * lastIdx
, int_T oldestIdx , int_T newIdx , real_T initOutput , boolean_T discrete ,
boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout , t1 , t2
, u1 , u2 ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 ) && ( tMinusDelay >
tStart ) ) return initOutput ; if ( tMinusDelay <= tStart ) return initOutput
; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if ( discrete ) { return (
uBuf [ oldestIdx ] ) ; } else { int_T tempIdx = oldestIdx + 1 ; if (
oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [ oldestIdx ] ; t2 = tBuf [
tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [ tempIdx ] ; if ( t2 == t1 )
{ if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } return yout ; } } if ( minorStepAndTAtLastMajorOutput
) { if ( newIdx != 0 ) { if ( * lastIdx == newIdx ) { ( * lastIdx ) -- ; }
newIdx -- ; } else { if ( * lastIdx == newIdx ) { * lastIdx = bufSz - 1 ; }
newIdx = bufSz - 1 ; } } i = * lastIdx ; if ( tBuf [ i ] < tMinusDelay ) {
while ( tBuf [ i ] < tMinusDelay ) { if ( i == newIdx ) break ; i = ( i < (
bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while ( tBuf [ i ] >= tMinusDelay
) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i = ( i < ( bufSz - 1 ) ) ? ( i
+ 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) { double tempEps = (
DBL_EPSILON ) * 128.0 ; double localEps = tempEps * muDoubleScalarAbs ( tBuf
[ i ] ) ; if ( tempEps > localEps ) { localEps = tempEps ; } localEps =
localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] - localEps ) ) { yout =
uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [ bufSz - 1 ] ; } else {
yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) { t1 = tBuf [ bufSz - 1 ]
; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i - 1 ] ; u1 = uBuf [ i - 1
] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 == t1 ) { if ( tMinusDelay
>= t2 ) { yout = u2 ; } else { yout = u1 ; } } else { real_T f1 = ( t2 -
tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2
; } } return ( yout ) ; } void rt_ssGetBlockPath ( SimStruct * S , int_T
sysIdx , int_T blkIdx , char_T * * path ) { _ssGetBlockPath ( S , sysIdx ,
blkIdx , path ) ; } void rt_ssSet_slErrMsg ( SimStruct * S , void * diag ) {
if ( ! _ssIsErrorStatusAslErrMsg ( S ) ) { _ssSet_slErrMsg ( S , diag ) ; }
else { _ssDiscardDiagnostic ( S , diag ) ; } } void
rt_ssReportDiagnosticAsWarning ( SimStruct * S , void * diag ) {
_ssReportDiagnosticAsWarning ( S , diag ) ; } static void mdlOutputs (
SimStruct * S , int_T tid ) { real_T B_4_3_0 ; real_T B_4_11_0 ; real_T
B_4_21_0 ; real_T B_4_29_0 ; boolean_T rtb_B_4_6_0 ; real_T
rtb_RealImagtoComplex_re ; real_T rtb_RealImagtoComplex_im ; real_T
rtb_RealImagtoComplex_re_a ; real_T rtb_RealImagtoComplex_im_a ; int32_T
isHit ; B_SigNetLabExp3code_19CS30031_T * _rtB ;
P_SigNetLabExp3code_19CS30031_T * _rtP ; X_SigNetLabExp3code_19CS30031_T *
_rtX ; DW_SigNetLabExp3code_19CS30031_T * _rtDW ; _rtDW = ( (
DW_SigNetLabExp3code_19CS30031_T * ) ssGetRootDWork ( S ) ) ; _rtX = ( (
X_SigNetLabExp3code_19CS30031_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_SigNetLabExp3code_19CS30031_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_SigNetLabExp3code_19CS30031_T * ) _ssGetModelBlockIO ( S ) ) ;
rtb_RealImagtoComplex_re = _rtP -> P_5 * ssGetT ( S ) ; if (
rtb_RealImagtoComplex_re - muDoubleScalarFloor ( rtb_RealImagtoComplex_re )
>= 0.5 ) { _rtB -> B_4_0_0 = _rtP -> P_4 ; } else { _rtB -> B_4_0_0 = - _rtP
-> P_4 ; } ssCallAccelRunBlock ( S , 4 , 1 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_4_2_0 = _rtX -> integrator_CSTATE ; { real_T * * uBuffer = ( real_T * * ) &
_rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_15 ;
B_4_3_0 = SigNetLabExp3code_19CS30031_acc_rt_TDelayInterpolate ( tMinusDelay
, 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK .
CircularBufSize , & _rtDW -> TransportDelay_IWORK . Last , _rtDW ->
TransportDelay_IWORK . Tail , _rtDW -> TransportDelay_IWORK . Head , _rtP ->
P_16 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput
( S ) == ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_4_5_0 = _rtP -> P_17 ; } rtb_B_4_6_0 = ( ssGetT ( S
) >= _rtB -> B_4_5_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit !=
0 ) { _rtB -> B_4_7_0 = _rtDW -> Memory_PreviousInput ; } if ( rtb_B_4_6_0 )
{ _rtB -> B_4_9_0 = ( _rtB -> B_4_2_0 - B_4_3_0 ) * _rtP -> P_3 ; } else {
_rtB -> B_4_9_0 = _rtB -> B_4_7_0 ; } _rtB -> B_4_10_0 = _rtX ->
integrator_CSTATE_l ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_20 ; B_4_11_0 =
SigNetLabExp3code_19CS30031_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_d . CircularBufSize , &
_rtDW -> TransportDelay_IWORK_d . Last , _rtDW -> TransportDelay_IWORK_d .
Tail , _rtDW -> TransportDelay_IWORK_d . Head , _rtP -> P_21 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { _rtB -> B_4_13_0 = _rtP -> P_22 ; } rtb_B_4_6_0 = ( ssGetT ( S ) >= _rtB
-> B_4_13_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_4_15_0 = _rtDW -> Memory_PreviousInput_m ; } if ( rtb_B_4_6_0 ) {
_rtB -> B_4_17_0 = ( _rtB -> B_4_10_0 - B_4_11_0 ) * _rtP -> P_2 ; } else {
_rtB -> B_4_17_0 = _rtB -> B_4_15_0 ; } rtb_RealImagtoComplex_re = _rtB ->
B_4_9_0 ; rtb_RealImagtoComplex_im = _rtB -> B_4_17_0 ; _rtB -> B_4_20_0 =
_rtX -> integrator_CSTATE_ls ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay_PWORK_e . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK_e . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_25 ;
B_4_21_0 = SigNetLabExp3code_19CS30031_acc_rt_TDelayInterpolate ( tMinusDelay
, 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_f .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_f . Last , _rtDW ->
TransportDelay_IWORK_f . Tail , _rtDW -> TransportDelay_IWORK_f . Head , _rtP
-> P_26 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_4_23_0 = _rtP -> P_27 ; }
rtb_B_4_6_0 = ( ssGetT ( S ) >= _rtB -> B_4_23_0 ) ; isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_4_25_0 = _rtDW ->
Memory_PreviousInput_a ; } if ( rtb_B_4_6_0 ) { _rtB -> B_4_27_0 = ( _rtB ->
B_4_20_0 - B_4_21_0 ) * _rtP -> P_1 ; } else { _rtB -> B_4_27_0 = _rtB ->
B_4_25_0 ; } _rtB -> B_4_28_0 = _rtX -> integrator_CSTATE_m ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_n . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_n .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_30 ; B_4_29_0 =
SigNetLabExp3code_19CS30031_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_m . CircularBufSize , &
_rtDW -> TransportDelay_IWORK_m . Last , _rtDW -> TransportDelay_IWORK_m .
Tail , _rtDW -> TransportDelay_IWORK_m . Head , _rtP -> P_31 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { _rtB -> B_4_31_0 = _rtP -> P_32 ; } rtb_B_4_6_0 = ( ssGetT ( S ) >= _rtB
-> B_4_31_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_4_33_0 = _rtDW -> Memory_PreviousInput_p ; } if ( rtb_B_4_6_0 ) {
_rtB -> B_4_35_0 = ( _rtB -> B_4_28_0 - B_4_29_0 ) * _rtP -> P_0 ; } else {
_rtB -> B_4_35_0 = _rtB -> B_4_33_0 ; } rtb_RealImagtoComplex_re_a = _rtB ->
B_4_27_0 ; rtb_RealImagtoComplex_im_a = _rtB -> B_4_35_0 ; _rtB -> B_4_38_0 =
muDoubleScalarHypot ( rtb_RealImagtoComplex_re , rtb_RealImagtoComplex_im ) /
muDoubleScalarHypot ( _rtB -> B_4_27_0 , _rtB -> B_4_35_0 ) ;
ssCallAccelRunBlock ( S , 4 , 39 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_4_42_0 =
_rtP -> P_34 * muDoubleScalarAtan2 ( rtb_RealImagtoComplex_im ,
rtb_RealImagtoComplex_re ) - _rtP -> P_35 * muDoubleScalarAtan2 (
rtb_RealImagtoComplex_im_a , rtb_RealImagtoComplex_re_a ) ;
ssCallAccelRunBlock ( S , 4 , 43 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_4_44_0 =
_rtP -> P_36 * _rtB -> B_4_1_0 [ 1 ] ; ssCallAccelRunBlock ( S , 4 , 45 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_4_46_0 = _rtP -> P_37 * _rtB -> B_4_1_0 [ 0
] ; ssCallAccelRunBlock ( S , 4 , 47 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_4_49_0 = ( muDoubleScalarSin ( _rtP -> P_40 * ssGetTaskTime ( S , 0 ) +
_rtP -> P_41 ) * _rtP -> P_38 + _rtP -> P_39 ) * _rtB -> B_4_44_0 ; _rtB ->
B_4_51_0 = ( muDoubleScalarSin ( _rtP -> P_44 * ssGetTaskTime ( S , 0 ) +
_rtP -> P_45 ) * _rtP -> P_42 + _rtP -> P_43 ) * _rtB -> B_4_44_0 ; _rtB ->
B_4_53_0 = ( muDoubleScalarSin ( _rtP -> P_48 * ssGetTaskTime ( S , 0 ) +
_rtP -> P_49 ) * _rtP -> P_46 + _rtP -> P_47 ) * _rtB -> B_4_46_0 ; _rtB ->
B_4_55_0 = ( muDoubleScalarSin ( _rtP -> P_52 * ssGetTaskTime ( S , 0 ) +
_rtP -> P_53 ) * _rtP -> P_50 + _rtP -> P_51 ) * _rtB -> B_4_46_0 ;
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { int32_T isHit ;
B_SigNetLabExp3code_19CS30031_T * _rtB ; P_SigNetLabExp3code_19CS30031_T *
_rtP ; DW_SigNetLabExp3code_19CS30031_T * _rtDW ; _rtDW = ( (
DW_SigNetLabExp3code_19CS30031_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( (
P_SigNetLabExp3code_19CS30031_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_SigNetLabExp3code_19CS30031_T * ) _ssGetModelBlockIO ( S ) ) ;
ssCallAccelRunBlock ( S , 4 , 1 , SS_CALL_MDL_UPDATE ) ; { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK . Head = ( ( _rtDW -> TransportDelay_IWORK . Head < (
_rtDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK
. Head == _rtDW -> TransportDelay_IWORK . Tail ) { if ( !
SigNetLabExp3code_19CS30031_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_15 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_4_2_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW
-> Memory_PreviousInput = _rtB -> B_4_9_0 ; } { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_m . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_d . Head =
( ( _rtDW -> TransportDelay_IWORK_d . Head < ( _rtDW ->
TransportDelay_IWORK_d . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_d . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_d . Head == _rtDW -> TransportDelay_IWORK_d . Tail ) {
if ( ! SigNetLabExp3code_19CS30031_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK_d . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_d . Tail , & _rtDW -> TransportDelay_IWORK_d . Head , &
_rtDW -> TransportDelay_IWORK_d . Last , simTime - _rtP -> P_20 , tBuffer ,
uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_d . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_d . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_d . Head ] = _rtB -> B_4_10_0 ; } isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput_m = _rtB ->
B_4_17_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_e . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_e . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_f . Head = ( ( _rtDW ->
TransportDelay_IWORK_f . Head < ( _rtDW -> TransportDelay_IWORK_f .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_f . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_f . Head == _rtDW ->
TransportDelay_IWORK_f . Tail ) { if ( !
SigNetLabExp3code_19CS30031_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_f . CircularBufSize , & _rtDW -> TransportDelay_IWORK_f
. Tail , & _rtDW -> TransportDelay_IWORK_f . Head , & _rtDW ->
TransportDelay_IWORK_f . Last , simTime - _rtP -> P_25 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_f .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_f . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_f . Head ] = _rtB ->
B_4_20_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW
-> Memory_PreviousInput_a = _rtB -> B_4_27_0 ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK_n . TUbufferPtrs [ 0 ] ; real_T
* * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_n . TUbufferPtrs
[ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_m .
Head = ( ( _rtDW -> TransportDelay_IWORK_m . Head < ( _rtDW ->
TransportDelay_IWORK_m . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_m . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_m . Head == _rtDW -> TransportDelay_IWORK_m . Tail ) {
if ( ! SigNetLabExp3code_19CS30031_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK_m . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_m . Tail , & _rtDW -> TransportDelay_IWORK_m . Head , &
_rtDW -> TransportDelay_IWORK_m . Last , simTime - _rtP -> P_30 , tBuffer ,
uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_m . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_m . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_m . Head ] = _rtB -> B_4_28_0 ; } isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput_p = _rtB ->
B_4_35_0 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) {
B_SigNetLabExp3code_19CS30031_T * _rtB ; P_SigNetLabExp3code_19CS30031_T *
_rtP ; XDot_SigNetLabExp3code_19CS30031_T * _rtXdot ;
DW_SigNetLabExp3code_19CS30031_T * _rtDW ; _rtDW = ( (
DW_SigNetLabExp3code_19CS30031_T * ) ssGetRootDWork ( S ) ) ; _rtXdot = ( (
XDot_SigNetLabExp3code_19CS30031_T * ) ssGetdX ( S ) ) ; _rtP = ( (
P_SigNetLabExp3code_19CS30031_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_SigNetLabExp3code_19CS30031_T * ) _ssGetModelBlockIO ( S ) ) ;
ssCallAccelRunBlock ( S , 4 , 1 , SS_CALL_MDL_DERIVATIVES ) ; _rtXdot ->
integrator_CSTATE = _rtB -> B_4_53_0 ; _rtXdot -> integrator_CSTATE_l = _rtB
-> B_4_55_0 ; _rtXdot -> integrator_CSTATE_ls = _rtB -> B_4_49_0 ; _rtXdot ->
integrator_CSTATE_m = _rtB -> B_4_51_0 ; }
#define MDL_PROJECTION
static void mdlProjection ( SimStruct * S ) { B_SigNetLabExp3code_19CS30031_T
* _rtB ; P_SigNetLabExp3code_19CS30031_T * _rtP ;
DW_SigNetLabExp3code_19CS30031_T * _rtDW ; _rtDW = ( (
DW_SigNetLabExp3code_19CS30031_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( (
P_SigNetLabExp3code_19CS30031_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_SigNetLabExp3code_19CS30031_T * ) _ssGetModelBlockIO ( S ) ) ;
ssCallAccelRunBlock ( S , 4 , 1 , SS_CALL_MDL_PROJECTION ) ; } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 2436097753U
) ; ssSetChecksumVal ( S , 1 , 1419125163U ) ; ssSetChecksumVal ( S , 2 ,
4059903442U ) ; ssSetChecksumVal ( S , 3 , 3844819683U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "10.1" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_SigNetLabExp3code_19CS30031_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_SigNetLabExp3code_19CS30031_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_SigNetLabExp3code_19CS30031_T ) ) { static char msg [ 256 ] ; sprintf ( msg
, "Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & SigNetLabExp3code_19CS30031_rtDefaultP ) ; rt_InitInfAndNaN ( sizeof (
real_T ) ) ; } static void mdlInitializeSampleTimes ( SimStruct * S ) { }
static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
