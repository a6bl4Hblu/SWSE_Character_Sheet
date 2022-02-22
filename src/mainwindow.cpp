#include "mainwindow.h"
#include <QtWidgets>
#include <QVector>
#include <QFile>
#include <QJsonDocument>
#include <character.h>
#include <clas.h>
#include <species.h>
#include <pregen.h>
// =========================================================================
// Characters array
QVector<Character *> Chars = QVector<Character *>();
// Current character
Character *ch;

// Spacing for styles
int spacingValueH = 10;
int spacingValueV = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Fonts embedding
    QFontDatabase::addApplicationFont(":/Nedian-Bold.ttf");
    QFontDatabase::addApplicationFont(":/Nedian-Medium.otf");
    QFontDatabase::addApplicationFont(":/Nedian-Light.ttf");
    QFontDatabase::addApplicationFont(":/gothic.ttf");
    //QFontDatabase::addApplicationFont(":/Rotis Regular.ttf");

    // Menu Bar
    QAction *newAction = new QAction("&New");
    QAction *saveAction = new QAction("&Save");
    QAction *saveAsAction = new QAction("Save &As");
    QAction *loadAction = new QAction("&Open");

    QMenu *characterMenu = new QMenu("Character");
    //characterMenu->setFont(QFont("ITC Serif Gothic, 10"));
    characterMenu->addAction(newAction);
    characterMenu->addSeparator();
    characterMenu->addAction(saveAction);
    characterMenu->addAction(saveAsAction);
    characterMenu->addAction(loadAction);

    this->menuBar()->addMenu(characterMenu);
    //this->menuBar()->setFont(QFont("ITC Serif Gothic", 10));


    //QCoreApplication::setAttribute(Qt::AA_UseStyleSheetPropagationInWidgetStyles, true);
    //QApplication::setFont(QFont("Nedian"));
    qApp->setStyleSheet(
                "QTabWidget, QTabWidget * {"
                    "font-family: 'Nedian';"
                    "font-size: 10;}"
                "QMenuBar, QMenu {"
                    "font-family: 'ITC Serif Gothic';"
                    "font-size: 10;}"
                //"QMenu {"
                    //"font-family: 'ITC Serif Gothic';}"
                "QGroupBox {"
                    "font-weight: bold;"
                    "border: 1px solid gray;"
                    "border-radius: 3px;"
                    "margin: 10px;"
                    "padding: 4px;}"
                "QGroupBox::title {"
                    "subcontrol-origin: margin;"
                    "subcontrol-position: top left;"
                    "border: 1px solid gray;"
                    "border-radius: 3px;"
                    "color: white;"
                    "background-color: black;"
                    "padding: 4px;"
                    "left: 20px;}");
    // Main Tab Widget
    QTabWidget *mainTabs = new QTabWidget();
    //mainTabs->setFont(QFont("Nedian", 10));
    mainTabs->setTabsClosable(true);
    this->setCentralWidget(mainTabs);

    connect(mainTabs, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(mainTabs, &QTabWidget::tabBarDoubleClicked, this, &MainWindow::closeTab);

    connect(saveAction, &QAction::triggered, this, [=](){MainWindow::saveAction_triggered(mainTabs->currentIndex());});
    connect(saveAsAction, &QAction::triggered, this, [=](){MainWindow::saveAsAction_triggered(mainTabs->currentIndex());});
    connect(newAction, &QAction::triggered,
            this, [=](){addAction_triggered(false);});
    connect(loadAction, &QAction::triggered,
            this, [=](){addAction_triggered(true);});
}

MainWindow::~MainWindow()
{
    for(char i = 0; i < Chars.size(); i++)
        delete Chars.value(i);
    for(char i = 0; i < clases.size(); i++)
        delete clases.value(i);
    for(char i = 0; i < specieses.size(); i++)
        delete specieses.value(i);
}
// =========================================================================
void MainWindow::addAction_triggered(bool opened)
{
    QString fileName;
    QJsonObject json;
    if(opened)
    {
        try {
            fileName = QFileDialog::getOpenFileName(this, "Open Character");
            if(fileName.isEmpty())
                return;
            QFile file(fileName);
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QString data = file.readAll();
            json = QJsonDocument::fromJson(data.toUtf8()).object();
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("Something went wrong with opening file");
            error->exec();
            return;
        }
    }
// =========================================================================
    int numChar = Chars.size();
    Chars.append(new Character());
    ch = Chars.at(numChar);
    // temp variables
    QString qs;
    QLabel *ql;
    QLineEdit *qleTemp;
    QCheckBox *qchkbTemp;
// =========================================================================
    // Main Traits
    // Names
    QLineEdit *player = new QLineEdit();
    QLineEdit *name = new QLineEdit();
    // Species-Size-Class-Level
    QComboBox *species = new QComboBox();
    QComboBox *size = new QComboBox();
    QComboBox *clas = new QComboBox();
    QSpinBox *level = new QSpinBox();
    // XP
    QProgressBar *xpBar = new QProgressBar();
    QLineEdit *xp = new QLineEdit("0");
    QLineEdit *xpAdd = new QLineEdit("0");
    QPushButton *xpAddButton = new QPushButton("+");
// =========================================================================
    // Species Traits
    QLabel *specTraits = new QLabel;
    // Base Attack
    QLabel *baseAttack = new QLabel("+1");
    // Speed
    QLineEdit *speed = new QLineEdit("6");
    // Force Points
    QLineEdit *forcePoints = new QLineEdit("0");
// =========================================================================
    // Bio Traits
    QComboBox *gender = new QComboBox();
    QLineEdit *age = new QLineEdit("20");
    QLineEdit *height = new QLineEdit("180");
    QLineEdit *weight = new QLineEdit("80");
// =========================================================================
    // Abilities
    QVector<QLabel *> absLabels = QVector<QLabel *>(LastAbility+1);
    QVector<QLineEdit *> absScr = QVector<QLineEdit *>(LastAbility+1);
    QVector<QLabel *> absMod = QVector<QLabel *>(LastAbility+1);
// =========================================================================
    // Skills
    QVector<QLabel *> sksScr = QVector<QLabel *>(LastSkill+1);
    QVector<QCheckBox *> sksClass = QVector<QCheckBox *>(LastSkill+1);
    QVector<QCheckBox *> sksTrain = QVector<QCheckBox *>(LastSkill+1);
    QVector<QCheckBox *> sksFocus = QVector<QCheckBox *>(LastSkill+1);
    QVector<QLineEdit *> sksMisc = QVector<QLineEdit *>(LastSkill+1);
// =========================================================================
    // Healthcare
    QLabel *hitDice = new QLabel((QString::number(clases.at(Jedi)->getHitDice())));
    QLabel *startHP = new QLabel(QString::number(clases.at(Jedi)->getStartHP()));
    QLineEdit *currentHP = new QLineEdit("0");
    QLineEdit *maxHP = new QLineEdit("0");
    QLabel *dmgThreshold = new QLabel("11");
    QLineEdit *dmgThresholdMisc = new QLineEdit("0");
    QComboBox *condition = new QComboBox;
    QLineEdit *dmgReduction = new QLineEdit("0");
    QLineEdit *shieldRating = new QLineEdit("0");
// =========================================================================
    // Defences
    // Fortitude
    QLabel *fortitude = new QLabel("11");
    QLineEdit *fortArmor = new QLineEdit("0");
    QLineEdit *fortMisc = new QLineEdit("0");
    //Reflex
    QLabel *reflex= new QLabel("11");
    QLineEdit *reflArmor = new QLineEdit("0");
    QLineEdit *reflMisc = new QLineEdit("0");
    // Will
    QLabel *will = new QLabel("11");
    QLineEdit *willArmor = new QLineEdit("0");
    QLineEdit *willMisc = new QLineEdit("0");
// =========================================================================
    // Inventory
    // Credits
    QLineEdit *credits = new QLineEdit("0");
    QLineEdit *creditsAdd = new QLineEdit("0");
    QPushButton *creditsAddButton = new QPushButton("+");
    // Armor
    QComboBox *armorType = new QComboBox;
    QLineEdit *armor = new QLineEdit;
    QLineEdit *armorRefBonus = new QLineEdit;
    QLineEdit *armorFortBonus = new QLineEdit;
    QLineEdit *armorMaxDexBonus = new QLineEdit;
    QLineEdit *armorCost = new QLineEdit;
    QComboBox *armorAvailability = new QComboBox;
    QLineEdit *armorNotes = new QLineEdit;
    // Weapons
    QVector<QComboBox *> weaponGr(4);
    QVector<QComboBox *> weaponSize(4);
    QVector<QLineEdit *> weaponName(4);
    QVector<QLineEdit *> weaponDmg(4);
    QVector<QCheckBox *> weaponStunDmg(4);
    QVector<QLineEdit *> weaponRof(4);
    QVector<QLineEdit *> weaponType(4);
    QVector<QLineEdit *> weaponCost(4);
    QVector<QComboBox *> weaponAvailability(4);
    QVector<QLineEdit *> weaponNotes(4);
    // Equipments
    QTextEdit *equipments = new QTextEdit;
// =========================================================================
    //QPushButton *featAdd = new QPushButton("+");
    QTextEdit *feats = new QTextEdit;
    //QPushButton *talentAdd = new QPushButton("+");
    QTextEdit *talents= new QTextEdit;
    QTextEdit *languages = new QTextEdit;
    QTextEdit *notes = new QTextEdit;
    QTextEdit *story = new QTextEdit("A long time ago, in a galaxy far far away...");
// =========================================================================
// =========================================================================
    // Player name text line
    QHBoxLayout *playerLayout = new QHBoxLayout();
    playerLayout->addWidget(new QLabel("Player"));
    playerLayout->addWidget(player);
    playerLayout->setSpacing(spacingValueH);
    connect(player, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setPlayer(qs);
    });
    // Character name text line
    QHBoxLayout *nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("Character"));
    nameLayout->addWidget(name);
    nameLayout->setSpacing(spacingValueH);
    connect(name, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setName(qs);
    });
