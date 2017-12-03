#include "celldialog.h"
#include "ui_celldialog.h"
#include "expressionanalizer.cpp"

CellDialog::CellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CellDialog)
{
    ui->setupUi(this);

    ui->submitButton->setStyleSheet("QPushButton { color: palette(dark); }");

    connect(ui->submitButton, SIGNAL(released()), this, SLOT( onSubmit() )  );

    ui->lineEdit->setText("Here comes our expression");
}

void CellDialog::onSubmit()
{

    //qDebug() <<  "On sumbit ";
    std::cout <<  "On sumbit ";

    // 1 Analyse Expresion
    std::string expr = ui->lineEdit->text().toStdString();

    //std::string expr_str = start_expr_analyse(expr);

    std::string expr_str = ipn(expr);



    QMessageBox::information(this, "", QString(expr_str.c_str()));
    // 1-1 Check
    // 1-2 Calculate
    this->selectedTableWidgetItem->setText(ui->lineEdit->text());

   // QMessageBox::information(this, "", ui->lineEdit->text());
    // QMessageBox::information(this, "", QString(expr_str.c_str()));
}

void CellDialog::setExpression(QString expr){
    this->ui->lineEdit->setText(expr);
}

void CellDialog::setSelectedTableWidgetItem(QTableWidgetItem* ptr)
{ this->selectedTableWidgetItem=ptr;
}

CellDialog::~CellDialog()
{
    delete ui;
}
