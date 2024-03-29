#include "tree.h"

//static-----------------------------------------------------------------------

static void TreeDumpNode(const TreeNode* node,
                         FILE* dump_file,
                         DumpTreeNodeFunc* DumpNode);

//global-----------------------------------------------------------------------

void TreeCtor(Tree* tree) {
  ASSERT(tree != NULL);

  tree->root.l_child = NULL;
  tree->root.r_child = NULL;
  tree->root.parent = NULL;
}

void TreeDtor(Tree* tree) {
  ASSERT(tree != NULL);

  TreeDtorNode(tree->root.l_child);
  TreeDtorNode(tree->root.r_child);
}

void TreeDotDump(const Tree* tree, DumpTreeNodeFunc* DumpNode) {
  FILE* dump_file = fopen("dump_tree.dot", "w");
  if (dump_file == NULL) { return; }

  fprintf(dump_file, "digraph {\n");
  // fprintf(dump_file, "rankdir=LR\n");
  TreeDumpNode(tree->root.l_child, dump_file, DumpNode);
  TreeDumpNode(tree->root.r_child, dump_file, DumpNode);
  fprintf(dump_file, "}\n");

  fclose(dump_file);
}

TreeNode* TreeCtorNode(TreeElem* data, TreeNode* parent) {
  ASSERT(data != NULL);
  // ASSERT(parent != NULL);

  TreeNode* new_node = (TreeNode*)calloc(1, sizeof(TreeNode));
  if (new_node == NULL) { return NULL; }

  memcpy(&new_node->data, data, sizeof(TreeElem));

  new_node->parent = parent;

  return new_node;
}

Counter TreeDtorNode(TreeNode* node) {
  if (node == NULL) { return 0; }

  Counter cnt = 0;

  cnt += TreeDtorNode(node->l_child);
  cnt += TreeDtorNode(node->r_child);
  free(node);

  return cnt + 1;
}

//static-----------------------------------------------------------------------

static void TreeDumpNode(const TreeNode* node,
                         FILE* dump_file,
                         DumpTreeNodeFunc* DumpNode) {
  ASSERT(dump_file != NULL);
  ASSERT(DumpNode != NULL);

  if (node == NULL) { return; }

  DumpNode(node, dump_file);

  TreeDumpNode(node->l_child, dump_file, DumpNode);
  TreeDumpNode(node->r_child, dump_file, DumpNode);
}
