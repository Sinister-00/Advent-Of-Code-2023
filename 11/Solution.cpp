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


static vs lines;
static set<int> empty_columns;

static bool empty_row(string row)
{
    for (char c : row)
        if (c != '.')
            return false;
    return true;
}

static bool empty_col(vs &lines, int col)
{
    for (string &row : lines)
        if (row[col] != '.')
            return false;
    return true;
}

static int manhattan(pair<int, int> &a, pair<int, int> &b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int64_t part(uint32_t delta)
{
    vector<pair<int, int>> galaxy;
    uint32_t y_inc = 0;
    for (size_t y = 0; y < lines.size(); y++)
    {
        if (empty_row(lines[y]))
            y_inc += delta;
        int x_inc = 0;
        for (size_t x = 0; x < lines[0].size(); x++)
        {
            if (empty_columns.find(x) != empty_columns.end())
                x_inc += delta;
            if (lines[y][x] == '#')
                galaxy.pb(make_pair(y + y_inc, x + x_inc));
        }
    }
    int64_t sum = 0;
    for (size_t i = 0; i < galaxy.size() - 1; i++)
        for (size_t j = i + 1; j < galaxy.size(); j++)
            sum += manhattan(galaxy[i], galaxy[j]);
    return sum;
}

int main()
{
    fo;
    fi;
    ifstream f("input.txt");
    string line;
    while (getline(f, line))
        lines.pb(line);
    for (size_t x = 0; x < lines[0].size(); x++)
        if (empty_col(lines, x))
            empty_columns.insert(x);
    cout
        << "Part 1: " << part(1) << endl
        << "Part 2: " << part(999999) << endl;
}
