/* Reference KD/kd.h for OpenKODE Core 1.0 Final candidate (draft 5124) */
#ifndef __kd_h_
#define __kd_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "kdplatform.h"



/*******************************************************
 * Introduction
 *******************************************************/

/*******************************************************
 * OpenKODE conformance
 *******************************************************/

/*******************************************************
 * Overview
 *******************************************************/

/*******************************************************
 * Programming environment
 *******************************************************/
#define KD_VERSION_1_0 1
typedef char KDchar;
typedef signed char KDint8;
typedef unsigned char KDuint8;
typedef int KDint;
typedef unsigned int KDuint;
typedef float KDfloat32;
typedef KDint KDboolean;
typedef KDint64 KDtime;
typedef KDint64 KDust;
typedef KDint64 KDoff;
typedef KDuint32 KDmode;
#define KDINT32_MIN (-0x7fffffff-1)
#define KDINT32_MAX 0x7fffffff
#define KDUINT32_MAX 0xffffffffU
#define KD_TRUE 1
#define KD_FALSE 0
#ifdef __cplusplus
  const int KD_NULL = 0; /* Yes, int. See Stroustrup 3rd edition. */
#else
  #define KD_NULL ((void *)0)
#endif

/*******************************************************
 * Errors
 *******************************************************/
#define KD_EACCES 1
#define KD_EADDRINUSE 2
#define KD_EADDRNOTAVAIL 3
#define KD_EAFNOSUPPORT 4
#define KD_EAGAIN (5)
#define KD_EALREADY 6
#define KD_EBADF 7
#define KD_EBUSY 8
#define KD_ECONNREFUSED 9
#define KD_ECONNRESET 10
#define KD_EDEADLK 11
#define KD_EDESTADDRREQ 12
#define KD_EEXIST 13
#define KD_EFBIG 14
#define KD_EHOSTUNREACH 15
#define KD_EHOST_NOT_FOUND 16
#define KD_EINVAL 17
#define KD_EIO 18
#define KD_EILSEQ 19
#define KD_EISCONN 20
#define KD_EISDIR 21
#define KD_EMFILE 22
#define KD_ENAMETOOLONG 23
#define KD_ENOENT 24
#define KD_ENOMEM 25
#define KD_ENOSPC 26
#define KD_ENOSYS 27
#define KD_ENOTCONN 28
#define KD_ENO_DATA 29
#define KD_ENO_RECOVERY 30
#define KD_EOPNOTSUPP 31
#define KD_EOVERFLOW 32
#define KD_EPERM 33
#define KD_EPIPE 34
#define KD_ERANGE 35
#define KD_ETIMEDOUT (36)
#define KD_ETRY_AGAIN 37

/* kdGetError: Get last error indication. */
KD_API KDint KD_APIENTRY kdGetError(void);

/* kdSetError: Set last error indication. */
KD_API void KD_APIENTRY kdSetError(KDint error);

/*******************************************************
 * Versioning and attribute queries
 *******************************************************/

/* kdQueryAttribi: Obtain the value of a numeric OpenKODE Core attribute. */
KD_API KDint KD_APIENTRY kdQueryAttribi(KDint attribute, KDint *value);

/* kdQueryAttribcv: Obtain the value of a string OpenKODE Core attribute. */
KD_API const KDchar *KD_APIENTRY kdQueryAttribcv(KDint attribute);
#define KD_ATTRIB_VENDOR 39
#define KD_ATTRIB_VERSION 40
#define KD_ATTRIB_PLATFORM 41

/* kdQueryIndexedAttribcv: Obtain the value of an indexed string OpenKODE Core attribute. */
KD_API const KDchar *KD_APIENTRY kdQueryIndexedAttribcv(KDint attribute, KDint index);

/*******************************************************
 * Threads and synchronization
 *******************************************************/

/* kdThreadAttrCreate: Create a thread attribute object. */
typedef struct KDThreadAttr KDThreadAttr;
KD_API KDThreadAttr *KD_APIENTRY kdThreadAttrCreate(void);

/* kdThreadAttrFree: Free a thread attribute object. */
KD_API KDint KD_APIENTRY kdThreadAttrFree(KDThreadAttr *attr);

/* kdThreadAttrSetDetachState: Set detachstate attribute. */
#define KD_THREAD_CREATE_JOINABLE 0
#define KD_THREAD_CREATE_DETACHED 1
KD_API KDint KD_APIENTRY kdThreadAttrSetDetachState(KDThreadAttr *attr, KDint detachstate);

/* kdThreadAttrSetStackSize: Set stacksize attribute. */
KD_API KDint KD_APIENTRY kdThreadAttrSetStackSize(KDThreadAttr *attr, KDsize stacksize);

/* kdThreadCreate: Create a new thread. */
typedef struct KDThread KDThread;
KD_API KDThread *KD_APIENTRY kdThreadCreate(const KDThreadAttr *attr, void *(*start_routine)(void *), void *arg);

/* kdThreadExit: Terminate this thread. */
KD_API KD_NORETURN void KD_APIENTRY kdThreadExit(void *retval);

/* kdThreadJoin: Wait for termination of another thread. */
KD_API KDint KD_APIENTRY kdThreadJoin(KDThread *thread, void **retval);

/* kdThreadDetach: Allow resources to be freed as soon as a thread terminates. */
KD_API KDint KD_APIENTRY kdThreadDetach(KDThread *thread);

/* kdThreadSelf: Return calling thread&#8217;s ID. */
KD_API KDThread *KD_APIENTRY kdThreadSelf(void);

/* kdThreadOnce: Wrap initialization code so it is executed only once. */
#ifndef KD_NO_STATIC_DATA
typedef struct KDThreadOnce {
    void *impl;
} KDThreadOnce;
#define KD_THREAD_ONCE_INIT { 0 }
KD_API KDint KD_APIENTRY kdThreadOnce(KDThreadOnce *once_control, void (*init_routine)(void));
#endif /* ndef KD_NO_STATIC_DATA */

/* kdThreadMutexCreate: Create a mutex. */
typedef struct KDThreadMutex KDThreadMutex;
KD_API KDThreadMutex *KD_APIENTRY kdThreadMutexCreate(const void *mutexattr);

