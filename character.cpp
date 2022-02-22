#include "character.h"
// =========================================================================
const QString &Character::getPlayer() const
{
    return player;
}

void Character::setPlayer(const QString &newPlayer)
{
    player = newPlayer;
}

const QString &Character::getName() const
{
    return name;
}

void Character::setName(const QString &newName)
{
    name = newName;
}

const QString &Character::getForcePoints() const
{
    return forcePoints;
}

void Character::setForcePoints(const QString &newForcePoints)
{
    forcePoints = newForcePoints;
}
// =========================================================================
Gender Character::getGender() const
{
    return gender;
}

void Character::setGender(Gender newGender)
{
    gender = newGender;
}

const QString &Character::getAge() const
{
    return age;
}

void Character::setAge(const QString &newAge)
{
    age = newAge;
}

const QString &Character::getHeight() const
{
    return height;
}

void Character::setHeight(const QString &newHeight)
{
    height = newHeight;
}

const QString &Character::getWeight() const
{
    return weight;
}

void Character::setWeight(const QString &newWeight)
{
    weight = newWeight;
}

const QString &Character::getSpeed() const
{
    return speed;
}

void Character::setSpeed(const QString &newSpeed)
{
    speed = newSpeed;
}
/*
const QVector<Language> &Character::getLanguages() const
{
    return languages;
}

void Character::setLanguages(const QVector<Language> &newLanguages)
{
    languages = newLanguages;
}
*/
const QString &Character::getLanguage() const
{
    return language;
}

void Character::setLanguage(const QString &newLanguage)
{
    language = newLanguage;
}
// =========================================================================
SpeciesName Character::getSpecies() const
{
    return species;
}

void Character::setSpecies(SpeciesName newSpecies)
{
    species = newSpecies;
}

Size Character::getSize() const
{
    return size;
}

void Character::setSize(Size newSize)
{
    size = newSize;
}

ClasName Character::getClas() const
{
    return clas;
}

void Character::setClas(ClasName newClas)
{
    clas = newClas;
    // defence change?
    // baseAttackBonus change?
}

unsigned char Character::getLevel() const
{
    return level;
}

void Character::setLevel(unsigned char newLevel)
{
    char delta = newLevel/2 - level/2;

    for(char i=FirstSkill; i <= LastSkill; i++)
        skillScore.replace(i, skillScore.at(i) + delta);
    level = newLevel;
    //baseAttackBonus change?
    //nextXP change?
}

unsigned int Character::getXp() const
{
    return xp;
}

void Character::setXp(unsigned int newXp)
{
    xp = newXp;
}
// =========================================================================
const QVector<char> &Character::getAbilityScores() const
{
    return abilityScore;
}

char Character::getAbilityScore(Ability gettedAbility) const
{
    return abilityScore.at(gettedAbility);
}

void Character::setAbilityScore(Ability settedAbility, char newScore, const QVector<char> *clasBonus, QVector<Ability> *skillAbility)
{
    abilityScore.replace(settedAbility, newScore);
    abilityMod.replace(settedAbility, (newScore - (newScore % 2==0 ? 10  : 11))/2);

    if(settedAbility == Constitution)
    {
        updDefenceScore(Fortitude, clasBonus->at(Fortitude));
        updSkillScore(Endurance, skillAbility);
    }
    else
    {
        switch(settedAbility)
        {
            case Dexterity :
                updDefenceScore(Reflex, clasBonus->at(Reflex));
                break;
            case Wisdom :
                updDefenceScore(Will, clasBonus->at(Will));
                break;
            default :
                break;
        }

        for(char i = FirstSkill; i <= LastSkill; i++)
            if(skillAbility->at(i) == settedAbility)
                updSkillScore((Skill)i, skillAbility);
    }
}

char Character::getAbilityMod(Ability gettedAbility) const
{
    return abilityMod.at(gettedAbility);
}
// =========================================================================
const QVector<char> &Character::getSkillScores() const
{
    return skillScore;
}

char Character::getSkillScore(Skill gettedSkill) const
{
    return skillScore.at(gettedSkill);
}

void Character::setSkillScore(Skill settedSkill, char newSkillScore)
{
    skillScore.replace(settedSkill, newSkillScore);
}

void Character::updSkillScore(Skill upddedSkill, QVector<Ability> *skillAbility)
{
    char checks = (skillTrain.at(upddedSkill) ? 5 : 0) + (skillFocus.at(upddedSkill) ? 5 : 0);
    setSkillScore(upddedSkill, level/2 + abilityMod.at(skillAbility->at(upddedSkill)) + checks + skillMisc.at(upddedSkill));
}

char Character::getSkillMisc(Skill gettedSkill) const
{
    return skillMisc.at(gettedSkill);
}

void Character::setSkillMisc(Skill settedSkill, char newSkillMisc, QVector<Ability> *skillAbility)
{
    skillMisc.replace(settedSkill, newSkillMisc);
    updSkillScore(settedSkill, skillAbility);
}

