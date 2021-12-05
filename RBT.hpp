#ifndef RBT_HPP
#define RBT_HPP

#include <memory>

#define RED 1
#define BLACK 0

namespace ft{

	template<class T>
	class Node {
		typedef T value_type;
		public:
		Node(void) : value(NULL), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
		Node(value_type const value) : value(value), color(RED), left(NULL), right(NULL), parent(NULL) {}
		Node(Node const &n) {
			*this = n;
		}
		
		Node operator=(Node const &src)
		{
			if (this == &n)
				return *this;
			parent = n.parent;
			left = n.left ;
			right = n.right ;
			color = n.color ;
			value = n.value ;
			_TNULL = n._TNULL;
			_size = n._size;
			return *this;
		}
		~Node{};
		private:
		short color;
		T value;
		Node *left;
		Node *right;
		Node *parent;
	};

	template < class T,
		class Compare,
		class Node = ft::Node<T>,
		class AllocNode = std::allocator<Node> >
	class RBT{
		public:
		typedef				T										value_type;
		typedef				Node									node_type;

		typedef				Compare									value_compare;

		typedef				AllocNode								allocator_type;
		typedef	typename	allocator_type::reference				reference;
		typedef	typename	allocator_type::const_reference			const_reference;
		typedef	typename	allocator_type::pointer					pointer;
		typedef	typename	allocator_type::const_pointer			const_pointer;

		typedef	typename	allocator_type::difference_type			difference_type;
		typedef	typename	allocator_type::size_type				size_type;
		RBT(value_compare const & compare = value_compare()) : _size(0), _comp(compare){
			_TNULL = allocator_type().allocate(1);
			allocator_type().construct(_TNULL, node_type())
			_TNULL.color = BLACK;
			this->_root = _TNULL;
		};

		pointer get_root() const
		{ return _root };
		pointer get_TNULL() const
		{ return _TNULL };
		size_type const size() const
		{ return _size };


		void fixtree()

		bool insert(value_type key)
		{
			pointer node = allocator_type().allocate(1);
			allocator_type().construct(node, node_type(key));
			node.right = _TNULL;
			node.left = _TNULL;

			pointer y = nullptr;
			pointer x = this->root;
			
			while (x != _TNULL)
			{
				y = x;
				if (_comp(node.value, x->value))
					x = x->left;
				else if (_comp(x.value, node.value))
					x = x->right;
				else
				{
					allocator_type.destroy(node);
					allocator_type.deallocate(node, 1);
					return false;
				}
			}
			node.parent = y;
			if (y == nullptr)
			{
				this->_root = node;
				this->_root.color = BLACK;
				return true;
			}
			else if (_comp(node.value, y->value))
				y->left = node;
			else
				y->right = node;
			if (node.parent.parent == nullptr)
				return true;
			fixinsert(node);
			return true;
		}

		// pointer insert(pointer root, value_type value)
		// {
		// 	if (!root)
		// 		return *(new node_type(value));
		
		// 	if (value > root->data)
		// 		root->right = insert(root->right, value);
		// 	else
		// 		root->left = insert(root->left, value);

		// 	return root;
		// }
		pointer searchTreeHelper(pointer root, valu_type const & val)
		{
			// Base Cases: root is null or val is present at root
			if (root == NULL || root->val == val)
			return root;
			
			// Key is greater than root's val
			if (root->val < val)
			return search(root->right, val);
		
			// Key is smaller than root's val
			return search(root->left, val);
		}
		
		private:
		
		void leftRotate(pointer node)
		{
			pointer tmp = node->right;

			node->right = tmp->left;
			if (tmp->left != _TNULL)
				y->left->parent = node;
			tmp->parent = node->parent;
			if (tmp->parent == nullptr)
				_root = tmp;
			else if (node == node->parent->left)
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
			node->parent = tmp;
			tmp->left = node;
		}

		void rightRotate(pointer node)
		{
			pointer tmp = node->left;

			node->left = tmp->right;
			if (tmp->right != _TNULL)
				y->right->parent = node;
			tmp->parent = node->parent;
			if (tmp->parent == nullptr)
				_root = tmp;
			else if (node == node->parent->right)
				node->parent->right = tmp;
			else
				node->parent->left = tmp;
			node->parent = tmp;
			tmp->right = node;
		}

		void fixInsert(pointer node)
		{
			pointer u;
			while (node.parent.color == RED)
			{
				if (node.parent == node.parent.parent.right)
				{
					u = node.parent.parent.left; //uncle
					if (u.color == RED)
					{ // case 3.1;
						u.color = BLACK;
						node.parent.color = BLACK;
						node.parent.parent.color = RED;
						node = node.parent.parent;
					}
					else if (node == node.parent.left)// case 3.3.1 and 3.3.2
					{
						node = node.parent;
						leftRotate(node);
					}
						node.parent.color = BLACK
						node.parent.parent.color = RED
						RIGHT-ROTATE(T, node.parent.parent)
				}
				else
			}
		}

		pointer *_root;
		pointer *_TNULL;
		value_compare _comp;
		size_type		_size;

	};
	/*template< class Key, class T>
	void add(Key key, T value) {
			Node<Key, T> node = new Node<Key, T>(key, value);
			if (!(_root))
			{
				this->_root = node;
				node.color = BLACK;
				this->_size++;
				return ;
			}
			add(this->_root, node)
			_size++;
		}

		private:
		void add(Node<Key, T> parent, Node<Key, T> newNode)
		{

		}
		Node<Key, T> 	_root;
		int				_size;*/

}//end namespace
#endif