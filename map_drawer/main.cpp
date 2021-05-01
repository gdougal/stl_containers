#include <iostream>
#include "../ft_map.hpp"
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
//	k.insert(std::pair<int, std::string>(70, "smth"));

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