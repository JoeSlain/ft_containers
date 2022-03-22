#ifndef VECTOR_HPP
#define VECTOR_HPP

# include "Vector_template.hpp"
namespace ft {

	typedef ptrdiff_t									difference_type;
	typedef size_t										size_type;
	/*--------------
		CONSTRUCTORS
	--------------*/
	template <typename T, typename Allocator>
	vector<T, Allocator>::vector(const allocator_type &Alloc) : \
	_alloc(Alloc), _data(NULL), _size(0), _capacity(0) {}

	template <typename T, typename Allocator>
	vector<T, Allocator>::vector(size_type n, const value_type& value, const allocator_type& Alloc) : _size(n),  _capacity(n), _alloc(Alloc)
	{
		this->create(n, value);
	}

	template <typename T, typename Allocator> 
	vector<T, Allocator>::vector(const vector<T,Allocator>& lhs)
	{
		*this = lhs;
	}
	
	template <typename T, typename Allocator>
	vector<T, Allocator>::~vector()
	{
		this->destroy();
	}

	template <typename T, typename Allocator> 
	vector<T,Allocator>& vector<T, Allocator>::operator=(const vector<T,Allocator>& lhs)
	{
		if (this == &lhs)
			return *this;
		this->clear();
		difference_type n = lhs.size();
		if ( n > this->capacity())
			this->reserve( n );
		for (int i = 0; i < n; i++)
			this->_alloc.construct(&this->_data[i], lhs[i]);
		return *this;
	}

