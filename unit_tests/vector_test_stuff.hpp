//
// Created by Gilberto Dougal on 5/22/21.
//

#ifndef CONTAINERS_VECTOR_TEST_STUFF_HPP
#define CONTAINERS_VECTOR_TEST_STUFF_HPP
#include "ft_vector.hpp"
#include "general_test_stuff.hpp"


template <typename T>
class fill_behavior_vector: public Ifill_behavior<ft::vector<T>, std::vector<T> > {
	public:
	fill_behavior_vector() = default;
	void fill_rand(ft::vector<T>& my, std::vector<T>& origin, int cnt_obj) override {
		int tmp;
		for (int i = 0; i < cnt_obj; ++i) {
			tmp = rand()%1000;
			my.push_back(T(tmp));
			origin.push_back(T(tmp));
		}
	}

	void fill_stable(ft::vector<T>& my, std::vector<T>& origin, int cnt_obj) override {
		for (int i = 0; i < cnt_obj; ++i) {
			my.push_back(T(i));
			origin.push_back(T(i));
		}
}

	virtual ~fill_behavior_vector() = default;
};


class Vector_test_int : public Generazed_test<ft::vector<int>, std::vector<int> > {
	public:
	Vector_test_int() {
		fill_object = std::shared_ptr<fill_behavior_vector<int> >(new fill_behavior_vector<int>);
		size_ = 100;
	}
	virtual ~Vector_test_int() = default;
};

class Vector_test_TEST_CLASS : public Generazed_test<ft::vector<TEST_CLASS>, std::vector<TEST_CLASS> > {
	public:
	Vector_test_TEST_CLASS() {
		fill_object = std::shared_ptr<fill_behavior_vector<TEST_CLASS> >(new fill_behavior_vector<TEST_CLASS>);
		size_ = 100;
	}
	virtual ~Vector_test_TEST_CLASS() = default;
};


typedef ft::vector<int> ft_vec_int;
typedef std::vector<int> std_vec_int;
typedef ft::vector<TEST_CLASS> ft_vec_class;
typedef std::vector<TEST_CLASS> std_vec_class;


template<class ft_cont, class std_cont>
void reserve(ft_cont& ft, std_cont& std, uint64_t new_size) {
	assert_containers_eq(ft, std);
	ft.reserve(new_size);
	std.reserve(new_size);
	assert_containers_eq(ft, std);
	EXPECT_EQ(ft.capacity(), std.capacity());
}

template<class ft_cont, class std_cont>
void acess(const ft_cont& ft, const std_cont& std) {
	assert_containers_eq(ft, std);
	for (uint64_t i = 0; i < std.size(); ++i) {
		EXPECT_EQ(ft[i], std[i]);
	}
	for (uint64_t i = 0; i < ft.size(); ++i) {
		EXPECT_EQ(ft[i], std[i]);
	}
	assert_containers_eq(ft, std);
}

template<class ft_cont, class std_cont>
void at(const ft_cont& ft, const std_cont& std) {
	assert_containers_eq(ft, std);
	for (uint64_t i = 0; i < std.size(); ++i) {
		EXPECT_EQ(ft.at(i), std.at(i));
	}
	for (uint64_t i = 0; i < ft.size(); ++i) {
		EXPECT_EQ(ft.at(i), std.at(i));
	}
	// WITH THROW :
	//ft.at(ft.size());
	//std.at(std.size());
	assert_containers_eq(ft, std);
}


#endif //CONTAINERS_VECTOR_TEST_STUFF_HPP
