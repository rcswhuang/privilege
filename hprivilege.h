#ifndef HPRIVILEGE_H
#define HPRIVILEGE_H

#include <QObject>
#include <QList>
#include <QFlags>
#include "hprivilegeapi.h"
/*
 * 完成权限文件的读取和存储
*/
class HPrivilege
{
public:
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
        PrintSetPrivi               = 0x00100000L, //打印设置
        SystemLoginPrivi            = 0x01000000L, //系统登录
        SystemExitPrivi             = 0x02000000L,  //系统退出

        AllPrivi  =  PeopleManagerPrivi | ConfigureToolPrivi | GraphEditorPrivi | SystemSetPrivi |  \
        ManualSetPrivi | GroupOnOffPrivi | OperTicketBrowserPrivi | OperTicketEditorPrivi | OperTicketDeletePrivi | \
        OperTicketCancelPrivi | OperTicketRunPrivi | OperTicketGuardPrivi | ModelTicketToRunPrivi | TempTicketToRunPrivi | \
        WorkTicketManagerPrivi | WorkTicketModelManagerPrivi | GiveOrderPrivi | PrepareOrderPrivi | PrintSetPrivi | \
        DutyManagerPrivi | DutyLeaderPrivi | SystemLoginPrivi | SystemExitPrivi,

        defaulPrivi = ConfigureToolPrivi | GraphEditorPrivi | SystemSetPrivi |  \
        ManualSetPrivi | GroupOnOffPrivi | OperTicketBrowserPrivi | OperTicketEditorPrivi | \
        WorkTicketManagerPrivi | WorkTicketModelManagerPrivi | SystemLoginPrivi | SystemExitPrivi

    };
    Q_DECLARE_FLAGS(privis,privi)
public:
    HPrivilege();
    ~HPrivilege();
public:
    void loadData();
    void saveData();

public:
    //组相关
    Group* addGroup(const QString& strGroupName);
    User* addUser(quint16 wGroupID,const QString& strUserName,const QString& strUserPwd);

    Group* findGroup(const QString& groupName);
    Group* findGroup(quint16 groupID);
    User* findUser(quint16 groupID,const QString& userName);
    User* findUser(quint16 userID);

    bool delGroup(quint16 groupID);
    bool delUser(quint16 userID);
public:
    QList<Group*> m_pGroupList;
    QList<User*> m_pUserList;


};
Q_DECLARE_OPERATORS_FOR_FLAGS(HPrivilege::privis)
#endif // HPRIVDOC_H
