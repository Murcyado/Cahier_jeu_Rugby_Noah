#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QWidget>
#include <QMouseEvent>
#include <QCursor>
#include <QPainter>
#include <QtMath>
#include <QPainterPath>
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QSettings>
#include <QObject>
#include <QColor>
#include <QPushButton>

struct ligne  //joueur 1
{
  QPoint  pta;
  QPoint ptb;
  QList<QPoint> ptint;

};

struct ballon   //ballon
{
  QPoint  pta;
  QPoint ptb;
  QList<QPoint> ptint;

};

struct joueur_2  //joueur 2
{
  QPoint  pta;
  QPoint ptb;
  QList<QPoint> ptint;

};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void mousePressEvent ( QMouseEvent * event )  override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

protected:
    void keyPressEvent(QKeyEvent *event) override; // test de modifications des couleurs

private slots:
  void paintEvent(QPaintEvent* )  override;
  void animationStart();
 // void paint(QPainter *painter);

//mettre en marche le programme

  void on_start_clicked();

  void on_stop_clicked();


//donner le ballon à un joueur

  void on_joueur1_clicked();

  void on_joueur2_clicked();


//reset les positions des joueurs et du ballon

  void on_reset_clicked();

  void on_reset_joueur_clicked();


// définir la vitesse du ballon et des joueurs

  void on_Courir_clicked();

  void on_Marcher_clicked();

  void on_Trottiner_clicked();

private:
  Ui::MainWindow *ui;
  QTimer *timer;
  /*QTimer *timer_course;
  QTimer *timer_marche;*/
  int mouvement = 0;
  bool switchPoint=1;


  int xNew = 0+71/2; // joueur 1
  int yNew = 0-71/2;
  int newX;
  int newY;

  int xLab = 0+71/2; // joueur 2
  int yLab = 0-71/2;
  int LabelX;
  int LabelY;

  int xLabNew = 0+71/2; // ballon
  int yLabNew = 0-71/2;
  int newLabelX;
  int newLabelY;


  QPen pen;

  //point de départ et d'arrivée
  QPoint lastPoint;
  QPoint firstPoint;

  //distance entre 1 joueur et le ballon
  QString distance_joueur2;
  QString distance_joueur1;
  QString distance;

  //distance entre deux points
  QString distance_ballon;
  QString distance_joueur_1;
  QString distance_joueur_2;

  //vitesse d'un joueur ou du ballon
  QString vitesse_du_ballon;
  QString vitesse_du_joueur_1;
  QString vitesse_du_joueur_2;



  QList<QPoint> interPoint;
  QRect rec1;
  QPainter *pencilPainter = new QPainter(this);


  int vitesse_trottiner = 8;
  int vitesse_marche = 5;
  int vitesse_course = 15;


  ligne *tempLigne = new ligne();   //ligne du joueur 1
  ballon *ligne_ballon = new ballon();
  joueur_2 *ligne_joueur_2 = new joueur_2();

  bool mousePressed;
  bool isDrawing , isMoving = false ;

  //variable donnant le ballon à un joueur
  bool joueurballon = false;
  bool joueur2ballon = false;

  //variable définissant la vitesse du ballon et des joueurs
  bool courir = false;
  bool marcher = false;
  bool trottiner = false;

  /*bool course_color = false;
  bool marche_color = false;
  bool trottiner_color = false;*/

  unsigned index = 0 ;
  unsigned pt = 0;
  QPoint coord;
  float x = 0;
  unsigned index_2=0;
  int selecteur = 0;
  QList<ligne> mesLignes;
  QList<ballon> LeBallon;
  QList<joueur_2> AutreJoueur;
  QColor color;

};
#endif // MAINWINDOW_H
