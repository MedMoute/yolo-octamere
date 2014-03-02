#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->Plot = new plotting;
    Plot->setPlot(ui->customPlot);
    Plot->initPlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

plotting* MainWindow::getPlotting()
{
    return Plot;
}

void MainWindow::on_button_FindFile_clicked()
{
    fileName=QFileDialog::getOpenFileName(this,tr("Open Text file"), "", tr("Text Files (*.txt)"));
}

void MainWindow::on_button_PlotEnvir_clicked()
{
    qDebug()<<fileName.compare(Plot->getObstacles()->getenvirPath());
    if (fileName.compare(Plot->getObstacles()->getenvirPath())==0)
    {}
    else
    {
        if (ui->checkBox_detailenvir->isChecked())
        {
            verbose=true;
            qDebug()<<"Youpi on écrit tout !";
            // TODO : Afficher tout plein d'infos et de positions de points
        }
        else
        {}

        Plot->getObstacles()->setEnvironment(this->getFileName());
        Plot->drawEnvironment();
    }

}

QString MainWindow::getFileName()
{
    return fileName;
}

void MainWindow::on_button_PlotGraph_clicked()
{
    setMainPoints();
    Plot->createNewSegments(this->getMainPoints()); //A l'intérieur crée ts les segs mais ne garde que ceux qui sont OK (eux qui coupent/passent pas dans un obstacle)
    Plot->drawEnvironment();
    Plot->drawGraph();

}

void MainWindow::on_button_LaunchAlgo_clicked()
{

}

void MainWindow::setMainPoints()
{
    sommet tmpsom_A(ui->A_x->value(),ui->A_y->value());
    //qDebug()<<"("<<ui->A_x->value()<<";"<<ui->A_y->value()<<")";
    //qDebug()<<"("<<ui->B_x->value()<<";"<<ui->B_y->value()<<")";
    sommet tmpsom_B(ui->B_x->value(),ui->B_y->value());
    ptA=tmpsom_A;
    ptB=tmpsom_B;
}

pairsom MainWindow::getMainPoints()
{
    pairsom pair=std::make_pair(ptA,ptB);
    return pair;
}
