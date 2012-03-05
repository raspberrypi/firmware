
/*******************************************************
 * OpenKODE Core extension: KD_KHR_thread_storage
 *******************************************************/
/* Sample KD/KHR_thread_storage.h for OpenKODE Core */
#ifndef __kd_KHR_thread_storage_h_
#define __kd_KHR_thread_storage_h_
#include <KD/kd.h>

#ifdef __cplusplus
extern "C" {
#endif



/* KDThreadStorageKeyKHR: The representation of a thread storage key. */
typedef KDuint32 KDThreadStorageKeyKHR;

/* kdMapThreadStorageKHR: Maps an arbitrary pointer to a global thread storage key. */
KD_API KDThreadStorageKeyKHR KD_APIENTRY KD_APIENTRY kdMapThreadStorageKHR(const void * id);

/* kdSetThreadStorageKHR: Stores thread-local data. */
KD_API KDint KD_APIENTRY KD_APIENTRY kdSetThreadStorageKHR(KDThreadStorageKeyKHR key, void * data);

/* kdGetThreadStorageKHR: Retrieves previously stored thread-local data. */
KD_API void * KD_APIENTRY KD_APIENTRY kdGetThreadStorageKHR(KDThreadStorageKeyKHR key);

#ifdef __cplusplus
}
#endif

#endif /* __kd_KHR_thread_storage_h_ */

