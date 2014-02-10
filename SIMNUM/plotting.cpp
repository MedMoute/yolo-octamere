#include "plotting.h"
#include <QFile>
#include <QTextStream>

plotting::plotting()
{
}

void plotting::setDatas(QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        //process_line(line);
    }
}
