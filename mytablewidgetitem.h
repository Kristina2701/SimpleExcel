#ifndef MYTABLEWIDGETITEM_H
#define MYTABLEWIDGETITEM_H

#include<iostream>
#include<string>
#include<QTableWidgetItem>

class MyTableWidgetItem : public QTableWidgetItem{
    private:
        std::string expression;
    public:
        MyTableWidgetItem(QString s, QString e): QTableWidgetItem(s) {expression = e.toStdString(); }
        MyTableWidgetItem(QString s): QTableWidgetItem(s) {expression = ""; }
        std::string getExpression(){return expression;}
        QString getQExpression(){return QString::fromStdString(expression);}
  //      void setExpression(std::string s){ this->expression = s;}
   //     void setQExpression(QString qs){ this->expression = qs.toStdString();}

};

#endif // MYTABLEWIDGETITEM_H
