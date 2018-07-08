#ifndef HCHECKPRIVIDLG_H
#define HCHECKPRIVIDLG_H

#include <QDialog>

namespace Ui {
class HCheckPriviDlg;
}

class HCheckPriviDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HCheckPriviDlg(QWidget *parent = 0);
    ~HCheckPriviDlg();
    void initCheckPrivi();

public slots:
    void on_okBtn();
    void on_cancelBtn();

public:
    QString m_strUserName;
    QString m_strTitle;
    quint64 m_lPrivilege;
private:
    Ui::HCheckPriviDlg *ui;
};

#endif // HCHECKPRIVIDLG_H
