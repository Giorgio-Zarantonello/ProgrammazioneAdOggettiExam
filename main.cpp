#include "modello.h"
#include "controller.h"
#include "vista.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Modello m;
    Controller c(&m);
    Vista v(&c);

    c.setView(&v);
    v.show();
    return a.exec();
}
