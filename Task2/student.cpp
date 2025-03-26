#include "student.h"

Student::Student(int group, QString surname, QString name, QString patronymic)
{
    setGroup(group);
    setFIO(surname, name, patronymic);
    marks1 = new int[5]{};
    marks2 = new int[5]{};
}

qreal Student::averageScore1()
{
    qreal sum = 0;
    for(int i = 0; i < 5; i++)
        sum += marks1[i];
    return sum / 5;
}

qreal Student::averageScore2()
{
    qreal sum = 0;
    for(int i = 0; i < 5; i++)
        sum += marks2[i];
    return sum / 5;
}

int Student::getMark(int semester, subjects sub)
{
    if(semester == 1)
    {
        return marks1[sub];
    }
    else if(semester == 2)
    {
        return marks2[sub];
    }
    else
    {
        return -1;
    }
}

int *Student::getMarks(int semester)
{
    if(semester == 1)
    {
        return marks1;
    }
    else if(semester == 2)
    {
        return marks2;
    }
    else
    {
        return nullptr;
    }
}

void Student::setMark(int semester, subjects sub, int mark)
{
    if(mark < 0 || mark > 10)
        return;

    if(semester == 1)
    {
        marks1[sub] = mark;
    }
    else if(semester == 2)
    {
        marks2[sub] = mark;
    }
    else
    {
        return;
    }
}
