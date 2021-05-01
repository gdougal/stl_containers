//
// Created by Gilberto Dougal on 3/30/21.
//

#ifndef FT_MAP_UTILS_HPP
#define FT_MAP_UTILS_HPP
#include <utility>
#include <iterator>


namespace map_util {

	template <class value_type>
	struct	map_node {
		typedef map_util::map_node<value_type>* node_pointer;
		value_type								pair_;
		int16_t										height_;
		node_pointer							parent_;
		node_pointer							left_;
		node_pointer							right_;


		map_node():  height_(0), parent_(nullptr), left_(nullptr), right_(nullptr) {}
		explicit map_node(const value_type& val): pair_(val), height_(1), parent_(nullptr), left_(nullptr), right_(nullptr) {};

		int16_t height(node_pointer& Node)		{ return Node ? Node->height_ : 0; };
		int16_t max(int16_t a, int16_t b)	{ return (a < b) ? b : a; }

		void	fix_height() {
			if (!this)
				return ;
			left_->fix_height();
			right_->fix_height();
			height_ = 1 + max(height(left_), height(right_));
		}

		int16_t getBalanceFactor(node_pointer& Node) {
			if (Node == nullptr)
				return 0;
			Node->fix_height();
			Node->left_->fix_height();
			Node->right_->fix_height();
			return (Node->height(Node->right_) - Node->height(Node->left_));
		}

		node_pointer&	getOneChild() { return left_ ? left_ : right_; }

		void	setLeftChild(node_pointer& left_child, const bool begin_end_ = false) {
			left_ = left_child;
			if (left_child)
				left_child->parent_ = this;
			if (!begin_end_) {
				left_child->fix_height();
				fix_height();
			}
		}

		void	setRightChild(node_pointer& right_child, const bool begin_end_ = false) {
			right_ = right_child;
			if (right_child)
				right_child->parent_ = this;
			if (!begin_end_) {
				right_child->fix_height();
				fix_height();
			}
		}

		void	setParent(node_pointer& child, node_pointer& parent, node_pointer ref = nullptr) {
			if (child)
				child->parent_ = parent;
			if (parent && parent->left_ == ref) {
				parent->setLeftChild(child);
			}
			else if (parent && parent->right_ == ref) {
				parent->setRightChild(child);
			}
			child->fix_height();
			parent->fix_height();
		}
		~map_node() {}
	};

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

		explicit					mapIterator(node_pointer& reference): pointer_(reference) {};
		mapIterator(const mapIterator& ref) { (*this) = ref; };
		virtual 					~mapIterator() {};

		mapIterator&			operator=(const mapIterator& ref) {
			if(this == &ref) {
				return *this;
			}
			pointer_ = ref.getPointer();
			return *this;
		};

		reference					operator*()																{ return (pointer_->pair_); };
		pointer						operator->() const												{ return &pointer_->pair_; };
		bool							operator!=(mapIterator const& other)			{ return pointer_ != other.pointer_; };
		bool							operator==(mapIterator const& other)			{ return pointer_ == other.pointer_; };
		bool							operator!=(constIterator const& other)		{ return pointer_ != other.pointer_; };
		bool							operator==(constIterator const& other)		{ return pointer_ == other.pointer_; };

		mapIterator&			operator++() {
			if(pointer_->right_) {
				pointer_ = pointer_->right_;
				while(pointer_->left_) {
					pointer_ = pointer_->left_;
				}
				return *this;
			}
			else if (pointer_->parent_->left_ == pointer_) {
				pointer_ = pointer_->parent_;
				return *this;
			}
			else {
				node_pointer prev_point;
				do {
					prev_point = pointer_;
					pointer_ = pointer_->parent_;
				} while (prev_point != pointer_->left_);
				return *this;
			}
		};

		mapIterator			operator++(int) {
			mapIterator	ret(pointer_);
			this->operator++();
			return ret;
		};

		mapIterator&			operator--() {
			if(pointer_->left_) {
				pointer_ = pointer_->left_;
				while(pointer_->right_) {
					pointer_ = pointer_->right_;
				}
				return *this;
			}
			else if (pointer_->parent_->right_ == pointer_) {
				pointer_ = pointer_->parent_;
				return *this;
			}
			else {
				node_pointer prev_point;
				do {
					prev_point = pointer_;
					pointer_ = pointer_->parent_;
				} while (pointer_ && prev_point != pointer_->right_);
				return *this;
			}
		};

		mapIterator			operator--(int) {
			mapIterator	ret(pointer_);
			this->operator--();
			return ret;
		};

		const node_pointer& getPointer() const {return pointer_;}
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

	public:
		explicit			constMapIterator(const node_pointer& ref): pointer_(ref) {};
									constMapIterator(): pointer_(nullptr) {};
									constMapIterator(const nonConstIterator& ref) { *this = ref; };
									constMapIterator(const constMapIterator& ref) { *this = ref; };
		virtual				~constMapIterator() {};

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

		const reference				operator*()																			{ return (pointer_->pair_); };
		const pointer					operator->()																		{ return &pointer_->pair_; };
		bool									operator==(constMapIterator const& other)				{ return pointer_ == other.pointer_; };
		bool									operator!=(constMapIterator const& other)				{ return pointer_ != other.pointer_; };
		bool									operator==(nonConstIterator const& other)				{ return pointer_ == other.pointer_; };
		bool									operator!=(nonConstIterator const& other)				{ return pointer_ != other.pointer_; };

		constMapIterator&	operator++() {
			if(pointer_->right_) {
				pointer_ = pointer_->right_;
				while(pointer_->left_) {
					pointer_ = pointer_->left_;
				}
				return *this;
			}
			else if (pointer_->parent_->left_ == pointer_) {
				pointer_ = pointer_->parent_;
				return *this;
			}
			else {
				node_pointer prev_point;
				do {
					prev_point = pointer_;
					pointer_ = pointer_->parent_;
				} while (prev_point != pointer_->left_);
				return *this;
			}
		};

		constMapIterator		operator++(int) {
			constMapIterator	ret(pointer_);
			this->operator++();
			return ret;
		};

		constMapIterator&			operator--() {
			if(pointer_->left_) {
				pointer_ = pointer_->left_;
				while(pointer_->right_) {
					pointer_ = pointer_->right_;
				}
				return *this;
			}
			else if (pointer_->parent_->right_ == pointer_) {
				pointer_ = pointer_->parent_;
				return *this;
			}
			else {
				node_pointer prev_point;
				do {
					prev_point = pointer_;
					pointer_ = pointer_->parent_;
				} while (pointer_ && prev_point != pointer_->right_);
				return *this;
			}
		};

		constMapIterator			operator--(int) {
			constMapIterator	ret(*this);
			this->operator--();
			return ret;
		};

		const node_pointer& getPointer() const { return pointer_; };
	};
}

#endif
