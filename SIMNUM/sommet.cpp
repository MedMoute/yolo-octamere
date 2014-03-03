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
float sommet::Xcoord() const
{
    return x;
}
float sommet::Ycoord() const
{
    return y;
}
sommet::~sommet() //destructeur
{
 }

sommet & sommet::operator = (sommet S) //operateur =
{
          x=S.Xcoord();
          y=S.Ycoord();
    return * this;
}
