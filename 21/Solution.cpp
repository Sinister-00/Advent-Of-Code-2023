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
using position = array<int, 2>;

struct hash_pos
{
    size_t operator()(const position &p) const { return p[0] | (size_t(p[1]) << 32); }
};

using position_set = unordered_set<position, hash_pos>;
using position_map = unordered_map<position, int, hash_pos>;

static position_set start_positions, visited;
static vs grid;

static void update_pos()
{
    position_set next_positions;
    for (const auto &pos : start_positions)
    {
        if (pos[0] > 0 && grid[pos[0] - 1][pos[1]] != '#')
            next_positions.insert({pos[0] - 1, pos[1]});
        if (pos[0] < static_cast<int>(grid.size()) - 1 && grid[pos[0] + 1][pos[1]] != '#')
            next_positions.insert({pos[0] + 1, pos[1]});
        if (pos[1] > 0 && grid[pos[0]][pos[1] - 1] != '#')
            next_positions.insert({pos[0], pos[1] - 1});
        if (pos[1] < static_cast<int>(grid[pos[0]].size()) - 1 && grid[pos[0]][pos[1] + 1] != '#')
            next_positions.insert({pos[0], pos[1] + 1});
    }
    start_positions = next_positions;
}

static void search()
{
    position_set next_pos;
    int height = grid.size();
    int width = grid[0].size();
    for (const auto &pos : start_positions)
    {
        array<position, 4> moves{{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};
        for (const auto &mov : moves)
        {
            position check_pos{(((pos[0] + mov[0]) % height) + height) % height,
                               (((pos[1] + mov[1]) % width) + width) % width};
            if (grid[check_pos[0]][check_pos[1]] != '#' &&
                visited.find({pos[0] + mov[0], pos[1] + mov[1]}) == visited.end())
            {
                next_pos.insert({pos[0] + mov[0], pos[1] + mov[1]});
                visited.insert({pos[0] + mov[0], pos[1] + mov[1]});
            }
        }
    }
    start_positions = next_pos;
}

int main()
{
    fo;
    fi;
    ifstream f("input.txt");
    position start_pos;
    string line;
    size_t row = 0;
    while (getline(f, line))
    {
        grid.pb(line);
        size_t col = line.find('S');
        if (col != string::npos)
        {
            start_pos[0] = row;
            start_pos[1] = col;
            grid[row][col] = '.';
        }
        ++row;
    }
    start_positions.insert(start_pos);
    int steps = 64;
    while (steps--)
        update_pos();
    auto part1 = start_positions.size();
    start_positions.clear();
    start_positions.insert(start_pos);
    visited.insert(start_pos);
    position_map offs;
    offs[start_pos] = 0;
    steps = 26501365;
    vi parms, lengths;
    lengths.pb(1);
    for (size_t i = 0; i < static_cast<size_t>(steps); ++i)
    {
        search();
        lengths.pb(start_positions.size());
        if (i % grid.size() == steps % grid.size())
        {
            int len = 0;
            for (size_t j = 0; j < lengths.size() - 1; ++j)
                if (j % 2 == i % 2)
                    len += lengths[j];
            parms.pb(len);
        }
        if (parms.size() == 3)
            break;
    }
    int64_t p1 = parms[0], p2 = parms[1] - parms[0], p3 = parms[2] - parms[1],
            p = steps / grid.size(), part2 = p1 + p2 * p + (p * (p - 1) / 2) * (p3 - p2);
    cout
        << "Part 1: " << part1 << endl
        << "Part 2: " << part2 << endl;
}
