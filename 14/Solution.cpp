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

static void roll(vs &g)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (size_t x = 0; x < g[0].size(); x++)
            for (size_t y = 0; y < g.size() - 1; y++)
            {
                auto &curr = g[y][x];
                auto &above = g[y + 1][x];
                if (curr == '.' && above == 'O')
                {
                    swap(curr, above);
                    changed = true;
                }
            }
    }
    changed = true;
    while (changed)
    {
        changed = false;
        for (size_t y = 0; y < g.size(); y++)
            for (size_t x = 0; x < g[0].size() - 1; x++)
            {
                auto &curr = g[y][x];
                auto &above = g[y][x + 1];
                if (curr == '.' && above == 'O')
                {
                    swap(curr, above);
                    changed = true;
                }
            }
    }
    changed = true;
    while (changed)
    {
        changed = false;
        for (size_t x = 0; x < g[0].size(); x++)
            for (size_t y = g.size() - 1; y != 0; y--)
            {
                auto &curr = g[y][x];
                auto &above = g[y - 1][x];
                if (curr == '.' && above == 'O')
                {
                    swap(curr, above);
                    changed = true;
                }
            }
    }
    changed = true;
    while (changed)
    {
        changed = false;
        for (size_t y = 0; y < g.size(); y++)
            for (size_t x = g[0].size() - 1; x != 0; x--)
            {
                auto &curr = g[y][x];
                auto &above = g[y][x - 1];
                if (curr == '.' && above == 'O')
                {
                    swap(curr, above);
                    changed = true;
                }
            }
    }
}

static string join(const vs &g)
{
    string r;
    for (auto &s : g)
        r += s;
    return r;
}

static int total_load(const vs &g)
{
    int sum = 0;
    for (size_t i = 0; i < g.size(); i++)
        for (size_t x = 0; x < g[0].size(); x++)
            if (g[i][x] == 'O')
                sum += g.size() - i;
    return sum;
}

static int part2(vs g)
{
    map<string, int> grids;
    map<int, int> loads;
    int i = 0, cycle_start = 0, cycle_end = 0;
    constexpr int target = 1000000000;
    while (true)
    {
        roll(g);
        i++;
        const auto key = join(g);
        if (grids.find(key) != grids.end())
        {
            cycle_start = grids.at(key);
            cycle_end = i;
            break;
        }
        else
        {
            grids[key] = i;
            loads[i] = total_load(g);
        }
    }
    const auto period = cycle_end - cycle_start;
    const auto cycle = target - cycle_start;
    return loads[cycle_start + cycle % period];
}

static int part1(vs g)
{
    int i = 1;
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (size_t x = 0; x < g[0].size(); x++)
            for (size_t y = 0; y < g.size() - 1; y++)
            {
                auto &curr = g[y][x];
                auto &above = g[y + 1][x];
                if (curr == '.' && above == 'O')
                {
                    swap(curr, above);
                    changed = true;
                }
            }
        i++;
    }
    return total_load(g);
}

int main()
{
    fo;
    fi;
    ifstream inf("input.txt");
    string line;
    vs grid;
    while (getline(inf, line))
        grid.pb(line);
    cout
        << "Part 1: " << part1(grid) << endl
        << "Part 2: " << part2(grid) << endl;
}
