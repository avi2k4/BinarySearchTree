//
//  main.cpp
//  BinarySearchTree
//
//  Created by Avighnash Kumar on 5/15/23.
//

#include <iostream>
#include <cstring>

struct TreeNode {
    int value;
    TreeNode * left;
    TreeNode * right;
};

class BinarySearchTree {
public:
    BinarySearchTree() {
        this->root = NULL;
    }
    
    /*
     Values to the right should be > 'value'
     */
    void add(int value) {
        struct TreeNode * new_node = new TreeNode();
        new_node->value = value;
        
        // If root doesn't exist then new_node is new root
        if (this->root == NULL) {
            this->root = new_node;
            return;
        }
        
        struct TreeNode * current = this->root;
        while (true) {
            // If value to the right is greater, then look at left
            if (current->value > value) {
                if (current->left != NULL) {
                    current = current->left;
                }
                // Can end loop early because spot is found
                else {
                    current->left = new_node;
                    return;
                }
            }
            else {
                if (current->right != NULL) {
                    current = current->right;
                }
                // Can end loop early because spot is found
                else {
                    current->right = new_node;
                    return;
                }
            }
        }
    }
    
    void del(int value) {
        if (this->root == NULL) {
            return;
        }
        
        struct TreeNode * previous = NULL;
        struct TreeNode * current = this->root;
        
        // BEGIN SEARCHING FOR NODE TO DELETE
        while (current != NULL && current->value != value) {
            previous = current;
            current = (value < current->value) ? current->left : current->right;
        }

        if (current == NULL) {
            return;
        }
        
        // To be deleted node has > 1 children
        if (current->left != NULL && current->right != NULL) {
            struct TreeNode * next = current->right;
            previous = current;
            
            // Locate next
            while (next->left != NULL) {
                previous = next;
                next = next->left;
            }
            
            current->value = next->value;
            current = next;
        }

        // To be deleted node has <= 1 children
        TreeNode * next = (current->left != NULL) ? current->left : current->right;

        // If root, then delete
        if (previous == NULL) {
            delete current;
            // IMPORTANT otherwise segfault
            this->root = NULL;
            return;
        }

        // Node to be deleted is not a root node
        if (current == previous->left) {
            previous->left = next;
        }
        else {
            previous->right = next;
        }

        delete current;
    }
    
    bool doesExist(int value) {
        bool result = false;
         
        struct TreeNode * current = this->root;
        while(true) {
            // If NULL or equal value, break
            if (current == NULL) {
                break;
            }
            
            // If current value is the same as 'value' then met criteria for true return
            if (current->value == value) {
                return true;
            }
            
            // If value to the right is greater, then set to left
            if (current->value > value) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
 
        return result;
    }
    
    void print() {
        if (this->root == NULL) {
            std::cout << "Tree is empty!" << std::endl;
            return;
        }
        
        this->printHelper(this->root, 0);
    }
    
private:
    TreeNode * root;
    
    void printHelper(struct TreeNode * current, int spacing) {
        if (current == NULL) {
            return;
        }
        
        this->printHelper(current->right, spacing + 3);
        
        // Prevents text from condensing
        std::cout << std::endl;

        // Increment till 'spacing' value
        for (int i = 0; i < spacing; i++) {
            std::cout << " ";
        }
        
        std::cout << current->value << std::endl;
        this->printHelper(current->left, spacing + 3);
    }
};

int main() {
    BinarySearchTree * tree = new BinarySearchTree();
    tree->add(15);
    tree->add(10);
    tree->add(1);
    tree->add(15);
    tree->add(10);
    tree->add(1);
    tree->print();
    
    tree->del(15);
    tree->del(10);
    tree->del(1);

    tree->print();

    std::cout << "Does exist 29: " << tree->doesExist(29) << std::endl;
    
    return 0;
}
