#include <QtWidgets>

#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>

#include <QDomDocument>

#include <iostream>
#include <fstream>

#include <mytablewidgetitem.h>


MainWindow::MainWindow()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    /*
     * */

    m_pTableWidget = new QTableWidget(this);
    m_pTableWidget->setRowCount(8);
    m_pTableWidget->setColumnCount(8);

    m_TableHeader<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H";

    m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
    m_pTableWidget->verticalHeader()->setVisible(true);
    m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableWidget->setShowGrid(true);
   // m_pTableWidget->setStyleSheet("QTableView::item:focus{selection-background-color: red;}");

     m_pTableWidget->setStyleSheet("QTableView::item:hover{selection-background-color: yellow;}");

    m_pTableWidget->setGeometry(QApplication::desktop()->screenGeometry());

    //insert data
  //  m_pTableWidget->setItem(0, 1, new QTableWidgetItem("Hello"));

   connect( m_pTableWidget, SIGNAL( cellDoubleClicked (int, int) ), this, SLOT( cellSelected( int, int ) ) );

   /*
    * */


    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);

    layout->addWidget(m_pTableWidget);

    layout->addWidget(bottomFiller);
    widget->setLayout(layout);



    createActions();
    createMenus();

    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);

    setWindowTitle(tr("Menus"));
    setMinimumSize(160, 160);
    resize(1200, 500);
}


void MainWindow::cellSelected(int nRow, int nCol)
{
 //QMessageBox::information(this, "", "Cell at row "+QString::number(nRow)+" column "+QString::number(nCol)+" was double clicked.");

  cellDialog_obj.setExpression("Cell at row "+QString::number(nRow)+" column "+QString::number(nCol)+" was double clicked.");

  if(this->m_pTableWidget->item(nRow, nCol) != NULL){

    //  this->m_pTableWidget->item

  cellDialog_obj.setSelectedTableWidgetItem(this->m_pTableWidget->item(nRow, nCol));
  cellDialog_obj.setExpression(this->m_pTableWidget->item(nRow, nCol)->text());
  }else
  {   m_pTableWidget->setItem(nRow, nCol, new MyTableWidgetItem("here may be done a lot"));
      // the line below was missed
      cellDialog_obj.setSelectedTableWidgetItem(this->m_pTableWidget->item(nRow, nCol));
      cellDialog_obj.setExpression("There is a lot to do");
  }
  cellDialog_obj.show();

}

/**/
/*
#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

*/

void MainWindow::newFile()
{
    infoLabel->setText(tr("Invoked <b>File|New</b>"));
}



void MainWindow::open()
{
    infoLabel->setText(tr("Invoked <b>File|Open</b>"));                    

      QString plugin_xml_fileName = QFileDialog::getOpenFileName(this, tr("Select xml file of e-table"), qApp->applicationDirPath(), tr("xml Files (*.xml)"));
      QFile xmlFile(plugin_xml_fileName);

      if (xmlFile.open(QIODevice::ReadOnly))
      {

          QDomDocument document;
          QString errorStr;
          int errorLine;
          int errorColumn;
          if (!document.setContent(&xmlFile, true, &errorStr, &errorLine,&errorColumn))
          {   qDebug()<<"Parse error at line "<<errorLine<<", column "<<errorColumn<<":"<<errorStr<<endl;

          }else
          {   QDomElement root = document.firstChildElement();
              QDomNode domnode;
              /*
              QDomNodeList etab_grid = root.elementsByTagName("GRID");
              QDomNode domnode;




              domnode = etab_grid.at(0);
              if(domnode.isElement())
              {
                QDomElement domelement = domnode.toElement();
                */
                QDomNodeList etab_cell = root.elementsByTagName("CELL"); //domelement.elementsByTagName("CELL");
                qDebug() <<" expected CELL level ";

                for(int i = 0; i < etab_cell.count(); i++)
                {   domnode = etab_cell.at(i);
                    if(domnode.isElement())
                    { QDomElement domelement = domnode.toElement();
                       // QMessageBox::about(this, tr("Debug"), tr("expected CELL level"));
/*
                      qDebug() <<"  Row  "<<domelement.elementsByTagName("Row").at(0).toElement().text();
                      qDebug() <<"  Column  "<<domelement.elementsByTagName("Column").at(0).toElement().text();
                      qDebug() <<"  Expresion  "<<domelement.elementsByTagName("Expression").at(0).toElement().text();
                      qDebug() <<"  Format  "<<domelement.elementsByTagName("Format").at(0).toElement().text();
*/

                      QString sRow = domelement.elementsByTagName("Row").at(0).toElement().text();
                      char cRow = sRow[0].unicode();
                      int nRow = ( cRow >= 48 && cRow <= 58 )? (short)cRow - 48 : 0;

                      QString sCol = domelement.elementsByTagName("Column").at(0).toElement().text();
                      char cCol = sCol.at(0).unicode();
                      int nCol = ( cCol >= 65 && cCol <= 91 )? (short)cCol - 65 : 0;


                      /*
                      setForeground() for text color
                      setBackground() for cell background color.

                      tbl_item = new QTableWidgetItem (QTableWidgetItem (QString (SList.at(0))));
                      tbl_item->setBackground(QBrush(QColor(Qt::blue)));
                      */


                      QString expr = domelement.elementsByTagName("Expression").at(0).toElement().text();

                                      if(this->m_pTableWidget->item(nRow, nCol) != NULL){
                                         this->m_pTableWidget->item(nRow, nCol)->setText(expr);
                                     }else
                                     {   this->m_pTableWidget->setItem(nRow, nCol, new MyTableWidgetItem(expr, expr));
                                     }
/*
                     QString cellFormat = domelement.elementsByTagName("Format").at(0).toElement().text();
                     if(cellFormat == "label"){
                         this->m_pTableWidget->item(nRow, nCol)->setBackground(QBrush(QColor(Qt::blue)));
                         this->m_pTableWidget->item(nRow, nCol)->setForeground(QBrush(QColor(Qt::white)));
                     }
*/

                    }
                }
             // }
          }
          xmlFile.close();
        }else
        {
          qDebug()<<"XML File failed to open  "<<plugin_xml_fileName<<endl;
        }

}


