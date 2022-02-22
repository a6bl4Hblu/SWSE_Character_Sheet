#include "clas.h"
// =========================================================================
const QString &Clas::getDescription() const
{
    return description;
}
// =========================================================================
char Clas::getBaseTrainSkill() const
{
    return baseTrainSkill;
}

char Clas::getStartHP() const
{
    return startHP;
}

const QVector<char> &Clas::getBaseAttack() const
{
    return baseAttack;
}

const QVector<char> &Clas::getDefenceBonus() const
{
    return defenceBonus;
}

char Clas::getHitDice() const
{
    return hitDice;
}
// =========================================================================
Clas::Clas(const QString &_description, char _baseTrainSkill, char _startHP, const QVector<char> &_baseAttack, const QVector<char> &_defBonus, char _hitDice) :
    description(_description),
    baseTrainSkill(_baseTrainSkill),
    startHP(_startHP),
    baseAttack(_baseAttack),
    defenceBonus(_defBonus),
    hitDice(_hitDice)
{}
// =========================================================================
