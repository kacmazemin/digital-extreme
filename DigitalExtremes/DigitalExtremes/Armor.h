#ifndef ARMOUR_H
#define ARMOUR_H

#include "PowerUp.h"

#include <stddef.h>
#include <string.h>

class Armor : public PowerUp
{
public:
    Armor(const char* name, const Vertex& position) :
        PowerUp(name, position)
    {
        mType = PowerUpType::ARMOUR;
    }

    ~Armor()
    {
        delete[] mClanTag;
    }

    const char* GetClanTag() const
    {
        return(mClanTag);
    }

    void SetClanTag(char* n)
    {
        delete[] mClanTag;
        mClanTag = new char[strlen(n) + 1];
        strcpy_s(mClanTag, strlen(n) + 1, n);
    }

protected:
    char* mClanTag = nullptr;
};

#endif // ARMOUR_H

