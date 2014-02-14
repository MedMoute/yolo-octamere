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
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    std::vector<sommet>*sommets(0);
    sommets =new std::vector<sommet>;

    std::vector<sommet>*sommets_tmp(0);
    sommets_tmp =new std::vector<sommet>;
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

            int l=curObst->getSommet().size();

            for (int i=0;i<l;i++)
            {
                sommets_tmp->push_back(curObst->getSommet().back());
                curObst->getSommet().pop_back();
            }

            l=sommets_tmp->size();

            for (int i=0;i<l;i++)
            {
                sommets->push_back(sommets_tmp->back());
                sommets_tmp->pop_back();
                //qDebug()<<sommets->size();
            }

            std::vector<segment>*segments(0);
            segments =new std::vector<segment>;

            //obstacle obst(sommets,segments);
            //Envir.push_back(obst);
            qDebug()<<Envir.front().getSommet().front().Ycoord();

        }
        else
        {
            std::cout<<"Point non valide."<<std::endl;
            std::cout<<"Abandon de la recherche des points."<<std::endl;
            return;
        }
    }
    qDebug()<<"test";
}


