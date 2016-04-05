//
// MATLAB Compiler: 6.0 (R2015a)
// Date: Wed Mar 30 17:12:43 2016
// Arguments: "-B" "macro_default" "-W" "cpplib:AudioScore" "-T" "link:lib"
// "-d" "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Audio
// Score\AudioScore\for_testing" "-v" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Audio Score\audioScoreMain.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Audio
// Score\compute_audio_matching_score.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Audio
// Score\dis2scoreAudio.m" "-a" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Audio Score\enframe.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Audio
// Score\generate_mfccd_feature.m" "-a" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Audio Score\melbankm.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Audio Score\mfcc.m"
// "-a" "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Audio
// Score\vad.m" 
//

#ifndef __AudioScore_h
#define __AudioScore_h 1

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

#ifdef EXPORTING_AudioScore
#define PUBLIC_AudioScore_C_API __global
#else
#define PUBLIC_AudioScore_C_API /* No import statement needed. */
#endif

#define LIB_AudioScore_C_API PUBLIC_AudioScore_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_AudioScore
#define PUBLIC_AudioScore_C_API __declspec(dllexport)
#else
#define PUBLIC_AudioScore_C_API __declspec(dllimport)
#endif

#define LIB_AudioScore_C_API PUBLIC_AudioScore_C_API


#else

#define LIB_AudioScore_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_AudioScore_C_API 
#define LIB_AudioScore_C_API /* No special import/export declaration */
#endif

extern LIB_AudioScore_C_API 
bool MW_CALL_CONV AudioScoreInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_AudioScore_C_API 
bool MW_CALL_CONV AudioScoreInitialize(void);

extern LIB_AudioScore_C_API 
void MW_CALL_CONV AudioScoreTerminate(void);



extern LIB_AudioScore_C_API 
void MW_CALL_CONV AudioScorePrintStackTrace(void);

extern LIB_AudioScore_C_API 
bool MW_CALL_CONV mlxAudioScoreMain(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_AudioScore
#define PUBLIC_AudioScore_CPP_API __declspec(dllexport)
#else
#define PUBLIC_AudioScore_CPP_API __declspec(dllimport)
#endif

#define LIB_AudioScore_CPP_API PUBLIC_AudioScore_CPP_API

#else

#if !defined(LIB_AudioScore_CPP_API)
#if defined(LIB_AudioScore_C_API)
#define LIB_AudioScore_CPP_API LIB_AudioScore_C_API
#else
#define LIB_AudioScore_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_AudioScore_CPP_API void MW_CALL_CONV audioScoreMain(int nargout, mwArray& audioScore, const mwArray& refAudioFile, const mwArray& subAudioFile);

#endif
#endif
