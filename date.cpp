#include <iostream>
#include <string>
#include <vector>

const char* monthNames[] = {
        "jan", "feb", "mar", "apr", "may", "jun",
        "jul", "aug", "sep", "oct", "nov", "dec"
};

using namespace std;

class Day{
private:
    unsigned int numDay;
    string month;
};

class Month {
public:
    string monthName;
    vector<int> days;
};

class Date {
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;
    unsigned int curM;

public:
    Date (unsigned int day, unsigned int month,unsigned int year) : day(day), month(month), year(year)
    {
        setDate();
    }

    int checkYear ()
    {
        if(year % 4 == 0 || year % 400 == 0 )
            return 29;
        if(year % 100 == 0 && year % 400 == 0 )
            return 29;
        return 28;
    }

    bool checkMonth () {
        unsigned int months[7] = {1, 3,5,7,8,10,12};
        for(int i=0; i< sizeof(months); ++i)
        {
            if(month == months[i])
                return true;
        }
        return false;       //RETURN 31 DAYS
    };

    void setDate () {
        if (month < 1)
            month = 1;
        if (month > 12)
            month = 12;
        if (checkMonth()) {
            if (day > 31)
                day = 31;
            if (day < 1)
                day = 1;
        }
        else if(month!=2)
        {
            if (day > 30)
                day = 30;
            if (day < 1)
                day = 1;
        }
        else
        {
            if(day>checkYear())
                day=checkYear();
            if(day<1)
                day=1;
        }
    }

    void showDate() const
    {
        cout << day << " " << monthNames[month-1] << " " << year << endl;
    }

    int getMonthDays()
    {
        if(checkMonth())        //RETURN 31 DAYS
        {
            return 31;
        }
        else if(month!=2)       //RETURN 30 DAYS
        {
            return 30;
        }
        return checkYear();     //RETURN 28-29 DAYS
    }


    // overloaded
    int getMonthDays(unsigned int& curMonth)
    {
        curM = curMonth;
        if(checkCurMonth(curM))        //RETURN 31 DAYS
        {
            return 31;
        }
        else if(curM!=2)       //RETURN 30 DAYS
        {
            return 30;
        }
        else
            return checkYear();     //RETURN 28-29 DAYS
    }

    bool checkCurMonth (unsigned int& curMonth)  {
        curM = curMonth;
        unsigned int months[7] = {1, 3,5,7,8,10,12};
        for(int i=0; i< sizeof(months); ++i)
        {
            if(curM == months[i])
                return true;
        }
        return false;       //RETURN 31 DAYS
    };

};

class Calendar{
private:
    Date* date;
    vector<Month> month;
    short int totalDays = 0;
    short int holiday;
public:

    Calendar (Date& date) : date(&date) {

    }
    void createCalendar()
    {
        for(unsigned int i = 1; i <= 12; ++i)
        {
            Month current;
            current.monthName = monthNames[i-1];
            for(int day = 1; day <= date->getMonthDays(i); ++day )
            {
                ++totalDays;                // TOTAL DAYS CALCULATE
                current.days.push_back(day);
            }
            month.push_back(current);

        }
        cout << "total days: " << totalDays <<endl;
    }
    void printCalendar()
    {
        short int curCalendar;
        for(int i = 0; i < 12; ++i)
        {
            cout << month[i].monthName << ": " << endl;

            int line = 0; // connection 1

            for(int days = 1; days <= month[i].days.size() ; ++days )
            {
                if(days==1)
                {
                    line = createSpaces();
                    curCalendar = month[i].days.size();
                }
                cout << "\t" << month[i].days[days-1];
                if(days % 7 - line-1 == 0)
                    cout << endl;
            }
            cout << endl;
            if(curCalendar == 31)
                holiday-=1;
            else if (curCalendar == 30)
                holiday-=2;
            else if (curCalendar == 29)
                holiday-=3;
            else if (curCalendar == 28)
                holiday-=4;
            if(holiday < 1)
                holiday = 5;
            cout << holiday <<endl;
        }
    }

    short int createSpaces()
    {
        if (holiday == 5)
            cout << "\t" ;
        else if (holiday == 4)
            cout << "\t\t" ;
        else if (holiday == 3)
            cout << "\t\t\t" ;
        else if (holiday == 2)
            cout << "\t\t\t\t" ;
        else if (holiday == 1)
            cout << "\t\t\t\t\t" ;
        return holiday;                 //connection 1
    }

    // set sanday
    void setHolidays(short int sunday) {
        holiday = sunday;
        if(holiday > 7)
            holiday = 7;
        else if (holiday < 1)
            holiday = 1;
    }
};

int main ()
{
    Date date(32,8,2016);
    date.showDate();
    cout << date.getMonthDays() <<endl;
    Calendar cal(date);
    cal.setHolidays(4);
    cal.createCalendar();
    cal.printCalendar();

}