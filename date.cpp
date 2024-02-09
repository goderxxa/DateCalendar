#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

#define WEEK 7

const char* monthNames[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

class Day{
private:
    int numDay;
    string month;
};

class Month {
public:
    string monthName;
    vector<int> days;
};

class Date {
private:
    int day;
    int month;
    int year;
    int curM;

public:
    int getYear()
    {
        return year;
    }

    Date (int day, int month,int year) : day(day), month(month), year(year)
    {
        setDate();
    }

    int checkYear ()
    {
        if( year % 400 == 0 )
            return 29;
        else if(year % 100 == 0 )
            return 28;
        else if (year % 4 == 0 )
            return 29;
        return 28;
    }    

    bool checkMonth () {
        int months[7] = {1,3,5,7,8,10,12};
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
    int getMonthDays(int& curMonth)
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

    bool checkCurMonth (int& curMonth)  {
        curM = curMonth;
        int months[7] = {1, 3,5,7,8,10,12};
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
    int totalDays = 0;
    int holiday;              // sarturday
    
public:

    Calendar (Date& date) : date(&date) {
    }
    void createCalendar()
    {
        for(int i = 1; i <= 12; ++i)
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
            cout <<"_______________" << month[i].monthName << "________________" << endl;             // month name out
            cout <<"Mon  Tue  Wed  Thu  Fri  Sat  Sun"  << endl; 
            cout << endl;      

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
                if(spaces==0 && days==1)
                    cout << "  " ;
                cout <<  month[i].days[days-1] << "  " << setw(3)  ;

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

    int createSpaces()
    {
        int spc = 0;
        for(int i = 0; i < WEEK - holiday ; ++i)
        {
            if(i==0)
                cout << "  ";
            cout << "     " ;
            ++spc;
        }
        return spc;              //connection 1
    }

    // set sanday
    void setHolidays(int sarturday) {
        holiday = sarturday;
        if(holiday > WEEK)
            holiday = WEEK;
        else if (holiday < 1)
            holiday = 1;
    }
};

class HollidayCalculate {
    public:

    HollidayCalculate () {}

    int getHoliday(Date& date)
    {
        if(date.getYear() > year )
        {
            // cout << holliday << " ";
            for(int cur = year; cur != date.getYear(); ++cur )
            {
                // cout << cur << endl;
                if(checkYear(cur))
                {
                    holliday -=2;
                }                    
                else if(!checkYear(cur))
                {
                    holliday -=1;
                }
                if(holliday == 0)
                    holliday = 7;
                else if(holliday < 0 )
                    holliday = 6;
                // cout << holliday << " ";
            }                    
        }
        else if( date.getYear() < year )
        {
            for(int cur = date.getYear(); cur != year; ++cur )
            {
                if( checkYear(cur) )
                    holliday +=2;
                if(!checkYear(cur))    
                    holliday +=1;
                if(holliday == 8)
                    holliday=1;
                else if(holliday > 8 )
                    holliday=2;    
                    
                // cout << holliday << " ";           
            }
        }  
        // cout << endl;
        return holliday;         
    }

    bool checkYear (int& y)
    {
        if(y % 400 == 0 )
            return true;
        else if(y % 100 == 0 )
            return false;
        else if (y % 4 == 0 )
            return true;
        return false;

    }

    private:
        Date* date;
        int year = 2024;
        int holliday = 7;
};

int main ()
{        
    std::cout << "Enter date (day, month, year): ";
    std::string inputStr;

    std::getline(std::cin, inputStr);
    std::stringstream inputDate(inputStr);

    int day, month, year;
    inputDate >> day;
    inputDate.ignore();
    inputDate >> month;
    inputDate.ignore();
    inputDate >> year;

    Date date(day,month,year);

    Calendar cal(date);
    HollidayCalculate calc;
    cal.setHolidays(calc.getHoliday(date));
    
    date.showDate();    
    cal.createCalendar();
    cal.printCalendar();
    system("pause");

}
