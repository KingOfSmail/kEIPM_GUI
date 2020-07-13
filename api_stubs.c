#include "api.h"
#define DEBUG_API

#ifdef DEBUG_API

keipm_err_t keipm_gen_key_pair(){
    if(1){
        return ERROR(kEIPM_OK,"生成成功，点击完成退出。");
    }else{
        return ERROR(kEIPM_ERR_MALFORMED,"无法写入文件。");
    }
}

#endif
