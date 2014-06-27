#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#ifdef __cplusplus
extern "C" {
#endif

struct st_huffman_node {
	char key;
	size_t freq;
	struct st_huffman_node *left;
	struct st_huffman_node *right;
};

struct st_huffman_node *create_huffman_tree(const size_t *freq)
{
}

void destroy_huffman_tree(struct st_huffman_node *root)
{
}

	
#ifdef __cplusplus
}
#endif
#endif
