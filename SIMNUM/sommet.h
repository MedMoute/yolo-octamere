#ifndef SOMMET_H
#define SOMMET_H

class sommet
{
private :
    float x;
    float y;
public:
    float & Xcoord();
    float & Ycoord();
    sommet();
    sommet(float p, float q);
    ~sommet ();
    sommet & operator = (sommet & S);


};

#endif // SOMMET_H
