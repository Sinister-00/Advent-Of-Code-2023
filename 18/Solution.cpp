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

static vector<pair<int64_t, int64_t>> vertices;
static vs lines;

static vs split(const string &s, char delim)
{
    vs res;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        res.pb(item);
    return res;
}

static int64_t solve(bool part2)
{
    vertices.clear();
    int dir, x = 0, y = 0, steps, i = 0;
    for (auto &line : lines)
    {
        auto v = split(line, ' ');
        if (part2)
        {
            dir = strtoll(v[2].substr(7, 1).c_str(), NULL, 10);
            steps = strtoll(v[2].substr(2, 5).c_str(), NULL, 16);
        }
        else
        {
            switch (v[0][0])
            {
            case 'U':
                dir = 0;
                break;
            case 'R':
                dir = 1;
                break;
            case 'D':
                dir = 2;
                break;
            case 'L':
                dir = 3;
                break;
            }
            steps = strtoll(v[1].c_str(), NULL, 10);
        }
        switch (dir)
        {
        case 0:
            x -= steps;
            break;
        case 1:
            y += steps;
            break;
        case 2:
            x += steps;
            break;
        case 3:
            y -= steps;
            break;
        }
        vertices.pb(make_pair(x, y));
        i++;
    }
    vertices.pb(make_pair(vertices[0].first, vertices[0].second));
    int64_t res = 0;
    for (; i > 0; i--) // shoelace formula
    {
        int64_t a = vertices[i].second * vertices[i - 1].first,
                b = vertices[i].first * vertices[i - 1].second,
                c = vertices[i].first - vertices[i - 1].first,
                d = vertices[i].second - vertices[i - 1].second;
        res += abs(c) + abs(d) + b - a;
    }
    return res / 2 + 1;
}

int main()
{
    fo;
    fi;
    ifstream f("input.txt");
    string line;
    while (getline(f, line))
        lines.pb(line);
    cout
        << "Part 1: " << solve(false) << endl
        << "Part 2: " << solve(true) << endl;
}
