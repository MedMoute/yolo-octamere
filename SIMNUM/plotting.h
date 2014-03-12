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
    int Rank_T;

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


    void createNewSegments(pairsom pair,int n); //  Transforme Envir de obstacles en graphe
                                 // A l'intérieur crée ts les segs mais ne garde que ceux qui sont OK (eux qui coupent/passent pas dans un obstacle)
    void drawGraph(); //dessine tous le graphe validé
   // bool QuiaLaPlusPetite(const std::pair<sommet, float>&, const std::pair<sommet, float>&); //true si michel se fait dominer par micheline

    void Dijkstra (pairsom pair);

private:
    QString fileName;
    std::list<dataarray> datas;
    QCustomPlot* customPlot;
    environnement* obstacles;

    graphe* graph;
};

struct pA_comp {
    bool operator() (sommet& left,sommet& right) const {
        return ((left.Xcoord()-)*(left.Xcoord()-)+(left.Ycoord()-)*(left.Ycoord()-)) < ((right.Xcoord()-)*(right.Xcoord()-)+(right.Ycoord())*(right.Ycoord()));
    }
};

#endif // PLOTTING_H
