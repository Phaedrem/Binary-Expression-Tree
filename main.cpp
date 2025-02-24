#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

// Definition of the TreeNode template class
template <typename T>
class TreeNode {
public:
    T value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T val) : value(val), left(nullptr), right(nullptr) {}
};

// Helper function to parse a subexpression and build the tree
template <typename T>
TreeNode<T>* parseExpression(const string& expression, int& index) {
    TreeNode<T>* root = nullptr;

    while (index < expression.size()) {
        if (expression[index] == '(') {
            index++;  // Skip '('
            TreeNode<T>* subTree = parseExpression<T>(expression, index);
            if (root == nullptr) {
                root = subTree;
            } else if (root->left == nullptr) {
                root->left = subTree;
            } else {
                root->right = subTree;
            }
        } else if (isalnum(expression[index])) {
            // Handle both multi-digit numbers and single-character operands
            string operand;
            if (isdigit(expression[index])) {
                // Collect full multi-digit number
                while (index < expression.size() && isdigit(expression[index])) {
                    operand += expression[index];
                    index++;
                }
            } else {
                // Single alphabetic character operand (e.g., 'A', 'B', etc.)
                operand = expression[index];
                index++;
            }
            TreeNode<T>* newNode = new TreeNode<T>(operand);  // Store operand as string
            if (root == nullptr) {
                root = newNode;
            } else if (root->left == nullptr) {
                root->left = newNode;
            } else {
                root->right = newNode;
            }
        } else if (expression[index] == '+' || expression[index] == '-' || expression[index] == '*' || expression[index] == '/') {
            // Operator node
            string op(1, expression[index]);  // Convert char to string
            TreeNode<T>* newNode = new TreeNode<T>(op);
            newNode->left = root;  // Set the current root as left child of the new operator
            root = newNode;        // Update root to the new operator node
            index++;
        } else {
            index++;
        }
    }
    return root;
}

// In-order traversal
template <typename T>
void inOrder(TreeNode<T>* node, string& result) {
    if (node != nullptr){
    inOrder(node->left, result);
    result += node->value + " ";
    inOrder(node->right, result);
    }
}

// Pre-order traversal
template <typename T>
void preOrder(TreeNode<T>* node, string& result) {
    if (node != nullptr){
    result += node->value + " ";
    preOrder(node->left, result);
    preOrder(node->right, result);
    }
}

// Post-order traversal
template <typename T>
void postOrder(TreeNode<T>* node, string& result) {
    if (node != nullptr){
    postOrder(node->left, result);
    postOrder(node->right, result);
    result += node->value + " ";
    }
}

// Main function to convert expression and print results
template <typename T>
void convertExpression(const string& expression) {
    int index = 0;
    TreeNode<T>* root = parseExpression<T>(expression, index);

    // Generate pre-order, in-order, and post-order traversals
    string preOrderResult, inOrderResult, postOrderResult;
    preOrder(root, preOrderResult);
    inOrder(root, inOrderResult);
    postOrder(root, postOrderResult);

    // Output results
    cout << "Pre-order: " << preOrderResult << endl;
    cout << "In-order: " << inOrderResult << endl;
    cout << "Post-order: " << postOrderResult << endl;
}

// Main program to test the implementation
int main() {
    string expression = "(((3*5)-10)+((8*3)-(6*2)))";
    convertExpression<string>(expression);  // Using std::string as the template type

    
    return 0;
}