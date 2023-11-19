#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

struct node {
  int data;
  int height; // A node’s height is the number of edges to
              // its most distant leaf node
  node *left;
  node *right;
};

node *initNode(int key) {
  node *result = new node;

  result->data = key;
  result->height = 0;
  result->left = NULL;
  result->right = NULL;

  return result;
}

// Binary Search Tree
class AVL {
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
  node *rightRotate(node *);
  node *leftRotate(node *);
  int maxDepth(node *);
  int getHeight(node *);
  int getLength(node *);
  int getBalance(node *);
  node *findMin(node *);

  void destroyTree(node *);

public:
  AVL();
  AVL(int);
  ~AVL();

  node *search(int);
  node *insert(int);
  node *remove(int);

  void print();
  void prettyPrint(node *, const string &);

  node *getRoot();
  int maxDepth();
  int getHeight();
  int getLength();
};

AVL::AVL() : root(nullptr) {}
AVL::AVL(int data) { root = initNode(data); }
AVL::~AVL() {
  destroyTree(root);
  cout << "The tree was deleted;\n";
}

//
// data operations
//
node *AVL::insert(int data) {
  return insert(root, data); // creates new leaf
}

node *AVL::insert(node *parent, int data) {
  if (parent == NULL) {
    parent = initNode(data);
    return parent;
  }

  if (data < parent->data) {
    parent->left = insert(parent->left, data);
  } else {
    parent->right = insert(parent->right, data);
  }

  // updates height of the new node ancestor
  parent->height = 1 + max(getHeight(parent->left), getHeight(parent->right));

  int balance = getBalance(parent); // 0 means the tree is balanced

  // Left Left Case
  if (balance > 1 && data < parent->left->data)
    return rightRotate(parent);

  // Right Right Case
  if (balance < -1 && data > parent->right->data)
    return leftRotate(parent);

  // Left Right Case
  if (balance > 1 && data > parent->left->data) {
    parent->left = leftRotate(parent->left);
    return rightRotate(parent);
  }

  // Right Left Case
  if (balance < -1 && data < parent->right->data) {
    parent->right = rightRotate(parent->right);
    return leftRotate(parent);
  }

  // returns the (unchanged) root
  return parent;
}

// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
node *AVL::rightRotate(node *y) {
  node *x = y->left;
  node *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

  // Return new root
  return x;
}

// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
node *AVL::leftRotate(node *x) {
  node *y = x->right;
  node *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights
  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

  // Return new root
  return y;
}

node *AVL::remove(int data) { return remove(root, data); }

// node *AVL::remove(node *parent, int data) {}
node *AVL::remove(node *root, int data) {

  // STEP 1: PERFORM STANDARD BST DELETE
  if (root == NULL)
    return root;

  // If the key to be deleted is smaller
  // than the root's key, then it lies
  // in left subtree
  if (data < root->data)
    root->left = remove(root->left, data);

  // If the key to be deleted is greater
  // than the root's key, then it lies
  // in right subtree
  else if (data > root->data)
    root->right = remove(root->right, data);

  // if key is same as root's key, then
  // This is the node to be deleted
  else {
    // node with only one child or no child
    if ((root->left == NULL) || (root->right == NULL)) {
      node *temp = root->left ? root->left : root->right;

      // No child case
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else           // One child case
        *root = *temp; // Copy the contents of
                       // the non-empty child
      free(temp);
    } else {
      // node with two children: Get the inorder
      // successor (smallest in the right subtree)
      node *temp = findMin(root->right);

      // Copy the inorder successor's
      // data to this node
      root->data = temp->data;

      // Delete the inorder successor
      root->right = remove(root->right, temp->data);
    }
  }

  // If the tree had only one node
  // then return
  if (root == NULL)
    return root;

  // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
  root->height = 1 + max(getHeight(root->left), getHeight(root->right));

  // STEP 3: GET THE BALANCE FACTOR OF
  // THIS NODE (to check whether this
  // node became unbalanced)
  int balance = getBalance(root);

  // If this node becomes unbalanced,
  // then there are 4 cases

  // Left Left Case
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  // Left Right Case
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  // Right Right Case
  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  // Right Left Case
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

//
// search operations
//
node *AVL::search(int data) {
  return search(root, data); // starts from the root node
}

node *AVL::search(node *parent, int data) {
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
void AVL::print() {
  cout << "\nTree Depth: " << maxDepth();

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

void AVL::inorder(node *n) { // ordered by data
  if (n == NULL)
    return;

  inorder(n->left);
  cout << n->data << " ";
  inorder(n->right);
}

void AVL::preorder(node *n) { // parent comes first
  if (n == NULL)
    return;

  cout << n->data << " ";
  preorder(n->left);
  preorder(n->right);
}

void AVL::postorder(node *n) { // parent comes after
  if (n == NULL)
    return;

  postorder(n->left);
  postorder(n->right);
  cout << n->data << " ";
}

void AVL::levelorder(node *parent) {
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

void AVL::prettyPrint(node *root, const string &prefix) {
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
    printf("%d(%d)\n", root->right->data, root->right->height);
    prettyPrint(root->right, newPrefix);
  }

  if (hasLeft) {
    printf("%s└──%d(%d)\n", (hasRight ? prefix : "").c_str(), root->left->data,
           root->left->height);
    prettyPrint(root->left, prefix + "    ");
  }
}

//
// auxiliary functions
//
node *AVL::getRoot() { return root; }

int AVL::getBalance(node *parent) {
  return getHeight(parent->left) - getHeight(parent->right);
}

int AVL::getHeight() { return getHeight(root); }

int AVL::getHeight(node *n) {
  if (n == NULL)
    return -1;

  return n->height;
}

int AVL::maxDepth() {
  return maxDepth(root);
} // returns the depth of the entire tree

int AVL::maxDepth(node *n) {
  if (n == NULL)
    return 0;

  int leftDepth = maxDepth(n->left);
  int rightDepth = maxDepth(n->right);

  return max(leftDepth, rightDepth) + 1;
}

int AVL::getLength() { return getLength(root); }

int AVL::getLength(node *parent) {
  if (parent == NULL)
    return 0;

  int leftCount = getLength(parent->left);
  int rightCount = getLength(parent->right);

  return 1 + leftCount + rightCount;
}

node *AVL::findMin(node *n) {
  if (n == NULL)
    return n;
  else if (n->left == NULL)
    return n;
  else
    return findMin(n->left);
}

//
// destruction
//
void AVL::destroyTree(node *parent) {
  if (parent != NULL) {
    destroyTree(parent->left);
    destroyTree(parent->right);
  }

  delete parent;
}

int main() {

  cout << "\n===========\n AVL (self-balancing BST)\n===========\n" << endl;
  cout << "time complexity: O(log n)\n" << endl;

  AVL *tree = new AVL(10);

  tree->insert(20);
  tree->insert(5);
  tree->insert(80);
  tree->insert(4);
  tree->insert(3);
  tree->insert(8);

  tree->remove(4);

  printf("%d(%d)\n", tree->getRoot()->data, tree->getHeight());

  tree->prettyPrint(tree->getRoot(), "");
  tree->print();
  
  node *found = tree->search(3);
  node *notFound = tree->search(100);

  delete tree;
}
