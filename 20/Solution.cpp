/// This is giving WA for some reason :(
// will debug later
// You can use python code for the meantime in the same folder
// run it with
// python3 20.py input.txt
/// Thanks!

// #include <bits/stdc++.h>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
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

using namespace std;

enum mod_type
{
    none,
    flop,
    conj
};

struct module_t
{
    mod_type type = none;
    bool on;
    vs dests;
    unordered_map<string, bool> inputs;
};

struct pulse_t
{
    string from, to;
    bool high;
};

static deque<pulse_t> pulse_q;
static uint64_t low_cnt, high_cnt, pulse_cnt;
static unordered_map<string, module_t> modules;
static unordered_map<string, uint64_t> cycles;

static vs split(const string &s, char delim)
{
    vs result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        result.pb(item);
    return result;
}

static void send_pulse()
{
    pulse_q.pb({"button", "broadcaster", false});
    while (!pulse_q.empty())
    {
        pulse_t &p = pulse_q.front();
        pulse_q.pop_front();
        if (p.high)
            high_cnt++;
        else
            low_cnt++;
        auto modii = modules.find(p.to);
        if (modii != modules.cend())
        {
            module_t &m = modii->second;
            switch (m.type)
            {
            case none:
                for (auto &d : m.dests)
                    pulse_q.pb({p.to, d, p.high});
                break;
            case flop:
                if (!p.high)
                {
                    m.on = !m.on;
                    for (auto &d : m.dests)
                        pulse_q.pb({p.to, d, m.on});
                }
                break;
            case conj:
                auto iter = m.inputs.find(p.from);
                if (iter != m.inputs.cend())
                    iter->second = p.high;
                bool all_hi = true;
                for (auto &[_, high] : m.inputs)
                    all_hi = all_hi && high;
                if (!all_hi)
                {
                    auto iter = cycles.find(p.to);
                    if (iter != cycles.cend() && iter->second == 0)
                        iter->second = pulse_cnt;
                }
                for (auto &d : m.dests)
                    pulse_q.pb({p.to, d, !all_hi});
            }
        }
    }
}

int main()
{
    ifstream f("input.txt");
    string line, rx_mod;
    vs conjs;
    while (getline(f, line))
    {
        auto v = split(line, ' ');
        string name = v[0], out;
        stringstream ss(v[2]);
        module_t m;
        for (size_t i = 2; i < v.size(); i++)
        {
            out = v[i].back() == ',' ? v[i].substr(0, v[i].size() - 1) : v[i];
            m.dests.pb(out);
            if (out == "rx")
                rx_mod = name.substr(1);
        }
        if (name[0] == '%')
        {
            name = name.substr(1);
            m.type = flop;
            m.on = false;
        }
        else if (name[0] == '&')
        {
            name = name.substr(1);
            m.type = conj;
            conjs.pb(name);
        }
        modules[name] = m;
    }
    sort(conjs.begin(), conjs.end());
    for (auto &[name, m] : modules)
        for (const string &s : m.dests)
            if (binary_search(conjs.cbegin(), conjs.cend(), s))
                modules[s].inputs[name] = false;
    uint64_t part1 = 0, part2 = 1;
    low_cnt = high_cnt = pulse_cnt = 0;
    for (auto &[input, _] : modules[rx_mod].inputs)
        cycles[input] = 0;
    bool has0;
    do
    {
        pulse_cnt++;
        send_pulse();
        if (pulse_cnt == 1000)
            part1 = low_cnt * high_cnt;
        has0 = false;
        for (auto &[_, cycle] : cycles)
            has0 = has0 || !cycle;
    } while (has0);
    for (auto &[_, cycle] : cycles)
        part2 = lcm(part2, cycle);
    cout
        << "Part 1: " << part1 << endl
        << "Part 2: " << part2 << endl;
}
