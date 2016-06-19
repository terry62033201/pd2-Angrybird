#ifndef BKG_H
#define BKG_H

#include <gameitem.h>
#include <QGraphicsScene>

class Bkg : public GameItem
{
public:
    Bkg(float x, float y, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // BKG_H
