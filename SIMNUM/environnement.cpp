#include "environnement.h"
#include <QDebug>
#include "sommet.h"
#include "vector"

environnement::environnement()
{
    this->curObst = new obstacle;
}

void environnement::setEnvironment(QString path)
{
    setPoints(path);
}

void environnement::setPoints(QString path)
{
        qDebug()<<"On est dans Environnement";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    std::list<sommet> sommets_tmp;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();

        int j=curObst->setSommetsFromTxt(line);

        if (j==0)
        {
        }
        else if (j==1)
        {

    /*
     * Fin de l'obstacle
     * Dump de curObst dans Envir
    */

        }
        else
        {
            std::cout<<"Point non valide."<<std::endl;
            std::cout<<"Abandon de la recherche des points."<<std::endl;
            return;
        }
    }
    //qDebug()<<"test";
}


