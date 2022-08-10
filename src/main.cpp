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
    node* left = nullptr;
    node* right = nullptr;

};

// Declarations
void add(node *root, int val);
node* build(std::ifstream &file);
void print(node *tree, std::ofstream &file);

int main()
{
    std::ofstream outfile("resources/output.txt");
    std::ifstream infile("resources/input.txt");

    std::cout << "Binary Search Tree Example" << std::endl;

    node *treeOne = build(infile);

    print(treeOne, outfile);

    return 0;
}

// Definitions
void add(node *root, int val)
{
    if (val > root->value)
    {
        root->rightCount++;

        std::cout << "val: " << val << " > node->value: " << root->value << std::endl;

        if (root->right == nullptr)
        {
            root->right = new node;
            root->right->value = val;
            std::cout << "Created new node with value: " << val << std::endl;
        }
        else
        {
            add(root->right, val);
        }
    }
    else if (val < root->value)
    {
        root->leftCount++;
        std::cout << "val: " << val << " < node->value: " << root->value << std::endl;

        if (root->left == nullptr)
        {
            root->left = new node;
            root->left->value = val;
            std::cout << "Created new node with value: " << val << std::endl;
        }
        else
        {
            add(root->left, val);
        }
    }
    else
    {
        root->numCount++;
        std::cout << "Incrementing numCount: " << root->numCount << std::endl;
    }
}

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

    return root;
}

void print(node* tree, std::ofstream &file)
{
    // Print Left first
    file << "Node Value: " << tree->value << ", Occurrences: " << tree->numCount << std::endl;
    if(tree->left != nullptr)
    {
        print(tree->left, file);
    }

    if(tree->right != nullptr)
    {
        print(tree->right, file);
    }
}




