#include "obstacle.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "sommet.h"
#include "segment.h"
#include <QDebug>

obstacle::obstacle()
{
}

obstacle::obstacle(const obstacle & Obs)
{
    sommets=Obs.getSommet();
    segments=Obs.getSegment();
}

obstacle::obstacle(std::vector<sommet> soms, std::vector<segment> segs)
{
    sommets=soms;
    segments=segs;
}

void obstacle::clear()
{
    sommets.clear();
    segments.clear();
}

std::vector<sommet> obstacle::getSommet()const
{
    return sommets;
}

std::vector<segment> obstacle::getSegment()const
{
    return segments;
}

int obstacle::setSommetsFromTxt(QString& line)
{

    int code=-1;
    QRegularExpression RegNumbr("\([0-9]*[,\.]*[0-9]*;[0-9]*[,\.]*[0-9]*\)");
    QRegularExpression RegEndObs("#END_OBS");

    if (RegNumbr.match(line).hasMatch())
    {
        float X,Y;

        QString line_cpy_x=line;
        QString line_cpy_y=line;
        line_cpy_x.remove(QRegularExpression("[(]*[)]*"));
        line_cpy_y.remove(QRegularExpression("[(]*[)]*"));

        line_cpy_x.remove(QRegularExpression(";.*"));
        line_cpy_y.remove(QRegularExpression(".*;"));

        convertToPointDecimal(line_cpy_x);
        convertToPointDecimal(line_cpy_y);

        X=line_cpy_x.toFloat();
        Y=line_cpy_y.toFloat();

        sommet S(X,Y);
        sommets.push_back(S);

        code=0;
    }

    else if (RegEndObs.match(line).hasMatch())
    {
        code=1;
    }

    return code;
}

void obstacle::setSegmentsFromSommets()
{
    for (unsigned int i=0;i<(sommets.size())-1;i++)
    {
        segment S(sommets[i],sommets[i+1]);
        segments.push_back(S);

    }
    segment S(sommets[sommets.size()-1],sommets[0]);
    segments.push_back(S);
}

void obstacle::convertToPointDecimal(QString& str)
{
    unsigned n = str.size();
    for(unsigned i = 0 ; i < n ; i++)
    {
        if(str[i]==',')
            str[i]='.';
    }
}

bool obstacle::TestInside ( const sommet S)
{
    //qDebug()<<"("<<S.Xcoord()<<";"<<S.Ycoord()<<")";
    std::vector<sommet> vect_sommets(sommets);
    std::vector<segment> vect_segments(segments);

    std::vector<segment> normales;
    float X=S.Xcoord();
    float Y=S.Ycoord();

    int Ndroite=0;
    int Ngauche=0;
    bool T;

    for ( unsigned int i=0; i<(segments.size()); i++)
    {
        segment tmpseg=vect_segments.back();
        segment tmpnorm=tmpseg.normale();
        normales.push_back(tmpnorm);
        vect_segments.pop_back();

        sommet A=normales.back().getSommet().first;
        sommet B=normales.back().getSommet().second;

        //Coordonnnées des deux sommets définissant le segment i
        float x1=sommets[i].Xcoord();
        float y1=sommets[i].Ycoord();
        float x2=sommets[i+1].Xcoord();
        float y2=sommets[i+1].Ycoord();

        //Pente et ordonée à l'origine de la droite portant le segment i
        float a=(y1-y2)/(x1-x2);
        float b=y1-a*x1;

        if ((a==0)&&(Y==b))
        {
            if ((((x1<x2)&&(X>=x1)&&(X<=x2))||((x1>x2)&&(X>=x2)&&(X<=x1))))
            //On entre a la main les valeurs de Ngauche et Ndroite pour obtenir le bon résultat avec le test final
            {Ngauche=1;
            Ndroite=1;}
            }
        else if ((a==0)&&(Y!=b))
        {Ngauche=2;
        Ndroite=2;}
        else
        {
        //Abscisse du point d'intersection de l'horizontale passant par S avec la droite
        float xI=(Y-b)/a;
        qDebug()<<xI;
        //Test si le point d'intersection est bien sur le segment et compte le nombre de points d'intersection
        if ((((x1<x2)&&(xI>=x1)&&(xI<=x2))||((x1>x2)&&(xI>=x2)&&(xI<=x1)))&&(xI<=X))
        {Ngauche=Ngauche+1;}
        else if ((((x1<x2)&&(xI>=x1)&&(xI<=x2))||((x1>x2)&&(xI>=x2)&&(xI<=x1)))&&(xI>=X))
        {Ndroite=Ndroite+1;};
        }

    }

    //Test sur la parité de N : si il est impair le point est dans l'obstacle, sinon il est à l'extérieur
    if ((Ngauche%2==0)&&(Ndroite%2==0))
    {T=false;}
    else
    {T=true;}
    //qDebug()<<"test inside : "<<T;

    return T; //true : le point est dedans ; false il est à l'extérieur
}

