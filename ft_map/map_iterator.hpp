//
// Created by Gilberto Dougal on 3/19/21.
//

#ifndef FT_LIST_MAPITERATOR_HPP
#define FT_LIST_MAPITERATOR_HPP
#include <iterator>

namespace ft {

	template<typename T, typename T_node>
	class constMapIterator;

	template<typename T, typename T_node>
	class mapIterator {
		typedef		T_node																		node_type;
		typedef		T_node*																		node_pointer;
		typedef		T_node&																		node_referense;
	public:
		typedef		T																					value_type;
		typedef		std::ptrdiff_t														difference_type;
		typedef		value_type*																pointer;
		typedef		value_type&																reference;
		typedef		std::bidirectional_iterator_tag						iterator_category;
		typedef		constMapIterator<value_type, node_type>		constIterator;
	private:
		node_pointer		pointer_;
	public:
		mapIterator(): pointer_(nullptr) {};

		explicit					mapIterator(node_pointer& reference)
						: pointer_(reference) {};
		mapIterator(const mapIterator& ref) {
			(*this) = ref;
		};
		virtual 					~mapIterator() {};

		mapIterator&		operator=(const mapIterator& ref) {
			if(this == &ref) {
				return *this;
			}
			pointer_ = ref.getPointer();
			return *this;
		};

		reference					operator*()																{ return (pointer_->pair_); }
		pointer						operator->() const												{ return &pointer_->pair_; }
		bool							operator!=(mapIterator const& right)			{ return pointer_ != right.pointer_; }
		bool							operator==(mapIterator const& right)			{ return pointer_ == right.pointer_; }

		bool							operator!=(constIterator const& right)		{ return pointer_ != right.pointer_; }
		bool							operator==(constIterator const& right)		{ return pointer_ == right.pointer_; }

		void	go_rl() {
				pointer_ = pointer_->right_;
				while(pointer_->left_) {
					pointer_ = pointer_->left_;
				}
		}

		mapIterator&			operator++() {
			node_pointer cur;
			if(pointer_->right_) {
				go_rl();
				return *this;
			}
			else if (pointer_ == pointer_->parent_->right_ && !pointer_->right_) {
				node_pointer tmp = pointer_->right_;
				while (pointer_->parent_) {
					cur = pointer_;
					pointer_ = pointer_->parent_;
					if (pointer_->right_) {
						go_rl();
						break;
					}
				}
				if (!pointer_->parent_ && pointer_->right_ == cur)
					pointer_ = tmp;
				return *this;
			}
			else {
				do {
						cur = pointer_;
						pointer_ = pointer_->parent_;
						if (pointer_->right_) {
							go_rl();
							break;
						}
				} while (cur != pointer_->left_);
				return *this;
			}
			return *this;
		}

		mapIterator			operator++(int) {
			mapIterator	ret(pointer_);
			this->operator++();
			return ret;
		}

		mapIterator&			operator--() {
			if(pointer_->left_) {
				pointer_ = pointer_->left_;
				while(pointer_->rigth_) {
					pointer_ = pointer_->rigth_;
				}
			}
			else {
				node_pointer cur;
				do {
					cur = pointer_;
					pointer_ = pointer_->parent_;
				} while (cur != pointer_->rigth_);
			}
			return *this;
		}

		mapIterator			operator--(int) {
			mapIterator	ret(pointer_);
			this->operator--();
			return ret;
		}

		const node_pointer& getPointer() const {
			return pointer_;
		}

//		node_pointer& getPointer() {
//			return pointer_;
//		}
	};

	template<typename T, typename T_node>
	class constMapIterator {
		typedef		T_node															node_type;
		typedef		T_node*															node_pointer;
		typedef		T_node&															node_referense;
	public:
		typedef		T																		value_type;
		typedef		std::ptrdiff_t											difference_type;
		typedef		value_type*													pointer;
		typedef		value_type&													reference;
		typedef		std::bidirectional_iterator_tag			iterator_category;
		typedef		mapIterator<value_type, node_type>	nonConstIterator;
	private:
		node_pointer		pointer_;

		explicit					constMapIterator(node_pointer& ref)
						: pointer_(ref) {};
	public:
		constMapIterator(): pointer_(nullptr) {};
		constMapIterator(const nonConstIterator& ref) {
			*this = ref;
		};
		constMapIterator(const constMapIterator& ref) {
			*this = ref;
		};

		virtual									~constMapIterator() {};

		constMapIterator&		operator=(const constMapIterator& ref) {
			if(this == &ref) {
				return *this;
			}
			pointer_ = ref.getPointer();
			return *this;
		};

		constMapIterator&		operator=(const nonConstIterator& ref) {
			if(this == &ref) {
				return *this;
			}
			pointer_ = ref.getPointer();
			return *this;
		};

		const reference				operator*()																			{ return (pointer_->val); }
		const pointer					operator->()																		{ return &pointer_->val; }
		bool									operator==(constMapIterator const& right)			{ return pointer_ == right.pointer_; }
		bool									operator!=(constMapIterator const& right)			{ return pointer_ != right.pointer_; }

		bool									operator==(nonConstIterator const& right)				{ return pointer_ == right.pointer_; }
		bool									operator!=(nonConstIterator const& right)				{ return pointer_ != right.pointer_; }

		constMapIterator&	operator++() {
			pointer_ = pointer_->next;
			return *this;
		}

		constMapIterator		operator++(int) {
			constMapIterator	ret(pointer_);
			this->operator++();
			return ret;
		}

		constMapIterator&			operator--() {
			pointer_ = pointer_->prev;
			return *this;
		}

		constMapIterator			operator--(int) {
			constMapIterator	ret(*this);
			this->operator--();
			return ret;
		}

		const node_pointer& getPointer() const {
			return pointer_;
		}

	};
}

#endif //FT_LIST_MAPITERATOR_HPP
