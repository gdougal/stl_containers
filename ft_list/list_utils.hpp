//
// Created by Gilberto Dougal on 3/19/21.
//

#ifndef FT_LIST_LIST_UTILS_HPP
#define FT_LIST_LIST_UTILS_HPP

namespace ft {

	template <typename valye_type>
	struct	Node {
	public:
		valye_type*						val;
		ft::Node<valye_type>*	prev;
		ft::Node<valye_type>*	next;
	};
}

#endif //FT_LIST_LIST_UTILS_HPP
