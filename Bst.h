#ifndef _BST_H
#define _BST_H

#include <iostream>

/**
 * 	@class 		Bst
 *
 * 	@brief 		Definition and Implementation of the Bst Template.
 *
 * 	File Name: Bst.h
 *
 *	@author 	Geoffrey Lawson (33176674)
 *
 *	@version 	0.2		4/5/2021	Adding function pointers to template methods, removed ostream from traversal methods.
 *	@version 	0.1		26/4/2021	Initial creation of the Bst template.
 *
 *	@date 		4/5/2021
 *
 */
template < class dataType >
class Bst {
public:
	/**
	 * @brief	Default constructor. Sets root, left and right to nullptr, and leaves info blank.
	 */
	Bst();
	/**
	 * @brief	Inserts the given dataType object into the tree.
	 *
	 * @param	newData		Reference to a dataType object to be inserted into the tree.
	 *
	 * @post	The given object has been inserted into the tree, or discarded if it already exists.
	 */
	void Insert( const dataType & newData );
	/**
	 * @brief	Deletes the contents of the entire tree.
	 *
	 * @post	All memory reserved for the tree's dataType objects is freed up in the system.
	 *
	 * @return	Boolean value denoting whether the deletion was successful or not. True if the tree was deleted, False if an error occured or the tree was already empty.
	 */
	bool DeleteTree();
	/**
	 * @brief	Searches the entire tree for the given dataType object.
	 *
	 * @param	searchData	Constant reference to the dataType object to search through the tree for.
	 *
	 * @return	Boolean value denoting if the given dataType object is present in the tree. True if it is, False if it isn't.
	 */
	bool Search( const dataType & searchData ) const;
	/**
	 * @brief	Traverses the entire tree using the 'In Order' formula.
	 *
	 * @param	visit	Function pointer determining what will happen to the elements of the tree during the traversal.
	 *
	 * @post	The entire tree is traversed using the 'In Order' formula, with the given parameter function applied to each item.
	 */
	void InOrder( void ( * visit ) ( dataType & ) );
	/**
	 * @brief	Traverses the entire tree using the 'Pre Order' formula.
	 *
	 * @param	visit	Function pointer determining what will happen to the elements of the tree during the traversal.
	 *
	 * @post	The entire tree is traversed using the 'Pre Order' formula, with the given parameter function applied to each item.
	 */
	void PreOrder( void ( * visit ) ( dataType & ) );
	/**
	 * @brief	Traverses the entire tree using the 'Post Order' formula.
	 *
	 * @param	visit	Function pointer determining what will happen to the elements of the tree during the traversal.
	 *
	 * @post	The entire tree is traversed using the 'Post Order' formula, with the given parameter function applied to each item.
	 */
	void PostOrder( void ( * visit ) ( dataType & ) );
	/**
	 *	@brief	Counts the number of Nodes in the entire Tree.
	 *
	 *	@return	Unsigned value representing the number of Nodes in the entire Tree.
	 */
	unsigned TreeNodeCount() const;

