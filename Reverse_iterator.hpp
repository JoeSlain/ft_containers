#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "utils.hpp"
namespace ft
{
template <class Iterator>
class reverse_iterator {
	protected:
		typedef Iterator	super;
		Iterator _base;
	public:
		typedef Iterator							iterator_type;
		typedef typename super::difference_type		difference_type;
		typedef typename super::reference			reference;
		typedef typename super::pointer				pointer;

		reverse_iterator(void);
		explicit reverse_iterator(Iterator x);
		template <class U> reverse_iterator(const reverse_iterator<U> &u);
		template <class U> reverse_iterator &operator=(const reverse_iterator<U> &u);
		Iterator base(void) const { return this->_base; };

		reference			operator*(void) const { return (--super(this->_base)).operator*(); };
		pointer				operator->(void) const { return &this->operator*(); };

		reverse_iterator	&operator++(void) { this->_base.operator--(); return *this; };
		reverse_iterator	operator++(int) { return reverse_iterator(this->_base.operator--(0)); };
		reverse_iterator	&operator--(void) { this->_base.operator++(); return *this; };
		reverse_iterator	operator--(int) { return reverse_iterator(this->_base.operator++(0)); };

		template <class U>
		difference_type		operator-(const reverse_iterator<U> &u) { return u.base().operator-(this->_base); };
		reverse_iterator	operator+ (difference_type n) const { return reverse_iterator(this->_base.operator-(n)); };
		reverse_iterator	&operator+=(difference_type n) { this->_base.operator-=(n); return *this; };
		reverse_iterator	operator- (difference_type n) const { return reverse_iterator(this->_base.operator+(n)); };
		reverse_iterator	&operator-=(difference_type n) { this->_base.operator+=(n); return *this; };
		reference			operator[](difference_type n) const { return *this->operator+(n); };

		friend reverse_iterator	operator+(difference_type n, const reverse_iterator &rhs)
			{ return rhs.operator+(n); };

		template <class U> bool	operator==(const reverse_iterator<U> &rhs) const { return this->_base.operator==(rhs.base()); };
		template <class U> bool	operator!=(const reverse_iterator<U> &rhs) const { return this->_base.operator!=(rhs.base()); };
		template <class U> bool	operator< (const reverse_iterator<U> &rhs) const { return this->_base.operator> (rhs.base()); };
		template <class U> bool	operator<=(const reverse_iterator<U> &rhs) const { return this->_base.operator>=(rhs.base()); };
		template <class U> bool	operator> (const reverse_iterator<U> &rhs) const { return this->_base.operator< (rhs.base()); };
		template <class U> bool	operator>=(const reverse_iterator<U> &rhs) const { return this->_base.operator<=(rhs.base()); };

}; // ************************************************** class ReverseIte end //

template <class Iterator>
reverse_iterator<Iterator>::reverse_iterator(void) : _base() { };

template <class Iterator>
reverse_iterator<Iterator>::reverse_iterator(Iterator x) : _base(x) { };

template <class Iterator> template <class U>
reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<U> &u) : _base(u.base()) { };

template <class Iterator> template <class U>
reverse_iterator<Iterator>	&reverse_iterator<Iterator>::operator=(const reverse_iterator<U> &u) {
	if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&u))
		return (*this);
	this->_base = u.base();
	return (*this);
};



	// template <class Iterator>
	// class reverse_iterator
	// {
	// 	public:
	// 	typedef Iterator								iterator_type;
	// 	typedef typename Iterator::value_type			value_type;
	// 	typedef typename Iterator::difference_type		difference_type;
	// 	typedef typename Iterator::pointer				pointer;
	// 	typedef typename Iterator::reference			reference;
		

	// 	reverse_iterator() : _it() {}
	// 	explicit reverse_iterator( iterator_type x ) : _it(x) {}
	// 	template< class U >
	// 	reverse_iterator( const reverse_iterator<U>& other ) : _it(other.base()){}
	// 	virtual ~reverse_iterator(void) {}
	// 	template< class U >
	// 	reverse_iterator& operator=( const reverse_iterator<U>& other )
	// 	{
	// 		_it = other.base(); 
	// 	}
	// 	iterator_type base() const
	// 	{
	// 		return _it;
	// 	}
		

	// 	reference operator*() const
	// 	{
	// 		iterator_type it = _it;
	// 		return *(--it);
	// 	}
	// 	pointer operator->() const
	// 	{
	// 		return &(operator*());
	// 	}

	// 	reference operator[]( difference_type n ) const
	// 	{
	// 		return (_it[-n - 1]);
	// 	}

	// 	reverse_iterator& operator++()
	// 	{
	// 		_it--;
	// 		return (*this);
	// 	}
	// 	reverse_iterator& operator--()
	// 	{
	// 		_it++;
	// 		return (*this);
	// 	}
	// 	reverse_iterator operator++( int )
	// 	{
	// 		reverse_iterator tmp(*this);
	// 		operator++();
	// 		return (tmp);
	// 	}
	// 	reverse_iterator operator--( int )
	// 	{
	// 		reverse_iterator tmp(*this);
	// 		operator--();
	// 		return (tmp);
	// 	}
	// 	reverse_iterator operator+( difference_type n ) const
	// 	{
	// 		return (reverse_iterator(_it - n));
	// 	}
	// 	reverse_iterator operator-( difference_type n ) const
	// 	{
	// 		return (reverse_iterator(_it + n));
	// 	}
	// 	reverse_iterator& operator+=( difference_type n )
	// 	{
	// 		_it -= n;
	// 		return (*this);
	// 	}
	// 	reverse_iterator& operator-=( difference_type n )
	// 	{
	// 		_it += n;
	// 		return (*this);
	// 	}


	// 	template <class U> bool	operator==(const reverse_iterator<U> &rhs) const { return this->_base.operator==(rhs.base()); };
	// 	template <class U> bool	operator!=(const reverse_iterator<U> &rhs) const { return this->_base.operator!=(rhs.base()); };
	// 	template <class U> bool	operator< (const reverse_iterator<U> &rhs) const { return this->_base.operator> (rhs.base()); };
	// 	template <class U> bool	operator<=(const reverse_iterator<U> &rhs) const { return this->_base.operator>=(rhs.base()); };
	// 	template <class U> bool	operator> (const reverse_iterator<U> &rhs) const { return this->_base.operator< (rhs.base()); };
	// 	template <class U> bool	operator>=(const reverse_iterator<U> &rhs) const { return this->_base.operator<=(rhs.base()); };

	// 	private:
	// 		value_type *_it;
	// };//end class
}//end namespace ft

#endif