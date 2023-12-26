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

static vector<vector<int8_t>> grid;
static const pair<int, int> dirs[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

struct step
{
    int loss, x, y, d;
    bool operator<(const step &s) const { return s.loss < loss; }
};

struct visit
{
    int x, y, d;
};

static bool in_grid(pair<int, int> pos)
{
    return pos.first >= 0 && pos.first < static_cast<int>(grid[0].size()) && pos.second >= 0 &&
           pos.second < static_cast<int>(grid.size());
}

static int solve(int mindist, int maxdist)
{
    priority_queue<struct step> q;
    vector<vector<uint8_t>> visited(grid.size(), vector<uint8_t>(grid[0].size(), 0));
    vector<vvi> losses(
        grid.size(),
        vvi(grid[0].size(), vector<int>(4, numeric_limits<int>::max())));
    q.push({0, 0, 0, -1});
    while (!q.empty())
    { // Dijkstra's Algo
        auto [loss, x, y, d] = q.top();
        q.pop();
        if (x == static_cast<int>(grid[0].size()) - 1 && y == static_cast<int>(grid.size()) - 1)
            return loss;
        if (visited[x][y] & (1 << d))
            continue;
        visited[x][y] |= (1 << d);
        for (int dir = 0; dir < 4; dir++)
        {
            int path_loss = 0;
            if (dir == d || (dir + 2) % 4 == d)
                continue;
            for (int dist = 1; dist <= maxdist; dist++)
            {
                int xx = x + dirs[dir].first * dist, yy = y + dirs[dir].second * dist;
                if (in_grid({xx, yy}))
                {
                    path_loss += grid[yy][xx];
                    if (dist < mindist)
                        continue;
                    int nc = loss + path_loss, cc = losses[xx][yy][dir];
                    if (cc < nc)
                        continue;
                    losses[xx][yy][dir] = nc;
                    q.push({nc, xx, yy, dir});
                }
            }
        }
    }
    abort();
}

int main()
{
    fo;
    fi;
    ifstream f("input.txt");
    string line;
    while (getline(f, line))
    {
        grid.pb({});
        for (auto c : line)
            grid.back().pb(c - '0');
    }
    cout
        << "Part 1: " << solve(1, 3) << endl
        << "Part 2: " << solve(4, 10) << endl;
}
