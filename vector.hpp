#ifndef VECTOR_TEMPLATE_HPP
# define VECTOR_TEMPLATE_HPP
# include <memory>
# include <stdexcept>
# include <limits>
# include <iterator>
# include "RandIterator.hpp"
# include "utils.hpp"

namespace ft
{
template <class T, class Allocator = std::allocator<T> >
class vector {

	public:

	/*--------------
		TYPEDEF
	--------------*/
	typedef T											value_type;
	typedef Allocator									allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;


	typedef ptrdiff_t									difference_type;
	typedef size_t										size_type;
	
	/*--------------
		ITERATOR
	--------------*/
	class iterator : public RandIterator<value_type> {
		protected:
		typedef RandIterator<value_type> base;
		iterator(value_type *src) : RandIterator<value_type>(src) {};
		private:
		iterator(const RandIterator<value_type> &src) : RandIterator<value_type>(src) {};

		public:
		iterator(void) : RandIterator<value_type>() {};
		iterator(const iterator &src) : RandIterator<value_type>(src) {};

		typedef value_type&			reference;
		typedef value_type*			pointer;
		typedef std::random_access_iterator_tag iterator_category;

	reference			operator*(void) const
	{return (*this->_ptr);}

	pointer				operator->(void) const
	{return (this->_ptr);}
	
	iterator			&operator+=(difference_type n)
	{	this->_ptr += n;
		return (*this);
	}
	
	iterator			&operator-=(difference_type n)
	{
		this->_ptr -= n;
		return (*this);
	}
	
	reference			operator[](difference_type n) const
	{ return (this->_ptr[n]);}

		difference_type		operator-(const RandIterator<value_type> &n) const { return base::operator-(n); };
		iterator			operator-(difference_type n) const { return base::operator-(n); };
		iterator			operator+(difference_type n) const { return base::operator+(n); };
		friend iterator		operator+(difference_type n, const iterator &rhs) { return rhs.operator+(n); };

		iterator			&operator++(void) { base::operator++(); return *this; };
		iterator			operator++(int) { return base::operator++(0); };
		iterator			&operator--(void) { base::operator--(); return *this; };
		iterator			operator--(int) { return base::operator--(0); };

		friend class vector;
	};

	/*--------------
		CONST ITE
	--------------*/
	class const_iterator : public RandIterator<value_type> {
	protected:
	typedef RandIterator<value_type> base;
	const_iterator(value_type *src) : RandIterator<value_type>(src) {};
	private:

	public:
	const_iterator(const RandIterator<value_type> &src) : RandIterator<value_type>(src) {};
	const_iterator(void) : RandIterator<value_type>() {};
	const_iterator(const const_iterator &src) : RandIterator<value_type>(src) {};

	typedef value_type&			reference;
	typedef value_type*			pointer;
	typedef std::random_access_iterator_tag iterator_category;

	reference			operator*(void) const
	{
		return *this->_ptr;
	}

	pointer				operator->(void) const
	{
		return this->_ptr;
	}
	const_iterator			&operator+=(difference_type n) {*this->_ptr += n; return *this;}
	const_iterator			&operator-=(difference_type n) {{*this->_ptr -= n; return *this;}}
	reference			operator[](difference_type n) const;

	difference_type		operator-(const RandIterator<value_type> &n) const { return base::operator-(n); };
	const_iterator			operator-(difference_type n) const { return base::operator-(n); };
	const_iterator			operator+(difference_type n) const { return base::operator+(n); };
	friend const_iterator		operator+(difference_type n, const const_iterator &rhs) { return rhs.operator+(n); };

	const_iterator			&operator++(void) { base::operator++(); return *this; };
	const_iterator			operator++(int) { return base::operator++(0); };
	const_iterator			&operator--(void) { base::operator--(); return *this; };
	const_iterator			operator--(int) { return base::operator--(0); };

	friend class vector;
	};
	
	/*--------------
		VECTOR
	--------------*/

	typedef std::reverse_iterator<iterator> 		reverse_iterator;
	typedef std::reverse_iterator<const_iterator> 	const_reverse_iterator;

	/*----------------
		CONSTRUCTORS
	----------------*/
	explicit vector(const allocator_type &Alloc = allocator_type()) : \
	_data(NULL), _size(0), _capacity(0), _alloc(Alloc) {}

	explicit vector(size_type n, const value_type& value = T(), const allocator_type& Alloc= allocator_type()) \
	: _size(n),  _capacity(n), _alloc(Alloc)
	{this->create(n, value);}

