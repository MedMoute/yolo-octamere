#include "sommet.h"

sommet::sommet() //constructeur par défaut
{
    x=0;
    y=0;
}

sommet::sommet(float p, float q) //constructeur avec valeur
{
    x=p;
    y=q;
}
float & sommet::Xcoord()
{return x;}
float & sommet::Ycoord()
{return y;}
sommet::~sommet() //destructeur
{ delete [] &x;
     delete [] &y;
}

sommet & sommet::operator = (sommet  S) //operateur =
{
    delete [] &x;
        x=S.Xcoord();

    delete[] &y;
        y=S.Ycoord();

    return * this;};