// =========================================================================
    // Skills
    QGridLayout *sksLayout = new QGridLayout;
    sksLayout->setHorizontalSpacing(spacingValueH);
    sksLayout->setVerticalSpacing(spacingValueV);
    ql = new QLabel("T");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    sksLayout->addWidget(ql, 0, 2);
    ql = new QLabel("F");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    sksLayout->addWidget(ql, 0, 3);
    ql = new QLabel("Misc");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    sksLayout->addWidget(ql, 0, 4);
    ql = new QLabel("C");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    sksLayout->addWidget(ql, 0, 5);
    for(char i = FirstSkill; i <= LastSkill; i++)
    {
        sksScr.replace(i, new QLabel("0"));
        qs = abilityNameText.at(skillAbility.at(i));
        qs.append(" mod + Half Level + Misc + (?Trained)5 + (?Focus)5");
        sksScr.at(i)->setToolTip(qs);
        sksTrain.replace(i, new QCheckBox());
        qchkbTemp = sksTrain.at(i);
        connect(qchkbTemp, &QCheckBox::stateChanged,
                this, [=](int chk){ ch->setSkillTrain((Skill)i, chk, &skillAbility);
                                    sksScr.at(i)->setText(QString::number(ch->getSkillScore((Skill)i)));
        });
        sksFocus.replace(i, new QCheckBox());
        qchkbTemp = sksFocus.at(i);
        connect(qchkbTemp, &QCheckBox::stateChanged,
                this, [=](int chk){ ch->setSkillFocus((Skill)i, chk, &skillAbility);
                                    sksScr.at(i)->setText(QString::number(ch->getSkillScore((Skill)i)));
        });
        sksClass.replace(i, new QCheckBox());
        qchkbTemp = sksClass.at(i);
        connect(qchkbTemp, &QCheckBox::stateChanged,
                this, [=](int chk){ ch->setSkillClass((Skill)i, chk);
        });
        sksMisc.replace(i, new QLineEdit("0"));
        qleTemp = sksMisc.at(i);
        qleTemp->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        connect(qleTemp, &QLineEdit::textChanged,
                this, [=](QString qs){  ch->setSkillMisc((Skill)i, qs.toInt(), &skillAbility);
                                        sksScr.at(i)->setText(QString::number(ch->getSkillScore((Skill)i)));
        });
        sksLayout->addWidget(new QLabel(skillNameText.at(i)), i+1, 0);
        sksLayout->addWidget(sksScr.at(i), i+1, 1);
        sksLayout->addWidget(sksTrain.at(i), i+1, 2);
        sksLayout->addWidget(sksFocus.at(i), i+1, 3);
        sksLayout->addWidget(sksMisc.at(i), i+1, 4);
        sksLayout->addWidget(sksClass.at(i), i+1, 5);
    }
    // Skills box
    QGroupBox *sksGroup = new QGroupBox("Skills");
    sksGroup->setLayout(sksLayout);
// =========================================================================
    // Abilities
    QGridLayout *absLayout = new QGridLayout;
    absLayout->setHorizontalSpacing(spacingValueH);
    absLayout->setVerticalSpacing(spacingValueV);
    for(char i = FirstAbility; i <= LastAbility; i++)
    {
        absLabels.replace(i, new QLabel(abilityNameText.at(i)));
        absMod.replace(i, new QLabel("0"));
        absScr.replace(i, new QLineEdit("10"));
        qleTemp = absScr.at(i);
        qleTemp->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        connect(qleTemp, &QLineEdit::textChanged,
                this, [=](QString qs){  Ability numAb = (Ability)i;

                                        ch->setAbilityScore(numAb, qs.toInt(), &(clases.at(ch->getClas())->getDefenceBonus()), &skillAbility);
                                        char mod = ch->getAbilityMod(numAb);

                                        QString str = QString::number(mod);
                                        if(mod > 0)
                                            str.prepend("+");
                                        absMod.value(i)->setText(str);
                                        for(int i = FirstSkill; i <= LastSkill; i++)
                                            if(skillAbility.at(i) == numAb)
                                                sksScr.at(i)->setText(QString::number(ch->getSkillScore((Skill)i)));
        });
        absLayout->addWidget(absLabels.at(i), i, 0);
        absLayout->addWidget(absScr.at(i), i, 1);
        absLayout->addWidget(absMod.at(i), i, 2);
    }
    // Abilities box
    QGroupBox *absGroup = new QGroupBox("Abilities");
    absGroup->setLayout(absLayout);
