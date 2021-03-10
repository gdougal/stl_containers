//
// Created by Gilberto Dougal on 2/26/21.
//

#ifndef FT_VECTOR_VECTOR_HPP
#define FT_VECTOR_VECTOR_HPP
#include <memory>
#include <iterator>

//	reallocate memory	: new_el + size/10 * ln(size) + size
//	allocate memory		: new_el + new_el/10 * ln(new_el)


namespace ft {

//	struct false_type {
////		char c;
//		const static bool value = false;
//	};
//
//	struct true_type {
////		false_type f[2];
//		const static bool value = true;
//	};

	template<class T, class U>
	struct is_same {
		const static bool value = false;
	};

	template<class T>
	struct is_same<T, T> {
		const static bool value = true;
	};

	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>
	{ typedef T type; };

	template <class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		class vectorIterator;
		typedef		T																		value_type;
		typedef		Allocator														allocator_type;
		typedef		typename Allocator::reference				reference;
		typedef		typename Allocator::const_reference	const_reference;
		typedef		typename Allocator::pointer					pointer;
		typedef		typename Allocator::const_pointer		const_pointer;
		typedef		size_t															size_type;
		typedef		std::ptrdiff_t											difference_type;
		typedef		vectorIterator											iterator;

	private:
		pointer			vector_;
		size_type				capacity_;
		size_type 			size_;
		allocator_type	alloc_ ;

		template<class InputIterator>
		void	destroyElem(InputIterator start, pointer end) {
			size_type n = 0;
			for (; start + n != end && n < size_; ++n) {
				alloc_.destroy(start + n);
			}
			size_ -= n;
		}

		template<class InputIterator>
		void	dealocateElem(InputIterator start, size_type n) {
			alloc_.deallocate(start, n);
		}

		void	constructRange(size_type n, const value_type& val, pointer& buf) {
			size_type cur = 0;
			for (; cur != n; ++cur) {
				alloc_.construct((buf + cur), val);
			}
			size_ = cur;
		}

		template<class InputIterator>
		void	constructRange(InputIterator first, InputIterator last, pointer& buf,
			typename ft::enable_if<ft::is_same<InputIterator, pointer>::value, value_type>::type i = 0) {
			size_type cur = 0;
			for (; first != last; ++first, ++cur) {
				alloc_.construct((buf + cur), *first);
			}
			size_ = cur;
		}

		template<typename Tfill1, typename Tfill2>
		pointer		fillVectorFrom(Tfill1 first, Tfill2 last, size_type capacity) {
			pointer buf = alloc_.allocate(capacity);
			constructRange(first, last, buf);
			capacity_ = capacity;
			return buf;
		}
	public:
//------------------------RANDOM ACCESS ITERATOR CLASS------------------------//
		class vectorIterator {
		public:
			typedef		value_type											iterator_type;
			typedef		std::random_access_iterator_tag	iterator_category;
			typedef		iterator_type										value_type;
			typedef		iterator_type&									reference;
			typedef		iterator_type*									pointer;
			typedef		std::ptrdiff_t									difference_type;
		private:
			pointer		pointer_;
		public:
											vectorIterator(): pointer_(nullptr) {};
			explicit				vectorIterator(iterator_type& reference)
			: pointer_(&reference) {};
			vectorIterator&	operator=(iterator_type& reference) {
				if(this->pointer_ == &reference) {
					return *this;
				}
				pointer_ = &reference;
				return *this;
			};
			virtual ~vectorIterator() {};

			bool						operator==(iterator const& right) {
				if (this->pointer_ == right.pointer_) {
					return true;
				}
				else {
					return false;
				}
			}
			bool						operator!=(iterator const& right) {
				if (pointer_ == right.pointer_) {
					return false;
				}
				else {
					return true;
				}
			}

			iterator_type&			operator*() {
				return *pointer_;} // NON CONSTANT/MUTABLE ITERATOR ? (lvalue)
			//																																										a->m
			/// I rly need it ? (operator "->")
//			pointer  operator->() const {return &(operator*());}

			iterator&				operator++() {
				++pointer_;
				return *this;
			}

			iterator				operator++(int) {
				iterator	ret(*this);
				this->operator++();
				return ret;
			}

			iterator&				operator--() {
				--pointer_;
				return *this;
			}

			iterator				operator--(int) {
				iterator	ret(*this);
				this->operator--();
				return ret;
			}

			iterator&			operator+(difference_type n) {
				this->pointer_ = this->pointer_ + n;
				return *this;
			}

			iterator			operator-(difference_type n) {
				this->pointer_ = this->pointer_ - n;
				return *this;
			}

			bool					operator<(iterator const& reference) {
				if (pointer_ < reference.pointer_) {
					return true;
				}
				else {
					return false;
				}
			}

