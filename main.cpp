#include <QApplication>
#include "hprivilegeset.h"

int main(int argv,char* args[])
{
    QApplication app(argv,args);

    HPrivilegeSet mw;
    mw.show();
    return app.exec();
}
