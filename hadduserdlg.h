#ifndef HADDUSERDLG_H
#define HADDUSERDLG_H

#include <QDialog>

namespace Ui {
class addUserDlg;
}
class HPrivilege;
class HAddUserDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HAddUserDlg(QString groupName,quint16 groupID,QWidget *parent = 0);
    ~HAddUserDlg();

public slots:
    void on_addBtn();
    void on_cancleBtn();
public:
    QString strGroupName;
    quint16 wGroupID;
    QString strName;
    QString strPwd;
    QString strPwd1;
private:
    Ui::addUserDlg *ui;
};

#endif // HADDUESRDLG_H
