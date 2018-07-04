#ifndef HPRIVILEGESET_H
#define HPRIVILEGESET_H

#include <QDialog>
#include "hprivilegeapi.h"
class HPrivilege;
namespace Ui {
class HPrivilegeSet;
}

class HPrivilegeSet : public QDialog
{
    Q_OBJECT

public:
    explicit HPrivilegeSet(QWidget *parent = 0);
    ~HPrivilegeSet();

public:
    void initPrivilegeSet();
    void updatePrivilege(quint64 lGroupPrivilege,bool bUnitGroupPrivi = true);
    void setPrivilege(quint64 lPrivilge,Group* group,User* user);
    void setGroupPrivilege(quint64 lPrivilege,Group* group);
    void setUserPrivilege(quint64 lPrivilege,User* user);
public slots:
    void treeRightClick();
    void on_addGroup();
    void on_delGroup();
    void on_reGroupName();
    void on_addUser();
    void on_delUser();
    void on_reNameUser();
    void on_modifyPwd();

    void on_SystemLoginBox();
    void on_SysetmExitBox();
    void on_PeopleManagerBox();
    void on_ConfigureToolBox();
    void on_GraphEditorBox();
    void on_SystemSetBox();
    void on_OperTicketBrowserBox();
    void on_OperTicketEditorBox();
    void on_OperTicketDeleteBox();
    void on_OperTicketCancelBox();
    void on_OperTicketRunBox();
    void on_OperTicketGuardBox();
    void on_ModelTicketToRunBox();
    void on_TempTicketToRunBox();
    void on_GiveOrderBox();
    void on_DutyManagerBox();
    void on_DutyLeaderBox();
    void on_PrintSetBox();
    void on_ManualSetBox();
    void on_GroupOnOffBox();
    void on_WorkTicketManagerBox();
    void on_WorkTicketModelManagerBox();
private:
    Ui::HPrivilegeSet *ui;
    QAction* addGroupAct;
    QAction* delGroupAct;
    QAction* reGroupNameAct;
    QAction* addUserAct;
    QAction* delUserAct;
    QAction* reNameAct;
    QAction* modifyPwdAct;
    HPrivilege* m_pPrivilege;
    Group* m_Group;
    User* m_User;
};

#endif // HPRIVILEGESET_H
