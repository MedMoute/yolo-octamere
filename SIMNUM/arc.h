#ifndef ARC_H
#define ARC_H
#include "segment.h"

class arc
{
private :
    segment seg;
    float l;

public :
    arc();
    segment getSegment() const;
    float getLong() const;
    arc (segment segseg);
    ~arc ();
    arc & operator = (const arc & A);

};

#endif // ARC_H
