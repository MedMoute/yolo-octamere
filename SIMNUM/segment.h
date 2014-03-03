#ifndef SEGMENT_H
#define SEGMENT_H
#include <stdlib.h>
#include "utility"
#include "sommet.h"
#include <vector>




class sommet;
typedef std::pair<sommet,sommet> pairsom;

class segment
{
private :
    sommet S1;
    sommet S2;
public:

    pairsom getSommet() const;
    segment();
    segment(sommet A, sommet B);
    ~segment ();
    segment & operator = (const segment & seg);
    float longueur(segment seg);
    segment normale();
    std::vector<sommet> Discret(int n); //Discrétise le segment en n points (plus les deux sommets)

};

#endif // SEGMENT_H
