#include "feedback.h"
#include <string>
using namespace std;

int mypower(int a, int b, int m)
{
    int res = 1;
    a = a % m;
    for(int i=1 ; i<=b ; ++i)
        res = (res * a) % m;
    return res;
}

string secretNumber (int gameID)
{
    bool stop = false;
    string s = "   ";
    while (!stop)
    {
        gameID = gameID*gameID % 15307;
        int secret = mypower (393, gameID, 15307) % 1000;
        s = "   ";
        s[2] = secret % 10 + 48;
        s[1] = (secret / 10) % 10 + 48;
        s[0] = (secret / 100) % 10 + 48;
        stop = !(s[0] == s[1] || s[0] == s[2] || s[2] == s[1]);
        gameID=gameID*2 + 128;
    }
    return s;
}

string get_the_feedback (string guess, int game_id)
{
    string secret_number = secretNumber(game_id);

    string feedback_str(3,' ');
    for (int i = 0; i< 3; i ++)
    {
        if (guess[i] == secret_number[i])
            feedback_str[i] = 'G';
        else if (guess[i] == secret_number[(i+1)%3] || guess[i] == secret_number[(i+2)%3])
            feedback_str[i] = 'Y';
        else
            feedback_str[i] = 'R';
    }
    return feedback_str;
}