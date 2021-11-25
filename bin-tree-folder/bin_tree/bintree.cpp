#include "bintree.h"

// FILE: bintree.template
// IMPLEMENTS: The binary_tree node class (see bintree.h for documentation).
#include <cassert>  // Provides assert
#include <cstdlib>  // Provides NULL, std::size_t
#include <iomanip>  // Provides std::setw
#include <iostream> // Provides std::cout
namespace main_savitch_10
{
    void inorder(binary_tree_node *node_ptr)
    // Library facilities used: cstdlib
    {
        if (node_ptr != NULL)
        {
            inorder(node_ptr->left());
            std::cout << node_ptr->data() << " ";
            inorder(node_ptr->right());
        }
    }

    void tree_clear(binary_tree_node *&root_ptr)
    // Library facilities used: cstdlib
    {
        binary_tree_node *child;
        
        if (root_ptr != NULL)
        {
            child = root_ptr->left();
            tree_clear(child);
            child = root_ptr->right();
            tree_clear(child);
            delete root_ptr;
            root_ptr = NULL;
        }
    }

    binary_tree_node *insert(binary_tree_node *node, int key)
    {
        if (node == NULL)
            return new binary_tree_node(key);

        if (key < node->data())
            node->set_left(insert(node->left(), key));
        else if (key > node->data())
            node->set_right(insert(node->right(), key));
        return node;
    }

    binary_tree_node *tree_copy(const binary_tree_node *root_ptr)
    // Library facilities used: cstdlib
    {
        binary_tree_node *l_ptr;
        binary_tree_node *r_ptr;
        if (root_ptr == NULL)
            return NULL;
        else
        {
            l_ptr = tree_copy(root_ptr->left());
            r_ptr = tree_copy(root_ptr->right());
            return new binary_tree_node(root_ptr->data(), l_ptr, r_ptr);
        }
    }

    size_t tree_size(const binary_tree_node *node_ptr)
    // Library facilities used: cstdlib
    {
        if (node_ptr == NULL)
            return 0;
        else
            return 1 + tree_size(node_ptr->left()) + tree_size(node_ptr->right());
    }
} // namespace main_savitch_10

