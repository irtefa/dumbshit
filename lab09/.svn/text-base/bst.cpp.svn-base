/*
   Binary Search Tree (Lab 09)
   Created by Chase Geigle for CS225, Spring 2011
*/

// include the given functions
#include "bst_given.cpp"

/*
   Dictionary ADT functions and helpers
*/

// insert() - public interface
template <class K, class V>
void BST<K,V>::insert( K const & key, V const & value ) {
    insert(root, key, value);
}

// insert() - private helper
template <class K, class V>
void BST<K,V>::insert( Node * & croot, K const & key, V const & value ) {
	
	if(croot==NULL)
	{
	  	
		croot = new Node(key,value);
	}
	else if(key < croot->key)
	{
		insert(croot->left,key,value);
	}
	else
	{
		insert(croot->right,key,value);
	}
	
}

// find() - public interface
template <class K, class V>
V BST<K,V>::find( K const & key ) const {
    return find(root,key);
}

// find() - private helper
template <class K, class V>
V BST<K,V>::find( Node const * croot, K const & key ) const {
    if(croot==NULL) return V();
	if(croot->key == key) return (croot->value);
	//if(croot==NULL) return NULL;
	else{
		 if(key < croot->key)
			return find(croot->left,key);
		 else
			return find(croot->right,key);
	}
}

// remove() - public interface
template <class K, class V>
void BST<K,V>::remove( K const & key ) {
    remove( root, key );
}

// remove() - private helper
template <class K, class V>
void BST<K,V>::remove( Node * & croot, K const & key ) {
    if (croot == NULL)
		return;
	else if(croot->key==key)
		remove(croot);
	else if(key < croot->key)
		remove(croot->left,key);
	else
		remove(croot->right,key);
}

/*
   Additional functions and helpers
*/
template <class K, class V>
void BST<K,V>::remove(Node * & croot)
{
	if((croot->left == NULL) && (croot->right == NULL))
	{
		//noChildRemove
		delete croot;
		croot = NULL;
	}
	else if ((croot->left != NULL) && (croot->right != NULL))
	{
		//twoChildRemove
		Node * &iop = IOP(croot);
		croot->key = iop->key;
		remove(iop);	
	}	
	else{
		//oneChildRemove
		Node * temp = croot;
		if(croot->left == NULL)
			croot = croot->right;
		else
			croot = croot->left;
		delete temp;
	}
}

template <class K, class V>
typename BST<K,V>::Node * & BST<K,V>::IOP(Node * & croot)
{
	return rightMostChild(croot->left);
}
template <class K, class V>
typename BST<K,V>::Node * & BST<K,V>::rightMostChild(Node * & croot)
{
	if(croot->right==NULL) return croot;
	else
		return rightMostChild(croot->right);
}
// keySort()
template <class K, class V>
vector<V> BST<K,V>::keySort() const {
     vector<V> vec; // your code here, helpers are allowed
	 keySort(root,vec);
	 return vec;
}

template <class K,class V>
void BST<K,V>::keySort(Node * const & croot,vector<V> & vec) const
{
 if(croot == NULL) return;

  keySort(croot->left,vec);
  // push it in
  vec.push_back(croot->value);
  keySort(croot->right,vec);
}
// levelOrder()
template <class K, class V>
vector<V> BST<K,V>::levelOrder() const {
    vector<V> vec; // the thing that levelOrder returns
	queue<V>    q; // the queue we use to keep track of level order
	
	q.push(root->value);
	levelOrder(root, vec, q);
	return vec;
}

template <class K, class V>
void  BST<K,V>::levelOrder(Node * const & croot,vector<V> & vec,queue<V> & q) const
{
	if(!q.empty())
	{
		vec.push_back(q.front());
		q.pop();
	}
	if(croot==NULL)
		return;
	if(croot->left!=NULL)
	{
		q.push(croot->left->value);
	}
	if(croot->right!=NULL)
	{
		q.push(croot->right->value);
	}
	if(croot->left != NULL)
		levelOrder(croot->left, vec, q);
	if(croot->right != NULL)
		levelOrder(croot->right, vec, q);
	return;	
}
