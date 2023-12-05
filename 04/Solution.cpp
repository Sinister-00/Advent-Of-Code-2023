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

vi helper(const string &str, char delimiter)
{
    vi numbers;
    stringstream ss(str);
    string temp;

    while (getline(ss, temp, delimiter))
    {
        if (temp != "")
        {
            numbers.pb(stoi(temp));
        }
    }

    return numbers;
}

void dayFourPartOne(vs lines)
{
    int res = 0;

    size_t i = 0;
    while (i < lines.size())
    {
        size_t splitPos = lines[i].find(':');
        size_t splitPos2 = lines[i].find('|', splitPos + 1);
        vi winningNumbers = helper(string(lines[i].begin() + splitPos + 2, lines[i].begin() + splitPos2), ' ');
        vi ourNumbers = helper(string(lines[i].begin() + splitPos2 + 1, lines[i].end()), ' ');

        set<int> winningNumbersSet(winningNumbers.begin(), winningNumbers.end());
        set<int> ourNumbersSet(ourNumbers.begin(), ourNumbers.end());

        set<int> intersect;
        auto it1 = winningNumbersSet.begin();
        while (it1 != winningNumbersSet.end())
        {
            auto it2 = ourNumbersSet.begin();
            while (it2 != ourNumbersSet.end())
            {
                if (*it1 == *it2)
                {
                    intersect.insert(*it1);
                    break;
                }
                ++it2;
            }
            ++it1;
        }

        int matches = intersect.size();
        res += matches ? pow(2, matches - 1) : 0;

        ++i;
    }

    cout << "First solution: " << res << endl;
}

void dayFourPartTwo(vs lines)
{
    vi cards(lines.size(), 1);

    size_t i = 0;
    while (i < lines.size())
    {
        size_t splitPos = lines[i].find(':');
        size_t splitPos2 = lines[i].find('|', splitPos + 1);
        vi winningNumbers = helper(string(lines[i].begin() + splitPos + 2, lines[i].begin() + splitPos2), ' ');
        vi ourNumbers = helper(string(lines[i].begin() + splitPos2 + 1, lines[i].end()), ' ');

        set<int> winningNumbersSet(winningNumbers.begin(), winningNumbers.end());
        set<int> ourNumbersSet(ourNumbers.begin(), ourNumbers.end());

        set<int> intersect;
        auto it1 = winningNumbersSet.begin();
        while (it1 != winningNumbersSet.end())
        {
            auto it2 = ourNumbersSet.begin();
            while (it2 != ourNumbersSet.end())
            {
                if (*it1 == *it2)
                {
                    intersect.insert(*it1);
                    break;
                }
                ++it2;
            }
            ++it1;
        }

        int matches = intersect.size();

        int j = 0;
        while (j < matches)
        {
            cards[i + j + 1] += cards[i];
            ++j;
        }

        ++i;
    }

    cout << "Second solution: " << accumulate(cards.begin(), cards.end(), 0) << endl;
}

int main()
{
    fo;
    fi;
    ifstream file("input.txt");
    vs lines;
    string line;

    while (getline(file, line))
    {
        lines.pb(line);
    }

    dayFourPartOne(lines);
    dayFourPartTwo(lines);

    return 0;
}