	template <typename T, typename Allocator>
	void vector<T, Allocator>::assign(size_type n, const T& u)
	{
		if ( n > this->_capacity)
			this->reserve(n);
		if (this->_size < n)
			this->_size = n;
		for (int i = 0; i < n; i++)
		{
			this->_alloc.destroy(&this->_data[i]);
			this->_alloc.construct(&this->_data[i], u);

		}
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::allocator_type vector<T, Allocator>::get_allocator() const
	{
		return this->_alloc;
	}

	/*--------------
		ITERATORS
	--------------*/
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::begin()
	{
		return (iterator(this->_data));
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const
	{
		return (const_iterator(this->_data));
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::end()
	{
		return (iterator(&this->_data[this->_size]));
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const
	{
		return (const_iterator(&this->_data[this->_size]));
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin()
	{
		return (reverse_iterator(this->_data));
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const
	{
		return (const_reverse_iterator(this->_data));
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend()
	{
		return (reverse_iterator(&this->_data[this->_size]));
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const
	{
		return (const_reverse_iterator(&this->_data[this->_size]));
	}

	/*--------------
		capacity √
	--------------*/
	template <typename T, typename Allocator> typename vector<T, Allocator>::
	size_type vector<T, Allocator>::size() const
	{
		return (this->_size);
	}
	template <typename T, typename Allocator> typename vector<T, Allocator>::
	size_type vector<T, Allocator>::max_size() const
	{
		return(std::numeric_limits<difference_type>::max());
	}
	template <typename T, typename Allocator>
	void vector<T, Allocator>::resize(size_type sz, value_type value)
	{
		if (sz < this->_size)
		{
			while (this->_size > sz)
				this->_alloc.destroy(this->_data[--this->_size]);
		}
		else
		{
			if (sz > this->_capacity)
				this->reserve(sz);
			while (this->_size < sz)
				this->_alloc.construct(&this->data[this->_size++], value);
		}
	}
	template <typename T, typename Allocator> typename vector<T, Allocator>::
	size_type vector<T, Allocator>::capacity() const
	{
		return (this->_capacity);
	}
	template <typename T, typename Allocator>
	bool vector<T, Allocator>::empty() const
	{
		if (!(this->_size))
			return (true);
		return (false);
	}
	
	template <typename T, typename Allocator>
	void vector<T, Allocator>::reserve(size_type n)
	{
		if( n < this->_capacity )
            return;
        T *newArray = this->_alloc.allocate(n); 
        for( int k = 0; k < this->_size; ++k )          
			_alloc.construct( &newArray[ k ], this->_data[ k ] );
		std::swap( this->_data, newArray );
        for (int i = 0; i < this->_size; i++)
			this->_alloc.destroy(&newArray[i]);
		this->_alloc.deallocate(newArray, this->_capacity); 
        this->_capacity = n;
	}

	/*--------------
		ACCESSOR √
	--------------*/
	template <typename T, typename Allocator> typename vector<T, Allocator>::
	reference vector<T, Allocator>::operator[](size_type n)
	{
		return (this->_data[n]);
	}
	template <typename T, typename Allocator> typename vector<T, Allocator>::
	const_reference vector<T, Allocator>::operator[](size_type n) const
	{
		return (this->_data[n]);
	}
	template <typename T, typename Allocator> typename vector<T, Allocator>::
	const_reference vector<T, Allocator>::at(size_type n) const
	{
		if (n >= 0)
		{
			if (!(n < size()))
				throw std::out_of_range("Out of range");
			return (this->_data[n]);
		}
	}
	template <typename T, typename Allocator> typename vector<T, Allocator>::
	reference vector<T, Allocator>::at(size_type n)
	{
		if (n >= 0)
		{
			if (!(n < size()))
				throw std::out_of_range("Out of range");
			return (this->_data[n]);
		}
	}
	template <typename T, typename Allocator> typename vector<T, Allocator>::
	reference vector<T, Allocator>::front()
	{
		return (this->_data[0]);
	}
	template <typename T, typename Allocator> typename vector<T, Allocator>::
	const_reference vector<T, Allocator>::front() const
	{
		return (this->_data[0]);
	}
	template <typename T, typename Allocator> typename vector<T, Allocator>::
	reference vector<T, Allocator>::back()
	{
		return (this->_data[this->_size - 1]);
	}
	template <typename T, typename Allocator> typename vector<T, Allocator>::
	const_reference vector<T, Allocator>::back() const
	{
		return (this->_data[this->_size - 1]);
	}

	/*--------------
		MODIFIERS
	--------------*/
	template <typename T, typename Allocator>
	void vector<T, Allocator>::push_back(const T& lhs)
	{
		if( this->_size == this->_capacity )
            reserve( 2 * this->_capacity + 1 );
        this->_data[ this->_size++ ] = lhs;
	}
	template <typename T, typename Allocator>
	void vector<T, Allocator>::pop_back()
	{
		this->_alloc.destroy(&this->_data[--this->_size]);
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator position, const T& lhs)
	{
		T *newArray = this->_alloc.allocate(this->_size + 1);
		int i = 0;
		int tmp = this->_size + 1;
		iterator it = this->begin();
		iterator end = this->end();
		while (it != position)
			newArray[i++] = *it++;
		newArray[i++] = lhs;
		while (it != end)
			newArray[i++] = *it++;
		position--;
		this->destroy();
		this->_data = newArray;
		this->_capacity = tmp;
		this->_size = tmp;
		return position;
		
	}
	template <typename T, typename Allocator>
	void vector<T, Allocator>::insert(iterator position, size_type n, const T& lhs)
	{
		T *newArray = this->_alloc.allocate(this->_size + n);
		int i = 0;
		int tmp = this->_size + n;
		iterator it = this->begin();
		iterator end = this->end();
		while (it != position)
			newArray[i++] = *it++;
		while (n--)
			newArray[i++] = lhs;
		while (it != end)
			newArray[i++] = *it++;
		this->destroy();
		this->_data = newArray;
		this->_capacity = tmp;
		this->_size = tmp;
	}

	template <typename T, typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator position)
	{
		T *newArray = this->_alloc.allocate(this->_size - 1);
		int s = this->_size - 1;
		iterator start = this->begin();
		iterator end = this->end();
		int i = 0;

		while (start != position)
			newArray[i++] = *start++;
		start++;
		position = start;
		while (start != end)
			newArray[i++] = *start++;
		this->destroy();
		this->_size = s;
		this->_capacity = s;
		this->_data = newArray;
		return position;
	}

	template <typename T, typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator first, iterator last)
	{
		if (!(last - first))
			return last;
		T *newArray = this->_alloc.allocate(this->_size - (last - first));
		int s = this->_size - (last - first);
		int i = 0;
		iterator start = this->begin();
		iterator end = this->end();

		while (start != first)
			newArray[i++] = *start++;
		iterator tmp = start;
		start += last - first;
		while (start != end)
			newArray[i++] = *start++;
		this->destroy();
		this->_size = s;
		this->_capacity = s;
		this->_data = newArray;
		return tmp;
	}
	
	template <typename T, typename Allocator>
	void swap( vector<T,Allocator>& lhs, vector<T,Allocator>& rhs )
	{
		lhs.swap(rhs);
	}
	template <typename T, typename Allocator>
	void vector<T, Allocator>::clear()
	{
		while (this->_size)
			this->_alloc.destroy(&this->_data[--this->_size]);
	}

	/*--------------
		OPERATORS √
	--------------*/
	template <class T, class Allocator>
	bool operator==(const vector<T,Allocator>& lhs,const vector<T,Allocator>& rhs)
	{
		if (lhs._size != rhs._size)
			return false;
		for (int i =0; i < lhs._size; i++)
		{
			if (lhs._data[i] != rhs._data[i])
				return false;
		}
		return true;
	}
	template <class T, class Allocator>
	bool operator< (const vector<T,Allocator>& lhs,
	const vector<T,Allocator>& rhs)
	{
		return (lhs < rhs);
	}
	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& lhs,
	const vector<T,Allocator>& rhs)
	{
		if (lhs._size != rhs._size)
			return true;
		for (int i =0; i < lhs._size; i++)
		{
			if (lhs._data[i] != rhs._data[i])
				return true;
		}
		return false;
	}
	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& lhs,
	const vector<T,Allocator>& rhs)
	{
		return (lhs > rhs);
	}
	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& lhs,
	const vector<T,Allocator>& rhs)
	{
		return (lhs >= rhs);
	}
	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		return (lhs <= rhs);
	}
	/*-----------
		ITERATOR √
	-----------*/
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::iterator::reference			vector<T, Allocator>::iterator::operator*(void) const
	{
		return (*this->_ptr);
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::iterator::pointer				vector<T, Allocator>::iterator::operator->(void) const
	{
		return (this->_ptr);
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::iterator			&vector<T, Allocator>::iterator::operator+=(difference_type n)
	{
		this->_ptr += n;
		return (*this);
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::iterator			&vector<T, Allocator>::iterator::operator-=(difference_type n)
	{
		this->_ptr -= n;
		return (*this);
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::iterator::reference			vector<T, Allocator>::iterator::operator[](difference_type n) const
	{
		return (this->_ptr[n]);
	}

	/*-----------
		PRIVATE
	-----------*/
	template <typename T, typename Allocator>
	void vector<T, Allocator>::create(size_type n, value_type value)
	{
		this->_data = _alloc.allocate(n);
		for (size_t i = 0; i < n; i++)
			this->_alloc.construct(&this->_data[i], value);
	}
	template <typename T, typename Allocator>
	void vector<T, Allocator>::destroy()
	{
		if (!(this->_data))
			return ;
		this->clear();
		this->_alloc.deallocate(this->_data, this->_capacity);
		this->_capacity = 0;
		this->_data = NULL;
	}
}// end namespace ft
#endif