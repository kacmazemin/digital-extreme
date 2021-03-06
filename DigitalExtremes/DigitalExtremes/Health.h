#ifndef HEALTH_H
#define HEALTH_H

#include "PowerUp.h"

class Health : public PowerUp
{
public:
    Health(const char* name, const Vertex& position) :
        PowerUp(name, position)
    {
        mType = PowerUpType::HEALTH;
    }

protected:
    float healing = 10.f;
};

#endif // HEALTH_H

