#include "hprivilegeapi.h"
#include "hprivilege.h"
HPrivilege m_privi;
//校验
bool PRIV_EXPORT checkPrivilege(quint64 lPrivilege,QString& strUserName,QString& strTitle)
{
    //注意还要增加口令有效性的判断
    bool b = m_privi.checkPrivilege(lPrivilege,strUserName,strTitle);
    return b;
}

//权限设置
bool PRIV_EXPORT setPrivilege()
{

}
