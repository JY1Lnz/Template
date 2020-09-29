const int MAXN = 1e6+10;

struct Node
{
    int ls, rs;
    int v;
}seg[MAXN*30];

int a[MAXN], rot[MAXN], n, m, tot;

int build(int rt, int l, int r)
{
    int new_node = ++tot;
    if (l == r)
    {
        seg[new_node].v = a[l];
        return new_node;
    }
    int mid = (l+r)/2;
    seg[new_node].ls = build(seg[rt].ls, l, mid);
    seg[new_node].rs = build(seg[rt].rs, mid+1, r);
    return new_node;
}

int upd(int rt, int l, int r, int p, int v)
{
    int new_node = ++tot;
    seg[new_node] = seg[rt];
    if (l == r)
    {
        seg[new_node].v = v;
        return new_node;
    }
    int mid = (l+r)/2;
    if (p <= mid) seg[new_node].ls = upd(seg[rt].ls, l, mid, p, v);
    else seg[new_node].rs = upd(seg[rt].rs, mid+1, r, p, v);
    return new_node;
}

int qry(int rt, int l, int r, int p)
{
    // cout << l << ' ' << r << endl;
    if (l == r) return seg[rt].v;
    int mid = (l+r)/2;
    if (p <= mid) return qry(seg[rt].ls, l, mid, p);
    else return qry(seg[rt].rs, mid+1, r, p);
}

int main()
{
IOS;
#ifdef LOCAL
    freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1;i <= n; ++i) scanf("%d", &a[i]);
    rot[0] = build(0, 1, n);
    int v, op, p, val;
    for (int i = 1;i <= m; ++i)
    {
        scanf("%d%d%d", &v, &op, &p);
        if (op == 1)
        {
            scanf("%d", &val);
            rot[i] = upd(rot[v], 1, n, p, val);
        }
        else
        {
            int ans;
            printf("%d\n", ans = qry(rot[v], 1, n, p));
            rot[i] = rot[v];
        }
        
    }

return 0;
}
