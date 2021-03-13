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

	template<class U>
	struct is_same {
	private:
		template<typename T1>
		static char	lol(T1* a) {return 0;};
		template<typename T1>
		static int	lol(T1) {return 0;};
	public:
		const static bool value = sizeof(lol<U>(0)) == sizeof(char);
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
//			size_ -= n;
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
//			size_ = cur;
		}

		template<class InputIt>
		void	constructRange(InputIt first, InputIt last, pointer& buf,
			typename ft::enable_if<ft::is_same<InputIt>::value, InputIt>::type* = 0) {
			size_type cur = 0;
			for (; first != last; ++first, ++cur) {
				alloc_.construct((buf + cur), *first);
			}
//			size_ = cur;
		}

//		template<class InputIt>
//		void	constructRange(size_type n, InputIt new_last) {
//			iterator	last = end() - 1;
//			for (size_type i = 0; n != 0 ; --last, ++i, --n) {
//				if (i) {
//					alloc_.destroy(last.operator->() + 1);
//				}
//				alloc_.construct(new_last, *last);
//			}
//			alloc_.destroy(last.operator->() + 1);
//		}

		template<typename Tfill1, typename Tfill2>
		void		fillVectorFrom(Tfill1 first, Tfill2 last, size_type capacity) {
			pointer buf = alloc_.allocate(capacity);
			constructRange(first, last, buf);
			if (capacity_ != capacity) {
				destroyElem(vector_, vector_ + size_);
				dealocateElem(vector_, capacity_);
				capacity_ = capacity;
			}
			vector_ = buf;
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
			explicit				vectorIterator(pointer reference)
			: pointer_(reference) {};
			vectorIterator&	operator=(pointer reference) {
				if(this->pointer_ == reference) {
					return *this;
				}
				pointer_ = reference;
				return *this;
			};
			virtual ~vectorIterator() {};

			bool						operator==(iterator const& right) {
			return pointer_ == right.pointer_;
			}
			bool						operator!=(iterator const& right) {
				return pointer_ != right.pointer_;
			}

			iterator_type&			operator*() {
				return *pointer_;} // NON CONSTANT/MUTABLE ITERATOR ? (lvalue)
			//																																										a->m
			/// I rly need it ? (operator "->")
			pointer  operator->() const {return pointer_;}

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

			iterator			operator+(difference_type n) {
				iterator it(pointer_ + n);
				return it;
			}

			iterator			operator-(difference_type n) {
				iterator it(pointer_ - n);
				return it;
			}

			difference_type	operator-(iterator b) {
				return pointer_ - b.pointer_;
			}

			bool					operator<(iterator const& reference) {
					return pointer_ < reference.pointer_;
			}

			bool					operator>(iterator const& reference) {
				return	pointer_ > reference.pointer_;
			}

			bool					operator<=(iterator const& reference) {
				return pointer_ <= reference.pointer_;
			}

			bool				operator>=(iterator const& reference) {
				return pointer_ >= reference.pointer_;
			}

			iterator		operator+=(difference_type n) {
				return this->operator+(n);
			}

			iterator&		operator-=(difference_type n) {
				return this->operator-(n);
			}

			iterator&		operator[](difference_type n) {
				return (pointer_ + n);
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
				typename ft::enable_if<ft::is_same<InputIt>::value, InputIt>::type* = 0)
				: size_(std::distance(first, last)), capacity_(std::distance(first, last)), vector_(0) {
			fillVectorFrom(first, last, capacity_);
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
				fillVectorFrom(begin(), end(), n);
			}
		};

		void reserve (size_type n) {
			if (n <= capacity_)
				return ;
			fillVectorFrom(begin(), end(), n);
		};

		template <class InputIt>
		void assign (InputIt first, InputIt last,
				typename ft::enable_if<ft::is_same<InputIt>::value, InputIt>::type* = 0) {
			difference_type	diference = std::distance(first, last);
			destroyElem(vector_, vector_ + size_);
			if (diference < capacity_) {
				constructRange(first, last, vector_);
			}
			else {
//				dealocateElem(vector_, capacity_);
				fillVectorFrom(first, last, diference);
			}
		};

		void assign (size_type n, const value_type& val) {
			if (n <= capacity_) {
				destroyElem(vector_, vector_ + n);
				constructRange(n, val, vector_);
			}
			else {
				fillVectorFrom(n, val, n);
			}
		};

		void push_back (const value_type& val) {
			if (size_ ==  capacity_) {
				fillVectorFrom(begin().operator->(), end().operator->(), 2 * capacity_);
				alloc_.construct((vector_ + size_), val);
			}
			else {
				alloc_.construct((vector_ + size_), val);
			}
			size_++;
		};

		void pop_back() {
			alloc_.destroy(--size_ + vector_);
		};

		void	ft_memmove(iterator dest, iterator src, size_type n)
		{
			while (n >= 0 && n != UINT64_MAX)
			{
				alloc_.construct((dest + n).operator->(), *(src + n));
				alloc_.destroy((src + n).operator->());
				n--;
			}
		}

		iterator	insert(iterator position, const value_type& val) {
			if (size_ + 1 < capacity_) {
				ft_memmove(position + 1, position, end() - position);
				alloc_.construct((position.operator->()), val);
				++size_;
				return position;
			}
			difference_type	len = position - begin();
			fillVectorFrom(begin(), end(), capacity_ * 2);
			iterator new_pos(vector_ + len);
			return (insert(new_pos, val));
		};

		void insert (iterator position, size_type n, const value_type& val) {
			if (size_ + n < capacity_) {
				ft_memmove(position + n, position, end() - position);
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
//		fill (2)
//		void insert (iterator position, size_type n, const value_type& val);
//		range (3)
//		template <class InputIterator>
//		void insert (iterator position, InputIterator first, InputIterator last);



		iterator				begin() {
			iterator first(vector_);
			return first;
		};

		iterator				end() {
			iterator last((vector_ + size_));
			return last;
		};

		const iterator	begin() const {
			const iterator first(vector_);
			return first;
		};

		const iterator	end() const {
			const iterator last((vector_ + size_));
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