#ifndef MAP_HPP
#define MAP_HPP
#include "RBT.hpp"
#include "RandIterator.hpp"
#include "Reverse_iterator.hpp"

#include <functional>


namespace ft {
	template <class Key, class T, class Compare = std::less<Key>,
	class Allocator = allocator<pair<const Key, T> > >
	class map {
	public:
	// types:
	typedef Key key_type;
	typedef T mapped_type;
	typedef pair<const Key, T> value_type;
	typedef Compare key_compare;
	typedef Allocator allocator_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef  iterator; // See 23.1
	typedef const_iterator; // See 23.1
	typedef size_type; // See 23.1
	typedef difference_type;// See 23.1
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		
}
#endif