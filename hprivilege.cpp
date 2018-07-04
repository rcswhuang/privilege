#include "hprivilege.h"

HPrivilege::HPrivilege()
{

}

HPrivilege::~HPrivilege()
{

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
