#ifndef VECTOR_HPP
#define VECTOR_HPP

# include "Vector_template.hpp"
namespace ft {
/*--------------
		CONSTRUCTORS
	--------------*/

	vector(const Allocator& = Allocator()) : \
		_alloc(Allocator), _data(NULL), _size(0), _capacity(0) {}

	vector(size_type n, const T& value = T(), const Allocator& = Allocator()) \
			: _alloc(Allocator), _data(T), _size(n), _capacity(n) {}
	/*template <class InputIterator>
	vector(InputIterator first, InputIterator last,
	const Allocator& = Allocator());
	vector(const vector<T,Allocator>& x);
	~vector()
	{
		if (!(this->_data))
			return ;
		this->clear();
			this->_alloc.deallocate(this->_data, this->_capacity);
			this->_data = NULL;
	}
	vector<T,Allocator>& operator=(const vector<T,Allocator>& x);

	template <class InputIterator>
	void assign(InputIterator first, InputIterator last);
	void assign(size_type n, const T& u);

	allocator_type get_allocator() const;*/

	/*--------------
		ITERATORS
	--------------*/
	iterator begin()
	{
		return (iterator(this->_data));
	}

	const_iterator begin() const
	{
		return (this->_data);
	}

	iterator end()
	{
		return (iterator(&this->_data[size]));
	}

	const_iterator end() const
	{

	}

	reverse_iterator rbegin()
	{

	}

	const_reverse_iterator rbegin() const
	{

	}

	reverse_iterator rend()
	{

	}

	const_reverse_iterator rend() const
	{

	}

	/*--------------
		CAPACITY √
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
		if (!(this->_size)
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
            newArray[ k ] = std::move( this->_data[ k ] );
        std::swap( this->_data, newArray );
        for (int i = 0; newArray[i]; i++)
			this->_alloc.destroy(newArray[i]);
		this._alloc.deallocate(newArray, this->_capacity); 
        this->capacity = n;
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
				throw std::out_of_range();
			return (this->_data[n]);
		}
	}
	template <typename T, typename Allocator> typename vector<T, Allocator>::
	reference vector<T, Allocator>::at(size_type n)
	{
		if (n >= 0)
		{
			if (!(n < size()))
				throw std::out_of_range();
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
	void vector<T, Allocator>::push_back(const T& x)
	{
		if( this->_size == this->_capacity )
            reserve( 2 * this->_capacity + 1 );
        this->_data[ this->_size++ ] = x;
	}
	template <typename T, typename Allocator>
	void vector<T, Allocator>::pop_back()
	{
		this->_alloc.destroy(&this->_data[--this->_size]);
	}
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator position, const T& x)
	{

	}
	template <typename T, typename Allocator>
	void vector<T, Allocator>::insert(iterator position, size_type n, const T& x)
	{

	}

	/*template <class InputIterator>
	void insert(iterator position,
	InputIterator first, InputIterator last);
	iterator erase(iterator position);

	iterator erase(iterator first, iterator last);*/
	
	template <typename T, typename Allocator>
	void swap( std::vector<T,Allocator>& lhs, std::vector<T,Alloc>& rhs )
	{
		lhs.swap(rhx);
	}
	template <typename T, typename Allocator>
	void clear()
	{
		while (this->_size)
			this->_alloc.destroy(&this->_data[--this->_size]);
	}

	/*--------------
		OPERATORS √
	--------------*/
	template <class T, class Allocator>
	bool operator==(const vector<T,Allocator>& x,const vector<T,Allocator>& y)
	{
		if (x._size != y._size)
			return false;
		for (int i =0; i < x._size; i++)
		{
			if (x._data[i] != y._data[i])
				return false;
		}
		return true;
	}
	template <class T, class Allocator>
	bool operator< (const vector<T,Allocator>& x,
	const vector<T,Allocator>& y)
	{
		return (lhs < rhs);
	}
	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& x,
	const vector<T,Allocator>& y)
	{
		if (x._size != y._size)
			return true;
		for (int i =0; i < x._size; i++)
		{
			if (x._data[i] != y._data[i])
				return true;
		}
		return false;
	}
	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& x,
	const vector<T,Allocator>& y)
	{
		return (lhs > rhs);
	}
	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x,
	const vector<T,Allocator>& y)
	{
		return (lhs >= rhs);
	}
	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
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
}
// end namespace ft
#endif