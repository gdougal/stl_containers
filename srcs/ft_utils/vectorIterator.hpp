//
// Created by Gilberto Dougal on 3/15/21.
//
#pragma once
//#include <iterator>


//#ifndef FT_VECTOR_VECTORITERATOR_HPP
//#define FT_VECTOR_VECTORITERATOR_HPP

namespace vec_util {

	template<typename T>
	class constVectorIterator;

	template<typename T>
	class vectorIterator {
	public:
		typedef		T																value_type;
		typedef		std::ptrdiff_t									difference_type;
		typedef		value_type*											pointer;
		typedef		value_type&											reference;
		typedef		std::random_access_iterator_tag	iterator_category;
		typedef		constVectorIterator<value_type>	constIterator;
	private:
		pointer		pointer_;

	public:
		explicit					vectorIterator(pointer reference)
			: pointer_(reference) {};
											vectorIterator(): pointer_(nullptr) {};
											vectorIterator(const constIterator& ref) {
			*this = ref;
		};
											vectorIterator(const vectorIterator& ref) {
			*this = ref;
		};
		virtual 					~vectorIterator() {};

		vectorIterator&		operator=(const vectorIterator& ref) {
			if(this == &ref) {
				return *this;
			}
			pointer_ = ref.getPointer();
			return *this;
		};

		vectorIterator&		operator=(const constIterator& ref) {
			if(this == &ref) {
				return *this;
			}
			pointer_ = ref.getPointer();
			return *this;
		};

		reference					operator*()																	{ return *pointer_; }
		pointer						operator->() const													{ return pointer_; }
		vectorIterator&		operator+=(difference_type n)								{ return *this = operator+(n); }
		vectorIterator&		operator-=(difference_type n)								{ return *this = operator-(n); }
		reference					operator[](difference_type n)								{ return *(pointer_ + n); }
		bool							operator!=(vectorIterator const& right)			{ return pointer_ != right.pointer_; }
		bool							operator==(vectorIterator const& right)			{ return pointer_ == right.pointer_; }
		difference_type		operator-(vectorIterator b)									{ return pointer_ - b.pointer_; }
		bool							operator<(vectorIterator const& reference)	{ return pointer_ < reference.pointer_; }
		bool							operator>(vectorIterator const& reference)	{ return pointer_ > reference.pointer_; }
		bool							operator<=(vectorIterator const& reference)	{ return pointer_ <= reference.pointer_;}
		bool							operator>=(vectorIterator const& reference)	{ return pointer_ >= reference.pointer_; }

		bool							operator!=(constIterator const& right)			{ return pointer_ != right.pointer_; }
		bool							operator==(constIterator const& right)			{ return pointer_ == right.pointer_; }
		difference_type		operator-(constIterator b)									{ return pointer_ - b.pointer_; }
		bool							operator<(constIterator const& reference)		{ return pointer_ < reference.pointer_; }
		bool							operator>(constIterator const& reference)		{ return pointer_ > reference.pointer_; }
		bool							operator<=(constIterator const& reference)	{ return pointer_ <= reference.pointer_;}
		bool							operator>=(constIterator const& reference)	{ return pointer_ >= reference.pointer_; }

		vectorIterator&			operator++() {
			++pointer_;
			return *this;
		}

		vectorIterator			operator++(int) {
			vectorIterator	ret(*this);
			this->operator++();
			return ret;
		}

		vectorIterator&			operator--() { --pointer_;
			return *this;
		}

		vectorIterator			operator--(int) {
			vectorIterator	ret(*this);
			this->operator--();
			return ret;
		}

		vectorIterator			operator+(difference_type n) {
			vectorIterator it(pointer_ + n);
			return it;
		}

		vectorIterator			operator-(difference_type n) {
			vectorIterator it(pointer_ - n);
			return it;
		}

		const pointer getPointer() const {
			return pointer_;
		}
	};

	template<typename T>
	class constVectorIterator {
	public:
		typedef		T																value_type;
		typedef		std::ptrdiff_t									difference_type;
		typedef		value_type*											pointer;
		typedef		value_type&											reference;
		typedef		std::random_access_iterator_tag	iterator_category;
		typedef		vectorIterator<value_type>			nonConstIterator;
	private:
		pointer		pointer_;

	public:
														constVectorIterator(): pointer_(nullptr) {};
		explicit								constVectorIterator(value_type* reference)
			: pointer_(reference) {};
														constVectorIterator(const nonConstIterator& ref) {
			*this = ref;
		};
														constVectorIterator(const constVectorIterator& ref) {
			*this = ref;
		};

		virtual									~constVectorIterator() {};

		constVectorIterator&		operator=(const constVectorIterator& ref) {
			if(this == &ref) {
				return *this;
			}
			pointer_ = ref.getPointer();
			return *this;
		};

		constVectorIterator&		operator=(const nonConstIterator& ref) {
			if(*this == ref) {
				return *this;
			}
			pointer_ = ref.getPointer();
			return *this;
		};

		const value_type			operator*()																				{ return *pointer_; }
		const pointer					operator->()																			{ return pointer_; }
		constVectorIterator		operator+=(difference_type n)											{ return this->operator+(n); }
		constVectorIterator		operator-=(difference_type n)											{ return this->operator-(n); }
		reference							operator[](difference_type n)											{ return *(pointer_ + n); }
		bool									operator==(constVectorIterator const& right)			{ return pointer_ == right.pointer_; }
		bool									operator!=(constVectorIterator const& right)			{ return pointer_ != right.pointer_; }
		difference_type				operator-(constVectorIterator b)									{ return pointer_ - b.pointer_; }
		bool									operator<(constVectorIterator const& reference)		{ return pointer_ < reference.pointer_; }
		bool									operator>(constVectorIterator const& reference)		{ return pointer_ > reference.pointer_; }
		bool									operator<=(constVectorIterator const& reference)	{ return pointer_ <= reference.pointer_;}
		bool									operator>=(constVectorIterator const& reference)	{ return pointer_ >= reference.pointer_; }

