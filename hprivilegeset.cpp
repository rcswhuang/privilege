#if defined(_MSC_VER) &&(_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif
#include "hprivilegeset.h"
#include "ui_privilegeset.h"
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QMessageBox>
#include "hprivilege.h"
#include "hadduserdlg.h"
#include "hmodifypwddlg.h"
extern HPrivilege m_privi;


HPrivilegeSet::HPrivilegeSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HPrivilegeSet)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    initPrivilegeSet();
    setWindowTitle("权限设置");
}

HPrivilegeSet::~HPrivilegeSet()
{
    delete ui;
}

void HPrivilegeSet::initPrivilegeSet()
{
    connect(ui->manTreeWidget,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(treeRightClick()));
    addGroupAct = new QAction("增加组",this);
    connect(addGroupAct,SIGNAL(triggered(bool)),this,SLOT(on_addGroup()));
    delGroupAct = new QAction("删除组",this);
    connect(delGroupAct,SIGNAL(triggered(bool)),this,SLOT(on_delGroup()));
    reGroupNameAct = new QAction("修改组名",this);
    connect(reGroupNameAct,SIGNAL(triggered(bool)),this,SLOT(on_reGroupName()));
    addUserAct = new QAction("增加组用户",this);
    connect(addUserAct,SIGNAL(triggered(bool)),this,SLOT(on_addUser()));
    delUserAct = new QAction("删除组用户",this);
    connect(delUserAct,SIGNAL(triggered(bool)),this,SLOT(on_delUser()));
    reNameAct = new QAction("修改用户名",this);
    connect(reNameAct,SIGNAL(triggered(bool)),this,SLOT(on_reNameUser()));
    modifyPwdAct = new QAction("修改密码",this);
    connect(modifyPwdAct,SIGNAL(triggered(bool)),this,SLOT(on_modifyPwd()));

    connect(ui->SystemLoginBox,SIGNAL(clicked(bool)),this,SLOT(on_SystemLoginBox()));
    connect(ui->SystemExitBox,SIGNAL(clicked(bool)),this,SLOT(on_SysetmExitBox()));
    connect(ui->PeopleManagerBox,SIGNAL(clicked(bool)),this,SLOT(on_PeopleManagerBox()));
    connect(ui->ConfigureToolBox,SIGNAL(clicked(bool)),this,SLOT(on_ConfigureToolBox()));
    connect(ui->GraphEditorBox,SIGNAL(clicked(bool)),this,SLOT(on_GraphEditorBox()));
    connect(ui->OperTicketBrowserBox,SIGNAL(clicked(bool)),this,SLOT(on_OperTicketBrowserBox()));
    connect(ui->OperTicketEditorBox,SIGNAL(clicked(bool)),this,SLOT(on_OperTicketEditorBox()));
    connect(ui->OperTicketDeleteBox,SIGNAL(clicked(bool)),this,SLOT(on_OperTicketDeleteBox()));
    connect(ui->OperTicketCancelBox,SIGNAL(clicked(bool)),this,SLOT(on_OperTicketCancelBox()));
    connect(ui->OperTicketRunBox,SIGNAL(clicked(bool)),this,SLOT(on_OperTicketRunBox()));
    connect(ui->OperTicketGuardBox,SIGNAL(clicked(bool)),this,SLOT(on_OperTicketGuardBox()));
    connect(ui->ModelTicketToRunBox,SIGNAL(clicked(bool)),this,SLOT(on_ModelTicketToRunBox()));
    connect(ui->TempTicketToRunBox,SIGNAL(clicked(bool)),this,SLOT(on_TempTicketToRunBox()));
    connect(ui->GiveOrderBox,SIGNAL(clicked(bool)),this,SLOT(on_GiveOrderBox()));
    connect(ui->DutyManagerBox,SIGNAL(clicked(bool)),this,SLOT(on_DutyManagerBox()));
    connect(ui->DutyLeaderBox,SIGNAL(clicked(bool)),this,SLOT(on_DutyLeaderBox()));
    connect(ui->PrintSetBox,SIGNAL(clicked(bool)),this,SLOT(on_PrintSetBox()));
    connect(ui->ManualSetBox,SIGNAL(clicked(bool)),this,SLOT(on_ManualSetBox()));
    connect(ui->GroupOnOffBox,SIGNAL(clicked(bool)),this,SLOT(on_GroupOnOffBox()));
    connect(ui->WorkTicketManagerBox,SIGNAL(clicked(bool)),this,SLOT(on_WorkTicketManagerBox()));
    connect(ui->WorkTicketModelManagerBox,SIGNAL(clicked(bool)),this,SLOT(on_WorkTicketModelManagerBox()));
    connect(ui->UnitPrivilegeBox,SIGNAL(clicked(bool)),this,SLOT(on_UnitPrivilegeBox()));

    connect(ui->saveBtn,SIGNAL(clicked(bool)),this,SLOT(on_saveBtn()));
    connect(ui->quitBtn,SIGNAL(clicked(bool)),this,SLOT(on_quitBtn()));

    QTreeWidgetItem* item = new QTreeWidgetItem(ui->manTreeWidget,TREE_PRIVSET_ROOT);
    item->setText(0,"权限设置");
    //如果初始就定义系统管理组和1个系统管理员，初始密码为空
    for(int i = 0; i < m_privi.m_pGroupList.count();i++)
    {
        Group* group = (Group*)m_privi.m_pGroupList[i];
        if(!group) return;
        QTreeWidgetItem* item1 = new QTreeWidgetItem(item,TREE_PRIVSET_GROUP);
        item1->setText(0,group->strGroupName);
        item1->setData(0,Qt::UserRole,group->wGroupID);
        item->addChild(item1);
        for(int j = 0; j < m_privi.m_pUserList.count();j++)
        {
            User* user = (User*)m_privi.m_pUserList[j];
            if(!user) return;
            if(user->wGroupID == group->wGroupID)
            {
                QTreeWidgetItem *userItem = new QTreeWidgetItem(item1,TREE_PRIVSET_USER);
                userItem->setData(0,Qt::UserRole,user->wUserID);//userID是唯一的
                userItem->setText(0,user->strUserName);
                item1->addChild(userItem);
            }
        }
    }
    ui->manTreeWidget->expandItem(item);

}

