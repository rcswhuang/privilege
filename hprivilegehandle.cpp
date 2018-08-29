#include "hprivilegeapi.h"
#include "hprivilege.h"
#include "time.h"
HPrivilege m_privi;
QString g_strUserName;
quint64 g_lPrivilege;
time_t g_startLogintime;
//校验
bool PRIV_EXPORT checkPrivilege(quint64 lPrivilege,QString& strUserName,QString& strTitle)
{
    //注意还要增加口令有效性的判断
    if(!g_strUserName.isEmpty() && ((g_lPrivilege & lPrivilege) == lPrivilege))
    {
        time_t t;
        time(&t);
        QVariant var;
        getSettingValue(SYS_SET_NORMAL,SYS_PASSWORD_VALID_TIME,var);
        int n = var.toInt();//配置文档里面读取有效时间
        if(n > 0)
        {
            if(t - g_startLogintime < n)
            {
                strUserName = g_strUserName;
                return true;
            }
        }
    }
    bool b = m_privi.checkPrivilege(lPrivilege,strUserName,strTitle);
    if(b)
    {
        time(&g_startLogintime);
        if(!g_strUserName.isEmpty())
            g_strUserName.clear();
        g_strUserName = strUserName;
    }
    return b;
}

//权限设置
bool PRIV_EXPORT setPrivilege()
{
    return m_privi.setPrivilege();
}
