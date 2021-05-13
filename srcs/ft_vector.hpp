//
// Created by Gilberto Dougal on 2/26/21.
//
//#pragma once
#ifndef FT_VECTOR_VECTOR_HPP
#define FT_VECTOR_VECTOR_HPP
#include "ft_utils/ft_utils.hpp"

namespace ft {

	template <class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef		size_t																		size_type;
		typedef		Allocator																	allocator_type;
		typedef		typename Allocator::pointer								pointer;
		typedef		typename Allocator::reference							reference;
		typedef		typename Allocator::value_type						value_type;
		typedef		typename Allocator::const_pointer					const_pointer;
		typedef		typename Allocator::const_reference				const_reference;
		typedef		std::ptrdiff_t														difference_type;

		typedef		vec_util::vectorIterator<value_type>			iterator;
		typedef		vec_util::constVectorIterator<value_type>	const_iterator;
		typedef		gu::reverse_it<iterator>									reverse_iterator;
		typedef		gu::const_reverse_it<iterator>						const_reverse_iterator;

	private:
		pointer					vector_;
		size_type				capacity_;
		size_type 			size_;
		allocator_type	alloc_;

	public:
		explicit	vector(const allocator_type& alloc = allocator_type())
			: vector_(nullptr),
			capacity_(0),
			size_(0),
			alloc_(alloc)
			{};

		explicit	vector(size_type n, const value_type& val = value_type(),
													const allocator_type& alloc = allocator_type())
			: capacity_(n),
			size_(n),
			alloc_(alloc) {
			vector_ = alloc_.allocate(n);
			for (size_type i = 0; i < n; ++i) {
				alloc_.construct((vector_ + i), val);
			}
		};

								template<class InputIt>
		vector(InputIt first, InputIt last, const Allocator &alloc = Allocator(),
																					ENABLE_IF_TYPE(InputIt)) :
			vector_(0),
			capacity_(std::distance(first, last)),
			size_(std::distance(first, last)),
			alloc_(alloc) {
			fillVectorFrom(first, last, capacity_);
		}

		vector (const vector& x)
			: size_(0), capacity_ (0) {
			if (this == &x)
				return ;
			*this = x;
		}

		vector& 	operator=(const vector& x) {
			if (this == &x)
				return *this;
			clear();
//			fillVectorFrom(x.begin(), x.end(), x.capacity());
//			size_ = x.size_;
			assign(x.begin(), x.end());
//			alloc_ = x.alloc_;
			return *this;
		};

		virtual		~vector() {
			destroyElem(begin(), end());
			dealocateElem(begin(), capacity_);
		};

		void			resize(size_type n, value_type val = value_type()) {
			if (n >= size_ && n <= capacity_)
				return;
			else if (n < size_) {
				destroyElem(begin() + n, end());
				size_ = n;
			}
			else if (n > capacity_) {
				size_type tmp = size_;
				fillVectorFrom(begin(), end(), n);
				constructRange(tmp, n,  val);
			}
		};

		void			reserve (size_type n) {
			if (n <= capacity_)
				return ;
			fillVectorFrom(begin(), end(), n);
		};

		template <class InputIt>
		void			assign(InputIt first, InputIt last, ENABLE_IF_TYPE(InputIt)) {
			difference_type	diference = std::distance(first, last);
			clear();
			if (diference < capacity_) {
				constructRange(first, last, vector_);
				size_ = diference;
			}
			else {
				fillVectorFrom(first, last, diference);
			}
		};

		void			assign(size_type n, const value_type& val) {
			if (n <= capacity_) {
				destroyElem(begin(), begin() + n);
				constructRange(n, val, vector_);
			}
			else {
				fillVectorFrom(n, val, n);
			}
			size_ = n;
		};

		void			push_back(const value_type& val) {
			if (size_ ==  capacity_) {
				if (empty())
					fillVectorFrom(begin(), end(), 1);
				else
					fillVectorFrom(begin(), end(), 2 * capacity_);
				alloc_.construct((vector_ + size_), val);
			}
			else {
				alloc_.construct((vector_ + size_), val);
			}
			size_++;
		};

		void			pop_back() {
			if (!empty())
				alloc_.destroy(--size_ + vector_);
		};

		iterator	insert(iterator position, const value_type& val) {
			size_type new_pos = position - begin();
			insert_util(position, 1, val);
			return begin() + new_pos;
		};

		void			insert (iterator position, size_type n, const value_type& val) {
			insert_util(position, n, val);
		};

		template <class InputIt>
		void			insert (iterator position, InputIt first, InputIt last,
											ENABLE_IF_TYPE(InputIt)) {
			size_type n = std::distance(first, last);
			if (size_ + n < capacity_) {
				move(position + n, position, end() - position);
				iterator	finish = position + n;
				for (; first != last; ++first, ++position) {
					alloc_.construct((position.operator->()), *first);
				}
				size_ += n;
				return ;
			}
			difference_type	len = position - begin();
			fillVectorFrom(vector_, vector_ + size_, (capacity_ + n) * 2);
			iterator new_pos((begin() + len).operator->());
			insert(new_pos, first, last);
		};

		iterator	erase (iterator position) {
			size_type new_pos = position - begin();
			move(position, position + 1, 0);
			--size_;
			return begin() + new_pos;
		};

