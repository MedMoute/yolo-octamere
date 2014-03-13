#include "environnement.h"
#include <QDebug>
#include "sommet.h"
#include "vector"
#include<cmath>

#define Pi 3.14159265

environnement::environnement()
{
}

void environnement::setEnvironment(QString path)
{
    envirPath=path;
    setPoints(path,false,-1);
}
void environnement::setEnvironment(QString path,float _padding,int _preci,int _mode)
{
    envirPath=path;
    setPadding(_padding);
    setPrecision(_preci);
    setPoints(path,true,_mode);

}

void environnement::setPadding(float _padding)
{
    padding=_padding;
}

void environnement::setPrecision(int _preci)
{
    precision=_preci;
}

void environnement::setPoints(QString path,bool b,int mode)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        int j;

        j=curObst.setSommetsFromTxt(line);

        if (j==0) //On détecte un point
        {
            // qDebug()<<"Point détécté";
        }
        else if (j==1)//On détecte le parser de fin d'obstacle
        {
            // qDebug()<<"Fin de l'obstacle"; //Dump de curObst dans Envir
            // qDebug()<<"L'obstacle contient :"<<curObst.getSommet().size()<<" points.";
            curObst.setSegmentsFromSommets();
            if (b==true)//modif des points pour s'adapter au padding
            {
                obstacle obst(curObst);
                std::vector<sommet> soms;
                std::vector<segment>segs;
                if (mode==1)//Mode évolué
                {
                    for (unsigned int i=0;i<obst.getSegment().size();i++)//Pour tout les points on détermine les segments antérieurs et ultérieurs
                    {
                        sommet curSom=obst.getSommet()[i];
                        segment  seg_ant;
                        segment  seg_ult;
                        if (i==0)
                        {
                            segment  seg_ant_t(obst.getSommet()[obst.getSegment().size()-1],obst.getSommet()[i]);
                            segment  seg_ult_t(obst.getSommet()[i],obst.getSommet()[i+1]);
                            seg_ant=seg_ant_t;
                            seg_ult=seg_ult_t;
                        }
                        else if(i==obst.getSommet().size()-1)
                        {
                            segment seg_ant_t(obst.getSommet()[i-1],obst.getSommet()[i]);
                            segment seg_ult_t(obst.getSommet()[i],obst.getSommet()[0]);
                            seg_ant=seg_ant_t;
                            seg_ult=seg_ult_t;
                        }
                        else
                        {
                            segment seg_ant_t(obst.getSommet()[i-1],obst.getSommet()[i]);
                            segment seg_ult_t(obst.getSommet()[i],obst.getSommet()[i+1]);
                            seg_ant=seg_ant_t;
                            seg_ult=seg_ult_t;
                        }
                        float lg=seg_ant.longueur(seg_ant);
                        double X_Vn=seg_ant.getCoords().first;
                        double Y_Vn=seg_ant.getCoords().second;

                        double X_Un=curSom.Xcoord()+X_Vn/lg*padding;
                        double Y_Un=curSom.Ycoord()+Y_Vn/lg*padding;
                        sommet som(X_Un,Y_Un);
                        if (obst.TestInside(som))//Le point ainsi défini est dans l'obstacle; on définit le nouveau point comme un point de la bissectrice éloigné de  padding/sin(a/2) a=angle(seg_ant,seg_ult)
                        {
                            double X_bis=seg_ant.getCoords().first-seg_ult.getCoords().first;
                            double Y_bis=seg_ant.getCoords().second-seg_ult.getCoords().second;
                            segment seg_bis(curSom,std::make_pair(X_bis,Y_bis));
                            double long_bis=seg_bis.longueur(seg_bis);

                            double alpha=acos((seg_ant.getCoords().first*seg_ult.getCoords().first+seg_ant.getCoords().second*seg_ult.getCoords().second)/(seg_ant.longueur(seg_ant)*seg_ult.longueur(seg_ult)));
                            double X=padding/(sin(alpha/2));
                            double X_bis_fin=X_bis/long_bis*X;
                            double Y_bis_fin=Y_bis/long_bis*X;
                            segment seg_bis_fin(curSom,std::make_pair(X_bis_fin,Y_bis_fin));

                            sommet newSom=seg_bis_fin.getSommet().second;
                            soms.push_back(newSom);
                        }
                        else //le point curSom est donc en dehors de l'obstacle on crée un nombre N de points pour arondir les bords de l'angle de seg_ant à celui de seg_ult
                        {
                            double X=curSom.Xcoord();
                            double Y=curSom.Ycoord();

                            double B_ant=atan(seg_ant.getCoords().second/seg_ant.getCoords().first);
                            double B_ult=atan(seg_ult.getCoords().second/seg_ult.getCoords().first);
                            double alpha;
                                alpha=Pi-std::abs(B_ult-B_ant);

                            for(int k=0;(2*k*Pi/precision)<(std::abs(Pi-alpha));k++)
                            {
                                double Xi=padding*cos(2*Pi*k/precision-(B_ant)+Pi/2);
                                double Yi=padding*sin(2*Pi*k/precision-(B_ant)+Pi/2);
                                sommet newSom(X+Xi,Y+Yi);
                                soms.push_back(newSom);

                            }
                        }
                    }

                    obstacle new_obst(soms,segs);
                    curObst=new_obst;
                    curObst.setSegmentsFromSommets();
                }
                else
                {
                    for (unsigned int i=0;i<obst.getSegment().size();i++)//Pour tout les points
                    {
                        sommet curSom=obst.getSommet()[i];
                        double X=curSom.Xcoord();
                        double Y=curSom.Ycoord();
                        for(int k=0;k<precision;k++)
                        {
                            double Xi=padding*cos(2*Pi*k/precision);
                            double Yi=padding*sin(2*Pi*k/precision);
                            sommet newSom(X+Xi,Y+Yi);
                            soms.push_back(newSom);
                        }
                    }
                    obstacle new_obst(soms,segs);
                    curObst=new_obst;
                    curObst.setSegmentsFromSommets();
                }
            }

            Envir.push_back(curObst);
            curObst.clear();
        }
        else
        {
            // std::cout<<"Point non valide."<<std::endl;
            // std::cout<<"Abandon de la recherche des points."<<std::endl;
            return;
        }
    }
}

std::list<obstacle> environnement::getEnvir()
{
    return Envir;
}


void environnement::resetEnviron()
{
    curObst.clear();
    Envir.clear();
}

QString environnement::getenvirPath()
{
    return envirPath;
}
