//
// Created by Nickt on 10/08/2022.
//

#include <iostream>
#include <fstream>

struct node
{
    int value = 0;
    unsigned int numCount = 1;
    unsigned int leftCount = 0;
    unsigned int rightCount = 0;
    unsigned int depth = 0;
    node* left = nullptr;
    node* right = nullptr;
};

// Declarations
void add(node *root, int val);
node* build(std::ifstream &file);
unsigned int depth(node *node);
node* find(node *tree, int num);
void print(node *node);
void write(node *tree, std::ofstream &file);

int main()
{
    std::ofstream outfile("resources/output.txt");
    std::ifstream infile("resources/input.txt");

    std::cout << "=== Binary Search Tree Example ===\n" << std::endl;

    node *treeOne = build(infile);
    write(treeOne, outfile);

    node *root = find(treeOne, 5);

    if (root != nullptr)
    {
        print(root);
    }

    return 0;
}

// Definitions
/**
 * Recursive function.
 * Adds nodes to a binary search tree.
 * @param root Root node of the tree.
 * @param val Value to be stored within the new node.
 */
void add(node *root, int val)
{
    if (val > root->value)
    {
        if (root->right == nullptr)
        {
            root->right = new node;
            root->right->value = val;
        }
        else
        {
            add(root->right, val);
        }
    }
    else if (val < root->value)
    {
        if (root->left == nullptr)
        {
            root->left = new node;
            root->left->value = val;
        }
        else
        {
            add(root->left, val);
        }
    }
    else
    {
        root->numCount++;
    }
}

/**
 * Constructs a binary search tree from a file containing 1 number per line.
 * @param file The file to use for construction.
 * @return A pointer to the root node of the tree,
 */
node* build(std::ifstream &file)
{
    std::string line;
    node *root = new node;
    bool start = true;
    try
    {
        while(std::getline(file, line))
        {
            if (start)
            {
                // Setup root node
                root->value = std::stoi(line);
                start = false;
            }
            else
            {
                // Build tree
                add(root, std::stoi(line));
            }
        }
    } catch (std::invalid_argument const &e)
    {
        std::cout << "Error: cannot parse " << line << " to int " << std::endl;
    }

    depth(root);

    return root;
}

/**
 * Recursive function.
 * Determines the maximum depth of a binary search tree.
 * @param tree Tree to be traversed.
 * @return int, maximum depth.
 */
unsigned int depth(node *node)
{
    if (node->left != nullptr)
    {
        node->leftCount = depth(node->left) + 1;
    }

    if (node->right != nullptr)
    {
        node->rightCount = depth(node->right) + 1;
    }

    node->depth = std::max(node->leftCount, node->rightCount);
    return node->depth;
}

/**
 * Recursive function.
 * Depth First Search. O(n)
 * Finds the node within a binary search tree that matches the given value.
 * @param tree Tree to be traversed.
 * @param num Value to search for.
 * @return A pointer to the node matching the given value, or nullptr if no match is found.
 */
node* find(node *tree, const int num)
{
    if (num == tree->value)
    {
        return tree;
    }
    else if (num < tree->value && tree->left != nullptr)
    {
        find(tree->left, num);
    }
    else if (num > tree->value && tree->right != nullptr)
    {
        find(tree->right, num);
    }
    else
    {
        std::cout << num << " was not found" << std::endl;
        return nullptr;
    }
}

/**
 * Prints node details to console.
 * @param node Node to be printed.
 */
void print(node *node)
{
    std::cout << "Node: " << node->value << std::endl;
    std::cout << "Occurrences: " << node->numCount << std::endl;
    std::cout << "Depth: " << node->depth << "\n" << std::endl;
}

/**
 * Traverses given tree from left to right.
 * Writes values and occurrences of each node to file.
 * @param tree Tree to be traversed.
 * @param file Output file.
 */
void write(node *tree, std::ofstream &file)
{
    // Print Left first
    file << "Node Value: " << tree->value << ", Occurrences: " << tree->numCount << std::endl;
    if(tree->left != nullptr)
    {
        write(tree->left, file);
    }

    if(tree->right != nullptr)
    {
        write(tree->right, file);
    }
}