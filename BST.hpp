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
		
		void deleteTreeHelper(pointer node)
		{
			if (node == _null) return;
			deleteTreeHelper(node->_left);
			deleteTreeHelper(node->_right);
			if (node)
			{
				delete node;
				node = NULL;
			}
		}

		void deleteTree()
		{
			deleteTreeHelper(_root);
			delete _null;
		}

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
			node->_right = _null;
			node->_left = _null;
			if (!(_root))
			{
				_root = node;
				return true;
			}
		/*	allocator_type().allocate(1);
			allocator_type().construct(node, node_type(key));*/

			pointer current = NULL;
			pointer tmp_root = this->_root;
			
			while (tmp_root != _null)
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
		pointer minValueNode(pointer node)
		{
			pointer current = node;

			// Find the leftmost leaf
			while (current && current->_left != NULL)
				current = current->_left;

			return current;
		}


		/*
		*** @param toDelete Node to delete
		*** @param newNode Node to replace deleted node.
		*** @brief Connects toDelete's parent with newNode.
		*** If toDelete is root then newNode is the new _root
		*** 
		*/
		void deleteConnector(pointer toDelete, pointer newNode)
		{
			if (toDelete->_parent == NULL)
				_root = newNode;
			else if (toDelete == toDelete->_parent->_left)
				toDelete->_parent->_left = newNode;
			else
				toDelete->_parent->_right = newNode;

			newNode->_parent = toDelete->_parent;
		}

		bool deleteNode(const value_type val)
		{
			pointer toDelete = NULL;
			pointer current = _root;
			pointer	tmp = NULL;
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
					toDelete = current;
					break;
				}
			}
			if (!(toDelete))
			return false;
			if (toDelete->_left == _null) {
				tmp = toDelete->_right;
				deleteConnector(toDelete, toDelete->_right);
			}
			else if (toDelete->_right == _null) {
				tmp = toDelete->_left;
				deleteConnector(toDelete, toDelete->_left);
			}
			else {
				current = minValueNode(toDelete->_right);
				tmp = current->_right;
				if (current->_parent == toDelete) {
					tmp->_parent = current;
				}
				else {
					deleteConnector(current, current->_right);
					current->_right = toDelete->_right;
					current->_right->_parent = current;
					}

					deleteConnector(toDelete, current);
					current->_left = toDelete->_left;
					current->_left->_parent = current;
				}
				delete toDelete;
				return true;
		}
		
		private:
		pointer _root;
		pointer _null;
		value_compare _comp;

	};//end BST

}//end namespace
#endif