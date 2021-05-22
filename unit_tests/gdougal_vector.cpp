//
// Created by Gilberto Dougal on 5/21/21.
//

#include "ft_vector.hpp"
#include "general_fiction.hpp"

#define INT_VEQ_EQUALITY(ft, std) Generazed_test<ft_vec_int, std_vec_int>::checkAreEqualIt(ft, std)

template <typename T>
class fill_behavior_vector_int: public Ifill_behavior<ft::vector<T>, std::vector<T> > {
public:
	fill_behavior_vector_int() = default;
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

	virtual ~fill_behavior_vector_int() = default;
};


class Vector_test_int : public Generazed_test<ft::vector<int>, std::vector<int> > {
public:
	Vector_test_int() {
		 fill_object = std::shared_ptr<fill_behavior_vector_int<int> >(new fill_behavior_vector_int<int>);
		 size_ = 100;
	}
	virtual ~Vector_test_int() = default;
};

class Vector_test_TEST_CLASS : public Generazed_test<ft::vector<TEST_CLASS>, std::vector<TEST_CLASS> > {
public:
	Vector_test_TEST_CLASS() {
		fill_object = std::shared_ptr<fill_behavior_vector_int<TEST_CLASS> >(new fill_behavior_vector_int<TEST_CLASS>);
		size_ = 100;
	}
	virtual ~Vector_test_TEST_CLASS() = default;
};




typedef ft::vector<int> ft_vec_int;
typedef std::vector<int> std_vec_int;
typedef ft::vector<TEST_CLASS> ft_vec_class;
typedef std::vector<TEST_CLASS> std_vec_class;

TEST(Vector_Constructor_test_int, default_const)
{
	ft_vec_int ft;
	std_vec_int std;
	assert_containers_eq(ft, std);
}

TEST(Vector_Constructor_test_int, fill_const)
{
	ft_vec_int ft(100, 100);
	std_vec_int std(100, 100);
	assert_containers_eq(ft, std);
}

TEST(Vector_Constructor_test_int, range_const_from_vector)
{
	std_vec_int		temp(100, 100);
	ft_vec_int ft(temp.begin(), temp.end());
	std_vec_int std(temp.begin(), temp.end());
	assert_containers_eq(ft, std);
}

TEST(Vector_Constructor_test_int, range_const_from_array)
{
	int		temp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ft_vec_int ft(temp, temp + 6);
	std_vec_int std(temp, temp + 6);
	assert_containers_eq(ft, std);
}

TEST(Vector_Constructor_test_int, range_const_from_list)
{
	std::list<int>	temp = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ft_vec_int ft(temp.begin(), temp.end());
	std_vec_int std(temp.begin(), temp.end());
	assert_containers_eq(ft, std);
}

TEST_F(Vector_test_int, copy_const_and_asign_operator)
{
	ft_cont_ = ft_cont_rand_;
	orig_cont_ = orig_cont_rand_;
	Check_sum_all();

	ft_cont_ = ft_cont_;
	orig_cont_ = orig_cont_;
	Check_sum_all();

	ft_cont_ = ft_cont_filed_;
	orig_cont_ = orig_cont_filed_;
	Check_sum_all();

	ft_vec_int	ft_tmp(ft_cont_);
	std_vec_int	std_tmp(orig_cont_);
	assert_containers_eq(ft_tmp, std_tmp);
}

TEST_F(Vector_test_int, empty)
{
	Check_sum_all();
}

TEST_F(Vector_test_int, size)
{
	Check_sum_all();
}

TEST_F(Vector_test_int, capacity)
{
	EXPECT_GE(ft_cont_.capacity(), ft_cont_.size());	// val1 >= val2
	EXPECT_GT(ft_cont_filed_.capacity(), ft_cont_filed_.size()); // val1 > val2
	EXPECT_GT(ft_cont_rand_.capacity(), ft_cont_rand_.size()); // val1 > val2
	EXPECT_EQ(ft_cont_filed_.capacity(), ft_cont_rand_.capacity());
}


template<class ft_cont, class std_cont>
void resize(ft_cont& ft, std_cont& std, uint64_t new_size) {
	assert_containers_eq(ft, std);
	ft.resize(new_size);
	std.resize(new_size);
	assert_containers_eq(ft, std);
}

TEST_F(Vector_test_int, resize_without_val)
{
	Check_sum_all();
	resize(ft_cont_, orig_cont_, 100);
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size());
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size()/2);
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() + orig_cont_filed_.size()*2);
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.capacity() + 1);
}


