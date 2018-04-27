#ifndef HPRIVILEGESET_H
#define HPRIVILEGESET_H

#include <QDialog>

namespace Ui {
class HPrivilegeSet;
}

class HPrivilegeSet : public QDialog
{
    Q_OBJECT

public:
    explicit HPrivilegeSet(QWidget *parent = 0);
    ~HPrivilegeSet();

private:
    Ui::HPrivilegeSet *ui;
};

#endif // HPRIVILEGESET_H
