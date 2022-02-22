#include "armor.h"
// =========================================================================
const QString &Armor::getName() const
{
    return name;
}

void Armor::setName(const QString &newName)
{
    name = newName;
}

ArmorType Armor::getType() const
{
    return type;
}

void Armor::setType(ArmorType newType)
{
    type = newType;
}

const QString &Armor::getCost() const
{
    return cost;
}

void Armor::setCost(const QString &newCost)
{
    cost = newCost;
}
// =========================================================================
const QString &Armor::getBonusRefl() const
{
    return bonusRefl;
}

void Armor::setBonusRefl(const QString &newBonusRefl)
{
    bonusRefl = newBonusRefl;
}

const QString &Armor::getBonusFort() const
{
    return bonusFort;
}

void Armor::setBonusFort(const QString &newBonusFort)
{
    bonusFort = newBonusFort;
}

const QString &Armor::getMaxDex() const
{
    return maxDex;
}

void Armor::setMaxDex(const QString &newMaxDex)
{
    maxDex = newMaxDex;
}
// =========================================================================
Availability Armor::getAvailability() const
{
    return availability;
}

void Armor::setAvailability(Availability newAvailability)
{
    availability = newAvailability;
}

const QString &Armor::getNotes() const
{
    return notes;
}

void Armor::setNotes(const QString &newNotes)
{
    notes = newNotes;
}
// =========================================================================
