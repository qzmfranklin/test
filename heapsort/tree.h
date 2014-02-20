#ifndef _TREE_H_
#define _TREE_H_
/******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

struct st_node {
	int key;
	struct st_node *left;
	struct st_node *right;
};

enum {
	PREORDER,
	INORDER,
	POSTORDER
};

int nnode(struct st_node *tree);
int nleaf(struct st_node *tree);
void push(struct st_node *&tree, const int key);
struct st_node *pop (struct st_node *tree);
struct st_node *seek(struct st_node *tree, const int key);
struct st_node *crttree(const int n, int const *keys);
void deltree(struct st_node *tree); 
	
#ifdef __cplusplus
}
#endif 
/******************************************************************************/
#endif
