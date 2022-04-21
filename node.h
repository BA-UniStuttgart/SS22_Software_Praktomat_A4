/*
 * node.h
 *
 *  Created on: 29.01.2019
 *      Author: student
 */

#ifndef NODE_H_
#define NODE_H_

#include "insel.h"

typedef struct node{
	Insel * insel;
	struct node *next;
	struct node * prev;
}Node;


Node * Node_New(void);
void Node_Insert(Node * theNode);

#endif /* NODE_H_ */
