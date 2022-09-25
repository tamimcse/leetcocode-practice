/*
Array to BST. Given a sorted array. Convert it into a Height balanced Binary Search Tree (BST).
Height balanced BST means a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Input: nums = {1, 2, 3, 4}
Output: {2, 1, 3, 4}
Explanation: 
The preorder traversal of the following 
BST formed is {2, 1, 3, 4}:
     3
    /  \
   2    4
 /
1

Input: nums = {1,2,3,4,5,6,7}
Ouput: {4,2,1,3,6,5,7}
Explanation: 
The preorder traversal of the following
BST formed is {4,2,1,3,6,5,7} :
        4
       / \
      2   6
     / \  / \
    1   3 5  7

*/
#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *left, *right;
};

void insert_bst (struct node **root, int val)
{
  struct node *runner;
  struct node *new_node = (struct node *) malloc (sizeof (*new_node));
  new_node->data = val;
  new_node->left = NULL;
  new_node->right = NULL;

  //The tree is empty
  if (!*root) {
    *root = new_node;
    return;
  }

  runner = *root;
  while (runner) {
    if (val >= runner->data) {
      if (runner->right) {
        runner = runner->right;
      } else {
        runner->right = new_node;
        break;
      }
    } else {
      if (runner->left) {
        runner = runner->left;
      } else {
        runner->left = new_node;
        break;
      }
    }
  }
}

#define QUEUE_SIZE 100

int level_order (struct node *root)
{
  struct node *runner;
  struct node *queue[QUEUE_SIZE] = {0};
  int start_ix = 0, end_ix = 0;

  if (!root)
    return 0;

  //insert root to queue
  queue[end_ix++] = root;

  //queue is not empty
  while (end_ix > start_ix) {
    //dequeue
    runner = queue[start_ix++];
    printf ("%d ", runner->data);
    //insert chieldren to queue
    if (end_ix >= QUEUE_SIZE) {
      printf ("Queue is full. Please increase the queue size\n");
      return 1;
    }
    if (runner->left)
      queue[end_ix++] = runner->left;
    if (runner->right)
      queue[end_ix++] = runner->right;
  }
  return 0;
}

void main ()
{
  int i;
  int arr1 [] = {1, 2, 3, 4};
  int arr2 [] = {1,2,3,4,5,6,7};

  struct node *root1 = NULL, *root2 = NULL;

  for (i = 0; i < sizeof (arr1) / sizeof (arr1[0]); i++) {
    insert_bst (&root1, arr1[i]);
  }

  for (i = 0; i < sizeof (arr2) / sizeof (arr2[0]); i++) {
    insert_bst (&root2, arr2[i]);
  }


  level_order (root1);
  printf ("\n");
  level_order (root2);
  printf ("\n");
}