/* kdThreadMutexFree: Free a mutex. */
KD_API KDint KD_APIENTRY kdThreadMutexFree(KDThreadMutex *mutex);

/* kdThreadMutexLock: Lock a mutex. */
KD_API KDint KD_APIENTRY kdThreadMutexLock(KDThreadMutex *mutex);

/* kdThreadMutexUnlock: Unlock a mutex. */
KD_API KDint KD_APIENTRY kdThreadMutexUnlock(KDThreadMutex *mutex);

/* kdThreadCondCreate: Create a condition variable. */
typedef struct KDThreadCond KDThreadCond;
KD_API KDThreadCond *KD_APIENTRY kdThreadCondCreate(const void *attr);

/* kdThreadCondFree: Free a condition variable. */
KD_API KDint KD_APIENTRY kdThreadCondFree(KDThreadCond *cond);

/* kdThreadCondSignal, kdThreadCondBroadcast: Signal a condition variable. */
KD_API KDint KD_APIENTRY kdThreadCondSignal(KDThreadCond *cond);
KD_API KDint KD_APIENTRY kdThreadCondBroadcast(KDThreadCond *cond);

/* kdThreadCondWait: Wait for a condition variable to be signalled. */
KD_API KDint KD_APIENTRY kdThreadCondWait(KDThreadCond *cond, KDThreadMutex *mutex);

/* kdThreadSemCreate: Create a semaphore. */
typedef struct KDThreadSem KDThreadSem;
KD_API KDThreadSem *KD_APIENTRY kdThreadSemCreate(KDuint value);

/* kdThreadSemFree: Free a semaphore. */
KD_API KDint KD_APIENTRY kdThreadSemFree(KDThreadSem *sem);

/* kdThreadSemWait: Lock a semaphore. */
KD_API KDint KD_APIENTRY kdThreadSemWait(KDThreadSem *sem);

/* kdThreadSemPost: Unlock a semaphore. */
KD_API KDint KD_APIENTRY kdThreadSemPost(KDThreadSem *sem);

/*******************************************************
 * Events
 *******************************************************/

/* KDEvent: Struct type containing an event. */
typedef struct KDEvent KDEvent;
#define KD_EVENT_USER 0x40000000

/* kdWaitEvent: Get next event from thread&#8217;s event queue. */
KD_API const KDEvent *KD_APIENTRY kdWaitEvent(KDust timeout);

/* kdSetEventUserptr: Set the userptr for global events. */
KD_API void KD_APIENTRY kdSetEventUserptr(void *userptr);

/* kdDefaultEvent: Perform default processing on an unrecognized event. */
KD_API void KD_APIENTRY kdDefaultEvent(const KDEvent *event);

/* kdPumpEvents: Pump the thread&#8217;s event queue, performing callbacks. */
KD_API KDint KD_APIENTRY kdPumpEvents(void);

/* kdInstallCallback: Install or remove a callback function for event processing. */
typedef void (KD_APIENTRY KDCallbackFunc)(const KDEvent *event);
KD_API KDint KD_APIENTRY kdInstallCallback(KDCallbackFunc *func, KDint eventtype, void *eventuserptr);

/* kdCreateEvent: Create an event for posting. */
KD_API KDEvent *KD_APIENTRY kdCreateEvent(void);

/* kdPostEvent, kdPostThreadEvent: Post an event into a queue. */
KD_API KDint KD_APIENTRY kdPostEvent(KDEvent *event);
KD_API KDint KD_APIENTRY kdPostThreadEvent(KDEvent *event, KDThread *thread);
typedef struct KDEventUser {
    union {
        KDint64 i64;
        void *p;
        struct {
            KDint32 a;
            KDint32 b;
        } i32pair;
    } value1;
    union {
        KDint64 i64;
        struct {
            union {
                KDint32 i32;
                void *p;
            } value2;
            union {
                KDint32 i32;
                void *p;
            } value3;
        } i32orp;
    } value23;
} KDEventUser;

/* kdFreeEvent: Abandon an event instead of posting it. */
KD_API void KD_APIENTRY kdFreeEvent(KDEvent *event);

/*******************************************************
 * System events
 *******************************************************/

/* KD_EVENT_QUIT: Event to request to quit application. */
#define KD_EVENT_QUIT 43

/* KD_EVENT_PAUSE: Application pause event. */
#define KD_EVENT_PAUSE 45

/* KD_EVENT_RESUME: Application resume event. */
#define KD_EVENT_RESUME 46

/* KD_EVENT_ORIENTATION: Orientation change event. */
#define KD_EVENT_ORIENTATION 48

/* KD_IOGROUP_EVENT: I/O group for OpenKODE Core system events implemented as state values. */
#define KD_IOGROUP_EVENT 0x100
#define KD_STATE_EVENT_USING_BATTERY       (KD_IOGROUP_EVENT + 0)
#define KD_STATE_EVENT_LOW_BATTERY         (KD_IOGROUP_EVENT + 1)


/* KD_IOGROUP_ORIENTATION: I/O group for OpenKODE Core orientation state. */
#define KD_IOGROUP_ORIENTATION 0x200
#define KD_STATE_ORIENTATION_OVERALL       (KD_IOGROUP_ORIENTATION + 0)
#define KD_STATE_ORIENTATION_SCREEN        (KD_IOGROUP_ORIENTATION + 1)
#define KD_STATE_ORIENTATION_RENDERING     (KD_IOGROUP_ORIENTATION + 2)
#define KD_STATE_ORIENTATION_LOCKSURFACE   (KD_IOGROUP_ORIENTATION + 3)


/*******************************************************
 * Application startup and exit.
 *******************************************************/

/* kdMain: The application-defined main function. */
KD_API KDint KD_APIENTRY kdMain(KDint argc, const KDchar *const *argv);

/* kdExit: Exit the application. */
KD_API KD_NORETURN void KD_APIENTRY kdExit(KDint status);

/*******************************************************
 * Utility library functions
 *******************************************************/

