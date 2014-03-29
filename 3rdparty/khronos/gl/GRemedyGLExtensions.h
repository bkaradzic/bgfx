// ------------------------------ GRemdeyGLExtensions.h ------------------------------

// -----------------------------------------------------------------
//   © 2004 - 2012 Advanced Micro Devices, Inc. All rights reserved.
// -----------------------------------------------------------------

#ifndef __GREMDEYGLEXTENSIONS
#define __GREMDEYGLEXTENSIONS


#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#ifndef GLAPI
#define GLAPI extern
#endif

#ifdef __cplusplus
extern "C"
{
#endif

        /* ----------------------- GL_GREMEDY_string_marker ----------------------- */
        
#ifndef GL_GREMEDY_string_marker
#define GL_GREMEDY_string_marker 1
        
#ifdef GL_GLEXT_PROTOTYPES
        GLAPI void APIENTRY glStringMarkerGREMEDY(GLsizei len, const GLvoid *string);
#endif /* GL_GLEXT_PROTOTYPES */
        
        typedef void (APIENTRYP PFNGLSTRINGMARKERGREMEDYPROC)(GLsizei len, const GLvoid *string);
        
#endif /* GL_GREMEDY_string_marker */
        
        
        
        /* ----------------------- GL_GREMEDY_frame_terminator ----------------------- */
        
#ifndef GL_GREMEDY_frame_terminator
#define GL_GREMEDY_frame_terminator 1
        
#ifdef GL_GLEXT_PROTOTYPES
        GLAPI void APIENTRY glFrameTerminatorGREMEDY(void);
#endif /* GL_GLEXT_PROTOTYPES */
        
        typedef void (APIENTRYP PFNGLFRAMETERMINATORGREMEDYPROC)(void);
        
#endif /* GL_GREMEDY_frame_terminator */
        
        
#ifdef __cplusplus
}
#endif


#endif  /* __GREMDEYGLEXTENSIONS */
