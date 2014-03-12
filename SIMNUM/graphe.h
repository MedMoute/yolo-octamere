#ifndef GRAPHE_H
#define GRAPHE_H
#include "arc.h"
#include <list>

class graphe
{
public:
    graphe();
    std::list<arc> getGraph()const;
    void setGraph(std::list<arc> &);

    graphe (std::list<arc> arks); //Je me demande si ce jean-michel est vraiment nécessaire vu qu'on a déjà l'opérateur = (enfin je vais le faire)
    ~graphe ();
    graphe & operator = (const graphe & grph);
    std::vector< std::pair<sommet,float> > Recherche(sommet A); //Recherche les adjacents et donne la distance
 private :
    std::list<arc> arcs;
};

#endif // GRAPHE_H
