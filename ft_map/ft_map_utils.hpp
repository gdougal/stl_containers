//
// Created by Gilberto Dougal on 3/30/21.
//

#ifndef FT_MAP_FT_MAP_UTILS_HPP
#define FT_MAP_FT_MAP_UTILS_HPP
#include <utility>

namespace ft {

	template <class value_type>
	class	map_node {
		typedef ft::map_node<value_type>* node_pointer;
	public:
		value_type								pair_;
		int8_t										height_;
		node_pointer							parent_;
		node_pointer							left_;
		node_pointer							right_;



		map_node():  height_(0), parent_(nullptr), left_(nullptr), right_(nullptr) {}
		explicit map_node(const value_type& val): pair_(val), height_(1), parent_(nullptr), left_(nullptr), right_(nullptr) {};

		int8_t height(node_pointer Node)		{ return Node ? Node->height_ : 0; };
		int8_t max(int8_t a, int8_t b)	{ return (a > b) ? a : b; }

		void	fix_height(/*node_pointer cur*/) {
			if (this)
				height_ = 1 + max(height(left_), height(right_));
		}

		int8_t getBalanceFactor(node_pointer Node) {
			if (Node == NULL)
				return 0;
			Node->fix_height();
			Node->left_->fix_height();
			Node->right_->fix_height();
			return height(Node->left_) - height(Node->right_);
		}

		node_pointer&	getOneChild() {
			return left_ ? left_ : right_;
		}

		void	setLeftChild(node_pointer& left_child) {
				left_ = left_child;
				if (left_child)
					left_child->parent_ = this;
//				left_child->fix_height();
		}

		void	setRightChild(node_pointer& right_child) {
				right_ = right_child;
				if (right_child)
					right_child->parent_ = this;
//				right_child->fix_height();
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
//			parent->fix_height();
		}
		~map_node() {}
	};

}

#endif //FT_MAP_FT_MAP_UTILS_HPP
