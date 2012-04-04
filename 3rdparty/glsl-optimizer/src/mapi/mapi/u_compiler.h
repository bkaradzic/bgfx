#ifndef _U_COMPILER_H_
#define _U_COMPILER_H_

/* Function inlining */
#ifndef INLINE
#  ifdef __cplusplus
#    define INLINE inline
#  elif defined(__GNUC__)
#    define INLINE __inline__
#  elif defined(_MSC_VER)
#    define INLINE __inline
#  elif defined(__ICL)
#    define INLINE __inline
#  elif defined(__INTEL_COMPILER)
#    define INLINE inline
#  elif defined(__WATCOMC__) && (__WATCOMC__ >= 1100)
#    define INLINE __inline
#  elif defined(__SUNPRO_C) && defined(__C99FEATURES__)
#    define INLINE inline
#  elif (__STDC_VERSION__ >= 199901L) /* C99 */
#    define INLINE inline
#  else
#    define INLINE
#  endif
#endif

/* Function visibility */
#ifndef PUBLIC
#  if defined(__GNUC__) || (defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590))
#    define PUBLIC __attribute__((visibility("default")))
#  elif defined(_MSC_VER)
#    define PUBLIC __declspec(dllexport)
#  else
#    define PUBLIC
#  endif
#endif

#ifndef likely
#  if defined(__GNUC__)
#    define likely(x)   __builtin_expect(!!(x), 1)
#    define unlikely(x) __builtin_expect(!!(x), 0)
#  else
#    define likely(x)   (x)
#    define unlikely(x) (x)
#  endif
#endif

#endif /* _U_COMPILER_H_ */
