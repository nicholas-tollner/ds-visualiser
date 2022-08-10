//
// Created by Nickt on 10/08/2022.
//

#include <iostream>

struct node
{
    int value = 0;
    unsigned int numCount = 0;
    unsigned int leftCount = 0;
    unsigned int rightCount = 0;
    node* left = nullptr;
    node* right = nullptr;

};

// Declarations
void add(node* root, int val);

int main()
{
    node *root = new node;

    std::cout << "Binary Search Tree Example" << std::endl;

    // Define root node value
    root->value = 32;
    int arr[] = {3,8,9,1,56,78,1,4,10,90, 3, 56, 32, 10, 90, 90, 90, 1, 3};

    for (int num : arr)
    {
        std::cout << "Adding : " << num << std::endl;
        add(root, num);
    }


    return 0;
}

// Definitions
void add(node* root, int val)
{
    if (val > root->value)
    {
        root->rightCount++;

        std::cout << "val: " << val << " > root->value: " << root->value << std::endl;

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
        std::cout << "val: " << val << " < root->value: " << root->value << std::endl;

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
    return;
}


