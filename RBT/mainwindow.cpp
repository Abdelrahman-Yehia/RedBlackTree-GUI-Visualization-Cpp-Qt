#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QtGui"
#include "QtCore"
#include "RedBlackTree.h"
#include <string>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_flag = 0;
    ctr = 0;
}





MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawTree(Nodeptr c, QPoint p1, QPoint ppoint)
{
    if(c == tree->getTNull()) return;
    QPainter drawer(this);
    QPen Pen;
    drawer.drawLine(p1,ppoint);
    if(c->color)
        Pen.setColor(Qt::red);
    else
        Pen.setColor(Qt::black);
    Pen.setWidth(2);
    drawer.setPen(Pen);
    drawer.drawEllipse(p1,25,25);
    //char num = char(int('0')+c->data);
    string x = to_string(c->data);
    //x+=num;
    QString print = QString::fromStdString(x);
    drawer.drawText(p1,print);
    if(c->liftchild != tree->getTNull()){
        QPoint p2;
        int a = p1.x();
        p2.setX(a-50);
        p2.setY(p1.y()+100);
        Pen.setColor(Qt::blue);
        Pen.setWidth(2);
        //drawer.drawLine(p1,p2);
        drawTree(c->liftchild,p2,p1);
    }
    if(c->rightchild != tree->getTNull()){
        QPoint p2;
        p2.setX(p1.x()+50);
        p2.setY(p1.y()+100);
        Pen.setColor(Qt::blue);
        Pen.setWidth(2);
        //drawer.drawLine(p1,p2);
        drawTree(c->rightchild,p2,p1);
    }
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    if(m_flag){
        QPoint p1;
        p1.setX(200);
        p1.setY(100);
        drawTree(tree->getRoot(), p1,p1);
        m_flag = 0;
    }
}










void MainWindow::on_InsertButton_clicked()
{
    QString data = ui->InsertText->toPlainText();
    string current = data.toLocal8Bit().constData();
    stringstream ss(current);
    int val;
    ss >> val;
    tree->insert(val);
    ui->InsertText->clear();
    ctr++;
}

void MainWindow::on_DeleteButton_clicked()
{
    QString data = ui->DeleteText->toPlainText();
    string current = data.toLocal8Bit().constData();
    stringstream ss(current);
    int val;
    ss >> val;
    tree->Delete(val);
    ui->DeleteText->clear();
    ctr--;
}

void MainWindow::on_Print_clicked()
{
    m_flag = true;
    update();
}

void MainWindow::on_Clear_clicked()
{
   tree = new RedBlackTree();
   MainWindow::on_Print_clicked();
   ctr=0;
}
