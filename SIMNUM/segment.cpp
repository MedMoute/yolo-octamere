#include "segment.h"
#include "math.h"
#include <QDebug>


segment::segment() //constructeur par dÃ©faut
{
    sommet S1;
    sommet S2;
}

segment::segment(sommet A, sommet B) //constructeur avec valeur
{
    S1=A;
    S2=B;
    coords.first=S2.Xcoord()-S1.Xcoord();
    coords.second=S2.Ycoord()-S1.Ycoord();
}

segment::segment(sommet S, std::pair<double, double> _coords)
{
    S1=S;
    coords=_coords;
    sommet _S2(S.Xcoord()+_coords.first,S.Ycoord()+_coords.second);
    S2=_S2;
}

pairsom segment::getSommet() const
{
    pairsom pair=std::make_pair(S1, S2);
    return pair;
}

segment::~segment() //destructeur
{
}

segment & segment::operator = (const segment & seg) //operateur =
{
    S1 = seg.getSommet().first;
    S2 = seg.getSommet().second;
    coords.first=S2.Xcoord()-S1.Xcoord();
    coords.second=S2.Ycoord()-S1.Ycoord();

    return * this;
}

float segment::longueur(segment seg) //longueur d'un segment
{
    float l;
    //RÃ©cupÃ©ration des coordonnÃ©es
    sommet S1 = seg.getSommet().first;
    sommet S2 = seg.getSommet().second;
    float x1= S1.Xcoord();
    float y1= S1.Ycoord();
    float x2= S2.Xcoord();
    float y2= S2.Ycoord();
    //Calcul
    l = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    return l;

}

segment segment::normale() //normale au segment
{
    //qDebug()<<"flag";
    float x1= S1.Xcoord();
    float y1= S1.Ycoord();
    float x2= S2.Xcoord();
    float y2= S2.Ycoord();
    //qDebug()<<"Segment:("<<x1<<";"<<y1<<")->"<<"("<<x2<<";"<<y2<<")";
    //qDebug()<<"Normale:("<<y1<<";"<<x2<<")->"<<"("<<y2<<";"<<x1<<")";

    sommet Sperp1 (y1,x2);
    sommet Sperp2 (y2, x1);
    segment perp (Sperp1, Sperp2);
    return perp;
}

std::vector<sommet> segment::Discret(int n)
{
    float x1 = S1.Xcoord();
    float y1 = S1.Ycoord();
    float x2 = S2.Xcoord();
    float y2 = S2.Ycoord();

    float a = (y2-y1)/(x2-x1); //pente du segment
    float b = y2-a*x2; //ordonnée a l'origine
    float eps = sqrt(pow(y2-y1,2)+pow(x2-x1,2))/(n+1); //pas de discrétisation
    float Cos = x1/sqrt(pow(y1-b,2)+pow(x1,2));

    std::vector<sommet> points;

    for (int i=0; i<n; i++)
    {
        float x = x1+ i*eps*Cos;
        float y = x*a+b;
        sommet som(x,y);
        points.push_back(som);
    }

    return points;
}

sommet segment::projOrth(sommet C)
{
    //qDebug()<<"Projection de ("<<C.Xcoord()<<";"<<C.Ycoord()<<") sur"<<"("<<S1.Xcoord()<<";"<<S1.Ycoord()<<")->"<<"("<<S2.Xcoord()<<";"<<S2.Ycoord()<<")";
    sommet A=S1;
    segment AC(A,C);
    segment AB(S1,S2);

    float Long=sqrt((AB.getCoords().first)*(AB.getCoords().first)+(AB.getCoords().second)*(AB.getCoords().second));

    float P=coords.first*AC.getCoords().first+coords.second*AC.getCoords().second;
    float Pnorm=P/((Long)*(Long));
    //qDebug()<<Pnorm<<"="<<P<<"/"<<Long<<"²";
    double Coord_pX=Pnorm*coords.first;
    double Coord_pY=Pnorm*coords.second;


    std::pair<double,double> P_Coords=std::make_pair(Coord_pX,Coord_pY);
    segment Proj(A,P_Coords);

   // qDebug()<<"Résultat: ("<<Proj.getSommet().second.Xcoord()<<";"<<Proj.getSommet().second.Ycoord()<<")";
    return Proj.getSommet().second;
}

std::pair<double,double> segment::getCoords()
{
    return coords;
}

void segment::setCoords(std::pair<double,double> _coord)
{
    coords=_coord;
}
