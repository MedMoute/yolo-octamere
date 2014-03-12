#include "plotting.h"
#include <QDebug>
#include "qcustomplot.h"

plotting::plotting()
{
    this->obstacles = new environnement;
    this->graph=new graphe;
}

void plotting::drawEnvironment()
{
    std::list<obstacle> Environnement_tmp=obstacles->getEnvir();
    obstacle obstToPlot;
    int l=Environnement_tmp.size();
    for (int i=0;i<l;i++)
    {
        obstToPlot=Environnement_tmp.front();
        drawPolygon(obstToPlot);
        Environnement_tmp.pop_front();

        //qDebug()<<"Fin du "<<i+1<<"eme polynome.";
    }
}

void plotting::drawPolygon(obstacle obst)
{
    obstacle obstToPlot=obst;
    std::vector<sommet> sommets = obstToPlot.getSommet();
    dataarray data_obst;

    data_obst = setDatas(sommets);

    // qDebug()<<"L'obstacle est de taille"<<data_obst.second.size();
    QCPCurveDataMap plot_data;
    int l;
    for (unsigned int i=0;i<data_obst.second.size();i++)
    {
        QCPCurveData data(i,data_obst.first[i],data_obst.second[i]);
        plot_data.insert(i,data);
        l=i;
    }
    QCPCurveData data(l+1,data_obst.first[0],data_obst.second[0]);
    plot_data.insert(l+1,data);

    QCPCurve *plot = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

    plot->addData(plot_data);
    plot->setPen(QPen(Qt::blue));
    plot->setBrush(QBrush(QColor(0, 40, 255, 80)));

    customPlot->addPlottable(plot);
    customPlot->setVisible(true);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->rescaleAxes();
    customPlot->replot();
}

dataarray plotting::setDatas(std::vector<sommet> sommets)
{
    dataarray data;
    std::vector<double> X_points;
    std::vector<double> Y_points;
    unsigned int l=sommets.size();
    for (unsigned int i=0;i<l;i++)
    {
        sommet S=sommets.back();

        X_points.push_back(S.Xcoord());
        Y_points.push_back(S.Ycoord());
        //qDebug()<<"("<<S.Xcoord()<<","<<S.Ycoord()<<")";

        sommets.pop_back();
    }
    data = std::make_pair(X_points,Y_points);
    return data;
}

void plotting::setPlot(QCustomPlot* plot)
{
    customPlot=plot;
}

void plotting::initPlot()
{
    //qDebug()<<&customPlot;
    customPlot->xAxis->setRange(-5,5);
    customPlot->yAxis->setRange(-5,5);
}

environnement* plotting::getObstacles()
{
    return obstacles;
}

void plotting::resetEnvironment()
{
    obstacles->resetEnviron();
}

