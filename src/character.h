#ifndef CHARACTER_H
#define CHARACTER_H
// =========================================================================
#include <clas.h>
#include <species.h>
#include <weapon.h>
#include <armor.h>
#include <weapon.h>
#include <lists.h>
// =========================================================================
class Character
{
// =========================================================================
private:
// =========================================================================
    QString player;
    QString name;
    QString forcePoints;
// =========================================================================
    SpeciesName species = Human;
    Size size = Medium;
    ClasName clas = Jedi;
    unsigned char level = 1;
    unsigned int xp = 0;
// =========================================================================
    Gender gender = U;
    QString age = "20";
    QString height = "180";
    QString weight = "80";
    QString speed = "6";
    //QVector<Language> languages = QVector<Language>{BasicLang};
    QString language;
// =========================================================================
    QVector<char> abilityScore = QVector<char>(LastAbility+1,10);
    QVector<char> abilityMod = QVector<char>(LastAbility+1,0);
// =========================================================================
    QVector<char> skillScore = QVector<char>(LastSkill+1,0);
    QVector<char> skillMisc = QVector<char>(LastSkill+1,0);
    QVector<bool> skillClass = QVector<bool>(LastSkill+1,false);
    QVector<bool> skillTrain = QVector<bool>(LastSkill+1,false);
    QVector<bool> skillFocus = QVector<bool>(LastSkill+1,false);
// =========================================================================
    QString maxHP = "0";
    QString currentHP = "0";
    unsigned char dmgThreshold = 10;
    unsigned char dmgThresholdMisc = 0;
    QString dmgReduction;
    QString shieldRating;
    Condition condition = CondNormal;
// =========================================================================
    QVector<char> defencesScore = QVector<char>(3,11);
    QVector<char> defencesArmor = QVector<char>(3,0);
    QVector<char> defencesMisc = QVector<char>(3,0);
// =========================================================================
    //QVector<QString *> feats;
    QString feats;
    //QVector<QString *> talents;
    QString talents;
    QString notes;
    QString story;
// =========================================================================
    int credits = 0;
    Armor *armor = new Armor;
    QVector<Weapon *> weapons = QVector<Weapon *>{new Weapon, new Weapon, new Weapon, new Weapon, new Weapon, new Weapon};
    //QVector<QString *> equipments;
    QString equipments;
// =========================================================================
public:
// =========================================================================
    QString saveFileName;
// =========================================================================
    const QString &getPlayer() const;
    void setPlayer(const QString &newPlayer);
    const QString &getName() const;
    void setName(const QString &newName);
    const QString &getForcePoints() const;
    void setForcePoints(const QString &newForcePoints);
// =========================================================================
    Gender getGender() const;
    void setGender(Gender newGender);
    const QString &getAge() const;
    void setAge(const QString &newAge);
    const QString &getHeight() const;
    void setHeight(const QString &newHeight);
    const QString &getWeight() const;
    void setWeight(const QString &newWeight);
    const QString &getSpeed() const;
    void setSpeed(const QString &newSpeed);
    /*const QVector<Language> &getLanguages() const;
    void setLanguages(const QVector<Language> &newLanguages); */
    const QString &getLanguage() const;
    void setLanguage(const QString &newLanguage);
// =========================================================================
    SpeciesName getSpecies() const;
    void setSpecies(SpeciesName newSpecies);
    Size getSize() const;
    void setSize(Size newSize);
    ClasName getClas() const;
    void setClas(ClasName newClas);
    unsigned char getLevel() const;
    void setLevel(unsigned char newLevel);
    unsigned int getXp() const;
    void setXp(unsigned int newXp);
// =========================================================================
    const QVector<char> &getAbilityScores() const;
    char getAbilityScore(Ability gettedAbility) const;
    void setAbilityScore(Ability settedAbility, char newScore, const QVector<char> *clasBonus, QVector<Ability> *skillAbility);
    char getAbilityMod(Ability gettedAbility) const;
    const QVector<char> &getSkillScores() const;
    char getSkillScore(Skill gettedSkill) const;
    void setSkillScore(Skill gettedSkill, char newSkillScore);
    void updSkillScore(Skill upddedSkill, QVector<Ability> *skillAbility);
    char getSkillMisc(Skill gettedSkill) const;
    void setSkillMisc(Skill settedSkill, char newSkillMisc, QVector<Ability> *skillAbility);
    bool getSkillClass(Skill gettedSkill) const;
    void setSkillClass(Skill settedSkill, bool newSkillClass);
    bool getSkillTrain(Skill gettedSkill) const;
    void setSkillTrain(Skill settedSkill, bool newSkillTrain, QVector<Ability> *skillAbility);
    bool getSkillFocus(Skill gettedSkill) const;
    void setSkillFocus(Skill settedSkill, bool newSkillFocus, QVector<Ability> *skillAbility);
// =========================================================================
    const QString &getMaxHP() const;
    void setMaxHP(const QString &newMaxHP);
    const QString &getCurrentHP() const;
    void setCurrentHP(const QString &newCurrentHP);
    unsigned char getDmgThreshold() const;
    void setDmgThreshold(unsigned char newDmgThreshold);
    void updDmgThreshold();
    unsigned char getDmgThresholdMisc() const;
    void setDmgThresholdMisc(unsigned char newDmgThresholdMisc);
    const QString &getDmgReduction() const;
    void setDmgReduction(const QString &newDmgReduction);
    const QString &getShieldRating() const;
    void setShieldRating(const QString &newShieldRating);
    Condition getCondition() const;
    void setCondition(Condition newCondition);
// =========================================================================
    char getDefenceScore(Defence def) const;
    void setDefenceScore(Defence def, char newDefenceScore);
    void updDefenceScore(Defence def, char clasBonus);
    char getDefenceArmor(Defence def) const;
    void setDefenceArmor(Defence def, char newDefenceArmor, char clasBonus);
    char getDefenceMisc(Defence def) const;
    void setDefenceMisc(Defence def, char newDefenceMisc, char clasBonus);
// =========================================================================
    const QString &getNotes() const;
    void setNotes(const QString &newNotes);
    const QString &getStory() const;
    void setStory(const QString &newStory);
    const QString &getFeats() const;
    void setFeats(const QString &newFeats);
    const QString &getTalents() const;
    void setTalents(const QString &newTalents);
// =========================================================================
    int getCredits() const;
    void setCredits(int newCredits);
    Armor *getArmor() const;
    const QVector<Weapon *> &getWeapons() const;
    Weapon *getWeapon(int gettedWeapon) const;
    /*void addWeapon();
    void removeWeapon(int removedWeapon);*/
    const QString &getEquipments() const;
    void setEquipments(const QString &newEquipments);
// =========================================================================
};
// =========================================================================
#endif // CHARACTER_H
