const int MAXN = 1e5;
struct Splay
{
#define root e[0].ch[1]
    struct Node
    {
        int v, fa;
        int ch[2] = {0, 0};
        int sum;
        int rec;
    };
    Node e[MAXN];
    int n;
    void update(int x)
    {
        e[x].sum = e[e[x].ch[0]].sum+e[e[x].ch[1]].sum+e[x].rec;
    }
    int id(int x)
    {
        return e[e[x].fa].ch[0] == x ? 0: 1;
    }
    inline void connect(int x, int y, int p) // x连到y的p儿子上
    {
        e[x].fa = y;
        e[y].ch[p] = x;
    }
    inline void rotate(int x)
    {
        int fa = e[x].fa;
        int gfa = e[fa].fa;
        int px = id(x), py = id(fa);
        connect(e[x].ch[px^1], fa, px);
        connect(fa, x, px^1);
        connect(x, gfa, py);
        update(fa);
        update(x);
    }
    inline void splay(int src, int dec)
    {
        dec = e[dec].fa;
        while(e[src].fa != dec)
        {
            int up = e[src].fa;
            if (e[up].fa == dec) rotate(src);
            else
            {
                if (id(src) == id(up))
                {
                    rotate(up);
                    rotate(src);
                }
                else
                {
                    rotate(src);
                    rotate(src);
                }
            }
        }
    }
    int crepoint(int v, int fa)
    {
        ++n;
        e[n].v = v;
        e[n].fa = fa;
        e[n].rec = 1;
        e[n].sum = 1;
        return n;
    }
    int getroot(){return root;}
    int find(int v)
    {
        int now = root;
        while (true)
        {
            if (e[now].v == v)
            {
                splay(now, root);
                return now;
            }
            int nxt = v < e[now].v ? 0 : 1;
            if (!e[now].ch[nxt]) return 0;
            now = e[now].ch[nxt];
        }
    }
    void insert(int v)
    {
        int now = root;
        if (root == 0)
        {
            int p = crepoint(v, 0);
            root = p;
            return;
        }
        while (true)
        {
            e[now].sum++;
            if (e[now].v == v)
            {
                e[now].rec++;
                splay(now, root);
                return;
            }
            int nxt = v < e[now].v ? 0: 1;
            if (!e[now].ch[nxt])
            {
                int p = crepoint(v, 0);
                e[now].ch[nxt] = p;
                e[p].fa = now;
                splay(p, now);
                return;
            }
            now = e[now].ch[nxt];
        }
    }
    void delet(int v) // 删除节点
    {
        int deal = find(v);
        if (!deal) return;
        if (e[deal].rec > 1)
        {
            --e[deal].sum;
            --e[deal].rec;
            return;
        }
        if (!e[deal].ch[0] && !e[deal].ch[1])
            root = 0;
        else if (!e[deal].ch[0])
        {
            root = e[deal].ch[1];
            e[root].fa = 0;
        }
        else
        {
            int lef = e[deal].ch[0];
            while (e[lef].ch[1]) lef = e[lef].ch[1];
            splay(lef, e[deal].ch[0]);
            int rig = e[deal].ch[1];
            connect(rig, lef, 1);
            connect(lef, 0, 1);
            update(lef);
        }
    }
    int rank(int v) // v值的排序
    {
        int ans = 0, now = root;
        while (true)
        {
            if (now == 0) return 0;
            if (e[now].v == v)
            {
                int tmp = ans+e[e[now].ch[0]].sum+1;
                splay(now, root);
                return tmp;
            }
            if (v < e[now].v) now = e[now].ch[0];
            else
            {
                ans += e[e[now].ch[0]].sum+e[now].rec;
                now = e[now].ch[1];
            }
        }
    }
    int atrank(int x) // 排在x位的元素
    {
        int now = root;
        while (true)
        {
            if (now == 0) return 0;
            int tmp = e[now].sum-e[e[now].ch[1]].sum;
            if (x > e[e[now].ch[0]].sum && x <= tmp) break;
            if (x < tmp) now = e[now].ch[0];
            else
            {
                x -= tmp;
                now = e[now].ch[1];
            }
        }
        splay(now, root);
        return e[now].v;
    }
    int upper(int v) // 后继
    {
        int res = INF;
        int now = root;
        while (now)
        {
            if (e[now].v > v && e[now].v < res) res = e[now].v;
            if (v < e[now].v) now = e[now].ch[0];
            else now = e[now].ch[1];
        }
        return res;
    }
    int lower(int v) // 前驱
    {
        int res = -INF;
        int now = root;
        while (now)
        {
            if (e[now].v < v && e[now].v > res) res = e[now].v;
            if (v > e[now].v) now = e[now].ch[1];
            else now = e[now].ch[0];
        }
        return res;
    }
#undef root
};