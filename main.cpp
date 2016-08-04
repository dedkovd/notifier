#include <QtWidgets/QApplication>
#include "widget.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator t;
    t.load("notifier");
    a.installTranslator(&t);

    Widget *w = new Widget();
    w->hide();

    return a.exec();
}
