#include <iostream>
#include "IntQueueHW6.h"
#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <mutex>
#include <vector>

// Racing multiple threads - multithreading

using namespace std;
mutex myMutex;

vector<int> eliminated;

void GetChair(int order, struct tm *ptm, IntQueueHW6 &que, vector<int> &vec, bool notSetted)
{                                                                                  // getting chair for threads if not have any chair
    this_thread::sleep_until(std::chrono::system_clock::from_time_t(mktime(ptm))); // sleep until 2 seconds counts
    myMutex.lock();
    if (!que.isFull() && notSetted)
    { // if que is not full and notSetted then we can add it
        que.enqueue(order);
        time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << "Player " << order << " captured a chair at " << put_time(localtime(&tt), "%X") << ".\n";
    }

    else if (que.isFull() && notSetted)
    { // else condition for not getting chair when que is full and notSetted
        cout << "Player " << order << " couldn't capture a chair." << endl;
        vec.push_back(order);
    }

    myMutex.unlock();
}

int main()
{
    int playerNum;
    cout << "Welcome to Musical Chairs game!" << endl;
    cout << "Enter the number of players in the game:" << endl;
    cin >> playerNum;
    cout << "Game Start!" << endl
         << endl;
    thread threads[playerNum]; // Some ide's give an error for this. The HW was written on CLion where this declaration is legal
    int chairNum = playerNum - 1;
    int playerNumAtFirst = playerNum;

    time_t currentTime = time(nullptr);            // taking current time
    struct tm *timeInfo = localtime(&currentTime); // converting to pointer object
    int hour = timeInfo->tm_hour;
    int minute = timeInfo->tm_min;
    int second = timeInfo->tm_sec;
    cout << "Time is now " << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute << ":" << setfill('0') << setw(2) << second << endl;

    while (chairNum != 0)
    {
        IntQueueHW6 chairs = IntQueueHW6(chairNum);

        time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // current time now
        struct tm *ptm = new struct tm;
        localtime_s(ptm, &tt);
        if (ptm->tm_sec <= 58)
        {
            ptm->tm_sec += 2;
        }
        else
        {
            int diff = 60 - ptm->tm_sec;
            ptm->tm_min++;
            ptm->tm_sec = diff;
        }
        for (int i = 0; i < playerNumAtFirst; i++)
        {
            bool notEliminated = true;
            for (int j = 0; j < eliminated.size(); j++)
            {
                if (eliminated[j] == i)
                {
                    notEliminated = false;
                }
            }
            if (notEliminated)
            {
                threads[i] = thread(&GetChair, i, ptm, ref(chairs), ref(eliminated), notEliminated); // if not eliminated than call function
            }
        }
        for (int i = 0; i < playerNumAtFirst; i++)
        {
            bool notEliminated = true;
            for (int j = eliminated.size() - 1; j >= 0; j--)
            {
                if (eliminated[j] == i)
                {
                    notEliminated = false; // finding the eliminated one
                }
            }
            if (threads[i].joinable() && notEliminated)
            { // if joinable thread and notEliminated then it can join
                threads[i].join();
            }
        }
        cout << "Remaining players are as follows: ";
        int temp;
        while (!chairs.isEmpty())
        {
            chairs.dequeue(temp); // dequeueing one by one to print out the threads
            cout << temp << " ";
        }
        cout << endl
             << endl;
        playerNum--;
        chairNum--;
        currentTime = time(nullptr);
        timeInfo = localtime(&currentTime); // finding the localtime
        hour = timeInfo->tm_hour;
        minute = timeInfo->tm_min;
        second = timeInfo->tm_sec;
        if (playerNum != 1)
        {
            cout << "Time is now " << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute << ":" << setfill('0') << setw(2) << second << endl;
        }
        delete ptm;
    }
    int winner = 0;
    for (int i = 0; i < playerNumAtFirst; i++)
    { // finding the winner thread by iterating over vector
        bool notInVec = true;
        for (int j = 0; j < eliminated.size(); j++)
        {
            if (eliminated[j] == i)
            {
                notInVec = false;
            }
        }
        if (notInVec)
        { // finding the winner that if not eliminated
            winner = i;
        }
    }
    for (int i = 0; i < playerNumAtFirst; i++)
    { // join if it is joinable
        if (threads[i].joinable())
        {
            threads[i].join();
        }
    }
    cout << "Game over!" << endl;
    cout << "Winner is Player " << winner << "!" << endl;
}
