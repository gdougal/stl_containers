//
// Created by Gilberto Dougal on 3/19/21.
//

#ifndef FT_LIST_LISTITERATOR_HPP
#define FT_LIST_LISTITERATOR_HPP
#include <iterator>

namespace ft {

	template<typename T, typename T_node>
	class constListIterator;

	template<typename T, typename T_node>
	class listIterator {
		typedef		T_node													node_type;
		typedef		T_node*													node_pointer;
		typedef		T_node&													node_referense;
	public:
		typedef		T																					value_type;
		typedef		std::ptrdiff_t														difference_type;
		typedef		value_type*																pointer;
		typedef		value_type&																reference;
		typedef		std::bidirectional_iterator_tag						iterator_category;
		typedef		constListIterator<value_type, node_type>	constIterator;
	private:
		node_pointer		pointer_;

	public:
		listIterator(): pointer_(nullptr) {};

		explicit					listIterator(node_pointer reference)
						: pointer_(reference) {};
		listIterator(const listIterator& ref) {
			*this = ref;
		};
		virtual 					~listIterator() {};

		listIterator&		operator=(const listIterator& ref) {
			if(this == &ref) {
				return *this;
			}
			pointer_ = ref.getPointer();
			return *this;
		};

		reference					operator*()																{ return *(pointer_->val); }
		pointer						operator->() const												{ return pointer_->val; }
		bool							operator!=(listIterator const& right)			{ return pointer_ != right.pointer_; }
		bool							operator==(listIterator const& right)			{ return pointer_ == right.pointer_; }

		bool							operator!=(constIterator const& right)		{ return pointer_ != right.pointer_; }
		bool							operator==(constIterator const& right)		{ return pointer_ == right.pointer_; }

		listIterator&			operator++() {
			pointer_ = pointer_->next;
			return *this;
		}

		listIterator			operator++(int) {
			listIterator	ret(pointer_);
			this->operator++();
			return ret;
		}

		listIterator&			operator--() {
			pointer_ = pointer_->prev;
			return *this;
		}

		listIterator			operator--(int) {
			listIterator	ret(pointer_);
			this->operator--();
			return ret;
		}

		const node_pointer getPointer() const {
			return pointer_;
		}
	};

	template<typename T, typename T_node>
	class constListIterator {
		typedef		T_node															node_type;
		typedef		T_node*															node_pointer;
		typedef		T_node&															node_referense;
	public:
		typedef		T																		value_type;
		typedef		std::ptrdiff_t											difference_type;
		typedef		value_type*													pointer;
		typedef		value_type&													reference;
		typedef		std::bidirectional_iterator_tag			iterator_category;
		typedef		listIterator<value_type, node_type>	nonConstIterator;
	private:
		node_pointer		pointer_;

		explicit					constListIterator(node_pointer ref)
						: pointer_(ref) {};
	public:
		constListIterator(): pointer_(nullptr) {};
		constListIterator(const nonConstIterator& ref) {
			*this = ref;
		};
		constListIterator(const constListIterator& ref) {
			*this = ref;
		};

		virtual									~constListIterator() {};

		constListIterator&		operator=(const constListIterator& ref) {
			if(this == &ref) {
				return *this;
			}
			pointer_ = ref.getPointer();
			return *this;
		};

		constListIterator&		operator=(const nonConstIterator& ref) {
			if(this == &ref) {
				return *this;
			}
			pointer_ = ref.getPointer();
			return *this;
		};

		const value_type			operator*()																			{ return *(pointer_->val); }
		const pointer					operator->()																		{ return pointer_->val; }
		bool									operator==(constListIterator const& right)			{ return pointer_ == right.pointer_; }
		bool									operator!=(constListIterator const& right)			{ return pointer_ != right.pointer_; }

		bool									operator==(nonConstIterator const& right)				{ return pointer_ == right.pointer_; }
		bool									operator!=(nonConstIterator const& right)				{ return pointer_ != right.pointer_; }

		constListIterator&	operator++() {
			pointer_ = pointer_->next;
			return *this;
		}

		constListIterator		operator++(int) {
			constListIterator	ret(pointer_);
			this->operator++();
			return ret;
		}

		constListIterator&			operator--() { --pointer_;
			return *this;
		}

		constListIterator			operator--(int) {
			constListIterator	ret(*this);
			this->operator--();
			return ret;
		}

		const node_pointer getPointer() const {
			return pointer_;
		}

	};
}

#endif //FT_LIST_LISTITERATOR_HPP
