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
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
    clicmode=0;
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

        if (ui->checkBox_padding->isChecked())
        {
            Plot->getObstacles()->setEnvironment(this->getFileName(),ui->Pad_val->value(),ui->Pad_N->value(),ui->comboBox->currentIndex());
            Plot->drawEnvironment();
        }
        else
        {
            Plot->getObstacles()->setEnvironment(this->getFileName());
            Plot->drawEnvironment();
        }
}
void MainWindow::on_button_ResetEnvir_clicked()
{
    ui->customPlot->clearGraphs();
    ui->customPlot->clearItems();
    ui->customPlot->clearFocus();
    ui->customPlot->clearPlottables();
    ui->customPlot->clearMask();
    Plot->resetEnvironment();
    ui->customPlot->replot();
}

QString MainWindow::getFileName()
{
    return fileName;
}

void MainWindow::on_button_PlotGraph_clicked()
{
    setMainPoints();
    Plot->createNewSegments(this->getMainPoints(),ui->Disc_N->value()); //A l'intérieur crée ts les segs mais ne garde que ceux qui sont OK (eux qui coupent/passent pas dans un obstacle)
    Plot->drawEnvironment();
    Plot->drawGraph();

}

void MainWindow::on_button_LaunchAlgo_clicked()
{

}

void MainWindow::on_button_selec_A_clicked()
{
    clicmode=1;
}

void MainWindow::on_button_selec_B_clicked()
{
    clicmode=2;
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

void MainWindow::mousePress(QMouseEvent* event)
{
    QCustomPlot *customPlot=ui->customPlot;
    static QCPItemLine *hCursor, *vCursor;
    double x=customPlot->xAxis->pixelToCoord(event->pos().x());
    double y=customPlot->yAxis->pixelToCoord(event->pos().y());

    if(hCursor) customPlot->removeItem(hCursor);
    hCursor = new QCPItemLine(customPlot);
    customPlot->addItem(hCursor);
    hCursor->start->setCoords(QCPRange::minRange, y);
    hCursor->end->setCoords(QCPRange::maxRange, y);

    if(vCursor) customPlot->removeItem(vCursor);
    vCursor = new QCPItemLine(customPlot);
    customPlot->addItem(vCursor);
    vCursor->start->setCoords( x, QCPRange::minRange);
    vCursor->end->setCoords( x, QCPRange::maxRange);

    ui->X_val->setText(QString::number(x));
    ui->Y_val->setText(QString::number(y));

    if (clicmode==1)
    {
        ui->A_x->setValue(x);
        ui->A_y->setValue(y);
    }
    else if (clicmode==2)
    {
        ui->B_x->setValue(x);
        ui->B_y->setValue(y);
    }

    customPlot->replot();
    clicmode=0;
}
