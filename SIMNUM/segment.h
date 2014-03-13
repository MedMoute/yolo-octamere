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
    std::pair<double,double> coords;
public:
    segment();
    segment(sommet A, sommet B);
    segment(sommet S,std::pair<double,double> coords);
    ~segment ();

    segment & operator = (const segment & seg);

    bool operator ==(const segment & seg);

    float longueur(segment seg);
    segment normale();
    pairsom getSommet() const;
    std::vector<sommet> Discret(int n); //DiscrÃ©tise le segment en n points (plus les deux sommets)
                                        //Plus utilisÃ©e : remplacÃ©e par la mÃ©thode des projections ortho
    sommet projOrth(sommet S);

    std::pair<double,double> getCoords();
    void setCoords(std::pair<double,double>);

};

#endif // SEGMENT_H