	template <class Ite>
	vector(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
			Ite last, const allocator_type &alloc = allocator_type()) : _data(NULL),  _size(0), _capacity(0), _alloc(alloc) {
		this->create(ft::itlen(first, last), first, last);
	}



	
	vector(vector const &src) : \
	_data(NULL), _size(0), _capacity(0), _alloc(allocator_type()) {
	*this = src;
	}

	~vector() {this->destroy();}

	vector<T, allocator_type>	&operator=(vector const &rhs) {
		if (this == &rhs)
			return (*this);
		const_iterator first = rhs.begin();
		const_iterator last = rhs.end();
		size_type len = ft::itlen(first, last);
		this->create((len > this->_capacity) ? len : this->_capacity, first, last);
		return (*this);
	}



	template <typename InputIterator>
	void	assign(InputIterator first, InputIterator last) {
		this->clear();
		this->insert(this->begin(), first, last);
	}

	void	assign(size_type n, T const &val) {
		this->clear();
		this->insert(this->begin(), n, val);
	}

	allocator_type get_allocator() const
	{return this->_alloc;}



	/*--------------
		ITERATORS
	--------------*/
	
	iterator begin() {return (iterator(this->_data));}

	const_iterator begin() const {return (const_iterator(this->_data));}

	iterator end() {return (iterator(&this->_data[this->_size]));}

	const_iterator end() const {return (const_iterator(&this->_data[this->_size]));}

	reverse_iterator rbegin() {return (reverse_iterator(this->_data));}

	const_reverse_iterator rbegin() const {return (const_reverse_iterator(this->_data));}

	reverse_iterator rend() {return (reverse_iterator(&this->_data[this->_size]));}

	const_reverse_iterator rend() const {return (const_reverse_iterator(&this->_data[this->_size]));}
	
	/*--------------
		CAPACITY
	--------------*/
	size_type size() const {return (this->_size);}

	size_type max_size() const {return (this->_alloc.max_size());}

	void		resize(size_type size, value_type val = value_type()) {
		if (size < this->_size)
		{
			while (size < this->_size)
				this->_alloc.destroy(&this->_data[--this->_size]);
		}
		else
		{
			size_type const &lambda = this->_size;

			if (size <= this->_capacity)
				;
			else if (size <= lambda * 2)
				this->reserve(lambda * 2);
			else
				this->reserve(size);
			while (this->_size < size)
				this->_alloc.construct(&this->_data[this->_size++], val);
		}
	}

	size_type capacity() const {return (this->_capacity);}

	bool empty() const
	{
		if (!(this->_size))
			return (true);
		return (false);
	}

	void reserve(size_type n)
	{
		if( n < this->_capacity )
            return;
        T *newArray = this->_alloc.allocate(n); 
        for( long unsigned int k = 0; k < this->_size; ++k )          
			_alloc.construct( &newArray[ k ], this->_data[ k ] );
		std::swap( this->_data, newArray );
        for (long unsigned int i = 0; i < this->_size; i++)
			this->_alloc.destroy(&newArray[i]);
		this->_alloc.deallocate(newArray, this->_capacity); 
        this->_capacity = n;
	}

	/*--------------
		ACCESSOR
	--------------*/

	reference operator[](size_type n)
	{
		return (this->_data[n]);
	}
	const_reference operator[](size_type n) const
	{
		return (this->_data[n]);
	}
	const_reference at(size_type n) const
	{
		if (n >= 0)
		{
			if (!(n < size()))
				throw std::out_of_range("Out of range");
			return (this->_data[n]);
		}
		else
			throw std::out_of_range("Out of range");
	}
	reference at(size_type n)
	{
		if (n >= 0)
		{
			if (!(n < size()))
				throw std::out_of_range("Out of range");
			return (this->_data[n]);
		}
		else
			throw std::out_of_range("Out of range");
	}
	reference front()
	{
		return (this->_data[0]);
	}
	const_reference front() const
	{
		return (this->_data[0]);
	}
	reference back()
	{
		return (this->_data[this->_size - 1]);
	}
	const_reference back() const
	{
		return (this->_data[this->_size - 1]);
	}

	/*--------------
		MODIFIERS
	--------------*/
		
	void push_back(const T& lhs)
	{
		if( this->_size == this->_capacity )
            reserve( 2 * this->_capacity + 1 );
        this->_data[ this->_size++ ] = lhs;
	}
	
