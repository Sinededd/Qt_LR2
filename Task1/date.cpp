#include "date.h"
#include <QDebug>

Date::Date() {
    day = 1;
    month = 1;
    year = 1;
    isCorrect = 1;
}

Date::Date(QString str)
{
    isCorrect = 1;
    QStringList numList = str.split(".");
    bool success;
    if(numList.size() != 3)
    {
        isCorrect = 0;
        return;
    }
    day = numList[0].toInt(&success);
    if(!success)
    {
        isCorrect = 0;
        day = 1;
        return;
    }
    month = numList[1].toInt(&success);
    if(!success)
    {
        isCorrect = 0;
        month = 1;
        return;
    }
    year = numList[2].toInt(&success);
    if(!success)
    {
        isCorrect = 0;
        year = 1;
        return;
    }

    if(!CheckDate(this))
    {
        isCorrect = 0;
        day = 1;
        month = 1;
        year = 1;
        return;
    }
}

Date::Date(int day, int month, int year)
{
    isCorrect = 1;
    this->day = day;
    this->month = month;
    this->year = year;
    if(!CheckDate(this))
    {
        isCorrect = 0;
        this->day = 1;
        this->month = 1;
        this->year = 1;
        return;
    }
}

bool Date::CheckDate(Date *date)
{
    if(date->month < 1 || date->month > 12 || date->day < 1 || date->year < 1)
    {
        return false;
    }
    else
    {
        switch (date->month)
        {
        case 4: case 6: case 9: case 11:
            return (date->day <= 30);
            break;
        case 2:
            if ((this->year % 4 == 0 && this->year % 100 != 0) || this->year % 400 == 0)
            {
                if(date->day > 29)
                    return false;
                else
                    return true;
            }
            else
            {
                if(date->day > 28)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            break;
        default:
            if(date->day > 31)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }


}

void Date::addDays(int days)
{
    if(this->day < 0)
        return;
    bool fl = 1;
    days += this->day;
    while(fl)
    {
        switch (this->month) {
        case 4: case 6: case 9: case 11:
            days -= 30;
            if(days <= 0)
            {
                days += 30;
                fl = 0;
            }
            break;
        case 2:
            if ((this->year % 4 == 0 && this->year % 100 != 0) || this->year % 400 == 0)
            {
                days -= 29;
                if(days <= 0)
                {
                    days += 29;
                    fl = 0;
                }
            }
            else {
                days -= 28;
                if(days <= 0)
                {
                    days += 28;
                    fl = 0;
                }
            }
            break;
        default:
            days -= 31;
            if(days <= 0)
            {
                days += 31;
                fl = 0;
            }
            break;
        }
        if(fl == 0)
        {
            this->day = days;
        }
        else
        {
            this->month++;
            if(this->month > 12)
            {
                this->month = 1;
                this->year++;
            }
        }
    }
}

void Date::subDays(int days)
{
    if(this->day < 0)
        return;
    this->day -= days;

    while(this->day <= 0)
    {
        this->month--;
        if(this->month == 0)
        {
            this->year--;
            this->month = 12;
        }

        switch (this->month) {
        case 4: case 6: case 9: case 11:
            this->day += 30;
            break;
        case 2:
            if ((this->year % 4 == 0 && this->year % 100 != 0) || this->year % 400 == 0)
            {
                this->day += 29;
            }
            else {
                this->day += 28;
            }
            break;
        default:
                this->day += 31;
            break;
        }
    }
}

QString Date::getString()
{
    QString out;
    if(this->day < 10)
        out += "0";
    out += QString::number(this->day);
    out += ".";
    if(this->month < 10)
        out += "0";
    out += QString::number(this->month);
    out += ".";
    if(this->year < 10)
        out += "0";
    out += QString::number(this->year);

    return out;
}

int Date::getDays()
{
    int curYear = this->year - 1;
    int leapYears = curYear / 4 - curYear / 100 + curYear / 400;
    int daysDate = curYear * 365 + leapYears;
    int daysInMonth[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    daysDate += daysInMonth[this->month - 1];
    if(((this->year % 4 == 0 && this->year % 100 != 0) || this->year % 400 == 0) && this->month > 2)
    {
        daysDate++;
    }
    daysDate += (this->day - 1);
    return daysDate;
}

Date Date::Now()
{
    time_t mytime = time(NULL);
    struct tm *now = localtime(&mytime);
    Date curDate;
    curDate.day = now->tm_mday;
    curDate.month = now->tm_mon + 1;
    curDate.year = now->tm_year + 1900;
    return curDate;
}

Date Date::NextDay()
{
    Date nextDate(*this);
    nextDate.addDays(1);
    return nextDate;
}

Date Date::PreviousDay()
{
    Date nextDate(*this);
    nextDate.subDays(1);
    return nextDate;
}

bool Date::IsLeap()
{
    return ((this->year % 4 == 0 && this->year % 100 != 0) || this->year % 400 == 0) ? 1 : 0;
}

int Date::Duration(Date date)
{
    return qAbs(date.getDays() - this->getDays());
}

short Date::WeekNumber()
{
    return this->getDays() % 7 +1;
}

int Date::DaysTillYourBithday(Date bithdaydate)
{
    bithdaydate.year = Date::Now().year;
    return bithdaydate.Duration(Date::Now());
}
