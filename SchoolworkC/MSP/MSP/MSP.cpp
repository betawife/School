#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  // ��󶥵���
#define INF 1000000000  // ��ʾ������Ȩֵ

typedef struct {
    int u, v;      // �ߵ���������
    int weight;    // �ߵ�Ȩֵ���������Ȼ���ۣ�
} Edge;

typedef struct {
    int vertexNum;  // ������
    int edgeNum;    // ����
    Edge edges[MAX];  // �洢�ߵ���Ϣ
    char cityNames[MAX][50];  // ��������
} Graph;

int parent[MAX];  // ���鼯����

// ���鼯��ʼ��
void initUnionFind(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

// ���鼯����
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// ���鼯�ϲ�
void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

// �ȽϺ��������ڱ�Ȩֵ����������
int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Kruskal�㷨����С������
void kruskal(Graph* g) {
    int totalWeight = 0;  // ��С��������Ȩֵ
    int edgeCount = 0;  // �Ѽ����������ı���

    // ��ʼ�����鼯
    initUnionFind(g->vertexNum);

    // ��Ȩֵ���������
    qsort(g->edges, g->edgeNum, sizeof(Edge), compareEdges);

    printf("��С�������ı����£�\n");
    for (int i = 0; i < g->edgeNum; i++) {
        Edge e = g->edges[i];
        if (find(e.u) != find(e.v)) {
            unionSets(e.u, e.v);
            printf("<%s, %s, ���: %d��Ԫ>\n", g->cityNames[e.u], g->cityNames[e.v], e.weight);
            totalWeight += e.weight;
            edgeCount++;
            if (edgeCount == g->vertexNum - 1) {
                break;
            }
        }
    }

    printf("��С�������������Ϊ��%d��Ԫ\n", totalWeight);
}

// ���ļ���ȡͼ����
void readGraphFromFile(Graph* g, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("�޷����ļ�");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d", &g->vertexNum, &g->edgeNum);

    // ��ȡ��������
    for (int i = 0; i < g->vertexNum; i++) {
        fscanf(file, "%s", g->cityNames[i]);
    }

    // ��ȡ����Ϣ
    for (int i = 0; i < g->edgeNum; i++) {
        char city1[50], city2[50];
        int weight;
        fscanf(file, "%s %s %d", city1, city2, &weight);

        // ���ҳ��ж�Ӧ�ı��
        int u = -1, v = -1;
        for (int j = 0; j < g->vertexNum; j++) {
            if (strcmp(city1, g->cityNames[j]) == 0) {
                u = j;
            }
            if (strcmp(city2, g->cityNames[j]) == 0) {
                v = j;
            }
        }

        if (u != -1 && v != -1) {
            g->edges[i].u = u;
            g->edges[i].v = v;
            g->edges[i].weight = weight;
        }
        else {
            fprintf(stderr, "�������ƴ���%s �� %s\n", city1, city2);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}

// ������
int main() {
    Graph g;

    char filename[100];
    printf("�����������ļ�����\n");
    scanf("%s", filename);

    // ���ļ���ȡͼ����
    readGraphFromFile(&g, "C:/data/graph.txt");


    // ִ��Kruskal�㷨
    kruskal(&g);

    return 0;
}