TEST_F(Vector_test_TEST_CLASS, resize_without_val)
{
	Check_sum_all();
	resize(ft_cont_, orig_cont_, 100);
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size());
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size()/2);
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() + orig_cont_filed_.size()*2);
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.capacity() + 1);
}

template<class ft_cont, class std_cont>
void resize_with_val(ft_cont& ft, std_cont& std, uint64_t new_size, int value) {
	assert_containers_eq(ft, std);
	ft.resize(new_size, value);
	std.resize(new_size, value);
	assert_containers_eq(ft, std);
}

TEST_F(Vector_test_int, resize_with_val)
{
	Check_sum_all();
	resize_with_val(ft_cont_, orig_cont_, 100, 1);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size(), 2);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size()/2, 3);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() + orig_cont_filed_.size()*2, 4);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.capacity() + 1, 5);
}

TEST_F(Vector_test_TEST_CLASS, resize_with_val)
{
	Check_sum_all();
	resize_with_val(ft_cont_, orig_cont_, 100, 1);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size(), 2);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size()/2, 3);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() + orig_cont_filed_.size()*2, 4);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.capacity() + 1, 5);
}

template<class ft_cont, class std_cont>
void reserve(ft_cont& ft, std_cont& std, uint64_t new_size) {
	assert_containers_eq(ft, std);
	ft.reserve(new_size);
	std.reserve(new_size);
	assert_containers_eq(ft, std);
	EXPECT_EQ(ft.capacity(), std.capacity());
}

TEST_F(Vector_test_int, reserve)
{
	Check_sum_all();
	reserve(ft_cont_, orig_cont_, 100);
	reserve(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.capacity() + 1);
	reserve(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.capacity() * 2);
	reserve(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.capacity() - ft_cont_filed_.capacity());
}

