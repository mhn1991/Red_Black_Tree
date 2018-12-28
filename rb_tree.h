typedef struct node {
  int red;
  void *data;
  struct node *leaves[2];
}*node;


typedef struct rb_tree {
  int size;
  struct node *head;
}*rb_tree;
