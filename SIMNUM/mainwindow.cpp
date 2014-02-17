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

void MainWindow::on_pushButton_2_clicked()
{
    fileName=QFileDialog::getOpenFileName(this,tr("Open Text file"), "", tr("Text Files (*.txt)"));
}

QString MainWindow::getFileName()
{
    return fileName;
}
void MainWindow::on_pushButton_3_clicked()
{

    Plot->getObstacles()->setEnvironment(this->getFileName());
    Plot->drawEnvironment();
    Plot->resetEnvironment();
    //Plot.drawPolygon();
}
