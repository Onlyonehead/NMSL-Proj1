#include "TCPConnection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SQLTool::connection();
    TCPConnection w;

    return a.exec();
}
