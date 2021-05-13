//
// Created by Gilberto Dougal on 3/19/21.
//

#ifndef FT_LIST_LIST_UTILS_HPP
#define FT_LIST_LIST_UTILS_HPP

namespace list_util {

	template <typename value_type>
	struct	list_node {
	public:
		value_type							val;
		list_node<value_type>*	prev;
		list_node<value_type>*	next;
	};

	template <typename value_type>
	inline bool compare(const value_type& first, const value_type& second) {return (first < second);}

	template <typename value_type>
	bool								defaultPred(value_type& a, value_type& b) {
		return a == b;
	}
//	template <typename value_type>
//	inline bool								defaultRemovePred(value_type& val, value_type& ref) {
//		return val == ref;
//	}


	template<typename T, typename T_node>
	class constListIterator;

	template<typename T, typename T_node  = list_node<T> >
	class listIterator {
		typedef		T_node																		node_type;
		typedef		T_node*																		node_pointer;
		typedef		T_node&																		node_referense;
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

		explicit					listIterator(const node_pointer& reference)
						: pointer_(reference) {};
		listIterator(const listIterator& ref) {
			(*this) = ref;
		};
		explicit listIterator(const constIterator& ref) {
			(*this) = ref;
		};
		virtual 					~listIterator() {};

		listIterator&		operator=(const listIterator& ref) {
			if(this == &ref) {
				return *this;
			}
			pointer_ = ref.getPointer();
			return *this;
		};

		listIterator&		operator=(const constIterator& ref) {
			pointer_ = ref.getPointer();
			return *this;
		};

		reference					operator*()																{ return (pointer_->val); }
		pointer						operator->() const												{ return &pointer_->val; }
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

		const node_pointer& getPointer() const {
			return pointer_;
		}
	};

	template<typename T, typename T_node = list_node<T> >
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

	public:
		explicit					constListIterator(const node_pointer& ref)
						: pointer_(ref) {};
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
			pointer_ = ref.getPointer();
			return *this;
		};

		reference							operator*()																			{ return (pointer_->val); }
		const pointer					operator->()																		{ return &pointer_->val; }
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

		constListIterator&			operator--() {
			pointer_ = pointer_->prev;
			return *this;
		}

		constListIterator			operator--(int) {
			constListIterator	ret(*this);
			this->operator--();
			return ret;
		}

		const node_pointer& getPointer() const {
			return pointer_;
		}
	};

	template <class T>
	bool operator==(const listIterator<T>& lhs, const listIterator<T>& rhs)	{ return lhs.getPointer() == rhs.getPointer(); };

	template <class T>
	bool operator==(const listIterator<T>& lhs, const constListIterator<T>& rhs)	{ return lhs.getPointer() == rhs.getPointer(); };

	template <class T>
	bool operator==(const constListIterator<T>& lhs, const listIterator<T>& rhs)	{ return lhs.getPointer() == rhs.getPointer(); };

	template <class T>
	bool operator==(const constListIterator<T>& lhs, const constListIterator<T>& rhs)	{ return lhs.getPointer() == rhs.getPointer(); };

	template <class T>
	bool operator!=(const listIterator<T>& lhs, const listIterator<T>& rhs)	{ return lhs.getPointer() != rhs.getPointer(); };

	template <class T>
	bool operator!=(const listIterator<T>& lhs, const constListIterator<T>& rhs)	{ return lhs.getPointer() != rhs.getPointer(); };

	template <class T>
	bool operator!=(const constListIterator<T>& lhs, const listIterator<T>& rhs)	{ return lhs.getPointer() != rhs.getPointer(); };

	template <class T>
	bool operator!=(const constListIterator<T>& lhs, const constListIterator<T>& rhs)	{ return lhs.getPointer() != rhs.getPointer(); };
}

#endif //FT_LIST_LIST_UTILS_HPP