	void pop_back()
	{
		this->_alloc.destroy(&this->_data[--this->_size]);
	}
	
	iterator	insert(iterator position, const value_type &val) {
		difference_type idx = position - this->begin();

		this->insert(position, 1, val);
		return (iterator(this->begin() + idx));
	}

	
	void	insert(iterator position, size_type n, const value_type &val) {
		difference_type const	idx = position - this->begin();
		difference_type const	old_end_idx = this->end() - this->begin();
		iterator				old_end, end;

		this->resize(this->_size + n);

		end = this->end();
		position = this->begin() + idx;
		old_end = this->begin() + old_end_idx;
		while (old_end != position)
			*--end = *--old_end;
		while (n-- > 0)
			*position++ = val;
	}

	
	iterator erase(iterator position)
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

	
	iterator	erase(iterator first, iterator last) {
	iterator tmp = first;
	iterator end = this->end();
	size_type deleted = ft::itlen(first, last);

	while (last != end)
	{
		*first = *last;
		++first;
		++last;
	}
	while (deleted-- > 0)
		this->_alloc.destroy(&this->_data[--this->_size]);
	return (tmp);
}
	
	
	void swap( vector<T,Allocator>& lhs, vector<T,Allocator>& rhs )
	{
		lhs.swap(rhs);
	}
	
	void clear()
	{
		while (this->_size)
			this->_alloc.destroy(&this->_data[--this->_size]);
	}
	
	template <typename Ite>
	void insert(iterator position, Ite first, typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type last) {
		difference_type const	idx = position - this->begin();
		difference_type const	old_end_idx = this->end() - this->begin();
		iterator				old_end, end;

		this->resize(this->_size + (ft::itlen(first, last)));

		end = this->end();
		position = this->begin() + idx;
		old_end = this->begin() + old_end_idx;
		while (old_end != position)
			*--end = *--old_end;
		while (first != last)
			*position++ = *first++;
	}



	void	swap(vector &x) {
		vector<T, allocator_type> tmp;

		tmp._cpy_content(x);
		
		x._cpy_content(*this);
		
		this->_cpy_content(tmp);
		
	}
	private:
	value_type	*_data; //the array
	size_type	_size;	// the actual occupied space in array
	size_type	_capacity; //total space available in array
	allocator_type _alloc; //allocator

	void create(size_type n, value_type value)
	{
		this->_data = _alloc.allocate(n);
		for (size_t i = 0; i < n; i++)
			this->_alloc.construct(&this->_data[i], value);
	}
	template <typename Ite>
	void	create(difference_type capacity, Ite first, Ite last) {
	vector<T, allocator_type> res;
	difference_type len = ft::itlen(first, last);

	if (capacity < len || capacity < 0)
		throw std::bad_alloc();
	res._alloc = this->_alloc;
	res._size = len; res._capacity = capacity;
	res._data = res._alloc.allocate(capacity);
	for (size_type i = 0; first != last; ++first)
		res._alloc.construct(&res._data[i++], *first);
	this->destroy();
	this->_cpy_content(res);
	}
	template <typename Ite, typename Iterator>
	void	_cpy_data(Ite start, Iterator first, Iterator last) {
	while (first != last)
	{
		*start = *first;
		++start;
		++first;
	}
}

	void	_cpy_content(vector<T, allocator_type> &vct) {
		this->_data = vct._data;
		this->_alloc = vct._alloc;
		this->_size = vct._size;
		this->_capacity = vct._capacity;
		vct._data = NULL; vct._size = 0; vct._capacity = 0;
	}

	void destroy()
	{
		if (!(this->_data))
			return ;
		this->clear();
		this->_alloc.deallocate(this->_data, this->_capacity);
		this->_capacity = 0;
		this->_data = NULL;
	}


};//---------------------------------------- END OF VECTOR CLASS 

	/*--------------
		OPERATORS √
	--------------*/
template <class T, class Alloc>
bool	operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool	operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool	operator< (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool	operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool	operator> (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	return (rhs < lhs);
}

template <class T, class Alloc>
bool	operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	return !(lhs < rhs);
}

/*---------------------
	SPECIALIZED ALGOS
----------------------*/
template <class T, class Allocator>
void swap(vector<T,Allocator>& x, vector<T,Allocator>& y)
{
	x.swap(y) ;
}

}//----------------------------------------- END OF NAMESPACE

#endif

