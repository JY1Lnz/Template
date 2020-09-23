// lx -> linkx[] 左边点匹配的右边的点 -1 表示未匹配， ly同理
// dx 在bfs中， 到x点的匹配路径长度，
// HK算法用来优化匈牙利算法找增广路， 一次性可以找多个，并且要满足条件
bool bfs()
{
	queue<int> que;
	for (int i = 1;i <= cnt1; ++i) dx[i] = -1;
	for (int i = 1;i <= cnt2; ++i) dy[i] = -1;
	for (int i = 1;i <= cnt1; ++i)
	{
		if (lx[i] == -1)
		{
			que.push(i);
			dx[i] = 0;
		}
	}
	dis = INF;
	// cout << "bfs" << endl;
	while (!que.empty())
	{
		int u = que.front(); que.pop();
		// cout << "bfs: " << u << ' ' << dx[u] << ' ' << dis << endl;
		if (dx[u] > dis) break;
		for (int i = fir[u]; ~i; i = e[i].nxt)
		{
			int v = e[i].v;
			// cout << v << ' ' << dy[v] << ' ' << ly[v] << endl;
			if (dy[v] == -1)
			{
				dy[v] = dx[u]+1;
				if (ly[v] == -1) dis = dy[v];
				else 
				{
					dx[ly[v]] = dy[v]+1;
					que.push(ly[v]);
				}
			}
		}
	}
	return dis != INF;
}

int dfs(int u)
{
	// cout << u << endl;
	for (int i = fir[u]; ~i; i = e[i].nxt)
	{
		int v = e[i].v;
		// cout << v << endl;
		// cout << dy[v] << ' ' << dx[u]+1 << endl;
		if (!used[v] && dy[v] == dx[u]+1)
		{
			used[v] = 1;
			// cout << dy[v] << ' ' << dis << endl;
			if (ly[v] != -1 && dy[v] == dis) continue;
			if (ly[v] == -1 || dfs(ly[v]))
			{
				ly[v] = u;
				lx[u] = v;
				return 1;
			}
		}
	}
	return 0;
}

int hk_match()
{
	int ans = 0;
	for (int i = 1;i <= cnt1; ++i) lx[i] = -1;
	for (int i = 1;i <= cnt2; ++i) ly[i] = -1;
	while(bfs())
	{
		// cout << "in: " << dis << endl;
		// for (int i = 1;i <= cnt1; ++i) cout << lx[i] << ' ' ; cout << endl;
		// for (int i = 1;i <= cnt2; ++i) cout << ly[i] << ' ' ; cout << endl;
		for (int i = 1;i <= cnt2; ++i) used[i] = 0;
		for (int i = 1;i <= cnt1; ++i)
			if (lx[i] == -1) ans += dfs(i);
	}
	return ans;
}