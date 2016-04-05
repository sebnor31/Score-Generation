//
// MATLAB Compiler: 6.0 (R2015a)
// Date: Tue Apr 05 15:00:54 2016
// Arguments: "-B" "macro_default" "-W" "cpplib:VideoScore" "-T" "link:lib"
// "-d" "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Video
// Score\VideoScore\for_testing" "-v" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Video Score\videoScoreMain.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Video
// Score\dis2scoreVideo.m" "-a" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Video Score\dtw_cv.mexw64" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Video
// Score\LBPXY.m" "-a" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Video Score\LBPXY_FEA_Ourdata.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Video
// Score\matching_video_prob.m" "-a" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Video Score\simple_video_input_rawpixel.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Video
// Score\libsvm-3.18\matlab\svmpredict.mexw64" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Video
// Score\VideoStateSequenceProb.m" 
//

#ifndef __VideoScore_h
#define __VideoScore_h 1

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

#ifdef EXPORTING_VideoScore
#define PUBLIC_VideoScore_C_API __global
#else
#define PUBLIC_VideoScore_C_API /* No import statement needed. */
#endif

#define LIB_VideoScore_C_API PUBLIC_VideoScore_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_VideoScore
#define PUBLIC_VideoScore_C_API __declspec(dllexport)
#else
#define PUBLIC_VideoScore_C_API __declspec(dllimport)
#endif

#define LIB_VideoScore_C_API PUBLIC_VideoScore_C_API


#else

#define LIB_VideoScore_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_VideoScore_C_API 
#define LIB_VideoScore_C_API /* No special import/export declaration */
#endif

extern LIB_VideoScore_C_API 
bool MW_CALL_CONV VideoScoreInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_VideoScore_C_API 
bool MW_CALL_CONV VideoScoreInitialize(void);

extern LIB_VideoScore_C_API 
void MW_CALL_CONV VideoScoreTerminate(void);



extern LIB_VideoScore_C_API 
void MW_CALL_CONV VideoScorePrintStackTrace(void);

extern LIB_VideoScore_C_API 
bool MW_CALL_CONV mlxVideoScoreMain(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_VideoScore
#define PUBLIC_VideoScore_CPP_API __declspec(dllexport)
#else
#define PUBLIC_VideoScore_CPP_API __declspec(dllimport)
#endif

#define LIB_VideoScore_CPP_API PUBLIC_VideoScore_CPP_API

#else

#if !defined(LIB_VideoScore_CPP_API)
#if defined(LIB_VideoScore_C_API)
#define LIB_VideoScore_CPP_API LIB_VideoScore_C_API
#else
#define LIB_VideoScore_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_VideoScore_CPP_API void MW_CALL_CONV videoScoreMain(int nargout, mwArray& videoScore, const mwArray& trainedModelFile, const mwArray& UniformLBP8File, const mwArray& refVideoFile, const mwArray& subVideoFile);

#endif
#endif
