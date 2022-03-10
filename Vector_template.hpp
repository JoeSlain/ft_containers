#ifndef VECTOR_TEMPLATE_HPP
# define VECTOR_TEMPLATE_HPP
# include <memory>
# include <stdexcept>
# include <limits>
# include "RandIterator.hpp"

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

		reference			operator*(void) const;
		pointer				operator->(void) const;
		iterator			&operator+=(difference_type n);
		iterator			&operator-=(difference_type n);
		reference			operator[](difference_type n) const;

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

	class const_iterator : public RandIterator<value_type> {
	protected:
	typedef RandIterator<value_type> base;
	const_iterator(value_type *src) : RandIterator<value_type>(src) {};
	private:
	const_iterator(const RandIterator<value_type> &src) : RandIterator<value_type>(src) {};

	public:
	const_iterator(void) : RandIterator<value_type>() {};
	const_iterator(const const_iterator &src) : RandIterator<value_type>(src) {};

	typedef value_type&			reference;
	typedef value_type*			pointer;

	reference			operator*(void) const;
	pointer				operator->(void) const;
	const_iterator			&operator+=(difference_type n);
	const_iterator			&operator-=(difference_type n);
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
	
	typedef std::reverse_iterator<iterator> 		reverse_iterator;
	typedef std::reverse_iterator<const_iterator> 	const_reverse_iterator;

	/*--------------
		CONSTRUCTORS
	--------------*/
	explicit vector(const allocator_type &Alloc = allocator_type());

	explicit vector(size_type n, const value_type& value = T(), const allocator_type& Alloc= allocator_type());
	template <class iterator>
	vector(iterator first, iterator last, const allocator_type& Alloc = allocator_type())
	{
		difference_type diff = last - first;
		int i = 0;
		this->_capacity = static_cast<size_type>(diff);
		this->_size = static_cast<size_type>(diff);
		this->_alloc = Alloc;
		this->_data = this->_alloc.allocate(this->_capacity);
		while (first < last)
		{
			this->_alloc.construct(&this->_data[i++], *first);
			first++;
		}
	}
	vector(const vector<T,Allocator>& x);
	~vector();
	vector<T,Allocator>& operator=(const vector<T,Allocator>& x);

	template <class InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		int i = 0;
		this->clear();
		difference_type s = last - first;
		if (s > this->_capacity)
			this->reserve(s);
		while (first != last)
			this->_alloc.construct(&this->_data[i++], *first++);
		this->_size = s;
	}
	void assign(size_type n, const T& u);

	allocator_type get_allocator() const;

	/*--------------
		ITERATORS
	--------------*/
	
	iterator begin();

	const_iterator begin() const;

	iterator end();

	const_iterator end() const;

	reverse_iterator rbegin();

	const_reverse_iterator rbegin() const;

	reverse_iterator rend();

	const_reverse_iterator rend() const;
	
	/*--------------
		CAPACITY
	--------------*/
	size_type size() const;

	size_type max_size() const;

	void resize(size_type sz, T c = T());

	size_type capacity() const;

	bool empty() const;

	void reserve(size_type n);

	/*--------------
		ACCESSOR
	--------------*/
	
	reference operator[](size_type n);

	const_reference operator[](size_type n) const;

	const_reference at(size_type n) const;

	reference at(size_type n);

	reference front();

	const_reference front() const;

	reference back();

	const_reference back() const;

	/*--------------
		MODIFIERS
	--------------*/
	void push_back(const T& x);

	void pop_back();

	iterator insert(iterator position, const T& x);

	void insert(iterator position, size_type n, const T& x);

	template <class InputIterator>
	void insert(iterator position,
	InputIterator first, InputIterator last)
	{
		T *newArray = this->_alloc.allocate(this->_size + (last - first));
		int i = 0;
		int tmp = this->_size + (last - first);
		iterator it = this->begin();
		iterator end = this->end();
		while (it != position)
			newArray[i++] = *it++;
		while (first != last)
			newArray[i++] = *first++;
		while (it != end)
			newArray[i++] = *it++;
		this->destroy();
		this->_data = newArray;
		this->_capacity = tmp;
		this->_size = tmp;
	}
	iterator erase(iterator position);

	iterator erase(iterator first, iterator last);

	void swap(vector<T,Allocator>&);

	void clear();

	private:
	value_type	*_data; //the array
	size_type	_size;	// the actual occupied space in array
	size_type	_capacity; //total space available in array
	allocator_type _alloc; //allocator

	void destroy();
	void create(size_type n, value_type value);
};//---------------------------------------- END OF VECTOR CLASS 

template <class T, class Allocator>
bool operator==(const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator< (const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator!=(const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator> (const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator>=(const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator<=(const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
/*---------------------
	SPECIALIZED ALGOS
----------------------*/
template <class T, class Allocator>
void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);

}//----------------------------------------- END OF NAMESPACE

#endif

