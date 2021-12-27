#ifndef MAP_HPP
#define MAP_HPP
#include "BST.hpp"
#include "RandIterator.hpp"
#include "Reverse_iterator.hpp"
#include "utils.hpp"
#include "Iterator_bst.hpp"

#include <functional>


namespace ft {
	template <class Key, class T, class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T> > >
	class map {
	public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef ft::pair<const Key, T> value_type;
	typedef Compare key_compare;
	typedef Allocator allocator_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef ft::bstIte<value_type, ft::Node<value_type>> iterator;
	typedef ft::bstIte<const value_type, ft::Node<value_type>> const_iterator;
	typedef typename allocator_type::size_type size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	
    class value_compare {
      friend class map;
    protected:
      Compare comp;
      value_compare(Compare c) : comp(c) {}
    public:
      bool operator()(const value_type& x, const value_type& y) const {
        return comp(x.first, y.first);
      }
    };
	

	/*----------------
		CONSTRUCTORS
	----------------*/
	map() : map(Compare()) { }
    explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : _bst(value_compare(comp)), _alloc(alloc)
	{}
	/*template< class InputIt >
	map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
	{

	}*/

	map( const map& other )
	{
		*this = other;
	}

	allocator_type get_allocator() const { return _alloc; }
	map& operator=( const map& other )
	{
		if (*this == other)
			return *this;
		this->~map();
		_bst = ft::BST<value_type, value_compare>(value_compare(key_compare()));
		
	}


	private:
		ft::BST<value_type, value_compare> _bst;
		allocator_type _alloc;


	};
}
#endif