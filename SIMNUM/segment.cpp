#include "segment.h"
#include "math.h"
#include <QDebug>


segment::segment() //constructeur par défaut
{
    sommet S1;
    sommet S2;
}

segment::segment(sommet A, sommet B) //constructeur avec valeur
{
    S1=A;
    S2=B;
}

pairsom segment::getSommet() const
{
    pairsom pair=std::make_pair(S1, S2);
    return pair;
}

segment::~segment() //destructeur
{
}

segment & segment::operator = (const segment & seg) //operateur =
{
    S1 = seg.getSommet().first;
    S2 = seg.getSommet().second;

    return * this;
}

float segment::longueur(segment seg) //longueur d'un segment
{
    float l;
    //Récupération des coordonnées
    sommet S1 = seg.getSommet().first;
    sommet S2 = seg.getSommet().second;
    float x1= S1.Xcoord();
    float y1= S1.Ycoord();
    float x2= S2.Xcoord();
    float y2= S2.Ycoord();
    //Calcul
    l = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    return l;

}

segment segment::normale() //normale au segment
{
    //qDebug()<<"flag";
    float x1= S1.Xcoord();
    float y1= S1.Ycoord();
    float x2= S2.Xcoord();
    float y2= S2.Ycoord();
    //qDebug()<<"Segment:("<<x1<<";"<<y1<<")->"<<"("<<x2<<";"<<y2<<")";
    //qDebug()<<"Normale:("<<y1<<";"<<x2<<")->"<<"("<<y2<<";"<<x1<<")";

    sommet Sperp1 (y1,x2);
    sommet Sperp2 (y2, x1);
    segment perp (Sperp1, Sperp2);
    return perp;
}

std::vector<sommet> segment::Discret(int n)
{
    sommet S1 = this->getSommet().first;
    sommet S2 = this->getSommet().second;
    float x1 = S1.Xcoord();
    float y1 = S1.Ycoord();
    float x2 = S2.Xcoord();
    float y2 = S2.Ycoord();

    float a = (y2-y1)/(x2-x1); //pente du segment
    float b = y2-a*x2; //ordonnée a l'origine
    float eps = sqrt(pow(y2-y1,2)+pow(x2-x1,2))/(n+1); //pas de discrétisation
    float Cos = x1/sqrt(pow(y1-b,2)+pow(x1,2));

    std::vector<sommet> points;

    for (int i=0; i<n; i++)
    {
        float x = x1+ i*eps*Cos;
        float y = x*a+b;
        sommet som(x,y);
        points.push_back(som);
    }

    return points;
}

