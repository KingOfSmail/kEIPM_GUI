#include "api.h"
#define DEBUG_API

#ifdef DEBUG_API

keipm_err_t keipm_set_Key(const char* publicKey_Path,const char* elf_Path){
    if(rand() & 1){
        return ERROR(kEIPM_OK,"生成成功，点击完成退出。");
    }else{
        return ERROR(kEIPM_ERR_MALFORMED,"无法写入文件。");
    }
}

keipm_err_t keipm_set_UserCA(const char* UserCA_Path,const char* elf_Path){
    if(rand() & 1){
        return ERROR(kEIPM_OK,"生成成功，点击完成退出。");
    }else{
        return ERROR(kEIPM_ERR_MALFORMED,"无法写入文件。");
    }
}

#endif
