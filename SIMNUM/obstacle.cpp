#include "obstacle.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "sommet.h"
#include "segment.h"
#include <QDebug>

obstacle::obstacle()
{
}

obstacle::obstacle(const obstacle & Obs)
{
    sommets=Obs.getSommet();
    segments=Obs.getSegment();
}

obstacle::obstacle(std::vector<sommet> soms, std::vector<segment> segs)
{
    sommets=soms;
    segments=segs;
}

void obstacle::clear()
{
    sommets.clear();
    segments.clear();
}

std::vector<sommet> obstacle::getSommet()const
{
    return sommets;
}

std::vector<segment> obstacle::getSegment()const
{
    return segments;
}

int obstacle::setSommetsFromTxt(QString& line)
{

    int code=-1;
    QRegularExpression RegNumbr("\([0-9]*[,\.]*[0-9]*;[0-9]*[,\.]*[0-9]*\)");
    QRegularExpression RegEndObs("#END_OBS");

    if (RegNumbr.match(line).hasMatch())
    {
        float X,Y;

        QString line_cpy_x=line;
        QString line_cpy_y=line;
        line_cpy_x.remove(QRegularExpression("[(]*[)]*"));
        line_cpy_y.remove(QRegularExpression("[(]*[)]*"));

        line_cpy_x.remove(QRegularExpression(";.*"));
        line_cpy_y.remove(QRegularExpression(".*;"));

        convertToPointDecimal(line_cpy_x);
        convertToPointDecimal(line_cpy_y);

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

    return code;
}

void obstacle::setSegmentsFromSommets()
{
    for (unsigned int i=0;i<(sommets.size())-1;i++)
    {
        segment S(sommets[i],sommets[i+1]);
        segments.push_back(S);

    }
    segment S(sommets[sommets.size()-1],sommets[0]);
    segments.push_back(S);
}

void obstacle::convertToPointDecimal(QString& str)
{
    unsigned n = str.size();
    for(unsigned i = 0 ; i < n ; i++)
    {
        if(str[i]==',')
            str[i]='.';
    }
}

bool obstacle::TestInside ( const sommet S)
{

    std::vector<sommet> vect_sommets(sommets);
    std::vector<segment> vect_segments(segments);

    std::vector<segment> normales;
    std::vector<bool> tests;

    float X=S.Xcoord();
    float Y=S.Ycoord();

    int N=0;
    bool T;

    for ( unsigned int i=0; i<(segments.size()); i++)
    {
        segment tmpseg=vect_segments.back();
        segment tmpnorm=tmpseg.normale();
        normales.push_back(tmpnorm);
        vect_segments.pop_back();

        sommet A=normales.back().getSommet().first;
        sommet B=normales.back().getSommet().second;

        //Coordonnnées des deux sommets définissant le segment i
        float x1=sommets[i].Xcoord();
        float y1=sommets[i].Ycoord();
        float x2=sommets[i++].Xcoord();
        float y2=sommets[i++].Ycoord();

        //Pente et ordonée à l'origine de la droite portant le segment i
        float a=(y1-y2)/(x1-x2);
        float b=y1-a*x1;

        //Abscisse du point d'intersection de l'horizontale passant par S avec la droite
        float xI=(Y-b)/a;

        //Test si le point d'intersection est bien sur le segment et compte le nombre de points d'intersection
        if (((x1<x2)&&(xI>=x1)&&(xI<=x2))||((x1>x2)&&(xI>=x2)&&(xI<=x1)))
        {N=N+1;}

    }

    //Test sur la parité de N : si il est impair le point est dans l'obstacle, sinon il est à l'extérieur
    if (N%2==0)
        {T=false;}
    else
        {T=true;}

    return T; //true : le point est dedans ; false il est à l'extérieur
}

bool obstacle::Traverse ( segment  seg, int n)
{
    bool T;
    std::vector<bool> tests;
    std::vector<sommet> points=seg.Discret(n) ;
    //Discrétisation du segment en n points

    //Boucle sur tous les points : on teste pour chacun d'entre eux si il est dans l'obstacle

    for (int i=0; i<points.size(); i++)
    {
        tests.push_back(TestInside(points[i])); //test sur chaque point

        //test final
        if(tests[i]==true)
        {
            break;
            T=true;
        }
        else
        {T=false;}
    }

    return T; //Renvoie "true" si ça traverse (cad si un des points du segment est dedans) et "false" sinon
}
