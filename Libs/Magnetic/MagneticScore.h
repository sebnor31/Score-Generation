//
// MATLAB Compiler: 6.0 (R2015a)
// Date: Fri Apr 01 12:08:13 2016
// Arguments: "-B" "macro_default" "-W" "cpplib:MagneticScore" "-T" "link:lib"
// "-d" "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Magnetic
// Score\MagneticScore\for_testing" "-v" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Magnetic Score\magneticScoreMain.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Magnetic
// Score\biorwin.m" "-a" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Magnetic Score\dis2scoreMag.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Magnetic
// Score\dtw_c.mexw64" "-a" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Magnetic Score\enframe.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Magnetic
// Score\GenerateSpectrum.m" "-a" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Magnetic Score\matching_mag.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Magnetic
// Score\multi_word_segment_mag.m" "-a" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Magnetic Score\normalise.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Magnetic
// Score\normzeromean.m" "-a" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Magnetic Score\SensorFeatureExtraction.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Magnetic
// Score\shiftcir.m" "-a" "C:\Users\nsebkhi3\GitHub\GT-Bionics
// TTS\Visual_Feedback\Magnetic Score\stft.m" "-a"
// "C:\Users\nsebkhi3\GitHub\GT-Bionics TTS\Visual_Feedback\Magnetic
// Score\vadmultiple_mag.m" 
//

#ifndef __MagneticScore_h
#define __MagneticScore_h 1

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

#ifdef EXPORTING_MagneticScore
#define PUBLIC_MagneticScore_C_API __global
#else
#define PUBLIC_MagneticScore_C_API /* No import statement needed. */
#endif

#define LIB_MagneticScore_C_API PUBLIC_MagneticScore_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_MagneticScore
#define PUBLIC_MagneticScore_C_API __declspec(dllexport)
#else
#define PUBLIC_MagneticScore_C_API __declspec(dllimport)
#endif

#define LIB_MagneticScore_C_API PUBLIC_MagneticScore_C_API


#else

#define LIB_MagneticScore_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_MagneticScore_C_API 
#define LIB_MagneticScore_C_API /* No special import/export declaration */
#endif

extern LIB_MagneticScore_C_API 
bool MW_CALL_CONV MagneticScoreInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_MagneticScore_C_API 
bool MW_CALL_CONV MagneticScoreInitialize(void);

extern LIB_MagneticScore_C_API 
void MW_CALL_CONV MagneticScoreTerminate(void);



extern LIB_MagneticScore_C_API 
void MW_CALL_CONV MagneticScorePrintStackTrace(void);

extern LIB_MagneticScore_C_API 
bool MW_CALL_CONV mlxMagneticScoreMain(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_MagneticScore
#define PUBLIC_MagneticScore_CPP_API __declspec(dllexport)
#else
#define PUBLIC_MagneticScore_CPP_API __declspec(dllimport)
#endif

#define LIB_MagneticScore_CPP_API PUBLIC_MagneticScore_CPP_API

#else

#if !defined(LIB_MagneticScore_CPP_API)
#if defined(LIB_MagneticScore_C_API)
#define LIB_MagneticScore_CPP_API LIB_MagneticScore_C_API
#else
#define LIB_MagneticScore_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_MagneticScore_CPP_API void MW_CALL_CONV magneticScoreMain(int nargout, mwArray& magScore, const mwArray& refMagFile, const mwArray& subMagFile, const mwArray& refAudioFile, const mwArray& subAudioFile);

#endif
#endif
