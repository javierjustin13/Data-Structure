#include<stdio.h>
#include<stdlib.h>
#include "linkedlist.cpp"

struct Graph {
	int V; // V: number of vertices, E: number of edges
	Node *head, *tail;
};

Graph createGraph(int V) {
	Graph graph;
	graph.V = V;
	graph.head = NULL;
	graph.tail = NULL;
	return graph;
}

int findParent(int parent[], int pos) {
	// if (parent[pos] == pos) return pos;
	// return findParent(parent, parent[pos]);
	return (parent[pos] == pos) ? pos : findParent(parent, parent[pos]);
}

bool isCycle(Graph graph) {
	int parent[graph.V];

	//MAKE SETS
	for (int i = 0; i < graph.V; i++) {
		parent[i] = i;
	}

	Node* curr = graph.head;
	while(curr != NULL) {
		int src = curr->edge.src;
		int dst = curr->edge.dst;
		
		//FIND PARENTS
		int srcParent = findParent(parent, src);
		int dstParent = findParent(parent, dst);

		if (srcParent == dstParent) return true;

		//UNION
		parent[srcParent] = dstParent;
		curr = curr->next;
	}
	return false;
}

int main() {
	
	Node *qHead = NULL, *qTail = NULL;
	
//	//4
//	pushValue(&qHead, &qTail, createEdge(0, 1, 2));
//	pushValue(&qHead, &qTail, createEdge(3, 0, 4));
//	pushValue(&qHead, &qTail, createEdge(2, 3, 1));
//	pushValue(&qHead, &qTail, createEdge(1, 2, 3));
	
//	//5
//	pushValue(&qHead, &qTail, createEdge(0, 1, 2));
//	pushValue(&qHead, &qTail, createEdge(0, 3, 6));
//	pushValue(&qHead, &qTail, createEdge(1, 2, 3));
//	pushValue(&qHead, &qTail, createEdge(1, 3, 8));
//	pushValue(&qHead, &qTail, createEdge(1, 4, 5));
//	pushValue(&qHead, &qTail, createEdge(2, 4, 7));
//	pushValue(&qHead, &qTail, createEdge(3, 4, 9));
	
	
//	//9
//	pushValue(&qHead, &qTail, createEdge(0, 1, 4));
//	pushValue(&qHead, &qTail, createEdge(0, 7, 8));
//	pushValue(&qHead, &qTail, createEdge(1, 2, 8));
//	pushValue(&qHead, &qTail, createEdge(1, 7, 11));
//	pushValue(&qHead, &qTail, createEdge(2, 3, 7));
//	pushValue(&qHead, &qTail, createEdge(2, 5, 4));
//	pushValue(&qHead, &qTail, createEdge(2, 8, 2));
//	pushValue(&qHead, &qTail, createEdge(3, 4, 9));
//	pushValue(&qHead, &qTail, createEdge(3, 5, 14));
//	pushValue(&qHead, &qTail, createEdge(4, 5, 10));
//	pushValue(&qHead, &qTail, createEdge(5, 6, 2));
//	pushValue(&qHead, &qTail, createEdge(6, 7, 1));
//	pushValue(&qHead, &qTail, createEdge(6, 8, 6));
//	pushValue(&qHead, &qTail, createEdge(7, 8, 7));
	
	// viewNode(qHead);

	int V = 4;
	int total = 0;
	Graph graph = createGraph(V);
	Node* curr = qHead;
	while (curr != NULL) {
		pushValue(&graph.head, &graph.tail, curr->edge);
		if(isCycle(graph)) {
			popValue(&graph.head, &graph.tail, curr->edge.src, curr->edge.dst);
		}
		else {
			total += curr->edge.weight;
			printf("%d --- %d (%d)\n", curr->edge.src, curr->edge.dst, curr->edge.weight);
		}
		curr = curr->next;
	}
	printf("Total: %d", total);

	return 0;
}
