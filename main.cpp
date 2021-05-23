#include <iostream>
#include "ft_list.hpp"
#include "ft_vector.hpp"
#include "ft_map.hpp"
#include "ft_stack.hpp"
#include "ft_queue.hpp"

int main()
{
	ft::vector<ssize_t> vectora(10, 10);
	ft::list<ft::vector<ssize_t> > listbl(10, ft::vector<ssize_t>(vectora));
	ft::map<std::string, ft::list<ft::vector<ssize_t> > > mapa;

	std::pair<ft::map<std::string, ft::list<ft::vector<ssize_t> > >::iterator, bool > ret =  mapa.insert(std::make_pair(std::string("Ono pravda"), ft::list<ft::vector<ssize_t> >(listbl)));
	std::cout << ret.first->first + " compilatable" << std::endl;

	return 0;
}