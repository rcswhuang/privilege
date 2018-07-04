#ifndef HMODIFYPWDDLG_H
#define HMODIFYPWDDLG_H

#include <QDialog>
#include "hprivilegeapi.h"
namespace Ui {
class modifyPwdDlg;
}

class HModifyPwdDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HModifyPwdDlg(User* user,QWidget *parent = 0);
    ~HModifyPwdDlg();

public slots:
    void on_yesBtn();
    void on_noBtn();
private:
    Ui::modifyPwdDlg *ui;
    User* m_user;

};

#endif // HMODIFYPWDDLG_H
