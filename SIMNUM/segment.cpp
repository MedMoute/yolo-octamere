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

pairsom segment::getSommet()
  {
    pairsom pair=std::make_pair(S1, S2);
    return pair;
}

segment::~segment() //destructeur
{ delete [] &S1;
     delete [] &S2;
}

segment & segment::operator = (segment & seg) //operateur =
{
    //delete &S1;
    //delete &S2;

 pairsom pair=std::make_pair(S1, S2);
 pair.first;

    S1 =(seg.getSommet()).first;
    S2 = seg.getSommet().second;
    return * this;
};
float  longueur(const segment & seg)
{
    float l
    S1= seg.getSommet().first;
    S2= seg.getSommet().second;
    x1= S1.Xcoord();
    y1= S1.Ycoord();
    x2= S2.Xcoord();
    y2= S2.Ycoord();
    l = sqrt((x2-x1)^2+(y2-y1)^2);;
    return l;

}


