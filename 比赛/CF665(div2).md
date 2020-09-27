# Codeforces Round #665 (Div. 2)
## A
## B
## C
这题没想到，排序之后挨个比较， 对于不在需要在的位置上的值，如果不是$Min\{A\}$的倍数，说明不能通过几次交换变成需要位置。
## D
计算每条边会经过多少次，排个序，大质数配经过次数多的值，质数更多则前几个相乘去最大化，较少则后面多放1.  
因为取模没改在那wa疯了。

```
#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<string.h>
#include<cstring>
#include<set>
#include<queue>
#include<algorithm>
#include<math.h>
#include<stdio.h>
#include<map>
#include<stack>
#include<list>
#include<assert.h>
#define pii pair<int, int>
#define pll pair<LL, LL>
#define pil pair<int, LL>
#define pli pair<LL, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define MINF 0x3f3f3f3f
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL LLINF = 1e18;
const int INF = 1e9;
const int MOD = 1e9+7;
const int HMOD = 999959;
const int VMOD = 5000000;
const int MAXN = 1e5+10;
const int MAXM = 5e5+10;
const int INV = 10050505;
const LL LLINV = 1e18;
const double eps = 1e-3;
int dirx[5] = {0, -1, 1, 0, 0}, diry[5] = {0, 0, 0, -1, 1};

int n, m, tot;
vector<int> G[MAXN];
LL e[MAXN];
int sz[MAXN], p[MAXN];

void dfs(int u, int fa)
{
    sz[u] = 0;
    for (auto v: G[u]) if (v != fa)
    {
        dfs(v, u);
        e[++tot] = (LL)sz[v]*(n-sz[v]);
        sz[u] += sz[v];
    }
    sz[u]++;
}

void solve()
{
    scanf("%d", &n);
    for (int i = 1;i <= n; ++i) G[i].clear();
    for (int i = 1, x, y;i < n; ++i) 
    {
        scanf("%d%d", &x, &y);
        G[x].pb(y);
        G[y].pb(x);
    }
    tot = 0;
    dfs(1, 0);
    scanf("%d", &m);
    for (int i = 1;i <= m; ++i) scanf("%d", &p[i]);
    sort(p+1, p+1+m, greater<int>());
    sort(e+1, e+1+n-1, greater<LL>());
    // for (int i = 1;i <= m; ++i) cout << p[i] << endl;
    LL ans = 0;
    if (m <= n-1)
    {
        for (int i = 1;i < n; ++i)
        {
            if (i <= m) ans = (ans + e[i]%MOD*p[i]%MOD)%MOD;
            else ans = (ans + e[i]%MOD)%MOD;
        }
    }
    else
    {
        LL tmp = 1;
        for (int i = 1;i <= m-(n-2); ++i) tmp = tmp*p[i]%MOD;
        ans = tmp*(e[1]%MOD)%MOD;
        for (int i = 2, j = m-(n-2)+1;i <= n-1;++i, ++j)
            ans = (ans + e[i]%MOD*p[j]%MOD)%MOD;
    }
    printf("%lld\n", ans);
}

int main()
{
IOS;
#ifdef LOCAL
    freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while(T--) solve();


return 0;
}
```

# E
可以发现交点数和分割整个图形的线段都能产生$1$的贡献。（不会证明）  
就可以把竖着的从下到上记录是否存在，起点增加$1$，终点减少$1$，横着的用树状数组查个区间和。  

```c++
#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<string.h>
#include<cstring>
#include<set>
#include<queue>
#include<algorithm>
#include<math.h>
#include<stdio.h>
#include<map>
#include<stack>
#include<list>
#include<assert.h>
#define pii pair<int, int>
#define pll pair<LL, LL>
#define pil pair<int, LL>
#define pli pair<LL, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define MINF 0x3f3f3f3f
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL LLINF = 1e18;
const int INF = 1e9;
const int MOD = 998244353;
const int HMOD = 999959;
const int VMOD = 5000000;
const int MAXN = 1e6+10;
const int MAXM = 5e5+10;
const int INV = 10050505;
const LL LLINV = 1e18;
const double eps = 1e-3;
int dirx[5] = {0, -1, 1, 0, 0}, diry[5] = {0, 0, 0, -1, 1};

int c[MAXN], up = 1e6+1;

int lowbit(int x)
{
    return x&-x;
}

void upd(int x,int v)
{
    while(x <= up)
    {
        c[x] += v;
        x += lowbit(x);
    }
}

int qry(int x)
{
    int ans = 0;
    while(x > 0)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}

vector<pii> p[MAXN];
vector<int> v[MAXN];
int n, m;

int main()
{
IOS;
#ifdef LOCAL
    freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    LL ans = 1;
    for (int i = 1, x, y, z;i <= n; ++i)
    {
        scanf("%d%d%d", &x, &y, &z);
        x++;y++;z++;
        p[x].emplace_back(y, z);
        if (y == 1 && z == up) ++ans;
    }
    for (int i = 1, x, y, z;i <= m; ++i)
    {
        scanf("%d%d%d", &x, &y, &z);
        x++;y++;z++;
        v[y].pb(x);
        v[z+1].pb(-x);
        if (y == 1 && z == up) ++ans;
    }
    for (int i = 1;i <= up; ++i)
    {
        for (auto x: v[i]) upd(abs(x), x > 0 ? 1 : -1);
        for (auto pi: p[i]) ans += qry(pi.se)-qry(pi.fi-1);
    }
    printf("%lld\n", ans);

    return 0;
}
```

