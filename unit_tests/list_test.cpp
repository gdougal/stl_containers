//
// Created by Gilberto Dougal on 5/23/21.
//

#include "list_test_stuff.hpp"

TEST(List_Constructor_test_int, default_const)
{
	ft::list<int> ft;
	std::list<int> std;
	assert_containers_eq(ft, std);
}

TEST(List_Constructor_test_int, fill_const)
{
	ft::list<int> ft(100, 100);
	std::list<int> std(100, 100);
	assert_containers_eq(ft, std);
}

TEST(List_Constructor_test_int, range_const_from_vector)
{
	std::vector<int>		temp(100, 100);
	ft::list<int> ft(temp.begin(), temp.end());
	std::list<int> std(temp.begin(), temp.end());
	assert_containers_eq(ft, std);
}

TEST(List_Constructor_test_int, range_const_from_array)
{
	int		temp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ft::list<int> ft(temp, temp + 6);
	std::list<int> std(temp, temp + 6);
	assert_containers_eq(ft, std);
}

TEST(List_Constructor_test_int, range_const_from_list)
{
	std::list<int>	temp = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ft::list<int> ft(temp.begin(), temp.end());
	std::list<int> std(temp.begin(), temp.end());
	assert_containers_eq(ft, std);
}


TEST(List_Constructor_test_CLASS, fill_const)
{
	ft::list<TEST_CLASS> ft(100, 100);
	std::list<TEST_CLASS> std(100, 100);
	assert_containers_eq(ft, std);
}

TEST(List_Constructor_test_CLASS, range_const_from_vector)
{
	std::vector<TEST_CLASS>		temp(100, 100);
	ft::list<TEST_CLASS> ft(temp.begin(), temp.end());
	std::list<TEST_CLASS> std(temp.begin(), temp.end());
	assert_containers_eq(ft, std);
}

TEST(List_Constructor_test_CLASS, range_const_from_array)
{
	TEST_CLASS		temp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ft::list<TEST_CLASS> ft(temp, temp + 6);
	std::list<TEST_CLASS> std(temp, temp + 6);
	assert_containers_eq(ft, std);
}

TEST(List_Constructor_test_CLASS, range_const_from_list)
{
	std::list<TEST_CLASS>	temp = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ft::list<TEST_CLASS> ft(temp.begin(), temp.end());
	std::list<TEST_CLASS> std(temp.begin(), temp.end());
	assert_containers_eq(ft, std);
}

