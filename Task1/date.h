#ifndef DATE_H
#define DATE_H

#include <QString>
#include <QStringList>
#include <ctime>

class Date
{
private:
    int day = 1;
    int month = 1;
    int year = 1900;
    bool isCorrect = 1;


public:
    Date();
    Date(QString str);
    Date(int day, int month, int year);
    bool IsCorrect() { return isCorrect; }
    bool CheckDate(Date *date);

    int Day() { return day; }
    int Month() { return month; }
    int Year() { return year; }
    void addDays(int days);
    void subDays(int days);
    QString getString();
    int getDays();
    static Date Now();

    Date NextDay();
    Date PreviousDay();
    bool IsLeap();
    int Duration (Date date);
    short WeekNumber();
    static int DaysTillYourBithday(Date bithdaydate);
};

#endif // DATE_H
