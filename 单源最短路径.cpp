#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTICES 100
#define INF INT_MAX
// 优先队列节点结构体
typedef struct {
    int vertex;
    int distance;
} Node;
// 优先队列结构体
typedef struct {
    Node *array;
    int size;
    int capacity;
} PriorityQueue;
// 创建优先队列
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->array = (Node*)malloc(capacity * sizeof(Node));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}
// 交换两个节点
void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}
// 最小堆化
void minHeapify(PriorityQueue* pq, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < pq->size && pq->array[left].distance < pq->array[smallest].distance)
        smallest = left;
    if (right < pq->size && pq->array[right].distance < pq->array[smallest].distance)
        smallest = right;
    if (smallest != idx) {
        swap(&pq->array[smallest], &pq->array[idx]);
        minHeapify(pq, smallest);
    }
}
// 检查优先队列是否为空
int isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}
// 插入节点到优先队列
void insert(PriorityQueue* pq, int vertex, int distance) {
    if (pq->size == pq->capacity) {
        printf("Priority queue is full\n");
        return;
    }
    pq->size++;
    int i = pq->size - 1;
    pq->array[i].vertex = vertex;
    pq->array[i].distance = distance;
    while (i > 0 && pq->array[(i - 1) / 2].distance > pq->array[i].distance) {
        swap(&pq->array[(i - 1) / 2], &pq->array[i]);
        i = (i - 1) / 2;
    }
}
// 从优先队列中提取最小元素
Node extractMin(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        Node empty = {-1, -1};
        return empty;
    }
    Node root = pq->array[0];
    Node last = pq->array[pq->size - 1];
    pq->size--;
    if (!isEmpty(pq)) {
        pq->array[0] = last;
        minHeapify(pq, 0);
    }
    return root;
}
// 分枝界限法实现单源最短路径
void branchAndBoundShortestPath(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices, int source) {
    int dist[MAX_VERTICES];
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INF;
    }
    dist[source] = 0;
    PriorityQueue* pq = createPriorityQueue(numVertices);
    insert(pq, source, 0);
    while (!isEmpty(pq)) {
        Node u = extractMin(pq);
        int vertex = u.vertex;
        int distance = u.distance;
        if (distance > dist[vertex]) continue;
        for (int v = 0; v < numVertices; v++) {
            if (graph[vertex][v] != 0 && dist[vertex] != INF && dist[vertex] + graph[vertex][v] < dist[v]) {
                dist[v] = dist[vertex] + graph[vertex][v];
                insert(pq, v, dist[v]);
            }
        }
    }
    // 输出最短路径
    printf("最短路径 %d:\n", source);
    for (int i = 0; i < numVertices; i++) {
        if (dist[i] == INF) {
            printf("Vertex %d: INF\n", i);
        } else {
            printf("Vertex %d: %d\n", i, dist[i]);
        }
    }
    free(pq->array);
    free(pq);
}
int main() {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0,7, 11, 0},
        {0, 8, 0, 6, 0, 4, 0, 0, 2},
        {0, 9, 0, 0, 0, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 13, 0, 0, 0},
        {0, 6, 8, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 7, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 18, 0}
    };
    int numVertices = 9;
    int source = 0;
    branchAndBoundShortestPath(graph, numVertices, source);
    return 0;
}