// =========================================================================
    // Clas combo box
    clas->addItems(QStringList(QList<QString>(clasNameText.begin(), clasNameText.end())));
    // Level spin box
    level->setRange(1, 20);
    level->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    // Clas-Level
    QHBoxLayout *clasLevelLayout = new QHBoxLayout();
    clasLevelLayout->addWidget(new QLabel("Class"));
    clasLevelLayout->addWidget(clas);
    clasLevelLayout->addWidget(new QLabel("Level"));
    clasLevelLayout->addWidget(level);
    clasLevelLayout->setSpacing(spacingValueH);
    connect(clas, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [=](int i){   ch->setClas((ClasName)i);
                                Clas *clas = clases.at(i);
                                baseAttack->setText(QString("+").append(QString::number(clas->getBaseAttack().at(ch->getLevel()-1))));
                                hitDice->setText(QString::number(clas->getHitDice()));
                                startHP->setText(QString::number(clas->getStartHP()));
                                QVector<char> temp = clases.at(i)->getDefenceBonus();
                                ch->updDefenceScore(Fortitude, temp.at(Fortitude));
                                ch->updDefenceScore(Reflex, temp.at(Reflex));
                                ch->updDefenceScore(Will, temp.at(Will));
                                fortitude->setText(QString::number(ch->getDefenceScore(Fortitude)));
                                reflex->setText(QString::number(ch->getDefenceScore(Reflex)));
                                will->setText(QString::number(ch->getDefenceScore(Will)));
                                ch->updDmgThreshold();
                                dmgThreshold->setText(QString::number(ch->getDmgThreshold()));
    });
    connect(level, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [=](unsigned char i){ ch->setLevel(i);
                                        baseAttack->setText(QString("+").append(QString::number(clases.at(ch->getClas())->getBaseAttack().at(i-1))));
                                        xpBar->setMaximum(xpStages.at(i));
                                        xpBar->setFormat(QString("%v/%m"));
                                        for(int i = FirstSkill; i <= LastSkill; i++)
                                        {
                                            ch->updSkillScore((Skill)i, &skillAbility);
                                            sksScr.at(i)->setText(QString::number(ch->getSkillScore((Skill)i)));
                                        }
    });
    // Species combo box
    species->addItems(QStringList(QList<QString>(speciesNameText.begin(), speciesNameText.end())));
    connect(species, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [=](int i){   ch->setSpecies((SpeciesName)i);
                                QString qs = QString(specieses.at(i)->getDescription()).append("\n\n\n");
                                QVector<QString> temp = specieses.at(i)->getTraits();
                                for(char i = 0; i < temp.size(); i++)
                                    qs.append(temp.at(i)).append("\n\n");
                                specTraits->setText(qs);
    });
    // Size combo box
    size->addItems(QStringList(QList<QString>(sizeNameText.begin(), sizeNameText.end())));
    size->setCurrentIndex(Medium);
    connect(size, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [=](int i){   ch->setSize((Size)i);
    });
    // Species-Size
    QHBoxLayout *speciesSizeLayout = new QHBoxLayout;
    speciesSizeLayout->addWidget(new QLabel("Species"));
    speciesSizeLayout->addWidget(species);
    speciesSizeLayout->addWidget(new QLabel("Size"));
    speciesSizeLayout->addWidget(size);
    speciesSizeLayout->setSpacing(spacingValueH);
    // BAB-FP
    QHBoxLayout *babFpLayout = new QHBoxLayout;
    babFpLayout->addWidget(new QLabel("Base Attack"));
    babFpLayout->addWidget(baseAttack);
    babFpLayout->addWidget(new QLabel("Force Points"));
    babFpLayout->addWidget(forcePoints);
    babFpLayout->setSpacing(spacingValueH);
    forcePoints->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(forcePoints, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setForcePoints(qs);
    });
    // Main Traits box
    QVBoxLayout *mainTraitsLayout = new QVBoxLayout();
    mainTraitsLayout->addLayout(playerLayout);
    mainTraitsLayout->addLayout(nameLayout);
    mainTraitsLayout->addLayout(clasLevelLayout);
    mainTraitsLayout->addLayout(speciesSizeLayout);
    mainTraitsLayout->addLayout(babFpLayout);
    mainTraitsLayout->setSpacing(spacingValueV);
    QGroupBox *mainTraitsGroup = new QGroupBox("General Information");
    mainTraitsGroup->setLayout(mainTraitsLayout);
// =========================================================================
    // Species Traits box
    QVector<QString> humanTraits = specieses.at(Human)->getTraits();
    QHBoxLayout *specTraitsLayout = new QHBoxLayout;
    qs = specieses.at(Human)->getDescription();
    qs.append("\n\n");
    for(char i = 0; i < humanTraits.size(); i++)
        qs.append(humanTraits.at(i)).append("\n\n");
    specTraits->setText(qs);
    specTraits->setWordWrap(true);
    specTraitsLayout->addWidget(specTraits);
    QGroupBox *specTraitsGroup = new QGroupBox("Species Traits");
    specTraitsGroup->setLayout(specTraitsLayout);
// =========================================================================
    // XP text line and progress bar
    xpBar->setRange(0, 1000);
    xpBar->setValue(0);
    xpBar->setFormat("%v/1000");
    xp->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    xpAdd->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(xp, &QLineEdit::textChanged,
            this, [=](QString qs){  unsigned int temp = qs.toInt();
                                    ch->setXp(temp);
                                    xpBar->setValue(temp);
    });
    connect(xpAddButton, &QPushButton::released,
            this, [=](){    xp->setText(QString::number(ch->getXp() + xpAdd->text().toInt()));
    });
    // XP box
    QGridLayout *xpLayout = new QGridLayout;
    xpLayout->addWidget(xp, 0, 0, 1, 2);
    xpLayout->addWidget(xpBar, 1, 0, 1, 2);
    xpLayout->addWidget(xpAdd, 2, 0);
    xpLayout->addWidget(xpAddButton, 2, 1);
    xpLayout->setHorizontalSpacing(spacingValueH);
    xpLayout->setVerticalSpacing(spacingValueV);
    QGroupBox *xpGroup = new QGroupBox("XP");
    xpGroup->setLayout(xpLayout);
