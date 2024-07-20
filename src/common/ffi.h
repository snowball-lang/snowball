
#pragma once

#ifdef __cplusplus
#define SN_EXTERN_START extern "C" {
#define SN_EXTERN_END }
#else
#define SN_EXTERN_START
#define SN_EXTERN_END
#endif

#ifdef SN_API_EXPORT
#define SN_API SN_API_EXPORT
#else
#define SN_API
#endif