TEST_F(Vector_test_TEST_CLASS, reserve)
{
	Check_sum_all();
	reserve(ft_cont_, orig_cont_, 100);
	reserve(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.capacity() + 1);
	reserve(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.capacity() * 2);
	reserve(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.capacity() - ft_cont_filed_.capacity());
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

TEST_F(Vector_test_int, access_operator)
{
	Check_sum_all();
	acess(ft_cont_, orig_cont_);
	acess(ft_cont_filed_, orig_cont_filed_);
	acess(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, access_operator)
{
	Check_sum_all();
	acess(ft_cont_, orig_cont_);
	acess(ft_cont_filed_, orig_cont_filed_);
	acess(ft_cont_rand_, orig_cont_rand_);
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

TEST_F(Vector_test_int, at)
{
	Check_sum_all();
	at(ft_cont_, orig_cont_);
	at(ft_cont_filed_, orig_cont_filed_);
	at(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, at)
{
	Check_sum_all();
	at(ft_cont_, orig_cont_);
	at(ft_cont_filed_, orig_cont_filed_);
	at(ft_cont_rand_, orig_cont_rand_);
}

template<class ft_cont, class std_cont>
void front(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	while (!std.empty()) {
		EXPECT_EQ(ft.front(), std.front());
		ft.erase(ft.begin());
		std.erase(std.begin());
	}
	assert_containers_eq(ft, std);
}

TEST_F(Vector_test_int, front)
{
	Check_sum_all();
	front(ft_cont_, orig_cont_);
	front(ft_cont_filed_, orig_cont_filed_);
	front(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, front)
{
	Check_sum_all();
	front(ft_cont_, orig_cont_);
	front(ft_cont_filed_, orig_cont_filed_);
	front(ft_cont_rand_, orig_cont_rand_);
}


template<class ft_cont, class std_cont>
void back(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	while (!std.empty()) {
		EXPECT_EQ(ft.back(), std.back());
		ft.pop_back();
		std.pop_back();
	}
	assert_containers_eq(ft, std);
}

TEST_F(Vector_test_int, back)
{
	Check_sum_all();
	back(ft_cont_, orig_cont_);
	back(ft_cont_filed_, orig_cont_filed_);
	back(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, back)
{
	Check_sum_all();
	back(ft_cont_, orig_cont_);
	back(ft_cont_filed_, orig_cont_filed_);
	back(ft_cont_rand_, orig_cont_rand_);
}

template<class ft_cont, class std_cont>
void assign(const ft_cont& ft, const std_cont& std, ft_cont ft_assign = ft_cont(), std_cont std_assign = std_cont()) {
	assert_containers_eq(ft, std);
	typename ft_cont::const_iterator ft_it_begin(ft.begin());
	typename std_cont::const_iterator std_it_begin(std.begin());
	for (; ft_it_begin != ft.end() && std_it_begin != std.end(); ++ft_it_begin, ++std_it_begin) {
		ft_assign.assign(ft_it_begin, ft.end());
		std_assign.assign(std_it_begin, std.end());
		assert_containers_eq(ft, std);
		ft_assign.assign((size_t)std::distance(ft_it_begin, ft.end()), ft.front());
		std_assign.assign((size_t)std::distance(ft_it_begin, ft.end()), ft.front());
		assert_containers_eq(ft, std);
	}
}

TEST_F(Vector_test_int, assign)
{
	Check_sum_all();
	assign(ft_cont_, orig_cont_);
	assign(ft_cont_filed_, orig_cont_filed_, ft_vec_int(10, 10), std_vec_int(10, 10));
	assign(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, assign)
{
	Check_sum_all();
	assign(ft_cont_, orig_cont_);
	assign(ft_cont_filed_, orig_cont_filed_, ft_vec_class (10, 10), std_vec_class(10, 10));
	assign(ft_cont_rand_, orig_cont_rand_);
}

template<class ft_cont, class std_cont>
void push_back(ft_cont& ft, std_cont& std, ft_cont ft_assign = ft_cont(), std_cont std_assign = std_cont()) {
	assert_containers_eq(ft, std);
	typename ft_cont::iterator ft_it_begin(ft.begin());
	typename std_cont::iterator std_it_begin(std.begin());
	for (int i = 0; i != (int)std::distance(ft.begin(), ft.end()); ++i) {
		ft_assign.push_back(*ft_it_begin);
		std_assign.push_back(*std_it_begin);
		++ft_it_begin;
		++std_it_begin;
		assert_containers_eq(ft, std);
	}
}

TEST_F(Vector_test_int, push_back)
{
	Check_sum_all();
	push_back(ft_cont_, orig_cont_);
	push_back(ft_cont_filed_, orig_cont_filed_, ft_vec_int(ft_cont_rand_), std_vec_int(orig_cont_rand_));
	push_back(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, push_back)
{
	Check_sum_all();
	push_back(ft_cont_, orig_cont_);
	push_back(ft_cont_filed_, orig_cont_filed_, ft_vec_class(ft_cont_rand_), std_vec_class(orig_cont_rand_));
	push_back(ft_cont_rand_, orig_cont_rand_);
}

template<class ft_cont, class std_cont>
void pop_back(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	while (!ft.empty() && !std.empty()) {
		ft.pop_back();
		std.pop_back();
		assert_containers_eq(ft, std);
	}
}

TEST_F(Vector_test_int, pop_back)
{
	Check_sum_all();
	pop_back(ft_cont_, orig_cont_);
	pop_back(ft_cont_filed_, orig_cont_filed_);
	pop_back(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, pop_back)
{
	Check_sum_all();
	push_back(ft_cont_, orig_cont_);
	push_back(ft_cont_filed_, orig_cont_filed_);
	push_back(ft_cont_rand_, orig_cont_rand_);
}

template<class ft_cont, class std_cont>
void insert(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	int tmp;
	while (ft.size() != 500 && std.size() != 500) {
		tmp = (rand()%1023);
		ft.insert(ft.begin(), tmp);
		std.insert(std.begin(), tmp);
		ft.insert(ft.begin(), tmp);
		std.insert(std.begin(), tmp);
	}
}

TEST_F(Vector_test_int, insert)
{
	Check_sum_all();
	insert(ft_cont_filed_, orig_cont_filed_);
	insert(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, insert)
{
	Check_sum_all();
	insert(ft_cont_filed_, orig_cont_filed_);
	insert(ft_cont_rand_, orig_cont_rand_);
}

template<class ft_cont, class std_cont>
void insert_fill(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	int tmp;
	size_t number;
	while (ft.size() != 1000 && std.size() != 1000) {
		tmp = (rand()%1023);
		number = 20;
		ft.insert(ft.end(), number, tmp);
		std.insert(std.end(), number, tmp);
	}
}

TEST_F(Vector_test_int, insert_fill)
{
	Check_sum_all();
	insert_fill(ft_cont_, orig_cont_);
	insert_fill(ft_cont_filed_, orig_cont_filed_);
	insert_fill(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, insert_fill)
{
	Check_sum_all();
	insert_fill(ft_cont_, orig_cont_);
	insert_fill(ft_cont_filed_, orig_cont_filed_);
	insert_fill(ft_cont_rand_, orig_cont_rand_);
}