		bool									operator==(nonConstIterator const& right)					{ return pointer_ == right.getPointer(); }
		bool									operator!=(nonConstIterator const& right)					{ return pointer_ != right.getPointer(); }
		difference_type				operator-(nonConstIterator b)											{ return pointer_ - b.getPointer(); }
		bool									operator<(nonConstIterator const& reference)			{ return pointer_ < reference.getPointer(); }
		bool									operator>(nonConstIterator const& reference)			{ return pointer_ > reference.getPointer(); }
		bool									operator<=(nonConstIterator const& reference)			{ return pointer_ <= reference.getPointer();}
		bool									operator>=(nonConstIterator const& reference)			{ return pointer_ >= reference.getPointer(); }

		constVectorIterator&	operator++() {
			++pointer_;
			return *this;
		}

		constVectorIterator		operator++(int) {
			constVectorIterator	ret(*this);
			this->operator++();
			return ret;
		}

		constVectorIterator&			operator--() { --pointer_;
			return *this;
		}

		constVectorIterator			operator--(int) {
			constVectorIterator	ret(*this);
			this->operator--();
			return ret;
		}

		constVectorIterator			operator+(difference_type n) {
			constVectorIterator it(pointer_ + n);
			return it;
		}

		constVectorIterator			operator-(difference_type n) {
			constVectorIterator it(pointer_ - n);
			return it;
		}

		const pointer getPointer() const {
			return pointer_;
		}

	};

	template <class T>
	bool operator==(const vectorIterator<T>& lhs, const vectorIterator<T>& rhs)	{ return lhs == rhs; };

	template <class T>
	bool operator!=(const vectorIterator<T>& lhs, const vectorIterator<T>& rhs)	{ return !(lhs == rhs); };

	template <class T>
	bool operator<(const vectorIterator<T>& lhs, const vectorIterator<T>& rhs)	{ return lhs < rhs; };

	template <class T>
	bool operator<=(const vectorIterator<T>& lhs, const vectorIterator<T>& rhs)	{ return lhs <= rhs; };

	template <class T>
	bool operator>(const vectorIterator<T>& lhs, const vectorIterator<T>& rhs)	{ return !(lhs < rhs); };

	template <class T>
	bool operator>=(const vectorIterator<T>& lhs, const vectorIterator<T>& rhs)	{ return !(lhs <= rhs); };

	template <class T>
	bool operator==(const constVectorIterator<T> lhs, const constVectorIterator<T> rhs)	{ return lhs == rhs; };

	template <class T>
	bool operator!=(const constVectorIterator<T> lhs, const constVectorIterator<T> rhs)	{ return !(lhs == rhs); };

	template <class T>
	bool operator<(const constVectorIterator<T> lhs, const constVectorIterator<T> rhs)	{ return lhs < rhs; };

	template <class T>
	bool operator<=(const constVectorIterator<T> lhs, const constVectorIterator<T> rhs)	{ return lhs <= rhs; };

	template <class T>
	bool operator>(const constVectorIterator<T> lhs, const constVectorIterator<T> rhs)	{ return !(lhs < rhs); };

	template <class T>
	bool operator>=(const constVectorIterator<T> lhs, const constVectorIterator<T> rhs)	{ return !(lhs <= rhs); };

	template <class T>
	bool operator==(const constVectorIterator<T> lhs, const vectorIterator<T> rhs)	{ return lhs == rhs; };

	template <class T>
	bool operator!=(const constVectorIterator<T> lhs, const vectorIterator<T> rhs)	{ return !(lhs == rhs); };

	template <class T>
	bool operator<(const constVectorIterator<T> lhs, const vectorIterator<T> rhs)	{ return lhs < rhs; };

	template <class T>
	bool operator<=(const constVectorIterator<T> lhs, const vectorIterator<T> rhs)	{ return lhs <= rhs; };

	template <class T>
	bool operator>(const constVectorIterator<T> lhs, const vectorIterator<T> rhs)	{ return !(lhs < rhs); };

	template <class T>
	bool operator>=(const constVectorIterator<T> lhs, const vectorIterator<T> rhs)	{ return !(lhs <= rhs); };


	template <class T>
	bool operator==(const vectorIterator<T> lhs, const constVectorIterator<T> rhs)	{ return lhs == rhs; };

	template <class T>
	bool operator!=(const vectorIterator<T> lhs, const constVectorIterator<T> rhs)	{ return !(lhs == rhs); };

	template <class T>
	bool operator<(const vectorIterator<T> lhs, const constVectorIterator<T> rhs)	{ return lhs < rhs; };

	template <class T>
	bool operator<=(const vectorIterator<T> lhs, const constVectorIterator<T> rhs)	{ return lhs <= rhs; };

	template <class T>
	bool operator>(const vectorIterator<T> lhs, const constVectorIterator<T> rhs)	{ return !(lhs < rhs); };

	template <class T>
	bool operator>=(const vectorIterator<T> lhs, const constVectorIterator<T> rhs)	{ return !(lhs <= rhs); };

}

//#endif //FT_VECTOR_VECTORITERATOR_HPP
