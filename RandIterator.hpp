#ifndef RANDITERATOR_TEMPLATE_HPP
#define RANDITERATOR_TEMPLATE_HPP
# include <cstddef>

namespace ft{
	template<typename T>
	class RandIterator{
		public:
			typedef T  value_type;
			typedef ptrdiff_t  difference_type;

	
		RandIterator(void) : _ptr(NULL) {}
		
		RandIterator(T *src) : _ptr(src) {}
		
		RandIterator(const RandIterator &src)
		{
			*this = src;
		}
		
		~RandIterator(void) {}
		
		RandIterator<T>	& operator=(RandIterator const &rhs)
		{
			if (this == &rhs)
				return (*this);
			this->_ptr = rhs._ptr;
			return (*this);
		}




		bool	operator==(const RandIterator &rhs) const
		{
			return (this->_ptr == rhs._ptr);
		}
		
		bool	operator!=(const RandIterator &rhs) const
		{
			return (this->_ptr != rhs._ptr);
		}
		
		bool	operator<(const RandIterator &rhs) const
		{
			return (this->_ptr < rhs._ptr);
		}
		
		bool	operator<=(const RandIterator &rhs) const
		{
			return (this->_ptr <= rhs._ptr);
		}
		
		bool	operator>(const RandIterator &rhs) const
		{
			return (this->_ptr > rhs._ptr);
		}
		
		bool	operator>=(const RandIterator &rhs) const
		{
			return (this->_ptr >= rhs._ptr);
		}

		
		RandIterator<T>	&operator++(void)
		{
			this->_ptr++;
			return (*this);
		}
		
		RandIterator<T>	operator++(int)
		{
			RandIterator<T> tmp = *this;
			++(*this);
			return (tmp);
		}
		
		RandIterator<T>	&operator--(void)
		{
			this->_ptr--;
			return (*this);
		}
		
		RandIterator<T>	operator--(int)
		{
			RandIterator<T> tmp = (*this);
			this->_ptr++;
			return (tmp);
		}
		
		difference_type	operator-(const RandIterator &rhs) const
		{
			return (this->_ptr - rhs._ptr);
		}
		
		RandIterator<T>			operator+(difference_type n) const
		{
			return (RandIterator(this->_ptr + n));
		}
		
		RandIterator<T>			operator-(difference_type n) const
		{
			return (RandIterator(this->_ptr - n));
		}
				friend RandIterator<T>	operator+(difference_type n, const RandIterator &rhs)
					{ return rhs.operator+(n); };

		protected:
			T *_ptr; 
	};//end RandIterator class
}//end namespace
#endif
