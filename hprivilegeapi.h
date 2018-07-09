#ifndef HPRIVILEGEAPI_H
#define HPRIVILEGEAPI_H
#if defined(_MSC_VER) &&(_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif
/*
 * api接口和相关结构定义
*/
#include<QtGlobal>
#include<QString>
#include "hprivexport.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define ADMINGROUP "系统管理组"
#define ADMINUSER  "系统管理员"
#define ADMINPWD   "hyx-2018"
//定义管理组结构
typedef struct _tagGroup
{
    quint16 wGroupID;
    QString strGroupName;
    quint64 lGroupPrivilege; //组权限
    bool bUnitePrivilege; //组统一设置标志
}Group;

//定义用户结构
typedef struct _tagUser
{
    quint16 wGroupID;
    quint16 wUserID;
    QString strUserName;
    QString strUserPwd;
    quint64 lGroupPrivilege; //组权限
}User;

//校验
bool PRIV_EXPORT checkPrivilege(quint64 lPrivilege,QString& strUserName,QString& strTitle);

//权限设置
bool PRIV_EXPORT setPrivilege();


#ifdef __cplusplus
}
#endif
#endif // HPRIVILEGEAPI_H
