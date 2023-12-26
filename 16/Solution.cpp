#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define vvi vector<vi>
#define vc vector<char>
#define vs vector<string>
#define pb push_back
#define test     \
    ll temp;     \
    cin >> temp; \
    while (temp--)
#define mod 1000000007
#define fo ios_base::sync_with_stdio(false);
#define fi cin.tie(NULL);

enum directions
{
    RIGHT,
    DOWN,
    LEFT,
    UP
};

struct beam_t
{
    int x, y;
    directions d;
};

static list<beam_t> beams[4];
static vs grid;

static uint32_t energy(list<beam_t> &beams, beam_t start_beam)
{
    const vector<uint8_t> visited_row(grid[0].size(), 0);
    vector<vector<uint8_t>> visited(grid.size(), visited_row);
    beams.pb(start_beam);
    while (beams.size())
    {
        beam_t beam = beams.front();
        beams.pop_front();
        if (!(visited[beam.y][beam.x] & (1 << beam.d)))
        {
            visited[beam.y][beam.x] |= 1 << beam.d;
            switch (grid[beam.y][beam.x])
            {
            case '.':
                if (beam.d == RIGHT && beam.x < static_cast<int>(grid[0].size()) - 1)
                    beams.pb({beam.x + 1, beam.y, beam.d});
                else if (beam.d == LEFT && beam.x > 0)
                    beams.pb({beam.x - 1, beam.y, beam.d});
                else if (beam.d == DOWN && beam.y < static_cast<int>(grid.size()) - 1)
                    beams.pb({beam.x, beam.y + 1, beam.d});
                else if (beam.d == UP && beam.y > 0)
                    beams.pb({beam.x, beam.y - 1, beam.d});
                break;
            case '/':
                if (beam.d == UP && beam.x < static_cast<int>(grid[0].size()) - 1)
                    beams.pb({beam.x + 1, beam.y, RIGHT});
                else if (beam.d == DOWN && beam.x > 0)
                    beams.pb({beam.x - 1, beam.y, LEFT});
                else if (beam.d == LEFT && beam.y < static_cast<int>(grid.size()) - 1)
                    beams.pb({beam.x, beam.y + 1, DOWN});
                else if (beam.d == RIGHT && beam.y > 0)
                    beams.pb({beam.x, beam.y - 1, UP});
                break;
            case '\\':
                if (beam.d == DOWN && beam.x < static_cast<int>(grid[0].size()) - 1)
                    beams.pb({beam.x + 1, beam.y, RIGHT});
                else if (beam.d == UP && beam.x > 0)
                    beams.pb({beam.x - 1, beam.y, LEFT});
                else if (beam.d == RIGHT && beam.y < static_cast<int>(grid.size()) - 1)
                    beams.pb({beam.x, beam.y + 1, DOWN});
                else if (beam.d == LEFT && beam.y > 0)
                    beams.pb({beam.x, beam.y - 1, UP});
                break;
            case '-':
                if (beam.d == RIGHT && beam.x < static_cast<int>(grid[0].size()) - 1)
                    beams.pb({beam.x + 1, beam.y, RIGHT});
                else if (beam.d == LEFT && beam.x > 0)
                    beams.pb({beam.x - 1, beam.y, LEFT});
                else if (beam.d == DOWN || beam.d == UP)
                {
                    if (beam.x < static_cast<int>(grid[0].size()) - 1)
                        beams.pb({beam.x + 1, beam.y, RIGHT});
                    if (beam.x > 0)
                        beams.pb({beam.x - 1, beam.y, LEFT});
                }
                break;
            case '|':
                if (beam.d == DOWN && beam.y < static_cast<int>(grid.size()) - 1)
                    beams.pb({beam.x, beam.y + 1, DOWN});
                else if (beam.d == UP && beam.y > 0)
                    beams.pb({beam.x, beam.y - 1, UP});
                else if (beam.d == RIGHT || beam.d == LEFT)
                {
                    if (beam.y < static_cast<int>(grid.size()) - 1)
                        beams.pb({beam.x, beam.y + 1, DOWN});
                    if (beam.y > 0)
                        beams.pb({beam.x, beam.y - 1, UP});
                }
                break;
            }
        }
    }
    int count = 0;
    for (auto &row : visited)
        for (auto c : row)
            if (c)
                count++;
    return count;
}

static uint32_t sides[4];

void temp(size_t i)
{
    uint32_t p2 = 0;
    switch (i)
    {
    case 0:
        for (int i = 0; i < static_cast<int>(grid.size()); i++)
            p2 = max(energy(beams[0], {0, static_cast<int>(i), RIGHT}), p2);

        break;
    case 1:
        for (int i = 0; i < static_cast<int>(grid.size()); i++)
            p2 = max(energy(beams[1], {int(grid.size() - 1), static_cast<int>(i), LEFT}), p2);
        break;
    case 2:
        for (size_t i = 0; i < grid[0].size(); i++)
            p2 = max(energy(beams[2], {static_cast<int>(i), 0, DOWN}), p2);
        break;
    case 3:
        for (size_t i = 0; i < grid[0].size(); i++)
            p2 = max(energy(beams[3], {static_cast<int>(i), int(grid[0].size() - 1), UP}), p2);
        break;
    }
    sides[i] = p2;
}

int main()
{
    fo;
    fi;
    ifstream f("input.txt");
    string line;
    while (getline(f, line))
        grid.pb(line);
    uint32_t part1 = energy(beams[0], {0, 0, RIGHT}), part2 = 0;
    thread *threads[4];
    for (int i = 0; i < 4; i++)
        threads[i] = new thread(temp, i);
    for (int i = 0; i < 4; i++)
    {
        threads[i]->join();
        part2 = max(part2, sides[i]);
    }
    cout
        << "Part 1: " << part1 << endl
        << "Part 2: " << part2 << endl;
}
