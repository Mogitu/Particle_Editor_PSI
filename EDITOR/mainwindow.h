
//mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcolordialog.h>
#include "irrcorerenderer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    IrrCoreRenderer* irr0;
    //IrrCoreRenderer* irr1;
     QColorDialog* d;


private:
    Ui::MainWindow *ui;
    void initIrrInstance0(QWidget *irrRenderTarget);
   //void initIrrInstance1(QWidget *irrRenderTarget);

protected:
    virtual void resizeEvent(QResizeEvent *event);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
