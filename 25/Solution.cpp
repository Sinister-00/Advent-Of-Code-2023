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

static int n_nodes;
static vvi adjacent;
static map<string, int> names;

static pair<int, vi> minCut()
{
    pair<int, vi> res = {numeric_limits<int>::max(), {}};
    vvi co(n_nodes);
    for (int i = 0; i < n_nodes; i++)
        co[i] = {i};
    for (int ph = 1; ph < n_nodes; ph++)
    {
        vi w = adjacent[0];
        size_t s = 0, t = 0;
        for (int it = 0; it < n_nodes - ph; it++)
        {
            w[t] = numeric_limits<int>::min();
            auto largest_elm = w.begin();
            auto largest = numeric_limits<int>::min();
            for (auto m = w.begin(); m != w.end(); m++)
                if (*m > largest)
                {
                    largest_elm = m;
                    largest = *m;
                }
            s = t, t = largest_elm - w.begin();
            for (int i = 0; i < n_nodes; i++)
                w[i] += adjacent[t][i];
        }
        res = min(res, {w[t] - adjacent[t][t], co[t]});
        co[s].insert(co[s].end(), co[t].begin(), co[t].end());
        for (int i = 0; i < n_nodes; i++)
            adjacent[s][i] += adjacent[t][i];
        for (int i = 0; i < n_nodes; i++)
            adjacent[i][s] = adjacent[s][i];
        adjacent[0][t] = numeric_limits<int>::min();
    }
    return res;
}

static int nameIdx(const string &s)
{
    if (names.find(s) != names.cend())
        return names[s];
    int idx = names.size();
    names[s] = idx;
    return idx;
}

int main()
{
    fo;
    fi;
    ifstream f("input.txt");
    vector<pair<int, int>> connections;
    string l;
    while (getline(f, l))
    {
        stringstream ss(l);
        string name;
        ss >> name;
        name = name.substr(0, name.size() - 1);
        int parent = nameIdx(name);
        while (ss >> name)
            connections.emplace_back(parent, nameIdx(name));
    }
    adjacent = vector<vi>(names.size(), vi(names.size(), 0));
    for (const auto &p : connections)
        adjacent[p.first][p.second] = adjacent[p.second][p.first] = 1;
    n_nodes = adjacent.size();
    auto res = minCut();
    cout
        << "part 1: " << res.second.size() * (names.size() - res.second.size()) << endl
        << "part 2: NA" << endl;
}
