#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
      ui->setupUi(this);
      this->fileName="";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Open Text file"), "", tr("Text Files (*.txt)"));
}

void MainWindow::on_pushButton_3_clicked()
{
   /* Plot.setDatas(fileName);

    Plot.drawPolygon();*/
}
