#include "changedialog.h"

ChangeDialog::ChangeDialog(Student &student, QWidget *parent, Qt::WindowFlags f) : QDialog{parent, f}
{
    connect(this, &ChangeDialog::accepted, this, &ChangeDialog::saving);
    connect(this, &ChangeDialog::applied, this, &ChangeDialog::saving);
    tempStudent = &student;

    QBoxLayout* contentLayout = new QVBoxLayout;
    QGridLayout* editLayout = new QGridLayout;
    surnameLabel = new QLabel("Фамилия");
    surnameEdit = new QLineEdit;
    editLayout->addWidget(surnameLabel, 0, 0);
    editLayout->addWidget(surnameEdit, 0, 1);
    nameLabel = new QLabel("Имя");
    nameEdit = new QLineEdit;
    editLayout->addWidget(nameLabel, 1, 0);
    editLayout->addWidget(nameEdit, 1, 1);
    patronymicLabel = new QLabel("Отчество");
    patronymicEdit = new QLineEdit;
    editLayout->addWidget(patronymicLabel, 2, 0);
    editLayout->addWidget(patronymicEdit, 2, 1);
    groupLabel = new QLabel("Группа");
    groupEdit = new QSpinBox;
    groupEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
    groupEdit->setRange(1, 999999);
    editLayout->addWidget(groupLabel, 3, 0);
    editLayout->addWidget(groupEdit, 3, 1);
    QLabel *averageScore = new QLabel("Средний балл: ");
    editLayout->addWidget(averageScore, 4, 0);
    valueScore = new QLabel("0/0");
    editLayout->addWidget(valueScore, 4, 1);


    QLabel *mathLabel = new QLabel("Математика");
    QHBoxLayout *mathSpin= new QHBoxLayout();
    mathMark1 = new QSpinBox();
    mathMark2 = new QSpinBox();
    mathMark1->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mathMark2->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mathMark1->setRange(0, 10);
    mathMark2->setRange(0, 10);

    mathSpin->addWidget(mathMark1);
    mathSpin->addWidget(mathMark2);

    QLabel *OAIPLabel = new QLabel("ОАИП");
    QHBoxLayout *OAIPSpin= new QHBoxLayout();
    OAIPMark1 = new QSpinBox();
    OAIPMark2 = new QSpinBox();
    OAIPMark1->setButtonSymbols(QAbstractSpinBox::NoButtons);
    OAIPMark2->setButtonSymbols(QAbstractSpinBox::NoButtons);
    OAIPMark1->setRange(0, 10);
    OAIPMark2->setRange(0, 10);
    OAIPSpin->addWidget(OAIPMark1);
    OAIPSpin->addWidget(OAIPMark2);

    QLabel *englishLabel = new QLabel("Английский");
    QHBoxLayout *englishSpin= new QHBoxLayout();
    englishMark1 = new QSpinBox();
    englishMark2 = new QSpinBox();
    englishMark1->setButtonSymbols(QAbstractSpinBox::NoButtons);
    englishMark2->setButtonSymbols(QAbstractSpinBox::NoButtons);
    englishMark1->setRange(0, 10);
    englishMark2->setRange(0, 10);
    englishSpin->addWidget(englishMark1);
    englishSpin->addWidget(englishMark2);

    QLabel *physicsLabel = new QLabel("Физика");
    QHBoxLayout *physicsSpin= new QHBoxLayout();
    physicsMark1 = new QSpinBox();
    physicsMark2 = new QSpinBox();
    physicsMark1->setButtonSymbols(QAbstractSpinBox::NoButtons);
    physicsMark2->setButtonSymbols(QAbstractSpinBox::NoButtons);
    physicsMark1->setRange(0, 10);
    physicsMark2->setRange(0, 10);
    physicsSpin->addWidget(physicsMark1);
    physicsSpin->addWidget(physicsMark2);

    QLabel *belorussianLabel = new QLabel("Белорусский");
    QHBoxLayout *belorussianSpin= new QHBoxLayout();
    belorussianMark1 = new QSpinBox();
    belorussianMark2 = new QSpinBox();
    belorussianMark1->setButtonSymbols(QAbstractSpinBox::NoButtons);
    belorussianMark2->setButtonSymbols(QAbstractSpinBox::NoButtons);
    belorussianMark1->setRange(0, 10);
    belorussianMark2->setRange(0, 10);
    belorussianSpin->addWidget(belorussianMark1);
    belorussianSpin->addWidget(belorussianMark2);

    editLayout->addWidget(mathLabel, 0, 3);
    editLayout->addLayout(mathSpin, 0, 4);
    editLayout->addWidget(OAIPLabel, 1, 3);
    editLayout->addLayout(OAIPSpin, 1, 4);
    editLayout->addWidget(englishLabel, 2, 3);
    editLayout->addLayout(englishSpin, 2, 4);
    editLayout->addWidget(physicsLabel, 3, 3);
    editLayout->addLayout(physicsSpin, 3, 4);
    editLayout->addWidget(belorussianLabel, 4, 3);
    editLayout->addLayout(belorussianSpin, 4, 4);

    QBoxLayout* buttonLayout = new QHBoxLayout;
    QPushButton* okBtn = new QPushButton( "OK" );
    connect( okBtn, SIGNAL( clicked() ), SLOT( accept() ) );
    buttonLayout->addWidget( okBtn );
    QPushButton* applyBtn = new QPushButton( "Apply" );
    connect( applyBtn, SIGNAL( clicked() ), SIGNAL( applied() ) );
    buttonLayout->addWidget( applyBtn);
    QPushButton* cancelBtn = new QPushButton( "Cancel" );
    connect( cancelBtn, SIGNAL( clicked() ), SLOT( reject() ) );
    buttonLayout->addWidget( cancelBtn );

    contentLayout->addLayout(editLayout);
    contentLayout->addLayout(buttonLayout);
    setLayout( contentLayout );

    loadStudent();
}

