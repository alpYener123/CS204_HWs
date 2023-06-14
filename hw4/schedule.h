//
// Created by ALP on 4/16/2023.
//

#ifndef HW4_SCHEDULE_H
#define HW4_SCHEDULE_H
using namespace std;
#include <string>

enum Days {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

class Schedule
{
    private:
        int time_slots;
        string ** data;

    public:
        Schedule(); // default constructor
        Schedule(int c); // parametric constructor
        Schedule(const Schedule & copy); // deep copy
        ~Schedule(); // destructor

        string ** getterData() const; //getters and setters
        int getterSlot() const;
        void setterData(string ** ptr);
        void setterSlot(int slot);

        Schedule & operator=(const Schedule & rhs);
        Schedule operator+(Schedule & rhs);
        const Schedule operator*(const Schedule & rhs);
        string * operator[](const Days rhs) const;
        const bool operator<(const Schedule rhs);
};

Schedule operator+(const Schedule lhs, const Days rhs);
Schedule operator+(const Schedule lhs, const int rhs);
ostream& operator<<(ostream &output, const Schedule & rhs);
ostream& operator<<(ostream &output, const Days & rhs);

#endif //HW4_SCHEDULE_H