void HPrivilegeSet::treeRightClick()
{
    bool bRight = (QGuiApplication::mouseButtons() & Qt::RightButton);
    QTreeWidgetItem* item = ui->manTreeWidget->currentItem();
    if(bRight)
    {
        if(item->type() == TREE_PRIVSET_ROOT)
        {
            QMenu* menu = new QMenu;
            menu->addAction(addGroupAct);
            menu->exec(QCursor::pos());
        }
        else if(item->type() == TREE_PRIVSET_GROUP) //组
        {
            QMenu* menu = new QMenu;
            menu->addAction(addUserAct);
            menu->addAction(reGroupNameAct);
            menu->addSeparator();
            menu->addAction(delGroupAct);
            menu->exec(QCursor::pos());
        }
        else if(item->type() == TREE_PRIVSET_USER)//用户
        {
            QMenu* menu = new QMenu;
            menu->addAction(modifyPwdAct);
            menu->addAction(reNameAct);
            menu->addSeparator();
            menu->addAction(delUserAct);
            menu->exec(QCursor::pos());
        }
    }
    else
    {
        m_User = NULL;
        m_Group = NULL;
        if(TREE_PRIVSET_GROUP == item->type())
        {
            quint16 wGroupID = item->data(0,Qt::UserRole).toUInt();
            Group* group = m_privi.findGroup(wGroupID);
            if(!group)
                return;
            ui->UnitPrivilegeBox->setVisible(true);
            ui->UnitPrivilegeBox->setChecked(group->bUnitePrivilege);
            updatePrivilege(group->lGroupPrivilege);
            m_Group = group;
        }
        else if(TREE_PRIVSET_USER == item->type())
        {
            quint16 wUserID = item->data(0,Qt::UserRole).toUInt();
            User* user = m_privi.findUser(wUserID);
            if(NULL == user)
                return;
            QTreeWidgetItem* parentItem = item->parent();
            quint16 wGroupID = parentItem->data(0,Qt::UserRole).toUInt();
            Group* group = m_privi.findGroup(wGroupID);
            if(NULL == group)
                return;
            ui->UnitPrivilegeBox->setVisible(false);
            if(group->bUnitePrivilege)
            {
                updatePrivilege(group->lGroupPrivilege,false);
            }
            else
            {
                updatePrivilege(user->lGroupPrivilege);
            }
            m_User = user;
        }
    }
}