void ChangeDialog::saving()
{
    if(tempStudent == nullptr)
        tempStudent = new Student(1, "", "", "");
    tempStudent->setFIO(surnameEdit->text(), nameEdit->text(), patronymicEdit->text());
    tempStudent->setGroup(groupEdit->value());
    tempStudent->setMark(1, Student::Math, mathMark1->value());
    tempStudent->setMark(2, Student::Math, mathMark2->value());
    tempStudent->setMark(1, Student::Belorussian, belorussianMark1->value());
    tempStudent->setMark(2, Student::Belorussian, belorussianMark2->value());
    tempStudent->setMark(1, Student::English, englishMark1->value());
    tempStudent->setMark(2, Student::English, englishMark2->value());
    tempStudent->setMark(1, Student::Physics, physicsMark1->value());
    tempStudent->setMark(2, Student::Physics, physicsMark2->value());
    tempStudent->setMark(1, Student::OAIP, OAIPMark1->value());
    tempStudent->setMark(2, Student::OAIP, OAIPMark2->value());
}

void ChangeDialog::loadStudent()
{
    if(tempStudent == nullptr)
        return;
    surnameEdit->setText(tempStudent->surname());
    nameEdit->setText(tempStudent->name());
    patronymicEdit->setText(tempStudent->patronymic());
    groupEdit->setValue(tempStudent->group());
    valueScore->setText(QString::number(tempStudent->averageScore1(), 'g', 2)
                        + "/" + QString::number(tempStudent->averageScore2(), 'g', 2));
    mathMark1->setValue(tempStudent->getMark(1, Student::Math));
    mathMark2->setValue(tempStudent->getMark(2, Student::Math));
    OAIPMark1->setValue(tempStudent->getMark(1, Student::OAIP));
    OAIPMark2->setValue(tempStudent->getMark(2, Student::OAIP));
    englishMark1->setValue(tempStudent->getMark(1, Student::English));
    englishMark2->setValue(tempStudent->getMark(2, Student::English));
    physicsMark1->setValue(tempStudent->getMark(1, Student::Physics));
    physicsMark2->setValue(tempStudent->getMark(2, Student::Physics));
    belorussianMark1->setValue(tempStudent->getMark(1, Student::Belorussian));
    belorussianMark2->setValue(tempStudent->getMark(2, Student::Belorussian));
}
