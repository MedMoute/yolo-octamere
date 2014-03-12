#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include "sommet.h"
#include "segment.h"
#include "obstacle.h"
#include "graphe.h"
#include <vector>
#include <QString>
#include <iostream>
#include <QFile>
#include <QTextStream>


class environnement
{
public:
    environnement();
    void setEnvironment(QString path);
    void setEnvironment(QString path,float _padding,int _preci,int mode);
    void setPoints(QString path,bool b,int mode);

    void resetEnviron();

    void setPadding(float _padding);
    void setPrecision(int _preci);

    std::list<obstacle> getEnvir();
    QString getenvirPath();

private:
    obstacle curObst;
    std::list<obstacle> Envir;
    QString envirPath;

    float padding;
    int precision;
};

#endif // ENVIRONNEMENT_H
