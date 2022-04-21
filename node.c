/*
 * node.c
 *
 *  Created on: 29.01.2019
 *      Author: student
 */
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

Node * Node_New(void)
{
	Node * newNode;

	newNode = (Node*)malloc(sizeof(Node));
	if(newNode==NULL){
		printf("Kein Speicher\n");
	}else{
		newNode->next = NULL;
		newNode->prev = NULL;
	}
	return newNode;
}


void Node_Insert(Node * theNode){
	Node * newNode;

	newNode = Node_New();
	if(newNode != NULL){
		if(theNode != NULL){
			newNode->next = theNode->next;
			theNode->next = newNode;
			newNode->prev = theNode;
			if(newNode->next != NULL)newNode->next->prev = newNode;
		}else{
			theNode = newNode;
		}
	}
}
