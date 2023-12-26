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
static int rows, cols;

using grid_t = vvi;
using visited_t = vector<vector<bool>>;

static grid_t grid;
static visited_t vis;

static void visit(int r, int c, int num)
{
    if (lines[r][c] == '#')
        return;
    if (vis[r][c])
        return;
    vis[r][c] = true;
    grid[r][c] = max(grid[r][c], num);
    if ((c > 0) && ((lines[r][c] == '.') || (lines[r][c] == '<')))
        visit(r, c - 1, num + 1);
    if (((c + 1) < cols) && ((lines[r][c] == '.') || (lines[r][c] == '>')))
        visit(r, c + 1, num + 1);
    if ((r > 0) && ((lines[r][c] == '.') || (lines[r][c] == '^')))
        visit(r - 1, c, num + 1);
    if (((r + 1) < rows) && ((lines[r][c] == '.') || (lines[r][c] == 'v')))
        visit(r + 1, c, num + 1);
    vis[r][c] = false;
}

static int partOne()
{
    grid = grid_t(rows, vi(cols, 0));
    vis = visited_t(rows, vector<bool>(cols, false));
    visit(0, 1, 0);
    return grid[rows - 1][cols - 2];
}

using pos = pair<int, int>;

struct pos_hash
{
    size_t operator()(const pos &p) const { return (size_t(p.second) << 32) | p.first; }
};

using nodes_t = unordered_set<pos, pos_hash>;
using longest_paths_t = unordered_map<pos, int, pos_hash>;
using edges_t = unordered_map<pos, longest_paths_t, pos_hash>;
using visited2_t = unordered_map<pos, bool, pos_hash>;

static nodes_t nodes;
static edges_t edges;
static longest_paths_t longPath;
static visited2_t vis2;

static void visit2(pos node, int path)
{
    if (vis2[node])
        return;
    vis2[node] = true;
    longPath[node] = max(longPath[node], path);
    for (auto [node2, length] : edges[node])
        visit2(node2, path + length);
    vis2[node] = false;
}

static tuple<int, int, int> run_length(int r, int c, char dir)
{
    nodes_t vis;
    auto isVis = [&](int r, int c)
    { return vis.find({r, c}) != vis.end(); };
    vis.insert({r, c});
    switch (dir)
    {
    case '<':
        c -= 1;
        break;
    case '>':
        c += 1;
        break;
    case '^':
        r -= 1;
        break;
    case 'v':
        r += 1;
        break;
    }
    int length = 0;
    if (lines[r][c] == '#')
        return make_tuple(r, c, length);
    while (nodes.find({r, c}) == nodes.end())
    {
        ++length;
        vis.insert({r, c});
        if ((c > 0) && (lines[r][c - 1] != '#') && !isVis(r, c - 1))
            c -= 1;
        else if ((r > 0) && (lines[r - 1][c] != '#') && !isVis(r - 1, c))
            r -= 1;
        else if (((c + 1) < cols) && (lines[r][c + 1] != '#') && !isVis(r, c + 1))
            c += 1;
        else if (((r + 1) < rows) && (lines[r + 1][c] != '#') && !isVis(r + 1, c))
            r += 1;
    }
    return make_tuple(r, c, length + 1);
}

static int partTwo()
{
    nodes.insert({0, 1});
    nodes.insert({rows - 1, cols - 2});
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
        {
            if (lines[r][c] == '#')
                continue;
            int exits = 0;
            if (c > 0)
                exits += (lines[r][c - 1] != '#');
            if ((c + 1) < cols)
                exits += (lines[r][c + 1] != '#');
            if (r > 0)
                exits += (lines[r - 1][c] != '#');
            if ((r + 1) < rows)
                exits += (lines[r + 1][c] != '#');
            if (exits > 2)
                nodes.insert({r, c});
        }
    for (auto [r, c] : nodes)
    {
        if (c > 0)
        {
            auto [r2, c2, len] = run_length(r, c, '<');
            if (len > 1)
                edges[{r, c}][{r2, c2}] = len;
        }
        if ((c + 1) < cols)
        {
            auto [r2, c2, len] = run_length(r, c, '>');
            if (len > 1)
                edges[{r, c}][{r2, c2}] = len;
        }
        if (r > 0)
        {
            auto [r2, c2, len] = run_length(r, c, '^');
            if (len > 1)
                edges[{r, c}][{r2, c2}] = len;
        }
        if ((r + 1) < rows)
        {
            auto [r2, c2, len] = run_length(r, c, 'v');
            if (len > 1)
                edges[{r, c}][{r2, c2}] = len;
        }
    }
    visit2(pos{0, 1}, 0);
    return longPath[pos{rows - 1, cols - 2}];
}

int main()
{
    fo;
    fi;
    ifstream f("input.txt");
    string line;
    while (f >> line)
        lines.pb(line);
    rows = lines.size();
    cols = lines[0].size();
    cout
        << "Part 1: " << partOne() << endl
        << "Part 2: " << partTwo() << endl;
}