// =========================================================================
    // Bio Traits
    // Gender combo box
    gender->addItems(QStringList(QList<QString>(genderNameText.begin(), genderNameText.end())));
    gender->setCurrentIndex(U);
    connect(gender, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [=](int i){   ch->setGender((Gender)i);
    });
    // Age text line
    age->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(age, &QLineEdit::textChanged,
            this, [=](QString qs){   ch->setAge(qs);
    });
    // Height text line
    height->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(height, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setHeight(qs);
    });
    // Weight text line
    weight->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(weight, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setWeight(qs);
    });
    // Speed text line
    speed->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(speed, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setSpeed(qs);
    });
    QGridLayout *bioTraitsLayout = new QGridLayout;
    bioTraitsLayout->addWidget(new QLabel("Gender"), 0, 0);
    bioTraitsLayout->addWidget(gender, 0, 1);
    bioTraitsLayout->addWidget(new QLabel("Age"), 1, 0);
    bioTraitsLayout->addWidget(age, 1, 1);
    bioTraitsLayout->addWidget(new QLabel("Height"), 2, 0);
    bioTraitsLayout->addWidget(height, 2, 1);
    bioTraitsLayout->addWidget(new QLabel("Weight"), 3, 0);
    bioTraitsLayout->addWidget(weight, 3, 1);
    bioTraitsLayout->addWidget(new QLabel("Speed"), 4, 0);
    bioTraitsLayout->addWidget(speed, 4, 1);
    bioTraitsLayout->setHorizontalSpacing(spacingValueH);
    bioTraitsLayout->setVerticalSpacing(spacingValueV);
    QGroupBox *bioTraitsGroup = new QGroupBox("Biometrics");
    bioTraitsGroup->setLayout(bioTraitsLayout);
// =========================================================================
    // Healthcare
    // Current HP text line
    currentHP->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(currentHP, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setCurrentHP(qs); // add big skull, if hp < dmgThreshold
    });
    // Max HP text line
    maxHP->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(maxHP, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setMaxHP(qs);
    });
    // Damage Threshold text lines
    dmgThreshold->setToolTip("Fortitude + Misc");
    dmgThresholdMisc->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(dmgThresholdMisc, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setDmgThresholdMisc(qs.toInt());
                                    dmgThreshold->setText(QString::number(ch->getDmgThreshold()));
    });
    // Condition combo box
    condition->addItems(QStringList(QList<QString>(conditionNameText.begin(), conditionNameText.end())));
    connect(condition, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [=](int i){   ch->setCondition((Condition)i);
    });
    // Healthcare Box
    QVBoxLayout *hpLayout = new QVBoxLayout();
    QHBoxLayout *hpRow1 = new QHBoxLayout;
    hpRow1->addWidget(new QLabel("HP"));
    hpRow1->addWidget(currentHP);
    hpRow1->addWidget(new QLabel("/"));
    hpRow1->addWidget(maxHP);
    hpRow1->setSpacing(spacingValueH);
    QHBoxLayout *hpRow2 = new QHBoxLayout;
    hpRow2->addWidget(new QLabel("Start"));
    hpRow2->addWidget(startHP);
    hpRow2->addWidget(new QLabel("HitDice"));
    hpRow2->addWidget(hitDice);
    hpRow2->setSpacing(spacingValueH);
    QHBoxLayout *hpRow3 = new QHBoxLayout;
    hpRow3->addWidget(new QLabel("Threshold"));
    hpRow3->addWidget(dmgThreshold);
    hpRow3->addWidget(dmgThresholdMisc);
    hpRow3->setSpacing(spacingValueH);
    QHBoxLayout *hpRow4 = new QHBoxLayout;
    hpRow4->addWidget(new QLabel("Condition"));
    hpRow4->addWidget(condition);
    hpRow4->setSpacing(spacingValueH);
    QHBoxLayout *hpRow5 = new QHBoxLayout;
    hpRow5->addWidget(new QLabel("DR"));
    hpRow5->addWidget(dmgReduction);
    hpRow5->addWidget(new QLabel("Shield"));
    hpRow5->addWidget(shieldRating);
    hpRow5->setSpacing(spacingValueH);
    hpLayout->addLayout(hpRow1);
    hpLayout->addLayout(hpRow2);
    hpLayout->addLayout(hpRow3);
    hpLayout->addLayout(hpRow4);
    hpLayout->addLayout(hpRow5);
    hpLayout->setSpacing(spacingValueV);
    QGroupBox *hpGroup = new QGroupBox("Healthcare");
    hpGroup->setLayout(hpLayout);
// =========================================================================
    // Defences
    // Fortitude text lines
    fortitude->setToolTip("10 + Constitution mod + Class mod + Fortitude + Misc");
    connect(fortitude, &QLabel::windowIconTextChanged,
            this, [=](QString){dmgThreshold->setText(QString::number(ch->getDmgThreshold()));
    });
    fortArmor->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(fortArmor, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setDefenceArmor(Fortitude, (char)qs.toInt(), clases.at(ch->getClas())->getDefenceBonus().at(Fortitude));
                                    fortitude->setText(QString::number(ch->getDefenceScore(Fortitude)));
                                    dmgThreshold->setText(QString::number(ch->getDmgThreshold()));
    });
    fortMisc->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(fortMisc, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setDefenceMisc(Fortitude, (char)qs.toInt(), clases.at(ch->getClas())->getDefenceBonus().at(Fortitude));
                                    fortitude->setText(QString::number(ch->getDefenceScore(Fortitude)));
                                    dmgThreshold->setText(QString::number(ch->getDmgThreshold()));
    });
    // Reflex text lines
    reflex->setToolTip("10 + Dexterity mod + Class mod + Fortitude + Misc");
    reflArmor->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(reflArmor, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setDefenceArmor(Reflex, (char)qs.toInt(), clases.at(ch->getClas())->getDefenceBonus().at(Reflex));
                                    reflex->setText(QString::number(ch->getDefenceScore(Reflex)));
    });
    reflMisc->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(reflMisc, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setDefenceMisc(Reflex, (char)qs.toInt(), clases.at(ch->getClas())->getDefenceBonus().at(Reflex));
                                    reflex->setText(QString::number(ch->getDefenceScore(Reflex)));
    });
    // Will text lines
    will->setToolTip("10 + Wisdom mod + Class mod + Fortitude + Misc");
    willArmor->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(willArmor, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setDefenceArmor(Will, (char)qs.toInt(), clases.at(ch->getClas())->getDefenceBonus().at(Will));
                                    will->setText(QString::number(ch->getDefenceScore(Will)));
    });
    willMisc->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(willMisc, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setDefenceMisc(Will, (char)qs.toInt(), clases.at(ch->getClas())->getDefenceBonus().at(Will));
                                    will->setText(QString::number(ch->getDefenceScore(Will)));
    });
    // Defences box
    QGridLayout *defenceLayout = new QGridLayout;
    ql = new QLabel("Armor/Level");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    defenceLayout->addWidget(ql, 0, 2);
    ql = new QLabel("Misc");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    defenceLayout->addWidget(ql, 0, 3);
    defenceLayout->addWidget(new QLabel("Fortitude"), 1, 0);
    defenceLayout->addWidget(fortitude, 1, 1);
    defenceLayout->addWidget(fortArmor, 1, 2);
    defenceLayout->addWidget(fortMisc, 1, 3);
    defenceLayout->addWidget(new QLabel("Reflex"), 2, 0);
    defenceLayout->addWidget(reflex, 2, 1);
    defenceLayout->addWidget(reflArmor, 2, 2);
    defenceLayout->addWidget(reflMisc, 2, 3);
    defenceLayout->addWidget(new QLabel("Will"), 3, 0);
    defenceLayout->addWidget(will, 3, 1);
    defenceLayout->addWidget(willArmor, 3, 2);
    defenceLayout->addWidget(willMisc, 3, 3);
    defenceLayout->setHorizontalSpacing(spacingValueH);
    defenceLayout->setVerticalSpacing(spacingValueV);
    QGroupBox *defenceGroup = new QGroupBox("Defences");
    defenceGroup->setLayout(defenceLayout);
