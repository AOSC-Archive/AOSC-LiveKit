#include "installermain.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc,char *argv[]){
#if QT_VERSION < 0x050000
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForTr(codec);
        QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
        QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
#else
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
#endif
        QApplication a(argc, argv);
        InstallerMain MainWindow;
        MainWindow.show();
        return a.exec();
}
