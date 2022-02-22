#ifndef RACE_H
#define RACE_H

#include <QString>
#include <QVector>
#include <lists.h>


class Species
{
// =========================================================================
private:
// =========================================================================
    QString description;
// =========================================================================
    QVector<QString> traits;
// =========================================================================
public:
// =========================================================================
    Species(const QString &description, const QVector<QString> &traits);
// =========================================================================
    const QString &getDescription() const;
// =========================================================================
    const QVector<QString> &getTraits() const;
    void setTraits(const QVector<QString> &newTraits);
// =========================================================================
};

#endif // RACE_H
