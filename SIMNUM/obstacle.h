#ifndef OBSTACLE_H
#define OBSTACLE_H

#include<queue>
#include <QString>
#include <list>
#include<sommet.h>
#include<segment.h>

class obstacle
{
public:
    obstacle();
    //obstacle(obstacle& Obs);
    obstacle(std::list<sommet>,std::list<segment>);
    ~obstacle();

    std::list<sommet> getSommet();
    std::list<segment> getSegment();

    int setSommetsFromTxt(QString line); //Teste une regex pour voir si la ligne correspond à un point - Retour le code suivant : 0=bon 1=fin d'obstacle "#FIN_OBS" -1 sinon.
    void setSegmentsFromSommets();
private:
    std::list<sommet> sommets;
    std::list<segment> segments;
};

#endif // OBSTACLE_H
