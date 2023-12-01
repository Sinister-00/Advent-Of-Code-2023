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

void dayOneFirst()
{
    string line;
    vs lines;

    ifstream file("input.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }

    int res = 0; // Sum of sums

    for (const auto &line : lines)
    {
        regex dig("\\d");
        sregex_iterator it(line.begin(), line.end(), dig);
        sregex_iterator end;

        vs n;
        while (it != end)
        {
            n.push_back(it->str());
            ++it;
        }

        if (!n.empty())
        {
            res += stoi(n[0] + n.back());
        }
    }

    cout << "First solution: " << res << endl;
}

void dayOneSecond()
{
    string line;
    vs lines;

    ifstream file("input.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }

    int res = 0; // Sum of sums

    for (auto &line : lines)
    {
        line = regex_replace(line, regex("one"), "o1e");
        line = regex_replace(line, regex("two"), "t2o");
        line = regex_replace(line, regex("three"), "t3e");
        line = regex_replace(line, regex("four"), "f4r");
        line = regex_replace(line, regex("five"), "f5e");
        line = regex_replace(line, regex("six"), "s6x");
        line = regex_replace(line, regex("seven"), "s7n");
        line = regex_replace(line, regex("eight"), "e8t");
        line = regex_replace(line, regex("nine"), "n9e");

        regex dig("\\d");
        sregex_iterator it(line.begin(), line.end(), dig);
        sregex_iterator end;

        vs n;
        while (it != end)
        {
            n.push_back(it->str());
            ++it;
        }

        if (!n.empty())
        {
            res += stoi(n[0] + n.back());
        }
    }

    cout << "Second solution: " << res << endl;
}

int main()
{
    fo;
    fi;
    dayOneFirst();
    dayOneSecond();

    return 0;
}
