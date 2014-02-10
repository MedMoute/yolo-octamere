#ifndef PLOTTING_H
#define PLOTTING_H

#include "sommet.h"
#include <QPen>

typedef std::pair< std::vector< double > , std::vector< double > > dataarray;

class plotting
{
public:
    plotting();
    void drawLine(sommet p1,sommet p2);
    void drawPolygon(sommet* point_ptr);

    dataarray getDatas();

private:
    QPen pen;
    dataarray datas;
};



#endif // PLOTTING_H