/* kdAbs: Compute the absolute value of an integer. */
KD_API KDint KD_APIENTRY kdAbs(KDint i);

/* kdStrtof: Convert a string to a floating point number. */
KD_API KDfloat32 KD_APIENTRY kdStrtof(const KDchar *s, KDchar **endptr);

/* kdStrtol, kdStrtoul: Convert a string to an integer. */
KD_API KDint KD_APIENTRY kdStrtol(const KDchar *s, KDchar **endptr, KDint base);
KD_API KDuint KD_APIENTRY kdStrtoul(const KDchar *s, KDchar **endptr, KDint base);

/* kdLtostr, kdUltostr: Convert an integer to a string. */
#define KD_LTOSTR_MAXLEN ((sizeof(KDint)*8*3+6)/10+2)
#define KD_ULTOSTR_MAXLEN ((sizeof(KDint)*8+2)/3+1)
KD_API KDssize KD_APIENTRY kdLtostr(KDchar *buffer, KDsize buflen, KDint number);
KD_API KDssize KD_APIENTRY kdUltostr(KDchar *buffer, KDsize buflen, KDuint number, KDint base);

/* kdFtostr: Convert a float to a string. */
#define KD_FTOSTR_MAXLEN 16
KD_API KDssize KD_APIENTRY kdFtostr(KDchar *buffer, KDsize buflen, KDfloat32 number);

/* kdCryptoRandom: Return random data. */
KD_API KDint KD_APIENTRY kdCryptoRandom(KDuint8 *buf, KDsize buflen);

/*******************************************************
 * Locale specific functions
 *******************************************************/

/* kdGetLocale: Determine the current language and locale. */
KD_API const KDchar *KD_APIENTRY kdGetLocale(void);

/*******************************************************
 * Memory allocation
 *******************************************************/

/* kdMalloc: Allocate memory. */
KD_API void *KD_APIENTRY kdMalloc(KDsize size);
/* Memory debugger */
#ifndef KD_NDEBUG
KD_API void * KD_APIENTRY kdMalloc_memDebug(KDsize size, const KDchar *file, KDint line);
#define kdMalloc(size) kdMalloc_memDebug(size, __FILE__, __LINE__)
#endif

/* kdFree: Free allocated memory block. */
KD_API void KD_APIENTRY kdFree(void *ptr);

/* kdRealloc: Resize memory block. */
KD_API void *KD_APIENTRY kdRealloc(void *ptr, KDsize size);

/*******************************************************
 * Thread-local storage.
 *******************************************************/

/* kdGetTLS: Get the thread-local storage pointer. */
KD_API void *KD_APIENTRY kdGetTLS(void);

/* kdSetTLS: Set the thread-local storage pointer. */
KD_API void KD_APIENTRY kdSetTLS(void *ptr);

/*******************************************************
 * Mathematical functions
 *******************************************************/
#define KD_E_F 2.71828175F
#define KD_PI_F 3.14159274F
#define KD_PI_2_F 1.57079637F
#define KD_2PI_F 6.28318548F
#define KD_LOG2E_F 1.44269502F
#define KD_LOG10E_F 0.434294492F
#define KD_LN2_F 0.693147182F
#define KD_LN10_F 2.30258512F
#define KD_PI_4_F 0.785398185F
#define KD_1_PI_F 0.318309873F
#define KD_2_PI_F 0.636619747F
#define KD_2_SQRTPI_F 1.12837923F
#define KD_SQRT2_F 1.41421354F
#define KD_SQRT1_2_F 0.707106769F
#define KD_FLT_EPSILON 1.19209290E-07F
#define KD_FLT_MAX 3.40282346638528860e+38F
#define KD_FLT_MIN 1.17549435e-38F
/* KD_INFINITY is defined in kdplatform.h since no portable definition
 * is possible. */
#define kdIsNan(x) (((x) != (x)) ? 1 : 0)
#define KD_HUGE_VALF KD_INFINITY
#define KD_DEG_TO_RAD_F 0.0174532924F
#define KD_RAD_TO_DEG_F 57.2957802F

/* kdAcosf: Arc cosine function. */
KD_API KDfloat32 KD_APIENTRY kdAcosf(KDfloat32 x);

/* kdAsinf: Arc sine function. */
KD_API KDfloat32 KD_APIENTRY kdAsinf(KDfloat32 x);

/* kdAtanf: Arc tangent function. */
KD_API KDfloat32 KD_APIENTRY kdAtanf(KDfloat32 x);

/* kdAtan2f: Arc tangent function. */
KD_API KDfloat32 KD_APIENTRY kdAtan2f(KDfloat32 y, KDfloat32 x);

/* kdCosf: Cosine function. */
KD_API KDfloat32 KD_APIENTRY kdCosf(KDfloat32 x);

/* kdSinf: Sine function. */
KD_API KDfloat32 KD_APIENTRY kdSinf(KDfloat32 x);

/* kdTanf: Tangent function. */
KD_API KDfloat32 KD_APIENTRY kdTanf(KDfloat32 x);

/* kdExpf: Exponential function. */
KD_API KDfloat32 KD_APIENTRY kdExpf(KDfloat32 x);

/* kdLogf: Natural logarithm function. */
KD_API KDfloat32 KD_APIENTRY kdLogf(KDfloat32 x);

/* kdFabsf: Absolute value. */
KD_API KDfloat32 KD_APIENTRY kdFabsf(KDfloat32 x);

/* kdPowf: Power function. */
KD_API KDfloat32 KD_APIENTRY kdPowf(KDfloat32 x, KDfloat32 y);

/* kdSqrtf: Square root function. */
KD_API KDfloat32 KD_APIENTRY kdSqrtf(KDfloat32 x);

/* kdCeilf: Return ceiling value. */
KD_API KDfloat32 KD_APIENTRY kdCeilf(KDfloat32 x);

/* kdFloorf: Return floor value. */
KD_API KDfloat32 KD_APIENTRY kdFloorf(KDfloat32 x);

/* kdRoundf: Round value to nearest integer. */
KD_API KDfloat32 KD_APIENTRY kdRoundf(KDfloat32 x);

