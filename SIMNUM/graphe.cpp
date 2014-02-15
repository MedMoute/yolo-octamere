#include "graphe.h"

graphe::graphe() //constructeur par défaut
{

}

std::list<arc> graphe::getGraph() //
{
    return arcs;
}

graphe::graphe(graphe & grph) //constructeur par copie
{
  arcs=grph.getGraph();

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