void plotting::createNewSegments(pairsom pair,int n)
{
    //réinitialisation du graphe
    graph->getGraph().clear();
    customPlot->clearPlottables();

    std::list<arc> tmp_graph;

    //récupération des points A et B
    sommet ptA=pair.first;
    sommet ptB=pair.second;
    //récupération des infos sur les obstacles
    std::list<obstacle> Envir_tmp=obstacles->getEnvir();


    int l=Envir_tmp.size();
    //Boucle de création des arcs à partir de A et B
    for(int i=0;i<l;i++)
    {
        obstacle obst_tmp=Envir_tmp.front();
        int m=obst_tmp.getSommet().size();
        for(int j=0;j<m;j++)
        {
            segment segA_tmp(ptA,obst_tmp.getSommet()[j]);
            segment segB_tmp(ptB,obst_tmp.getSommet()[j]);
            arc arcA_tmp(segA_tmp);
            arc arcB_tmp(segB_tmp);
            //Test de la validité des nouveaux arcs
            //TODO//
            bool addA=true;
            bool addB=true;
            std::list<obstacle> Envir_tmp_check=obstacles->getEnvir();
            for (int k=0;k<l;k++)
            {
                obstacle obst=Envir_tmp_check.front();
                bool testA=obst.Traverse(segA_tmp,n);

                if (testA==true)
                {
                    // qDebug()<<Envir_tmp_check.front().Traverse(segA_tmp);
                    addA=false;
                    break;
                }
                else
                {
                    //qDebug()<<Envir_tmp_check.front().Traverse(segA_tmp);
                }
                Envir_tmp_check.pop_front();
            }
            if (addA==true)
            {
                tmp_graph.push_back(arcA_tmp);
            }
            Envir_tmp_check=obstacles->getEnvir();
            for (int k=0;k<l;k++)
            {
                obstacle obst=Envir_tmp_check.front();
                bool testB=obst.Traverse(segB_tmp,n);
                if (testB==true)
                {
                    addB=false;
                    break;
                }
                else
                {}
                Envir_tmp_check.pop_front();
            }
            if (addB==true)
            {
                tmp_graph.push_back(arcB_tmp);
            }

            //Ajout des arcs correspondant aux cotés d'obstacles
            arc arcObst_tmp(obst_tmp.getSegment()[j]);
            tmp_graph.push_back(arcObst_tmp);
        }
        Envir_tmp.pop_front();
    }
    //Boucle de création d'arcs entre plusieurs obstacles
    Envir_tmp=obstacles->getEnvir();


    while(!Envir_tmp.empty())//Première boucle de choix d'obstacle
    {
        //qDebug()<<"Taille de Envir_tmp"<<Envir_tmp.size();
        std::list<obstacle> Envir_tmp_2=Envir_tmp;
        obstacle obst_tmp=Envir_tmp.front();
        while (!Envir_tmp_2.empty()) //Deuxième boucle de choix sur les obstacles
        {

            obstacle obst_tmp_2=Envir_tmp_2.front();
            int m=obst_tmp.getSommet().size();
            int m2=obst_tmp_2.getSommet().size();
            for(int j=0;j<m;j++)
            {
                for(int j2=0;j2<m2;j2++)
                {
                    segment seg_tmp(obst_tmp.getSommet()[j],obst_tmp_2.getSommet()[j2]); //création du segment
                    arc arc_tmp(seg_tmp);
                    bool add=true;
                    std::list<obstacle> Envir_tmp_check=obstacles->getEnvir();
                    for (int k=0;k<l;k++)//Boucle de vérification sur les obstacles (traverse)
                    {
                        obstacle obst=Envir_tmp_check.front();
                        bool test=obst.Traverse(seg_tmp,n); //Test de la validité des nouveaux arcs
                        if (test==true)
                        {
                            add=false;
                            break;
                        }
                        else
                        {}
                        Envir_tmp_check.pop_front();
                    }
                    if (add==true)
                    {
                        tmp_graph.push_back(arc_tmp);
                    }
                }
            }
            Envir_tmp_2.pop_front();
        }
        Envir_tmp.pop_front();
    }

    //Ne pas oublier le chemin direct
    segment seg_dir(ptA,ptB);
    arc arc_dir(seg_dir);
    bool adddir=true;
    std::list<obstacle> Envir_tmp_check=obstacles->getEnvir();
    for (int k=0;k<l;k++)
    {
        obstacle obst=Envir_tmp_check.front();
        bool testdir=obst.Traverse(seg_dir,n);
        if (testdir==true)
        {
            adddir=false;
            //qDebug()<<Envir_tmp_check.front().Traverse(seg_dir);
            break;
        }
        else
        {}
        Envir_tmp_check.pop_front();
    }
    if (adddir==true)
    {
        tmp_graph.push_back(arc_dir);
    }

    //Maj de graph
    graph->setGraph(tmp_graph);
}

