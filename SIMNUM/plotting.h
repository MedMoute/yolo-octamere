#ifndef PLOTTING_H
#define PLOTTING_H

#include "sommet.h"
#include "environnement.h"
#include "qcustomplot.h"
#include "graphe.h"
#include <QPen>
#include <QString>
#include "mainwindow.h"

extern QCustomPlot& Plot;

typedef std::pair< std::vector< double > , std::vector< double > > dataarray;

class plotting
{
public:
    plotting();

    void resetEnvironment();
    void drawEnvironment();

    void drawPolygon(obstacle obst);

    std::list<dataarray> getDatas();
    dataarray setDatas(std::vector<sommet> sommets);

    QString getFileName();
    void setFileName(QString);

    void setPlot(QCustomPlot* plot);
    void initPlot();

    environnement* getObstacles();


    void createNewSegments(pairsom pair); //  Transforme Envir de obstacles en graphe
                                 // A l'intérieur crée ts les segs mais ne garde que ceux qui sont OK (eux qui coupent/passent pas dans un obstacle)
    void drawGraph(); //dessine tous le graphe validé

private:
    QString fileName;
    std::list<dataarray> datas;
    QCustomPlot* customPlot;
    environnement* obstacles;

    graphe* graph;
};



#endif // PLOTTING_H
