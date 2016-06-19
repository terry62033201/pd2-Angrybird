#ifndef BUILDING_H
#define BUILDING_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BUILDING_DENSITY 2.0f
#define BUILDING_FRICTION 0.3f
#define BUILDING_RESTITUTION 0.5f


class Building : public GameItem
{
public:
    Building(float x, float y,float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // BUILDING_H
