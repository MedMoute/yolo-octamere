#ifndef SEGMENT_H
#define SEGMENT_H
#include <stdlib.h>
#include "utility"
#include "sommet.h"



class sommet;
typedef std::pair<sommet,sommet> pairsom;

class segment
{
private :
    sommet S1;
    sommet S2;
public:

    pairsom getSommet();
    segment();
    segment(sommet A, sommet B);
    ~segment ();
    segment & operator = (segment & seg);
    float  longueur(segment & seg);

};

#endif // SEGMENT_H
