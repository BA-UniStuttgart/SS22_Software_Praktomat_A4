#include <stdlib.h>
#include "node.h"

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
KokosError node_new(Insel* insel, Node** dst) {

	// Sanity check
	if (!insel) {
		*dst = NULL;
		return kokos_nullptr(1);
	}

	// Try allocating enough memory to hold a Node
	Node* new_node = (Node*)malloc(sizeof(Node));

	// Sanity check
	if (!new_node) {
		*dst = NULL;
		return kokos_memory();
	}

	// Assign
	new_node->insel = insel;
	new_node->next = NULL;
	new_node->prev = NULL;
	*dst = new_node;

	return kokos_noerr();
}

/*
	Returns a pointer to the last Node element of node.
	If node doesn't have a next node, it will return itself.
	If the passed node was a nullptr, a nullptr will be returned.
*/
Node* _last_node(Node* node) {

	// Sanity check
	if (!node) return NULL;

	Node* last_node = node;

	while (last_node->next) {
		last_node = last_node->next;
	}

	return last_node;
}

/*
	Tries to push 'node' in 'into'.
	This function will push 'node' as the last element of 'into'.

	May return KokosError:NullPointerError
	if either 'into' or 'node' are nullptr.

	If no error occurred, a KokosError:None will be returned.
*/
KokosError node_push_back(Node* into, Node* node) {
	// Sanity check
	if (!into) {
		return kokos_nullptr(1);
	}

	// Sanity check
	if (!node) {
		return kokos_nullptr(2);
	}

	// Get the last node
	Node* last = _last_node(into);

	// Assign
	last->next = node;
	node->prev = last;

	return kokos_noerr();
}

/*
	Dequeues the last Node element in 'node'.
	If 'node' is the only element or 'node' is a nullptr, 
	this function will return a nullptr.
*/
Node* _node_dq(Node* node) {

	// Sanity check
	if (!node) return NULL;

	// Get the last node
	Node* last = _last_node(node);

	// Sanity check if node is the only Node
	if (last == node) return NULL;
	
	// Invalidate pointers
	last->prev->next = NULL;
	last->prev = NULL;

	return last;
}

/*
	Performs the cleanup of node.
	No-Op if node is a nullptr.
*/
void _cleanup_node(Node* node) {

	// Sanity check
	if (!node) return;

	/* 
		Free and invalidate the owned insel ptr.
	*/
	KokosError free_result = insel_free(node->insel);

	/*
		If node->insel is already null, then invalidation
		doesn't have to be handled.
	*/
	if (!kokos_has_error(&free_result)) {
		node->insel = NULL;
	}

	// Free the node itself
	free(node);
}

/*
	Frees a Node.
	This function will attempt to free a heap
	allocated Node, as well as all consecutive nodes 
	owned by 'node'.

	May return a KokosError:NullpointerError if node is a nullptr.
	If no error occurred, a KokosError:None will be returned.
*/
KokosError node_free(Node* node) {
	
	// Sanity check
	if (!node) {
		return kokos_nullptr(1);
	}

	// Try dequeue the last node owned by node
	Node* dq_node = _node_dq(node);

	/* 
		As long as there are Nodes owned by
		'node', perform cleanup and try to
		dequeue the next node
	*/
	while (dq_node) {
		_cleanup_node(dq_node);
		dq_node = _node_dq(node);
	}

	// Cleanup 'node' itself
	_cleanup_node(node);

	return kokos_noerr();
}

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
KokosError node_push_back_insel(Node* node, Insel* insel) {

	// Sanity check
	if (!node) {
		return kokos_nullptr(1);
	}

	// Sanity check
	if (!insel) {
		return kokos_nullptr(2);
	}

	Node* new_node;
	KokosError alloc_result = node_new(insel, &new_node);

	// Check if allocation succeeded
	if (kokos_has_error(&alloc_result)) {
		return alloc_result;
	}

	// Error handling can be ignored since both ptr are valid
	node_push_back(node, new_node);

	return kokos_noerr();
}