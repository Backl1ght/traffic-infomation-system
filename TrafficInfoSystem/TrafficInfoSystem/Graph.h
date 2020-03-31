#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAX_NODE=1005;
const int INF = (int)1e9 + 9;
/*边（路径）*/
class Edge
{
private:
	int Length;				//路径长度
	string Name;			//路名
	int From;				//起点
	int To;					//终点
public:
	Edge(){}
	Edge(int from,int to,int length, string name) :From(from),To(to),Length(length), Name(name) {}
	void setLength(int l) { Length = l; }
	int getLength() { return Length; }
	void setName(string name) { Name = name; }
	string getName() { return Name; }
	void setFrom(int from) { From = from; }
	int getFrom() { return From; }
	void setTo(int to) { To = to; }
	int getTo() { return To; }

	bool operator<(Edge e)const {
		return Length < e.getLength();
	}

};
/*结点（城市）*/
class Node
{
private:
	int ID;							//编号
	string Name;					//名称
	string Code;					//代号
	string Intro;					//简介
	int X, Y;
public:
	void setID(int id) { ID = id; }
	int getID() { return ID; }
	void setName(string name) { Name = name; }
	string getName() { return Name; }
	void setCode(string code) { Code = code; }
	string getCode() { return Code; }
	void setIntro(string intro) { Intro = intro; }
	string getIntro() { return Intro; }
	int setX( int x) { X = x; return 1; }
	int getX() { return X; }
	int setY(int y) { Y = y; return 1; }
	int getY() { return Y; }
	Node() {}
	Node(int id, string name, string code, string intro, int x, int y)
		:ID(id), Name(name), Code(code), Intro(intro), X(x), Y(y) {}
};
/*图（交通网络）*/
class Graph
{
private:
	Node NodeList[MAX_NODE];					//顶点
	vector<Edge>AdjMatrix[MAX_NODE][MAX_NODE];	//领接矩阵
	int Node_num, Edge_num;						//结点数，边数

	/*获取节点编号*/
	int getNodeID(string name){
		for (int i = 0; i < Node_num; i++) {
			if (NodeList[i].getName() == name)
				return i;
		}
		return -1;
	}

	/*迪杰斯特拉算法*/
	void Dijkstra(int from, int to,int& dis,int* p) {
		//TODO
		int dist[MAX_NODE];
		bool vis[MAX_NODE];
		int path[MAX_NODE];
		for (int i = 0; i < Node_num; i++) {
			if (!AdjMatrix[from][i].empty())
				dist[i] = AdjMatrix[from][i][0].getLength();
			else
				dist[i] = INF;
			vis[i] = 0;
			if (dist[i] == INF) {
				path[i] = -1;
			}
			else {
				path[i] = from;
			}
		}
		path[from] = -1;

		if (from == to) {
			dis = 0;
			return;
		}

		vis[from] = 1;
		int mi, u=-1;
		for (int i = 1; i < Node_num; i++) {
			mi = INF;
			u = -1;
			for (int j = 0; j < Node_num; j++) {
				if (!vis[j] && dist[j] < mi) {
					u = j;
					mi = dist[j];
				}
			}
			vis[u] = 1;
			for (int j = 0; j < Node_num; j++) {
				if (!vis[j] && !AdjMatrix[u][j].empty()) {
					if (dist[j] > dist[u] + AdjMatrix[u][j][0].getLength()) {
						dist[j] = dist[u] + AdjMatrix[u][j][0].getLength();
						path[j] = u;
					}
				}
			}
		}
		for (int i = 0; i < MAX_NODE; i++) {
			p[i] = path[i];
		}
		dis = dist[to];
	}