/* kdInvsqrtf: Inverse square root function. */
KD_API KDfloat32 KD_APIENTRY kdInvsqrtf(KDfloat32 x);

/* kdFmodf: Calculate floating point remainder. */
KD_API KDfloat32 KD_APIENTRY kdFmodf(KDfloat32 x, KDfloat32 y);

/*******************************************************
 * String and memory functions
 *******************************************************/

/* kdMemchr: Scan memory for a byte value. */
KD_API void *KD_APIENTRY kdMemchr(const void *src, KDint byte, KDsize len);

/* kdMemcmp: Compare two memory regions. */
KD_API KDint KD_APIENTRY kdMemcmp(const void *src1, const void *src2, KDsize len);

/* kdMemcpy: Copy a memory region, no overlapping. */
KD_API void *KD_APIENTRY kdMemcpy(void *buf, const void *src, KDsize len);

/* kdMemmove: Copy a memory region, overlapping allowed. */
KD_API void *KD_APIENTRY kdMemmove(void *buf, const void *src, KDsize len);

/* kdMemset: Set bytes in memory to a value. */
KD_API void *KD_APIENTRY kdMemset(void *buf, KDint byte, KDsize len);

/* kdStrchr: Scan string for a byte value. */
KD_API KDchar *KD_APIENTRY kdStrchr(const KDchar *str, KDint ch);

/* kdStrcmp: Compares two strings. */
KD_API KDint KD_APIENTRY kdStrcmp(const KDchar *str1, const KDchar *str2);

/* kdStrlen: Determine the length of a string. */
KD_API KDsize KD_APIENTRY kdStrlen(const KDchar *str);

/* kdStrnlen: Determine the length of a string. */
KD_API KDsize KD_APIENTRY kdStrnlen(const KDchar *str, KDsize maxlen);

/* kdStrncat_s: Concatenate two strings. */
KD_API KDint KD_APIENTRY kdStrncat_s(KDchar *buf, KDsize buflen, const KDchar *src, KDsize srcmaxlen);

/* kdStrncmp: Compares two strings with length limit. */
KD_API KDint KD_APIENTRY kdStrncmp(const KDchar *str1, const KDchar *str2, KDsize maxlen);

/* kdStrcpy_s: Copy a string with an overrun check. */
KD_API KDint KD_APIENTRY kdStrcpy_s(KDchar *buf, KDsize buflen, const KDchar *src);

/* kdStrncpy_s: Copy a string with an overrun check. */
KD_API KDint KD_APIENTRY kdStrncpy_s(KDchar *buf, KDsize buflen, const KDchar *src, KDsize srclen);

/*******************************************************
 * Time functions
 *******************************************************/

/* kdGetTimeUST: Get the current unadjusted system time. */
KD_API KDust KD_APIENTRY kdGetTimeUST(void);

/* kdTime: Get the current wall clock time. */
KD_API KDtime KD_APIENTRY kdTime(KDtime *timep);

/* kdGmtime_r, kdLocaltime_r: Convert a seconds-since-epoch time into broken-down time. */
typedef struct KDTm {
    KDint32 tm_sec;
    KDint32 tm_min;
    KDint32 tm_hour;
    KDint32 tm_mday;
    KDint32 tm_mon;
    KDint32 tm_year;
    KDint32 tm_wday;
    KDint32 tm_yday;
} KDTm;
KD_API KDTm *KD_APIENTRY kdGmtime_r(const KDtime *timep, KDTm *result);
KD_API KDTm *KD_APIENTRY kdLocaltime_r(const KDtime *timep, KDTm *result);

/* kdUSTAtEpoch: Get the UST corresponding to KDtime 0. */
KD_API KDust KD_APIENTRY kdUSTAtEpoch(void);

/*******************************************************
 * Timer functions
 *******************************************************/

/* kdSetTimer: Set timer. */
#define KD_TIMER_ONESHOT 61
#define KD_TIMER_PERIODIC_AVERAGE 62
#define KD_TIMER_PERIODIC_MINIMUM 63
typedef struct KDTimer KDTimer;
KD_API KDTimer *KD_APIENTRY kdSetTimer(KDint64 interval, KDint periodic, void *eventuserptr);

/* kdCancelTimer: Cancel and free a timer. */
KD_API KDint KD_APIENTRY kdCancelTimer(KDTimer *timer);

/* KD_EVENT_TIMER: Timer fire event. */
#define KD_EVENT_TIMER 42

/*******************************************************
 * File system
 *******************************************************/
#define KD_EOF (-1)

/* kdFopen: Open a file from the file system. */
typedef struct KDFile KDFile;
KD_API KDFile *KD_APIENTRY kdFopen(const KDchar *pathname, const KDchar *mode);

/* kdFclose: Close an open file. */
KD_API KDint KD_APIENTRY kdFclose(KDFile *file);

/* kdFflush: Flush an open file. */
KD_API KDint KD_APIENTRY kdFflush(KDFile *file);

/* kdFread: Read from a file. */
KD_API KDsize KD_APIENTRY kdFread(void *buffer, KDsize size, KDsize count, KDFile *file);

/* kdFwrite: Write to a file. */
KD_API KDsize KD_APIENTRY kdFwrite(const void *buffer, KDsize size, KDsize count, KDFile *file);

/* kdGetc: Read next byte from an open file. */
KD_API KDint KD_APIENTRY kdGetc(KDFile *file);

/* kdPutc: Write a byte to an open file. */
KD_API KDint KD_APIENTRY kdPutc(KDchar c, KDFile *file);

/* kdFgets: Read a line of text from an open file. */
KD_API KDchar *KD_APIENTRY kdFgets(KDchar *buffer, KDsize buflen, KDFile *file);

/* kdFEOF: Check for end of file. */
KD_API KDint KD_APIENTRY kdFEOF(KDFile *file);

/* kdFerror: Check for an error condition on an open file. */
KD_API KDint KD_APIENTRY kdFerror(KDFile *file);

/* kdClearerr: Clear a file&#8217;s error and end-of-file indicators. */
KD_API void KD_APIENTRY kdClearerr(KDFile *file);

