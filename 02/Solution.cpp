#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define vvi vector<vi>
#define vc vector<char>
#define vs vector<string>
#define pb push_back
#define test  \
    ll t;     \
    cin >> t; \
    while (t--)
#define mod 1000000007
#define fo ios_base::sync_with_stdio(false);
#define fi cin.tie(NULL);
void dayTwoFirst(const string &file, const int RED, const int BLUE, const int GREEN)
{
    ifstream input(file, ios::in);

    int res = 0;
    while (!input.eof())
    {
        string line;

        getline(input, line);
        string clr;

        int qty = 0;
        int redCount = 0;
        int greenCount = 0;
        int blueCount = 0;

        int id = 0;
        string::size_type pos = line.find("Game");
        if (pos != string::npos)
        {
            line.erase(0, pos + 5);
        }

        while (isdigit(line[0]))
        {
            id = id * 10 + (line[0] - '0');
            line.erase(0, 1);
        }
        line.erase(0, 2);

        line.append(";");
        bool possible = true;

        size_t i = 0;
        while (i < line.length() && possible)
        {
            if (isdigit(line[i]))
            {
                while (isdigit(line[i]))
                {
                    qty = qty * 10 + (line[i] - '0');
                    i++;
                }
            }
            else if (line[i] == ',' || line[i] == ' ')
            {
                if (clr == "red")
                {
                    redCount += qty;
                }
                else if (clr == "green")
                {
                    greenCount += qty;
                }
                else if (clr == "blue")
                {
                    blueCount += qty;
                }
                clr = "";
                qty = 0;
            }
            else if (line[i] == ';')
            {
                if (clr == "red")
                {
                    redCount += qty;
                }
                else if (clr == "green")
                {
                    greenCount += qty;
                }
                else if (clr == "blue")
                {
                    blueCount += qty;
                }
                if (redCount > RED || greenCount > GREEN || blueCount > BLUE)
                {
                    possible = false;
                }
                redCount = 0;
                greenCount = 0;
                blueCount = 0;
                qty = 0;
            }
            else
            {
                clr += line[i];
            }
            i++;
        }
        if (possible)
        {
            res += id;
        }
    }
    cout << "First solution: " << res << endl;
}

void dayTwoSecond(const string &file)
{
    ifstream input(file, ios::in);

    int res = 0;
    while (!input.eof())
    {
        string line;

        getline(input, line);
        string clr;

        int qty = 0;
        int redCount = 0;
        int greenCount = 0;
        int blueCount = 0;

        int id = 0;
        string::size_type pos = line.find("Game");
        if (pos != string::npos)
        {
            line.erase(0, pos + 5);
        }

        while (isdigit(line[0]))
        {
            id = id * 10 + (line[0] - '0');
            line.erase(0, 1);
        }
        line.erase(0, 2);

        line.append(";");

        size_t i = 0;
        while (i < line.length())
        {
            if (isdigit(line[i]))
            {
                while (isdigit(line[i]))
                {
                    qty = qty * 10 + (line[i] - '0');
                    i++;
                }
            }
            else if (line[i] == ',' || line[i] == ' ')
            {
                if (clr == "red")
                {
                    qty > redCount ? redCount = qty : redCount;
                }
                else if (clr == "green")
                {
                    qty > greenCount ? greenCount = qty : greenCount;
                }
                else if (clr == "blue")
                {
                    qty > blueCount ? blueCount = qty : blueCount;
                }
                clr = "";
                qty = 0;
            }
            else if (line[i] == ';')
            {
                if (clr == "red")
                {
                    qty > redCount ? redCount = qty : redCount;
                }
                else if (clr == "green")
                {
                    qty > greenCount ? greenCount = qty : greenCount;
                }
                else if (clr == "blue")
                {
                    qty > blueCount ? blueCount = qty : blueCount;
                }
                qty = 0;
            }
            else
            {
                clr += line[i];
            }
            i++;
        }
        res += redCount * greenCount * blueCount;
    }
    cout << "Second solution: " << res << endl;
}

int main()
{
    fo;
    fi;

    const int RED = 12;
    const int GREEN = 13;
    const int BLUE = 14;

    string file = "input.txt";
    dayTwoFirst(file, RED, BLUE, GREEN);
    dayTwoSecond(file);

    return 0;
}
