/* recursive_dfs.c -- serial recursive depth-first search.  Generates
 *     a random tree and uses recursive depth-first search to visit
 *     the nodes in the tree and find the leaf node with minimum
 *     value.
 *
 * Input:
 *     max_depth:  the maximum depth of a node in the tree.
 *
 * Output:
 *     1. The tree
 *     2. A list of the nodes visited by depth-first search
 *     3. The value of the minimum node.
 *
 * Algorithm:
 *     1. Get max_depth
 *     2. Set each entry in array storing tree to NULL
 *     3. Recursive function Generate_tree uses rand function
 *        to generate random tree.
 *     4. Use recursive depth-first search to find leaf with
 *        minimum value.
 *     5. Print minimum value.
 *
 * Data structures:
 *     The tree is a statically allocated array of pointers to
 * TREE_NODE_T.  Each tree node has a value -- a randomly
 * generated int with the property that the value assigned
 * to a parent is less than the value assigned to each of
 * its children.  Each tree node also stores the subscript of
 * its parent (-1 for root), its depth, the number of its
 * children, and subscripts of children.  The type NODE_T is
 * the subscript of the node in the tree array.
 *
 * Notes:
 *     1.  MAX_NODES (the maximum number of nodes in a tree) should be 
 * chosen so that it's at least as large as
 *      1 - c^(d+1)
 *     --------    
 *      1 - c
 * where c = MAX_CHILDREN and d = max_depth
 *     2.  The array storing the tree, and the current "best solution"
 * are global.
 *
 * See Chap. 14, pp. 324 & ff., in PPMPI.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDREN 3
#define MAX_NODES 1093
#define MAX_VALUE 1024
#define FALSE 0
#define TRUE  1

typedef struct {
    int  value;
    int  parent;
    int  depth;
    int  child_count;
    int  children[MAX_CHILDREN];
} TREE_NODE_T;

typedef TREE_NODE_T* TREE_T[MAX_NODES];
#define Child(tree, node, i)  ((tree)[(node)]->children[(i)])
#define Parent(tree, node) ((tree)[(node)]->parent)
#define Depth(tree, node)  ((tree)[(node)]->depth)
#define Value(tree, node)  ((tree)[(node)]->value)
#define Child_count(tree,node) ((tree)[(node)]->child_count)

/*-------------------------------------------------------------------*/
typedef int NODE_T;  /* Just the index of the node in the tree */

/*-------------------------------------------------------------------*/
/* GLOBALS */
int best_solution;
TREE_T  tree;

/*-------------------------------------------------------------------*/
void Initialize_tree(TREE_T tree, int max_nodes);
void Generate_tree(TREE_T tree, int max_depth, 
         int* node_count, int parent_depth, int parent);
void Alloc_node(TREE_T tree, int node);
void Print_tree(TREE_T tree, int node_count);

/*-------------------------------------------------------------------*/
void Dfs_recursive(NODE_T node);
void Expand(NODE_T node, NODE_T child_list[], int* num_children);
int Solution(NODE_T node);
int Evaluate(NODE_T node);
int Feasible(NODE_T node);
/*-------------------------------------------------------------------*/


/********************************************************************/
main() {
    int     max_depth;
    int     max_nodes = MAX_NODES;
    int     node_count;

    printf("What's the maximum depth of a node?\n");
    scanf("%d", &max_depth);

    Initialize_tree(tree, max_nodes);
    node_count = 0;

    /* "-1" indicates node being generated is the root */ 
    Generate_tree(tree, max_depth, &node_count, -1, -1);

    Print_tree(tree, node_count);

    best_solution = 2*MAX_VALUE;
    Dfs_recursive(0);
    printf("The best solution is %d\n", best_solution);
    
}  /* main */


/********************************************************************/
void Initialize_tree(
         TREE_T  tree       /* out */,
         int     max_nodes  /* in  */) {
    int i;

    for (i = 0; i < max_nodes; i++)
        tree[i] = (TREE_NODE_T*) NULL;
}  /* Initialize_tree */


