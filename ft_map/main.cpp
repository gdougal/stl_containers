#include <iostream>
#include "ft_map.hpp"
#include <map>
#include <vector>
#include <cctype>

void	getline_wrap(std::string& read_here, int* heh) {
	std::getline(std::cin, read_here);
	if (std::cin.eof())
		exit(0);
	if (heh && std::isdigit(read_here[0])) {
		*heh = std::atoi(read_here.c_str());
		std::cout << "Successfully, added! (\"stop\" for break ADD-mode)" << std::endl;
	}
}

void adding(ft::map<int, std::string>& map_fo_fill, std::string& read_here) {
	int					add_num;
	while(read_here != "stop") {
		std::cout << "Please write an integer: ";
		getline_wrap(read_here, &add_num);
		map_fo_fill.insert(std::pair<int, std::string>(add_num, "smth"));
	}
}

void	read_from_stdin(ft::map<int, std::string>& map_fo_fill) {
//	std::string	read_here;
//
//	std::cout << "Command: ADD or PRINT" << std::endl;
//	getline_wrap(read_here, nullptr);
//	if (read_here == "ADD") {
//		adding(map_fo_fill, read_here);
//	}
//	else if (read_here == "PRINT") {
		map_fo_fill.insert(std::pair<int, std::string>(100, "smth"));
		map_fo_fill.insert(std::pair<int, std::string>(200, "smth"));
		map_fo_fill.insert(std::pair<int, std::string>(300, "smth"));
		map_fo_fill.insert(std::pair<int, std::string>(400, "smth"));
		map_fo_fill.insert(std::pair<int, std::string>(500, "smth"));
		map_fo_fill.insert(std::pair<int, std::string>(600, "smth"));
		map_fo_fill.insert(std::pair<int, std::string>(700, "smth"));
		map_fo_fill.insert(std::pair<int, std::string>(800, "smth"));
		map_fo_fill.insert(std::pair<int, std::string>(900, "smth"));
		ft::map<int, std::string>::iterator it;
		it = map_fo_fill.begin();
		while (it != map_fo_fill.end()) {
			std::cout << (*it).first << std::endl;
			++it;
		}
		while (it-- != map_fo_fill.begin()) {
			std::cout << (*it).first << std::endl;
		}
//		read_here.clear();
//	}
}

//#include <SFML/Graphics.hpp>

int		main() {

//	sf::Window window(sf::VideoMode(800, 600), "My window");
//
//	// run the program as long as the window is open
//	while (window.isOpen())
//	{
//		// check all the window's events that were triggered since the last iteration of the loop
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			// "close requested" event: we close the window
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//	}
//	return 0;
//	exit(0);

		ft::map<int, std::string> k;

//	while (1) {
		read_from_stdin(k);
//	}
//	k.insert(std::pair<int, std::string>(100, "smth"));
//	k.insert(std::pair<int, std::string>(200, "smth"));
//	k.insert(std::pair<int, std::string>(300, "smth"));
//	k.insert(std::pair<int, std::string>(400, "smth"));
//	k.insert(std::pair<int, std::string>(500, "smth"));
//	k.insert(std::pair<int, std::string>(600, "smth"));
//	k.insert(std::pair<int, std::string>(700, "smth"));
//	k.insert(std::pair<int, std::string>(800, "smth"));
//	k.insert(std::pair<int, std::string>(900, "smth"));
	return 0;
}