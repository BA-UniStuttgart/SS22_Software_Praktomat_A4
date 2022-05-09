#ifndef _CSTM_NODE_H_
#define _CSTM_NODE_H_

#include "insel.h"

typedef struct Node {
	Insel * insel;
	struct Node *next;
	struct Node * prev;
} Node;


int node_new(Insel* insel, Node** dst);
int node_push_back(Node* into, Node* node);
void node_free(Node* node);
int node_push_back_insel(Node* node, Insel* insel);

#endif
