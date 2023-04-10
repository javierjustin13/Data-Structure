#include<stdio.h>

bool allVisited(bool visited[], int n) {
  for (int i = 0; i < n; i++) {
    if (!visited[i]) return false;
  }
  return true;
}

int main() {
  int V = 5;
  int graph[5][5] = {
{ 0, 2, 0, 6, 0 },
      { 2, 0, 3, 8, 5 },
      { 0, 3, 0, 0, 7 },
      { 6, 8, 0, 0, 9 },
      { 0, 5, 7, 9, 0 }
  };

  bool visited[5] = {};
  bool pathVisited[5][5] = {};
  int total = 0;

  visited[0] = true;
  while (!allVisited(visited, V)) {
    int src = -1, dst = -1;
    int minimumWeight = 99999;

    for (int i = 0; i < V; i++) { // i melambangkan src
      if (visited[i] == false) continue;

      for (int j = 0; j < V; j++) {
        if (i == j || graph[i][j] == 0 || visited[j] || pathVisited[i][j]) continue;

        // mau ambil weight terkecil
        if (graph[i][j] < minimumWeight) {
          minimumWeight = graph[i][j];
          src = i;
          dst = j;
        }
      }
    }

    // cek
    if (src != -1 && dst != -1) {
      visited[dst] = true;
      pathVisited[src][dst] = pathVisited[dst][src] = true;
      total += graph[src][dst];
      printf("%d --- %d (%d)\n", src, dst, graph[src][dst]);
    }
    else {
      printf("Invalid Graph\n");
      break;
    }
  }

  printf("Total %d\n", total);

  // int V = 9;
  // int graph[V][V] = {
  //  {0,  4, 0,  0,  0,  0, 0,  8, 0},
  //  {4,  0, 8,  0,  0,  0, 0, 11, 0},
  //  {0,  8, 0,  7,  0,  4, 0,  0, 2},
  //  {0,  0, 7,  0,  9, 14, 0,  0, 0},
  //  {0,  0, 0,  9,  0, 10, 0,  0, 0},
  //  {0,  0, 4, 14, 10,  0, 2,  0, 0},
  //  {0,  0, 0,  0,  0,  2, 0,  1, 6},
  //  {8, 11, 0,  0,  0,  0, 1,  0, 7},
  //  {0,  0, 2,  0,  0,  0, 6,  7, 0},
  // };

  return 0;
}