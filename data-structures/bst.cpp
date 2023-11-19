#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

struct node {
  int data;
  node *left;
  node *right;
};

node *initNode(int key) {
  node *result = new node;
  result->data = key;
  result->left = NULL;
  result->right = NULL;

  return result;
}

// Binary Search Tree
class BST {
private:
  node *root;

  node *insert(node *, int);
  node *search(node *, int);
  node *remove(node *, int);

  void inorder(node *);
  void preorder(node *);
  void postorder(node *);
  void levelorder(node *);

  // auxiliary methods
  void destroyTree(node *);
  bool isLeaf(node *);
  int getDepth(node *);
  int getLength(node*);
  node *findMin(node *);
  node *findMax(node *);

public:
  BST();
  BST(int);
  ~BST();

  node *search(int);
  node *insert(int);
  node *remove(int);

  void print();
  void prettyPrint(node *, const string &);

  node *getRoot();
  int getDepth();
  int getLength();
};

BST::BST() : root(nullptr) {}
BST::BST(int data) { root = initNode(data); }
BST::~BST() {
  destroyTree(root);
  cout << "The tree was deleted;\n";
}

//
// data operations
//
node *BST::insert(int data) {
  if (root == NULL) { // the tree is empty
    root = initNode(data);
    return root;
  } else {
    return insert(root, data); // creates new leaf
  }
}

node *BST::insert(node *parent, int data) {
  if (data < parent->data) { // new leaf at left

    if (parent->left != NULL)
      return insert(parent->left, data);
    else { // only root is created
      parent->left = initNode(data);
      return parent->left;
    }

  } else { // new leaf at right
           //
    if (parent->right != NULL)
      return insert(parent->right, data);
    else { // only root is created
      parent->right = initNode(data);
      return parent->right;
    }
  }
}

node *BST::remove(int data) { return remove(root, data); }

node *BST::remove(node *parent, int data) {

  if (parent == NULL) // the tree is empty
    return NULL;

  if (data < parent->data)
    parent->left = remove(parent->left, data);

  else if (data > parent->data)
    parent->right = remove(parent->right, data);

  else { // the key was found
    if (isLeaf(parent)) {
      // the node has no children (just delete it)
      //
      delete parent;
      parent = NULL;
    } else if (parent->left && parent->right) {
      // the node has left and right children
      //
      // steps:
      //  - find the minimum leaf on the right subtree and copy its data
      //  - delete the minimum node
      //
      node *aux = findMin(parent->right);
      parent->data = aux->data;
      parent->right = remove(parent->right, parent->data);

    } else {
      // the node has only one child
      //
      if (parent->right == NULL)
        parent = parent->left;
      else if (parent->left == NULL)
        parent = parent->right;
    }
  }

  return parent;
}

//
// search operations
//
node *BST::search(int data) {
  return search(root, data); // starts from the root node
}

node *BST::search(node *parent, int data) {
  if (parent == NULL) { // the tree is empty or could not find
    printf("Could not find node(%d)\n", data);
    return NULL;
  } else if (data == parent->data) { // found the element
    printf("node(%d) has address: %p.\n", parent->data, &parent);
    return parent;
  } else if (data < parent->data)
    return search(parent->left, data); // go search in the left node
  else
    return search(parent->right, data); // go search in the right node
}

//
// displaying
//
void BST::print() {
  cout << "\nTree Depth: " << getDepth();

  cout << "\nTree Length: " << getLength();

  cout << "\nIn-Order: ";
  inorder(root);

  cout << "\nPre-Order: ";
  preorder(root);

  cout << "\nPost-Order: ";
  postorder(root);

  cout << "\nLevel-Order: ";
  levelorder(root);

  cout << endl << endl;
}

void BST::inorder(node *n) { // ordered by data
  if (n == NULL)
    return;

  inorder(n->left);
  cout << n->data << " ";
  inorder(n->right);
}

void BST::preorder(node *n) { // parent comes first
  if (n == NULL)
    return;

  cout << n->data << " ";
  preorder(n->left);
  preorder(n->right);
}

void BST::postorder(node *n) { // parent comes after
  if (n == NULL)
    return;

  postorder(n->left);
  postorder(n->right);
  cout << n->data << " ";
}

void BST::levelorder(node *parent) {
  if (parent != NULL) {

    queue<node *> q;

    q.push(parent);

    // deque root node, enque left and right children.
    // exit loop when queue is empty.
    while (!q.empty()) {
      node *aux = q.front();
      cout << aux->data << " ";

      if (aux->left)
        q.push(aux->left);

      if (aux->right)
        q.push(aux->right);

      q.pop(); // remove the element at the front
    }
  }
}

void BST::prettyPrint(node *root, const string &prefix) {
  if (root == NULL)
    return;

  bool hasLeft = (root->left != NULL);
  bool hasRight = (root->right != NULL);

  if (!hasLeft && !hasRight)
    return;

  cout << prefix;
  cout << ((hasLeft && hasRight) ? "├── " : "");
  cout << ((!hasLeft && hasRight) ? "└── " : "");

  if (hasRight) {
    bool printStrand =
        (hasLeft && hasRight &&
         (root->right->right != NULL || root->right->left != NULL));
    string newPrefix = prefix + (printStrand ? "│   " : "    ");
    cout << root->right->data << endl;
    prettyPrint(root->right, newPrefix);
  }

  if (hasLeft) {
    cout << (hasRight ? prefix : "") << "└── " << root->left->data << endl;
    prettyPrint(root->left, prefix + "    ");
  }
}

//
// auxiliary functions
//
node *BST::getRoot() { return root; }

int BST::getDepth() { return getDepth(root); }

int BST::getDepth(node *n) {
  // the depth of a node is the distance from the root
  if (n == NULL)
    return 0;

  int leftDepth = getDepth(n->left);
  int rightDepth = getDepth(n->right);

  return max(leftDepth, rightDepth) + 1;
}

int BST::getLength() { return getLength(root); }

int BST::getLength(node *parent) {
  if (parent == NULL)
    return 0;

  int leftCount = getLength(parent->left);
  int rightCount = getLength(parent->right);

  return 1 + leftCount + rightCount;
}

bool BST::isLeaf(node *parent) {
  if (parent != NULL && parent->left == NULL && parent->right == NULL)
    return true;

  return false;
}

node *BST::findMin(node *n) {
  if (n == NULL)
    return n;
  else if (n->left == NULL)
    return n;
  else
    return findMin(n->left);
}

node *BST::findMax(node *n) {
  if (n == NULL)
    return n;
  else if (n->right == NULL)
    return n;
  else
    return findMax(n->right);
}

// destruction
void BST::destroyTree(node *parent) {
  if (parent != NULL) {
    destroyTree(parent->left);
    destroyTree(parent->right);
  }

  delete parent;
}

int main() {

  cout << "\n===========\n BST \n===========\n" << endl;
  cout << "time complexity: O(n)\n";
  cout << "avarage space complexity:\n - O(n) worst case\n - O(1) best case\n"
       << endl;

  BST *tree = new BST(10);

  tree->insert(20);
  tree->insert(5);
  tree->insert(3);
  tree->insert(41);
  tree->insert(39);
  tree->insert(4);
  tree->insert(6);
  tree->insert(123);
  tree->insert(456);

  tree->remove(6);
  tree->remove(100);

  cout << tree->getRoot()->data << endl;

  tree->prettyPrint(tree->getRoot(), "");
  tree->print();

  node *found = tree->search(40);
  node *notFound = tree->search(100);

  delete tree;
}
