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

struct pt
{
    pt(int px = 0, int py = 0, int pz = 0) : x(px), y(py), z(pz) {}
    bool operator<(const pt &p) const
    {
        if (z != p.z)
            return z < p.z;
        if (x != p.x)
            return x < p.x;
        return y < p.y;
    }
    int x, y, z;
};

struct sb
{
    sb(const pt &p1, const pt &p2)
    {
        if (p1 < p2)
        {
            from = p1;
            to = p2;
        }
        else
        {
            from = p2;
            to = p1;
        }
    }
    void fall_by(int by)
    {
        from.z -= by;
        to.z -= by;
    }
    bool operator<(const sb &s) const
    {
        if (from < s.from)
            return true;
        if (s.from < from)
            return false;
        return to < s.to;
    }
    bool overlaps(const sb &s) const
    {
        return !(s.to.x < from.x || s.from.x > to.x || s.to.y < from.y || s.from.y > to.y);
    }
    pt from, to;
    unordered_set<int> supported_by, supports;
};

static vs split(const string &s, char delim)
{
    vs result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        result.pb(item);
    return result;
}

static vector<sb> slabs, stable;

static int part1()
{
    vi isC;
    sort(slabs.begin(), slabs.end());
    for (sb s : slabs)
    {
        int high = 0;
        unordered_set<int> ss;
        for (size_t i = 0; i < stable.size(); ++i)
            if (stable[i].overlaps(s))
            {
                if (stable[i].to.z > high)
                {
                    high = stable[i].to.z;
                    ss = {static_cast<int>(i)};
                }
                else if (stable[i].to.z == high)
                    ss.insert(i);
            }
        int delta = s.from.z - high - 1;
        s.fall_by(delta);
        for (int i : ss)
            stable[i].supports.insert(stable.size());
        s.supported_by = ss;
        stable.pb(s);
        isC.pb(1);
    }
    for (size_t i = 0; i < stable.size(); ++i)
        if (stable[i].supported_by.size() == 1)
            isC[*stable[i].supported_by.cbegin()] = 0;
    return accumulate(isC.cbegin(), isC.cend(), 0);
}

static int part2()
{
    int p2 = 0;
    for (size_t i = 0; i < stable.size(); ++i)
    {
        unordered_set<int> ff = {static_cast<int>(i)}, check = stable[i].supports;
        int notC = -1;
        while (true)
        {
            for (int j : check)
            {
                int count = 0;
                for (const auto &s : stable[j].supported_by)
                    if (ff.find(s) != ff.end())
                        count++;
                if (count == static_cast<int>(stable[j].supported_by.size()))
                {
                    notC = j;
                    break;
                }
            }
            if (notC >= 0)
            {
                check.erase(notC);
                ff.insert(notC);
                for (int j : stable[notC].supports)
                    check.insert(j);
                notC = -1;
            }
            else
                break;
        }
        p2 += ff.size() - 1;
    }
    return p2;
}

int main()
{
    fo;
    fi;
    ifstream f("input.txt");
    string line;
    while (f >> line)
    {
        auto v1 = split(line, '~');
        auto v2 = split(v1[0], ',');
        auto v3 = split(v1[1], ',');
        slabs.emplace_back(pt(stoi(v2[0]), stoi(v2[1]), stoi(v2[2])),
                           pt(stoi(v3[0]), stoi(v3[1]), stoi(v3[2])));
    }
    cout
        << "Part 1: " << part1() << endl
        << "Part 2: " << part2() << endl;
}
