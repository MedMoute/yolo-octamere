#include "arc.h"
#include "segment.h"

arc::arc() //constructeur par défaut
{
 segment seg;
 l=seg.longueur(seg);
}

segment arc::getSegment() const //récupère les trucs dans private
{
    return seg;
}

float arc::getLong() const
{
    return l;
}

arc::arc(segment segseg) //constructeur avec valeur
{
  seg=segseg;
  l=seg.longueur(seg);
}

arc::~arc() //destructor
{
}

arc & arc::operator = (const arc & A) //opérateur =
{
    seg=A.getSegment();
    l=seg.longueur(seg);
    return * this;
}
