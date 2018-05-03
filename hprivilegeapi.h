#ifndef HPRIVILEGEAPI_H
#define HPRIVILEGEAPI_H
/*
 * api接口和相关结构定义
*/
#include<QtGlobal>
#ifdef __cplusplus
extern "C"
{
#endif
namespace _EnumPriviValue {
    enum privi
    {
        PeopleManagerPrivi          = 0x00000001L, //人员管理
        ConfigureToolPrivi          = 0x00000002L, //五防组态
        GraphEditorPrivi            = 0x00000004L, //画面编辑
        SystemSetPrivi              = 0x00000008L, //系统设置
        ManualSetPrivi              = 0x00000010L, //人工设置
        GroupOnOffPrivi             = 0x00000020L, //间隔五防投退
        OperTicketBrowserPrivi      = 0x00000040L, //操作票浏览
        OperTicketEditorPrivi       = 0x00000080L, //操作票编辑
        OperTicketDeletePrivi       = 0x00000100L, //操作票删除
        OperTicketCancelPrivi       = 0x00000200,  //操作票取消
        OperTicketRunPrivi          = 0x00000400L, //操作票执行
        OperTicketGuardPrivi        = 0x00000800L, //操作票监护
        ModelTicketToRunPrivi       = 0x00001000L, //模板票转执行
        TempTicketToRunPrivi        = 0x00002000L, //临时票或者编辑票转执行
        WorkTicketManagerPrivi      = 0x00004000L, //操作票(工作票)管理
        WorkTicketModelManagerPrivi = 0x00008000L, //工作票(操作票)模板管理
        GiveOrderPrivi              = 0x00010000L, //下令人
        PrepareOrderPrivi           = 0x00020000L, //预令人
        DutyManagerPrivi            = 0x00040000L, //值班负责人
        DutyLeaderPrivi             = 0x00080000L, //值长

        SystemLoginPrivi            = 0x01000000L, //系统登录
        SysetmExitPrivi             = 0x02000000L  //系统退出
    };
}

typedef _EnumPriviValue::privi HPrivilege;

#define allPrivi  (HPrivilege::PeopleManagerPrivi | HPrivilege::ConfigureToolPrivi | HPrivilege::GraphEditorPrivi | HPrivilege::SystemSetPrivi \
                   )
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

}User;
#ifdef __cplusplus
}
#endif
#endif // HPRIVILEGEAPI_H