/* kdFseek: Reposition the file position indicator in a file. */
typedef enum {
    KD_SEEK_SET =  0, 
    KD_SEEK_CUR =  1, 
    KD_SEEK_END =  2
} KDfileSeekOrigin;
KD_API KDint KD_APIENTRY kdFseek(KDFile *file, KDoff offset, KDfileSeekOrigin origin);

/* kdFtell: Get the file position of an open file. */
KD_API KDoff KD_APIENTRY kdFtell(KDFile *file);

/* kdMkdir: Create new directory. */
KD_API KDint KD_APIENTRY kdMkdir(const KDchar *pathname);

/* kdRmdir: Delete a directory. */
KD_API KDint KD_APIENTRY kdRmdir(const KDchar *pathname);

/* kdRename: Rename a file. */
KD_API KDint KD_APIENTRY kdRename(const KDchar *src, const KDchar *dest);

/* kdRemove: Delete a file. */
KD_API KDint KD_APIENTRY kdRemove(const KDchar *pathname);

/* kdTruncate: Truncate or extend a file. */
KD_API KDint KD_APIENTRY kdTruncate(const KDchar *pathname, KDoff length);

/* kdStat, kdFstat: Return information about a file. */
typedef struct KDStat {
    KDmode st_mode;
    KDoff st_size;
    KDtime st_mtime;
} KDStat;
KD_API KDint KD_APIENTRY kdStat(const KDchar *pathname, struct KDStat *buf);
KD_API KDint KD_APIENTRY kdFstat(KDFile *file, struct KDStat *buf);
#define KD_ISREG(m) ((m) & 0x8000)
#define KD_ISDIR(m) ((m) & 0x4000)

/* kdAccess: Determine whether the application can access a file or directory. */
KD_API KDint KD_APIENTRY kdAccess(const KDchar *pathname, KDint amode);
#define KD_R_OK 4
#define KD_W_OK 2
#define KD_X_OK 1

/* kdOpenDir: Open a directory ready for listing. */
typedef struct KDDir KDDir;
KD_API KDDir *KD_APIENTRY kdOpenDir(const KDchar *pathname);

/* kdReadDir: Return the next file in a directory. */
typedef struct KDDirent {
    const KDchar *d_name;
} KDDirent;
KD_API KDDirent *KD_APIENTRY kdReadDir(KDDir *dir);

/* kdCloseDir: Close a directory. */
KD_API KDint KD_APIENTRY kdCloseDir(KDDir *dir);

/* kdGetFree: Get free space on a drive. */
KD_API KDoff KD_APIENTRY kdGetFree(const KDchar *pathname);

/*******************************************************
 * Network sockets
 *******************************************************/

/* KDSockaddr: Struct type for socket address. */
typedef struct KDSockaddr {
    KDuint16 family;
    union {
#define KD_AF_INET 70
        struct {
            KDuint16 port;
            KDuint32 address;
        } sin;
    } data;
} KDSockaddr;

/* kdNameLookup: Look up a hostname. */
KD_API KDint KD_APIENTRY kdNameLookup(KDint af, const KDchar *hostname, void *eventuserptr);

/* kdNameLookupCancel: Selectively cancels ongoing kdNameLookup operations. */
KD_API void KD_APIENTRY kdNameLookupCancel(void *eventuserptr);

/* kdSocketCreate: Creates a socket. */
typedef struct KDSocket KDSocket;
KD_API KDSocket *KD_APIENTRY kdSocketCreate(KDint type, void *eventuserptr);
#define KD_SOCK_TCP 64
#define KD_SOCK_UDP 65

/* kdSocketClose: Closes a socket. */
KD_API KDint KD_APIENTRY kdSocketClose(KDSocket *socket);

/* kdSocketBind: Bind a socket. */
KD_API KDint KD_APIENTRY kdSocketBind(KDSocket *socket, const struct KDSockaddr *addr, KDboolean reuse);
#define KD_INADDR_ANY 0

/* kdSocketGetName: Get the local address of a socket. */
KD_API KDint KD_APIENTRY kdSocketGetName(KDSocket *socket, struct KDSockaddr *addr);

/* kdSocketConnect: Connects a socket. */
KD_API KDint KD_APIENTRY kdSocketConnect(KDSocket *socket, const KDSockaddr *addr);

/* kdSocketListen: Listen on a socket. */
KD_API KDint KD_APIENTRY kdSocketListen(KDSocket *socket, KDint backlog);

/* kdSocketAccept: Accept an incoming connection. */
KD_API KDSocket *KD_APIENTRY kdSocketAccept(KDSocket *socket, KDSockaddr *addr, void *eventuserptr);

/* kdSocketSend, kdSocketSendTo: Send data to a socket. */
KD_API KDint KD_APIENTRY kdSocketSend(KDSocket *socket, const void *buf, KDint len);
KD_API KDint KD_APIENTRY kdSocketSendTo(KDSocket *socket, const void *buf, KDint len, const KDSockaddr *addr);

/* kdSocketRecv, kdSocketRecvFrom: Receive data from a socket. */
KD_API KDint KD_APIENTRY kdSocketRecv(KDSocket *socket, void *buf, KDint len);
KD_API KDint KD_APIENTRY kdSocketRecvFrom(KDSocket *socket, void *buf, KDint len, KDSockaddr *addr);

/* kdHtonl: Convert a 32-bit integer from host to network byte order. */
KD_API KDuint32 KD_APIENTRY kdHtonl(KDuint32 hostlong);

/* kdHtons: Convert a 16-bit integer from host to network byte order. */
KD_API KDuint16 KD_APIENTRY kdHtons(KDuint16 hostshort);

/* kdNtohl: Convert a 32-bit integer from network to host byte order. */
KD_API KDuint32 KD_APIENTRY kdNtohl(KDuint32 netlong);

/* kdNtohs: Convert a 16-bit integer from network to host byte order. */
KD_API KDuint16 KD_APIENTRY kdNtohs(KDuint16 netshort);

/* kdInetAton: Convert a &#8220;dotted quad&#8221; format address to an integer. */
KD_API KDint KD_APIENTRY kdInetAton(const KDchar *cp, KDuint32 *inp);