//Autre version de testInside
//
/*bool obstacle::TestInside (const sommet S)
{
    float X=S.Xcoord();
    float Y=S.Ycoord();
            //qDebug()<<X<<"   "<<Y;

    int coupeGauche=0;
    int coupeDroite=0;
    for (unsigned int i=0; i<(sommets.size()); i++)//attention Ã  bien gÃ©rer le dernier segment
    {
        float X1_temp;
        float X2_temp;
        float Y1_temp;
        float Y2_temp;

        if (i==sommets.size())
        {
            X1_temp=sommets[i].Xcoord();
            X2_temp=sommets[0].Xcoord();
            Y1_temp=sommets[i].Ycoord();
            Y2_temp=sommets[0].Ycoord();
        }
        else
        {
            X1_temp=sommets[i].Xcoord();
            X2_temp=sommets[i+1].Xcoord();
            Y1_temp=sommets[i].Ycoord();
            Y2_temp=sommets[i+1].Ycoord();
        }

        float Xcut=X1_temp+(X2_temp-X1_temp)*(Y-Y1_temp)/(Y2_temp-Y1_temp);


        if((Xcut>=X1_temp&&Xcut<=X2_temp)||(Xcut<=X1_temp&&Xcut>=X2_temp))
        {
            if (Xcut<X)
            {
                coupeGauche++;
            }
            else if (Xcut>X)
            {
                coupeDroite++;
            }
            else
            {
                coupeDroite++;
                coupeGauche++;
            }
        }
    }
   // qDebug()<<coupeDroite<<"       "<<coupeGauche;
    if (coupeDroite%2==1||coupeGauche%2==1)
    {
        return true;
    }
    else
    {
        //qDebug()<<"on est pas dedaaaaaans !";
        return false;
    }
}
*/
bool obstacle::Traverse ( segment  seg, int n)
{
    bool T;
    std::vector<bool> tests;
    std::vector<sommet> points;
    points=seg.Discret(n);

    for (int i=0; i<points.size(); i++)
    {
        tests.push_back(TestInside(points[i])); //test sur chaque point
        //test final
        if(tests[i]==true)
        {
            break;
            T=true;
        }
        else
        {T=false;}
    }

    return T; //Renvoie "true" si ça traverse (cad si un des points du segment est dedans) et "false" sinon
}

bool obstacle::TraverseConvexe(segment seg)
{
    bool T;
    std::vector<bool> tests;
 //   std::vector<segment> droites;
    std::vector<sommet> projetes;
    for (int i=0; i<sommets.size(); i++)
    {
        projetes.push_back(seg.projOrth(sommets[i]));
        tests.push_back(TestInside(projetes[i]));
        if (tests[i]==true)
        {break;
            T=true;}
        else
            {T=false;}
     }

    return T; //Renvoie "true" si ça traverse (cad si un des points du segment est dedans) et "false" sinon
}
