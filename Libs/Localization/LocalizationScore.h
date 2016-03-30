//
// MATLAB Compiler: 6.0 (R2015a)
// Date: Tue Mar 29 16:39:36 2016
// Arguments: "-B" "macro_default" "-W" "cpplib:LocalizationScore" "-T"
// "link:lib" "-d" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Localization Score\LocalizationScore\for_testing" "-v"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Localization
// Score\locaScoreMain.m" 
//

#ifndef __LocalizationScore_h
#define __LocalizationScore_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_LocalizationScore
#define PUBLIC_LocalizationScore_C_API __global
#else
#define PUBLIC_LocalizationScore_C_API /* No import statement needed. */
#endif

#define LIB_LocalizationScore_C_API PUBLIC_LocalizationScore_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_LocalizationScore
#define PUBLIC_LocalizationScore_C_API __declspec(dllexport)
#else
#define PUBLIC_LocalizationScore_C_API __declspec(dllimport)
#endif

#define LIB_LocalizationScore_C_API PUBLIC_LocalizationScore_C_API


#else

#define LIB_LocalizationScore_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_LocalizationScore_C_API 
#define LIB_LocalizationScore_C_API /* No special import/export declaration */
#endif

extern LIB_LocalizationScore_C_API 
bool MW_CALL_CONV LocalizationScoreInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_LocalizationScore_C_API 
bool MW_CALL_CONV LocalizationScoreInitialize(void);

extern LIB_LocalizationScore_C_API 
void MW_CALL_CONV LocalizationScoreTerminate(void);



extern LIB_LocalizationScore_C_API 
void MW_CALL_CONV LocalizationScorePrintStackTrace(void);

extern LIB_LocalizationScore_C_API 
bool MW_CALL_CONV mlxLocaScoreMain(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_LocalizationScore
#define PUBLIC_LocalizationScore_CPP_API __declspec(dllexport)
#else
#define PUBLIC_LocalizationScore_CPP_API __declspec(dllimport)
#endif

#define LIB_LocalizationScore_CPP_API PUBLIC_LocalizationScore_CPP_API

#else

#if !defined(LIB_LocalizationScore_CPP_API)
#if defined(LIB_LocalizationScore_C_API)
#define LIB_LocalizationScore_CPP_API LIB_LocalizationScore_C_API
#else
#define LIB_LocalizationScore_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_LocalizationScore_CPP_API void MW_CALL_CONV locaScoreMain(int nargout, mwArray& locaScore, const mwArray& refTrajFile, const mwArray& subTrajFile, const mwArray& refAudioFile, const mwArray& subAudioFile);

#endif
#endif
