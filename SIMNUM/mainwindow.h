#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "plotting.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setGraph(dataarray datas);
    
private:
    Ui::MainWindow *ui;

public slots:
    void launchDataSearch();
    /*void launchEnvironment();
    void launchFullPlot();
    void launchAlgorithm();

    void pointA_xChanged(double xA);
    void pointA_yChanged(double yA);
    void pointB_xChanged(double xB);
    void pointB_yChanged(double yB);*/

private:
    plotting* Plot;
    QString  fileName;
};

#endif // MAINWINDOW_H
