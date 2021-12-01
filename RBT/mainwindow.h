#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPainter"
#include "QtGui"
#include "QtCore"
#include "RedBlackTree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    bool m_flag;
    int ctr;
    RedBlackTree *tree = new RedBlackTree();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void paintEvent(QPaintEvent *event);

    void drawTree(Nodeptr c, QPoint p1, QPoint ppoint);

private slots:

    void on_InsertButton_clicked();

    void on_DeleteButton_clicked();

    void on_Print_clicked();



    void on_Clear_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
