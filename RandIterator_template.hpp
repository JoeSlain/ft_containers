#ifndef RANDITERATOR_TEMPLATE_HPP
#define RANDITERATOR_TEMPLATE_HPP
# include <cstddef>

namespace ft{
	template<typename T>
	class RandIterator{
		public:
			typedef T  value_type;
			typedef ptrdiff_t  difference_type;

			RandIterator(void);
			RandIterator(T *src);
			RandIterator(const RandIterator &src);
			virtual ~RandIterator(void);
			RandIterator	&operator=(RandIterator const &rhs);

			bool	operator==(const RandIterator &rhs) const;
			bool	operator!=(const RandIterator &rhs) const;
			bool	operator<(const RandIterator &rhs) const;
			bool	operator<=(const RandIterator &rhs) const;
			bool	operator>(const RandIterator &rhs) const;
			bool	operator>=(const RandIterator &rhs) const;

			RandIterator<T>	&operator++(void);
			RandIterator<T>	operator++(int);
			RandIterator<T>	&operator--(void);
			RandIterator<T>	operator--(int);

			difference_type			operator-(const RandIterator &rhs) const;
			RandIterator<T>			operator+(difference_type n) const;
			RandIterator<T>			operator-(difference_type n) const;
			friend RandIterator<T>	operator+(difference_type n, const RandIterator &rhs)
				{ return rhs.operator+(n); };

		protected:
			T *_ptr; 
	};//end RandIterator class
}//end namespace
#endif
