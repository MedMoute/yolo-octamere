#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "plotting.h"


namespace Ui {
class MainWindow;
}


class plotting;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   plotting* getPlotting();
    QString getFileName();
    void setMainPoints();
    pairsom getMainPoints();

    bool verbose;

private:
    QCustomPlot* customPlot;
    Ui::MainWindow *ui;
    plotting* Plot;
    QString fileName;
    sommet ptA;
    sommet ptB;

public slots:
    void on_button_FindFile_clicked(); //Slot qui lance la recherche de fichiers --//Syntaxe pour que QtCreator reconnaisse le slot
    void on_button_PlotEnvir_clicked(); //Slot qui analyse le fichier txt et plot les obstacles
    void on_button_PlotGraph_clicked();
    void on_button_LaunchAlgo_clicked();

};

#endif // MAINWINDOW_H
