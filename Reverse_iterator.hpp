namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		public:
		typedef Iterator								iterator_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		

		reverse_iterator() : _it() {}
		explicit reverse_iterator( iterator_type x ) : _it(x) {}
		template< class U >
		reverse_iterator( const reverse_iterator<U>& other ) : _it(other.base()){}
		virtual ~reverse_iterator(void) {}
		template< class U >
		reverse_iterator& operator=( const reverse_iterator<U>& other )
		{
			_it = other.base(); 
		}
		iterator_type base() const
		{
			return _it;
		}
		

		reference operator*() const
		{
			iterator_type it = _it;
			return *(--it);
		}
		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[]( difference_type n ) const
		{
			return (_it[-n - 1]);
		}

		reverse_iterator& operator++()
		{
			_it--;
			return (*this);
		}
		reverse_iterator& operator--()
		{
			_it++;
			return (*this);
		}
		reverse_iterator operator++( int )
		{
			reverse_iterator tmp(*this);
			operator++();
			return (tmp);
		}
		reverse_iterator operator--( int )
		{
			reverse_iterator tmp(*this);
			operator--();
			return (tmp);
		}
		reverse_iterator operator+( difference_type n ) const
		{
			return (reverse_iterator(_it - n));
		}
		reverse_iterator operator-( difference_type n ) const
		{
			return (reverse_iterator(_it + n));
		}
		reverse_iterator& operator+=( difference_type n )
		{
			_it -= n;
			return (*this);
		}
		reverse_iterator& operator-=( difference_type n )
		{
			_it += n;
			return (*this);
		}


		template <class U> bool	operator==(const reverse_iterator<U> &rhs) const { return this->_base.operator==(rhs.base()); };
		template <class U> bool	operator!=(const reverse_iterator<U> &rhs) const { return this->_base.operator!=(rhs.base()); };
		template <class U> bool	operator< (const reverse_iterator<U> &rhs) const { return this->_base.operator> (rhs.base()); };
		template <class U> bool	operator<=(const reverse_iterator<U> &rhs) const { return this->_base.operator>=(rhs.base()); };
		template <class U> bool	operator> (const reverse_iterator<U> &rhs) const { return this->_base.operator< (rhs.base()); };
		template <class U> bool	operator>=(const reverse_iterator<U> &rhs) const { return this->_base.operator<=(rhs.base()); };

		private:
			value_type *_it;
	};//end class
}//end namespace ft