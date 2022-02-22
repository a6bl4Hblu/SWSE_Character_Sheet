#ifndef ARMOR_H
#define ARMOR_H
// =========================================================================
#include <QString>
#include <lists.h>
// =========================================================================
class Armor
{
// =========================================================================
private:
// =========================================================================
    QString name;
    ArmorType type;
    QString cost;
// =========================================================================
    QString bonusRefl;
    QString bonusFort;
    QString maxDex;
// =========================================================================
    Availability availability;
    QString notes;
// =========================================================================
public:
// =========================================================================

    // =========================================================================
    const QString &getName() const;
    void setName(const QString &newName);
    ArmorType getType() const;
    void setType(ArmorType newType);
    const QString &getCost() const;
    void setCost(const QString &newCost);
// =========================================================================
    const QString &getBonusRefl() const;
    void setBonusRefl(const QString &newBonusRefl);
    const QString &getBonusFort() const;
    void setBonusFort(const QString &newBonusFort);
    const QString &getMaxDex() const;
    void setMaxDex(const QString &newMaxDex);
// =========================================================================
    Availability getAvailability() const;
    void setAvailability(Availability newAvailability);
    const QString &getNotes() const;
    void setNotes(const QString &newNotes);
// =========================================================================
};
// =========================================================================
#endif // ARMOR_H
