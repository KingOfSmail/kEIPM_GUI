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

const char* keipm_create_PrivateKey(keipm_err_t *error){
    if(rand() & 1){
        *error = ERROR(kEIPM_OK,"生成私钥成功，点击完成退出。");
    }else{
        *error = ERROR(kEIPM_ERR_MALFORMED,"生成私钥失败，无法写入文件。");
    }
    return "/home/Desktop/Qt";
}
const char* keipm_create_PublicKey(keipm_err_t *error,const char* privateKeyPath){
    if(rand() & 1){
        *error = ERROR(kEIPM_OK,"生成公钥成功，点击完成退出。");
    }else{
        *error = ERROR(kEIPM_ERR_MALFORMED,"生成公钥失败，无法写入文件。");
    }
    return "/home/wangzhe/Desktop/新建文本.txt";
}

const char* keipm_create_rootCA(keipm_err_t *error,RootCa rootca){
    if(rand() & 1){
        *error = ERROR(kEIPM_OK,"生成根证书成功，点击完成退出。");
    }else{
        *error = ERROR(kEIPM_ERR_MALFORMED,"生成根证书失败，无法写入文件。");
    }
    return "/home/wangzhe/Desktop/新建文本.txt";
}

const char* keipm_create_userCA(keipm_err_t *error,UserCa userca){
    if(rand() & 1){
        *error = ERROR(kEIPM_OK,"生成用户证书成功，点击完成退出。");
    }else{
        *error = ERROR(kEIPM_ERR_MALFORMED,"生成用户证书失败，无法写入文件。");
    }
    return "/home/Desktop/Qt";
}

#endif
