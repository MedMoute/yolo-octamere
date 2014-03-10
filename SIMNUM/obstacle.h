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
    
    

    bool TestInside (const sommet S); //Teste si un point est à l'intérieur de l'obstacle
    void convertToPointDecimal(QString& str);

    bool Traverse ( segment seg, int n);  //Pour savoir si un segment coupe un obstacle (non convexe) par discrétisation : plus n est grand, plus le test est précis
    bool TraverseConvexe(segment seg);  //Pour les obstacles convexes : test infaillible

private:
    std::vector<sommet> sommets;
    std::vector<segment> segments;
    std::vector<arc> arcs;
};
bool IsFiniteNumber(double x);
#endif // OBSTACLE_H
