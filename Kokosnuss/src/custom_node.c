#include <stdlib.h>
#include "custom_node.h"

/*
	Tries to allocate a new Node.
	The ptr to insel will be owned by the allocated Node.

	@insel insel to push into dst
	@dst the new node
	@return 1 if insel is a nullptr, 2 if allocation of a Node failed, otherwise 0
*/
int node_new(Insel* insel, Node** dst) {

	// Sanity check
	if (!insel) {
		return 1;
	}

	// Try allocating enough memory to hold a Node
	Node* new_node = (Node*)malloc(sizeof(Node));

	// Sanity check
	if (!new_node) {
		return 2;
	}

	// Assign
	new_node->insel = insel;
	new_node->next = NULL;
	new_node->prev = NULL;
	*dst = new_node;

	return 0;
}

/*
	Returns a pointer to the last Node element of node.
	If node doesn't have a next node, it will return itself.
	If the passed node was a nullptr, a nullptr will be returned.

	@node Node to find the last node for
	@return last Node
*/
Node* _last_node(Node* node) {

	// Sanity check
	if (!node) return NULL;

	Node* last_node = node;

	// Iterate through the nodes, to find the last one
	while (last_node->next) {
		last_node = last_node->next;
	}

	return last_node;
}

/*
	Tries to push 'node' as the last element of 'into'.

	@into Node where 'node' will be pushed into
	@node node to push
	@return 1 if into was a nullptr, 2 if node was a nullptr, otherwise 0
*/
int node_push_back(Node* into, Node* node) {
	// Sanity check
	if (!into) {
		return 1;
	}

	// Sanity check
	if (!node) {
		return 2;
	}

	// Get the last node
	Node* last = _last_node(into);

	// Assign
	last->next = node;
	node->prev = last;

	return 0;
}

/*
	Dequeues the last Node element in 'node'.
	If 'node' is the only element or 'node' is a nullptr, 
	this function will return a nullptr.

	@node Node where an element should be dequeued
	@return dequeued Node
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

	@node node to be freed
*/
void _cleanup_node(Node* node) {

	// Sanity check
	if (!node) return;

	// Free and invalidate the owned insel ptr.
	insel_free(node->insel);
	node->insel = NULL;

	// Free the node itself
	free(node);
}

/*
	This function will attempt to free a heap
	allocated Node, as well as all consecutive nodes 
	owned by 'node'.
	If node is a nullptr, this function is a No-Op.

	@node the node to be freed
*/
void node_free(Node* node) {

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
}

/*
	This function will push a new Node with insel
	as the last element of node.
	The Insel pointer will be owned by the new Node.

	@node node where element should be pushed
	@insel the insel to be owned by the new node
	@return 1 if node is a nullptr, 
			2 if insel is a nullptr, 
			3 if allocation of a new node failed
*/
int node_push_back_insel(Node* node, Insel* insel) {

	// Sanity check
	if (!node) {
		return 1;
	}

	// Sanity check
	if (!insel) {
		return 2;
	}

	Node* new_node;

	// Check if allocation succeeded
	if (node_new(insel, &new_node)) {
		return 3;
	}

	// Error handling can be ignored since both ptr are valid
	node_push_back(node, new_node);

	return 0;
}