/* kdInetNtop: Convert a network address to textual form. */
#define KD_INET_ADDRSTRLEN 16
typedef struct KDInAddr {
    KDuint32 s_addr;
} KDInAddr;
KD_API const KDchar *KD_APIENTRY kdInetNtop(KDuint af, const void *src, KDchar *dst, KDsize cnt);

/* KD_EVENT_SOCKET_READABLE: Event to indicate that a socket is readable. */
#define KD_EVENT_SOCKET_READABLE 49
typedef struct KDEventSocketReadable {
    KDSocket *socket;
} KDEventSocketReadable;

/* KD_EVENT_SOCKET_WRITABLE: Event to indicate that a socket is writable. */
#define KD_EVENT_SOCKET_WRITABLE 50
typedef struct KDEventSocketWritable {
    KDSocket *socket;
} KDEventSocketWritable;

/* KD_EVENT_SOCKET_CONNECT_COMPLETE: Event generated when a socket connect is complete */
#define KD_EVENT_SOCKET_CONNECT_COMPLETE 51
typedef struct KDEventSocketConnect {
    KDSocket *socket;
    KDint32 error;
} KDEventSocketConnect;

/* KD_EVENT_SOCKET_INCOMING: Event generated when a listening socket detects an incoming connection or an error. */
#define KD_EVENT_SOCKET_INCOMING 52
typedef struct KDEventSocketIncoming {
    KDSocket *socket;
} KDEventSocketIncoming;

/* KD_EVENT_NAME_LOOKUP_COMPLETE: kdNameLookup complete event. */
#define KD_EVENT_NAME_LOOKUP_COMPLETE 53
typedef struct KDEventNameLookup {
    KDint32 error;
    KDint32 resultlen;
    const KDSockaddr *result;
    KDboolean more;
} KDEventNameLookup;

/*******************************************************
 * Input/output
 *******************************************************/

/* KD_EVENT_STATE: State changed event. */
#define KD_EVENT_STATE 55
        
typedef struct KDEventState {
    KDint32 index;
    union {
        KDint32 i;
        KDint64 l;
        KDfloat32 f;
    } value;
} KDEventState;

/* KD_EVENT_INPUT: Input changed event. */
#define KD_EVENT_INPUT 56
        
typedef struct KDEventInput {
    KDint32 index;
    union {
        KDint32 i;
        KDint64 l;
        KDfloat32 f;
    } value;
} KDEventInput;

/* KD_EVENT_INPUT_JOG: Jogdial jog event. */
#define KD_EVENT_INPUT_JOG 71
typedef struct KDEventInputJog {
    KDint32 index;
    KDint32 count;
} KDEventInputJog;

/* KD_EVENT_INPUT_POINTER: Pointer input changed event. */
#define KD_EVENT_INPUT_POINTER 57
typedef struct KDEventInputPointer {
    KDint32 index;
    KDint32 select;
    KDint32 x;
    KDint32 y;
} KDEventInputPointer;

/* KD_EVENT_INPUT_STICK: Joystick stick changed event. */
#define KD_EVENT_INPUT_STICK 58
typedef struct KDEventInputStick {
    KDint32 index;
    KDint32 x;
    KDint32 y;
    KDint32 z;
} KDEventInputStick;

/* kdStateGeti, kdStateGetl, kdStateGetf: get state value(s) */
KD_API KDint KD_APIENTRY kdStateGeti(KDint startidx, KDuint numidxs, KDint32 *buffer);
KD_API KDint KD_APIENTRY kdStateGetl(KDint startidx, KDuint numidxs, KDint64 *buffer);
KD_API KDint KD_APIENTRY kdStateGetf(KDint startidx, KDuint numidxs, KDfloat32 *buffer);

/* kdOutputSeti, kdOutputSetf: set outputs */
KD_API KDint KD_APIENTRY kdOutputSeti(KDint startidx, KDuint numidxs, const KDint32 *buffer);
KD_API KDint KD_APIENTRY kdOutputSetf(KDint startidx, KDuint numidxs, const KDfloat32 *buffer);
#define KD_IO_CONTROLLER_STRIDE 64

/* KD_IOGROUP_GAMEKEYS: I/O group for game keys. */
#define KD_IOGROUP_GAMEKEYS 0x1000
#define KD_STATE_GAMEKEYS_AVAILABILITY    (KD_IOGROUP_GAMEKEYS + 0)
#define KD_INPUT_GAMEKEYS_UP              (KD_IOGROUP_GAMEKEYS + 1)
#define KD_INPUT_GAMEKEYS_LEFT            (KD_IOGROUP_GAMEKEYS + 2)
#define KD_INPUT_GAMEKEYS_RIGHT           (KD_IOGROUP_GAMEKEYS + 3)
#define KD_INPUT_GAMEKEYS_DOWN            (KD_IOGROUP_GAMEKEYS + 4)
#define KD_INPUT_GAMEKEYS_FIRE            (KD_IOGROUP_GAMEKEYS + 5)
#define KD_INPUT_GAMEKEYS_A               (KD_IOGROUP_GAMEKEYS + 6)
#define KD_INPUT_GAMEKEYS_B               (KD_IOGROUP_GAMEKEYS + 7)
#define KD_INPUT_GAMEKEYS_C               (KD_IOGROUP_GAMEKEYS + 8)
#define KD_INPUT_GAMEKEYS_D               (KD_IOGROUP_GAMEKEYS + 9)