// =========================================================================
    // Inventory
    // Credits
    credits->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    creditsAdd->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    connect(credits, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->setCredits(qs.toInt());
    });
    connect(creditsAddButton, &QPushButton::released,
            this, [=](){    credits->setText(QString::number(ch->getCredits() + creditsAdd->text().toInt()));
    });
    QGridLayout *creditsLayout= new QGridLayout;
    creditsLayout->addWidget(credits, 0, 0, 1, 2);
    creditsLayout->addWidget(creditsAddButton, 1, 0);
    creditsLayout->addWidget(creditsAdd, 1, 1);
    QGroupBox *creditsGroup = new QGroupBox("Credits");
    creditsGroup->setLayout(creditsLayout);
    // Armor
    armorType->addItems(QStringList(QList<QString>(armorTypeNameText.begin(), armorTypeNameText.end())));
    connect(armorType, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [=](int t){   ch->getArmor()->setType((ArmorType)t);
    });
    connect(armor, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->getArmor()->setName(qs);
    });
    connect(armorRefBonus, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->getArmor()->setBonusRefl(qs);
    });
    connect(armorFortBonus, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->getArmor()->setBonusFort(qs);
    });
    connect(armorMaxDexBonus, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->getArmor()->setMaxDex(qs);
    });
    connect(armorCost, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->getArmor()->setCost(qs);
    });
    armorAvailability->addItems(QStringList(QList<QString>(availabilityNameText.begin(), availabilityNameText.end())));
    connect(armorAvailability, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [=](int t){   ch->getArmor()->setAvailability((Availability)t);
    });
    connect(armorNotes, &QLineEdit::textChanged,
            this, [=](QString qs){  ch->getArmor()->setNotes(qs);
    });
    // Armor box
    QGridLayout *armorLayout= new QGridLayout;
    ql = new QLabel("Type");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    armorLayout->addWidget(ql, 0, 0);
    armorLayout->addWidget(armorType, 1, 0);
    ql = new QLabel("Armor");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    armorLayout->addWidget(ql, 0, 1);
    armorLayout->addWidget(armor, 1, 1);
    ql = new QLabel("Ref");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    armorLayout->addWidget(ql, 0, 2);
    armorLayout->addWidget(armorRefBonus, 1, 2);
    ql = new QLabel("Fort");
    /*ql->setStyleSheet("QLabel {"
                      "font: Nedian"
                      "font-size: 6;}");*/
    armorLayout->addWidget(ql, 0, 3);
    armorLayout->addWidget(armorFortBonus, 1, 3);
    ql = new QLabel("Max Dex");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    armorLayout->addWidget(ql, 0, 4);
    armorLayout->addWidget(armorMaxDexBonus, 1, 4);
    ql = new QLabel("Cost");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    armorLayout->addWidget(ql, 0, 5);
    armorLayout->addWidget(armorCost, 1, 5);
    ql = new QLabel("Avail.");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    armorLayout->addWidget(ql, 0, 6);
    armorLayout->addWidget(armorAvailability, 1, 6);
    ql = new QLabel("Notes");
    /*ql->setStyleSheet("QLabel {"
                        "font-family: 'Nedian';"
                        "font-size: 6;"
                        "font-weight: light;}");*/
    armorLayout->addWidget(ql, 2, 0);
    armorLayout->addWidget(armorNotes, 2, 1, 1, 8);
    armorLayout->setHorizontalSpacing(spacingValueH);
    armorLayout->setVerticalSpacing(spacingValueV);
    armorLayout->setColumnStretch(1, 8);
    armorLayout->setColumnStretch(2, 1);
    armorLayout->setColumnStretch(3, 1);
    armorLayout->setColumnStretch(4, 1);
    QGroupBox *armorGroup = new QGroupBox("Armor");
    armorGroup->setLayout(armorLayout);

    // Weapons
    QVBoxLayout *weaponsLayout = new QVBoxLayout;
    for(int i = 0; i < 4; i++)
    {
        weaponGr.replace(i, new QComboBox);
        weaponGr.value(i)->addItems(QStringList(QList<QString>(weaponGroupNameText.begin(), weaponGroupNameText.end())));
        connect(weaponGr.at(i), QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, [=](int t){   ch->getWeapon(i)->setGroup((WeaponGroup)t);
        });
        weaponSize.replace(i, new QComboBox);
        weaponSize.value(i)->addItems(QStringList(QList<QString>(sizeNameText.begin(), sizeNameText.end())));
        connect(weaponSize.at(i), QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, [=](int t){   ch->getWeapon(i)->setSize((Size)t);
        });
        weaponName.replace(i, new QLineEdit);
        connect(weaponName.at(i), &QLineEdit::textChanged,
                this, [=](QString qs){  ch->getWeapon(i)->setName(qs);
        });
        weaponDmg.replace(i, new QLineEdit);
        connect(weaponDmg.at(i), &QLineEdit::textChanged,
                this, [=](QString qs){  ch->getWeapon(i)->setDmg(qs);
        });
        weaponStunDmg.replace(i, new QCheckBox);
        connect(weaponStunDmg.at(i), &QCheckBox::stateChanged,
                this, [=](int chk){   ch->getWeapon(i)->setStunDmg(chk);
        });
        weaponRof.replace(i, new QLineEdit);
        connect(weaponRof.at(i), &QLineEdit::textChanged,
                this, [=](QString qs){  ch->getWeapon(i)->setRof(qs);
        });
        weaponType.replace(i, new QLineEdit);
        connect(weaponType.at(i), &QLineEdit::textChanged,
                this, [=](QString qs){  ch->getWeapon(i)->setType(qs);
        });
        weaponCost.replace(i, new QLineEdit);
        connect(weaponCost.at(i), &QLineEdit::textChanged,
                this, [=](QString qs){  ch->getWeapon(i)->setCost(qs);
        });
        weaponAvailability.replace(i, new QComboBox);
        weaponAvailability.value(i)->addItems(QStringList(QList<QString>(availabilityNameText.begin(), availabilityNameText.end())));
        connect(weaponAvailability.at(i), QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, [=](int t){   ch->getWeapon(i)->setAvailability((Availability)t);
        });
        weaponNotes.replace(i, new QLineEdit);
        connect(weaponNotes.at(i), &QLineEdit::textChanged,
                this, [=](QString qs){  ch->getWeapon(i)->setNotes(qs);
        });

        QGridLayout *weaponLayout = new QGridLayout;
        ql = new QLabel("Group");
        /*ql->setStyleSheet("QLabel {"
                            "font-family: 'Nedian';"
                            "font-size: 6;"
                            "font-weight: light;}");*/
        weaponLayout->addWidget(ql, 0, 0);
        weaponLayout->addWidget(weaponGr.at(i), 1, 0);
        ql = new QLabel("Size");
        /*ql->setStyleSheet("QLabel {"
                            "font-family: 'Nedian';"
                            "font-size: 6;"
                            "font-weight: light;}");*/
        weaponLayout->addWidget(ql, 0, 1);
        weaponLayout->addWidget(weaponSize.at(i), 1, 1);
        ql = new QLabel("Weapon");
        /*ql->setStyleSheet("QLabel {"
                            "font-family: 'Nedian';"
                            "font-size: 6;"
                            "font-weight: light;}");*/
        weaponLayout->addWidget(ql, 0, 2);
        weaponLayout->addWidget(weaponName.at(i), 1, 2);
        ql = new QLabel("Dmg");
        /*ql->setStyleSheet("QLabel {"
                            "font-family: 'Nedian';"
                            "font-size: 6;"
                            "font-weight: light;}");*/
        weaponLayout->addWidget(ql, 0, 3);
        weaponLayout->addWidget(weaponDmg.at(i), 1, 3);
        ql = new QLabel("Stun");
        /*ql->setStyleSheet("QLabel {"
                            "font-family: 'Nedian';"
                            "font-size: 6;"
                            "font-weight: light;}");*/
        weaponLayout->addWidget(ql, 0, 4);
        weaponLayout->addWidget(weaponStunDmg.at(i), 1, 4, Qt::AlignCenter);
        ql = new QLabel("RoF");
        /*ql->setStyleSheet("QLabel {"
                            "font-family: 'Nedian';"
                            "font-size: 6;"
                            "font-weight: light;}");*/
        weaponLayout->addWidget(ql, 0, 5);
        weaponLayout->addWidget(weaponRof.at(i), 1, 5);
        ql = new QLabel("Dmg Type");
        /*ql->setStyleSheet("QLabel {"
                            "font-family: 'Nedian';"
                            "font-size: 6;"
                            "font-weight: light;}");*/
        weaponLayout->addWidget(ql, 0, 6);
        weaponLayout->addWidget(weaponType.at(i), 1, 6);
        ql = new QLabel("Cost");
        /*ql->setStyleSheet("QLabel {"
                            "font-family: 'Nedian';"
                            "font-size: 6;"
                            "font-weight: light;}");*/
        weaponLayout->addWidget(ql, 0, 7);
        weaponLayout->addWidget(weaponCost.at(i), 1, 7);
        ql = new QLabel("Avail.");
        /*ql->setStyleSheet("QLabel {"
                            "font-family: 'Nedian';"
                            "font-size: 6;"
                            "font-weight: light;}");*/
        weaponLayout->addWidget(ql, 0, 8);
        weaponLayout->addWidget(weaponAvailability.at(i), 1, 8);
        weaponLayout->addWidget(new QLabel("Notes"), 2, 0);
        weaponLayout->addWidget(weaponNotes.at(i), 2, 1, 1, 8);
        weaponLayout->setHorizontalSpacing(spacingValueH);
        weaponLayout->setVerticalSpacing(spacingValueV);
        weaponLayout->setColumnStretch(2, 7);
        weaponLayout->setColumnStretch(3, 4);
        weaponLayout->setColumnStretch(5, 1);
        weaponLayout->setColumnStretch(6, 3);

        weaponsLayout->addLayout(weaponLayout);
    }
    weaponsLayout->setSpacing(spacingValueH);


    QGroupBox *weaponsGroup = new QGroupBox("Weapons");
    weaponsGroup->setLayout(weaponsLayout);

    // Equipments
    QVBoxLayout *equipmentLayout = new QVBoxLayout;
    equipmentLayout->addWidget(equipments);
    equipments->setWordWrapMode(QTextOption::WrapMode(QTextEdit::WidgetWidth));
    connect(equipments, &QTextEdit::textChanged,
            this, [=](){    ch->setEquipments(equipments->toPlainText());
    });
    QGroupBox *equipmentGroup = new QGroupBox("Equipment");
    equipmentGroup->setLayout(equipmentLayout);
