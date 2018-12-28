#include<stdlib.h>
#include"rb_tree.h"

struct node * node_alloc(){
  return malloc(sizeof(struct node));
}


struct node * node_init(struct node *node,void *data){
  if(node){
    node->red = 1; // new insertation is always red
    node->data = data;
    node->leaves[0] = node->leaves[1] = NULL;
  }
  return node;
}


struct node * node_create(void *data){
  return node_init(node_alloc(),data);
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


void main(){

}
