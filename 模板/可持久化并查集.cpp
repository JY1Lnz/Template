struct Persistant_Union_Set
{
#define MID (l+r)/2
#define N 200010

    int L[N*40], R[N*40], f[N*40], dep[N*40], rot[N];
    int tot, n;
    int build(int rt, int l, int r)
    {
        int node = ++tot;
        if (l == r){f[node] = l;return node;}
        L[node] = build(L[rt], l, MID);
        R[node] = build(R[rt], MID+1, r);
        return node;
    }
    void make(int n) // 建树
    {
        this->n = n;
        rot[0] = build(1, 1, n);
    }
    int qry(int rt, int l, int r, int p) // 查询p位置在树上的节点
    {
        // cout << l << ' ' << r << ' ' << p << ' ' << rt << ' ' << f[rt] << endl;
        if (l == r) return rt;
        if (p <= MID) return qry(L[rt], l, MID, p);
        else return qry(R[rt], MID+1, r, p);
    }
    int find(int rt, int x) // 找x的祖先, 返回对应节点:w
    {
        int p = qry(rt, 1, n, x);
        if (f[p] == x) return p;
        return find(rt, f[p]);
    }
    int merge(int rt, int l, int r, int p, int fa) // 合并
    {
        int node = ++tot;
        L[node] = L[rt], R[node] = R[rt], f[node] = f[rt], dep[node] = dep[rt];
        if (l == r)
        {
            f[node] = fa;
            dep[node] = dep[rt];
            return node;
        }
        if (p <= MID) L[node] = merge(L[rt], l, MID, p, fa);
        else R[node] = merge(R[rt], MID+1, r, p, fa);
        return node;
    }
    void upd(int rt, int l, int r, int p) // 按深度合并 所以需要更新整颗树的深度
    {
        if (l == r){dep[rt]++; return;}
        if (p <= MID) upd(L[rt], l, MID, p);
        else upd(R[rt], MID+1, r, p);
    }

#undef MID
#undef N
};