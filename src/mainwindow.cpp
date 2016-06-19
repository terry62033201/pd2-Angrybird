#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
    // Back button
    exi = new QPushButton(this);
    exi->setStyleSheet("border-image:url(:/img/backward_128px_28344_easyicon.net.png);}");
    exi -> setGeometry(QRect(QPoint(0, 100), QSize(50,50)));
    connect(exi, SIGNAL(released()), this, SLOT(END()));
    // Restart button
    res = new QPushButton(this);
    res->setStyleSheet("border-image:url(:/img/restart_72px_28438_easyicon.net.png);}");
    res -> setGeometry(QRect(QPoint(0, 50), QSize(50, 50)));
    connect(res, SIGNAL(released()), this, SLOT(RESTART()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{


    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));
    // Create background
    itemList.push_back(new Bkg(-0.5,18.5,QPixmap(":/img/harryPotter.jpg").scaled(width()/1.001,height()/1.2),world,scene));

    sc = new QLabel("Score :");
    sc->setFont(QFont("Courier",20,QFont::Bold));
    sc->setGeometry(50,465,100,50);
    scene->addWidget(sc);

    sc = new QLabel(QString::number(grade));
    sc->setFont(QFont("Courier",20,QFont::Bold));
    sc->setGeometry(180,465,150,50);
    scene->addWidget(sc);


    // Create building
    building = new Building(16.0f,6.0f, 0.75, 3, &timer,QPixmap(":/img/PNG/thinwood1.png").scaled(width()/32.0*0.75,height()/18.0*3),world,scene);
    building2 = new Building(16.0f,10.0f, 0.75,3,&timer,QPixmap(":/img/PNG/thinwood1.png").scaled(width()/32.0*0.75,height()/18.0*3),world,scene);
    building3 = new Building(22.0f,6.0f, 0.75,3, &timer,QPixmap(":/img/PNG/thinwood1.png").scaled(width()/32.0*0.75,height()/18.0*3),world,scene);
    building4 = new Building(22.0f,10.0f, 0.75,3,&timer,QPixmap(":/img/PNG/thinwood1.png").scaled(width()/32.0*0.75,height()/18.0*3),world,scene);
    // Create enemy (You can edit here)
    pig = new Pig(19.0f,4.0f,1.0f,&timer,QPixmap(":/img/PNG/pig2.png").scaled(width()/32.0*2.0,height()/18.0*2.0),world,scene);

    // Creat bird
    birdie = new Bird(5.0f,5.0f,1.0f,&timer,QPixmap(":/bird.png").scaled(width()/32.0*2.0,height()/18.0*2.0),world,scene);

    itemList.push_back(pig);
    itemList.push_back(building);
    itemList.push_back(birdie);
    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mo = static_cast<QMouseEvent *>(event);

        fx = mo->globalX();
        fy = mo->globalY();
    }
    if(event->type() == QEvent::MouseMove)
    {
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
          press++;
          std::cout << press << std::endl;
        if(press == 2)
        {
            QMouseEvent *mo = static_cast<QMouseEvent *>(event);
            ax = mo->globalX();
            ay = mo->globalY();
            std::cout << ax;
            std::cout << ay;
            birdie->setLinearVelocity(b2Vec2((fx - ax)/30,(ay - fy)/30));
            itemList.push_back(birdie);

        }
        if(press == 4)
        {
            delete birdie;
            //birdie = new Bird(5.0f,5.0f,1.0f,&timer,QPixmap(":/bird.png").scaled(width()/32.0*2.0,height()/18.0*2.0),world,scene);
            birdie_b = new Bird2(5.0f,6.0f,1.0f,&timer,QPixmap(":/img/PNG/blue.png").scaled(width()/32.0*2.0,height()/18.0*2.0),world,scene);
        }
        if(press == 6)
        {
            birdie_b->setLinearVelocity(b2Vec2((fx - ax)/30,(ay - fy)/30));
        }
        if(press == 8)
        {
            birdie_b->skill();

        }
        if(press == 10)
        {
            delete birdie_b;
            birdie_w = new Bird3(5.0f,6.0f,1.0f,&timer,QPixmap(":/img/PNG/white.png").scaled(width()/32.0*2.0,height()/18.0*2.0),world,scene);

        }
        if(press == 12)
        {
            birdie_w->setLinearVelocity(b2Vec2((fx - ax)/30,(ay - fy)/30));
        }
        if(press == 14)
        {
           birdie_w->skill();
        }
        if(press == 16)
        {
            delete birdie_w;
            birdie_g = new Bird4(5.0f,6.0f,1.0f,&timer,QPixmap(":/img/PNG/green.png").scaled(width()/32.0*2.0,height()/18.0*2.0),world,scene);
        }
        if(press == 18)
        {
            birdie_g->setLinearVelocity(b2Vec2((fx - ax)/30,(ay - fy)/30));
        }
        if(press == 20)
        {
            birdie_g->skill();
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    emit quitGame();
}

void MainWindow::tick()
{
    if(press == 2)
    {
        score = true;
    }
    if(pig->g_body->GetAngularVelocity() != 0 || pig->g_body->GetLinearVelocity().x != 0 || pig->g_body->GetLinearVelocity().y != 0 && score)
    {
        calculate_score();
    }
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::END()
{
    emit quitGame();
    exit(1);
}

void MainWindow::RESTART()
{
    std::cout << "Restart !" << std::endl;


    delete birdie_g;
    delete pig;
    delete building;
    delete building2;
    delete building3;
    delete building4;

    press = 1;
    grade = 0;
    sc->setText(QString::number(grade));
    birdie = new Bird(5.0f,5.0f,1.0f,&timer,QPixmap(":/bird.png").scaled(width()/32.0*2.0,height()/18.0*2.0),world,scene);
    building = new Building(16.0f,6.0f, 0.75,3, &timer,QPixmap(":/img/PNG/thinwood1.png").scaled(width()/32.0*0.75,height()/18.0*3),world,scene);
    building2 = new Building(16.0f,10.0f, 0.75,3, &timer,QPixmap(":/img/PNG/thinwood1.png").scaled(width()/32.0*0.75,height()/18.0*3),world,scene);
    building3 = new Building(22.0f,6.0f, 0.75,3,&timer,QPixmap(":/img/PNG/thinwood1.png").scaled(width()/32.0*0.75,height()/18.0*3),world,scene);
    building4 = new Building(22.0f,10.0f, 0.75,3,&timer,QPixmap(":/img/PNG/thinwood1.png").scaled(width()/32.0*0.75,height()/18.0*3),world,scene);
    pig = new Pig(19.0f,4.0f,1.0f,&timer,QPixmap(":/img/PNG/pig2.png").scaled(width()/32.0*2.0,height()/18.0*2.0),world,scene);
}

void MainWindow::calculate_score()
{

    grade += 1;
    if(grade > 600)
    {
        sc->setText("Victory!");
        sc->setFont(QFont("Courier", 18, QFont::Bold));
    }
    else
        sc->setText(QString::number(grade));

}
