#ifndef LISTS_H
#define LISTS_H

// =========================================================================
enum ClasName
{
    Jedi,
    Noble,
    Scoundrel,
    Scout,
    Soldier
};

enum SpeciesName
{
    Human,
    Duros,
    KelDor,
    DroidAstromech,
    DroidBattle,
    DroidProbe,
    DroidProtocol
};

enum Size
{
    Tiny,
    Small,
    Medium,
    Large,
    Huge
};
// =========================================================================
enum Ability
{
    Strength,
    Dexterity,
    Constitution,
    Intelligence,
    Wisdom,
    Charisma,
    FirstAbility = Strength,
    LastAbility = Charisma
};
// =========================================================================
enum Skill
{
    Acrobatics,
    Climb,
    Deception,
    Endurance,
    GatherInfo,
    Initiative,
    Jump,
    KnowBureoucracy,
    KnowGalacticLore,
    KnowLifeSciences,
    KnowPhisicalSciences,
    KnowSocialSciences,
    KnowTactics,
    KnowTechnology,
    Mechanics,
    Perceprion,
    Persuation,
    Pilot,
    Ride,
    Stealth,
    Survival,
    Swim,
    TreatInjury,
    UseComputer,
    UseTheForce,
    FirstSkill = Acrobatics,
    LastSkill = UseTheForce
};
// =========================================================================
enum Gender
{
    M,
    F,
    G,
    D,
    U
};
// =========================================================================
enum Language
{
    BasicLang,
    MandoaLang,
    DurosLang,
    KelDorLang,
    BinaryLang,
    HutteseLang,
    MilitarySignLang
};

enum Condition
{
    CondNormal,
    Cond1,
    Cond2,
    Cond5,
    Cond10,
    CondHelpless,
    FirstCond = CondNormal,
    LastCond = CondHelpless
};
// =========================================================================
enum Defence
{
    Fortitude,
    Reflex,
    Will
};
// =========================================================================
enum Availability
{
    Usual,
    Licensed,
    Restricted,
    Military,
    Illegal,
    Rare
};

enum ArmorType
{
    LightArmor,
    MediumArmor,
    HeavyArmor
};

enum WeaponGroup
{
    AdvancedMeleeWeapons,
    ExoticWeapons,
    LightsabersWeapons,
    SimpleWeapons,
    UnarmedWeapons,
    HeavyWeapons,
    PistolWeapons,
    RifleWeapons,
    ExplosivesWeapons
};
/*
enum WeaponROF
{
    MROF,
    SROF,
    AROF,
    TROF
};

enum WeaponType
{
    Energy,
    Ion,
    Piercing,
    Slashing,
    Bludgeoning
};
*/
// =========================================================================
#endif // LISTS_H
