#ifndef PLOTTING_H
#define PLOTTING_H

#include "sommet.h"
#include "environnement.h"
#include <QPen>
#include <QString>

typedef std::pair< std::vector< double > , std::vector< double > > dataarray;

class plotting
{
public:
    plotting();
    void drawLine(sommet p1,sommet p2);
    void drawPolygon(sommet* point_ptr);

    dataarray* getDatas();
    void setDatas();

    QString getFileName();
    void setFileName(QString);

    environnement* getObstacles();

private:
    QString fileName;
    QPen pen;
    dataarray* datas;
    environnement* obstacles;

};



#endif // PLOTTING_H
