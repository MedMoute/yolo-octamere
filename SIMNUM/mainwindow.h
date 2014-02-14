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
    //void setGraph(dataarray datas);
    //void setPlotting();
    
private:
    Ui::MainWindow *ui;

public slots:
    void on_pushButton_2_clicked(); //Slot qui lance la recherche de fichiers --//Syntaxe pour que QtCreator reconnaisse le slot
    void on_pushButton_3_clicked(); //Slot qui analyse le fichier txt et plot les obstacles
    /*void launchFullPlot();
    void launchAlgorithm();

    void pointA_xChanged(double xA);
    void pointA_yChanged(double yA);
    void pointB_xChanged(double xB);
    void pointB_yChanged(double yB);*/

    QString getFileName();

private:
    plotting* Plot;
    QString fileName;
};

#endif // MAINWINDOW_H
