#include <stdio.h>
#include <malloc.h>
#include "tree.h"
/******************************************************************************/

void push(struct st_node *&tree, const int key)
{
	struct st_node *tmp=NULL;
	if (!(tree)) {
		tmp=(struct st_node*)malloc(sizeof(struct st_node));
		tmp->left = NULL;
		tmp->right= NULL;
		tmp->key  = key;
		tree      = tmp;
		return;
	}

	// assume all keys are distinct
	if (key < tree->key)
		push(tree->left,key);
	else
		push(tree->right,key);

	return;
}

struct st_node *seek(struct st_node *tree, const int key)
{
	if (!tree)
		return NULL;

	if (key==tree->key)
		return tree;

	if (key < tree->key)
		return seek(tree->left,key);
	else
		return seek(tree->right,key);
}

void deltree(struct st_node *tree)
{
	if (tree) {
		deltree(tree->left);
		deltree(tree->right);
		free(tree);
	}
}

struct st_node *pop (struct st_node *tree)
{
	if (!tree) return NULL;

	struct st_node *root=tree->right;
	while (root->left)
		root = root->left;
	root->left = tree->left;
	free(tree);

	return root;
}

// Assume keys are distinct.
struct st_node *crttree(const int n, int const *keys)
{
}

int nnode(struct st_node *tree)
{
	if (!tree) return 0;

	int n=1;
	n += nnode(tree->left);
	n += nnode(tree->right);
	return n;
}

int nleaf(struct st_node *tree)
{
	if (!tree) return 0; 
	if ( (!tree->left) && (!tree->right) ) return 1;

	int n=0;
	n += nleaf(tree->left);
	n += nleaf(tree->right);
	return n;
}

/******************************************************************************/
