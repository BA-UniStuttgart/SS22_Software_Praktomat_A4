#ifndef _NODE_H_
#define _NODE_H_

#include "insel.h"

typedef struct Node {
	Insel * insel;
	Node *next;
	Node * prev;
} Node;

/*
	Tries to allocate a new Node.
	This function will try to allocate a new Node.
	The ptr to insel will be owned by the returned Node.
	The new node will be assigned to dst.

	If an error occurs, dst will be invalidated as NULL.
	May return KokosError:NullPointerError if insel is a nullptr.
	May return KokosError:OutOfMemoryError if memory could not be allocated.

	If no error occurred, a KokosError:None will be returned.
*/
KokosError node_new(Insel* insel, Node** dst);

/*
	Tries to push 'node' in 'into'.
	This function will push 'node' as the last element of 'into'.

	May return KokosError:NullPointerError
	if either 'into' or 'node' are nullptr.

	If no error occurred, a KokosError:None will be returned.
*/
KokosError node_push_back(Node* into, Node* node);

/*
	Frees a Node.
	This function will attempt to free a heap
	allocated Node, as well as all consecutive nodes
	owned by 'node'.

	May return a KokosError:NullpointerError if node is a nullptr.

	If no error occurred, a KokosError:None will be returned.
*/
KokosError node_free(Node* node);

/*
	Pushes an insel into node.
	This function will push a new Node with insel
	as the last element of node.
	The Insel pointer will be owned by the new Node.

	May return a KokosError:NullPointerError if either
	node or insel are nullptr.
	May return a KokosError:OutOfMemoryError if
	the allocation of a new Node failed.

	If no error occurred, a KokosError:None will be returned.
*/
KokosError node_push_back_insel(Node* node, Insel* insel);

#endif
