typedef struct node {
  int red;
  void *data;
  struct node *leaves[2];// 0 left 1 right
}*node;


typedef struct rb_tree {
  int size;
  struct node *head;
}*rb_tree;
