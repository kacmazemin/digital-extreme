#ifndef WEAPON_H
#define WEAPON_H

#include "PowerUp.h"

enum class WeaponEffectType
{
    MAGICAL_ATTACK,
    PHYSICAL_ATTACK
};

struct WeaponStruct
{
    bool isCanBeStackable;
    bool isLootable;
    std::string description;
    std::string iconPath;
    PowerUpTimeType timeType;
    PowerUpUsageType usageType;
    WeaponEffectType weaponEffectType;
    float effectValue;
    float duration;
    float usageTypeValue;
};

class Weapon : public PowerUp
{

public:
    Weapon(const char* name, const Vertex& position) :
        PowerUp(name, position)
    {
        mType = PowerUpType::WEAPON;
    }
    ~Weapon()
    {
        delete icon;
        delete particle;
    }

    inline WeaponStruct getWeaponStruct() const 
    {
        return weaponStruct;
    }

    void usePowerUp() override
    {

    }
    
    void destroyByManual() override
    {

    }

    inline float getTotalAttackAfterUsage (const float baseAttack) const
    {
        return baseAttack + getWeaponStruct().effectValue;
    }

private:
    WeaponStruct weaponStruct;
    
    class Sprite* icon = nullptr;
    class Particle* particle = nullptr;
    
};

#endif // WEAPON_H

