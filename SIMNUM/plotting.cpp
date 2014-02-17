#include "plotting.h"
#include <QDebug>
#include "qcustomplot.h"

//QCustomPlot* MainPlot;


plotting::plotting()
{
    this->obstacles = new environnement;
}

void plotting::drawEnvironment()
{
    std::list<obstacle> Environnement_tmp=obstacles->getEnvir();
    obstacle obstToPlot;
    int l=Environnement_tmp.size();
    for (int i=0;i<l;i++)
    {
        obstToPlot=Environnement_tmp.front();
        drawPolygon(obstToPlot);
        Environnement_tmp.pop_front();

        qDebug()<<"Fin du "<<i+1<<"eme polynome.";
    }
}

void plotting::drawPolygon(obstacle obst)
{
    obstacle obstToPlot=obst;
    std::vector<sommet> sommets = obstToPlot.getSommet();
    dataarray data_obst;

    data_obst = setDatas(sommets);

    qDebug()<<"L'obstacle est de taille"<<data_obst.second.size();
    QCPCurveDataMap plot_data;
    int l;
    for (unsigned int i=0;i<data_obst.second.size();i++)
    {
        QCPCurveData data(i,data_obst.first[i],data_obst.second[i]);
        plot_data.insert(i,data);
        l=i;
    }
    QCPCurveData data(l+1,data_obst.first[0],data_obst.second[0]);
    plot_data.insert(l+1,data);

    QCPCurve *plot = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

    plot->addData(plot_data);
    plot->setPen(QPen(Qt::blue));
    plot->setBrush(QBrush(QColor(0, 40, 255, 80)));

    customPlot->addPlottable(plot);
    customPlot->setVisible(true);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->rescaleAxes();
      customPlot->replot();
}

dataarray plotting::setDatas(std::vector<sommet> sommets)
{
    dataarray data;
    std::vector<double> X_points;
    std::vector<double> Y_points;
    unsigned int l=sommets.size();
    for (unsigned int i=0;i<l;i++)
    {
        sommet S=sommets.back();

        X_points.push_back(S.Xcoord());
        Y_points.push_back(S.Ycoord());
        qDebug()<<"("<<S.Xcoord()<<","<<S.Ycoord()<<")";

        sommets.pop_back();
    }
    data = std::make_pair(X_points,Y_points);
    return data;
}

void plotting::setPlot(QCustomPlot* plot)
{
    customPlot=plot;
}

void plotting::initPlot()
{
    qDebug()<<&customPlot;
    customPlot->xAxis->setRange(-5,5);
    customPlot->yAxis->setRange(-5,5);
}

environnement* plotting::getObstacles()
{
    return obstacles;
}

void plotting::resetEnvironment()
{
    obstacles->resetEnviron();
}