// =========================================================================
    // Feats
    QVBoxLayout *featLayout = new QVBoxLayout;
    featLayout->addWidget(feats);
    feats->setWordWrapMode(QTextOption::WrapMode(QTextEdit::WidgetWidth));
    connect(feats, &QTextEdit::textChanged,
            this, [=](){    ch->setFeats(feats->toPlainText());
    });
    QGroupBox *featGroup = new QGroupBox("Feats");
    featGroup->setLayout(featLayout);
    // Talents
    QVBoxLayout *talentLayout = new QVBoxLayout;
    talentLayout->addWidget(talents);
    talents->setWordWrapMode(QTextOption::WrapMode(QTextEdit::WidgetWidth));
    connect(talents, &QTextEdit::textChanged,
            this, [=](){    ch->setTalents(talents->toPlainText());
    });
    QGroupBox *talentGroup = new QGroupBox("Talents");
    talentGroup->setLayout(talentLayout);
    // Languages
    QVBoxLayout *languagesLayout = new QVBoxLayout;
    languagesLayout->addWidget(languages);
    //languagesLayout->setSizeConstraint(QLayout::SetMaximumSize);
    connect(languages, &QTextEdit::textChanged,
            this, [=](){    ch->setLanguage(languages->toPlainText());
    });
    QGroupBox *languagesGroup = new QGroupBox("Languages");
    languagesGroup->setLayout(languagesLayout);
    // Notes
    QVBoxLayout *notesLayout = new QVBoxLayout;
    notesLayout->addWidget(notes);
    notes->setWordWrapMode(QTextOption::WrapMode(QTextEdit::WidgetWidth));
    connect(notes, &QTextEdit::textChanged,
            this, [=](){    ch->setNotes(notes->toPlainText());
    });
    QGroupBox *notesGroup = new QGroupBox("Notes");
    notesGroup->setLayout(notesLayout);
    // Story
    story->setWordWrapMode(QTextOption::WrapMode(QTextEdit::WidgetWidth));
    connect(story, &QTextEdit::textChanged,
            this, [=](){    ch->setStory(story->toPlainText());
    });
// =========================================================================
    // General Traits Page Layout
    QHBoxLayout *generalPageRow1 = new QHBoxLayout;
    generalPageRow1->addWidget(mainTraitsGroup);
    generalPageRow1->addWidget(bioTraitsGroup);
    generalPageRow1->addWidget(hpGroup);
    QHBoxLayout *generalPageRow21 = new QHBoxLayout;
    generalPageRow21->addWidget(absGroup);
    QVBoxLayout *generalPageRow22 = new QVBoxLayout;
    generalPageRow22->addWidget(defenceGroup);
    generalPageRow22->addWidget(xpGroup);
    generalPageRow21->addLayout(generalPageRow22);
    generalPageRow21->addWidget(languagesGroup);
    QVBoxLayout *generalPageCol1 = new QVBoxLayout;
    generalPageCol1->addLayout(generalPageRow1);
    generalPageCol1->addLayout(generalPageRow21);
    generalPageCol1->addWidget(specTraitsGroup, 1);
    QHBoxLayout *generalPageCol12 = new QHBoxLayout;
    generalPageCol12->addLayout(generalPageCol1);
    generalPageCol12->addWidget(sksGroup);
    QHBoxLayout *generalPageRow3 = new QHBoxLayout;
    feats->setAcceptRichText(false);
    generalPageRow3->addWidget(featGroup);
    talents->setAcceptRichText(false);
    generalPageRow3->addWidget(talentGroup);
    QVBoxLayout *generalPageLayout = new QVBoxLayout;
    generalPageLayout->addLayout(generalPageCol12);
    generalPageLayout->addLayout(generalPageRow3);
    notes->setAcceptRichText(false);
    generalPageLayout->addWidget(notesGroup);

    QVBoxLayout *equipPageLayout = new QVBoxLayout;
    equipPageLayout->addWidget(armorGroup);
    equipPageLayout->addWidget(weaponsGroup);
    equipments->setAcceptRichText(false);
    equipPageLayout->addWidget(equipmentGroup);
    equipPageLayout->addWidget(creditsGroup);
    // Story Page
    story->setAcceptRichText(false);

    // Toolbox
    QWidget *traitPage = new QWidget;
    traitPage->setLayout(generalPageLayout);
    QWidget *equipPage = new QWidget;
    equipPage->setLayout(equipPageLayout);
    QToolBox *toolbox = new QToolBox;
    toolbox->addItem(traitPage, "Traits");
    toolbox->addItem(equipPage, "Equipment");
    toolbox->addItem(story, "Story");
