#ifndef PREGEN_H
#define PREGEN_H

#include <QString>
#include <QVector>
#include <lists.h>
#include <clas.h>
#include <species.h>
#include <weapon.h>
#include <armor.h>

// =========================================================================
QVector<QString> clasNameText = QVector<QString>{
        "Jedi",
        "Noble",
        "Scoundrel",
        "Scout",
        "Soldier"};

// Base Attack Bonus arrays
QVector<char> strongBaseAttack{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
QVector<char> weakBaseAttack{0,1,2,3,3,4,5,6,6,7,8,9,9,10,11,12,12,13,14,15};
// List of all classes
QVector<Clas *> clases{
            new Clas( // Jedi
                      "A man with a lightsaber",
                      2, 30, strongBaseAttack, QVector<char>{1, 1, 1}, 10),
            new Clas( // Noble
                      "A man with a crown",
                      6, 18, weakBaseAttack, QVector<char>{0, 1, 2}, 6),
            new Clas( // Scoundrel
                      "A man with a pistol",
                      4, 18, weakBaseAttack, QVector<char>{0, 2, 1}, 6),
            new Clas( // Scout
                      "A man with an SVD",
                      5, 24, weakBaseAttack, QVector<char>{1, 2, 0}, 8),
            new Clas( // Soldier
                      "A man with a automat",
                      3, 30, strongBaseAttack, QVector<char>{2, 1, 0}, 10)};
// =========================================================================
QVector<QString> speciesNameText = QVector<QString>{
        "Human",
        //"Devaronian",
        "Duros",
        "Kel Dor",
        //"Mon Calamari",
        //"Trandoshan",
        //"Twi'lek",
        //"Zabrak",
        //"Zeltron",
        "Droid (Astromech)",
        "Droid (Battle)",
        "Droid (Probe)",
        "Droid (Protocol)"};

// List of all specieses
QVector<Species *> specieses{
            new Species( // Human
                         QString("One of the most dominant Species in the entire Galaxy."),
                         QVector<QString>{
                             "Bonus Talent.",
                             "Bonus Feat."}),
            /*new Species( // Devaronian
                         QString("(Male) Hairless humanoids with red-tinted skin, sharp incisors, and a pair of large horns growing from their foreheads. (Female) Hornless humanoids covered in thick fur with prominent canine teeth."),
                         QVector<QString>{
                             "(Male) +2 Dex, -2 Wis, -2 Cha, (Female) +2 Int, +2 Wis, -2 Dex",
                             "Conditional Bonus Feat: If Skill Trained, then Skill Focus (Deception only).",
                             "Natural Curiosity: Once per encounter as a Standard Action, can make a Perception check against a single target within line of sight (DC 15 or the result of an opposed Stealth check, if the target is actively attempting to hide) to gain a +1 insight bonus on attack rolls against that target."}),*/
            new Species( // Duros
                         QString("Tall, hairless humanoids with smooth blue-green skin, red eyes, lipless mouths, long thin noseless faces and green blood."),
                         QVector<QString>{
                             "+2 Dex, +2 Int, -2 Con",
                             "Expert Pilot: Reroll any Pilot checks (take the last)."}),
            /*new Species( // Ithorian
                         QString("Tall humanoids with long necks that curl forward and end in dome-shaped heads and two mouths, one on each side of their neck, producing a stereo effect when they talk."),
                         QVector<QString>{
                             "+2 Wis, +2 Cha, -2 Dex",
                             "Bellow: Can emit a terrible subsonic Bellow with [1d20 + Character Level] attack roll against to the Fortitude Defense of all objects in a 6-Square Cone and 3d6 of Sonic damage as a Standard Action. If the attack misses, the target takes half damage. Each use moves the user -1 step along the Condition Track. Can add more dice (d6s) to the damage, but each additional 1d6 of damage moves another -1 step along the Condition Track."
                             "Conditional Bonus Feat: If Skill Trained, then Skill Focus (Knowledge [Life Sciences] only).",
                             "Iron Will: Gain a +2 Species bonus to Will Defense.",
                             "Survival Instinct: Reroll any Survival checks (take the last)."}),*/
            new Species( // Kel Dor
                         QString("Hairless humanoids with trick lethery orange skin, black eyes, wearing breath masks that covered their eyes, nose and mouth."),
                         QVector<QString>{
                             "+2 Dex, +2 Wis, -2 Con",
                             "Keen Force Sense: Reroll any Use the Force checks (Search Feelings/Sense of Force) (take the best)."}),
            /*new Species( // Klatooinian
                         QString("Hairless humanoids with brown course skin, flat muzzle, pronounced jowls, and deepset eyes beneath a heavy brow."),
                         QVector<QString>{
                             "+2 Con, -2 Wis, -2 Int",
                             "Iron Will: Gain a +2 Species bonus to Will Defense."}),*/
            /*new Species( // Mon Calamari
                         QString("Amphibious humanoids with high-domed heads, large eyes, and smooth, mottled skin."),
                         QVector<QString>{
                             "+2 Int, +2 Wis, -2 Con",
                             "Breathe Underwater: Can't drown in water",
                             "Conditional Bonus Feat: If Skill Trained, then Skill Focus (Perceprion only).",
                             "Expert Swimmer: Reroll any Swim check (take the last). Can Take 10 on Swim checks, even when distracted or threatened.",
                             "Low-Light Vision: Ignore Concealment (but not Total Concealment) from darkness."}),*/
            /*new Species( // Sullustan
                         QString("Short hairless humanoids with large eyes, big ears, and jowls"),
                         QVector<QString>{
                             "+2 Dex, -2 Con",
                             "Darkvision: Ignore Concealment (and Total Concealment) from darkness."
                             "Expert Climber: Can Take 10 on Climb checks, even when distracted or threatened.
                             "Heightened Awareness: Reroll any Perception checks,( but the result of the reroll must be accepted, even if it is worse (take the last)."}),*/
            /*new Species( // Trandoshan
                         QString("Tall reptilian humanoids with scaly green hides."),
                         QVector<QString>{
                             "+2 Str, -2 Dex",
                             "Darkvision: Ignore Concealment (and Total Concealment) from darkness.",
                             "Limb Regeneration: Regrows a lost limb in 1d10 days. At the end of that time, all Persistent Conditions associated with the loss of the limb are removed.",
                             "Natural Armor: Gain a +1 Natural Armor bonus to their Reflex Defense. A Natural Armor bonus stacks with an Armor bonus."),*/
            /*new Species( // Twi'lek
                         QString("Hairless humanoids with the tentacular \"Head-Tails\" (Lekku) that protrude from the backs of their heads."),
                         QVector<QString>{
                             "+2 Cha, -2 Wis",
                             "Deceptive: Reroll any Deception check (take the last).",
                             "Great Fortitude: Gain +2 Species bonus to Fortitude Defense.",
                             "Low-Light Vision: Ignore Concealment (but not Total Concealment) from darkness."}),*/
            /*new Species( // Zabrak
                         QString("Hairless humanoids, distinguished by patterns of vestigial horns atop their heads."),
                         QVector<QString>{
                             "Heightened Awareness: Reroll any Perception checks (take the last).",
                             "Superior Defenses: Gain a +1 Species bonus to all Defenses."}),*/
            /*new Species( // Zeltron
                         QString("Humanoids considered to be attractive by Human standarts with red skin."),
                         QVector<QString>{
                             "+2 Cha, -2 Wis",
                             "Empathy: Add Charisma bonus (if any) to Perception checks (Sense Deception|Sense Influence).",
                             "Pheromones: Gain a +5 Species bonus on Persuasion checks (change the Attitude of creatures). Does not apply to other Zeltrons."}),*/
            new Species( // Droid (Astromech)
                         QString("A type of droid that served as an automated mechanic, performing a variety of repair duties."),
                         QVector<QString>{
                             "+2 Int, -2 Cha, -2 Con",
                             "Droid Traits: Second-Degree Droid.",
                             "Bonus Equipment: locomotion (wheeled, walking), magnetic feet, heuristic processor, appendages (6 tool, 1 claw), astrogation buffer (5). diagnostics package, internal storage (2 kg).",
                             "Hardwired Design (Mechanics): Trained in the Mechanics skill.",
                             "Conditional Bonus Feat: If Skill Trained, then Skill Focus (Mechanics/Use Computer only)."}),
            new Species( // Droid (Battle)
                         QString("A type of droid designed for combat."),
                         QVector<QString>{
                             "+2 Dex, -2 Int",
                             "Droid Traits: Fourth-Degree Droid.",
                             "Bonus Equipment: walking locomotion, plasteel shell (+2 armor), basic processor, internal comlink, locked access, 2 hand appendages, vocabulator.",
                             "Bonus Feats: At 1st level, can select one Armor Proficiency feat and one Weapon Proficiency feat for which it meets the prerequisites."}),
            new Species( // Droid (Probe)
                         QString("A type of droid that could be used for deep space exploration and reconnaissance."),
                         QVector<QString>{
                             "+2 Wis, -2 Cha",
                             "Droid Traits: Fourth-Degree Droid.",
                             "Bonus Equipment: hovering locomotion, heuristic processor, internal comlink, locked access, appendages (1 hand, 1 tool), improved sensor package, darkvision.",
                             "Hardwired Design (Perception): Trained in the Perception skill.",
                             "Conditional Bonus Feat: If Skill Trained, then Skill Focus (Perception/Stealth only)."}),
            new Species( // Droid (Protocol)
                         QString("A droid whose job was to aid sentients with their etiquette and relations with each other in the galaxy."),
                         QVector<QString>{
                             "+2 Wis, +2 Cha, -2 Dex",
                             "Droid Traits: Third-Degree Droid.",
                             "Bonus Equipment: walking locomotion, basic processor, 2 hand appendages, vocabulator, translator unit (DC 10).",
                             "Hardwired Design (Persuation): Trained in the Perception skill.",
                             "Bonus Feat: Can select Skill Training (Knowledge [Bureaucracy, Galactic Lore or Social Sciences])."})};
// =========================================================================
QVector<QString> sizeNameText = QVector<QString>{
        "Tiny",
        "Small",
        "Medium",
        "Large",
        "Huge"};
// =========================================================================
QVector<QString> abilityNameText = QVector<QString>{
        "Strength",
        "Dexterity",
        "Constitution",
        "Intelligence",
        "Wisdom",
        "Charisma"};
QVector<QString> skillNameText = QVector<QString>{
        "Acrobatics",
        "Climb",
        "Deception",
        "Endurance",
        "Gather Information",
        "Initiative",
        "Jump",
        "Know. [Bureaucracy]",
        "Know. [Galactic Lore]",
        "Know. [Life Sciences]",
        "Know. [Phisical Sciences]",
        "Know. [Social Sciences]",
        "Know. [Tactics]",
        "Know. [Technology]",
        "Mechanics",
        "Perceprion",
        "Persuation",
        "Pilot",
        "Ride",
        "Stealth",
        "Survival",
        "Swim",
        "Treat Injury",
        "Use Computer",
        "Use the Force"};
// =========================================================================
QVector<QString> genderNameText = QVector<QString>{
        "M",
        "F",
        "G",
        "D",
        "U"};
QVector<QString> languageNameText = QVector<QString>{
        "Basic",
        "Mandoa",
        "Duros",
        "Kel Dor",
        "Binary"};
QVector<QString> conditionNameText = QVector<QString>{
        "Normal",
        "-1 Penalty",
        "-2 Penalty",
        "-5 Penalty",
        "-10 Penalty",
        "Helpless"};
// =========================================================================
// Weapon Group list
QVector<QString> weaponGroupNameText{
    "Adv. Melee",
    "Exotic",
    "Lightsaber",
    "Simple",
    "Unarmed",
    "Heavy",
    "Pistol",
    "Rifle",
    "Explosive"};
// Armor Type list
QVector<QString> armorTypeNameText{
    "Light",
    "Medium",
    "Heavy"};
// Availability list
QVector<QString> availabilityNameText{
    "Usual",
    "Licensed",
    "Restricted",
    "Military",
    "Illegal",
    "Rare"};
/*
// Weapons names list
QVector<QString> weaponsMeleeAdvancedNameText{
    "Vibrodagger",
    "Vidroblade",
    "Vibrobayonet",
    "Force Pike",
    "Electrostaff",
    "Vibro-ax"};
QVector<QString> weaponsMeleeExoticNameText{
    "Atlatl",
    "Amphistaff",
    "Cesta"};
QVector<QString> weaponsMeleeLightsaberNameText{
    "Lightsaber (short)",
    "Lightsaber",
    "Lightsaber (double)"};
QVector<QString> weaponsMeleeSimpleNameText{
    "Knife",
    "Club/Baton",
    "Stun Baton",
    "Mace",
    "Spear",
    "Bayonet",
    "Quarterstaff"};
QVector<QString> weaponsMeleeUnarmedNameText{
    "Unarmed (small)",
    "Unarmed (medium)",
    "Combat Gloves(small)",
    "Combat Gloves(medium)"};
QVector<QString> weaponsRangeExoticNameText{
    "Flamethrower",
    "Bowcaster"};
QVector<QString> weaponsRangeHeavyNameText{
    "Grenade Launcher",
    "Blaster Heavy Repeating",
    "Blaster Cannon",
    "Missle Launcher",
    "Blaster E-Web Repeating"};
QVector<QString> weaponsRangePistolNameText{
    "Blaster Pistol (hold-out)",
    "Blaster Pistol",
    "Blaster Pistol (sporting)",
    "Ion Pistol",
    "Slugthrower Pistol"};
QVector<QString> weaponsRangeRifleNameText{
    "Blaster Pistol (heavy)",
    "Blaster Carbin",
    "Blaster Rifle",
    "Blaster Rifle (sporting)",
    "Blaster Ion",
    "Blaster Rifle",
    "Slugthrower Rifle",
    "Blaster Light Repeating",
    "Blaster Rifle (heavy)"};
QVector<QString> weaponsRangeSimpleNameText{
    "Energy Ball",
    "Grenade (frag)",
    "Grenade (ion)",
    "Grenade (stun)",
    "Thermal Detonator"
    "Sling",
    "Bow",
    "Net"};
// Armors names list
QVector<QString> armorLightNameText{
    "Blast Helmet and Vest",
    "Fight Suit (padded)",
    "Combat Jumpsuit",
    "Fight Suit (armored)",
    "Vonduun Crabshell",
    "Stormtrooper Armor"};
QVector<QString> armorMediumNameText{
    "Ceremonial Armor",
    "Corellian Powersuit",
    "Battle Armor"};
QVector<QString> armorHeavyNameText{
    "Armored Spacesuit",
    "Battle Armor (heavy)"};
*/

/*
// List of all weapons
QVector<Weapon *> weaponsAdvancedMelee{
            new Weapon(Tiny, 200, "2d4", "-", 1, QVector<WeaponROF>{MROF}, QVector<WeaponType>{Slashing, Piercing}, Usual),
            new Weapon(Small, 250, "2d6", "-", 1.8, QVector<WeaponROF>{MROF}, QVector<WeaponType>{Slashing, Piercing}, Licensed),
            new Weapon(Medium, 350, "2d6", "-", 1, QVector<WeaponROF>{MROF}, QVector<WeaponType>{Piercing}, Licensed),
            new Weapon(Medium, 500, "2d8", "2d8", 2, QVector<WeaponROF>{MROF}, QVector<WeaponType>{Piercing, Energy}, Restricted),
            new Weapon(Large, 3000, "2d6", "2d6", 2, QVector<WeaponROF>{MROF}, QVector<WeaponType>{Bludgeoning, Energy}, Restricted),
            new Weapon(Large, 500, "2d10", "-", 6, QVector<WeaponROF>{MROF}, QVector<WeaponType>{Slashing}, Restricted)
};
*/
// List of all armors

// =========================================================================
// Abilities short names list
/*QVector<QString> absString = QVector<QString>{
        "str",
        "dex",
        "con",
        "int",
        "wis",
        "cha"};
// Skills short names list
QVector<QString> sksString = QVector<QString>{
        "acr",
        "cli",
        "dec",
        "end",
        "gat"};*/
// Level up XP required
QVector<unsigned int> xpStages = QVector<unsigned int>{
        0, 1000, 3000, 6000, 10000, 15000, 21000, 28000, 36000, 45000, 55000,
        66000, 78000, 91000, 105000, 120000, 136000, 153000, 171000, 190000, 0};
// Skill abilities
QVector<Ability> skillAbility = QVector<Ability>{
        Dexterity,
        Strength,
        Charisma,
        Constitution,
        Charisma,
        Dexterity,
        Strength,
        Intelligence,
        Intelligence,
        Intelligence,
        Intelligence,
        Intelligence,
        Intelligence,
        Intelligence,
        Intelligence,
        Wisdom,
        Charisma,
        Dexterity,
        Dexterity,
        Dexterity,
        Wisdom,
        Strength,
        Wisdom,
        Intelligence,
        Charisma};
// =========================================================================
#endif // PREGEN_H
