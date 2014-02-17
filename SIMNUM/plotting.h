#ifndef PLOTTING_H
#define PLOTTING_H

#include "sommet.h"
#include "environnement.h"
#include "qcustomplot.h"
#include <QPen>
#include <QString>

typedef std::pair< std::vector< double > , std::vector< double > > dataarray;

class plotting
{
public:
    plotting();
    void drawPolygon(obstacle obst);

    void drawEnvironment();

    dataarray* getDatas();
    void setDatas();

    QString getFileName();
    void setFileName(QString);

    environnement* getObstacles();

private:
    QString fileName;
    QPen pen;
    dataarray* datas;
    QCustomPlot* mainPlot;
    environnement* obstacles;

};



#endif // PLOTTING_H
