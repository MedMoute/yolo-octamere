#include "obstacle.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "sommet.h"
#include "segment.h"
#include <math.h>
#include <float.h>
#include <QDebug>

#define PI 3.14159265

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
    float X=S.Xcoord();
    float Y=S.Ycoord();

    int Ndroite=0;
    int Ngauche=0;
    bool T=false;

    for ( unsigned int i=0; i<(segments.size()); i++)
    {
        //Coordonnnées des deux sommets définissant le segment i
        float x1;
        float y1;
        float x2;
        float y2;
        if (i==segments.size()-1)
        {
            x1=sommets[i].Xcoord();
            y1=sommets[i].Ycoord();
            x2=sommets[0].Xcoord();
            y2=sommets[0].Ycoord();
        }
        else
        {
            x1=sommets[i].Xcoord();
            y1=sommets[i].Ycoord();
            x2=sommets[i+1].Xcoord();
            y2=sommets[i+1].Ycoord();
        }

        //Pente et ordonée à l'origine de la droite portant le segment i
        float a=(y1-y2)/(x1-x2);//Pente
        float b=y1-a*x1;//Ordonnée à l'origine

        if ((a!=0)&&(IsFiniteNumber(a)))//Segment non horizontal ou non vertical
        {
            //Abscisse du point d'intersection de l'horizontale passant par S avec la droite
            float xI=(Y-b)/a;

            //qDebug()<<xI;

            if(Y==xI*a)//Test du cas ou le point intersecte le segment : on considère que le point n'est PAS dans l'obstacle
            {
                break;
            }

            //Test si le point d'intersection est bien sur le segment et compte le nombre de points d'intersection
            else if ((((x1<x2)&&(xI>=x1)&&(xI<=x2))||((x1>x2)&&(xI>=x2)&&(xI<=x1)))&&(xI<=X))
            {
                Ngauche++;
            }
            else if ((((x1<x2)&&(xI>=x1)&&(xI<=x2))||((x1>x2)&&(xI>=x2)&&(xI<=x1)))&&(xI>=X))
            {
                Ndroite++;
            }
        }
        else//segment horizontal ou vertical : rotation des points
        {
            float Xr=((sqrt(2)/2)*X-(sqrt(2)/2)*Y);
            float Yr=((sqrt(2)/2)*X+(sqrt(2)/2)*Y);

            if (i==segments.size()-1)
            {
                x1=(sqrt(2)/2)*sommets[i].Xcoord()-(sqrt(2)/2)*sommets[i].Ycoord();
                y1=(sqrt(2)/2)*sommets[i].Ycoord()+(sqrt(2)/2)*sommets[i].Xcoord();
                x2=(sqrt(2)/2)*sommets[0].Xcoord()-(sqrt(2)/2)*sommets[0].Ycoord();
                y2=(sqrt(2)/2)*sommets[0].Ycoord()+(sqrt(2)/2)*sommets[0].Xcoord();
            }
            else
            {
                x1=(sqrt(2)/2)*sommets[i].Xcoord()-(sqrt(2)/2)*sommets[i].Ycoord();
                y1=(sqrt(2)/2)*sommets[i].Ycoord()+(sqrt(2)/2)*sommets[i].Xcoord();
                x2=(sqrt(2)/2)*sommets[i+1].Xcoord()-(sqrt(2)/2)*sommets[i+1].Ycoord();
                y2=(sqrt(2)/2)*sommets[i+1].Ycoord()+(sqrt(2)/2)*sommets[i+1].Xcoord();
            }

            //Pente et ordonée à l'origine de la droite portant le segment i
            float a=(y1-y2)/(x1-x2);//Pente

            float b=y1-a*x1;//Ordonnée à l'origine

            float xI=(Yr-b)/a;

            //qDebug()<<xI;

            if(Y==xI*a)//Test du cas ou le point intersecte le segment : on considère que le point n'est PAS dans l'obstacle
            {
                break;
            }

            //Test si le point d'intersection est bien sur le segment et compte le nombre de points d'intersection
            else if ((((x1<x2)&&(xI>=x1)&&(xI<=x2))||((x1>x2)&&(xI>=x2)&&(xI<=x1)))&&(xI<=Xr))
            {
                Ngauche++;
            }
            else if ((((x1<x2)&&(xI>=x1)&&(xI<=x2))||((x1>x2)&&(xI>=x2)&&(xI<=x1)))&&(xI>=Xr))
            {
                Ndroite++;
            }

        }

    }

    if ((Ngauche%2==0)&&(Ndroite%2==0))    //Test sur la parité de N : si il est impair le point est dans l'obstacle, sinon il est à l'extérieur
    {
        T=false;
    }
    else
    {
        T=true;
    }
    return T; //true : le point est dedans ; false il est à l'extérieur
}

bool obstacle::Traverse ( segment  seg, int n)
{
    bool T;
    std::vector<sommet> points;
    points=seg.Discret(n);

    for (unsigned int i=1; i<points.size()-1; i++)
    {
        T=TestInside(points[i]); //test sur chaque point

        if (T==true)
        {
            break;
        }
    }

    return T; //Renvoie "true" si ça traverse (cad si un des points du segment est dedans) et "false" sinon
}

bool obstacle::TraverseConvexe(segment seg)
{
    bool T;

    std::vector<bool> tests;
    //   std::vector<segment> droites;
    std::vector<sommet> projetes;
    for (unsigned int i=0; i<sommets.size(); i++)
    {
        projetes.push_back(seg.projOrth(sommets[i]));
        tests.push_back(TestInside(projetes[i]));
        if (tests[i]==true)
        {break;
            T=true;}
        else
        {T=false;}
    }

    return T; //Renvoie "true" si ça traverse (cad si un des points du segment est dedans) et "false" sinon
}
bool IsFiniteNumber(double x)
{
    return (x <= DBL_MAX && x >= -DBL_MAX);
}