// =========================================================================
// =========================================================================

    if(opened)
    {
        ch->saveFileName = fileName;

        try {
            player->setText(json["Player"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Player Name\" is not correct");
            error->exec();
            return;
        }
        try {
            name->setText(json["Name"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Character Name\" is not correct");
            error->exec();
            return;
        }

        try {
            species->setCurrentIndex(json["Species"].toInt());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Species\" is not correct");
            error->exec();
            return;
        }
        try {
            size->setCurrentIndex(json["Size"].toInt());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Size\" is not correct");
            error->exec();
            return;
        }
        try {
            clas->setCurrentIndex(json["Clas"].toInt());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Class\" is not correct");
            error->exec();
            return;
        }
        try {
            level->setValue(json["Level"].toInt());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Level\" is not correct");
            error->exec();
            return;
        }

        try {
            gender->setCurrentIndex(json["Gender"].toInt());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Gender\" is not correct");
            error->exec();
            return;
        }
        try {
            age->setText(json["Age"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Age\" is not correct");
            error->exec();
            return;
        }
        try {
            height->setText(json["Height"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Height\" is not correct");
            error->exec();
            return;
        }
        try {
            weight->setText(json["Weight"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Weight\" is not correct");
            error->exec();
            return;
        }
        try {
            speed->setText(json["Speed"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Speed\" is not correct");
            error->exec();
            return;
        }

        QVector<QVariant> jsonVec;
        try {
            jsonVec = json["Ability"].toArray().toVariantList().toVector();
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Abilities\" is not correct");
            error->exec();
            return;
        }
        for(char i = FirstAbility; i <= LastAbility; i++)
            absScr.value(i)->setText(QString::number(jsonVec.at(i).toInt()));
        try {
            jsonVec = json["SkillTrain"].toArray().toVariantList().toVector();
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Skills Train\" is not correct");
            error->exec();
            return;
        }
        for(char i = FirstSkill; i <= LastSkill; i++)
            sksTrain.value(i)->setChecked(jsonVec.at(i).toBool());
        try {
            jsonVec = json["SkillFocus"].toArray().toVariantList().toVector();
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Skills Focus\" is not correct");
            error->exec();
            return;
        }
        for(char i = FirstSkill; i <= LastSkill; i++)
            sksFocus.value(i)->setChecked(jsonVec.at(i).toBool());
        try {
            jsonVec = json["SkillClass"].toArray().toVariantList().toVector();
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Skills Class\" is not correct");
            error->exec();
            return;
        }
        for(char i = FirstSkill; i <= LastSkill; i++)
            sksClass.value(i)->setChecked(jsonVec.at(i).toBool());
        try {
            jsonVec = json["SkillMisc"].toArray().toVariantList().toVector();
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Skills Misc\" is not correct");
            error->exec();
            return;
        }
        for(char i = FirstSkill; i <= LastSkill; i++)
            sksMisc.value(i)->setText(QString::number(jsonVec.at(i).toInt()));

        try {
            maxHP->setText(json["MaxHP"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Maximum HP\" is not correct");
            error->exec();
            return;
        }
        try {
            currentHP->setText(json["CurrentHP"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Current HP\" is not correct");
            error->exec();
            return;
        }
        try {
            dmgThresholdMisc->setText(json["DamageTresholdMisc"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Dmg Threshold Misc\" is not correct");
            error->exec();
            return;
        }

        try {
            jsonVec = json["Defences"].toArray().toVariantList().toVector();
            fortArmor->setText(QString::number(jsonVec.at(0).toInt()));
            reflArmor->setText(QString::number(jsonVec.at(1).toInt()));
            willArmor->setText(QString::number(jsonVec.at(2).toInt()));
            fortMisc->setText(QString::number(jsonVec.at(3).toInt()));
            reflMisc->setText(QString::number(jsonVec.at(4).toInt()));
            willMisc->setText(QString::number(jsonVec.at(5).toInt()));
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Defences\" is not correct");
            error->exec();
            return;
        }

        try {
            xp->setText(QString::number(json["XP"].toInt()));
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"XP\" is not correct");
            error->exec();
            return;
        }

        try {
            languages->setText(json["Languages"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Languages\" is not correct");
            error->exec();
            return;
        }

        try {
            talents->setPlainText(json["Talents"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Talents\" is not correct");
            error->exec();
            return;
        }
        try {
            feats->setPlainText(json["Feats"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Feats\" is not correct");
            error->exec();
            return;
        }
        try {
            notes->setPlainText(json["Notes"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Notes\" is not correct");
            error->exec();
            return;
        }

        try {
            credits->setText(QString::number(json["Credits"].toInt()));
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Credits\" is not correct");
            error->exec();
            return;
        }

        try {
            jsonVec = json["Armor"].toArray().toVariantList().toVector();
            armorAvailability->setCurrentIndex(jsonVec.at(0).toInt());
            armorFortBonus->setText(jsonVec.at(1).toString());
            armorRefBonus->setText(jsonVec.at(2).toString());
            armorCost->setText(jsonVec.at(3).toString());
            armorMaxDexBonus->setText(jsonVec.at(4).toString());
            armor->setText(jsonVec.at(5).toString());
            armorNotes->setText(jsonVec.at(6).toString());
            armorType->setCurrentIndex(jsonVec.at(7).toInt());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Armor\" is not correct");
            error->exec();
            return;
        }

        for(int i = 0; i < 4; i++)
        {
            try {
                QString qs = "Weapon";
                qs.append(QString::number(i));
                jsonVec = json[qs].toArray().toVariantList().toVector();
                weaponAvailability.value(i)->setCurrentIndex(jsonVec.at(0).toInt()); // Availability
                weaponCost.value(i)->setText(jsonVec.at(1).toString()); // Cost
                weaponDmg.value(i)->setText(jsonVec.at(2).toString()); // Dmg
                weaponGr.value(i)->setCurrentIndex(jsonVec.at(3).toInt()); // Group
                weaponName.value(i)->setText(jsonVec.at(4).toString()); // Name
                weaponNotes.value(i)->setText(jsonVec.at(5).toString()); // Notes
                weaponRof.value(i)->setText(jsonVec.at(6).toString()); // RoF
                weaponSize.value(i)->setCurrentIndex(jsonVec.at(7).toInt()); // Size
                weaponStunDmg.value(i)->setText(jsonVec.at(8).toString()); // StunDmg
                weaponType.value(i)->setText(jsonVec.at(9).toString()); // Type
            }  catch (QException &e) {
                QMessageBox *error = new QMessageBox(this);
                error->setText("\"Weapons\" is not correct");
                error->exec();
                return;
            }
        }

        try {
            equipments->setPlainText(json["Equipments"].toString());
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("\"Equipments\" is not correct");
            error->exec();
            return;
        }
    }
    // Central Tabs
    QTabWidget *tabs = (QTabWidget *)this->centralWidget();
    tabs->addTab(toolbox, (opened ? QFileInfo(QFile(ch->saveFileName)).fileName() : "NewCharacter"));
}

void MainWindow::saveAction_triggered(int numChar)
{
    QString str = Chars.at(numChar)->saveFileName;
    if(str.isEmpty())
        saveAsAction_triggered(numChar);
    else
    {
        QFile file(str);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << saveToJson(numChar);
        file.close();
    }
}

void MainWindow::saveAsAction_triggered(int numChar)
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Character");
    if(fileName.isEmpty())
        return;
    else
    {
        try {
            Chars.at(numChar)->saveFileName = fileName;
            QFile file(fileName);
            QFileInfo finfo(file);
            ((QTabWidget *)centralWidget())->tabBar()->setTabText(numChar, finfo.fileName());

            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << saveToJson(numChar);
            file.close();
        }  catch (QException &e) {
            QMessageBox *error = new QMessageBox(this);
            error->setText("Something went wrong with opening file");
            error->exec();
            return;
        }
    }
}

