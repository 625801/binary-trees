#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct binarytree {
    int data;
    struct binarytree* left;
    struct binarytree* right;
} BinaryTree;

void createTree(BinaryTree** p, int x) {

if (!(*p)) {
        BinaryTree* pnew = (BinaryTree*) malloc(sizeof(BinaryTree));
        (*pnew).data = x;
        (*pnew).left = (*pnew).right = NULL;
        *p = pnew;
    } else {
        if ((**p).data > x) {
            createTree(&((**p).left), x);
        } else {
            createTree(&((**p).right), x);
        }
    }
}

int deleteNode(BinaryTree ** node, int data) {
    if ((*node) != NULL) {
        if ((**node).data == data) {
            if ((**node).left == NULL && (**node).right == NULL) {
                (*node) = NULL;
            } else if ((**node).left == NULL) {
                (*node) = (**node).right;
            } else if ((**node).right == NULL) {
                (*node) = (**node).left;
            } else {
                // saving the address of the node due to deletion
                BinaryTree* ptr = (*node);

                // setting the top element to equal the right branch
                (*node) = (**node).right;

                // saving the adress of the address of the tree to a variable
                BinaryTree ** ptr1;
                ptr1 = node;
                // traversing down the tree through the left branches
                // until left branch is null
                while (*ptr1 != NULL) {
                    ptr1 = &((**ptr1).left);
                }
                // assign the left branch of the original
                // node (the one we are deleting) to the found null branch
                (*ptr1) = ptr->left;
                free(ptr);
            }
            deleteNode(node, data);
        } else {
            deleteNode(&(**node).left, data);
            deleteNode(&(**node).right, data);
        }
    }
    return 0;
}

int traverseTreePrefix(BinaryTree* node) {
    if (node != NULL) {
        printf("%31d\n", node->data);
        traverseTreePrefix((*node).left);
        traverseTreePrefix((*node).right);
    }
    return 0;
}

int traverseTreeInfix(BinaryTree* node) {
    if (node != NULL) {
        traverseTreePrefix((*node).left);
        printf("%31d\n", node->data);
        traverseTreePrefix((*node).right);
    }
    return 0;
}

int traverseTreePostfix(BinaryTree* node) {
    if (node != NULL) {
        traverseTreePrefix((*node).left);
        traverseTreePrefix((*node).right);
        printf("%31d\n", node->data);
    }
    return 0;
}

bool isEmpty(BinaryTree* node) {
    if (node == NULL) {
        return true;
    } else {
        return false;
    }
}

int getLevelCount(BinaryTree * node)
{
    if (node == NULL)
    {
        return 0;
    }
    int leftMaxLevel = 1 + getLevelCount(node->left);
    int rightMaxLevel = 1 + getLevelCount(node->right);
    if (leftMaxLevel > rightMaxLevel)
    {
        return leftMaxLevel;
    }
    else
    {
        return rightMaxLevel;
    }
}

void printLevel(BinaryTree * node, int level)
{
    if (node != NULL && level == 0)
    {
        printf("%d ", node->data);
    }
    else if (node != NULL)
    {
        printLevel(node->left, level - 1);
        printLevel(node->right, level - 1);
    }
}

void printElements(BinaryTree * node)
{
    int i;
    int levelCount = getLevelCount(node);
    for (i = 0; i < levelCount; i++)
    {
        printLevel(node, i);
        printf("\n");
    }
}
void printTree(BinaryTree * node, int level) {
    int i;
    if (node != NULL) {
        printTree((*node).right, level + 1);

        for (i = 0; i < level; i++) {
            printf("   ");
        }
        printf("%d\n", (*node).data);

        printTree((*node).left, level + 1);
    }
}

int deleteTree(BinaryTree * node) {
   if (node != NULL) {
       deleteTree((*node).left);
       deleteTree((*node).right);
       free(node);
   }
   return 0;
}

int numberOfNodes(BinaryTree * node, int level, int currLevel) {
    if (node == NULL || currLevel > level) {
        return 0;
    }
    int leftCount, rightCount, currNodeCount;
    leftCount =  numberOfNodes((*node).left, level, currLevel + 1);
    rightCount =  numberOfNodes((*node).right, level, currLevel + 1);
    currNodeCount = 0;
    if (level == currLevel) {
        currNodeCount = 1;
    }
    return currNodeCount + leftCount + rightCount;
}


int main() {
    int i, n, temp, nodesCount;
    BinaryTree* root = NULL;
    printf("Enter a number of elements of a tree: ");
    scanf("%d", &n);
    printf("\nEnter the elements:\n");
    for (i = 0; i < n; i++) {
        printf("%d: ", i + 1);
        scanf("%d", &temp);
        createTree(&root, temp);
    }
    printf("The following tree is created (in the landscape mode):\n");
    printTree(root, 0);

    printf("\nEnter the level to count the nodes at: ");
    scanf("%d", &temp);
    nodesCount = numberOfNodes(root, temp, 0);
    printf("Number of nodes at level %d: %d\n", temp, nodesCount);
    deleteTree(root);
    return 0;
}