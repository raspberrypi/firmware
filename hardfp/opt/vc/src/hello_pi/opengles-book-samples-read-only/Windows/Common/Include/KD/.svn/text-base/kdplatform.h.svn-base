/* Sample KD/kdplatform.h for OpenKODE Core 1.0 Provisional revision 1 */
#ifndef __kdplatform_h_
#define __kdplatform_h_

#define KD_API
#define KD_APIENTRY

typedef int KDint32;
typedef unsigned int KDuint32;
typedef long long KDint64;
typedef unsigned long long KDuint64;
typedef short KDint16;
typedef unsigned short KDuint16;
typedef unsigned long KDsize;
typedef long KDssize;
#define KDINT_MIN (-0x7fffffff-1)
#define KDINT_MAX 0x7fffffff
#define KDUINT_MAX 0xffffffffU
#define KDINT64_MIN (-0x7fffffffffffffffLL-1)
#define KDINT64_MAX 0x7fffffffffffffffLL
#define KDUINT64_MAX 0xffffffffffffffffULL

/* kdAssert: Test assertion and call assertion handler if it is false */
#ifdef KD_NDEBUG
#define kdAssert(c)
#else
#define kdAssert(c) ((c) || (kdHandleAssertion(#c, __FILE__, __LINE__), 0))
#endif

KD_API float KD_APIENTRY __kdInfinity(void);

#define KD_INFINITY __kdInfinity()

#define KD_WINDOW_SUPPORTED

#if defined(__GNUC__)

#include <stdint.h>
/* GNU C Compiler specific settings */
#define KD_NORETURN __attribute((noreturn))
typedef uintptr_t KDuintptr;

#elif defined(_MSC_VER)

#include <basetsd.h>
/* Microsot Visual C Compiler specific settings*/
#define KD_NORETURN __declspec(noreturn)
typedef UINT_PTR KDuintptr;

#elif defined(__ARMCC_VERSION)

/* ARM Realview compiler specifics */
#define KD_NORETURN __declspec(noreturn)
typedef unsigned long KDuintptr;

#else
#error Cannot detect the compiler used.
#endif

#endif /* __kdplatform_h_ */

