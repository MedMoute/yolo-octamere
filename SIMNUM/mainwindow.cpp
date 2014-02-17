#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->Plot = new plotting;
}

MainWindow::~MainWindow()
{
    delete ui;
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

    //Plot.drawPolygon();
}
