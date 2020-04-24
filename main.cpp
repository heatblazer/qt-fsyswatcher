#include <QCoreApplication>
#include "dirwatcher.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DirWatcher dw(argv[1]);

    return a.exec();
}
