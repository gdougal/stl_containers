//
// Created by Gilberto Dougal on 3/15/21.
//

#ifndef FT_VECTOR_VECTORITERATOR_HPP
#define FT_VECTOR_VECTORITERATOR_HPP

namespace ft {

	template<typename Val_T>
	class vectorIterator {
	public:
		typedef		Val_T														value_type;
		typedef		std::ptrdiff_t									difference_type;
		typedef		value_type*											pointer;
		typedef		value_type&											reference;
		typedef		std::random_access_iterator_tag	iterator_category;
	private:
		pointer		pointer_;
	public:
											vectorIterator(): pointer_(nullptr) {};
		explicit					vectorIterator(pointer reference)
						: pointer_(reference) {};
		virtual ~vectorIterator() {};

		vectorIterator&		operator=(vectorIterator reference) {
			if(this == &reference) {
				return *this;
			}
			pointer_ = reference.pointer_;
			return *this;
		};

		bool							operator==(vectorIterator const& right)			{ return pointer_ == right.pointer_; }
		bool							operator!=(vectorIterator const& right)			{ return pointer_ != right.pointer_; }
		value_type&				operator*()																	{ return *pointer_; }
		pointer						operator->() const													{ return pointer_; }
		difference_type		operator-(vectorIterator b)									{ return pointer_ - b.pointer_; }
		bool							operator<(vectorIterator const& reference)	{ return pointer_ < reference.pointer_; }
		bool							operator>(vectorIterator const& reference)	{ return pointer_ > reference.pointer_; }
		bool							operator<=(vectorIterator const& reference)	{ return pointer_ <= reference.pointer_;}
		bool							operator>=(vectorIterator const& reference)	{ return pointer_ >= reference.pointer_; }
		vectorIterator		operator+=(difference_type n)								{ return this->operator+(n); }
		vectorIterator&		operator-=(difference_type n)								{ return this->operator-(n); }
		vectorIterator&		operator[](difference_type n)								{ return (pointer_ + n); }

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
	};

	template<typename Val_T>
	class constVectorIterator {
	public:
		typedef		const Val_T											value_type;
		typedef		std::ptrdiff_t									difference_type;
		typedef		value_type*											pointer;
		typedef		value_type&											reference;
		typedef		std::random_access_iterator_tag	iterator_category;
	private:
		pointer		pointer_;
	public:
		constVectorIterator(): pointer_(nullptr) {};
		explicit					constVectorIterator(pointer reference)
						: pointer_(reference) {};
		virtual ~constVectorIterator() {};

		constVectorIterator&		operator=(constVectorIterator reference) {
			if(this == &reference) {
				return *this;
			}
			pointer_ = reference.pointer_;
			return *this;
		};

		bool									operator==(constVectorIterator const& right)			{ return pointer_ == right.pointer_; }
		bool									operator!=(constVectorIterator const& right)			{ return pointer_ != right.pointer_; }
		value_type&						operator*()																				{ return *pointer_; }
		pointer								operator->() const																{ return pointer_; }
		difference_type				operator-(constVectorIterator b)									{ return pointer_ - b.pointer_; }
		bool									operator<(constVectorIterator const& reference)		{ return pointer_ < reference.pointer_; }
		bool									operator>(constVectorIterator const& reference)		{ return pointer_ > reference.pointer_; }
		bool									operator<=(constVectorIterator const& reference)	{ return pointer_ <= reference.pointer_;}
		bool									operator>=(constVectorIterator const& reference)	{ return pointer_ >= reference.pointer_; }
		constVectorIterator		operator+=(difference_type n)											{ return this->operator+(n); }
		constVectorIterator&	operator-=(difference_type n)											{ return this->operator-(n); }
		constVectorIterator&	operator[](difference_type n)											{ return (pointer_ + n); }

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
	};
}

#endif //FT_VECTOR_VECTORITERATOR_HPP
