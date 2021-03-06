const int MAX_N = 100;
const int MAX_V = 2 * (MAX_N + 1);
const int S = MAX_V - 2;
const int E = MAX_V - 1;
const int inf = 2147483647;

int c[MAX_V][MAX_V];
int d[MAX_V][MAX_V];
int f[MAX_V][MAX_V];
vector<int> adj[MAX_V];

int cnt = 0;
int res = 0;

void MCMF(int source, int sink) {

	while (true) {
		int prev[MAX_V], dist[MAX_V];
		bool inQueue[MAX_V] = {false, };

		queue<int> q;
		fill(prev, prev + MAX_V, -1);
		fill(dist, dist + MAX_V, inf);

		dist[S] = 0;
		inQueue[S] = true;
		q.push(S);

		while (!q.empty()) {
			int curr = q.front();
			q.pop();
			inQueue[curr] = false;

			for (int i = 0; i < adj[curr].size(); i++) {
				int next = adj[curr][i];

				if (c[curr][next] - f[curr][next] > 0 && dist[next] > dist[curr] + d[curr][next]) {
					dist[next] = dist[curr] + d[curr][next];
					prev[next] = curr;
					
					if (!inQueue[next]) {
						q.push(next);
						inQueue[next] = true;
					}
				}
			}
		}

		if (prev[E] == -1)
			break;

		int flow = inf;

		for (int i = E; i != S; i = prev[i])
			flow = min(flow, c[prev[i]][i] - f[prev[i]][i]);

		for (int i = E; i != S; i = prev[i]) {
			res += flow * d[prev[i]][i];
			f[prev[i]][i] += flow;
			f[i][prev[i]] -= flow;
		}

		cnt += flow;
	}
}