void HPrivilegeSet::updatePrivilege(quint64 lGroupPrivilege,bool bUnitGroupPrivi)
{
    ui->SystemLoginBox->setEnabled(bUnitGroupPrivi);
    ui->SystemExitBox->setEnabled(bUnitGroupPrivi);
    ui->PeopleManagerBox->setEnabled(bUnitGroupPrivi);
    ui->ConfigureToolBox->setEnabled(bUnitGroupPrivi);
    ui->GraphEditorBox->setEnabled(bUnitGroupPrivi);
    ui->SystemSetBox->setEnabled(bUnitGroupPrivi);
    ui->OperTicketBrowserBox->setEnabled(bUnitGroupPrivi);
    ui->OperTicketEditorBox->setEnabled(bUnitGroupPrivi);
    ui->OperTicketDeleteBox->setEnabled(bUnitGroupPrivi);
    ui->OperTicketCancelBox->setEnabled(bUnitGroupPrivi);
    ui->OperTicketRunBox->setEnabled(bUnitGroupPrivi);
    ui->OperTicketGuardBox->setEnabled(bUnitGroupPrivi);
    ui->ModelTicketToRunBox->setEnabled(bUnitGroupPrivi);
    ui->TempTicketToRunBox->setEnabled(bUnitGroupPrivi);
    ui->GiveOrderBox->setEnabled(bUnitGroupPrivi);
    ui->DutyManagerBox->setEnabled(bUnitGroupPrivi);
    ui->DutyLeaderBox->setEnabled(bUnitGroupPrivi);
    ui->PrintSetBox->setEnabled(bUnitGroupPrivi);
    ui->ManualSetBox->setEnabled(bUnitGroupPrivi);
    ui->GroupOnOffBox->setEnabled(bUnitGroupPrivi);
    ui->WorkTicketManagerBox->setEnabled(bUnitGroupPrivi);
    ui->WorkTicketModelManagerBox->setEnabled(bUnitGroupPrivi);
    ui->SystemLoginBox->setChecked((lGroupPrivilege & Ht::SystemLoginPrivi) == Ht::SystemLoginPrivi);
    ui->SystemExitBox->setChecked((lGroupPrivilege & Ht::SystemExitPrivi) == Ht::SystemExitPrivi);
    ui->PeopleManagerBox->setChecked((lGroupPrivilege & Ht::PeopleManagerPrivi) == Ht::PeopleManagerPrivi);
    ui->ConfigureToolBox->setChecked((lGroupPrivilege & Ht::ConfigureToolPrivi) == Ht::ConfigureToolPrivi);
    ui->GraphEditorBox->setChecked((lGroupPrivilege & Ht::GraphEditorPrivi) == Ht::GraphEditorPrivi);
    ui->SystemSetBox->setChecked((lGroupPrivilege & Ht::SystemSetPrivi) == Ht::SystemSetPrivi);
    ui->OperTicketBrowserBox->setChecked((lGroupPrivilege & Ht::OperTicketBrowserPrivi) == Ht::OperTicketBrowserPrivi);
    ui->OperTicketEditorBox->setChecked((lGroupPrivilege & Ht::OperTicketEditorPrivi) == Ht::OperTicketEditorPrivi);
    ui->OperTicketDeleteBox->setChecked((lGroupPrivilege & Ht::OperTicketDeletePrivi) == Ht::OperTicketDeletePrivi);
    ui->OperTicketCancelBox->setChecked((lGroupPrivilege & Ht::OperTicketCancelPrivi) == Ht::OperTicketCancelPrivi);
    ui->OperTicketRunBox->setChecked((lGroupPrivilege & Ht::OperTicketRunPrivi) == Ht::OperTicketRunPrivi);
    ui->OperTicketGuardBox->setChecked((lGroupPrivilege & Ht::OperTicketGuardPrivi) == Ht::OperTicketGuardPrivi);
    ui->ModelTicketToRunBox->setChecked((lGroupPrivilege & Ht::ModelTicketToRunPrivi) == Ht::ModelTicketToRunPrivi);
    ui->TempTicketToRunBox->setChecked((lGroupPrivilege & Ht::TempTicketToRunPrivi) == Ht::TempTicketToRunPrivi);
    ui->GiveOrderBox->setChecked((lGroupPrivilege & Ht::GiveOrderPrivi) == Ht::GiveOrderPrivi);
    ui->DutyManagerBox->setChecked((lGroupPrivilege & Ht::DutyManagerPrivi) == Ht::DutyManagerPrivi);
    ui->DutyLeaderBox->setChecked((lGroupPrivilege & Ht::DutyLeaderPrivi) == Ht::DutyLeaderPrivi);
    ui->PrintSetBox->setChecked((lGroupPrivilege & Ht::PrintSetPrivi) == Ht::PrintSetPrivi);
    ui->ManualSetBox->setChecked((lGroupPrivilege & Ht::ManualSetPrivi) == Ht::ManualSetPrivi);
    ui->GroupOnOffBox->setChecked((lGroupPrivilege & Ht::GroupOnOffPrivi) == Ht::GroupOnOffPrivi);
    ui->WorkTicketManagerBox->setChecked((lGroupPrivilege & Ht::WorkTicketManagerPrivi) == Ht::WorkTicketManagerPrivi);
    ui->WorkTicketModelManagerBox->setChecked((lGroupPrivilege & Ht::WorkTicketModelManagerPrivi) == Ht::WorkTicketModelManagerPrivi);

}

