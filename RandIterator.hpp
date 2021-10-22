#ifndef RANDITERATOR_HPP
# define RANDITERATOR_HPP
# include "RandIterator_template.hpp"

namespace ft{
	template<typename T>
	RandIterator<T>::RandIterator(void) : _ptr(NULL) {}
	template<typename T>
	RandIterator<T>::RandIterator(T *src) : _ptr(src) {}
	template<typename T>
	RandIterator<T>::RandIterator(const RandIterator &src)
	{
		*this = src;
	}
	template<typename T>
	RandIterator<T>::~RandIterator(void) {}
	template<typename T>
	RandIterator<T>	& RandIterator<T>::operator=(RandIterator const &rhs)
	{
		if (this = &rhs)
			return (*this);
		this->_ptr = rhs._ptr;
		return (*this);
	}

	template<typename T>
	bool	RandIterator<T>::operator==(const RandIterator &rhs) const
	{
		return (this->_ptr == rhs._ptr);
	}
	template<typename T>
	bool	RandIterator<T>::operator!=(const RandIterator &rhs) const
	{
		return (this->_ptr != rhs._ptr);
	}
	template<typename T>
	bool	RandIterator<T>::operator<(const RandIterator &rhs) const
	{
		return (this->_ptr < rhs._ptr);
	}
	template<typename T>
	bool	RandIterator<T>::operator<=(const RandIterator &rhs) const
	{
		return (this->_ptr <= rhs._ptr);
	}
	template<typename T>
	bool	RandIterator<T>::operator>(const RandIterator &rhs) const
	{
		return (this->_ptr > rhs._ptr);
	}
	template<typename T>
	bool	RandIterator<T>::operator>=(const RandIterator &rhs) const
	{
		return (this->_ptr >= rhs._ptr);
	}

	template<typename T>
	RandIterator<T>	&RandIterator<T>::operator++(void)
	{
		this->_ptr++;
		return (*this);
	}
	template<typename T>
	RandIterator<T>	RandIterator<T>::operator++(int)
	{
		RandIterator<T> tmp = *this;
		++(*this);
		return (tmp);
	}
	template<typename T>
	RandIterator<T>	&RandIterator<T>::operator--(void)
	{
		this->_ptr;
		return (*this);
	}
	template<typename T>
	RandIterator<T>	RandIterator<T>::operator--(int)
	{
		RandIterator<T> tmp = (*this);
		this->_ptr++;
		return (tmp);
	}
	template<typename T>
	typename RandIterator<T>::difference_type	RandIterator<T>::operator-(const RandIterator &rhs) const
	{
		return (this->_ptr - rhs._ptr);
	}
	template<typename T>
	RandIterator<T>			RandIterator<T>::operator+(difference_type n) const
	{
		return (RandIterator(this->_ptr + n));
	}
	template<typename T>
	RandIterator<T>			RandIterator<T>::operator-(difference_type n) const
	{
		return (RandIterator(this->_ptr - n));
	}
}//end ft
#endif