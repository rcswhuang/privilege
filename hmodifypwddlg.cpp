#include "hmodifypwddlg.h"
#include "ui_modifypwddlg.h"

#include <QMessageBox>
HModifyPwdDlg::HModifyPwdDlg(User* user,QWidget *parent) :
    QDialog(parent),ui(new Ui::modifyPwdDlg),m_user(user)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    connect(ui->yesBtn,SIGNAL(clicked(bool)),this,SLOT(on_yesBtn()));
    connect(ui->noBtn,SIGNAL(clicked(bool)),this,SLOT(on_noBtn()));
    ui->userEdit->setText(m_user->strUserName);
}

HModifyPwdDlg::~HModifyPwdDlg()
{
    delete ui;
}

void HModifyPwdDlg::on_yesBtn()
{
    QString oldPwd = ui->oldPwdEdit->text();
    if(oldPwd != m_user->strUserPwd)
    {
        QMessageBox::warning(NULL,"警告","原密码不正确！",QMessageBox::Ok);
        return;
    }
    QString newPwd = ui->newPwdEdit->text();
    QString newPwd1 = ui->newPwd1Edit->text();
    if(newPwd != newPwd1)
    {
        QMessageBox::warning(NULL,"警告","两次新密码不匹配！",QMessageBox::Ok);
        return;
    }
    m_user->strUserPwd = newPwd;
    QDialog::accept();
}

void HModifyPwdDlg::on_noBtn()
{
    QDialog::reject();
}
