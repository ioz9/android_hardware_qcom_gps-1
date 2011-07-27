/* Copyright (c) 2011 Code Aurora Forum. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __LOG_UTIL_H__
#define __LOG_UTIL_H__

#ifdef LOG_UTIL_OFF_TARGET

#include <stdio.h>

//error logs
#define UTIL_LOGE(...) printf(__VA_ARGS__)
//warning logs
#define UTIL_LOGW(...) printf(__VA_ARGS__)
// debug logs
#define UTIL_LOGD(...) printf(__VA_ARGS__)
//info logs
#define UTIL_LOGI(...) printf(__VA_ARGS__)
//verbose logs
#define UTIL_LOGV(...) printf(__VA_ARGS__)

// Fake Log.h in host test environment will account for
// strlcpy and strlcat not being found.
#include <utils/Log.h>

#elif defined(_ANDROID_)

#include <utils/Log.h>

//error logs
#define UTIL_LOGE(...)   LOGE(__VA_ARGS__)
//warning logs
#define UTIL_LOGW(...)   LOGW(__VA_ARGS__)
// debug logs
#define UTIL_LOGD(...)   LOGD(__VA_ARGS__)
// info logs
#define UTIL_LOGI(...)   LOGI(__VA_ARGS__)
// verbose logs
#define UTIL_LOGV(...)   LOGV(__VA_ARGS__)

#endif //LOG_UTIL_OFF_TARGET

#ifdef __cplusplus
extern "C"
{
#endif
/*=============================================================================
 *
 *                         LOC LOGGER TYPE DECLARATION
 *
 *============================================================================*/
/* LOC LOGGER */
typedef struct loc_logger_s
{
  unsigned long  DEBUG_LEVEL;
  unsigned long  TIMESTAMP;
} loc_logger_s_type;

/*=============================================================================
 *
 *                               EXTERNAL DATA
 *
 *============================================================================*/
extern loc_logger_s_type loc_logger;

/*=============================================================================
 *
 *                        MODULE EXPORTED FUNCTIONS
 *
 *============================================================================*/
extern void loc_logger_init(unsigned long debug, unsigned long timestamp);
extern char* get_timestamp(char* str);


#include <utils/Log.h>

#ifndef DEBUG_DMN_LOC_API

/* LOGGING MACROS */
#define LOC_LOGE(...) \
if (loc_logger.DEBUG_LEVEL >= 1) { LOGE("E/"__VA_ARGS__); }

#define LOC_LOGW(...) \
if (loc_logger.DEBUG_LEVEL >= 2) { LOGE("W/"__VA_ARGS__); }

#define LOC_LOGI(...) \
if (loc_logger.DEBUG_LEVEL >= 3) { LOGE("I/"__VA_ARGS__); }

#define LOC_LOGD(...) \
if (loc_logger.DEBUG_LEVEL >= 4) { LOGE("D/"__VA_ARGS__); }

#define LOC_LOGV(...) \
if (loc_logger.DEBUG_LEVEL >= 5) { LOGE("V/"__VA_ARGS__); }

#else /* DEBUG_DMN_LOC_API */

#define LOC_LOGE(...) LOGE("E/"__VA_ARGS__)

#define LOC_LOGW(...) LOGW("W/"__VA_ARGS__)

#define LOC_LOGI(...) LOGI("I/"__VA_ARGS__)

#define LOC_LOGD(...) LOGD("D/"__VA_ARGS__)

#define LOC_LOGV(...) LOGV("V/"__VA_ARGS__)

#endif /* DEBUG_DMN_LOC_API */


/*=============================================================================
 *
 *                          LOGGING IMPROVEMENT MACROS
 *
 *============================================================================*/
extern const char *boolStr[];
#define VOID_RET "None"
#define CALLFLOW_TAG "callflow -->"

#define ENTRY_LOG()                                                                                                    \
do { if (loc_logger.TIMESTAMP) {                                                                                       \
             char time_stamp[32];                                                                                      \
             LOC_LOGV("[%s] %s called, line %d", get_timestamp(time_stamp), __func__, __LINE__);                       \
        } else    {                                                                                                    \
          LOC_LOGV("%s called, line %d", __func__, __LINE__);                                                          \
          }                                                                                                            \
    } while (0)

#define EXIT_LOG(SPECIFIER, RETVAL)                                                                                    \
do { if (loc_logger.TIMESTAMP) {                                                                                       \
             char time_stamp[32];                                                                                      \
             LOC_LOGV("[%s] %s finished, line %d", get_timestamp(time_stamp), __func__, __LINE__);                     \
        } else {                                                                                                       \
          LOC_LOGV("%s finished, line %d, returned" #SPECIFIER, __func__, __LINE__, RETVAL);                           \
          }                                                                                                            \
    } while (0)

#define ENTRY_LOG_CALLFLOW()                                                                                           \
do { if (loc_logger.TIMESTAMP) {                                                                                       \
             char time_stamp[32];                                                                                      \
             LOC_LOGI("[%s] %s %s called, line %d", get_timestamp(time_stamp), CALLFLOW_TAG, __func__, __LINE__);      \
        } else {                                                                                                       \
          LOC_LOGI("%s %s called, line %d", CALLFLOW_TAG, __func__, __LINE__);                                         \
          }                                                                                                            \
    } while (0)

#define EXIT_LOG_CALLFLOW(SPECIFIER, RETVAL)                                                                           \
do { if (loc_logger.TIMESTAMP) {                                                                                       \
             char time_stamp[32];                                                                                      \
             LOC_LOGI("[%s] %s %s finished, line %d", get_timestamp(time_stamp), CALLFLOW_TAG, __func__, __LINE__);    \
        } else {                                                                                                       \
          LOC_LOGI("%s %s finished, line %d, returned" #SPECIFIER, CALLFLOW_TAG, __func__, __LINE__, RETVAL);          \
          }                                                                                                            \
    } while (0)

#define CALLBACK_LOG_CALLFLOW(CALLBACK_NAME)                                                                           \
do { if (loc_logger.TIMESTAMP) {                                                                                       \
             char time_stamp[32];                                                                                      \
             LOC_LOGI("[%s] %s %s fired, line %d", get_timestamp(time_stamp), CALLFLOW_TAG, CALLBACK_NAME, __LINE__);  \
        } else {                                                                                                       \
          LOC_LOGI("%s %s fired, line %d", CALLFLOW_TAG, CALLBACK_NAME, __LINE__);                                     \
          }                                                                                                            \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif // __LOG_UTIL_H__
