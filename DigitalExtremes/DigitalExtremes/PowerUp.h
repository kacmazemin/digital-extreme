#ifndef POWER_UP_H
#define POWER_UP_H

#include "Vertex.h"
#include <string.h>

enum class PowerUpType
{
    WEAPON,
    ARMOUR,
    HEALTH
};

class PowerUp
{
public:
    PowerUp(const char* name, const Vertex& position)
    {
        mPosition = position;

        mName = new char[strlen(name) + 1];
        strcpy_s(mName, strlen(name) + 1, name);
    }

    virtual ~PowerUp()
    {
        delete[] mName;
    }

    PowerUpType GetPowerUpType() const
    {
        return(mType);
    };

    const Vertex& GetPosition() const
    {
        return(mPosition);
    }

protected:
    Vertex mPosition;
    PowerUpType mType;

    char* mName = nullptr;
};

#endif // POWER_UP_H
