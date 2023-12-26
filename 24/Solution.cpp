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
struct helperTwo
{
    double x, y, z;
    bool operator==(const helperTwo &a) const { return x == a.x && y == a.y && z == a.z; }
};

struct helper
{
    helperTwo pos, vel;
    bool operator==(const helper &a) const
    {
        return pos == a.pos && vel == a.vel;
    }
};

static vector<helper> stones;

static int partOne()
{
    const double minArea = 200000000000000, maxArea = 400000000000000;
    int res = 0;
    for (size_t i = 0; i < stones.size() - 1; i++)
    {
        for (size_t j = i + 1; j < stones.size(); j++)
        {
            auto &si = stones[i];
            auto &sj = stones[j];
            double det = (si.vel.x * sj.vel.y - si.vel.y * sj.vel.x);
            if (det == 0)
                continue;
            double u = (sj.vel.x * (si.pos.y - sj.pos.y) +
                        sj.vel.y * (sj.pos.x - si.pos.x)) /
                       det;
            double t = (si.vel.x * (si.pos.y - sj.pos.y) +
                        si.vel.y * (sj.pos.x - si.pos.x)) /
                       det;
            if (u < 0 || t < 0)
                continue;
            double x = sj.pos.x + sj.vel.x * t;
            double y = sj.pos.y + sj.vel.y * t;
            if (x >= minArea && x <= maxArea && y >= minArea && y <= maxArea)
                res++;
        }
    }
    return res;
}

static int64_t partTwo()
{
    int stone0_ix = 0, stone1_ix = 1;
    while (stones[stone0_ix].vel == stones[stone1_ix].vel)
        stone1_ix++;
    int stone2_ix = stone1_ix + 1;
    while (stones[stone0_ix].vel == stones[stone2_ix].vel ||
           stones[stone1_ix].vel == stones[stone2_ix].vel)
        stone2_ix++;
    double vx0 = stones[stone0_ix].vel.x;
    double vy0 = stones[stone0_ix].vel.y;
    double vz0 = stones[stone0_ix].vel.z;
    double vx1 = stones[stone1_ix].vel.x;
    double vy1 = stones[stone1_ix].vel.y;
    double vz1 = stones[stone1_ix].vel.z;
    double vx2 = stones[stone2_ix].vel.x;
    double vy2 = stones[stone2_ix].vel.y;
    double vz2 = stones[stone2_ix].vel.z;
    double abvx = vx0 - vx1;
    double abvy = vy0 - vy1;
    double abvz = vz0 - vz1;
    double acvx = vx0 - vx2;
    double acvy = vy0 - vy2;
    double acvz = vz0 - vz2;
    double abx = stones[stone0_ix].pos.x - stones[stone1_ix].pos.x;
    double aby = stones[stone0_ix].pos.y - stones[stone1_ix].pos.y;
    double abz = stones[stone0_ix].pos.z - stones[stone1_ix].pos.z;
    double acx = stones[stone0_ix].pos.x - stones[stone2_ix].pos.x;
    double acy = stones[stone0_ix].pos.y - stones[stone2_ix].pos.y;
    double acz = stones[stone0_ix].pos.z - stones[stone2_ix].pos.z;
    double h0 = (stones[stone1_ix].pos.y * vx1 - stones[stone1_ix].pos.x * vy1) -
                (stones[stone0_ix].pos.y * vx0 - stones[stone0_ix].pos.x * vy0);
    double h1 = (stones[stone2_ix].pos.y * vx2 - stones[stone2_ix].pos.x * vy2) -
                (stones[stone0_ix].pos.y * vx0 - stones[stone0_ix].pos.x * vy0);
    double h2 = (stones[stone1_ix].pos.x * vz1 - stones[stone1_ix].pos.z * vx1) -
                (stones[stone0_ix].pos.x * vz0 - stones[stone0_ix].pos.z * vx0);
    double h3 = (stones[stone2_ix].pos.x * vz2 - stones[stone2_ix].pos.z * vx2) -
                (stones[stone0_ix].pos.x * vz0 - stones[stone0_ix].pos.z * vx0);
    double h4 = (stones[stone1_ix].pos.z * vy1 - stones[stone1_ix].pos.y * vz1) -
                (stones[stone0_ix].pos.z * vy0 - stones[stone0_ix].pos.y * vz0);
    double h5 = (stones[stone2_ix].pos.z * vy2 - stones[stone2_ix].pos.y * vz2) -
                (stones[stone0_ix].pos.z * vy0 - stones[stone0_ix].pos.y * vz0);
    double pxx = acvx * abz - abvx * acz;
    double pyy = acvy * abx - abvy * acx;
    double pzz = acvz * aby - abvz * acy;
    double pxz = abvx * acx - acvx * abx;
    double pzy = abvz * acz - acvz * abz;
    double pyx = abvy * acy - acvy * aby;
    double pxc = abvx * h3 - acvx * h2;
    double pyc = abvy * h1 - acvy * h0;
    double pzc = abvz * h5 - acvz * h4;
    double pxd = acvx * abvz - abvx * acvz;
    double pyd = acvy * abvx - abvy * acvx;
    double pzd = acvz * abvy - abvz * acvy;
    double qz0 = (abvy / pxd) * pxz;
    double qx0 = (abvy / pxd) * pxx - (abvx / pyd) * pyx - aby;
    double qy0 = abx - (abvx / pyd) * pyy;
    double r0 = h0 - (abvy / pxd) * pxc + (abvx / pyd) * pyc;
    double qy1 = (abvx / pzd) * pzy;
    double qz1 = (abvx / pzd) * pzz - (abvz / pxd) * pxz - abx;
    double qx1 = abz - (abvz / pxd) * pxx;
    double r1 = h2 - (abvx / pzd) * pzc + (abvz / pxd) * pxc;
    double qx2 = (abvz / pyd) * pyx;
    double qy2 = (abvz / pyd) * pyy - (abvy / pzd) * pzy - abz;
    double qz2 = aby - (abvy / pzd) * pzz;
    double r2 = h4 - (abvz / pyd) * pyc + (abvy / pzd) * pzc;
    double qz = ((qx1 * qy0 - qx0 * qy1) * (qx2 * r0 - qx0 * r2) -
                 (qx2 * qy0 - qx0 * qy2) * (qx1 * r0 - qx0 * r1)) /
                ((qx2 * qy0 - qx0 * qy2) * (qx0 * qz1 - qx1 * qz0) -
                 (qx1 * qy0 - qx0 * qy1) * (qx0 * qz2 - qx2 * qz0));
    double qy = ((qx0 * qz1 - qx1 * qz0) * qz + (qx1 * r0 - qx0 * r1)) / (qx1 * qy0 - qx0 * qy1);
    double qx = (r0 - qy0 * qy - qz0 * qz) / qx0;
    double px = (pxz * qz + pxx * qx + pxc) / pxd;
    double py = (pyx * qx + pyy * qy + pyc) / pyd;
    double pz = (pzy * qy + pzz * qz + pzc) / pzd;
    return round(px) + round(py) + round(pz);
}

int main()
{
    fo;
    fi;
    ifstream f("input.txt");
    string line;
    helper s;
    char c;
    while (f >> s.pos.x)
    {
        f >> c >> s.pos.y >> c >> s.pos.z;
        f >> c >> s.vel.x >> c >> s.vel.y >> c >> s.vel.z;
        stones.pb(s);
    }
    cout
        << "part 1: " << partOne() << endl
        << "part 2: " << partTwo() << endl;
}