	unsigned TreeHeight() const;
	/**
	 *	@brief	Returns a pointer to the requested dataType object.
	 *
	 *	@param
	 *
	 *	@return
	 ///REPLACE WITH A COLLECT CLASS WITH THREE FUNCTIONS
	 */
	//dataType & Get( const dataType & requestedData );
protected:
	///	Pointer to the root Node of the tree. Initialised to nullptr when the tree is first created.
	Bst< dataType >* root;
private:
	/**
	 *	@brief	Recursive method for inserting a dataType object into the tree in the correct position according to its value.
	 *
	 *	@param	Node	Pointer to the current Node that will be compared to the given data.
	 *	@param	newData	Constant reference to the new dataType object to be inserted into the tree.
	 *
	 *	@post	If the given Node is a nullptr then it is instantiated with the value from the given newData object, otherwise it is
	 * 			compared to the value of the newData object and either terminated (if they're equal), inserted to the left (if the
	 *			newData value is lower) or inserted to the right (if the newDate value is larger).
	 */
	void Insert( Bst< dataType >* Node, Bst< dataType > * newNode );
	/**
	 * @brief	Deletes the contents of the tree from the given Node downwards, recursively calling itself for the given Node's children.
	 *
	 * @param	Node	Pointer reference to a Bst< dataType > Node in the tree to delete, along with all of the children that it has.
	 *
	 * @post	All memory reserved for the tree's dataType objects from the highest given Node is freed up in the system.
	 */
	void DeleteNode( Bst< dataType >* & Node );
	/**
	 * @brief	Traverses the subtree from the given Node downards using the 'In Order' formula.
	 * 			The Nodes to the left of the given Node are displayed first, then the given Node, then all the Nodes to the right.
	 *
	 * @param	Node	Pointer to a Bst< dataType > Node in the tree to apply the given function to, along with all of its children.
	 * @param	visit	Function pointer determining what will happen to the elements of the tree during the traversal.
	 *
	 * @post	The tree's dataType objects from the highest given Node are traversed using the 'In Order' formula, with the given parameter
	 *			function applied to each Node.
	 */
	void InOrder( Bst< dataType >* Node, void ( * visit ) ( dataType & ) );
	/**
	 * @brief	Traverses the subtree from the given Node downards using the 'Pre Order' formula.
	 * 			This Node has its details displayed first, then all Nodes to the left, then all the Nodes to the right.
	 *
	 * @param	Node	Constant pointer to a Bst< dataType > Node in the tree to display, along with all of the children that it has.
	 * @param	visit	Function pointer determining what will happen to the elements of the tree during the traversal.
	 *
	 * @post	The tree's dataType objects from the highest given Node are traversed using the 'Pre Order' formula, with the given parameter
	 *			function applied to each Node.
	 */
	void PreOrder( Bst< dataType >* Node, void ( * visit ) ( dataType & ) );
	/**
	 * @brief	Traverses the subtree from the given Node downards using the 'Post Order' formula.
	 * 			The Nodes to the left of the given Node are displayed first, then the Nodes to the right, then the details for this Node.
	 *
	 * @param	Node	Constant pointer to a Bst< dataType > Node in the tree to traverse, along with all of the children that it has.
	 * @param	visit	Function pointer determining what will happen to the elements of the tree during the traversal.
	 *
	 * @post	The tree's dataType objects from the highest given Node are traversed using the 'Post Order' formula, with the given parameter
	 *			function applied to each Node.
	 */
	void PostOrder( Bst< dataType >* Node, void ( * visit ) ( dataType & ) );
	/**
	 *	@brief	Counts the number of nodes in the given subtree.
	 *
	 *	@param	Node	Constant pointer to a Bst< dataType > Node that will have its Node children counted.
	 *
	 *	@return	Unsigned value representing the number of Nodes in the given subtree, along with the parent Node.
	 */
	unsigned TreeNodeCount( Bst< dataType >* Node ) const ;

	unsigned TreeHeight( Bst< dataType >* Node ) const ;
	/// Data object to be stored in this Node.
	dataType info;
	/// Pointer to this Node's child on the left.
	Bst< dataType >* left;
	/// Pointer to this Node's child on the right.
	Bst< dataType >* right;

};

#endif  //_BST_H

//	Default Constructor.
template < class dataType >
Bst< dataType >::Bst() : root(nullptr), info(), left(nullptr), right(nullptr) {
}

//	Insertion to tree.
template < class dataType >
void Bst< dataType >::Insert( const dataType & newData ) {
	Bst< dataType >* newNode;
	newNode = new Bst< dataType >;

	newNode->info = newData;
	newNode->left = nullptr;
	newNode->right = nullptr;

	if( root == nullptr ) {
		root = newNode;
	}else{
		Insert( root, newNode );
	}
}

//	Public method for deletion of the entire tree.
template < class dataType >
bool Bst< dataType >::DeleteTree() {
	bool isDeleted;
	if( root == nullptr ) {
		isDeleted = false;
	}else{
		DeleteNode( root );
		isDeleted = true;
	}

	return( isDeleted );
}

//	Searching the tree for the given object.
template < class dataType >
bool Bst< dataType >::Search( const dataType & searchData ) const {
	bool isFound = false;
	Bst< dataType >* current;

	if( root != nullptr ) {
		current = root;
		while( current != nullptr && !isFound ) {
			if( current->info == searchData ) {
				isFound = true;
			}else if( current->info > searchData ) {
				current = current->left;
			}else{
				current = current->right;
			}
		}
	}

	return( isFound );
}

//	Public method for traversing the entire tree using the 'In Order' formula.
template < class dataType >
void Bst< dataType >::InOrder( void ( * visit ) ( dataType & item ) ) {
	InOrder( root, *visit );
}

//	Public method for traversing the entire tree using the 'Pre Order' formula.
template < class dataType >
void Bst< dataType >::PreOrder( void ( * visit ) ( dataType & item ) ) {
	PreOrder( root, *visit );
}

