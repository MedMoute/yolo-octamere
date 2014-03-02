#ifndef OBSTACLE_H
#define OBSTACLE_H

#include<queue>
#include <QString>
#include <list>
#include<sommet.h>
#include<segment.h>
#include<arc.h>
#include "utility"

class obstacle
{
public:
    obstacle();
    obstacle(const obstacle& Obs);
    obstacle(std::vector<sommet>,std::vector<segment>);

    void clear();

    std::vector<sommet> getSommet()const;
    std::vector<segment> getSegment()const;

    int setSommetsFromTxt(QString & line); //Teste une regex pour voir si la ligne correspond à un point - Retour le code suivant : 0=bon 1=fin d'obstacle "#FIN_OBS" -1 sinon.
    void setSegmentsFromSommets();
    void setArcsFromSegments();
    
    bool TestInside (const obstacle & Obs, const sommet S);
    void convertToPointDecimal(QString& str);

private:
    std::vector<sommet> sommets;
    std::vector<segment> segments;
    std::vector<arc> arcs;
};

#endif // OBSTACLE_H
