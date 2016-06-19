#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QPushButton>
#include <QApplication>
#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <bird2.h>
#include <bird3.h>
#include <bird4.h>
#include <building.h>
#include <bkg.h>
#include <pig.h>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void calculate_score();

    int press = 1;

    int fx;
    int fy;
    int ax;
    int ay;

    bool score;
    bool check = true;
    QLabel *sc;
    int grade = 0;


signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void END();
    void RESTART();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;

    QPushButton *exi;
    QPushButton *res;

    Bird *birdie;
    Bird2 *birdie_b;
    Bird3 *birdie_w;
    Bird4 *birdie_g;

    Pig *pig;

    Building *building;
    Building *building2;
    Building *building3;
    Building *building4;
};

#endif // MAINWINDOW_H