void HPrivilegeSet::on_addGroup()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("组名设置"),tr("组名称:"), QLineEdit::Normal,"", &ok);
    if (!ok || text.isEmpty())
      return;
    Group* group = m_privi.findGroup(text);
    if(NULL != group)
    {
        QMessageBox::warning(NULL,"警告","组已经存在!",QMessageBox::Ok);
        return;
        //组名已存在
    }
    group = m_privi.addGroup(text);
    if(NULL == group)
    {
        //增加组名失败
    }
    QTreeWidgetItem* item = ui->manTreeWidget->currentItem();
    QTreeWidgetItem* childItem = new QTreeWidgetItem(item,1);
    if(NULL == childItem || NULL == item)
    {
        return;
    }
    childItem->setText(0,group->strGroupName);
    childItem->setData(0,Qt::UserRole,group->wGroupID);
    item->addChild(childItem);
}

void HPrivilegeSet::on_delGroup()
{
    if(QMessageBox::No == QMessageBox::warning(NULL,"警告","删除组及删除组内所有成员,确定删除该组?",QMessageBox::Yes|QMessageBox::No))
        return;
    QTreeWidgetItem* item = ui->manTreeWidget->currentItem();
    if(NULL == item || TREE_PRIVSET_GROUP != item->type())
    {
        return;
    }
    //确认删除？,将删除组内所有组成员
    quint16 wGroupID = item->data(0,Qt::UserRole).toUInt();
    if(wGroupID == ADMINGROUPID)
    {
        //系统管理组是不能删除
        QMessageBox::warning(NULL,"警告","系统组无法删除！",QMessageBox::Ok);
        return;
    }
    Group* group = m_privi.findGroup(wGroupID);
    if(NULL == group)
    {
        return;
    }
    m_privi.delGroup(group->wGroupID);

    QTreeWidgetItem* parentItem = item->parent();
    if(NULL == parentItem)
    {
        return;
    }
    parentItem->removeChild(item);
    QList<QTreeWidgetItem*> childItems = item->takeChildren();
    while(!childItems.isEmpty())
        delete (QTreeWidgetItem*)childItems.takeFirst();
    if(item)
    {
        delete item;
        item = NULL;
    }
    ui->manTreeWidget->setCurrentItem(parentItem);
}

void HPrivilegeSet::on_reGroupName()
{
    QTreeWidgetItem* item = ui->manTreeWidget->currentItem();
    if(NULL == item || TREE_PRIVSET_GROUP != item->type())
    {
        return;
    }
    quint16 wGroupID = item->data(0,Qt::UserRole).toUInt();
    Group* group = m_privi.findGroup(wGroupID);
    if(NULL == group)
    {
        return;
    }
    QString strGroup = group->strGroupName;
    bool ok;
    QString text = QInputDialog::getText(this, tr("组名设置"),tr("组名称:"), QLineEdit::Normal,strGroup, &ok);
    if (!ok || text.isEmpty())
      return;
    Group* group1 = m_privi.findGroup(text);
    if(NULL != group1)
    {
        QMessageBox::warning(NULL,"警告","组名重复！",QMessageBox::Ok);
        return;
    }
    group->strGroupName = text;
    item->setText(0,text);
}

