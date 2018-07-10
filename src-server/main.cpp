#include "TCPConnection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SQLTool::connection();
    TCPConnection w;
//    QStringList l;
//    l.append("1");
//    l.append("300");
//    l.append("3");
//    l.append("500");
//    l.append("4");
//    l.append("600");
//    Order order("7", "1997-03-19 10:10:10", l);
//    Warehouse::replenish("1", order);

    return a.exec();
}
