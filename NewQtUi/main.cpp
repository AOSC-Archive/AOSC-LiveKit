#include "AOSC_Installer_MainWindow.h"
#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AOSC_Installer_MainWindow *w = new AOSC_Installer_MainWindow();
    w->show();

    return a.exec();
}
