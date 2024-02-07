#include <iostream>
#include <string>
#include <vector>

#define WEEK 7

const char* monthNames[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
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
    short int holiday;              // sarturday
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
        bool next=0;
        for(int i = 0; i < 12; ++i)
        {
            cout << month[i].monthName << ":______________________" << endl;             // month name out
            int spaces;
            int monthDays;
            int elapsed;
            int strokes=0;

            for(int days = 1; days <= month[i].days.size() ; ++days )
            {
                monthDays = month[i].days.size();
                if(days == 1)
                {
                    spaces = createSpaces();
                    elapsed = monthDays - spaces ;
                    ++strokes;
                }
                if(spaces + days -1  == WEEK && next ==0)
                {
                    next=1;
                    cout << endl;
                    ++strokes;
                }
                cout <<  month[i].days[days-1] << "\t" ;

                if( spaces!= 0)
                {
                    if(days % WEEK - (WEEK-spaces) == 0 && next == 1)
                    {
                        cout << endl;
                        elapsed-=7;++strokes;

                    }
                }
                else if(days % WEEK - spaces == 0 && next == 1)
                {
                    cout << endl;
                    elapsed-=7;++strokes;
                }
            }
            cout << endl;
//            cout << strokes << endl;
            holiday = strokes * WEEK - monthDays - spaces;
//            cout << holiday << endl;
        }
    }

    short int createSpaces()
    {
        int spc = 0;
        for(int i = 0; i < WEEK - holiday ; ++i)
        {
            cout << "\t" ;
            ++spc;
        }
        return spc;              //connection 1
    }

    // set sanday
    void setHolidays(short int sarturday) {
        holiday = sarturday;
        if(holiday > WEEK)
            holiday = WEEK;
        else if (holiday < 1)
            holiday = 1;
    }
};

int main ()
{
    Date date(32,8,2024);
    date.showDate();
    Calendar cal(date);
    cal.setHolidays(7);
    cal.createCalendar();
    cal.printCalendar();

}