# F
裸数据结构，线段树增加了区间反转和交换。 反转操作就是将某一层的下面的全部节点全部左右孩子交换，交换只是单层交换。  
最开始用线段树一层一层去找这个位置，写完单次是$nlog(n)$的，之后可以发现，每次都是一整层，所以可以单独维护一整层的反转情况，查询的时候左右孩子修改一下。  
```c++
#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<string.h>
#include<cstring>
#include<set>
#include<queue>
#include<algorithm>
#include<math.h>
#include<stdio.h>
#include<map>
#include<stack>
#include<list>
#include<assert.h>
#define pii pair<int, int>
#define pll pair<LL, LL>
#define pil pair<int, LL>
#define pli pair<LL, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define MINF 0x3f3f3f3f
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL LLINF = 1e18;
const int INF = 1e9;
const int MOD = 998244353;
const int HMOD = 999959;
const int VMOD = 5000000;
const int MAXN = 1e6+10;
const int MAXM = 5e5+10;
const int INV = 10050505;
const LL LLINV = 1e18;
const double eps = 1e-3;
int dirx[5] = {0, -1, 1, 0, 0}, diry[5] = {0, 0, 0, -1, 1};

struct Node
{
    int ls, rs;
    int ols, ors;
    int cel;
    LL sum;
}seg[MAXN*4];
int srev[20];
int n, q, a[MAXN];

void build(int rt, int l, int r)
{
    seg[rt].ls = seg[rt].ols = rt<<1;
    seg[rt].rs = seg[rt].ors = rt<<1|1;
    if (l == r)
    {
        seg[rt].sum = a[l];
        seg[rt].cel = 0;
        return;
    }
    int mid = (l+r)/2;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
    seg[rt].sum = seg[rt<<1].sum+seg[rt<<1|1].sum;
    seg[rt].cel = seg[rt<<1].cel+1;
}

void pp(int rt)
{
    seg[rt].sum = seg[seg[rt].ls].sum + seg[seg[rt].rs].sum;
}

void pd(int rt)
{
    if (srev[seg[rt].cel])
    {
        seg[rt].ls = seg[rt].ors;
        seg[rt].rs = seg[rt].ols;
    }
    else
    {
        seg[rt].ls = seg[rt].ols;
        seg[rt].rs = seg[rt].ors;
    }
    
}

void upd(int rt, int l, int r, int p, int v)
{
    if (l == r)
    {
        seg[rt].sum = v;
        return;
    }
    pd(rt);
    int mid = (l+r)/2;
    if (p <= mid) upd(seg[rt].ls, l, mid, p, v);
    else upd(seg[rt].rs, mid+1, r, p, v);
    pp(rt);
}

LL qry(int rt, int l, int r, int ql, int qr)
{
    // cout << l << ' ' << r << ' ' << rt << ' ' << seg[rt].ls << ' ' << seg[rt].rs << endl;
    if (ql <= l && r <= qr) return seg[rt].sum;
    pd(rt);
    int mid = (l+r)/2;
    LL ans = 0;
    // cout << mid << endl;
    if (ql <= mid) ans += qry(seg[rt].ls, l, mid, ql, qr);
    if (qr > mid) ans += qry(seg[rt].rs, mid+1, r, ql, qr);
    pp(rt);
    return ans;
}

int main()
{
IOS;
#ifdef LOCAL
    freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
#endif
    scanf("%d%d", &n, &q);
    for (int i = 1;i <= (1<<n); ++i) scanf("%d", &a[i]);
    int op, x, y;
    build(1, 1, 1<<n);
    while(q--)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d%d", &x, &y);
            upd(1, 1, 1<<n, x, y);
        }
        if (op == 2)
        {
            scanf("%d", &x);
            for (int i = 0;i <= x; ++i) srev[i] ^= 1;
        }
        if (op == 3)
        {
            scanf("%d", &x);
            srev[x+1] ^= 1;
        }
        if (op == 4)
        {
            scanf("%d%d", &x, &y);
            // cout << "qry:" << endl;
            printf("%lld\n", qry(1, 1, 1<<n, x, y));
        }
    }

    return 0;
}
```