void HPrivilegeSet::on_addUser()
{
    QTreeWidgetItem* item = ui->manTreeWidget->currentItem();
    if(NULL == item || TREE_PRIVSET_GROUP != item->type())
    {
        return;
    }
    quint16 wGroupID = item->data(0,Qt::UserRole).toUInt();
    QString strGroupName = item->text(0);
    HAddUserDlg dlg(strGroupName,wGroupID,this);
    if(QDialog::Accepted ==  dlg.exec())
    {
        QString strUser = dlg.strName;
        QString strPwd = dlg.strPwd;
        User* user = m_privi.addUser(wGroupID,strUser,strPwd);
        if(NULL == user)
        {
            return;
        }
        QTreeWidgetItem* childItem = new QTreeWidgetItem(item,TREE_PRIVSET_USER);
        if(NULL == childItem || NULL == item)
        {
            return;
        }
        childItem->setText(0,user->strUserName);
        childItem->setData(0,Qt::UserRole,user->wUserID);
        item->addChild(childItem);
    }
}

void HPrivilegeSet::on_delUser()
{
    if(QMessageBox::No == QMessageBox::warning(NULL,"警告","确定删除该用户?",QMessageBox::Yes|QMessageBox::No))
        return;
    QTreeWidgetItem* item = ui->manTreeWidget->currentItem();
    if(NULL == item || TREE_PRIVSET_USER != item->type())
    {
        return;
    }
    //确认删除？,将删除组内所有组成员
    quint16 wUserID = item->data(0,Qt::UserRole).toUInt();
    if(wUserID == ADMINUSERID)
    {
        //系统管理组是不能删除
        QMessageBox::warning(NULL,"警告","系统管理员不能删除!",QMessageBox::Ok);
        return;
    }
    User* user = m_privi.findUser(wUserID);
    if(NULL == user)
    {

    }
    m_privi.delUser(user->wUserID);

    QTreeWidgetItem* parentItem = item->parent();
    if(NULL == parentItem)
    {
        return;
    }
    parentItem->removeChild(item);
    if(item)
    {
        delete item;
        item = NULL;
    }
    ui->manTreeWidget->setCurrentItem(parentItem);
}

void HPrivilegeSet::on_reNameUser()
{
    QTreeWidgetItem* item = ui->manTreeWidget->currentItem();
    if(NULL == item || TREE_PRIVSET_USER != item->type())
    {
        return;
    }
    quint16 wUserID = item->data(0,Qt::UserRole).toUInt();
    User* user = m_privi.findUser(wUserID);
    if(NULL == user)
    {
        return;
    }
    if(wUserID == ADMINUSERID)
    {
        //系统管理组是不能删除
        QMessageBox::warning(NULL,"警告","系统管理员不能改名!",QMessageBox::Ok);
        return;
    }
    QString strUser = user->strUserName;
    bool ok;
    QString text = QInputDialog::getText(this, tr("用户名设置"),tr("用户名:"), QLineEdit::Normal,strUser, &ok);
    if (!ok || text.isEmpty())
      return;
    QTreeWidgetItem* parentItem = item->parent();
    if(NULL == parentItem)
    {
        return;
    }
    quint16 wGroupID = parentItem->data(0,Qt::UserRole).toUInt();
    User* user1 = m_privi.findUser(wGroupID,text);
    if(NULL != user1)
    {
        //组名重复
        return;
    }
    user->strUserName = text;
    item->setText(0,text);
}

void HPrivilegeSet::on_modifyPwd()
{
    QTreeWidgetItem* item = ui->manTreeWidget->currentItem();
    if(NULL == item || TREE_PRIVSET_USER != item->type())
    {
        return;
    }
    quint16 wUserID = item->data(0,Qt::UserRole).toUInt();
    User* user = m_privi.findUser(wUserID);
    if(NULL == user)
    {
        return;
    }

    HModifyPwdDlg dlg(user,this);
    dlg.exec();
}

