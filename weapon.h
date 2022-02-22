#ifndef WEAPON_H
#define WEAPON_H
// =========================================================================
#include <QString>
#include <QVector>
#include <lists.h>
// =========================================================================
class Weapon
{
// =========================================================================
private:
// =========================================================================
    QString name;
    Size size;
    QString cost;
// =========================================================================
    QString dmg;
    bool stunDmg;
// =========================================================================
    WeaponGroup group;
    //QVector<WeaponROF> rof;
    QString rof;
    //QVector<WeaponType> type;
    QString type;
    Availability availability;
    QString notes;
// =========================================================================
public:
// =========================================================================
    const QString &getName() const;
    void setName(const QString &newName);
    Size getSize() const;
    void setSize(Size newSize);
    const QString &getCost() const;
    void setCost(const QString &newCost);
// =========================================================================
    const QString &getDmg() const;
    void setDmg(const QString &newDmg);
    bool getStunDmg() const;
    void setStunDmg(bool newStunDmg);
// =========================================================================
    WeaponGroup getGroup() const;
    void setGroup(WeaponGroup newGroup);
    const QString &getRof() const;
    void setRof(const QString &newRof);
    const QString &getType() const;
    void setType(const QString &newType);
    Availability getAvailability() const;
    void setAvailability(Availability newAvailability);
    const QString &getNotes() const;
    void setNotes(const QString &newNotes);
// =========================================================================
};
// =========================================================================
#endif // WEAPON_H
