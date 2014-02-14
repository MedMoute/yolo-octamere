#include "plotting.h"
#include <QDebug>

plotting::plotting()
{
    this->obstacles = new environnement;
}

void plotting::setDatas()
{
    //obstacles->setEnvironment(fileName);
}

environnement* plotting::getObstacles()
{
    qDebug()<<&obstacles;
    return obstacles;
}
