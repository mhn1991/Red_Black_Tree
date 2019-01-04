#include<stdio.h>
#include<stdlib.h>
#include"rb_tree.h"

struct node * node_alloc(){
  return malloc(sizeof(struct node));
}


struct node * node_init(struct node *node,void *data,struct node *parent){
  if(node){
    node->red = 1; // new insertation is always red
    node->data = data;
    node->parent = parent;//set parent to going backward
    node->leaves[0] = node->leaves[1] = NULL;
    return node;
  }
  else{
    printf("node init failed\n");
    return NULL;
  }
}


struct node * create_node(void *data,struct node *parent){
  return node_init(node_alloc(),data,parent);
}

int node_unalloc(struct node *node){
  if(node){
    free(node);
  }
}

int node_is_red(struct node *node){
  if(node->red){
    return 1;
  }
  return 0;
}

struct rb_tree * alloc_tree(){
  return malloc(sizeof(struct rb_tree));
}

struct rb_tree * init_tree(struct rb_tree * tree){
  if(tree){
    tree->size = 0;
    tree->head = NULL;
    return tree;
  }else{
    printf("tree init failed\n");
    return NULL;
  }
}

struct rb_tree * create_tree(){
  return init_tree(alloc_tree());
}

void print_left(struct rb_tree * tree){
  struct node * p = tree->head;
  while(p != NULL){
    printf("%d\n",*(int *)(p->data));
    p = p->leaves[0];
  }
}

void color_flip(struct node * node){
  //check we have valid node
  if(node){
    node->red = 1;
    node->leaves[0]->red = node->leaves[1]->red = 0;
  }
}

void left_rotation(struct node * grand_parent,struct node * parent,struct node * child){
  void * tmp = parent->data;
  struct node * left = grand_parent->leaves[0];
  grand_parent->leaves[1] = child;
  grand_parent->leaves[0] = parent;
  parent->data = grand_parent->data;
  grand_parent->data = tmp;
  parent->leaves[1] = NULL;
  parent->leaves[0] = left;
  child->parent = grand_parent;
  //changing color
  grand_parent->red=0;
  parent->red = child->red = 1;
}

void right_rotation(struct node * grand_parent,struct node * parent,struct node * child){
  void * tmp = parent->data;
  struct node * right = grand_parent->leaves[1];
  grand_parent->leaves[0] = child;
  grand_parent->leaves[1] = parent;
  parent->data = grand_parent->data;
  grand_parent->data = tmp;
  parent->leaves[0] = NULL;
  parent->leaves[1] = right;
  child->parent = grand_parent;
  // changing color
  grand_parent->red=0;
  parent->red = child->red = 1;
}

void right_left_rotation(struct node * grand_parent,struct node * parent,struct node * child){
  grand_parent->leaves[1] = child;
  child->leaves[1] = parent;
  child->parent  = grand_parent;
  parent->parent = child;
  parent->leaves[0] = NULL;
  left_rotation(grand_parent,child,parent);
}

void left_right_rotation(struct node * grand_parent,struct node * parent,struct node * child){
  grand_parent->leaves[0] = child;
  child->leaves[0] = parent;
  child->parent = grand_parent;
  parent->parent = child;
  parent->leaves[1] = NULL;
  right_rotation(grand_parent,child,parent);
}

void check_balance(struct node *grand_parent,struct node * parent,struct node * child){
  if((*(int *)grand_parent->data < *(int *)parent->data) && (*(int *)parent->data < *(int *)child->data)){
    printf("left rotation\n");
    printf("%d\t%d\t%d\n",*(int *)grand_parent->data,*(int *)parent->data,*(int *)child->data);
    left_rotation(grand_parent,parent,child);
  }else if((*(int *)grand_parent->data > *(int *)parent->data)&&(*(int *)parent->data > *(int *)child->data)){
    printf("right rotation\n");
    right_rotation(grand_parent,parent,child);
  }else if((*(int *)grand_parent->data > *(int *)parent->data) && (*(int *)parent->data < *(int *)child->data)){
    printf("left right rotation\n");
    left_right_rotation(grand_parent,parent,child);
  }else if((*(int *)grand_parent->data < *(int *)parent->data) && (*(int *)parent->data > *(int *)child->data)){
    printf("right left rotation\n");
    right_left_rotation(grand_parent,parent,child);
  }else{
    printf("tree is balance!\n");
  }
}

void ins(struct rb_tree * tree,struct node * node){
  if(tree->head == NULL){
    node->parent = NULL;
    tree->head = node;
    tree->size++;
  }else{
    struct node *iter;
    iter = tree->head;
    while(1){
      if(node->data < iter->data && iter->leaves[0] != NULL){
	iter = iter->leaves[0];
      }else if (node->data > iter->data && iter->leaves[1] != NULL){
	iter = iter->leaves[1];
      }else if (node->data < iter->data && iter->leaves[0] == NULL){
	iter->leaves[0] = node;
	node->parent = iter;
	if(iter->parent){
	  check_balance(iter->parent,iter,node);
	}
	break;
      }else if (node->data > iter->data && iter->leaves[1] == NULL){
	iter->leaves[1] = node;
	node->parent = iter;
	if(iter->parent){
	  check_balance(iter->parent,iter,node);
	}
	break;
      }
    }
  }
}

void main(){
  struct rb_tree * tree = create_tree();
  if(tree){
    int list[] = {8,4,6};
    for(int i=0;i<3;i++){
      ins(tree,create_node((void *)&list[i],NULL));
    }
    printf("%d\n",*(int *)tree->head->leaves[0]->data);
  }
}
