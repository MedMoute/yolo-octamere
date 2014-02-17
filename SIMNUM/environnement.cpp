#include "environnement.h"
#include <QDebug>
#include "sommet.h"
#include "vector"

environnement::environnement()
{
}

void environnement::setEnvironment(QString path)
{
    setPoints(path);
}

void environnement::setPoints(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();

        int j=curObst.setSommetsFromTxt(line);
        if (j==0) //On détecte un point
        {
            qDebug()<<"Point détécté";
        }
        else if (j==1)//On détecte le parser de fin d'obstacle
        {
            qDebug()<<"Fin de l'obstacle"; //Dump de curObst dans Envir
            qDebug()<<"L'obstacle contient :"<<curObst.getSommet().size()<<" points.";
            curObst.setSegmentsFromSommets();
            Envir.push_back(curObst);
            curObst.clear();
        }
        else
        {
            std::cout<<"Point non valide."<<std::endl;
            std::cout<<"Abandon de la recherche des points."<<std::endl;
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
