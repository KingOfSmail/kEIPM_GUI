#ifndef API_H_
#define API_H_

#include "errors.h"

#ifdef __cplusplus
extern "C" {
#endif

// 接口C函数原型
// extern keipm_err_t 接口名(参数...);

extern keipm_err_t keipm_gen_key_pair();


#ifdef __cplusplus
}
#endif

#endif // API_H_