/********************************************************************/
/* Adds current value in *node_count to tree */
void Generate_tree(
         TREE_T  tree          /* out    */,
         int     max_depth     /* in     */,
         int*    node_count    /* in/out */,
         int     parent_depth  /* in     */,
         int     parent        /* in     */) {
    int i = 0;
    int node = *node_count;
    
    Alloc_node(tree, node);
    Depth(tree,node) = parent_depth+1;
    if (parent == -1)
        Value(tree,node) = rand() % MAX_VALUE;
    else
        Value(tree,node) = (rand() % (MAX_VALUE/(1 << Depth(tree,node))))
            + Value(tree, parent);
    Parent(tree,node) = parent;

    if (Depth(tree,node) != max_depth) {
        while ( (i < MAX_CHILDREN) && (rand() % MAX_CHILDREN) ) {
            *node_count = *node_count + 1;
            Child_count(tree,node) = Child_count(tree,node)+1;
            Child(tree, node, i) = *node_count;
            Generate_tree(tree, max_depth, node_count, Depth(tree,node),
                node);
            i++;
        } /* while */
    }  /* if */
    if (node == 0)
        *node_count = *node_count + 1;

}  /* Generate_tree */


/********************************************************************/
void Alloc_node(
         TREE_T  tree  /* in/out */, 
         int     node  /* in     */) {
    int i;

    tree[node] = (TREE_NODE_T*) malloc(sizeof(TREE_NODE_T));
    for (i = 0; i < MAX_CHILDREN; i++)
        Child(tree, node, i) = -1;
    Child_count(tree, node) = 0;
}  /* Alloc_node */


/********************************************************************/
void Print_tree(
         TREE_T  tree        /* in */,
         int     node_count  /* in */) {
    int node, i;

    printf("node_count = %d\n", node_count);
    for (node = 0; node < node_count; node++) {
        printf("---------------------------------------------------\n");
        printf("Node = %d, Value = %d\n", node, Value(tree, node));
        printf("Parent = %d, Depth = %d, Child_count = %d\n",
            Parent(tree,node), Depth(tree,node), Child_count(tree,node));
        printf("Children = ");
        for (i = 0; i < Child_count(tree, node); i++)
            printf("%d ",Child(tree,node,i));
        printf("\n");
    }
    printf("---------------------------------------------------\n");
}  /* Print_tree */


/********************************************************************/
/********************************************************************/
void Dfs_recursive(
         NODE_T node  /* in */) {
    int    i;
    int    num_children;
    NODE_T child_list[MAX_CHILDREN];

    printf("Visiting Node %d\n", node);

    Expand(node, child_list, &num_children);

    for (i = 0; i < num_children; i++)
        if (Solution(child_list[i])) {
            if (Evaluate(child_list[i]) < best_solution)
                best_solution = Evaluate(child_list[i]);
        } else if (Feasible(child_list[i])) {
            Dfs_recursive(child_list[i]);
        }
} /* Dfs_recursive */


/********************************************************************/
void Expand(
         NODE_T  node          /* in  */, 
         NODE_T  child_list[]  /* out */, 
         int*    num_children  /* out */) {
    int i;

    *num_children = Child_count(tree, node);
    for (i = 0; i < *num_children; i++)
        child_list[i] = Child(tree,node,i);
}  /* Expand */


/********************************************************************/
/* A solution node has no children */
int Solution(
       NODE_T node /* in */) {
    if (Child_count(tree,node) == 0)
        return TRUE;
    else
        return FALSE;
}  /* Solution */


/********************************************************************/
int Evaluate(
        NODE_T node /* in */) {
    return Value(tree,node);
}  /* Evaluate */


/********************************************************************/
int Feasible(NODE_T node) {
    if (Value(tree,node) < best_solution)
        return TRUE;
    else
        return FALSE;
}  /* Feasible */
