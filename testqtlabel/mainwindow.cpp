#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spreadsheet.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  mousePressed = false;
  ui->setupUi(this);

  // on désactive ces boutons pour éviter que lorsqu'aucune trajectoire n'est crée, sinon si l'on ne crée pas de trajectoires, appuyer sur un de ces boutons

  ui->reset_joueur->setEnabled(false);
  ui->reset->setEnabled(false);
  ui->start->setEnabled(false);
  ui->stop->setEnabled(false);

}

MainWindow::~MainWindow()
{
  delete ui;
}

//on créer deux boutons rattachant le ballon aux joueurs

void MainWindow::on_joueur1_clicked()
{
    ui->reset_joueur->setEnabled(true);
    if(joueurballon == true or joueur2ballon == false or true)
    {
        joueurballon = true;
        joueur2ballon = false;
    QRect joueur1 =ui->joueur_1->geometry();
    int coordjoueur1[2] =  {joueur1.width(),joueur1.height()};

    QRect coord =ui->ballon->geometry();
    int coordballon[2] =  {coord.width(),coord.height()};

    ui->joueur_1->setGeometry(ui->joueur_1->x(),ui->joueur_1->y(),coordjoueur1[0],coordjoueur1[1]);
    ui->ballon->setGeometry(ui->joueur_1->x() + ui->joueur_1->width() -10,ui->joueur_1->y() -10 + ui->joueur_1->height(),coordballon[0],coordballon[1]);

    ui->joueur1->setEnabled(false);
    ui->joueur2->setEnabled(true);
}
    else{
        joueurballon = false;
        ui->joueur1->setEnabled(true);
        ui->joueur2->setEnabled(true);
    }


}