void MainWindow::save()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));

    QString filename = QFileDialog::getSaveFileName(this,
                                       tr("Save Xml"), ".",
                                       tr("Xml files (*.xml)"));


    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("GRID");

    xmlWriter.writeStartElement("CELL");
    xmlWriter.writeTextElement("Column", "A");
    xmlWriter.writeTextElement("Row", "1" );
    xmlWriter.writeTextElement("Expression", "Test lable");
    xmlWriter.writeTextElement("Format", "label");
    xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("CELL");
    xmlWriter.writeTextElement("Column", "B");
    xmlWriter.writeTextElement("Row", "1" );
    xmlWriter.writeTextElement("Expression", "3.14");
    xmlWriter.writeTextElement("Format", "numeric");
    xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("CELL");
    xmlWriter.writeTextElement("Column", "C");
    xmlWriter.writeTextElement("Row", "1" );
    xmlWriter.writeTextElement("Expression", "2");
    xmlWriter.writeTextElement("Format", "numeric");
    xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("CELL");
    xmlWriter.writeTextElement("Column", "D");
    xmlWriter.writeTextElement("Row", "1" );
    xmlWriter.writeTextElement("Expression", ":B1 * :C1 * :C1");
    xmlWriter.writeTextElement("Format", "expression");
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();

    file.close();

}




void MainWindow::cut()
{
    infoLabel->setText(tr("Invoked <b>Edit|Cut</b>"));
}

void MainWindow::copy()
{
    infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
}

void MainWindow::paste()
{
    infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

void MainWindow::bold()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Bold</b>"));
}

void MainWindow::italic()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Italic</b>"));
}

void MainWindow::leftAlign()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Left Align</b>"));
}

void MainWindow::rightAlign()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Right Align</b>"));
}

void MainWindow::center()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Center</b>"));
}

void MainWindow::about()
{
    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    //QMessageBox::about(this, tr("About Menu"), tr("Here some info comes"));
}



void MainWindow::ReadGridCellElement(QXmlStreamReader Rxml)
{
    while(!Rxml.atEnd())
    {
        if(Rxml.isEndElement())
        {
            Rxml.readNext();
            break;
        }
        else if(Rxml.isStartElement())
        {
            QString cellelement = Rxml.readElementText();   //Get the xml value
            Rxml.readNext();
            break;
        }
        else if(Rxml.isCharacters())
        {
           Rxml.readNext();
           //...
        }
        else
        {
           Rxml.readNext();
        }
    }

}




void MainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, &QAction::triggered, this, &MainWindow::copy);

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);

    boldAct = new QAction(tr("&Bold"), this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(QKeySequence::Bold);
    boldAct->setStatusTip(tr("Make the text bold"));
    connect(boldAct, &QAction::triggered, this, &MainWindow::bold);

    QFont boldFont = boldAct->font();
    boldFont.setBold(true);
    boldAct->setFont(boldFont);

    italicAct = new QAction(tr("&Italic"), this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(QKeySequence::Italic);
    italicAct->setStatusTip(tr("Make the text italic"));
    connect(italicAct, &QAction::triggered, this, &MainWindow::italic);

    QFont italicFont = italicAct->font();
    italicFont.setItalic(true);
    italicAct->setFont(italicFont);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    leftAlignAct = new QAction(tr("&Left Align"), this);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setShortcut(tr("Ctrl+L"));
    leftAlignAct->setStatusTip(tr("Left align the selected text"));
    connect(leftAlignAct, &QAction::triggered, this, &MainWindow::leftAlign);

    rightAlignAct = new QAction(tr("&Right Align"), this);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setShortcut(tr("Ctrl+R"));
    rightAlignAct->setStatusTip(tr("Right align the selected text"));
    connect(rightAlignAct, &QAction::triggered, this, &MainWindow::rightAlign);

    centerAct = new QAction(tr("&Center"), this);
    centerAct->setCheckable(true);
    centerAct->setShortcut(tr("Ctrl+E"));
    centerAct->setStatusTip(tr("Center the selected text"));
    connect(centerAct, &QAction::triggered, this, &MainWindow::center);

    alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(leftAlignAct);
    alignmentGroup->addAction(rightAlignAct);
    alignmentGroup->addAction(centerAct);
    leftAlignAct->setChecked(true);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);    
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);

    formatMenu = editMenu->addMenu(tr("&Format"));
    formatMenu->addAction(boldAct);
    formatMenu->addAction(italicAct);
    formatMenu->addSeparator()->setText(tr("Alignment"));
    formatMenu->addAction(leftAlignAct);
    formatMenu->addAction(rightAlignAct);
    formatMenu->addAction(centerAct);
    formatMenu->addSeparator();
}
