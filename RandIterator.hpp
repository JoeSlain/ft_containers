#ifndef RANDITERATOR_TEMPLATE_HPP
#define RANDITERATOR_TEMPLATE_HPP
# include <cstddef>

namespace ft{
template <typename Spe>
	class RandIte {
		protected:
		Spe									*_ptr;

		public:
		typedef Spe						value_type;
		typedef ptrdiff_t				difference_type;

	RandIte(void) : _ptr(NULL) {
		return ;
	}

	RandIte(Spe *src) : _ptr(src) {
		return ;
	}

	
	RandIte(const RandIte &src) {
		*this = src;
	}

	virtual~RandIte(void) {
		return ;
	}

	RandIte<Spe> &operator=(const RandIte &rhs) {
		if (this == &rhs)
			return (*this);
		this->_ptr = rhs._ptr;
		return (*this);
	}

	
	
		bool	operator==(const RandIte &rhs) const {
		return (this->_ptr == rhs._ptr);
	}

	
	bool	operator!=(const RandIte &rhs) const {
		return (this->_ptr != rhs._ptr);
	}

	
	bool	operator<(const RandIte &rhs) const {
		return (this->_ptr < rhs._ptr);
	}

	
	bool	operator<=(const RandIte &rhs) const {
		return (this->_ptr <= rhs._ptr);
	}

	
	bool	operator>(const RandIte &rhs) const {
		return (this->_ptr > rhs._ptr);
	}

	
	bool	operator>=(const RandIte &rhs) const {
		return (this->_ptr >= rhs._ptr);
	}

	
	RandIte<Spe> &operator++(void) {
		++this->_ptr;
		return (*this);
	}

	
	RandIte<Spe> operator++(int) {
		RandIte<Spe>	tmp(*this);
		++this->_ptr;
		return (tmp);
	}

	
	RandIte<Spe>& operator--(void) {
		--this->_ptr;
		return (*this);
	}

	
	RandIte<Spe> operator--(int) {
		RandIte<Spe>	tmp(*this);
		--this->_ptr;
		return (tmp);
	}

	
	difference_type operator-(const RandIte &rhs) const {
		return (this->_ptr - rhs._ptr);
	}

	
	RandIte<Spe> operator+(difference_type n) const {
		return (RandIte(this->_ptr + n));
	}

	
	RandIte<Spe> operator-(difference_type n) const {
		return (RandIte(this->_ptr - n));
	}
		friend RandIte<Spe>	operator+(difference_type n, const RandIte &rhs)
			{ return rhs.operator+(n); };

	};//end RandIterator class
}//end namespace
#endif
