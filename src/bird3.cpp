#include "bird3.h"

Bird3::Bird3(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x, y, radius, timer, pixmap, world, scene)
{

}

void Bird3::skill()
{
    g_body->SetLinearVelocity(b2Vec2 ((float(g_body->GetLinearVelocity().x)*0),float(-abs(g_body->GetLinearVelocity().y*100))));
}