bool Character::getSkillClass(Skill gettedSkill) const
{
    return skillClass.at(gettedSkill);
}

void Character::setSkillClass(Skill settedSkill, bool newSkillClass)
{
    skillClass.replace(settedSkill, newSkillClass);
}

bool Character::getSkillTrain(Skill gettedSkill) const
{
    return skillTrain.at(gettedSkill);
}

void Character::setSkillTrain(Skill settedSkill, bool newSkillTrain, QVector<Ability> *skillAbility)
{
    skillTrain.replace(settedSkill, newSkillTrain);
    updSkillScore(settedSkill, skillAbility);
}

bool Character::getSkillFocus(Skill gettedSkill) const
{
    return skillFocus.at(gettedSkill);
}

void Character::setSkillFocus(Skill settedSkill, bool newSkillFocus, QVector<Ability> *skillAbility)
{
    skillFocus.replace(settedSkill, newSkillFocus);
    updSkillScore(settedSkill, skillAbility);
}
// =========================================================================
const QString &Character::getMaxHP() const
{
    return maxHP;
}

void Character::setMaxHP(const QString &newMaxHP)
{
    maxHP = newMaxHP;
}

const QString &Character::getCurrentHP() const
{
    return currentHP;
}

void Character::setCurrentHP(const QString &newCurrentHP)
{
    currentHP = newCurrentHP;
}

unsigned char Character::getDmgThreshold() const
{
    return dmgThreshold;
}

void Character::setDmgThreshold(unsigned char newDmgThreshold)
{
    dmgThreshold = newDmgThreshold;
}

void Character::updDmgThreshold()
{
    setDmgThreshold(defencesScore.at(Fortitude) + dmgThresholdMisc);
}

unsigned char Character::getDmgThresholdMisc() const
{
    return dmgThresholdMisc;
}
void Character::setDmgThresholdMisc(unsigned char newDmgThresholdMisc)
{
    dmgThresholdMisc = newDmgThresholdMisc;
    updDmgThreshold();
}

const QString &Character::getDmgReduction() const
{
    return dmgReduction;
}

void Character::setDmgReduction(const QString &newDmgReduction)
{
    dmgReduction = newDmgReduction;
}

const QString &Character::getShieldRating() const
{
    return shieldRating;
}

void Character::setShieldRating(const QString &newShieldRating)
{
    shieldRating = newShieldRating;
}

Condition Character::getCondition() const
{
    return condition;
}

void Character::setCondition(Condition newCondition)
{
    condition = newCondition;
}
// =========================================================================
void Character::setDefenceScore(Defence def, char newDefenceScore)
{
    defencesScore.replace(def, newDefenceScore);
    if(def == Fortitude)
        updDmgThreshold();
}

char Character::getDefenceScore(Defence def) const
{
    return defencesScore.at(def);
}

void Character::updDefenceScore(Defence def, char clasBonus)
{
    char mod = abilityMod.at(2*def*def - 3*def + 2);

    setDefenceScore(def, 10 + defencesArmor.at(def) + mod + defencesMisc.at(def) + clasBonus);
}

void Character::setDefenceArmor(Defence def, char newDefenceArmor, char clasBonus)
{
    defencesArmor.replace(def, newDefenceArmor);
    updDefenceScore(def, clasBonus);
}

char Character::getDefenceArmor(Defence def) const
{
    return defencesArmor.at(def);
}

void Character::setDefenceMisc(Defence def, char newDefenceMisc, char clasBonus)
{
    defencesMisc.replace(def, newDefenceMisc);
    updDefenceScore(def, clasBonus);
}

char Character::getDefenceMisc(Defence def) const
{
    return defencesMisc.at(def);
}
// =========================================================================
const QString &Character::getNotes() const
{
    return notes;
}

void Character::setNotes(const QString &newNotes)
{
    notes = newNotes;
}

const QString &Character::getStory() const
{
    return story;
}

void Character::setStory(const QString &newStory)
{
    story = newStory;
}

const QString &Character::getFeats() const
{
    return feats;
}

void Character::setFeats(const QString &newFeats)
{
    feats = newFeats;
}

const QString &Character::getTalents() const
{
    return talents;
}

void Character::setTalents(const QString &newTalents)
{
    talents = newTalents;
}
// =========================================================================
int Character::getCredits() const
{
    return credits;
}

void Character::setCredits(int newCredits)
{
    credits = newCredits;
}

Armor *Character::getArmor() const
{
    return armor;
}

const QVector<Weapon *> &Character::getWeapons() const
{
    return weapons;
}

Weapon *Character::getWeapon(int gettedWeapon) const
{
    return weapons.at(gettedWeapon);
}
/*
void Character::addWeapon()
{
    weapons.append(new Weapon);
}

void Character::removeWeapon(int removedWeapon)
{
    weapons.remove(removedWeapon);
}
*/
const QString &Character::getEquipments() const
{
    return equipments;
}

void Character::setEquipments(const QString &newEquipments)
{
    equipments = newEquipments;
}
// =========================================================================
