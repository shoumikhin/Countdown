#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QLocale>

#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setStyle("plastique");

    QTranslator translator;

    translator.load(QString("countdown_") + QLocale::system().name());
    app.installTranslator(&translator);

    Dialog dialog;

    dialog.show();

    return app.exec();
}
