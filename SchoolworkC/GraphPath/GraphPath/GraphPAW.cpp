#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    int V; // ������
    vector<vector<int>> adj; // �ڽӱ�

public:
    // ���캯��
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // ��ӱ�
    void addEdge(int v, int w) {
        adj[v].push_back(w); // �� w ��ӵ� v ���б���
    }

    // ����ÿ����������
    vector<int> inDegree() {
        vector<int> indegree(V, 0);
        for (int i = 0; i < V; i++) {
            for (int j : adj[i]) {
                indegree[j]++;
            }
        }
        return indegree;
    }

    // ����ÿ������ĳ���
    vector<int> outDegree() {
        vector<int> outdegree(V, 0);
        for (int i = 0; i < V; i++) {
            outdegree[i] = adj[i].size();
        }
        return outdegree;
    }

    // �������Ϊ0�Ķ�����
    int countZeroOutDegree() {
        int count = 0;
        for (int i = 0; i < V; i++) {
            if (adj[i].empty()) {
                count++;
            }
        }
        return count;
    }
};

int main() {
    Graph g(5); // ����һ����5�������ͼ
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    vector<int> indegrees = g.inDegree();
    vector<int> outdegrees = g.outDegree();
    int zeroOutDegrees = g.countZeroOutDegree();

    cout << "\nÿ������������Ϊ��";
    for (int d : indegrees) {
        cout << d << " ";
    }
    cout << "\nÿ����ĳ�������Ϊ�� ";
    for (int d : outdegrees) {
        cout << d << " ";
    }
    cout << "\n����Ϊ��Ķ�������" << zeroOutDegrees << endl;

    return 0;
}
