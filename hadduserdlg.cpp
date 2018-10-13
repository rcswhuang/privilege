#if defined(_MSC_VER) &&(_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif
#include "hadduserdlg.h"
#include "ui_adduserdlg.h"
#include "hprivilege.h"
#include <QMessageBox>
extern HPrivilege m_privi;
HAddUserDlg::HAddUserDlg(QString groupName,quint16 groupID,QWidget *parent) :
    strGroupName(groupName),wGroupID(groupID),QDialog(parent),
    ui(new Ui::addUserDlg)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    ui->groupLineEdit->setText(strGroupName);
    connect(ui->addBtn,SIGNAL(clicked(bool)),this,SLOT(on_addBtn()));
    connect(ui->cancleBtn,SIGNAL(clicked(bool)),this,SLOT(on_cancleBtn()));
}

HAddUserDlg::~HAddUserDlg()
{
    delete ui;
}

void HAddUserDlg::on_addBtn()
{
    strName = ui->userEdit->text();
    //判断是否存在重名
    if(NULL != m_privi.findUser(wGroupID,strName))
    {
        QMessageBox::warning(NULL,"警告","存在重名,请修改用户名",QMessageBox::Ok);
        return;
    }
    strPwd = ui->pwdEdit->text();
    strPwd1 = ui->pwd1Edit->text();
    if(strPwd != strPwd1)
    {
        //密码不对
        QMessageBox::warning(NULL,"警告","两次密码不对，请重新设置!",QMessageBox::Ok);
        return;
    }

    QDialog::accept();
}

void HAddUserDlg::on_cancleBtn()
{
    QDialog::reject();
}
