#include "species.h"
// =========================================================================
const QString &Species::getDescription() const
{
    return description;
}
// =========================================================================
const QVector<QString> &Species::getTraits() const
{
    return traits;
}

void Species::setTraits(const QVector<QString> &newTraits)
{
    traits = newTraits;
}
// =========================================================================
Species::Species(const QString &_description, const QVector<QString> &_traits) :
    description(_description),
    traits(_traits)
{}
// =========================================================================
