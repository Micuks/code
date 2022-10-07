#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXM = 500005;

class Edge {
    public:
        int len;
        int to;
        int next;
        Edge(): len(0), to(0), next(0) {  };
};

class Node {
    public:
        int mNode;
        int mDis;
        Node(int node, int dis): mNode(node), mDis(dis) { };
        bool operator <(const Node& y) const
        {
            return y.mDis < mDis;
        }
};

int n, m, s;
int head[MAXN];
Edge edge[MAXM];
int cnt;
int dis[MAXN];

void store_edges()
{
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        cnt++;
        edge[cnt].len = w;
        edge[cnt].to = v;
        edge[cnt].next = head[u];
        head[u] = cnt;
    }
}

priority_queue<Node> pq;
int visited[MAXN];

void dijkstra() {
    dis[s] = 0;
    pq.push(Node(s, dis[s]));

    while(!pq.empty()) {
        Node tmp = pq.top();
        pq.pop();
        int x = tmp.mNode;
        if(visited[x]) {
            continue;
        }
        visited[x] = 1;

        for(int i = head[x]; i; i = edge[i].next) {
            int next_node = edge[i].to;
            if(dis[next_node] > dis[x] + edge[i].len) {
                dis[next_node] = dis[x] + edge[i].len;
                if(!visited[next_node]) {
                    pq.push(Node{next_node, dis[next_node]});
                }
            }

        }
    }
}

int main()
{
  cin >> n >> m >> s;
  for(int i = 1; i <= n; i++) {
      dis[i] = 0x7fffffff;
  }
  store_edges();
  dijkstra();
  for(int i = 1; i <= n; i++) {
      cout << dis[i] << ' ';
  }
  cout << endl;
}
