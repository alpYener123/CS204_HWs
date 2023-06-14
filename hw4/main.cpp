#include <iostream>
#include <string>
#include <iomanip>
#include "schedule.h"
using namespace std;

// 2D Dynamic Arrays, operator overloading

// ****************************************** Enum input >> operator ******************************************

istream & operator >> (istream& in, Days & d)
{
    string str_day;
    in>> str_day;

    if (str_day == "Monday")
    {
        d = Monday;
    }
    else if (str_day == "Tuesday")
    {
        d = Tuesday;
    }
    else if (str_day == "Wednesday")
    {
        d = Wednesday;
    }
    else if (str_day == "Thursday")
    {
        d = Thursday;
    }
    else if (str_day == "Friday")
    {
        d = Friday;
    }
    else if (str_day == "Saturday")
    {
        d = Saturday;
    }
    else if (str_day == "Sunday")
    {
        d = Sunday;
    }
    return in;
}

// ****************************************** display_sch ******************************************
void display_sch(const Schedule & sch, int slots)
{
        cout << "Printing using display_sch() function:"<<endl;
        for (Days d = Monday; d<= Sunday; d = Days (int(d)+1)) // type casting while updating d
        {
            cout << setw(10)<<d;
            for (int i = 0;i < slots ; i++)
            {
                cout<< " " <<*(sch[d]+i) ;
            }
            cout<<endl;
        }
}

Schedule full_schedule ()
{
    Schedule sch(1);
    sch = sch + 0;
    return sch;
}

int main() {

    int slots;
    int slot_to_fill;
    Days input_day;

    cout<< "Creating an empty schedule and displaying it."<<endl;
    Schedule s;
    cout<<s<<endl;

    s = full_schedule();
    cout << "Schedule s after calling the full_schedule() function"<<endl;
    cout << s;
    cout <<endl;

    cout<< "Please enter the number of slots per day:"<<endl;
    cin>>slots;

    if (slots <= 0)
    {
        cout<<"Invalid number of slots. Exiting the program."<<endl;
        return -1;
    }
    // Create two schedule objects with 7 rows (days) and 'slots' columns (time slots)
    Schedule schedule1( slots);
    Schedule schedule2( slots);

    cout<<"Throughout the program, whenever you are asked to enter a day, enter the day name with initial letter capitalized."<<endl<<endl;

    // Print the initial schedule
    cout << "Initial schedule 1 (all slots are free by default):"<<endl;
    cout<< schedule1<<endl;

    cout<< "Please enter the day of the week that you want to make busy in schedule 1:"<<endl;
    cin>>input_day;
    schedule1 = schedule1 + input_day;// Add busy status to input_day

    cout<< "Please enter the slot number that you want to change to busy in all days of the week in schedule 1:" <<endl;
    cout<< "The valid range is [0,"<<slots-1<<"]:"<<endl;
    cin>>slot_to_fill;
    schedule1 = schedule1 + slot_to_fill;// Add busy status to slot_to_fill

    // Print the updated schedule
    cout << "Schedule 1 after changing all the slots of "<<input_day<<" and slot number "<<slot_to_fill<<" to busy:"<<endl;
    cout<< schedule1<<endl;

    // schedule2 - some operations
    cout<< "Please enter the day of the week that you want to make busy in schedule 2:"<<endl;
    cin>>input_day;
    schedule2 = schedule2 + input_day;

    cout << "Schedule 2 after changing all the slots of "<<input_day<<" to busy:"<<endl;
    cout<<schedule2<<endl;

    cout<< "Please enter the slot number that you want to change to busy in all days of the week in schedule 2:" <<endl;
    cout<< "The valid range is [0,"<<slots-1<<"]:"<<endl;
    cin>>slot_to_fill;


    cout<< "The output of    cout << schedule2 + " <<slot_to_fill << " << endl;    is:" <<endl;
    //cout << "Schedule 2 would be the following, if slot number "<< slot_to_fill <<" was changed to busy:"<<endl;
    cout << schedule2 + slot_to_fill << endl;

    // self assignment
    schedule1 = schedule1;
    cout << "Schedule 1 after self-assignment:"<<endl;
    cout << schedule1 <<endl;

    // schedule3
    Schedule schedule3 (schedule1 * schedule2);
    cout << "Schedule 3 created as multiplication (common busy hours) of schedule 1 and schedule 2:"<<endl;
    display_sch(schedule3, slots);
    cout<<endl;

// Compare schedule 3 and schedule 2 using the < operator
    if (schedule3 < schedule2)
        cout<<"schedule 3 is less busy than schedule 2."<<endl;
    else if (schedule2 < schedule3)
        cout<<"schedule 2 is less busy than schedule 3."<<endl;
    else
        cout<<"schedule 2 and schedule 3 have the same number of busy slots."<<endl;
    cout<<endl;

    // Add schedule 2 object to schedule 1 object
    schedule1 = schedule1 + schedule2;
    // Print the updated schedule
    cout << "Schedule 1 after   schedule1 = schedule1 + schedule2; "<<endl;
    cout<< schedule1 <<endl;

    if (schedule2[Saturday][slots/2]=="busy")
    {
        schedule2[Saturday][slots/2]="free";
    }
    else
    {
        schedule2[Saturday][slots/2]="busy";
    }

    cout << "Schedule 2 after toggling one element:"<<endl;
    cout << schedule2;
    cout<<endl;

    schedule1 = schedule1 + schedule2 + schedule3;
    cout<< "schedule 1 after   schedule1 = schedule1 + schedule2 + schedule3; "<<endl;
    cout << schedule1 << endl;


    Schedule schedule4 (slots+4);
    cout << "Schedule 4 has been created with "<< slots+4 << " slots."<<endl;
    cout << schedule4 <<endl;

    schedule1 = schedule2 = schedule4;
    cout<< "schedule 1, 2 and 4 after   schedule1 = schedule2 = schedule4; "<<endl;
    cout << "schedule 1:"<<endl;
    cout << schedule1<<endl;
    cout << "schedule 2:"<<endl;
    cout << schedule2<<endl;
    cout << "schedule 4:"<<endl;
    cout << schedule4<<endl;

    return 0;
}