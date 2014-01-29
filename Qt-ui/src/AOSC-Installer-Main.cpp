#include <iostream>
#include <qt4/QtCore/QCoreApplication>
#include <qt4/QtGui/QApplication>
#include <qt4/QtCore/QTextCodec>
#include "AOSC-Installer-Basic-UI.h"
#include "AOSC-Installer-Core.h"

using namespace std;

QCoreApplication* createApplication(int &argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
        if (!qstrcmp(argv[i], "-no-gui"))
            return new QCoreApplication(argc, argv);
    return new QApplication(argc, argv);
}

int main(int argc, char* argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    QScopedPointer<QCoreApplication> app(createApplication(argc, argv));

    if (qobject_cast<QApplication *>(app.data())) {
        ProgressTab *Tab = new ProgressTab;
        Tab->show();
    } else {
       // start non-GUI version...
	cout << "Hehe" << endl;
    }

    return app->exec();
}
