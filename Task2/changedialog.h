#ifndef CHANGEDIALOG_H
#define CHANGEDIALOG_H

#include "student.h"
#include <QDialog>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>

class ChangeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ChangeDialog(Student &student, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void saving();

signals:
    void applied();

private:
    void loadStudent();

    QLabel *surnameLabel;
    QLineEdit* surnameEdit;
    QLabel *nameLabel;
    QLineEdit* nameEdit;
    QLabel *patronymicLabel;
    QLineEdit* patronymicEdit;
    QLabel *groupLabel;
    QSpinBox* groupEdit;

    QSpinBox *mathMark1;
    QSpinBox *mathMark2;
    QSpinBox *OAIPMark1;
    QSpinBox *OAIPMark2;
    QSpinBox *englishMark1;
    QSpinBox *englishMark2;
    QSpinBox *physicsMark1;
    QSpinBox *physicsMark2;
    QSpinBox *belorussianMark1;
    QSpinBox *belorussianMark2;
    QLabel *valueScore;

    Student *tempStudent;
};

#endif // CHANGEDIALOG_H
