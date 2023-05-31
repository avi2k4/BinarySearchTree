//
//  main.cpp
//  BinarySearchTree
//
//  Created by Avighnash Kumar on 5/15/23.
//

#include <iostream>
#include <fstream>
#include <cstring>

// Tree node struct declaration
struct TreeNode {
    int value;
    TreeNode * left;
    TreeNode * right;
};

// Binary search tree class declaration
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
        struct TreeNode * next = (current->left != NULL) ? current->left : current->right;

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
    
    std::cout << "How would you like to input numbers?" << std::endl;
    std::cout << "[1] file" << std::endl;
    std::cout << "[2] console" << std::endl;
    
    int method_input;
    std::cin >> method_input;
        
    if (method_input == 1) {
        std::cout << "Enter the name of the file" << std::endl;

        char file_name[100];
        std::cin >> file_name;
        
        std::ifstream file_input(file_name);
        
        if (!file_input) {
            std::cout << "File doesn't exit. Exiting." << std::endl;
            return 1;
        }
        
        int num_input;
        while (file_input >> num_input) {
            tree->add(num_input);
        }
        
        file_input.close();
    }
    else {
        std::cout << "Type each number and end with 9999 to signal the end of your input" << std::endl;

        int num_input = 0;
        
        while (num_input != 9999) {
            std::cin >> num_input;
            tree->add(num_input);
        }
    }
    
   
     std::cout << "\nHere are the commands to interact with the Binary Search Tree:" << std::endl;
     std::cout << "[1] to add a number" << std::endl;
     std::cout << "[2] to delete a number" << std::endl;
     std::cout << "[3] to check if a number exists in the tree" << std::endl;
     std::cout << "[4] to print the tree" << std::endl;
     std::cout << "[5] to end the program" << std::endl;
   

     while (true) {
	std::cout << "\nPerform a command" << std::endl;

        int cmd_input;
        std::cin >> cmd_input;
        
        if (cmd_input == 1) {
            std::cout << "Enter the number you want to add:" << std::endl;
            
            int input;
            std::cin >> input;
            
            tree->add(input);
            
            std::cout << "Successfully added " << input << std::endl;
        }
        else if (cmd_input == 2) {
            std::cout << "Enter the number you want to delete:" << std::endl;

            int input;
            std::cin >> input;
            
            tree->del(input);
            std::cout << "Successfully deleted " << input << std::endl;
        }
        else if (cmd_input == 3) {
            std::cout << "Enter the number you want to check:" << std::endl;
            
            int input;
            std::cin >> input;
        
            std::cout << "The number " << (tree->doesExist(input) ? "exists!" : "doesn't exist!") << std::endl;
        }
        else if (cmd_input == 4) {
            std::cout << "-------------------------------------" << std::endl;
            tree->print();
            std::cout << "-------------------------------------" << std::endl;
        }
        else if (cmd_input == 5) {
            break;
        }
    }
    
    return 0;
}