//	Public method for traversing the entire tree using the 'Post Order' formula.
template < class dataType >
void Bst< dataType >::PostOrder( void ( * visit ) ( dataType & item ) ) {
	PostOrder( root, *visit );
}

//	Public method for getting the Node count for the entire Tree.
template < class dataType >
unsigned Bst< dataType >::TreeNodeCount() const {
	return( TreeNodeCount( root ) );
}

template < class dataType >
unsigned Bst< dataType >::TreeHeight( ) const {
	return( TreeHeight( root ) );
}


//	Public method for getting a pointer to a specific node in the tree.
/*template < class dataType >
dataType & Bst< dataType >::Get( const dataType & requestedData ) {
	bool isFound = false;
	Bst< dataType >* current;
	dataType * requestedObject;// = new dataType;
	//dataType * requestPtr;

	if( root != nullptr ) {
		current = root;
		while( current != nullptr && !isFound ) {
			//std::cout << "comparing " << current->info << " & " << requestedData << std::endl;
			if( current->info == requestedData ) {
				requestedObject = & current->info;
				//std::cout << "matched, requestedObject: " << requestedObject << std::endl;
				isFound = true;
			}else if( current->info > requestedData ) {
				current = current->left;
			}else{
				current = current->right;
			}
		}
	}

	return( *requestedObject );
}
*/

//	Recursive formula for inserting a Node into the tree in the correct spot
template < class dataType >
void Bst< dataType >::Insert( Bst< dataType >* Node, Bst< dataType > * newNode ) {
	if( Node != nullptr ){
		if( Node->info == newNode->info ) {
			DeleteNode( newNode );	//already exists, delete the node that was created
		}else if( Node->info > newNode->info ) {
			if( Node->left == nullptr ) {
				Node->left = newNode;
			}else{
				Insert( Node->left, newNode );
			}
		}else{
			if( Node->right == nullptr ) {
				Node->right = newNode;
			}else{
				Insert( Node->right, newNode );
			}
		}
	}
}


//	Recursive formula for deleting all children for a given Node.
template < class dataType >
void Bst< dataType >::DeleteNode( Bst< dataType >* & Node ) {
	if( Node->left != nullptr ) {
		DeleteNode( Node->left );
	}
	if( Node->right != nullptr ) {
		DeleteNode( Node->right );
	}
	delete Node;
	Node = nullptr;
}

//	Recursive method for traversing all children of a given Node using the 'In Order' formula
template < class dataType >
void Bst< dataType >::InOrder( Bst< dataType >* Node, void ( * visit ) ( dataType & item ) ) {
	if( Node != nullptr ) {
		InOrder( Node->left, *visit );
		(* visit ) ( Node->info );
		InOrder( Node->right, *visit );
	}
}

//	Recursive method for traversing all children for a given Node using the 'Pre Order' formula
template < class dataType >
void Bst< dataType >::PreOrder( Bst< dataType >* Node, void ( * visit ) ( dataType & item ) ) {
	if( Node != nullptr ) {
		(* visit ) ( Node->info );
		PreOrder( Node->left, *visit );
		PreOrder( Node->right, *visit );
	}
}

//	Recursive method for traversing all children for a given Node using the 'Post Order' formula
template < class dataType >
void Bst< dataType >::PostOrder( Bst< dataType >* Node, void ( * visit ) ( dataType & item ) ) {
	if( Node != nullptr ) {
		PostOrder( Node->left, *visit );
		PostOrder( Node->right, *visit );
		(* visit ) ( Node->info );
	}
}

//	Recursive method for getting the total number of Nodes in the given Node's subtree, plus the given Node itself. Uses InOrder traversal.
template< class dataType >
unsigned Bst< dataType >::TreeNodeCount( Bst< dataType >* Node ) const {
	unsigned nodeCount = 0;
	if( Node != nullptr ) {
		nodeCount += TreeNodeCount( Node->left );
		nodeCount ++;
		nodeCount += TreeNodeCount( Node->right );
	}
	return( nodeCount );
}

template< class dataType >
unsigned Bst< dataType >::TreeHeight( Bst< dataType >* Node ) const {
	unsigned leftTreeHeight, rightTreeHeight, treeHeight = 0;

	if( Node != nullptr ) {
		leftTreeHeight = TreeHeight( Node->left );
		rightTreeHeight = TreeHeight( Node->right );
		if( leftTreeHeight > rightTreeHeight ) {
			treeHeight += leftTreeHeight;
		}else{
			treeHeight += rightTreeHeight;
		}
		treeHeight++;
	}

	return( treeHeight );
}
