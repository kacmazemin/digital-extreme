#ifndef WEAPON_H
#define WEAPON_H

#include "PowerUp.h"

class Weapon : public PowerUp
{
public:
    Weapon(const char* name, const Vertex& position) :
        PowerUp(name, position)
    {
        mType = PowerUpType::WEAPON;
    }
};

#endif // WEAPON_H

