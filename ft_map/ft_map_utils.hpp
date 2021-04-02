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
		uint16_t									hight;
		node_pointer							parent_;
		node_pointer							left_;
		node_pointer							right_;

//		map_node():  hight(1), parent_(nullptr), left_(nullptr), right_(nullptr) {}
		explicit map_node(const value_type& val): pair_(val), hight(1), parent_(nullptr), left_(nullptr), right_(nullptr) {}
	};

}

#endif //FT_MAP_FT_MAP_UTILS_HPP
