//
// Created by Gilberto Dougal on 5/21/21.
//

#include "vector_test_stuff.hpp"

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


TEST(Vector_Constructor_test_CLASS, fill_const)
{
	ft::vector<TEST_CLASS> ft(100, 100);
	std::vector<TEST_CLASS> std(100, 100);
	assert_containers_eq(ft, std);
}

TEST(Vector_Constructor_test_CLASS, range_const_from_vector)
{
	std::vector<TEST_CLASS>		temp(100, 100);
	ft::vector<TEST_CLASS> ft(temp.begin(), temp.end());
	std::vector<TEST_CLASS> std(temp.begin(), temp.end());
	assert_containers_eq(ft, std);
}

TEST(Vector_Constructor_test_CLASS, range_const_from_array)
{
	TEST_CLASS		temp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ft::vector<TEST_CLASS> ft(temp, temp + 6);
	std::vector<TEST_CLASS> std(temp, temp + 6);
	assert_containers_eq(ft, std);
}

TEST(Vector_Constructor_test_CLASS, range_const_from_list)
{
	std::list<TEST_CLASS>	temp = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ft::vector<TEST_CLASS> ft(temp.begin(), temp.end());
	std::vector<TEST_CLASS> std(temp.begin(), temp.end());
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

TEST_F(Vector_test_int, insert_range)
{
	Check_sum_all();
	insert_range(ft_cont_, orig_cont_);
	insert_range(ft_cont_filed_, orig_cont_filed_);
	insert_range(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, insert_range)
{
	Check_sum_all();
	insert_range(ft_cont_, orig_cont_);
	insert_range(ft_cont_filed_, orig_cont_filed_);
	insert_range(ft_cont_rand_, orig_cont_rand_);
}


TEST_F(Vector_test_int, erase_pos)
{
	Check_sum_all();
	erase(ft_cont_, orig_cont_);
	erase(ft_cont_filed_, orig_cont_filed_);
	erase(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, erase_pos)
{
	Check_sum_all();
	erase(ft_cont_, orig_cont_);
	erase(ft_cont_filed_, orig_cont_filed_);
	erase(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_int, erase_range)
{
	Check_sum_all();
	erase_range(ft_cont_, orig_cont_);
	erase_range(ft_cont_filed_, orig_cont_filed_);
	erase_range(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, erase_range)
{
	Check_sum_all();
	erase_range(ft_cont_, orig_cont_);
	erase_range(ft_cont_filed_, orig_cont_filed_);
	erase_range(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_int, swap)
{
	Check_sum_all();
	swap(ft_cont_, orig_cont_, ft_cont_filed_, orig_cont_filed_);
	swap(ft_cont_filed_, orig_cont_filed_, ft_cont_rand_, orig_cont_rand_);
	swap(ft_cont_rand_, orig_cont_rand_, ft_cont_, orig_cont_);
}

TEST_F(Vector_test_TEST_CLASS, swap_class)
{
	Check_sum_all();
	swap(ft_cont_, orig_cont_, ft_cont_filed_, orig_cont_filed_);
	swap(ft_cont_filed_, orig_cont_filed_, ft_cont_rand_, orig_cont_rand_);
	swap(ft_cont_rand_, orig_cont_rand_, ft_cont_, orig_cont_);
}

TEST_F(Vector_test_int, clear)
{
	Check_sum_all();
	clear(ft_cont_, orig_cont_);
	clear(ft_cont_filed_, orig_cont_filed_);
	clear(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(Vector_test_TEST_CLASS, clear_class)
{
	Check_sum_all();
	clear(ft_cont_, orig_cont_);
	clear(ft_cont_filed_, orig_cont_filed_);
	clear(ft_cont_rand_, orig_cont_rand_);
}