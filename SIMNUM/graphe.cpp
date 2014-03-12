#include "graphe.h"
#include <QDebug>

graphe::graphe() //constructeur par défaut
{
    std::list<arc> list;
    arcs=list;
}

std::list<arc> graphe::getGraph() const //Michel est privé
{
    return arcs;
}

graphe::graphe(std::list<arc> arks) //constructeur par copie
{
  arcs=arks;

}

graphe::~graphe() //destructor
{
}

graphe & graphe::operator = (const graphe & grph) //opérateur =
{
    arcs=grph.getGraph();
    return * this;
}

void graphe::setGraph( std::list<arc> & _graph)
{
    arcs=_graph;
}

std::vector< std::pair<sommet,float> > graphe::Recherche(sommet A)
{
        qDebug()<<"On entre ds Recherche";
    std::vector< std::pair<sommet,float> > l;
    std::list<arc> arclist=arcs;
    arc arctemp;
    for (unsigned int i=0; i<arcs.size(); i++)
    {
        arctemp=arclist.front();
        segment seg=arctemp.getSegment();
        pairsom soms=seg.getSommet();
        sommet som1=soms.first;
        sommet som2=soms.second;
        if ((som1.Xcoord()==A.Xcoord())&&(som1.Ycoord()==A.Ycoord()))
        {
            std::pair<sommet,float> couilles=std::make_pair(som2,arctemp.getLong());
            l.push_back(couilles);
        }

        else if ((som2.Xcoord()==A.Xcoord())&&(som2.Ycoord()==A.Ycoord()))
        {
            std::pair<sommet,float> couilles=std::make_pair(som1,arctemp.getLong());
            l.push_back(couilles);
        }

        arclist.pop_front();
    }

    qDebug()<<"On est sorti de Recherche";
    return l;
}