TEST_F(List_test_int, front)
{
	Check_sum_all();
	front(ft_cont_, orig_cont_);
	front(ft_cont_filed_, orig_cont_filed_);
	front(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, front)
{
	Check_sum_all();
	front(ft_cont_, orig_cont_);
	front(ft_cont_filed_, orig_cont_filed_);
	front(ft_cont_rand_, orig_cont_rand_);
}


TEST_F(List_test_int, back)
{
	Check_sum_all();
	back(ft_cont_, orig_cont_);
	back(ft_cont_filed_, orig_cont_filed_);
	back(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, back)
{
	Check_sum_all();
	back(ft_cont_, orig_cont_);
	back(ft_cont_filed_, orig_cont_filed_);
	back(ft_cont_rand_, orig_cont_rand_);
}


TEST_F(List_test_int, assign)
{
	Check_sum_all();
	assign(ft_cont_, orig_cont_);
	assign(ft_cont_filed_, orig_cont_filed_, ft::list<int>(10, 10), std::list<int>(10, 10));
	assign(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, assign)
{
	Check_sum_all();
	assign(ft_cont_, orig_cont_);
	assign(ft_cont_filed_, orig_cont_filed_, ft::list<TEST_CLASS> (10, 10), std::list<TEST_CLASS>(10, 10));
	assign(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_int, push_back)
{
	Check_sum_all();
	push_back(ft_cont_, orig_cont_);
	push_back(ft_cont_filed_, orig_cont_filed_, ft::list<int>(ft_cont_rand_), std::list<int>(orig_cont_rand_));
	push_back(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, push_back)
{
	Check_sum_all();
	push_back(ft_cont_, orig_cont_);
	push_back(ft_cont_filed_, orig_cont_filed_, ft::list<TEST_CLASS>(ft_cont_rand_), std::list<TEST_CLASS>(orig_cont_rand_));
	push_back(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_int, pop_back)
{
	Check_sum_all();
	pop_back(ft_cont_, orig_cont_);
	pop_back(ft_cont_filed_, orig_cont_filed_);
	pop_back(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, pop_back)
{
	Check_sum_all();
	push_back(ft_cont_, orig_cont_);
	push_back(ft_cont_filed_, orig_cont_filed_);
	push_back(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_int, insert)
{
	Check_sum_all();
	insert(ft_cont_filed_, orig_cont_filed_);
	insert(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, insert)
{
	Check_sum_all();
	insert(ft_cont_filed_, orig_cont_filed_);
	insert(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_int, insert_fill)
{
	Check_sum_all();
	insert_fill(ft_cont_, orig_cont_);
	insert_fill(ft_cont_filed_, orig_cont_filed_);
	insert_fill(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, insert_fill)
{
	Check_sum_all();
	insert_fill(ft_cont_, orig_cont_);
	insert_fill(ft_cont_filed_, orig_cont_filed_);
	insert_fill(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_int, insert_range)
{
	Check_sum_all();
	insert_range(ft_cont_, orig_cont_);
	insert_range(ft_cont_filed_, orig_cont_filed_);
	insert_range(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, insert_range)
{
	Check_sum_all();
	insert_range(ft_cont_, orig_cont_);
	insert_range(ft_cont_filed_, orig_cont_filed_);
	insert_range(ft_cont_rand_, orig_cont_rand_);
}


TEST_F(List_test_int, erase_pos)
{
	Check_sum_all();
	erase(ft_cont_, orig_cont_);
	erase(ft_cont_filed_, orig_cont_filed_);
	erase(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, erase_pos)
{
	Check_sum_all();
	erase(ft_cont_, orig_cont_);
	erase(ft_cont_filed_, orig_cont_filed_);
	erase(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_int, erase_range)
{
	Check_sum_all();
	erase_range(ft_cont_, orig_cont_);
	erase_range(ft_cont_filed_, orig_cont_filed_);
	erase_range(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, erase_range)
{
	Check_sum_all();
	erase_range(ft_cont_, orig_cont_);
	erase_range(ft_cont_filed_, orig_cont_filed_);
	erase_range(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, swap_class)
{
	Check_sum_all();
	swap(ft_cont_, orig_cont_, ft_cont_filed_, orig_cont_filed_);
	swap(ft_cont_filed_, orig_cont_filed_, ft_cont_rand_, orig_cont_rand_);
	swap(ft_cont_rand_, orig_cont_rand_, ft_cont_, orig_cont_);
}

TEST_F(List_test_int, clear)
{
	Check_sum_all();
	clear(ft_cont_, orig_cont_);
	clear(ft_cont_filed_, orig_cont_filed_);
	clear(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, clear_class)
{
	Check_sum_all();
	clear(ft_cont_, orig_cont_);
	clear(ft_cont_filed_, orig_cont_filed_);
	clear(ft_cont_rand_, orig_cont_rand_);
}


TEST_F(List_test_int, resize_without_val)
{
	Check_sum_all();
	resize(ft_cont_, orig_cont_, 100);
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size());
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size()/2);
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() + orig_cont_filed_.size()*2);
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() + 1);
}


TEST_F(List_test_TEST_CLASS, resize_without_val)
{
	Check_sum_all();
	resize(ft_cont_, orig_cont_, 100);
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size());
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size()/2);
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() + orig_cont_filed_.size()*2);
	resize(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() + 1);
}

TEST_F(List_test_int, resize_with_val)
{
	Check_sum_all();
	resize_with_val(ft_cont_, orig_cont_, 100, 1);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size(), 2);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size()/2, 3);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() + orig_cont_filed_.size()*2, 4);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() + 1, 5);
}

TEST_F(List_test_TEST_CLASS, resize_with_val)
{
	Check_sum_all();
	resize_with_val(ft_cont_, orig_cont_, 100, 1);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size(), 2);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() - orig_cont_filed_.size()/2, 3);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() + orig_cont_filed_.size()*2, 4);
	resize_with_val(ft_cont_filed_, orig_cont_filed_, orig_cont_filed_.size() + 1, 5);
}

TEST_F(List_test_int, splise_elem)
{
	Check_sum_all();
	splice_list(ft_cont_filed_, orig_cont_filed_, ft_cont_, orig_cont_);
	splice_elem(ft_cont_, orig_cont_, ft_cont_filed_, orig_cont_filed_);
	splice_elem(ft_cont_, orig_cont_, ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, splise_elem)
{
	Check_sum_all();
	splice_list(ft_cont_filed_, orig_cont_filed_, ft_cont_, orig_cont_);
	splice_elem(ft_cont_, orig_cont_, ft_cont_filed_, orig_cont_filed_);
	splice_elem(ft_cont_, orig_cont_, ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_int, splise_list)
{
	Check_sum_all();
	splice_list(ft_cont_filed_, orig_cont_filed_, ft_cont_, orig_cont_);
	splice_list(ft_cont_, orig_cont_, ft_cont_filed_, orig_cont_filed_);
	splice_list(ft_cont_, orig_cont_, ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, splise_list)
{
	Check_sum_all();
	splice_list(ft_cont_filed_, orig_cont_filed_, ft_cont_, orig_cont_);
	splice_list(ft_cont_, orig_cont_, ft_cont_filed_, orig_cont_filed_);
	splice_list(ft_cont_, orig_cont_, ft_cont_rand_, orig_cont_rand_);
}


TEST_F(List_test_int, splise_range)
{
	Check_sum_all();
	splice_range(ft_cont_filed_, orig_cont_filed_, ft_cont_, orig_cont_);
	splice_range(ft_cont_, orig_cont_, ft_cont_filed_, orig_cont_filed_);
	splice_range(ft_cont_, orig_cont_, ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, splise_range)
{
	Check_sum_all();
	splice_range(ft_cont_filed_, orig_cont_filed_, ft_cont_, orig_cont_);
	splice_range(ft_cont_, orig_cont_, ft_cont_filed_, orig_cont_filed_);
	splice_range(ft_cont_, orig_cont_, ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_int, remove)
{
	Check_sum_all();
	remove(ft_cont_filed_, orig_cont_filed_, int());
	remove(ft_cont_rand_, orig_cont_rand_, int());
}

TEST_F(List_test_TEST_CLASS, remove)
{
	Check_sum_all();
	remove(ft_cont_filed_, orig_cont_filed_, TEST_CLASS());
	remove(ft_cont_rand_, orig_cont_rand_, TEST_CLASS());
}

TEST_F(List_test_int, remove_if)
{
	Check_sum_all();
	remove_if(ft_cont_filed_, orig_cont_filed_);
	remove_if(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_int, unique)
{
	Check_sum_all();
	unique(ft_cont_filed_, orig_cont_filed_);
	ft_cont_filed_.resize(ft_cont_filed_.size() * 2, int(10));
	orig_cont_filed_.resize(orig_cont_filed_.size() * 2, int(10));
	unique(ft_cont_filed_, orig_cont_filed_);
	unique(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, unique)
{
	Check_sum_all();
	unique(ft_cont_filed_, orig_cont_filed_);
	ft_cont_filed_.resize(ft_cont_filed_.size() * 2, TEST_CLASS(10));
	orig_cont_filed_.resize(orig_cont_filed_.size() * 2, TEST_CLASS(10));
	unique(ft_cont_filed_, orig_cont_filed_);
	unique(ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_int, unique_with_binary_pred)
{
	Check_sum_all();
	unique_with_binary_pred(ft_cont_filed_, orig_cont_filed_, int());
	ft_cont_filed_.resize(ft_cont_filed_.size() * 2, int(10));
	orig_cont_filed_.resize(orig_cont_filed_.size() * 2, int(10));
	unique_with_binary_pred(ft_cont_filed_, orig_cont_filed_, int());
	unique_with_binary_pred(ft_cont_rand_, orig_cont_rand_, int());
}

TEST_F(List_test_TEST_CLASS, unique_with_binary_pred)
{
	Check_sum_all();
	unique_with_binary_pred(ft_cont_filed_, orig_cont_filed_, TEST_CLASS());
	ft_cont_filed_.resize(ft_cont_filed_.size() * 2, TEST_CLASS(10));
	orig_cont_filed_.resize(orig_cont_filed_.size() * 2, TEST_CLASS(10));
	unique_with_binary_pred(ft_cont_filed_, orig_cont_filed_, TEST_CLASS());
	unique_with_binary_pred(ft_cont_rand_, orig_cont_rand_, TEST_CLASS());
}

TEST_F(List_test_int, merge)
{
	Check_sum_all();
	merge(ft_cont_filed_, orig_cont_filed_, ft_cont_rand_, orig_cont_rand_);
}

TEST_F(List_test_TEST_CLASS, merge)
{
	Check_sum_all();
	merge(ft_cont_filed_, orig_cont_filed_, ft_cont_rand_, orig_cont_rand_);
}


TEST_F(List_test_int, sort)
{
	Check_sum_all();
	int tmp;
	while (ft_cont_.size() < 100000) {
		tmp = (int)random_size_t(0, 100000);
		ft_cont_.push_back(tmp);
		orig_cont_.push_back(tmp);
	}
	ft_cont_.sort();
	orig_cont_.sort();
	assert_containers_eq(ft_cont_, orig_cont_);
}

TEST_F(List_test_TEST_CLASS, sort)
{
	Check_sum_all();
	int tmp;
	while (ft_cont_.size() < 100000) {
		tmp = (int)random_size_t(0, 100000);
		ft_cont_.push_back(TEST_CLASS(tmp));
		orig_cont_.push_back(TEST_CLASS(tmp));
	}
	ft_cont_.sort();
	orig_cont_.sort();
	assert_containers_eq(ft_cont_, orig_cont_);
}


template <typename T>
bool compare_ (const T& first, const T& second)
{
	return ( first > second );
}


TEST_F(List_test_int, sort_param_and_reverse)
{
	Check_sum_all();
	int tmp;
	while (ft_cont_.size() < 100000) {
		tmp = (int)random_size_t(0, 100000);
		ft_cont_.push_back(tmp);
		orig_cont_.push_back(tmp);
	}
	ft_cont_.sort();
	orig_cont_.sort();
	assert_containers_eq(ft_cont_, orig_cont_);
	ft_cont_.sort(compare_<int>);
	orig_cont_.sort(compare_<int>);
	assert_containers_eq(ft_cont_, orig_cont_);
	ft_cont_.reverse();
	orig_cont_.reverse();
	assert_containers_eq(ft_cont_, orig_cont_);
}

TEST_F(List_test_TEST_CLASS, sort_param_and_reverse)
{
	Check_sum_all();
	int tmp;
	while (ft_cont_.size() < 100000) {
		tmp = (int)random_size_t(0, 100000);
		ft_cont_.push_back(TEST_CLASS(tmp));
		orig_cont_.push_back(TEST_CLASS(tmp));
	}
	ft_cont_.sort();
	orig_cont_.sort();
	assert_containers_eq(ft_cont_, orig_cont_);
	ft_cont_.sort(compare_<TEST_CLASS>);
	orig_cont_.sort(compare_<TEST_CLASS>);
	assert_containers_eq(ft_cont_, orig_cont_);
	ft_cont_.reverse();
	orig_cont_.reverse();
	assert_containers_eq(ft_cont_, orig_cont_);
}
