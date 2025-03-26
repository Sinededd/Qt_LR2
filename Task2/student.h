#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{
public:
    enum subjects {Math, OAIP, English, Physics, Belorussian};

    Student(int group, QString surname, QString name, QString patronymic);

    int group() { return myGroup; }
    QString surname() { return mySurname; }
    QString name() { return myName; }
    QString patronymic() { return myPatronymic; }
    QString FIO() { return mySurname + myName + myPatronymic; }
    qreal averageScore1();
    qreal averageScore2();
    int getMark(int semester, subjects sub);
    int* getMarks(int semester);

    void setGroup(int group) { myGroup = group; }
    void setSurname(QString surname) { mySurname = surname; }
    void setName(QString name) { myName = name; }
    void setPatronymic(QString patronymic) { myPatronymic = patronymic; }
    void setFIO(QString surname, QString name, QString patronymic)
    { mySurname = surname; myName = name; myPatronymic = patronymic; }
    void setMark(int semester, subjects sub, int mark);

private:
    int myGroup;
    QString mySurname;
    QString myName;
    QString myPatronymic;
    int *marks1;
    int *marks2;
};

#endif // STUDENT_H
