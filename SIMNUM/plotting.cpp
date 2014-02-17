#include "plotting.h"
#include <QDebug>
#include "qcustomplot.h"

plotting::plotting()
{
    this->obstacles = new environnement;
}

void plotting::setDatas()
{
    //obstacles->setEnvironment(fileName);
}

void plotting::drawEnvironment()
{
    std::list<obstacle> Environnement_tmp=obstacles->getEnvir();
    obstacle obstToPlot;

    for (int i=0;i<Environnement_tmp.size();i++)
    {
        obstToPlot=Environnement_tmp.front();
        Environnement_tmp.pop_front();

        drawPolygon(obstToPlot);
    }
}

void plotting::drawPolygon(obstacle obst)
{
    obstacle obstToPlot=obst;
    std::vector<segment> segs = obstToPlot.getSegment();
    segment seg;
    //On utilise QCP Curve

}


environnement* plotting::getObstacles()
{
    return obstacles;
}