/* KD_IOGROUP_GAMEKEYSNC: I/O group for game keys, no chording. */
#define KD_IOGROUP_GAMEKEYSNC 0x1100
#define KD_STATE_GAMEKEYSNC_AVAILABILITY  (KD_IOGROUP_GAMEKEYSNC + 0)
#define KD_INPUT_GAMEKEYSNC_UP            (KD_IOGROUP_GAMEKEYSNC + 1)
#define KD_INPUT_GAMEKEYSNC_LEFT          (KD_IOGROUP_GAMEKEYSNC + 2)
#define KD_INPUT_GAMEKEYSNC_RIGHT         (KD_IOGROUP_GAMEKEYSNC + 3)
#define KD_INPUT_GAMEKEYSNC_DOWN          (KD_IOGROUP_GAMEKEYSNC + 4)
#define KD_INPUT_GAMEKEYSNC_FIRE          (KD_IOGROUP_GAMEKEYSNC + 5)
#define KD_INPUT_GAMEKEYSNC_A             (KD_IOGROUP_GAMEKEYSNC + 6)
#define KD_INPUT_GAMEKEYSNC_B             (KD_IOGROUP_GAMEKEYSNC + 7)
#define KD_INPUT_GAMEKEYSNC_C             (KD_IOGROUP_GAMEKEYSNC + 8)
#define KD_INPUT_GAMEKEYSNC_D             (KD_IOGROUP_GAMEKEYSNC + 9)

/* KD_IOGROUP_PHONEKEYPAD: I/O group for phone keypad. */
#define KD_IOGROUP_PHONEKEYPAD 0x2000
#define KD_STATE_PHONEKEYPAD_AVAILABILITY  (KD_IOGROUP_PHONEKEYPAD + 0)
#define KD_INPUT_PHONEKEYPAD_0             (KD_IOGROUP_PHONEKEYPAD + 1)
#define KD_INPUT_PHONEKEYPAD_1             (KD_IOGROUP_PHONEKEYPAD + 2)
#define KD_INPUT_PHONEKEYPAD_2             (KD_IOGROUP_PHONEKEYPAD + 3)
#define KD_INPUT_PHONEKEYPAD_3             (KD_IOGROUP_PHONEKEYPAD + 4)
#define KD_INPUT_PHONEKEYPAD_4             (KD_IOGROUP_PHONEKEYPAD + 5)
#define KD_INPUT_PHONEKEYPAD_5             (KD_IOGROUP_PHONEKEYPAD + 6)
#define KD_INPUT_PHONEKEYPAD_6             (KD_IOGROUP_PHONEKEYPAD + 7)
#define KD_INPUT_PHONEKEYPAD_7             (KD_IOGROUP_PHONEKEYPAD + 8)
#define KD_INPUT_PHONEKEYPAD_8             (KD_IOGROUP_PHONEKEYPAD + 9)
#define KD_INPUT_PHONEKEYPAD_9             (KD_IOGROUP_PHONEKEYPAD + 10)
#define KD_INPUT_PHONEKEYPAD_STAR          (KD_IOGROUP_PHONEKEYPAD + 11)
#define KD_INPUT_PHONEKEYPAD_HASH          (KD_IOGROUP_PHONEKEYPAD + 12)
#define KD_INPUT_PHONEKEYPAD_LEFTSOFT      (KD_IOGROUP_PHONEKEYPAD + 13)
#define KD_INPUT_PHONEKEYPAD_RIGHTSOFT     (KD_IOGROUP_PHONEKEYPAD + 14)
#define KD_STATE_PHONEKEYPAD_ORIENTATION   (KD_IOGROUP_PHONEKEYPAD + 15)

/* KD_IOGROUP_VIBRATE: I/O group for vibrate. */
#define KD_IOGROUP_VIBRATE 0x3000
#define KD_STATE_VIBRATE_AVAILABILITY  (KD_IOGROUP_VIBRATE + 0)
#define KD_STATE_VIBRATE_MINFREQUENCY  (KD_IOGROUP_VIBRATE + 1)
#define KD_STATE_VIBRATE_MAXFREQUENCY  (KD_IOGROUP_VIBRATE + 2)
#define KD_OUTPUT_VIBRATE_VOLUME        (KD_IOGROUP_VIBRATE + 3)
#define KD_OUTPUT_VIBRATE_FREQUENCY     (KD_IOGROUP_VIBRATE + 4)

/* KD_IOGROUP_POINTER: I/O group for pointer. */
#define KD_IOGROUP_POINTER 0x4000
#define KD_STATE_POINTER_AVAILABILITY  (KD_IOGROUP_POINTER + 0)
#define KD_INPUT_POINTER_X             (KD_IOGROUP_POINTER + 1)
#define KD_INPUT_POINTER_Y             (KD_IOGROUP_POINTER + 2)
#define KD_INPUT_POINTER_SELECT        (KD_IOGROUP_POINTER + 3)

/* KD_IOGROUP_BACKLIGHT: I/O group for backlight. */
#define KD_IOGROUP_BACKLIGHT 0x5000
#define KD_STATE_BACKLIGHT_AVAILABILITY (KD_IOGROUP_BACKLIGHT + 0)
#define KD_OUTPUT_BACKLIGHT_FORCE (KD_IOGROUP_BACKLIGHT + 1)

/* KD_IOGROUP_JOGDIAL: I/O group for a jog dial. */
#define KD_IOGROUP_JOGDIAL 0x6000
#define KD_STATE_JOGDIAL_AVAILABILITY  (KD_IOGROUP_JOGDIAL + 0)
#define KD_INPUT_JOGDIAL_UP            (KD_IOGROUP_JOGDIAL + 1)
#define KD_INPUT_JOGDIAL_LEFT          (KD_IOGROUP_JOGDIAL + 2)
#define KD_INPUT_JOGDIAL_RIGHT         (KD_IOGROUP_JOGDIAL + 3)
#define KD_INPUT_JOGDIAL_DOWN          (KD_IOGROUP_JOGDIAL + 4)
#define KD_INPUT_JOGDIAL_SELECT        (KD_IOGROUP_JOGDIAL + 5)

/* KD_IOGROUP_STICK: I/O group for joystick. */
#define KD_IOGROUP_STICK 0x7000
#define KD_STATE_STICK_AVAILABILITY    (KD_IOGROUP_STICK + 0)
#define KD_INPUT_STICK_X               (KD_IOGROUP_STICK + 1)
#define KD_INPUT_STICK_Y               (KD_IOGROUP_STICK + 2)
#define KD_INPUT_STICK_Z               (KD_IOGROUP_STICK + 3)
#define KD_INPUT_STICK_BUTTON          (KD_IOGROUP_STICK + 4)
#define KD_IO_STICK_STRIDE 8

