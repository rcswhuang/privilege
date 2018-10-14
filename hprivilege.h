#ifndef HPRIVILEGE_H
#define HPRIVILEGE_H

#include <QObject>
#include <QList>
//#include <QFlags>
#include "hprivilegeapi.h"
#include "hfileapi.h"
#include "hconfigapi.h"

#define TREE_PRIVSET_ROOT 0
#define TREE_PRIVSET_GROUP 1
#define TREE_PRIVSET_USER 2
#define ADMINGROUPID 9999
#define ADMINUSERID 8888

/*
 * 完成权限文件的读取和存储
*/
class HPrivilege
{
public:
    HPrivilege();
    ~HPrivilege();
public:
    bool loadData();
    bool saveData();
    bool makePrivilegeFile();
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
    bool checkPrivilege(quint64 lPrivilege,QString& strUserName,QString& strTitle);
    bool PRIV_EXPORT setPrivilege();

public:
    QList<Group*> m_pGroupList;
    QList<User*> m_pUserList;
private:
    QString m_strPriFile;

};
#endif // HPRIVDOC_H
