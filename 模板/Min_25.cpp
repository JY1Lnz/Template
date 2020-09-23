const int MAXN = 1e6+10;
typedef long long LL;

LL n, sqr, w[MAXN];
int inv2 = 500000004, inv6 = 166666668;
int tot, cnt;
int pri[MAXN], sp1[MAXN], sp2[MAXN], g1[MAXN], g2[MAXN];
// sp1, sp2. 质数和质数平方的前缀和, g1, g2质数部分p^2, p
int id1[MAXN], id2[MAXN];
bool isp[MAXN];

void pre(int n)
{
    // 初始化素数筛
    tot = 0;
    for (int i = 2;i <= n; ++i)
    {
        if (!isp[i]) pri[++tot] = i;
        for (int j = 1;j <= tot && (LL)i*pri[j] <= n; ++j)
        {
            isp[i*pri[j]] = 1;
            if (i%pri[j] == 0) break;
        }
    }
    for (int i = 1;i <= tot; ++i)
    {
        sp1[i] = ((LL)sp1[i-1]+pri[i])%MOD;
        sp2[i] = ((LL)sp2[i-1]+1LL*pri[i]*pri[i]%MOD)%MOD;
    }
}

int getid(LL x)
{
    if (x <= sqr) return id1[x];
    return id2[n/x];
}

int f1(LL x)
{
    x %= MOD;
    return 1LL*x*(x+1)%MOD*inv2%MOD;
}

int f2(LL x)
{
    x %= MOD;
    return 1LL*x*(x+1)%MOD*(2LL*x+1)%MOD*inv6%MOD;
}

LL s(LL v, int j)
{
    if (pri[j] >= v) return 0;
    LL ans = ((LL)g2[getid(v)]-g1[getid(v)]-(sp2[j]-sp1[j])+2LL*MOD)%MOD;
    for (int i = j+1;i <= tot && 1LL*pri[i]*pri[i] <= v; ++i)
    {
        for (LL e = 1, tmp = pri[i]; tmp <= v; tmp = tmp * pri[i], ++e)
            ans = (ans + tmp%MOD*(tmp%MOD-1+MOD)%MOD*(s(v/tmp, i)+(e>1))%MOD)%MOD;
    }
    return ans;
}

int cal()
{
    cnt = 0;
    for (LL l = 1,r;l <= n;l = r+1)
    {
        r = n/(n/l);
        w[++cnt] = n/l;
        g1[cnt] = (f1(w[cnt])-1+MOD)%MOD;
        g2[cnt] = (f2(w[cnt])-1+MOD)%MOD;
        if (w[cnt] <= sqr) id1[w[cnt]] = cnt;
        else id2[n/w[cnt]] = cnt;
    }
    for (int i = 1;i <= tot; ++i)
    {
        for (int j = 1;j <= cnt && 1LL*pri[i]*pri[i] <= w[j]; ++j)
        {
            g1[j] = ((LL)g1[j]-(LL)pri[i]*((LL)g1[getid(w[j]/pri[i])]-sp1[i-1]+MOD)%MOD+MOD)%MOD;
            g2[j] = ((LL)g2[j]-(LL)pri[i]*pri[i]%MOD*((LL)g2[getid(w[j]/pri[i])]-sp2[i-1]+MOD)%MOD+MOD)%MOD;
        }
    }
    return (s(n, 0)+1)%MOD;
}

int main()
{
IOS;
#ifdef LOCAL
    freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
#endif
    scanf("%lld", &n);
    sqr = sqrt(n+0.5);
    pre(sqr);
    printf("%d\n", cal());
    
    return 0;
}