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
    vs result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        result.pb(item);
    return result;
}

static unsigned char hash_string(string instruction)
{
    unsigned char result = 0;
    for (unsigned char c : instruction)
        result = (result + c) * 17;
    return result;
}

static unsigned int part1(vs &instructions)
{
    unsigned int sum = 0;
    for (auto &instruction : instructions)
        sum += hash_string(instruction);
    return sum;
}

template <class InputIt, class UnaryPredicate>
constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
{
    for (; first != last; ++first)
        if (p(*first))
            return first;
    return last;
}

template <class ForwardIt, class UnaryPredicate>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
    first = find_if(first, last, p);
    if (first != last)
        for (ForwardIt i = first; ++i != last;)
            if (!p(*i))
                *first++ = move(*i);
    return first;
}

static int part2(vs &instructions)
{
    vector<vector<pair<string, int>>> boxes(256);
    for (auto &instruction : instructions)
        if (instruction.find("-") != string::npos)
        {
            string label = instruction.substr(0, instruction.size() - 1);
            vector<pair<string, int>> &box = boxes[hash_string(label)];
            auto last = std::remove_if(box.begin(), box.end(), [&label](const pair<string, int> &p)
                                       { return p.first == label; });

            box.erase(last, box.end());
        }
        else
        {
            int found = instruction.find('=');
            string label = instruction.substr(0, found);
            int level = stoi(instruction.substr(found + 1));
            vector<pair<string, int>> &box = boxes[hash_string(label)];
            bool replaced = false;
            for (auto &b : box)
                if (b.first == label)
                {
                    b.second = level;
                    replaced = true;
                }
            if (!replaced)
                box.pb({label, level});
        }
    int sum = 0;
    for (size_t i = 0; i < boxes.size(); i++)
        for (size_t j = 0; j < boxes[i].size(); j++)
            sum += (i + 1) * (j + 1) * boxes[i][j].second;
    return sum;
}

int main()
{
    fo;
    fi;
    ifstream f("input.txt");
    string line;
    getline(f, line);
    vs instructions = split(line, ',');
    cout
        << "Part 1: " << part1(instructions) << endl
        << "Part 2: " << part2(instructions) << endl;
}
