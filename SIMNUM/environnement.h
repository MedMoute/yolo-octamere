#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include "sommet.h"
#include "segment.h"
#include "obstacle.h"
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
    void setPoints(QString path);
    void resetEnviron();

    std::list<obstacle> getEnvir();

private:
    obstacle curObst;
    std::list<obstacle> Envir;
};

#endif // ENVIRONNEMENT_H
