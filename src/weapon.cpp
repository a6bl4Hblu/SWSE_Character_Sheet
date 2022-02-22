#include "weapon.h"
// =========================================================================
const QString &Weapon::getName() const
{
    return name;
}

void Weapon::setName(const QString &newName)
{
    name = newName;
}

Size Weapon::getSize() const
{
    return size;
}

void Weapon::setSize(Size newSize)
{
    size = newSize;
}

const QString &Weapon::getCost() const
{
    return cost;
}

void Weapon::setCost(const QString &newCost)
{
    cost = newCost;
}
// =========================================================================
const QString &Weapon::getDmg() const
{
    return dmg;
}

void Weapon::setDmg(const QString &newDmg)
{
    dmg = newDmg;
}

bool Weapon::getStunDmg() const
{
    return stunDmg;
}

void Weapon::setStunDmg(bool newStunDmg)
{
    stunDmg = newStunDmg;
}
// =========================================================================
WeaponGroup Weapon::getGroup() const
{
    return group;
}

void Weapon::setGroup(WeaponGroup newGroup)
{
    group = newGroup;
}

const QString &Weapon::getRof() const
{
    return rof;
}

void Weapon::setRof(const QString &newRof)
{
    rof = newRof;
}

const QString &Weapon::getType() const
{
    return type;
}

void Weapon::setType(const QString &newType)
{
    type = newType;
}

Availability Weapon::getAvailability() const
{
    return availability;
}

void Weapon::setAvailability(Availability newAvailability)
{
    availability = newAvailability;
}

const QString &Weapon::getNotes() const
{
    return notes;
}

void Weapon::setNotes(const QString &newNotes)
{
    notes = newNotes;
}
// =========================================================================
