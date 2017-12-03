#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "celldialog.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
        CellDialog*  cellDialog_ptr;
        CellDialog  cellDialog_obj;

        QLabel *infoLabel;
        QTableWidget* m_pTableWidget;
        QStringList m_TableHeader;


        QMenu *fileMenu;
        QAction *newAct;
        QAction *openAct;
        QAction *saveAct;
        QAction *exitAct;


        QMenu *editMenu;
        QAction *cutAct;
        QAction *copyAct;
        QAction *pasteAct;

        QMenu *formatMenu;
        QAction *boldAct;
        QAction *italicAct;
        QAction *leftAlignAct;
        QAction *rightAlignAct;
        QAction *centerAct;

        QMenu *helpMenu;
        QAction *aboutAct;

        QActionGroup *alignmentGroup;

        void createActions();
        void createMenus();

        void ReadGridCellElement(QXmlStreamReader Rxml);


private slots:
    void newFile();
    void open();
    void save();

    void cut();
    void copy();
    void paste();

    void bold();
    void italic();
    void leftAlign();
    void rightAlign();
    void center();

    void about();

    void cellSelected(int nRow, int nCol);


/*
protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU











      */
};

#endif
