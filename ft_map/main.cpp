#include <iostream>
#include "ft_map.hpp"
#include <map>
#include "draw_classes/drawer.hpp"




void	getline_wrap(std::string& read_here, int* heh) {
	std::getline(std::cin, read_here);
	if (std::cin.eof())
		exit(0);
	if (heh && std::isdigit(read_here[0])) {
		*heh = std::atoi(read_here.c_str());
		std::cout << "Successfully, added! (\"stop\" for break ADD-mode)" << std::endl;
	}
}


void	read_from_stdin(ft::map<int, std::string>& map_fo_fill) {
	std::string	read_here;
	int					add_num;
	std::cout << "Please write an integer: ";
	getline_wrap(read_here, &add_num);
	map_fo_fill.insert(std::pair<int, std::string>(add_num, "smth"));
}


int		main() {

	ft::map<int, std::string> k;
	k.insert(std::pair<int, std::string>(70, "smth"));
//	k.insert(std::pair<int, std::string>(80, "smth"));
//	k.insert(std::pair<int, std::string>(200, "smth"));
//	k.insert(std::pair<int, std::string>(300, "smth"));
//	k.insert(std::pair<int, std::string>(4300, "smth"));
//	k.insert(std::pair<int, std::string>(400, "smth"));
//	k.insert(std::pair<int, std::string>(1100, "smth"));
//	k.insert(std::pair<int, std::string>(1300, "smth"));
//	k.insert(std::pair<int, std::string>(1400, "smth"));
//	k.insert(std::pair<int, std::string>(3800, "smth"));
//	k.insert(std::pair<int, std::string>(3900, "smth"));
//	k.insert(std::pair<int, std::string>(4000, "smth"));
//	k.insert(std::pair<int, std::string>(4100, "smth"));
//	k.insert(std::pair<int, std::string>(4400, "smth"));
//	k.insert(std::pair<int, std::string>(1200, "smth"));
//	k.insert(std::pair<int, std::string>(4500, "smth"));
//	k.insert(std::pair<int, std::string>(4600, "smth"));
//	k.insert(std::pair<int, std::string>(4700, "smth"));
//	k.insert(std::pair<int, std::string>(4200, "smth"));
//	k.insert(std::pair<int, std::string>(100, "smth"));
//	k.insert(std::pair<int, std::string>(4900, "smth"));
//	k.insert(std::pair<int, std::string>(4800, "smth"));
//	k.insert(std::pair<int, std::string>(1700, "smth"));
//	k.insert(std::pair<int, std::string>(1800, "smth"));
//	k.insert(std::pair<int, std::string>(1600, "smth"));
//	k.insert(std::pair<int, std::string>(2100, "smth"));
//	k.insert(std::pair<int, std::string>(1900, "smth"));
//	k.insert(std::pair<int, std::string>(1500, "smth"));
//	k.insert(std::pair<int, std::string>(5000, "smth"));
//	k.insert(std::pair<int, std::string>(2200, "smth"));
//	k.insert(std::pair<int, std::string>(2000, "smth"));
//	k.insert(std::pair<int, std::string>(600, "smth"));
//	k.insert(std::pair<int, std::string>(2300, "smth"));
//	k.insert(std::pair<int, std::string>(2400, "smth"));
//	k.insert(std::pair<int, std::string>(700, "smth"));
//	k.insert(std::pair<int, std::string>(2600, "smth"));
//	k.insert(std::pair<int, std::string>(500, "smth"));
//	k.insert(std::pair<int, std::string>(2500, "smth"));
//	k.insert(std::pair<int, std::string>(800, "smth"));
//	k.insert(std::pair<int, std::string>(2700, "smth"));
//	k.insert(std::pair<int, std::string>(900, "smth"));
//	k.insert(std::pair<int, std::string>(3100, "smth"));
//	k.insert(std::pair<int, std::string>(2800, "smth"));
//	k.insert(std::pair<int, std::string>(3200, "smth"));
//	k.insert(std::pair<int, std::string>(3300, "smth"));
//	k.insert(std::pair<int, std::string>(2900, "smth"));
//	k.insert(std::pair<int, std::string>(3000, "smth"));
//	k.insert(std::pair<int, std::string>(3400, "smth"));
//	k.insert(std::pair<int, std::string>(3500, "smth"));
//	k.insert(std::pair<int, std::string>(3600, "smth"));
//	k.insert(std::pair<int, std::string>(3700, "smth"));
//	k.insert(std::pair<int, std::string>(1000, "smth"));
//	sf::Thread	thre(read_from_stdin, k);

	drawer<int, std::string>	drawer_(4500, "/Library/Fonts/Arial.ttf", k);
	while (drawer_.getSfmlWin()->isOpen()) {

		sf::Event e;
		while (drawer_.getSfmlWin()->pollEvent(e)) {

			switch (e.type) {
				case sf::Event::Closed:
					drawer_.getSfmlWin()->close();
					break;
			}
		}
		drawer_.drwning();
		read_from_stdin(k);
	}
	return 0;
}