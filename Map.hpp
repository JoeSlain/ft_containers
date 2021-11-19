#ifndef MAP_HPP
#define MAP_HPP

#define RED 1
#define BLACK 0

namespace ft {
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> >
		>
		class map {
		public:

		template< class Key, class T>
		class Node<class Key, class T>{
			public:
			Node(Key key, T value) : key(key), value(value), color(RED),\
			left(null), right(null), parent(null), isLeftChild(false) {};
			
			private:
			bool color;
			bool isLeftChild;
			Key key;
			T value;
			Node left;
			Node right;
			Node parent;
		};
		map( void ) : _root(nullptr), _size(0) {}
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
		int				_size;
	};
}
#endif