QString MainWindow::saveToJson(int numChar)
{
    Character *ch = Chars.at(numChar);
    QJsonObject record;
    QJsonArray jsonArray;
    QJsonObject jsonObj;

    record.insert("SaveFile", QJsonValue::fromVariant(ch->saveFileName));

    record.insert("Player", QJsonValue::fromVariant(ch->getPlayer()));
    record.insert("Name", QJsonValue::fromVariant(ch->getName()));

    record.insert("Species", QJsonValue::fromVariant(ch->getSpecies()));
    record.insert("Size", QJsonValue::fromVariant(ch->getSize()));
    record.insert("Clas", QJsonValue::fromVariant(ch->getClas()));
    record.insert("Level", QJsonValue::fromVariant(ch->getLevel()));

    record.insert("Gender", QJsonValue::fromVariant(ch->getGender()));
    record.insert("Age", QJsonValue::fromVariant(ch->getAge()));
    record.insert("Height", QJsonValue::fromVariant(ch->getHeight()));
    record.insert("Weight", QJsonValue::fromVariant(ch->getWeight()));
    record.insert("Speed", QJsonValue::fromVariant(ch->getSpeed()));

    for(int i = FirstAbility; i <= LastAbility; i++)
            jsonArray.append(ch->getAbilityScore((Ability)i));
    record.insert("Ability", jsonArray);
    jsonArray = QJsonArray();
    for(int i = FirstSkill; i <= LastSkill; i++)
        jsonArray.append(ch->getSkillTrain((Skill)i));
    record.insert("SkillTrain", jsonArray);
    jsonArray = QJsonArray();
    for(int i = FirstSkill; i <= LastSkill; i++)
        jsonArray.append(ch->getSkillFocus((Skill)i));
    record.insert("SkillFocus", jsonArray);
    jsonArray = QJsonArray();
    for(int i = FirstSkill; i <= LastSkill; i++)
        jsonArray.append(ch->getSkillClass((Skill)i));
    record.insert("SkillClass", jsonArray);
    jsonArray = QJsonArray();
    for(int i = FirstSkill; i <= LastSkill; i++)
        jsonArray.append(ch->getSkillMisc((Skill)i));
    record.insert("SkillMisc", jsonArray);

    record.insert("MaxHP", QJsonValue::fromVariant(ch->getMaxHP()));
    record.insert("CurrentHP", QJsonValue::fromVariant(ch->getCurrentHP()));
    record.insert("DamageTresholdMisc", QJsonValue::fromVariant(ch->getDmgThresholdMisc()));

    jsonArray = QJsonArray();
    jsonArray.append(ch->getDefenceArmor(Fortitude));
    jsonArray.append(ch->getDefenceArmor(Reflex));
    jsonArray.append(ch->getDefenceArmor(Will));
    jsonArray.append(ch->getDefenceMisc(Fortitude));
    jsonArray.append(ch->getDefenceMisc(Reflex));
    jsonArray.append(ch->getDefenceMisc(Will));
    record.insert("Defences", jsonArray);

    record.insert("XP", QJsonValue::fromVariant(ch->getXp()));

    record.insert("Languages", QJsonValue::fromVariant(ch->getLanguage()));

    record.insert("Feats", QJsonValue::fromVariant(ch->getFeats()));
    record.insert("Talents", QJsonValue::fromVariant(ch->getTalents()));
    record.insert("Notes", QJsonValue::fromVariant(ch->getNotes()));

    jsonArray = QJsonArray();
    Armor *arm = ch->getArmor();
    jsonArray.append(arm->getAvailability());
    jsonArray.append(arm->getBonusFort());
    jsonArray.append(arm->getBonusRefl());
    jsonArray.append(arm->getCost());
    jsonArray.append(arm->getMaxDex());
    jsonArray.append(arm->getName());
    jsonArray.append(arm->getNotes());
    jsonArray.append(arm->getType());
    record.insert("Armor", jsonArray);

    for(int i = 0; i < 4; i++)
    {
        jsonArray = QJsonArray();
        Weapon *weap = ch->getWeapon(i);
        jsonArray.append(weap->getAvailability());
        jsonArray.append(weap->getCost());
        jsonArray.append(weap->getDmg());
        jsonArray.append(weap->getGroup());
        jsonArray.append(weap->getName());
        jsonArray.append(weap->getNotes());
        jsonArray.append(weap->getRof());
        jsonArray.append(weap->getSize());
        jsonArray.append(weap->getStunDmg());
        jsonArray.append(weap->getType());
        record.insert(QString("Weapon").append(QString::number(i)), jsonArray);
    }

    record.insert("Equipments", QJsonValue::fromVariant(ch->getEquipments()));

    record.insert("Credits", QJsonValue::fromVariant(ch->getCredits()));

    QJsonDocument doc(record);
    return doc.toJson(QJsonDocument::Indented);
}

void MainWindow::closeTab(int numTab)
{
    QTabWidget *tabs = (QTabWidget *)this->centralWidget();
    QWidget *tab = tabs->widget(numTab);
    QMessageBox *msg = new QMessageBox;
    msg->setText("Do you want to save your character?");
    msg->setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    int ret = msg->exec();
    switch (ret) {
        case QMessageBox::Save :
            saveAction_triggered(numTab);
            break;
        case QMessageBox::Cancel :
            return;
        case QMessageBox::Discard :
            break;
    }
    tabs->removeTab(numTab);
    tab->~QWidget();
    Chars.value(numTab)->~Character();
    Chars.remove(numTab);
}
