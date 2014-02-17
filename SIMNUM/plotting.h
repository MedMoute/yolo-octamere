#ifndef PLOTTING_H
#define PLOTTING_H

#include "sommet.h"
#include "environnement.h"
#include "qcustomplot.h"
#include <QPen>
#include <QString>
#include "mainwindow.h"

extern QCustomPlot& Plot;

typedef std::pair< std::vector< double > , std::vector< double > > dataarray;

class plotting
{
public:
    plotting();
    void drawPolygon(obstacle obst);

    void drawEnvironment();

    std::list<dataarray> getDatas();
    dataarray setDatas(std::vector<sommet> sommets);

    QString getFileName();
    void setFileName(QString);

    void setPlot(QCustomPlot* plot);
    void initPlot();

    void resetEnvironment();

    environnement* getObstacles();


private:
    QString fileName;
    QPen pen;
    std::list<dataarray> datas;
    QCustomPlot* customPlot;
    environnement* obstacles;

};



#endif // PLOTTING_H
