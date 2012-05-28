

template <typename T>
void BinaryTree<T>::print() const
{
	// Base case
	if (root == NULL)
	{
		cout << "(empty)" << endl;
		return;
	}

	// Make a character matrix for outputting the tree onto
	int rootData  = getPrintData(root);
	int width     = (4 << rootData) - 3;
	int height_   = 2 * rootData + 1;

	// Initialize this matrix to be filled with spaces
	vector<string> output(height_);
	for (size_t i = 0; i < output.size(); i++)
		output[i] = string(width+4, ' '); // extra room for long things

	// Recursively print each node
	print(root, output, 0, 0, width);

	// Output the matrix
	for (int row = 0; row < height_; row++)
		cout << output[row] << endl;
}

// Gathers data about each node to determine the size of the output matrix
template <typename T>
int BinaryTree<T>::getPrintData(const Node * node) const
{
    if (node == NULL) return -1;
    return 1 + max( getPrintData(node->left),
	                getPrintData(node->right) );
}

// Recursively prints tree to output matrix
template <typename T>
void BinaryTree<T>::print(const Node * node, vector<string> & output,
                          int left, int top, int width) const
{
	// Convert data to string
	stringstream nodeOut;
	nodeOut << node->elem;
	string nodeStr = nodeOut.str();
	
	// Output data
	int shift = 1 - (nodeStr.length()-1)/2;
	for (size_t i = 0; i < nodeStr.length() && left + width/2 + i < output[top].length(); i++)
		output[top][left + width/2 + shift + i] = nodeStr[i];
	
	// Calculate / \ offset = 2 ^ height
	int branchOffset = (width+3) >> 3; //(1 << (node->printData - 1));
	
	// Print left child
    int center = left + width/2;
    int leftcenter = left + (width/2 - 1)/2;
    int rightcenter = left + width/2 + 2 + (width/2 - 1)/2;
	if (node->left  != NULL)
	{
        int branch_pos = center - branchOffset + 1;
        // draw left upper branch
        for (int pos = center + shift - 2; pos > branch_pos; pos--)
            output[top][pos] = '_';
        // draw left '/'
		output[top+1][branch_pos] = '/';
        // draw left lower branch
        for (int pos = branch_pos-1; pos > leftcenter + 2; pos--)
            output[top+1][pos] = '_';
        // draw left subtree
		print(node->left, output, left, top+2, width/2 - 1);
	}
	// Print right child
	if (node->right != NULL)
	{
        int branch_pos = center + branchOffset + 1;
        // draw right upper branch
        for (int pos = center + shift + nodeStr.length() + 1; pos < branch_pos; pos++)
            output[top][pos] = '_';
        // draw right '\'
        output[top+1][branch_pos] = '\\';
        // draw right lower branch
        for (int pos = branch_pos+1; pos < rightcenter; pos++)
            output[top+1][pos] = '_';
        // draw right subtree
		print(node->right, output, left + width/2 + 2, top+2, width/2 - 1);
	}
}



// Inserts an element into a random/sorted position in the tree
template <typename T>
void BinaryTree<T>::insert(const T & elem, bool sorted /* = false */)
{
	insert(root, elem, sorted);
}

// Recursive helper function for insert()
template <typename T>
void BinaryTree<T>::insert(Node * & node, const T & elem, bool sorted)
{
	// If we're at a NULL pointer, we can put our element here
	if (node == NULL)
		node = new Node(elem);

	// If sorted, go left/right based on ordering
	// If random, go left or right based on pseudorandom even/odd
	else if (sorted ? elem < node->elem : util::urand() % 2 == 0)
		insert(node->left, elem, sorted);

	else // right side / larger
		insert(node->right, elem, sorted);
}



// copy() big three helper function provided for you
template <typename T>
typename BinaryTree<T>::Node * BinaryTree<T>::copy(const Node * subRoot)
{
	if (subRoot == NULL) return NULL;

	// Copy this node and it's children	
	Node * newNode = new Node(subRoot->elem);
	newNode->left  = copy(subRoot->left );
	newNode->right = copy(subRoot->right);
	return newNode;
}


// clear() big three helper function provided for you
template <typename T>
void BinaryTree<T>::clear(BinaryTree::Node * subRoot)
{
	if (subRoot == NULL) return;
	
	clear(subRoot->left );
	clear(subRoot->right);
	delete subRoot;
}