void HPrivilegeSet::on_SystemLoginBox()
{
    setPrivilege(Ht::SystemLoginPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_SysetmExitBox()
{
    setPrivilege(Ht::SystemExitPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_PeopleManagerBox()
{
    setPrivilege(Ht::PeopleManagerPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_ConfigureToolBox()
{
    setPrivilege(Ht::ConfigureToolPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_GraphEditorBox()
{
    setPrivilege(Ht::GraphEditorPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_SystemSetBox()
{
    setPrivilege(Ht::SystemSetPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_OperTicketBrowserBox()
{
    setPrivilege(Ht::OperTicketBrowserPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_OperTicketEditorBox()
{
    setPrivilege(Ht::OperTicketEditorPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_OperTicketDeleteBox()
{
    setPrivilege(Ht::OperTicketDeletePrivi,m_Group,m_User);
}

void HPrivilegeSet::on_OperTicketCancelBox()
{
    setPrivilege(Ht::OperTicketCancelPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_OperTicketRunBox()
{
    setPrivilege(Ht::OperTicketRunPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_OperTicketGuardBox()
{
    setPrivilege(Ht::OperTicketGuardPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_ModelTicketToRunBox()
{
    setPrivilege(Ht::ModelTicketToRunPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_TempTicketToRunBox()
{
    setPrivilege(Ht::TempTicketToRunPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_GiveOrderBox()
{
    setPrivilege(Ht::GiveOrderPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_DutyManagerBox()
{
    setPrivilege(Ht::DutyManagerPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_DutyLeaderBox()
{
    setPrivilege(Ht::DutyLeaderPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_PrintSetBox()
{
    setPrivilege(Ht::PrintSetPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_ManualSetBox()
{
    setPrivilege(Ht::ManualSetPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_GroupOnOffBox()
{
    setPrivilege(Ht::GroupOnOffPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_WorkTicketManagerBox()
{
    setPrivilege(Ht::WorkTicketManagerPrivi,m_Group,m_User);
}

void HPrivilegeSet::on_WorkTicketModelManagerBox()
{
    setPrivilege(Ht::WorkTicketModelManagerPrivi,m_Group,m_User);
}


void HPrivilegeSet::setPrivilege(quint64 lPrivilege,Group* group,User* user)
{
    if(group!=NULL)
        setGroupPrivilege(lPrivilege,group);

    if(user != NULL)
        setUserPrivilege(lPrivilege,user);
}

void HPrivilegeSet::setGroupPrivilege(quint64 lPrivilege,Group* group)
{
    //已经存在这个权限就是去掉
    if((group->lGroupPrivilege & lPrivilege) == lPrivilege)
    {
        if(lPrivilege == Ht::PeopleManagerPrivi && (group->wGroupID = ADMINGROUPID))
        {
            ui->PeopleManagerBox->setChecked(true);
            QMessageBox::warning(NULL,"警告","系统管理员必须有人员维护权限!",QMessageBox::Ok);
            return;
        }
        group->lGroupPrivilege &=(~lPrivilege);
    }
    else
    {
        group->lGroupPrivilege |= lPrivilege;
    }

    if(group->bUnitePrivilege)
    {
        for(int i = 0; i < m_privi.m_pUserList.count();i++)
        {
            User* user = m_privi.m_pUserList[i];
            if(user->wGroupID == group->wGroupID)
                user->lGroupPrivilege = group->lGroupPrivilege;
        }
    }
}

void HPrivilegeSet::setUserPrivilege(quint64 lPrivilege,User* user)
{
    //已经存在这个权限就是去掉
    if((user->lGroupPrivilege & lPrivilege) == lPrivilege)
    {
        if(lPrivilege == Ht::PeopleManagerPrivi && (user->wGroupID = ADMINUSERID))
        {
            QMessageBox::warning(NULL,"警告","系统管理员必须有人员维护权限!",QMessageBox::Ok);
            ui->PeopleManagerBox->setChecked(true);
            return;
        }
        user->lGroupPrivilege &=(~lPrivilege);
    }
    else
    {
        user->lGroupPrivilege |= lPrivilege;
    }
}

void HPrivilegeSet::on_UnitPrivilegeBox()
{
    if(!m_Group)
        return;
    bool bCheck = ui->UnitPrivilegeBox->isChecked();
    m_Group->bUnitePrivilege = bCheck;
    for(int i = 0; i < m_privi.m_pUserList.count();i++)
    {
        User* user = m_privi.m_pUserList[i];
        if(user->wGroupID == m_Group->wGroupID)
            user->lGroupPrivilege = m_Group->lGroupPrivilege;
    }
    //updatePrivilege(bCheck);
}

void HPrivilegeSet::on_saveBtn()
{
    if(m_privi.saveData())
    {
        QMessageBox::information(NULL,"提示","保存成功!",QMessageBox::Ok);
    }
    QDialog::accept();
}

void HPrivilegeSet::on_quitBtn()
{
    QDialog::reject();
}
