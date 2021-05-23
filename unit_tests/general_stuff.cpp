//
// Created by Gilberto Dougal on 5/23/21.
//

#include "general_test_stuff.hpp"

bool	operator==(const TEST_CLASS& lhs, const TEST_CLASS& rhs) {
	return (lhs.int_val == rhs.int_val && lhs.str_val == rhs.str_val);
}

bool	operator!=(const TEST_CLASS& lhs, const TEST_CLASS& rhs) {
	return !(lhs == rhs);
}

size_t random_size_t(size_t min, size_t max) {
	return  (max - min) * ((((size_t) rand()) / (size_t) RAND_MAX)) + min ;
}
