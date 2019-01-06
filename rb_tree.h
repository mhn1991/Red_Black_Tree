//data structure
typedef struct node {
  int red;
  void *data;
  struct node *parent;//help to check balance of tree
  struct node *leaves[2];// 0 left 1 right
}*node;


typedef struct rb_tree {
  int size;
  struct node *head;
}*rb_tree;

//functions
struct node * node_alloc();
struct node * node_init(struct node *node,void *data,struct node *parent);
struct node * create_node(void *data,struct node *parent);
int node_unalloc(struct node *node);
int node_is_red(struct node *node);
struct rb_tree * alloc_tree();
struct rb_tree * init_tree(struct rb_tree * tree);
struct rb_tree * create_tree();
void color_flip(struct rb_tree * tree,struct node * node);
void left_rotation(struct rb_tree * tree,struct node * grand_parent,struct node * parent,struct node * child);
void right_rotation(struct rb_tree * tree,struct node * grand_parent,struct node * parent,struct node * child);
void right_left_rotation(struct rb_tree * tree,struct node * grand_parent,struct node * parent,struct node * child);
void rotations(struct rb_tree * tree,struct node *grand_parent,struct node * parent,struct node * child);
void check_rules(struct rb_tree * tree,struct node * parent,struct node * child);
void ins(struct rb_tree * tree,struct node * node);

