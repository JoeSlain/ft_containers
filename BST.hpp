#ifndef BST_HPP
#define BST_HPP

#include <memory>

namespace ft{


	template<class T>
	class Node {
		typedef T value_type;
		public:
		Node(void) : _value(), _left(NULL), _right(NULL), _parent(NULL) {}
		Node(value_type const value) : _value(value), _left(NULL), _right(NULL), _parent(NULL) {}
		Node(Node const &n) {
			*this = n;
		}
		
		Node operator=(Node const &src)
		{
			if (this == &src)
				return *this;
			_parent = src._parent;
			_left = src._left ;
			_right = src._right ;
			_value = src._value ;
			return *this;
		}
		~Node(){}
		T _value;
		Node *_left;
		Node *_right;
		Node *_parent;
	};
	template < class T,
		class Compare,
		class Node = ft::Node<T>,
		class AllocNode = std::allocator<Node> >
	class BST{
		public:
		typedef				T										value_type;
		typedef				Node									node_type;

		typedef				Compare									value_compare;

		typedef				AllocNode								allocator_type;
		typedef	typename	allocator_type::reference				reference;
		typedef	typename	allocator_type::const_reference			const_reference;
		typedef	typename	allocator_type::pointer					pointer;
		typedef	typename	allocator_type::const_pointer			const_pointer;

		typedef	typename	allocator_type::difference_type			difference_type;;
		BST(value_compare const & compare = value_compare()) : _root(NULL), _comp(compare) {
			_null = new node_type;
		}

		pointer get_root() const
		{ return _root; }

		pointer search(const value_type val, pointer root)
		{
			if (!(root))
				return NULL;
			if (val == root->_value)
				return root;
			if (val < root->_value) 
				return search(val, root->_left);
			if (val > root->_value) 
				return search(val, root->_right);
			return NULL;
		}

		bool insert(value_type const & key)
		{
			pointer node = new node_type(key);
			if (!(_root))
			{
				_root = node;
				return true;
			}
		/*	allocator_type().allocate(1);
			allocator_type().construct(node, node_type(key));*/
			node->_right = _null;
			node->_left = _null;

			pointer current = NULL;
			pointer tmp_root = this->_root;
			
			while (tmp_root != NULL)
			{
				current = tmp_root;
				if (_comp(node->_value, tmp_root->_value))
					tmp_root = tmp_root->_left;
				else if (_comp(tmp_root->_value, node->_value))
					tmp_root = tmp_root->_right;
				else
				{
					delete node;
					return false;
				}
				if (current == NULL)
					_root = node;
				else if (_comp(node->_value, current->_value))
					current->_left = node;
				else
					current->_right = node;
			}
			node->_parent = current;
			if (current == NULL)
				_root = node;
			else if (_comp(node->_value, current->_value))
				current->_left = node;
			else
				current->_right = node;
			return true;
		}

		// Inorder Traversal
		void inorder(pointer root) {
			if (root != _null) {
				// Traverse left
				inorder(root->_left);

				// Traverse root
				std::cout << root->_value << " -> ";

				// Traverse right
				inorder(root->_right);
			}
		}

		// Find the inorder successor
		pointer minValueNode(pointer node) {
			pointer current = node;

			// Find the leftmost leaf
			while (current && current->_left != NULL)
				current = current->_left;

			return current;
		}

		// Deleting a node
/*		pointer deleteNode(pointer root, value_type key) {
			// Return if the tree is empty
			if (root == NULL) return root;

			// Find the node to be deleted
			if (key < root->_value)
				root->_left = deleteNode(root->_left, key);
			else if (key > root->_value)
				root->_right = deleteNode(root->_right, key);
			else {
				// If the node is with only one child or no child
				if (root->_left == _null) {
					pointer temp = root->_right;
					free(root);
					_root = temp;
					return temp;
				}
				else if (root->_right == _null) {
					pointer temp = root->_left;
					free(root);
					_root = temp;
					return temp;
				}

				// If the node has two children
				pointer temp = minValueNode(root->_right);

				// Place the inorder successor in position of the node to be deleted
				root->_value = temp->_value;

				// Delete the inorder successor
				root->_right = deleteNode(root->_right, temp->_value);
			}
			return root;
		}
*/

bool deleteNode(const value_type val)
{
	pointer target = NULL;
	pointer current = _root;
	if (!(_root))
		return false;
	while(current != _null)
	{
		if (_comp(current->_value, val))
			current = current->_right;
		else if (_comp(val, current->_value))
			current = current->_left;
		else
		{
			target = current;
			break;
		}
	}
	if (!(target))
		return false;
	pointer parent = target->_parent;
	if (target->_left == _null)
	{
		target->_right->_parent = parent;

	}
	else if (target->_right == _null)
	{
		target->left->_parent = parent;

	}
	else
	{
		pointer newNode = minValueNode(target->_right);
		newNode->_parent = target->parent;
		newNode->_right 
		
	}
	if (target == parent->_right)
		parent->right = target->_right;
	else
		parent->_left = target->_right;
	delete target;
}
		
		private:
		pointer _root;
		pointer _null;
		value_compare _comp;

	};

}//end namespace
#endif