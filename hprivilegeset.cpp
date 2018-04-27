#include "hprivilegeset.h"
#include "ui_privilegeset.h"

HPrivilegeSet::HPrivilegeSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HPrivilegeSet)
{
    ui->setupUi(this);
}

HPrivilegeSet::~HPrivilegeSet()
{
    delete ui;
}
