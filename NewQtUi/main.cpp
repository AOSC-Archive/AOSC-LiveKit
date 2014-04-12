#include "AOSC_Installer_MainWindow.h"
#include <QApplication>
#include <QTextCodec>
using namespace std;

int main(int argc, char *argv[])
{
#if QT_VERSION < 0x050000
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
#else
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
#endif
    QApplication a(argc, argv);
    AOSC_Installer_MainWindow *w = new AOSC_Installer_MainWindow();
    w->show();

    return a.exec();
}
