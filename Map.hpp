#ifndef MAP_HPP
# define MAP_HPP
# include "RBT.hpp"
# include "utils.hpp"

namespace ft {
	template <typename Key, typename T, typename Compare = std::less<Key>,
	typename Allocator = std::allocator<ft::pair<Key const, T> > >
	class map {

		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef pair<Key const, T> value_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;

			class value_compare: public std::binary_function<value_type, value_type, bool> {
				private:
					friend class map;
				protected:
					key_compare comp;
					value_compare(key_compare c): comp(c) {
					}
				public:
					bool	operator()(value_type const &lhs, value_type const &rhs) const {
						return (comp(lhs.first, rhs.first));
					}
			};

		private:
			typedef rb_tree<value_type, allocator_type, value_compare> tree_type;

		public:
			typedef typename tree_type::iterator iterator;
			typedef typename tree_type::const_iterator const_iterator;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		private:
			allocator_type _alloc;
			key_compare _key_comp;
			value_compare _value_comp;
			tree_type _tree;

		public:
			explicit map(key_compare const &comp = key_compare(), allocator_type const alloc = allocator_type())
			: _alloc(alloc), _key_comp(comp), _value_comp(comp), _tree(_alloc, _value_comp) {
			}

			template <typename InputIterator>
			map(InputIterator first, InputIterator last,
			key_compare const &comp = key_compare(), allocator_type const alloc = allocator_type())
			: _alloc(alloc), _key_comp(comp), _value_comp(comp), _tree(_alloc, _value_comp) {
				this->insert(first, last);
			}

			map(map<key_type, value_type, key_compare, allocator_type> const &m)
			: _alloc(m.alloc), _key_comp(m.comp), _value_comp(m.comp), _tree(_alloc, _value_comp) {
				this->insert(m.begin(), m.end());
			}

			~map() {
			}

			map<key_type, value_type, key_compare, allocator_type>
			&operator=(map<key_type, value_type, key_compare, allocator_type> const &rhs) {
				if (this != &rhs) {
					this->_tree = rhs._tree;
					this->_alloc = rhs._alloc;
					this->_key_comp = rhs._key_comp;
					this->_value_comp = rhs._value_comp;
				}
				return (*this);
			}

// iterators

			iterator	begin(void) {
				return (this->_tree.begin());
			}

			const_iterator	begin(void) const {
				return (this->_tree.begin());
			}

			iterator	end(void) {
				return (this->_tree.end());
			}

			const_iterator	end() const {
				return (this->_tree.end());
			}

			reverse_iterator	rbegin(void) {
				return (this->_tree.rbegin());
			}

			const_reverse_iterator	rbegin(void) const {
				return (this->_tree.rbegin());
			}

			reverse_iterator	rend(void) {
				return (this->_tree.rend());
			}

			const_reverse_iterator	rend(void) const {
				return (this->_tree.rend());
			}

// capacity

			bool	empty(void) const {
				return (this->size() == 0);
			}

			size_type	size(void) const {
				return (this->_tree.size());
			}

			size_type	max_size(void) const {
				return (this->_tree.max_size());
			}

// element access

			mapped_type	&operator[](key_type const &key) {
				iterator it = this->find(key);
				if (it == this->end())
					it = this->insert(ft::make_pair(key, mapped_type())).first;
				return (it->second);
			}

// modifiers

			ft::pair<iterator, bool>	insert(value_type const &p) {
				return (this->_tree.insert(this->end(), p));
			}

			iterator	insert(iterator position, value_type const &p) {
				return (this->_tree.insert(position, p).first);
			}

			template <typename InputIterator>
			void	insert(InputIterator first, InputIterator last) {
				for (; first != last; ++first)
					this->_tree.insert(this->end(), *first);
			}

			void	erase(iterator position) {
				this->_tree.erase(position);
			}

			size_type	erase(key_type const &key) {
				size_type ret = this->count(key);
				this->_tree.erase(ft::make_pair(key, mapped_type()));
				return (ret);
			}

			void	erase(iterator first, iterator last) {
				iterator it;
				while (first != last) {
					it = first;
					++first;
					this->_tree.erase(it);
				}
			}

			void swap(map<Key, T, Compare, Allocator> &m) {
				this->_tree.swap(m._tree);
			}

			void	clear(void) {
				this->_tree.clear();
			}

// observers

			key_compare	key_comp(void) const {
				return (this->_key_comp);
			}

			value_compare	value_comp(void) const {
				return (this->_value_comp);
			}

// map operations

			iterator	find(key_type const &key) {
				return (this->_tree.find(ft::make_pair(key, mapped_type())));
			}

			const_iterator	find(key_type const &key) const {
				return (this->_tree.find(ft::make_pair(key, mapped_type())));
			}

			size_type	count(key_type const &key) const {
				return (this->find(key) != this->end());
			}

			iterator	lower_bound(key_type const &key) {
				return (this->_tree.lower_bound(ft::make_pair(key, mapped_type())));
			}

			const_iterator	lower_bound(key_type const &key) const {
				return (this->_tree.lower_bound(ft::make_pair(key, mapped_type())));
			}

			iterator	upper_bound(key_type const &key) {
				return (this->_tree.upper_bound(ft::make_pair(key, mapped_type())));
			}

			const_iterator	upper_bound(key_type const &key) const {
				return (this->_tree.upper_bound(ft::make_pair(key, mapped_type())));
			}

			pair<iterator, iterator>	equal_range(key_type const &key) {
				iterator it = upper_bound(key);
				iterator ite = lower_bound(key);
				return (ft::make_pair<iterator, iterator>(ite, it));
			}

			pair<const_iterator, const_iterator>	equal_range(key_type const &key) const {
				const_iterator it = upper_bound(key);
				const_iterator ite = lower_bound(key);
				return (ft::make_pair<const_iterator, const_iterator>(ite, it));
			}

			void	print(void) {
				this->_tree.print();
			}
	};//End map class

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool	operator==(map<Key, T, Compare, Allocator> const &lhs,
	map<Key, T, Compare, Allocator> const &rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool	operator<(map<Key, T, Compare, Allocator> const &lhs,
	map<Key, T, Compare, Allocator> const &rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool	operator!=(map<Key, T, Compare, Allocator> const &lhs,
	map<Key, T, Compare, Allocator> const &rhs) {
		return (!(lhs == rhs));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool	operator>(map<Key, T, Compare, Allocator> const &lhs,
	map<Key, T, Compare, Allocator> const &rhs) {
		return (rhs < lhs);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool	operator<=(map<Key, T, Compare, Allocator> const &lhs,
	map<Key, T, Compare, Allocator> const &rhs) {
		return (!(rhs < lhs));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool	operator>=(map<Key, T, Compare, Allocator> const &lhs,
	map<Key, T, Compare, Allocator> const &rhs) {
		return (!(lhs < rhs));
	}

// specialized algorithm

	template <typename Key, typename T, typename Compare, typename Allocator>
	void swap(map<Key, T, Compare, Allocator> &lhs, map<Key, T, Compare, Allocator> &rhs) {
		lhs.swap(rhs);
	}
}// End ft namespace

#endif