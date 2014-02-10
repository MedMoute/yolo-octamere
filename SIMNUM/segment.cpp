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



    S1.operator =( seg.getSommet().first);
    S2.operator =( seg.getSommet().second);
    return * this;
}

float  segment::longueur(segment & seg)
{
    float l;
    S1.operator =( seg.getSommet().first);
    S2.operator =( seg.getSommet().second);
    float x1= S1.Xcoord();
    float y1= S1.Ycoord();
    float x2= S2.Xcoord();
    float y2= S2.Ycoord();
    l = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));;
    return l;

}


