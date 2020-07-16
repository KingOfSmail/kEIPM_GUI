#include <stdlib.h>
#include "../api.h"
#define DEBUG_API

#ifdef DEBUG_API

keipm_err_t keipm_set_Key(const char* publicKey_Path,const char* elf_Path){
    (void)publicKey_Path;
    (void)elf_Path;
    if(rand() & 1){
        return ERROR(kEIPM_OK,"生成成功，点击完成退出。");
    }else{
        return ERROR(kEIPM_ERR_MALFORMED, "无法写入文件。");
    }
}

keipm_err_t keipm_set_UserCA(const char* UserCA_Path,const char* elf_Path){
    (void)UserCA_Path;
    (void)elf_Path;
    if(rand() & 1){
        return ERROR(kEIPM_OK,"生成成功，点击完成退出。");
    }else{
        return ERROR(kEIPM_ERR_MALFORMED,"无法写入文件。");
    }
}

keipm_err_t keipm_create_PrivateKey(const char *privateKeyPath){
    (void)privateKeyPath;
    if(1|| rand() & 1){
        return ERROR(kEIPM_OK,"生成私钥成功，点击完成退出。");
    }else{
        return ERROR(kEIPM_ERR_MALFORMED,"生成私钥失败，无法写入文件。");
    }
}
keipm_err_t keipm_create_PublicKey(const char* publicKeyPath, const char* privateKeyPath){
    (void)publicKeyPath;
    (void)privateKeyPath;
    if(rand() & 1){
        return ERROR(kEIPM_OK,"生成公钥成功，点击完成退出。");
    }else{
        return ERROR(kEIPM_ERR_MALFORMED,"生成公钥失败，无法写入文件。");
    }
}

keipm_err_t keipm_create_rootCA(const char *rootCA_Path, const RootCa *rootca){
    (void)rootCA_Path;
    (void)rootca;
    if(rand() & 1){
        return ERROR(kEIPM_OK,"生成根证书成功，点击完成退出。");
    }else{
        return ERROR(kEIPM_ERR_MALFORMED,"生成根证书失败，无法写入文件。");
    }
}

keipm_err_t keipm_create_userCA(const char *out_cert_path,const UserCa *userca){
    (void)out_cert_path;
    (void)userca;
    if(rand() & 1){
        return ERROR(kEIPM_OK,"生成用户证书成功，点击完成退出。");
    }else{
        return ERROR(kEIPM_ERR_MALFORMED,"生成用户证书失败，无法写入文件。");
    }
}

#endif
