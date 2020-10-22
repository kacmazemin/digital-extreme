#ifndef ARMOUR_H
#define ARMOUR_H

#include "PowerUp.h"

#include <string.h>

enum class ArmorEffectType
{
    MAGICAL_DEFENCE,
    PHYSICAL_DEFENCE
};

struct ArmorStruct
{
    bool isCanBeStackable;
    bool isLootable;
    std::string description;
    std::string iconPath;
    PowerUpTimeType timeType;
    PowerUpUsageType usageType;
    ArmorEffectType weaponEffectType;
    float effectValue;
    float duration;
    float usageTypeValue;
};

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
        delete icon;
        delete particle;
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

    inline ArmorStruct getArmorStruct() const
    {
        return armorStruct;
    }

    void usePowerUp() override
    {

    }
    
    void destroyByManual() override
    {

    }

    inline float getTotalArmorAfterUsage(const float baseArmor ) const
    {
        return baseArmor + getArmorStruct().effectValue;
    }

protected:
    char* mClanTag = nullptr;

private:
    ArmorStruct armorStruct;

    class Sprite* icon = nullptr;
    class Particle* particle = nullptr;
};

#endif // ARMOUR_H

