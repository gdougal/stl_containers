//
// Created by Gilberto Dougal on 3/15/21.
//

#ifndef FT_VECTOR_FT_UTILS_HPP
#define FT_VECTOR_FT_UTILS_HPP

#include <algorithm>
#include <memory>
#include "vectorIterator.hpp"
#include "list_utils.hpp"
#include "ft_map_utils.hpp"
//gu - general_utils
namespace gu {

	struct false_type {
		char v[1];
		const static bool value = false;
	};

	struct true_type {
		false_type v[2];
		const static bool value = true;
	};

	template<class T, class U>
	struct is_same : false_type {
	};

	template<class T>
	struct is_same<T, T> : true_type {
	};

	template<class U, typename ptr>
	struct is_input {
	private:
		template<class T1>
		static uint64_t	foo(ptr T1::* = 0)	{return 0;};
		template<typename T1>
		static uint8_t	foo(T1 = 0)					{return 0;};
	public:
		const static bool value = (sizeof(foo<U>(0)) == sizeof(uint64_t)) || is_same<U, ptr>::value;
	};

	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};


#define ENABLE_IF_TYPE(type_ref) \
	typename gu::enable_if<gu::is_input<type_ref, pointer>::value, type_ref>::type* = 0

	template<typename Any>
	void			f_swp(Any& val, Any& ref) {
		Any	buf;
		buf = val;
		val = ref;
		ref = buf;
	};

	template<class T_it>
	class const_reverse_it;

	template<class T_it>
	class reverse_it	{
	public:
		typedef	T_it																			iterator_type;
		typedef typename T_it::iterator_category					iterator_category;
		typedef	typename T_it::value_type									value_type;
		typedef std::ptrdiff_t														difference_type;
		typedef typename T_it::pointer										pointer;
		typedef typename T_it::reference									reference;
		typedef const_reverse_it<iterator_type>						const_it;


		reverse_it() {};

		explicit reverse_it(const iterator_type& it): iter(it) {};

		reverse_it(const reverse_it<iterator_type>& rev_it) {
			if (this != &rev_it)
				*this = rev_it;
		};

		explicit reverse_it(const const_it& rev_it) {
			*this = rev_it;
		};

		reverse_it& operator=(const reverse_it<iterator_type>& rev_it) {
			if (this != &rev_it)
				iter = rev_it.iter;
			return *this;
		};

		reverse_it& operator=(const const_it& rev_it) {
			iter = rev_it.base();
			return *this;
		};

		iterator_type	base()												const	{ return iter; };
		reference			operator*()										const	{ iterator_type it = iter; return *(--it); };
		pointer				operator->()									const	{ return &(operator*()); };
		reverse_it		operator+(difference_type n)	const { return reverse_it(iterator_type(iter - n)); };
		reverse_it&		operator++()												{ --iter; return *this ;};
		reverse_it		operator++(int)											{ reverse_it ret(*this); --iter; return ret; };
		reverse_it&		operator+=(difference_type n)				{ iter -= n; return *this; };
		reverse_it		operator-(difference_type n)	const { return reverse_it(iter + n); };
		reverse_it&		operator--()												{ ++iter; return *this ;};
		reverse_it		operator--(int)											{ reverse_it ret(*this); ++iter; return ret; };
		reverse_it&		operator-=(difference_type n)				{ iter += n; return *this; };
		reference			operator[](difference_type n)	const	{ return *(*this + n); };

	private:
		iterator_type iter;
	};

	template<class T_it>
	class const_reverse_it	{

	public:
		typedef	T_it																			iterator_type;
		typedef typename T_it::iterator_category					iterator_category;
		typedef	typename T_it::value_type									value_type;
		typedef typename T_it::difference_type						difference_type;
		typedef typename T_it::pointer										pointer;
		typedef typename T_it::reference									reference;

		const_reverse_it(): iter() {};

		const_reverse_it(const iterator_type& it): iter(it) {};

		const_reverse_it(const const_reverse_it<iterator_type>& rev_it) {
			if (this != &rev_it)
				*this = rev_it;
		};

		const_reverse_it(const reverse_it<iterator_type>& rev_it) {
			*this = rev_it;
		};

		const_reverse_it& operator=(const const_reverse_it<iterator_type>& rev_it) {
			if (this != &rev_it)
				iter = rev_it.iter;
			return *this;
		};

		const_reverse_it& operator=(const reverse_it<iterator_type>& rev_it) {
			iter = rev_it.base();
			return *this;
		};

		iterator_type				base()												const	{ return iter; };
		const reference			operator*()										const	{ iterator_type it = iter; return *(--it); };
		const pointer				operator->()									const	{ return &(operator*()); };
		const_reverse_it		operator+(difference_type n)	const { return const_reverse_it(iter - n); };
		const_reverse_it&		operator++()												{ --iter; return *this ;};
		const_reverse_it		operator++(int)											{ const_reverse_it ret(*this); --iter; return ret; };
		const_reverse_it&		operator+=(difference_type n)				{ iter -= n; return *this; };
		const_reverse_it		operator-(difference_type n)	const { return const_reverse_it(iter + n); };
		const_reverse_it&		operator--()												{ ++iter; return *this ;};
		const_reverse_it		operator--(int)											{ const_reverse_it ret(*this); ++iter; return ret; };
		const_reverse_it&		operator-=(difference_type n)				{ iter += n; return *this; };
		reference						operator[](difference_type n)	const	{ return *(*this + n); };

	private:
		iterator_type iter;
	};

	template <class Iterator>
	bool operator==(const reverse_it<Iterator>& lhs, const reverse_it<Iterator>& rhs)	{ return lhs.base() == rhs.base(); };

	template <class Iterator>
	bool operator!=(const reverse_it<Iterator>& lhs, const reverse_it<Iterator>& rhs)	{ return !(lhs.base() == rhs.base()); };

	template <class Iterator>
	bool operator<(const reverse_it<Iterator>& lhs, const reverse_it<Iterator>& rhs)	{ return lhs.base() < rhs.base(); };

	template <class Iterator>
	bool operator<=(const reverse_it<Iterator>& lhs, const reverse_it<Iterator>& rhs)	{ return lhs.base() <= rhs.base(); };

	template <class Iterator>
	bool operator>(const reverse_it<Iterator>& lhs, const reverse_it<Iterator>& rhs)	{ return !(lhs.base() < rhs.base()); };

	template <class Iterator>
	bool operator>=(const reverse_it<Iterator>& lhs, const reverse_it<Iterator>& rhs)	{ return !(lhs.base() <= rhs.base()); };

	template <class Iterator>
	reverse_it<Iterator> operator+(typename reverse_it<Iterator>::difference_type n, const reverse_it<Iterator>& rev_it) {
		return reverse_it<Iterator>(rev_it.base() - n);
	};

	template<class Iterator>
	typename reverse_it<Iterator>::difference_type operator-(const reverse_it<Iterator> &lhs, const reverse_it<Iterator> &rhs) {
		return rhs.base() - lhs.base();
//		return std::distance(lhs.base(), rhs.base());
	};

	template <class T>
	bool operator==(const const_reverse_it<T>& lhs, const const_reverse_it<T>& rhs)	{ return lhs.base() == rhs.base(); };

	template <class T>
	bool operator==(const const_reverse_it<T>& lhs, const reverse_it<T>& rhs)	{ return lhs.base() == rhs.base(); };

	template <class T>
	bool operator==(const reverse_it<T>& lhs, const const_reverse_it<T>& rhs)	{ return lhs.base() == rhs.base(); };

	template <class T>
	bool operator!=(const const_reverse_it<T>& lhs, const const_reverse_it<T>& rhs)	{ return lhs.base() != rhs.base(); };

	template <class T>
	bool operator!=(const const_reverse_it<T>& lhs, const reverse_it<T>& rhs)	{ return lhs.base() != rhs.base(); };

	template <class T>
	bool operator!=(const reverse_it<T>& lhs, const const_reverse_it<T>& rhs)	{ return lhs.base() != rhs.base(); };

	template <class T>
	bool operator<(const const_reverse_it<T>& lhs, const const_reverse_it<T>& rhs)	{ return lhs.base() < rhs.base(); };

	template <class T>
	bool operator<(const const_reverse_it<T>& lhs, const reverse_it<T>& rhs)				{ return lhs.base() < rhs.base(); };

	template <class T>
	bool operator<(const reverse_it<T>& lhs, const const_reverse_it<T>& rhs)				{ return lhs.base() < rhs.base(); };

	template <class T>
	bool operator>(const const_reverse_it<T>& lhs, const const_reverse_it<T>& rhs)	{ return lhs.base() > rhs.base(); };

	template <class T>
	bool operator>(const const_reverse_it<T>& lhs, const reverse_it<T>& rhs)				{ return lhs.base() > rhs.base(); };

	template <class T>
	bool operator>(const reverse_it<T>& lhs, const const_reverse_it<T>& rhs)				{ return lhs.base() > rhs.base(); };

	template <class T>
	bool operator<=(const const_reverse_it<T>& lhs, const const_reverse_it<T>& rhs)		{ return lhs.base() <= rhs.base(); };

	template <class T>
	bool operator<=(const const_reverse_it<T>& lhs, const reverse_it<T>& rhs)				{ return lhs.base() <= rhs.base(); };

	template <class T>
	bool operator<=(const reverse_it<T>& lhs, const const_reverse_it<T>& rhs)				{ return lhs.base() <= rhs.base(); };

	template <class T>
	bool operator>=(const const_reverse_it<T>& lhs, const const_reverse_it<T>& rhs)		{ return lhs.base() >= rhs.base(); };

	template <class T>
	bool operator>=(const const_reverse_it<T>& lhs, const reverse_it<T>& rhs)				{ return lhs.base() >= rhs.base(); };

	template <class T>
	bool operator>=(const reverse_it<T>& lhs, const const_reverse_it<T>& rhs)				{ return lhs.base() >= rhs.base(); };


}

#endif //FT_VECTOR_FT_UTILS_HPP
