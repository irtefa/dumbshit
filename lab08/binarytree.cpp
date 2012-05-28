
// height()
template <typename T>
int BinaryTree<T>::height() const
{
	// Call recursive helper function on root
	return height(root);
}

// height() recursive helper function
template <typename T>
int BinaryTree<T>::height(const Node * subRoot) const
{
	// Base case
	if (subRoot == NULL) return -1;
	
	// Recursive definition
	return 1 + max(height(subRoot->left), height(subRoot->right));
}



// printLeftToRight()
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
	// Call recursive helper function on the root
	printLeftToRight(root);

	// Finish the line
	cout << endl;
}

// printLeftToRight() recursive helper function
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node * subRoot) const
{
	// Base case - null node
	if (subRoot == NULL)
		return;

	// Print left subtree
	printLeftToRight(subRoot->left);

	// Print this node
	cout << subRoot->elem << ' ';

	// Print right subtree
	printLeftToRight(subRoot->right);
}



// mirror()
template <typename T>
void BinaryTree<T>::mirror()
{
	// mirror_helper(*subroot)
	mirror_helper(root);
}
// mirror_helper
template <typename T>
void BinaryTree<T>::mirror_helper(Node* subRoot)
{
 if(subRoot->right==NULL && subRoot->left==NULL) return;
 	if(subRoot->left!=NULL)
		mirror_helper(subRoot->left);
 	if(subRoot->right!=NULL)
		mirror_helper(subRoot->right);
 	Node * temp = subRoot->left;
 	subRoot->left = subRoot->right;
 	subRoot->right = temp;
}

// isOrdered()
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
	bool retval = true;
	queue<T> rack;
	isOrderedHelper(root,rack);
	while(rack.size() > 1)
	{
	 T temp = rack.front();
	 rack.pop();
	 //if(rack.front()==NULL) return true;
	 if( temp >  rack.front())
		return false;		
	}
	return retval;
}



// printPaths()
template <typename T>
void BinaryTree<T>::printPaths() const
{
	vector<T> v;
	printPaths(root,v);
}
template <typename T>
void BinaryTree<T>::printPaths(const Node * a, vector<T> &v) const
{
 v.push_back(a->elem);
 if(a->left==NULL && a->right==NULL)
 {
    typename vector<T>::iterator it;
	cout << "Path:";
	for( it = v.begin(); it < v.end(); it++ )
	{
		
		cout <<" "<<*it;
	}
	cout << endl;
	return;
 }
 if(a->left!=NULL)
 {
	printPaths(a->left,v);
	v.pop_back();
 }
 if(a->right!=NULL)
 {
	printPaths(a->right,v);
    v.pop_back();
 }

  
}


template <typename T>
int BinaryTree<T>::sumDistances() const
{
	int d = 0;
	return sumDistances(root,d);
}
template <typename T>
int BinaryTree<T>::sumDistances(const Node * a,int d) const
{
 int left = 0;
 int right = 0;
 if(a->left==NULL && a->right==NULL)
 {
	return 0;
 }
 if(a->left!=NULL){
	// its d+1 as you count the path of the previous node as well
	left = 1 + sumDistances(a->left,d+1)+d;
 }
 if(a->right!=NULL)
	// ditto
	right = 1 + sumDistances(a->right,d+1) + d;
 

  return left+right; // returning the sum of the paths on both left and right nodes
}

// private helpers
template <typename T>
void  BinaryTree<T>::isOrderedHelper(const Node * subRoot,queue<T> &rack) const
{
	
	if(subRoot==NULL)
		return;
	isOrderedHelper(subRoot->left,rack);
	rack.push(subRoot->elem);
	isOrderedHelper(subRoot->right,rack);

}	