void plotting::drawGraph()
{
    std::list<arc> tmp_grph=graph->getGraph();
    int l=tmp_grph.size();

    QCPCurveDataMap plot_data;
    std::list<QCPCurve*> plot_list;


    for (int i=0;i<l;i++)
    {
        QCPCurve* plot = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
        QCPCurveData data(0,tmp_grph.front().getSegment().getSommet().first.Xcoord(),tmp_grph.front().getSegment().getSommet().first.Ycoord());
        plot_data.insert(0,data);
        QCPCurveData data2(1,tmp_grph.front().getSegment().getSommet().second.Xcoord(),tmp_grph.front().getSegment().getSommet().second.Ycoord());
        plot_data.insert(1,data2);

        plot->addData(plot_data);
        plot->setPen(QPen(Qt::red));

        plot_list.push_back(plot);

        customPlot->addPlottable(plot_list.back());

        tmp_grph.pop_front();

    }
    customPlot->setVisible(true);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->rescaleAxes();
    customPlot->replot();

}
/*
bool plotting::QuiaLaPlusPetite (const std::pair<sommet,float>& michel,const std::pair<sommet,float>& micheline)
{
 std::pair<sommet,float> T;
    T=michel.front();
    std::vector<sommet> michelsort;
    for (int i=0; i=michel.size(); i++)
    {
        if (T.second<michel[i].second)
        {
            T=michel[i];
            Rank_T=i;
        }
    }

    return T;


    return(michel.second<micheline.second);
}
*/
void plotting::Dijkstra (pairsom pair)
{
    bool fini=false;
    qDebug()<<"On entre ds Dijik";
    sommet A=pair.first; //point de départ
    sommet B=pair.second; //point d'arrivée
    //std::vector< std::pair<sommet,float> > l; //longueur du plus court chemin entre sommet et A
    std::list<sommet>  p; //p(i)= sommet précédant i
    std::list<sommet> S;
    std::list<sommet> T;
    std::list<arc> arcs=graph->getGraph();
    std::list<obstacle> obstacles=getObstacles()->getEnvir();
    int Npts=2;
    std::vector<sommet> sommets;
    std::list<sommet> sommetlist;
    int n=obstacles.size();
    qDebug()<<"bite";
    sommets.push_back(A);
    for (int i=0; i<n; i++)
    {
        obstacle Obst=obstacles.front();
        for (unsigned int j=0; j<Obst.getSommet().size(); j++)
        {
            sommets.push_back(Obst.getSommet()[j]);
            Npts++;
        }
        obstacles.pop_front();
    }
    sommets.push_back(B);
    qDebug()<<"bite1";
    //Initialisations
    qDebug()<<"On entre ds l'init de dijik";
    qDebug()<<"On a"<< Npts<<"points, c'est cool !";
    std::vector<float> Boite(Npts,INFINITY);
    std::vector< std::vector<float> >  c(Npts,Boite); //cij=d(i,j)

    S.push_front(A);
    l=graph->Recherche(A);
    for(int j=0; j<Npts; j++)
    {
        sommetlist.push_front(sommets.back());

        std::vector< std::pair<sommet,float> >l_temp2=l;
        for(unsigned int j2=0;j2<l.size();j2++)
        {
            if(l_temp2.back().first==sommetlist.front())
            {
                c[0][j]=l_temp2.back().second;
            }
            l_temp2.pop_back();
        }
        sommets.pop_back();

    }
    T=sommetlist;
    T.pop_front();





    //Boucle ta race de mes deux
    qDebug()<<"On entre ds l'iteration de dijik";
    int Nit=0;
    while (!T.empty())
    {

        std::vector< std::pair<sommet,float> > ltemp=l;
        sommet michel;
        qDebug()<<"On detemine le poit à choisir à cette itération";
        for (unsigned int k=0;k<l.size();k++)
        {
            float curLeng=INFINITY;
            std::list<sommet> T_tmp=T;
            bool boul=false;
            //vérification que le point est toujours dans T
            for(int z=0;z<T.size();z++)
            {
                if (T_tmp.front()==ltemp.back().first)
                {
                    boul=true;
                    break;
                }
                else
                {
                    boul=false;
                }
                T_tmp.pop_front();
            }

            qDebug()<<boul;
            if(ltemp.back().second<curLeng&&boul==true)
            {
                michel=ltemp.back().first;
                curLeng=ltemp.back().second;
            }
            ltemp.pop_back();
        }
        p.push_front(michel);
        S.push_front(michel);
        qDebug()<<"On a deteminé le point à choisir à cette itération : ("<<michel.Xcoord()<<michel.Ycoord()<<")";

        if (michel==B)
        {
            qDebug()<<"C'est la fete du slip";
            break;
        }
        else
        {
            std::list<sommet> T_temp=T;
            unsigned int T_taill=T.size();
            qDebug()<<"Taille de T"<<T.size();
            T.clear();
            qDebug()<<"On supprime Michel de Tn";
            int N=0;
            for (unsigned int m=0;m<T_taill;m++)
            {

                if (T_temp.front().Xcoord()==michel.Xcoord()&&T_temp.front().Ycoord()==michel.Ycoord())
                {

                }

                else
                {
                    T.push_front(T_temp.front());
                    N++;

                }
                qDebug()<<N;
                if (N==T_taill)
                {

                    qDebug()<<"michel n'est pas dans le lot !Damned !";
                    fini=true;
                }
                T_temp.pop_front();
            }
            qDebug()<<"On a supprimé Michel de T";
            qDebug()<<"Taille de T"<<T.size();
            if (fini)
            {
                qDebug()<<"Finiii";
                break;
            }
            else{
                Nit++;
                qDebug()<<"On recherche le "<<Nit<<"ieme michel dans le graphe";
                l=graph->Recherche(michel);
                std::list<sommet> points=sommetlist;
                std::vector< std::pair<sommet,float> > l_temp3=l;
                qDebug()<<"On met a jouur les poids";
                for(int j2=0; j2<Npts; j2++)

                {
                    c[Nit][j2]=c[Nit-1][j2];
                    if(l_temp3.back().first==points.front())
                    {
                        if(c[Nit-1][j2]==INFINITY)
                        {
                            c[Nit][j2]=l_temp3.back().second;
                        }
                        else
                        {
                            c[Nit][j2]+=l_temp3.back().second;
                        }
                        l_temp3.pop_back();
                        qDebug()<<"Obitehel de T6";
                    }
                    if (!points.empty())
                    {points.pop_front();}
                }
                qDebug()<<"On a  mis les points à jour";
            }
        }
    }
    qDebug()<<"On a fini la";

    std::list<sommet> p_tmp=p;
    qDebug()<<p_tmp.size();
    std::list<arc> arks;
    for (unsigned int i3=0;i3<p.size();i3++)
    {
        qDebug()<<p_tmp.size();
        qDebug()<<"Coucou";
        sommet sommet1_tmp=p_tmp.front();
        p_tmp.pop_front();
        sommet sommet2_tmp=p_tmp.front();
        segment seg_tmp(sommet1_tmp,sommet2_tmp);
        arc arc_tmp(seg_tmp);
        arks.push_front(arc_tmp);
    }
        qDebug()<<"On y est presque ! !";
    grapheDijik->setGraph(arks);
    qDebug()<<"Balance la sauce !";
}

void plotting::drawGraphDijik ()
{
    std::list<arc> tmp_grph=grapheDijik->getGraph();
    int l=tmp_grph.size();

    QCPCurveDataMap plot_data;
    std::list<QCPCurve*> plot_list;


    for (int i=0;i<l;i++)
    {
        QCPCurve* plot = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
        QCPCurveData data(0,tmp_grph.front().getSegment().getSommet().first.Xcoord(),tmp_grph.front().getSegment().getSommet().first.Ycoord());
        plot_data.insert(0,data);
        QCPCurveData data2(1,tmp_grph.front().getSegment().getSommet().second.Xcoord(),tmp_grph.front().getSegment().getSommet().second.Ycoord());
        plot_data.insert(1,data2);

        plot->addData(plot_data);
        plot->setPen(QPen(Qt::black));

        plot_list.push_back(plot);

        customPlot->addPlottable(plot_list.back());

        tmp_grph.pop_front();

    }
    customPlot->setVisible(true);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->rescaleAxes();
    customPlot->replot();

}
