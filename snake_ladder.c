/*
Snake and Ladder Problem: Given a snake and ladder board, find the minimum number of dice throws required to reach the destination or last cell from source or 1st cell. Basically, the player has total control over outcome of dice throw and wants to find out minimum number of throws required to reach last cell.

https://www.geeksforgeeks.org/snake-ladder-problem-2/
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 30

struct edge {
  int v1;
  int v2;
  struct edge *next;
};

struct graph {
  int num_vertices;
  int num_edges;
  struct edge **adj_list;
};

int insert_edge(struct graph *g, int v1, int v2)
{
  if (v1 >= g->num_vertices || v2 >= g->num_vertices)
    return -1;

  struct edge *new_edge = (struct edge *) malloc (sizeof (*new_edge));
  new_edge->v1 = v1;
  new_edge->v2 = v2;
  new_edge->next = g->adj_list[v1];
  g->adj_list[v1] = new_edge;
  g->num_edges++;
  return 0;
}

void print_graph (struct graph *g)
{
  int i;
  struct edge *runner = NULL;

  printf ("Number of vertices %d\n", g->num_vertices);
  printf ("Edges: \n");
  for (i = 0; i < g->num_vertices; i++) {
    runner = g->adj_list[i];
    while (runner) {
      printf ("%d->%d ", runner->v1, runner->v2);
      runner = runner->next;
    }
    printf ("\n");
  }
}

void bfs (struct graph *g, int start_node)
{
  int i;
  int queue [SIZE];
  int start = 0, end = 0;
  int curr_v, adj_v;
  struct edge *runner = NULL;
  int *sortest_path = (int *) calloc (g->num_vertices, sizeof (*sortest_path));
  for (i = 0; i < g->num_vertices; i++) {
    sortest_path[i] = SIZE + 1;//infinite
  }

  int *prev = (int *) calloc (g->num_vertices, sizeof (*prev));
  for (i = 0; i < g->num_vertices; i++) {
    prev[i] = -1;
  }

  sortest_path[start_node] = 0;
  //enqueue start node
  queue[end++] = start_node;
  while (end > start) {
    curr_v = queue [start++]; 
    runner = g->adj_list[curr_v];
    while (runner) {
      adj_v = runner->v2;
      printf ("processin edge %d->%d\n", curr_v, adj_v);
      if (sortest_path[adj_v] > (sortest_path[curr_v] + 1)) {
        sortest_path[adj_v] = sortest_path[curr_v] + 1;
        prev[adj_v] = curr_v;
        queue[end++] = adj_v;
      }
      if (end >= SIZE) {
        printf ("Queue is full \n");
        exit (1);
      }
      runner = runner->next;
    }
  }
  
  printf ("Shortest path is %d \n", sortest_path[g->num_vertices - 1]);
  printf ("The path is = ");

  int node = g->num_vertices - 1;
  while (prev[node] != -1) {
    printf ("%d ", prev[node] + 1);
    node = prev[node];
  }

}

int snake_ladder (int move[], int size)
{
  int i, j;
  struct graph g;
  g.num_vertices = size;
  g.num_edges = 0;
  g.adj_list = (struct edge **) calloc (g.num_vertices, sizeof (*g.adj_list));

  for (i = 0; i < SIZE; i++) {
    for (j = 1; j <= 6; j++) {
      if (i + j >= SIZE)
        continue;
      if (move[i + j] == -1)
        insert_edge (&g, i, i + j);
      else
        insert_edge (&g, i, move[i + j]);
    }
  }

  print_graph(&g);

  bfs (&g, 0);
}

void main ()
{
  int moves[SIZE];
  int i;

  for (i = 0; i < SIZE; i++)
    moves[i] = -1;

  // Ladders 
  moves[2] = 21; 
  moves[4] = 7; 
  moves[10] = 25; 
  moves[19] = 28; 
  
  // Snakes 
  moves[26] = 0; 
  moves[20] = 8; 
  moves[16] = 3; 
  moves[18] = 6; 

  snake_ladder (moves, SIZE);
}
