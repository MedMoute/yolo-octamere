#include "segment.h"
#include "math.h"


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
{ delete [] &S1;
     delete [] &S2;
}

segment & segment::operator = (const segment & seg) //operateur =
{
    S1 = seg.getSommet().first;
    S2 = seg.getSommet().second;

    return * this;
}

float segment::longueur(const segment & seg) //longueur d'un segment
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
    l = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));;
    return l;

}

segment segment::normale(const segment & seg) //normale au segment
{
    sommet S1 = seg.getSommet().first;
    sommet S2 = seg.getSommet().second;
    float x1= S1.Xcoord();
    float y1= S1.Ycoord();
    float x2= S2.Xcoord();
    float y2= S2.Ycoord();

    sommet Sperp1 (y2,x1);
    sommet Sperp2 (y1, x2);
    segment perp (Sperp1, Sperp2);
    return perp;
}



