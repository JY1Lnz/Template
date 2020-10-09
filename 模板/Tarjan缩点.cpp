const int MAXN = 1e3+1;

vector<int> G[MAXN];
int n, pre[MAXN], lowlink[MAXN], sccno[MAXN], dfs_clock, scc_cnt;
stack<int> s;

void dfs(int u)
{
    pre[u] = lowlink[u] = ++dfs_clock;
    s.push(u);
    for (auto v: G[u])
    {
        if (!pre[v])
        {
            dfs(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        }
        else if (!sccno[v])
        {
            lowlink[u] = min(lowlink[u], pre[v]);
        }
    }
    if (lowlink[u] == pre[u])
    {
        ++scc_cnt;
        for(;;)
        {
            int x = s.top(); s.pop();
            sccno[x] = scc_cnt;
            if (x == u) break;
        }
    }
}

void find_scc(int n)
{
    dfs_clock = scc_cnt = 0 ;
    memset(sccno, 0, sizeof(sccno));
    memset(pre, 0, sizeof(pre));
    while (!s.empty())
        s.pop();
    
    for (int i = 1;i <= n; ++i) if (!pre[i]) dfs(i);
}