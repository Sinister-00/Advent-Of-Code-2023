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

static vs split(const string &s, char delim)
{
    vs v;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        v.pb(item);
    return v;
}

static vector<uint32_t> split_numbers(string &s)
{
    vector<uint32_t> v;
    stringstream ss(s);
    int n;
    char c;
    while (ss >> n)
    {
        v.pb(n);
        ss >> c;
    }
    return v;
}

struct key
{
    uint32_t k[4];
    bool operator==(const key &a) const
    {
        return (this->k[0] == a.k[0]) && (this->k[1] == a.k[1]) && (this->k[2] == a.k[2]) &&
               (this->k[3] == a.k[3]);
    }
    struct hasher
    {
        size_t operator()(const key &k) const
        {
            return ((size_t(k.k[0]) << 32) + k.k[1]) ^ ((size_t(k.k[2]) << 32) + k.k[3]);
        }
    };
};

static uint64_t solve(string s, vector<uint32_t> c)
{
    unordered_map<key, uint64_t, key::hasher> states({{{0, 0, 0, 0}, 1}}), nstates;
    uint64_t count = 0;
    while (states.size())
    {
        uint32_t si, ci, cc, dot;
        uint64_t num;
        for (auto &cs : states)
        {
            num = cs.second;
            si = cs.first.k[0];
            ci = cs.first.k[1];
            cc = cs.first.k[2];
            dot = cs.first.k[3];
            if (si == s.size())
            {
                if (ci == c.size())
                    count += num;
                continue;
            }
            if ((s[si] == '#' || s[si] == '?') && ci < c.size() && dot == 0)
            {
                if (s[si] == '?' && cc == 0)
                    nstates[{si + 1, ci, cc, dot}] += num;
                cc++;
                if (cc == c[ci])
                {
                    ci++;
                    cc = 0;
                    dot = 1;
                }
                nstates[{si + 1, ci, cc, dot}] += num;
            }
            else if ((s[si] == '.' || s[si] == '?') && cc == 0)
                nstates[{si + 1, ci, 0, 0}] += num;
        }
        states.swap(nstates);
        nstates.clear();
    }
    return count;
}

int main()
{
    ifstream f("input.txt");
    vs lines;
    string line;
    while (getline(f, line))
        lines.pb(line);
    uint64_t p1 = 0, p2 = 0;
    for (auto &l : lines)
    {
        auto kk = split(l, ' ');
        string s = kk[0];
        auto v = split_numbers(kk[1]);
        p1 += solve(s, v);
        string p2s = s;
        vector<uint32_t> p2v = v;
        for (uint32_t j = 0; j < 4; j++)
        {
            p2s += '?';
            p2s += s;
            for (size_t j = 0; j < v.size(); j++)
                p2v.pb(v[j]);
        }
        p2 += solve(p2s, p2v);
    }
    cout
        << "Part 1: " << p1 << endl
        << "Part 2: " << p2 << endl;
}
