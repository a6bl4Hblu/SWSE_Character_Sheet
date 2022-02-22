#ifndef CLAS_H
#define CLAS_H

#include <QString>
#include <QVector>
#include <lists.h>

// =========================================================================
class Clas
{
// =========================================================================
private:
// =========================================================================
    QString description;
// =========================================================================
    char baseTrainSkill;
    char startHP;
    QVector<char> baseAttack;
    QVector<char> defenceBonus;
    char hitDice;
// =========================================================================
public:
// =========================================================================
    Clas(const QString &description, char baseTrainSkill, char startHP, const QVector<char> &baseAttack, const QVector<char> &defBonus, char hitDice);
// =========================================================================
    const QString &getDescription() const;
// =========================================================================
    char getBaseTrainSkill() const;
    char getStartHP() const;
    const QVector<char> &getBaseAttack() const;
    char getHitDice() const;
    const QVector<char> &getDefenceBonus() const;
// =========================================================================
};
// =========================================================================
#endif // CLAS_H