	/*迪杰斯特拉算法*/
	void Dijkstra(int src,int* d) {
		int dist[MAX_NODE];
		bool vis[MAX_NODE];
		for (int i = 0; i < Node_num; i++) {
			if (!AdjMatrix[src][i].empty())
				dist[i] = AdjMatrix[src][i][0].getLength();
			else
				dist[i] = INF;
			vis[i] = 0;
		}
		dist[src] = 0;
		vis[src] = 1;
		int mi, u = -1;
		for (int i = 1; i < Node_num; i++) {
			mi = INF;
			u = -1;
			for (int j = 0; j < Node_num; j++) {
				if (!vis[j] && dist[j] < mi) {
					u = j;
					mi = dist[j];
				}
			}
			vis[u] = 1;
			for (int j = 0; j < Node_num; j++) {
				if (!vis[j] && !AdjMatrix[u][j].empty()) {
					if (dist[j] > dist[u] + AdjMatrix[u][j][0].getLength()) {
						dist[j] = dist[u] + AdjMatrix[u][j][0].getLength();
					}
				}
			}
		}
		for (int i = 0; i < Node_num; i++)
			d[i] = dist[i];
	}

	/*弗洛伊德算法*/
	void Floyd(int* d) {
		//TODO
		int dist[MAX_NODE][MAX_NODE],path[MAX_NODE][MAX_NODE];
		for (int i = 0; i < Node_num; i++) {
			for (int j = 0; j < Node_num; j++) {
				if (!AdjMatrix[i][j].empty())
					dist[i][j] = AdjMatrix[i][j][0].getLength();
				else
					dist[i][j] = INF;
			}
			dist[i][i] = 0;
		}
		for (int k = 0; k < Node_num; k++) {
			for (int i = 0; i < Node_num; i++) {
				for (int j = 0; j < Node_num; j++) {
					if (dist[i][k] + dist[k][j] < dist[i][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
						path[i][j] = path[i][k];		
					}
				}
			}
		}
		int p = 0;
		for (int i = 0; i < Node_num; i++) {
			for (int j = 0; j < Node_num; j++) {
				d[p++] = dist[i][j];
			}
		}
	}


public:
	/*加单向边*/
	bool AddEdge(int from, int to, int val, string name) {
		Edge newEdge(from,to,val,name);
		AdjMatrix[from][to].push_back(newEdge);
		AdjMatrix[to][from].push_back(newEdge);

		sort(AdjMatrix[from][to].begin(), AdjMatrix[from][to].end());
		sort(AdjMatrix[to][from].begin(), AdjMatrix[to][from].end());

		return 1;
	}
	bool AddEdge(string from,string to,int val,string name){
		//TODO
		int u = getNodeID(from);
		int v = getNodeID(to);
		if (u == -1 || v == -1)
			return 0;
		return AddEdge(u, v, val, name);
	}
	void AddEdge() {
		int from, to, val;
		cin >> from >> to >> val;
		from--; to--;
		string str;
		str = "default";
		//cin >> str;
		AddEdge(from, to, val, str);
		AddEdge(to, from, val, str);
	}

	/*加节点*/
	bool AddNode(string name, string code, string intro, int x, int y) {
		if (Node_num == MAX_NODE)
			return 0;
		Node node(Node_num,name, code, intro, x, y);
		node.setID(Node_num);
		NodeList[Node_num++] = node;
		return 1;
	}
	bool AddNode(Node newNode) {
		if (Node_num == MAX_NODE)
			return 0;
		NodeList[Node_num++] = newNode;
	}
	bool AddNode() {
		if (Node_num == MAX_NODE)
			return 0;
		Node node;
		string str; int x, y;
		str = "default"; x = 0; y = 0;
		//cin >> str;
		node.setName(str);
		//cin >> str;
		node.setCode(str);
		//cin >> str;
		node.setIntro(str);
		//cin >> x;
		node.setX(x);
		//cin >> y;
		node.setY(y);
		node.setID(Node_num);
		NodeList[Node_num++] = node;
		return 1;
	}

	/*两点间最短距离*/
	bool ShortestPath(string from,string to,int& dis,int* d){
		int u = getNodeID(from);
		int v = getNodeID(to);
		if (u <0 || v < 0)
			return 0;
		Dijkstra(u, v,dis,d);
		return 1;
	}
	bool ShortestPath(int from, int to,int& dis,int* d) {
		if (from == -1 || to == -1)
			return 0;
		Dijkstra(from, to, dis, d);
		return 1;
	}
	
	/*任意两点之间的最短路径*/
	void ShortestPath(int *d) {
		//TODO
		Floyd(d);
	}
	/*单源多汇最短路径*/
	bool ShortestPath(string src,int* d) {
		//TODO
		int u = getNodeID(src);
		if (u < 0)
			return 0;
		Dijkstra(u, d);
		return 1;
	}
	bool ShortestPath(int src,int* d) {
		//TODO
		if (src < 0)
			return 0;
		Dijkstra(src, d);
		return 1;
	}

	Graph() {
		Node_num = 0;
		Edge_num = 0;
	}

	Graph(int node_num,int edge_num){
		Node_num = 0;
		Edge_num = 0;
		for (int i = 0; i < node_num; i++) {
			AddNode();
		}
		for (int i = 0; i < edge_num; i++) {
			AddEdge();
		}
	}

	Node* getNodeList() { return NodeList; }

	Node getNode(int i) { return NodeList[i]; }

	int getNodeid(string to) { 
		for (int i = 0; i < Node_num; i++) {
			if (NodeList[i].getName() == to)
				return i;
		}
		return -1;
	}

	int getNode_num() { return Node_num; }

	vector<Edge> getEdgeList(int from,int to) {
		return AdjMatrix[from][to];
	}

	vector<Edge> getEdgeList(string from, string to) {
		int u = getNodeID(from), v = getNodeID(to);
		return getEdgeList(u, v);
	}

	Edge getEdge(string From, string To, int pos) {
		int u = getNodeID(From), v = getNodeID(To);
		if (AdjMatrix[u][v].size()) {
			return AdjMatrix[u][v][pos];
		}
		Edge e;
		e.setLength(-1);
		return e;
	}

	Edge getEdge(int From, int To, int pos) {
		if (AdjMatrix[From][To].size()) {
			return AdjMatrix[From][To][pos];
		}
		Edge e;
		e.setLength(-1);
		return e;
	}

	bool DelNode(int pos) {
		while (pos < Node_num) {
			NodeList[pos] = NodeList[pos + 1];
			++pos;
		}
		Node_num--;
		for (int i = 0; i < MAX_NODE; i++)
			AdjMatrix[pos][i].clear();
		return true;
	}

	bool DelEdge(string From, string To, string name) {
		int u = getNodeID(From), v = getNodeID(To);
		int n = AdjMatrix[u][v].size();
		for (int i = 0; i < n; i++) {
			if (AdjMatrix[u][v][i].getName() == name) {
				AdjMatrix[u][v].erase(AdjMatrix[u][v].begin() + i);
				AdjMatrix[v][u].erase(AdjMatrix[v][u].begin() + i);
				return true;
			}
		}
		return false;
	}

	int MPos(int id, int x, int y) {
		NodeList[id].setX(x);
		NodeList[id].setY(y);
		return 1;
	}
	int MdfC(int id,int i, CString cstr) {
		string str;
		int x;
		switch (i)
		{
		case 2:str = CT2A(cstr); NodeList[id].setName(str); break;
		case 3:str = CT2A(cstr); NodeList[id].setCode(str); break;
		case 4:str = CT2A(cstr); NodeList[id].setIntro(str); break;
		case 5:x = _ttoi(cstr); 
			if (x < 0 || x>1050)
			return 0;
			NodeList[id].setX(x); break;
		case 6:x = _ttoi(cstr);
			if (x < 0 || x>450)
				return 0;
			NodeList[id].setY(x); break;
		}
		return 1;
	}
	void MdfE(string From,string To,int i, CString cstr) {
		int from = getNodeID(From), to = getNodeID(To);
		if (i == 3) {
			string str = CT2A(cstr);
			if (AdjMatrix[from][to].empty())
				return;
			AdjMatrix[from][to][0].setName(str);
			AdjMatrix[to][from][0].setName(str);
		}
		else if (i == 4) {
			int l=_ttoi(cstr);
			if (AdjMatrix[from][to].empty())
				return;
			AdjMatrix[from][to][0].setLength(l);
			AdjMatrix[to][from][0].setLength(l);
		}
	}
};
