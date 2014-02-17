#include "graphe.h"

graphe::graphe() //constructeur par défaut
{

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
    delete [] &arcs;
}

graphe & graphe::operator = (const graphe & grph) //opérateur =
{
    arcs=grph.getGraph();
    return * this;
}