void MainWindow::on_joueur2_clicked()
{
    ui->reset_joueur->setEnabled(true);
    if(joueur2ballon == true or joueurballon == false or joueurballon == true)
    {
      joueur2ballon = true;
      joueurballon = false;
    QRect joueur2 =ui->joueur_2->geometry();
    int coordjoueur2[2] =  {joueur2.width(),joueur2.height()};

    QRect coord =ui->ballon->geometry();
    int coordballon[2] =  {coord.width(),coord.height()};

    ui->ballon->setGeometry(ui->joueur_2->x() + ui->joueur_2->width() -10 ,ui->joueur_2->y() + ui->joueur_2->height() -10,coordballon[0],coordballon[1]);
    ui->joueur_2->setGeometry(ui->joueur_2->x(), ui->joueur_2->y(),coordjoueur2[0],coordjoueur2[1]);

    ui->joueur1->setEnabled(true);
    ui->joueur2->setEnabled(false);
    }
    else{
    joueur2ballon = false;
    ui->joueur2->setEnabled(false);
    ui->joueur1->setEnabled(true);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::paintEvent(QPaintEvent *event) //Création de la trajectoire
   {

  //Tracer actuel
    //ligne du 1er joueur

    if(tempLigne->ptint.empty() != true && isDrawing)
    {
      QPoint *intl  = new QPoint[tempLigne->ptint.size()];  //création d'un nouveau point

      QPainter actualDraw(this);  //allocateur actualDraw appartient à mainwindow
      for(int i =0;i<tempLigne->ptint.size();i++)
      {
          intl[i] = tempLigne->ptint[i];
      }
      actualDraw.setPen(QPen(color,3));

      actualDraw.drawPolyline(intl,tempLigne->ptint.size());

    }



    if(mesLignes.empty() != true)
     {
    QPainter *oldDraw = new QPainter(this); //allocuteur oldDraw appartient à mainwindow
    for(int i =0;i<mesLignes.size();i++)
    {
    QPoint *oldDrawPoint  = new QPoint[mesLignes[i].ptint.size()];


      for(int j = 0;j<mesLignes[i].ptint.size();j++)
      {

        oldDrawPoint[j] = mesLignes[i].ptint[j];

      }

        oldDraw->drawPolyline(oldDrawPoint,mesLignes[i].ptint.size());
        oldDraw->setPen(QPen(Qt::red,15));
        oldDraw->drawPoint(mesLignes[i].pta);
        oldDraw->drawPoint(mesLignes[i].ptb);
        oldDraw->end();
        delete[] oldDrawPoint;

    }


    }



    //ligne du ballon

    if(ligne_ballon->ptint.empty() != true && isDrawing)
    {
      QPoint *intl  = new QPoint[ligne_ballon->ptint.size()];

      QPainter actualDraw(this);
      for(int i =0;i<ligne_ballon->ptint.size();i++)
      {

          intl[i] = ligne_ballon->ptint[i];
      }
      actualDraw.setPen(QPen(color,3));
      actualDraw.drawPolyline(intl,ligne_ballon->ptint.size());



    }



    if(LeBallon.empty() != true)
     {
    QPainter *oldDraw = new QPainter(this);
    for(int i =0;i<LeBallon.size();i++)
    {
    QPoint *oldDrawPoint  = new QPoint[LeBallon[i].ptint.size()];


      for(int j = 0;j<LeBallon[i].ptint.size();j++)
      {

        oldDrawPoint[j] = LeBallon[i].ptint[j];

      }

        oldDraw->drawPolyline(oldDrawPoint,LeBallon[i].ptint.size());
        oldDraw->setPen(QPen(Qt::red,15));
        oldDraw->drawPoint(LeBallon[i].pta);
        oldDraw->drawPoint(LeBallon[i].ptb);
        oldDraw->end();
         delete[] oldDrawPoint;

    }



    }




    //ligne joueur 2

    if(ligne_joueur_2->ptint.empty() != true && isDrawing)
    {
      QPoint *intl  = new QPoint[ligne_joueur_2->ptint.size()];

      QPainter actualDraw(this);
      for(int i =0;i<ligne_joueur_2->ptint.size();i++)
      {

          intl[i] = ligne_joueur_2->ptint[i];
      }
      actualDraw.setPen(QPen(color,3));
      actualDraw.drawPolyline(intl,ligne_joueur_2->ptint.size());



    }



    if(AutreJoueur.empty() != true)
     {
    QPainter *oldDraw = new QPainter(this);
    for(int i =0;i<AutreJoueur.size();i++)
    {
    QPoint *oldDrawPoint  = new QPoint[AutreJoueur[i].ptint.size()];


      for(int j = 0;j<AutreJoueur[i].ptint.size();j++)
      {

        oldDrawPoint[j] = AutreJoueur[i].ptint[j];

      }

        oldDraw->drawPolyline(oldDrawPoint,AutreJoueur[i].ptint.size());
        oldDraw->setPen(QPen(Qt::red,15));
        oldDraw->drawPoint(AutreJoueur[i].pta);
        oldDraw->drawPoint(AutreJoueur[i].ptb);
        oldDraw->end();
      delete[] oldDrawPoint;

    }


    }



}


void  MainWindow::mousePressEvent( QMouseEvent * event ){//animation lors d'utilisations des clics de souris
    //utilisation du 1er joueur

    if(event->button() == Qt::LeftButton)
    {
    QRect joueur1 =ui->joueur_1->geometry();
    ui->y->setText(QString("X="+QString::number(event->x())+"\nY="+QString::number(event->y())));
    int coordjoueur1[2] =  {joueur1.width(),joueur1.height()};
    xNew = 0+71/2;
    yNew = 0-71/2;
    newX = event->x() -xNew;
    newY = event->y() +yNew;


    QRect coord =ui->ballon->geometry();
    ui->y->setText(QString("X="+QString::number(event->x())+"\nY="+QString::number(event->y())));
    int coordballon[2] =  {coord.width(),coord.height()};
    xLabNew = 0+71/2;
    yLabNew = 0-71/2;
    newLabelX = event->x() -xLabNew;
    newLabelY = event->y() +yLabNew;


    if(joueurballon == true)
    {
        ui->joueur_1->setGeometry(newX,newY,coordjoueur1[0],coordjoueur1[1]);
        ui->ballon->setGeometry(ui->joueur_1->x() + ui->joueur_1->width() -10,ui->joueur_1->y() -10 + ui->joueur_1->height(),coordballon[0],coordballon[1]);
    }
    else
    {
        ui->joueur_1->setGeometry(newX,newY,coordjoueur1[0],coordjoueur1[1]);
    }


    ui->joueur_1->setGeometry(newX,newY,coordjoueur1[0],coordjoueur1[1]);
    if(firstPoint.isNull() )
    {
      firstPoint.setX(newX);
      firstPoint.setY(newY);
    }
    else if(lastPoint.isNull())
    {
     lastPoint.setX(newX);
      lastPoint.setY(newY);
    }
    if(!firstPoint.isNull() && !lastPoint.isNull())
    {
      this->update();
    }


    if(ui->joueur_1->x() == ui->ballon->x() and ui->joueur_1->y() == ui->ballon->y())
    {
        ui->ballon->setGeometry(newLabelX,newLabelY,coordballon[0],coordballon[1]);
        ui->joueur_1->setGeometry(newX,newY,coordjoueur1[0],coordjoueur1[1]);
    }

    }



    //utilisation du ballon

    else if(event->button() == Qt::RightButton)
    {
    /*if (event->x() > ui->joueur_2->x() && event->y() > ui->joueur_2->y() && event->x() < ui->joueur_2->x()+ui->joueur_2->width() && event->y() < ui->joueur_2->y()+ui->joueur_2->height())
    {*/
    QRect coord =ui->ballon->geometry();
    ui->y->setText(QString("X="+QString::number(event->x())+"\nY="+QString::number(event->y())));
    int coordballon[2] =  {coord.width(),coord.height()};
    xLabNew = 0+71/2;
    yLabNew = 0-71/2;
    newLabelX = event->x() -xLabNew;
    newLabelY = event->y() +yLabNew;


    QRect joueur1 =ui->joueur_1->geometry();
    ui->x->setText(QString("X="+QString::number(event->x())+"\nY="+QString::number(event->y())));
    int coordjoueur1[2] =  {joueur1.width(),joueur1.height()};
    xNew = 0+71/2;
    yNew = 0-71/2;
    newX = event->x() -xNew;
    newY = event->y() +yNew;


    QRect joueur2 =ui->joueur_2->geometry();
    ui->x->setText(QString("X="+QString::number(event->x())+"\nY="+QString::number(event->y())));
    int coordjoueur2[2] =  {joueur2.width(),joueur2.height()};
    xLab = 0+71/2;
    yLab = 0-71/2;
    LabelX = event->x() -xLab;
    LabelY = event->y() +yLab;


    if(joueur2ballon == true and joueurballon == false)
    {
        ui->joueur_2->setGeometry(LabelX,LabelY,coordjoueur2[0],coordjoueur2[1]);
        ui->ballon->setGeometry(ui->joueur_2->x() + ui->joueur_2->width(),ui->joueur_2->y() + ui->joueur_2->height(),coordballon[0],coordballon[1]);
    }
    else if(joueurballon == true and joueur2ballon == false)
    {
        ui->joueur_1->setGeometry(newX,newY,coordjoueur1[0],coordjoueur1[1]);
        ui->ballon->setGeometry(ui->joueur_1->x() + ui->joueur_1->width() -10,ui->joueur_1->y() -10 + ui->joueur_1->height(),coordballon[0],coordballon[1]);
    }
    else
    {
        ui->ballon->setGeometry(newX,newY,coordjoueur1[0],coordjoueur1[1]);
    }



    if(firstPoint.isNull() )
    {
      firstPoint.setX(newLabelX);
      firstPoint.setY(newLabelY);
    }
    else if(lastPoint.isNull())
    {
     lastPoint.setX(newLabelX);
      lastPoint.setY(newLabelY);
    }
    if(!firstPoint.isNull() && !lastPoint.isNull())
    {
      this->update();
    }


    if (ui->joueur_2->x() == ui->ballon->x() and ui->joueur_2->y() == ui->ballon->y()){
         ui->ballon->setGeometry(newLabelX,newLabelY,coordballon[0],coordballon[1]);
         ui->joueur_2->setGeometry(LabelX,LabelY,coordjoueur2[0],coordjoueur2[1]);

    }
    else if(ui->joueur_1->x() == ui->ballon->x() and ui->joueur_1->y() == ui->ballon->y())
    {
        ui->ballon->setGeometry(newLabelX,newLabelY,coordballon[0],coordballon[1]);
        ui->joueur_1->setGeometry(newX,newY,coordjoueur1[0],coordjoueur1[1]);
    }




    }



    //utilisation du 2e joueur

    else if(event->button() == Qt::MiddleButton)
    {
        QRect joueur2 =ui->joueur_2->geometry();
        ui->y->setText(QString("X="+QString::number(event->x())+"\nY="+QString::number(event->y())));
        int coordjoueur2[2] =  {joueur2.width(),joueur2.height()};
        xLab = 0+71/2;
        yLab = 0-71/2;
        LabelX = event->x() -xLab;
        LabelY = event->y() +yLab;


        QRect coord =ui->ballon->geometry();
        ui->y->setText(QString("X="+QString::number(event->x())+"\nY="+QString::number(event->y())));
        int coordballon[2] =  {coord.width(),coord.height()};
        xLabNew = 0+71/2;
        yLabNew = 0-71/2;
        newLabelX = event->x() -xLabNew;
        newLabelY = event->y() +yLabNew;


        if(joueur2ballon == true)
        {
            ui->joueur_2->setGeometry(LabelX,LabelY,coordjoueur2[0],coordjoueur2[1]);
            ui->ballon->setGeometry(ui->joueur_2->x() + ui->joueur_2->width(),ui->joueur_2->y() + ui->joueur_2->height(),coordballon[0],coordballon[1]);
        }
        else
        {
           ui->joueur_2->setGeometry(LabelX,LabelY,coordjoueur2[0],coordjoueur2[1]);
        }


        ui->joueur_2->setGeometry(LabelX,LabelY,coordjoueur2[0],coordjoueur2[1]);


        if(firstPoint.isNull() )
        {
          firstPoint.setX(LabelX);
          firstPoint.setY(LabelY);
        }
        else if(lastPoint.isNull())
        {
         lastPoint.setX(LabelX);
          lastPoint.setY(LabelY);
        }
        if(!firstPoint.isNull() && !lastPoint.isNull())
        {
          this->update();
        }

        if (ui->joueur_2->x() == ui->ballon->x() and ui->joueur_2->y() == ui->ballon->y()){
             ui->ballon->setGeometry(newLabelX,newLabelY,coordballon[0],coordballon[1]);
             ui->joueur_2->setGeometry(LabelX,LabelY,coordjoueur2[0],coordjoueur2[1]);

        }
        }



  qDebug() << "Nombre de figure : "<< mesLignes.size();


  if (event->button() == Qt::LeftButton)
  {
    if(!tempLigne->ptint.empty())
    {
    tempLigne->ptint.clear();
    qDebug() << "Taille : "<< tempLigne->ptint.size();
     }
    tempLigne->ptint.append(event->pos());
      tempLigne->pta = event->pos();
      qDebug() << "Ajout point de départ : " << event->pos();
      isDrawing = true;
      mousePressed = true;
      update();

  }
  else if (event->button() == Qt::RightButton)
  {
      if(!ligne_ballon->ptint.empty())
      {
      ligne_ballon->ptint.clear();
      qDebug() << "Taille : "<< ligne_ballon->ptint.size();
       }
      ligne_ballon->ptint.append(event->pos());
        ligne_ballon->pta = event->pos();
        qDebug() << "Ajout point de départ : " << event->pos();
        isDrawing = true;
        mousePressed = true;
        update();
  }
  else if (event->button() == Qt::MiddleButton)
  {
      if(!ligne_joueur_2->ptint.empty())
      {
      ligne_joueur_2->ptint.clear();
      qDebug() << "Taille : "<< ligne_joueur_2->ptint.size();
       }
      ligne_joueur_2->ptint.append(event->pos());
        ligne_joueur_2->pta = event->pos();
        qDebug() << "Ajout point de départ : " << event->pos();
        isDrawing = true;
        mousePressed = true;
        update();
  }







}






void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

      if(!isMoving)
      {
        ui->pos_souris->setText(QString("Position souris X:"+QString::number(event->pos().rx())+"\nPosition souris Y:"+QString::number(event->pos().ry())));
        ui->x->setText(QString("Pos X:"+QString::number(event->pos().rx())+"\nPosY:"+QString::number(event->pos().ry())));
        ui->y->setText(QString("X="+QString::number(event->x())+"\nY="+QString::number(event->y())));

        // calcul de la distance entre le point de départ et d'arrêt

        distance_ballon.setNum((ligne_ballon->ptint.length()/5.9)*2);
        ui->distance_ballon->setText("Distance entre le point de départ et d'arrêt (ballon) : " + distance_ballon + " m");

        distance_joueur_1.setNum((tempLigne->ptint.length()/5.9)*2);
        ui->distance->setText("Distance entre le point de départ et d'arrêt (joueur 1) : " + distance_joueur_1 + " m");

        distance_joueur_2.setNum((ligne_joueur_2->ptint.length()/5.9)*2);
        ui->label_2->setText("Distance entre le point de départ et d'arrêt (joueur 2) :" + distance_joueur_2 + " m");



        if ((event->buttons() & Qt::LeftButton) && isDrawing)
        {
          qDebug() << "Detect joueur 1:" << tempLigne->ptint.size();
         tempLigne->ptint.append(event->pos());
          qDebug() << "Ajout point intermediaire : "<< event->pos();
        }
        else if ((event->buttons() & Qt::RightButton) && isDrawing)
        {
          qDebug() << "Detect ballon:" << ligne_ballon->ptint.size();
         ligne_ballon->ptint.append(event->pos());
          qDebug() << "Ajout point intermediaire : "<< event->pos();
        }
        else if ((event->buttons() & Qt::MiddleButton) && isDrawing)
        {
          qDebug() << "Detect joueur 2:" << ligne_joueur_2->ptint.size();
         ligne_joueur_2->ptint.append(event->pos());
          qDebug() << "Ajout point intermediaire : "<< event->pos();
        }
      }
      else
      {
        switch (pt)
        {
          case 0 : mesLignes[index].pta = event->pos();
            LeBallon[index].pta = event->pos();
            AutreJoueur[index].pta = event->pos();
          break;
          case 1 : mesLignes[index].ptint.append(event->pos());
            LeBallon[index].ptint.append(event->pos());
            AutreJoueur[index].ptint.append(event->pos());
          break;
        //  case 2 : mesLignes[index].ptint = event->pos();
          break;

        }
      }

      update();

}



void MainWindow::animationStart() //début de l'animation
{
    ui->stop->setEnabled(true);
    if(index == 0)
    {
      qDebug() << "Lancement de l'animation";
      ui->joueur_1->move(mesLignes.last().pta);

      ui->ballon->move(LeBallon.last().pta);

      ui->joueur_2->move(AutreJoueur.last().pta);
    /*//calcul de la distance entre deux labels
    QString distance;
    distance.setNum(sqrt((ui->joueur_2->x() - ui->joueur_1->x()) + (ui->joueur_2->y()-ui->joueur_1->y())) / 13);
    ui->label->setText("Distance entre les deux joueurs : " + distance + " m");

    QString distance_joueur1;
    distance_joueur1.setNum(sqrt((ui->ballon->x() - ui->joueur_1->x()) + (ui->ballon->y()-ui->joueur_1->y())) / 13);
    ui->label_3->setText("Distance entre le joueur 1 et le ballon : " + distance_joueur1 + " m");

    QString distance_joueur2;
    distance_joueur2.setNum(sqrt((ui->ballon->x() - ui->joueur_2->x()) + (ui->ballon->y()-ui->joueur_2->y())) / 13);
    ui->label_4->setText("Distance entre le joueur 5 et le ballon : " + distance_joueur2 + " m");*/




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    //calcul de la vitesse d'un joueur ou du ballon en trottinant
    if (trottiner == true)
    {
        vitesse_du_ballon.setNum(((ligne_ballon->ptint.length()/5.9)*2) / ((((ligne_ballon->ptint.length()/5.9)*2) / vitesse_trottiner)));
        ui->vitesse_ballon->setText("Vitesse du ballon : " + vitesse_du_ballon + "km/s");

        vitesse_du_joueur_1.setNum(((tempLigne->ptint.length()/5.9)*2) / ((((tempLigne->ptint.length()/5.9)*2) / vitesse_trottiner)));
        ui->vitesse_joueur1->setText("Vitesse du joueur 1 : " + vitesse_du_joueur_1 + "km/s");

        vitesse_du_joueur_2.setNum(((ligne_joueur_2->ptint.length()/5.9)*2) / ((((ligne_joueur_2->ptint.length()/5.9)*2) / vitesse_trottiner)));
        ui->vitesse_joueur2->setText("Vitesse du joueur 2 : " + vitesse_du_joueur_2 + "km/s");
    }
    //calcul de la vitesse d'un joueur ou du ballon en marchant
    else if (marcher == true)
    {
        vitesse_du_ballon.setNum(((ligne_ballon->ptint.length()/5.9)*2) / ((((ligne_ballon->ptint.length()/5.9)*2) / vitesse_marche)));
        ui->vitesse_ballon->setText("Vitesse du ballon : " + vitesse_du_ballon + "m/s");

        vitesse_du_joueur_1.setNum(((tempLigne->ptint.length()/5.9)*2) / ((((tempLigne->ptint.length()/5.9)*2) / vitesse_marche)));
        ui->vitesse_joueur1->setText("Vitesse du joueur 1 : " + vitesse_du_joueur_1 + "m/s");

        vitesse_du_joueur_2.setNum(((ligne_joueur_2->ptint.length()/5.9)*2) / ((((ligne_joueur_2->ptint.length()/5.9)*2) / vitesse_marche)));
        ui->vitesse_joueur2->setText("Vitesse du joueur 2 : " + vitesse_du_joueur_2 + "m/s");
    }
    //calcul de la vitesse d'un joueur ou du ballon en courant
    else if (courir == true)
    {
        vitesse_du_ballon.setNum(((ligne_ballon->ptint.length()/5.9)*2) / ((((ligne_ballon->ptint.length()/5.9)*2) / vitesse_course)));
        ui->vitesse_ballon->setText("Vitesse du ballon : " + vitesse_du_ballon + "km/s");

        vitesse_du_joueur_1.setNum(((tempLigne->ptint.length()/5.9)*2) / ((((tempLigne->ptint.length()/5.9)*2) / vitesse_course)));
        ui->vitesse_joueur1->setText("Vitesse du joueur 1 : " + vitesse_du_joueur_1 + "km/s");

        vitesse_du_joueur_2.setNum(((ligne_joueur_2->ptint.length()/5.9)*2) / ((((ligne_joueur_2->ptint.length()/5.9)*2) / vitesse_course)));
        ui->vitesse_joueur2->setText("Vitesse du joueur 2 : " + vitesse_du_joueur_2 + "km/s");
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //active l'alerte si le ballon se trouve au-dessus des joueurs

    if (ui->ballon->x() and ui->ballon->y() > ui->joueur_1->x() and ui->joueur_1->y())
    {
        ui->alerte->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(0,0,0);");

        ui->joueur_1->setGeometry(10,10,71,71);
        ui->joueur_2->setGeometry(230,10,71,71);
        ui->ballon->setGeometry(430,10,71,71);
        qDebug() << "Arrêt";
        index = 0;
        timer->stop();

    }


    else if (ui->ballon->x() and ui->ballon->y() > ui->joueur_2->x() and ui->joueur_2->y())
    {
        ui->alerte->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(0,0,0);");

        ui->joueur_1->setGeometry(10,10,71,71);
        ui->joueur_2->setGeometry(230,10,71,71);
        ui->ballon->setGeometry(430,10,71,71);
        qDebug() << "Arrêt";
        index = 0;
        timer->stop();

    }


    if(ui->joueur_1->x() and ui->joueur_1->y() == ui->ballon->x() and ui->ballon->y())
    {
        ui->joueur_1->setGeometry(ui->joueur_1->x(),ui->joueur_1->y(),71,71);
        ui->ballon->setGeometry(ui->joueur_1->x() + ui->joueur_1->width() -10,ui->joueur_1->y() -10 + ui->joueur_1->height(),71,71);
    if(firstPoint.isNull() )
    {
      firstPoint.setX(newX);
      firstPoint.setY(newY);
      firstPoint.setX(newLabelX);
      firstPoint.setY(newLabelY);

    }
    else if(lastPoint.isNull())
    {
      lastPoint.setX(newX);
      lastPoint.setY(newY);
      lastPoint.setX(newLabelX);
      lastPoint.setY(newLabelY);
    }
    if(!firstPoint.isNull() && !lastPoint.isNull())
    {
      this->update();
    }

    }


    else if(ui->joueur_2->x() and ui->joueur_2->y() == ui->ballon->x() and ui->ballon->y())
    {
        ui->ballon->setGeometry(ui->joueur_2->x() + ui->joueur_2->width() -10 ,ui->joueur_2->y() + ui->joueur_2->height() -10,71,71);
        ui->joueur_2->setGeometry(ui->joueur_2->x(), ui->joueur_2->y(),71,71);
    if(firstPoint.isNull() )
    {
      firstPoint.setX(LabelX);
      firstPoint.setY(LabelY);
      firstPoint.setX(newLabelX);
      firstPoint.setY(newLabelY);
    }
    else if(lastPoint.isNull())
    {
      lastPoint.setX(LabelX);
      lastPoint.setY(LabelY);
      lastPoint.setX(newLabelX);
      lastPoint.setY(newLabelY);
    }
    if(!firstPoint.isNull() && !lastPoint.isNull())
    {
      this->update();
    }

    }


  }
  else
   {
    if(index == mesLignes.last().ptint.size() or index == LeBallon.last().ptint.size() or index == AutreJoueur.last().ptint.size())
    {
      ui->joueur_1->setGeometry(10,10,71,71);
      ui->joueur_2->setGeometry(230,10,71,71);
      ui->ballon->setGeometry(430,10,71,71);
      qDebug() << "Arrêt";
      index = 0;
      timer->stop();

      return;
    }
    else
    {
      qDebug() << "Animation au point :" <<index;
      ui->joueur_1->move(mesLignes.last().ptint[index]);

      ui->ballon->move(LeBallon.last().ptint[index]);

      ui->joueur_2->move(AutreJoueur.last().ptint[index]);


    }


  }
  index++;

}

////////////////////////////////////////////////////////////////////////

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

  isMoving = false;
  if (event->button() == Qt::LeftButton && isDrawing)
    {
      ligne *nouvelleligne = new ligne;
      nouvelleligne->pta = tempLigne->pta;
      nouvelleligne->ptb = event->pos();
      nouvelleligne->ptint = tempLigne->ptint;
      mesLignes.append(*nouvelleligne);

      index_2 =0;
      delete nouvelleligne;
      isDrawing = false;
      mousePressed = false;
      update();

  }

  if (event->button() == Qt::RightButton && isDrawing)
  {
      ballon *nouvelleligne = new ballon;
      nouvelleligne->pta = ligne_ballon->pta;
      nouvelleligne->ptb = event->pos();
      nouvelleligne->ptint = ligne_ballon->ptint;
      LeBallon.append(*nouvelleligne);

      index_2 =0;
      delete nouvelleligne;
      isDrawing = false;
      mousePressed = false;
      update();
  }

  if (event->button() == Qt::MiddleButton && isDrawing)
  {
      joueur_2 *nouvelleligne = new joueur_2;
      nouvelleligne->pta = ligne_joueur_2->pta;
      nouvelleligne->ptb = event->pos();
      nouvelleligne->ptint = ligne_joueur_2->ptint;
      AutreJoueur.append(*nouvelleligne);

      index_2 =0;
      delete nouvelleligne;
      isDrawing = false;
      mousePressed = false;
      update();
  }
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
  qDebug() << event->key() ;
  if(event->key()==Qt::Key::Key_R) color = Qt::red;
  if(event->key()==Qt::Key::Key_Y) color = Qt::yellow;
  else if(event->key()==Qt::Key::Key_G) color = Qt::green;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void MainWindow::on_Courir_clicked()
{
    ui->start->setEnabled(true);
    ui->reset->setEnabled(true);

    ui->Courir->setEnabled(false);
    if (courir == false or marcher == true or trottiner == true){
        courir = true;
        marcher = false;
        trottiner = false;

    color = Qt::red;
    ui->Marcher->setEnabled(true);
    ui->Trottiner->setEnabled(true);

    /*timer = new QTimer(this);
    timer->setInterval(tempLigne->ptint.length() / vitesse_course);
    connect(timer, SIGNAL(timeout()),this, SLOT(animationStart()));
    timer->start();*/
}

}


void MainWindow::on_Marcher_clicked()
{
    ui->start->setEnabled(true);
    ui->reset->setEnabled(true);

    ui->Marcher->setEnabled(false);
    if(marcher == false or courir == true or trottiner == true)
    {
        marcher = true;
        courir = false;
        trottiner = false;


    color = Qt::green;
    ui->Courir->setEnabled(true);
    ui->Trottiner->setEnabled(true);
}

}

void MainWindow::on_Trottiner_clicked()
{
    ui->start->setEnabled(true);
    ui->reset->setEnabled(true);

    ui->Trottiner->setEnabled(false);
    if(trottiner == false or marcher == true or courir == true)
    {
        trottiner = true;
        courir = false;
        marcher = false;
    ui->Courir->setEnabled(true);
    ui->Marcher->setEnabled(true);
    color = QColor(255,171,0);

}

}



/////////////////////////////////////////////////////////////////////////////

void MainWindow::on_start_clicked()
{
      timer = new QTimer(this);

         if (trottiner == true) {
             color = QColor(255,171,0);
             //trottiner = true;
             timer->setInterval(((tempLigne->ptint.length()/5.9)*2) / vitesse_trottiner);
            }

         else if (marcher == true)
         {
             color = Qt::green;
             //marcher = true;
             timer->setInterval(((tempLigne->ptint.length()/5.9)*2) / vitesse_marche);
         }

         else if (courir == true)
         {
             color = Qt::red;
             //courir = true;
             timer->setInterval(((tempLigne->ptint.length()/5.9)*2) / vitesse_course);
         }


          connect(timer, SIGNAL(timeout()),this, SLOT(animationStart()));
          timer->start();



  ui->stop->setEnabled(true);
  ui->start->setEnabled(false);
}


void MainWindow::on_stop_clicked()
{
    timer->stop();
    ui->stop->setEnabled(false);
    ui->Courir->setEnabled(true);
    ui->Marcher->setEnabled(true);
    ui->Trottiner->setEnabled(true);

}

void MainWindow::on_reset_clicked()
{

    ui->joueur_1->setGeometry(10,10,71,71);
    ui->joueur_2->setGeometry(230,10,71,71);
    ui->ballon->setGeometry(430,10,71,71);



    ui->start->setEnabled(false);
    ui->stop->setEnabled(false);
    ui->Marcher->setEnabled(true);
    ui->Courir->setEnabled(true);
    ui->Trottiner->setEnabled(true);
    ui->reset->setEnabled(false);

}



void MainWindow::on_reset_joueur_clicked()
{
    joueurballon = false;
    joueur2ballon = false;

    ui->joueur1->setEnabled(true);
    ui->joueur2->setEnabled(true);

    ui->ballon->setGeometry(430,10,71,71);

    ui->reset_joueur->setEnabled(false);

}

void MainWindow::on_bouton_tableur_clicked()
{
    tableau_retard = new SpreadSheet(10,10);
    tableau_retard->show();
}


ligne MainWindow::getTempLigne(ligne *tempLigne)
{
    emit sendTempLigne(tempLigne);
}

