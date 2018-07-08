#include "hcheckprividlg.h"
#include "ui_checkprividlg.h"
#include "hprivilege.h"
#include <QMessageBox>
extern HPrivilege m_privi;
HCheckPriviDlg::HCheckPriviDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HCheckPriviDlg)
{
    ui->setupUi(this);
    initCheckPrivi();
}

HCheckPriviDlg::~HCheckPriviDlg()
{
    delete ui;
}

void HCheckPriviDlg::initCheckPrivi()
{
    ui->userComboBox->clear();
    for(int i = 0;i < m_privi.m_pUserList.count();i++)
    {
        User* user = m_privi.m_pUserList[i];
        if(!user) continue;
        if((user->lGroupPrivilege & m_lPrivilege) == m_lPrivilege)
            ui->userComboBox->addItem(user->strUserName,user->wUserID);
    }
    setWindowTitle(m_strTitle);
    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(on_okBtn()));
    connect(ui->cancelBtn,SIGNAL(clicked(bool)),this,SLOT(on_cancelBtn()));
}

void HCheckPriviDlg::on_okBtn()
{
    bool bok;
    quint16 wUserID = ui->userComboBox->currentData().toUInt(&bok);
    if(!bok)
        QDialog::reject();
    User* user = m_privi.findUser(wUserID);
    if(!user)
        QDialog::reject();
    QString strPwd = ui->pwdEdit->text();
    if(strPwd == user->strUserPwd)
    {
        m_strUserName = user->strUserName;
        QDialog::accept();
    }
    else
    {
        QMessageBox::warning(NULL,"警告","密码不正确!",QMessageBox::Ok);
    }
}