			bool					operator>(iterator const& reference) {
				if (pointer_ > reference.pointer_) {
					return true;
				}
				else {
					return false;
				}
			}

			bool					operator<=(iterator const& reference) {
				if (pointer_ <= reference.pointer_) {
					return true;
				}
				else {
					return false;
				}
			}

			bool				operator>=(iterator const& reference) {
				if (pointer_ >= reference.pointer_) {
					return true;
				}
				else {
					return false;
				}
			}

			iterator		operator+=(difference_type n) {
				return this->operator+(n);
			}

			iterator&		operator-=(difference_type n) {
				return this->operator-(n);
			}

			iterator&		operator[](difference_type n) {
				return (*(this->pointer_));
			}
		};
//const_iterator	LegacyRandomAccessIterator to const value_type
//reverse_iterator	std::reverse_iterator<iterator>
//const_reverse_iterator	std::reverse_iterator<const_iterator>


		explicit vector (const allocator_type& alloc = allocator_type())
							: vector_(nullptr), capacity_(0), size_(0) {};

		explicit vector (size_type n, const value_type& val = value_type(),
													const allocator_type& alloc = allocator_type())
			: capacity_(n), size_(n) {
			vector_ = alloc_.allocate(n);
			for (size_type i = 0; i < n; ++i) {
				alloc_.construct((vector_ + i), val);
			}
		};

		template<class InputIt>
		vector(InputIt first, InputIt last, const Allocator &alloc = Allocator(),
				typename ft::enable_if<ft::is_same<InputIt, pointer>::value, value_type>::type i = 0)
				: size_(last - first), capacity_(last - first) {
			vector_ = fillVectorFrom(first, last, capacity_);
		}

//		vector (const vector& x)
//		{
//			// Copy allocator? what is copy for container???????/
//		}
		virtual					~vector() {
			destroyElem(vector_, vector_ + size_);
			dealocateElem(vector_, capacity_);
		};

//		vector& operator=(const vector& x) {
//
//		};

		void					resize(size_type n, value_type val = value_type()) {
			if (n >= size_ && n <= capacity_)
				return;
			else if (n < size_) {
				destroyElem(vector_ + n, vector_ + size_);
				size_ = n;
			}
			else if (n > capacity_) {
				pointer buf = fillVectorFrom(begin(), end(), n);
				destroyElem(vector_, vector_ + size_);
				dealocateElem(vector_, capacity_);
				vector_ = buf;
			}
		};

		void reserve (size_type n) {
			if (n <= capacity_)
				return ;
			pointer buf = fillVectorFrom(begin(), end(), n);
			destroyElem(vector_, vector_ + size_);
			dealocateElem(vector_, capacity_);
			vector_ = buf;
		};

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<ft::is_same<InputIterator, pointer>::value, value_type>::type i = 0) {
			difference_type	diference = last - first;
			if (diference < capacity_) {
				destroyElem(vector_, vector_ + diference);
				constructRange(first, last, vector_);
			}
			else {
				destroyElem(vector_, vector_ + size_);
				dealocateElem(vector_, capacity_);
				vector_ = fillVectorFrom(first, last, diference);
			}
		};

		void assign (size_type n, const value_type& val) {
			if (n < capacity_) {
				destroyElem(vector_, vector_ + n);
				constructRange(n, val, vector_);
			}
			else {
				destroyElem(vector_, vector_ + size_);
				dealocateElem(vector_, capacity_);
				vector_ = fillVectorFrom(n, val, n);
			}
		};


		iterator				begin() {
			iterator first(*vector_);
			return first;
		};

		iterator				end() {
			iterator last(*(vector_ + size_));
			return last;
		};

		const iterator	begin() const {
			const iterator first(*vector_);
			return first;
		};

		const iterator	end() const {
			const iterator last(*(vector_ + size_));
			return last;
		};

		size_type	size() const {
			return size_;
		};

		size_type capacity() const {
			return capacity_;
		};

		size_type			max_size() const {
			return (UINT64_MAX)/(sizeof(value_type) == 1 ? 2 : sizeof(value_type));
		};

		bool empty() const {
			return size_ == 0;
		};

		reference operator[] (size_type n) {
			return (vector_[n]);
		};

		const_reference operator[] (size_type n) const {
			return (vector_[n]);
		};

		reference at (size_type n) {
			if (n < 0 || n > size_)
				throw std::out_of_range("Out of range.");
			else
				return (vector_[n]);
		};

		const_reference at (size_type n) const {
			if (n < 0 || n > size_)
				throw std::out_of_range("Out of range.");
			else
				return (vector_[n]);
		};

		reference front() {
			return *vector_;
		};

		const_reference front() const {
			return *vector_;
		};

		reference back() {
			return *(vector_ + size_ - 1);
		};

		const_reference back() const {
			*(vector_ + size_ - 1);
		};
	};
}

#endif //FT_VECTOR_VECTOR_HPP