/* KD_IOGROUP_DPAD: I/O group for D-pad. */
#define KD_IOGROUP_DPAD 0x8000
#define KD_STATE_DPAD_AVAILABILITY     (KD_IOGROUP_DPAD + 0)
#define KD_STATE_DPAD_COPY             (KD_IOGROUP_DPAD + 1)
#define KD_INPUT_DPAD_UP               (KD_IOGROUP_DPAD + 2)
#define KD_INPUT_DPAD_LEFT             (KD_IOGROUP_DPAD + 3)
#define KD_INPUT_DPAD_RIGHT            (KD_IOGROUP_DPAD + 4)
#define KD_INPUT_DPAD_DOWN             (KD_IOGROUP_DPAD + 5)
#define KD_INPUT_DPAD_SELECT           (KD_IOGROUP_DPAD + 6)
#define KD_IO_DPAD_STRIDE 8

/* KD_IOGROUP_BUTTONS: I/O group for buttons associated with joystick or D-pad. */
#define KD_IOGROUP_BUTTONS 0x9000
#define KD_STATE_BUTTONS_AVAILABILITY  (KD_IOGROUP_BUTTONS + 0)
#define KD_INPUT_BUTTONS_0             (KD_IOGROUP_BUTTONS + 1)

/* KD_IO_UNDEFINED: I/O items reserved for implementation-dependent use. */
#define KD_IO_UNDEFINED 0x40000000

/*******************************************************
 * Windowing
 *******************************************************/
#ifdef KD_WINDOW_SUPPORTED
#include <EGL/egl.h>
typedef struct KDWindow KDWindow;

/* kdCreateWindow: Create a window. */
KD_API KDWindow *KD_APIENTRY kdCreateWindow(EGLDisplay display, EGLConfig config, void *eventuserptr);

/* kdDestroyWindow: Destroy a window. */
KD_API KDint KD_APIENTRY kdDestroyWindow(KDWindow *window);

/* kdSetWindowPropertybv, kdSetWindowPropertyiv, kdSetWindowPropertycv: Set a window property to request a change in the on-screen representation of the window. */
KD_API KDint KD_APIENTRY kdSetWindowPropertybv(KDWindow *window, KDint pname, const KDboolean *param);
KD_API KDint KD_APIENTRY kdSetWindowPropertyiv(KDWindow *window, KDint pname, const KDint32 *param);
KD_API KDint KD_APIENTRY kdSetWindowPropertycv(KDWindow *window, KDint pname, const KDchar *param);

/* kdGetWindowPropertybv, kdGetWindowPropertyiv, kdGetWindowPropertycv: Get the current value of a window property. */
KD_API KDint KD_APIENTRY kdGetWindowPropertybv(KDWindow *window, KDint pname, KDboolean *param);
KD_API KDint KD_APIENTRY kdGetWindowPropertyiv(KDWindow *window, KDint pname, KDint32 *param);
KD_API KDint KD_APIENTRY kdGetWindowPropertycv(KDWindow *window, KDint pname, KDchar *param, KDsize *size);

/* kdRealizeWindow: Realize the window as a displayable entity and get the native window handle for passing to EGL. */
KD_API KDint KD_APIENTRY kdRealizeWindow(KDWindow *window, EGLNativeWindowType *nativewindow);

/* KD_WINDOWPROPERTY_SIZE: Window client area width and height. */
#define KD_WINDOWPROPERTY_SIZE 66

/* KD_WINDOWPROPERTY_VISIBILITY: Window visibility status. */
#define KD_WINDOWPROPERTY_VISIBILITY 67

/* KD_WINDOWPROPERTY_FOCUS: Window input focus status. */
#define KD_WINDOWPROPERTY_FOCUS 68

/* KD_WINDOWPROPERTY_CAPTION: Window caption. */
#define KD_WINDOWPROPERTY_CAPTION 69

/* KD_EVENT_WINDOW_CLOSE: Event to request to close window. */
#define KD_EVENT_WINDOW_CLOSE 44

/* KD_EVENT_WINDOWPROPERTY_CHANGE: Notification about realized window property change. */
#define KD_EVENT_WINDOWPROPERTY_CHANGE 47
typedef struct KDEventWindowProperty {
    KDint32 pname;
} KDEventWindowProperty;

/* KD_EVENT_WINDOW_FOCUS: Event for change of window&#8217;s focus state. */
#define KD_EVENT_WINDOW_FOCUS 60
typedef struct KDEventWindowFocus {
    KDint32 focusstate;
} KDEventWindowFocus;

/* KD_EVENT_WINDOW_REDRAW: Event to notify need to redraw the window. */
#define KD_EVENT_WINDOW_REDRAW 59
#endif /* KD_WINDOW_SUPPORTED */

/*******************************************************
 * Assertions and logging
 *******************************************************/

/* kdHandleAssertion: Handle assertion failure. */
KD_API void KD_APIENTRY kdHandleAssertion(const KDchar *condition, const KDchar *filename, KDint linenumber);

/* kdLogMessage: Output a log message. */
#ifdef KD_NDEBUG
#define kdLogMessage(s)
#else
KD_API void KD_APIENTRY kdLogMessage(const KDchar *string);
#endif

/* struct KDEvent delayed to the end as it uses event data structs from
 * other parts of the .h file. */
struct KDEvent {
    KDust timestamp;
    KDint32 type;
    void *userptr;
    union KDEventData {
        KDEventState state;
        KDEventInput input;
        KDEventInputJog inputjog;
        KDEventInputPointer inputpointer;
        KDEventInputStick inputstick;
        KDEventSocketReadable socketreadable;
        KDEventSocketWritable socketwritable;
        KDEventSocketConnect socketconnect;
        KDEventSocketIncoming socketincoming;
        KDEventNameLookup namelookup;
#ifdef KD_WINDOW_SUPPORTED
        KDEventWindowProperty windowproperty;
        KDEventWindowFocus windowfocus;
#endif /* KD_WINDOW_SUPPORTED */
        KDEventUser user;
    } data;
};

#ifdef __cplusplus
}
#endif

#endif /* __kd_h_ */

