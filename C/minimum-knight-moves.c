/*
https://leetcode.com/problems/minimum-knight-moves/

In an infinite chess board with coordinates from -infinity to +infinity, you have a knight at square [0, 0].

A knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.

Return the minimum number of steps needed to move the knight to the square [x, y].  It is guaranteed the answer exists. 

Example 1:

Input: x = 2, y = 1
Output: 1
Explanation: [0, 0] → [2, 1]
Example 2:

Input: x = 5, y = 5
Output: 4
Explanation: [0, 0] → [2, 1] → [4, 2] → [3, 4] → [5, 5]
 

Constraints:

|x| + |y| <= 300


Note that, this solution can be improved by using a heap instead of queue. Should use A* search (use heap). 

https://www.geeksforgeeks.org/minimum-steps-reach-target-knight/
*/

struct cell {
  int row;
  int col;
};

struct cell_dis {
  struct cell c;
  int weight;
};

int dist (struct cell c, int x, int y)
{
  return abs (x - c.row) + abs (y - c.col); 
  //return sqrt(pow (x - c.row, 2) + pow (y - c.col, 2)); 
}

int cmp (const void *a, const void *b)
{
  return ((struct cell_dis *)a)->weight - ((struct cell_dis *)b)->weight;
}

int nm [][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

void next_vertices (struct cell curr, int target_x, int target_y, struct cell_dis *dis)
{
  int x, y, i;
  
  for (i = 0; i < 8; i++) {
    dis[i].c.row = curr.row + nm[i][0];
    dis[i].c.col = curr.col + nm[i][1];
    dis[i].weight = dist (dis[i].c, target_x, target_y);    
  }
  
  qsort (dis, 8, sizeof (struct cell_dis), cmp);
}



int minKnightMoves(int x, int y){
  struct cell *queue = (struct cell *) malloc (400000 * sizeof (*queue));
  int *level_queue = (int *) malloc (400000 * sizeof (*level_queue));
  int q_start = 0, q_end = 0;
  struct cell curr;
  int curr_level;
  int visit[605][605]={0};
  struct cell_dis vertices[8];
  int i, j; 
  
  queue[q_end].row = 0;
  queue[q_end].col = 0;
  level_queue[q_end] = 0;
  q_end++;
  visit[302][302] = 1;
  while (q_end > q_start) {
    curr = queue[q_start];
    curr_level = level_queue[q_start];
    q_start++;
    if (curr.row == x && curr.col == y)
      return curr_level;
    next_vertices (curr, x, y, vertices);
    for (i = 0; i < 8; i++) {
      if (visit[vertices[i].c.row + 302][vertices[i].c.col + 302])
        continue;
      visit[vertices[i].c.row + 302][vertices[i].c.col + 302] = 1;
      queue[q_end] = vertices[i].c;
      level_queue[q_end] = curr_level + 1;
      q_end++;
    }
  }
  return -1;
}
