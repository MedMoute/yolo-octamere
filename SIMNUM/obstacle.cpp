#include "obstacle.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "sommet.h"
#include "segment.h"
#include <QDebug>

obstacle::obstacle()
{
}

/*obstacle::obstacle(obstacle & Obs)
{
    sommets=Obs.getSommet();
    segments=Obs.getSegment();
}

obstacle::obstacle(std::list<sommet> soms, std::list<segment> segs)
{
    sommets=soms;
    segments=segs;
}*/

obstacle::~obstacle()
{
    sommets.clear();
    segments.clear();
}

std::vector<sommet> obstacle::getSommet()
{
    return sommets;
}

std::vector<segment> obstacle::getSegment()
{
    return segments;
}

int obstacle::setSommetsFromTxt(QString line)
{
        qDebug()<<"On est dans Obstacle";
    int code=-1;
    QRegularExpression RegNumbr("\([0-9]*[,\.]*[0-9]*;[0-9]*[,\.]*[0-9]*\)");
    QRegularExpression RegEndObs("#END_OBS");

    if (RegNumbr.match(line).hasMatch())
    {
        //Ajouter le point de la ligne
        float X,Y;

        QString line_cpy_x=line;
        QString line_cpy_y=line;
        line_cpy_x.remove(QRegularExpression("[(]*[)]*"));
        line_cpy_y.remove(QRegularExpression("[(]*[)]*"));

        line_cpy_x.remove(QRegularExpression(";.*"));
        line_cpy_y.remove(QRegularExpression(".*;"));

        X=line_cpy_x.toFloat();
        Y=line_cpy_y.toFloat();
        sommet S(X,Y);
        sommets.push_back(S);
        code=0;
    }
    else if (RegEndObs.match(line).hasMatch())
    {
        code=1;
    }
    else{}
    return code;
}

void obstacle::setSegmentsFromSommets()
{
    for (unsigned int i=0;i<(sommets.size())-1;i++)
    {
        segment S;//(sommets,sommets[i+1]);
        segments.push_back(S);
        qDebug()<<segments.size();
    }
}
