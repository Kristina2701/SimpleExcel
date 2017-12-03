#include <QApplication>

#include "mainwindow.h"
#include "celldialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;


    window.show();
/*
    CellDialog m_cellDialog;
    m_cellDialog.show();
*/

    return app.exec();
}
