#include <iostream>
#include <string>
#include <memory>

const char* monthNames[] = {
        "jan", "feb", "mar", "apr", "may", "jun",
        "jul", "aug", "sep", "oct", "nov", "dec"
};

using namespace std;

class Date {
private:
    string dateInString;
    unsigned int day;
    unsigned int month;
    unsigned int year;

public:
    Date(unsigned int day, unsigned int month, unsigned int year) : day(day), month(month), year(year)     {

    }

    Date& operator++ ()
    {
        plusDay();
    }
    Date& operator-- ()
    {
        minusDay();
    }

    int checkYear ()
    {
        if(year % 4 == 0 || year % 400 == 0 )
            return 29;
        if(year % 100 == 0 && year % 400 == 0 )
            return 29;
        return 28;
    }

    //bool check mount
    bool checkMonth () {
        unsigned int months[7] = {1, 3,5,7,8,10,12};
        for(int i=0; i< sizeof(months); ++i)
        {
            if(month == months[i])
                return true;
        }
        return false;
    };

    // ++ date;
    void plusDay()
    {
        if(checkMonth())
        {
            if(day < 31)
                ++day;
            else {
                day = 1;
                if(month < 12)
                    ++month;
                else
                {
                    month=1;
                    ++year;
                }
            }
        }
        else if( month != 2 )
        {
            if(day < 30)
                ++day;
            else {
                day = 1;
                if(month < 12)
                    ++month;
                else
                {
                    month=1;
                }
            }
        }
        else {
            if(day < checkYear())
                ++day;
            else
            {
                day = 1;
                ++month;
            }
        }
    }
    void minusDay()
    {
        if(checkMonth() && month !=8 && month != 3  ) // exclude jul , feb, dec && month!= 1
        {
            if(day > 1)
                --day;
            else
            {
                if(month == 1)
                {
                    day = 31; month =12; --year;
                }
                else {
                    day = 30;
                    if(month > 1)
                        --month;
                    else
                    {
                        month=12;
                        --year;
                    }
                }

            }
        }
        else if( month != 3  ) // exclude feb
        {
            if(day > 1)
                --day;
            else {
                day = 31;
                if(month > 1)
                    --month;
                else
                {
                    month=12;
                }
            }
        }
        else {
            if(checkYear() == 29)
            {
                if(day > 1)
                    --day;
                else
                {
                    day = 29;
                    --month;
                }
            }
            if(checkYear() == 28)
            {
                if(day > 1)
                    --day;
                else
                {
                    day = 28;
                    --month;
                }
            }
        }
    }

    void showDate() const
    {
        cout << day << " " << monthNames[month-1] << " " << year << endl;
    }
};

int main ()
{
    Date date(1, 1, 2005);

    for(int i=0; i< 2000; ++i)
    {
        --date; date.showDate();
    }

}