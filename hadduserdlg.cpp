#include "hadduserdlg.h"
#include "ui_adduserdlg.h"
#include "hprivilege.h"
#include <QMessageBox>

HAddUserDlg::HAddUserDlg(HPrivilege* privi,QString groupName,quint16 groupID,QWidget *parent) :
    m_privi(privi),strGroupName(groupName),wGroupID(groupID),QDialog(parent),
    ui(new Ui::addUserDlg)
{
    ui->setupUi(this);
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
    if(NULL != m_privi->findUser(wGroupID,strName))
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
