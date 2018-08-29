#include "hprivilege.h"
#include <QFile>
#include <QDataStream>
#include "hcheckprividlg.h"
#include "hprivilegeset.h"

HPrivilege::HPrivilege()
{
    loadData();
    initSysConfig();
    char szPriFile[256];
    getDataFilePath(DFPATH_DATA,szPriFile);
    m_strPriFile = QString(szPriFile) + "/" + "privilege.dat";
}

HPrivilege::~HPrivilege()
{
    while(!m_pUserList.isEmpty())
        delete (User*)m_pUserList.takeFirst();
    while (!m_pGroupList.isEmpty()) {
        delete (Group*)m_pGroupList.takeFirst();
    }
    m_pUserList.clear();
    m_pGroupList.clear();
}

bool HPrivilege::loadData()
{
    if(m_strPriFile.isEmpty())
        return false;
    QFile file(m_strPriFile);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QDataStream stream(&file);
    quint64 magic;
    stream>>magic;
    if(magic != 0xA0B00C0D)
        return false;
    quint16 wGroupCount;
    stream>>wGroupCount;
    for(int i = 0; i < wGroupCount;i++)
    {
        Group* group = new Group;
        if(!group)
            return false;
        quint16 n16;
        stream>>n16;
        group->wGroupID = n16;
        QString s;
        stream>>s;
        group->strGroupName = s;
        quint64 n64;
        stream>>n64;
        group->lGroupPrivilege = n64;
        bool b;
        stream>>b;
        group->bUnitePrivilege = b;
        m_pGroupList.append(group);
    }
    quint16 wUserCount;
    stream>>wUserCount;
    for(int i = 0; i < wUserCount;i++)
    {
        User* user = new User;
        if(!user)
            return false;
        quint16 n16;
        stream>>n16;
        user->wUserID = n16;
        QString s;
        stream>>s;
        user->strUserName = s;
        quint64 n64;
        stream>>n64;
        user->lGroupPrivilege = n64;
        stream>>s;
        user->strUserPwd = s;
        stream>>n16;
        user->wGroupID = n16;
        m_pUserList.append(user);
    }
    return true;
}

bool HPrivilege::saveData()
{
    if(m_strPriFile.isEmpty())
        return false;
    QFile file(m_strPriFile);
    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QDataStream stream(&file);
    quint64 magic = 0xA0B00C0D;
    stream<<(quint64)magic;
    quint16 wGroupCount = m_pGroupList.count();
    stream<<(quint16)wGroupCount;
    for(int i = 0;i < m_pGroupList.count();i++)
    {
        Group* group = (Group*)m_pGroupList[i];
        if(!group) return false;
        stream<<(quint16)group->wGroupID;
        stream<<(QString)group->strGroupName;
        stream<<(quint64)group->lGroupPrivilege;
        stream<<(bool)group->bUnitePrivilege;
    }
    quint16 wUserCount = m_pUserList.count();
    stream<<(quint16)wUserCount;
    for(int i = 0;i < m_pUserList.count();i++)
    {
        User* user = (User*)m_pUserList[i];
        if(!user)
            return false;
        stream<<(quint16)user->wUserID;
        stream<<(QString)user->strUserName;
        stream<<(quint64)user->lGroupPrivilege;
        stream<<(QString)user->strUserPwd;
        stream<<(quint16)user->wGroupID;
    }
    return true;
}

Group* HPrivilege::addGroup(const QString& strGroupName)
{
    Group* group = findGroup(strGroupName);
    if(group != NULL)
        return group;
    quint16 wGroupID = 0;
    while(findGroup(wGroupID) != NULL)
        wGroupID++;

    group = new Group;
    if(!group) return NULL;
    //组内统一权限不需要开始设置
    group->strGroupName = strGroupName;
    group->wGroupID = wGroupID;
    group->bUnitePrivilege = true;
    group->lGroupPrivilege = HPrivilege::defaulPrivi;
    if(!strGroupName.compare(ADMINGROUP))
        group->lGroupPrivilege = HPrivilege::AllPrivi;
    m_pGroupList.append(group);
    return group;
}

User* HPrivilege::addUser(quint16 wGroupID,const QString& strUserName,const QString& strUserPwd)
{
    Group* group = findGroup(wGroupID);
    if(NULL == group) return NULL;
    User* user = findUser(wGroupID,strUserName);
    if(user != NULL)
        return user;
    quint16 wUserID = 0;
    while(findUser(wUserID) != NULL)
        wUserID++;
    user = new User;
    if(user == NULL)
        return NULL;
    user->wGroupID = wGroupID;
    user->wUserID = wUserID;
    user->strUserName = strUserName;
    user->strUserPwd = strUserPwd;
    user->lGroupPrivilege = group->lGroupPrivilege;
    m_pUserList.append(user);
    return user;
}

Group* HPrivilege::findGroup(const QString& groupName)
{
    Group* group = NULL;
    for(int i = 0; i < m_pGroupList.count(); i++)
    {
        group = m_pGroupList[i];
        if(group->strGroupName == groupName)
            return group;
    }
    return NULL;
}

Group* HPrivilege::findGroup(quint16 groupID)
{
    Group* group = NULL;
    for(int i = 0; i < m_pGroupList.count(); i++)
    {
        group = m_pGroupList[i];
        if(group && group->wGroupID == groupID)
            return group;
    }
    return NULL;
}

User* HPrivilege::findUser(quint16 groupID,const QString& userName)
{
    Group* group = findGroup(groupID);
    if(!group)
        return NULL;
    User* user = NULL;
    for(int i = 0; i < m_pUserList.count(); i++)
    {
        user = m_pUserList[i];
        if(user)
        {
            if(user->strUserName == userName)
                return user;
        }
    }
    return NULL;
}

User* HPrivilege::findUser(quint16 userID)
{
    User* user = NULL;
    for(int i = 0; i < m_pUserList.count(); i++)
    {
        user = m_pUserList[i];
        if(user)
        {
            if(user->wUserID == userID)
                return user;
        }
    }
    return NULL;
}

bool HPrivilege::delGroup(quint16 groupID)
{
    Group* group = findGroup(groupID);
    if(!group) return false;
    QList<User*>::iterator it = m_pUserList.begin();
    for(;it!=m_pUserList.end();++it)
    {
        User* user = *it;
        m_pUserList.removeOne(user);
        delete user;
        user = NULL;
    }
    m_pGroupList.removeOne(group);
    delete group;
    group = NULL;
    return true;
}

bool HPrivilege::delUser(quint16 userID)
{
    User* user = findUser(userID);
    if(!user) return false;
    m_pUserList.removeOne(user);
    delete user;
    user = NULL;
    return true;
}

bool HPrivilege::checkPrivilege(quint64 lPrivilege,QString& strUserName,QString& strTitle)
{
    HCheckPriviDlg dlg;
    dlg.m_strTitle = strTitle;
    dlg.m_lPrivilege = lPrivilege;
    if(QDialog::Accepted == dlg.exec())
    {
        strUserName = dlg.m_strUserName;
        return true;
    }
    return false;
}

bool HPrivilege::setPrivilege()
{
    QString strUserName;
    QString strTitle = QStringLiteral("权限管理");
    if(!checkPrivilege(HPrivilege::PeopleManagerPrivi,strUserName,strTitle));
        return false;
    HPrivilegeSet dlg;
    dlg.exec();
    return true;
}