		iterator	erase (iterator first, iterator last) {
			size_type new_pos = first - begin();
			size_type	len = last - first;
			move(first, last, 0);
			size_ -= len;
			return begin() + new_pos;
		};

		void			swap (vector& x) {
			gu::f_swp(vector_, x.vector_);
			gu::f_swp(size_, x.size_);
			gu::f_swp(capacity_, x.capacity_);
			gu::f_swp(alloc_, x.alloc_);
		};

		void			clear() {
			destroyElem(begin(), end());
			size_ = 0;
		};

		const_reference	at(size_type n)	const {
			if (n < 0 || n > size_)
				throw std::out_of_range("Out of range.");
			else
				return (vector_[n]);
		};

		reference				at(size_type n) {
			if (n < 0 || n >= size_)
				throw std::out_of_range("Out of range.");
			else
				return (vector_[n]);
		};

		reverse_iterator				rbegin()											{ return reverse_iterator(end()); };
		const_reverse_iterator	rbegin()								const	{ return const_reverse_iterator(end()); };
		reverse_iterator				rend()												{ return reverse_iterator(begin()); };
		const_reverse_iterator	rend()									const	{ return const_reverse_iterator(begin()); };
		iterator								begin()												{ return iterator(vector_); };
		iterator								end()													{ return iterator((vector_ + size_)); };
		const_iterator					begin()									const	{ return const_iterator(vector_); };
		const_iterator					end()										const { return const_iterator(vector_ + size_); };
		size_type								size()									const	{ return size_; };
		size_type								capacity()							const	{ return capacity_;};
		size_type								max_size()							const	{ return (UINT64_MAX)/(sizeof(value_type) == 1 ? 2 : sizeof(value_type)); };
		bool										empty()									const	{ return size_ == 0; };
		reference								operator[](size_type n)				{ return (vector_[n]); };
		reference								front()												{ return *vector_; };
		reference								back()												{ return *(vector_ + size_ - 1); };
		const_reference					operator[](size_type n)	const	{ return (vector_[n]); };
		const_reference					front()									const	{ return *vector_; };
		const_reference					back()									const	{ return *(vector_ + size_ - 1); };

	private:
		template<class InputIt>
		inline void			destroyElem(InputIt start, InputIt end) {
			difference_type n = 0;
			for (; start + n != end && n < size_; ++n) {
				alloc_.destroy((start + n).operator->());
			}
		}

		template<class InputIt>
		inline void			dealocateElem(InputIt start, size_type n) {
			alloc_.deallocate(start.operator->(), n);
		}

		inline void			constructRange(size_type n, size_type capacity, const value_type& val) {
			for (; n != capacity; ++n) {
				alloc_.construct((vector_ + n), val);
				++size_;
			}
		}

		inline void			constructRange(size_type n, const value_type& val, pointer& buf) {
			size_type cur = 0;
			for (; cur != n; ++cur) {
				alloc_.construct((buf + cur), val);
				++size_;
			}
		}

		template<class InputIt>
		inline void			constructRange(InputIt first, InputIt last, pointer& buf, ENABLE_IF_TYPE(InputIt)) {
			size_type cur = 0;
			for (; first != last; ++first, ++cur) {
				alloc_.construct((buf + cur), *first);
				++size_;
			}
		}

		template<typename Tfill1, typename Tfill2>
		inline void	fillVectorFrom(Tfill1 first_orSize, Tfill2 last_orVal, size_type capacity) {
			size_ = 0;
			pointer buf = alloc_.allocate(capacity);
			constructRange(first_orSize, last_orVal, buf);
			if (size_ && capacity_ && capacity_ != capacity) {
				destroyElem(begin(), end());
				dealocateElem(begin(), capacity_);
			}
			capacity_ = capacity;
			vector_ = buf;
		}

		inline void	move(iterator dest, iterator src, size_type n) {
			if (dest > src) {
				for (; n >= 0 && n != UINT64_MAX; --n) {
					alloc_.construct((dest + n).operator->(), *(src + n));
					if (!empty())
						alloc_.destroy((src + n).operator->());
				}
			}
			else {
				for (; dest + n != end(); ++n) {
					if (!empty())
						alloc_.destroy((dest + n).operator->());
					alloc_.construct((dest + n).operator->(), *(src + n));
				}
			}
		}

		inline void			insert_util(iterator position, size_type n, const value_type& val) {
			if (size_ + n < capacity_) {
				move(position + n, position, end() - position);
				iterator	finish = position + n;
				for (; position != finish; ++position) {
					alloc_.construct((position.operator->()), val);
				}
				size_ += n;
				return ;
			}
			difference_type	len = position - begin();
			fillVectorFrom(vector_, vector_ + size_, (capacity_ + n) * 2);
			iterator new_pos((begin() + len).operator->());
			insert(new_pos, n, val);
		};
	};

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() == rhs.size()) {
			return std::equal(lhs.begin(), lhs.end(), rhs.begin());
		}
		return false;
	};

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(ft::operator==(lhs, rhs)));
	};

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	};

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(ft::operator>(lhs, rhs)));
	};

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(ft::operator<(lhs, rhs)));
	};

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	};

}

#endif //FT_VECTOR_VECTOR_HPP