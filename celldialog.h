#ifndef CELLDIALOG_H
#define CELLDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QMessageBox>

namespace Ui {
class CellDialog;
}

class CellDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CellDialog(QWidget *parent = 0);
    ~CellDialog();

    void setExpression(QString expr);
    void setSelectedTableWidgetItem(QTableWidgetItem* ptr);

private slots:
   void onSubmit();

private:
    Ui::CellDialog *ui;
    QTableWidgetItem* selectedTableWidgetItem;
};

#endif // CELLDIALOG_H
