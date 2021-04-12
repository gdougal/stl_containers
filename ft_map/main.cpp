#include <iostream>
#include "ft_map.hpp"
#include <map>
#include <vector>
#include <cctype>
#include <SFML/Graphics.hpp>


//void	getline_wrap(std::string& read_here, int* heh) {
//	std::getline(std::cin, read_here);
//	if (std::cin.eof())
//		exit(0);
//	if (heh && std::isdigit(read_here[0])) {
//		*heh = std::atoi(read_here.c_str());
//		std::cout << "Successfully, added! (\"stop\" for break ADD-mode)" << std::endl;
//	}
//}
//
//void adding(ft::map<int, std::string>& map_fo_fill, std::string& read_here) {
//	int					add_num;
//	while(read_here != "stop") {
//		std::cout << "Please write an integer: ";
//		getline_wrap(read_here, &add_num);
//		map_fo_fill.insert(std::pair<int, std::string>(add_num, "smth"));
//	}
//}

//void	read_from_stdin(ft::map<int, std::string>& map_fo_fill) {
//	std::string	read_here;
//
//	std::cout << "Command: ADD or PRINT" << std::endl;
//	getline_wrap(read_here, nullptr);
//	if (read_here == "ADD") {
//		adding(map_fo_fill, read_here);
//	}
//	else if (read_here == "PRINT") {
//		read_here.clear();
//	}
//}

const float g_radius_circles = 30.f;
const float win_width = 2500.f;
const float win_height = win_width / 1.5f;

typedef sf::Drawable* shapetype;
typedef std::vector<shapetype>::iterator ittype;
enum Hop : uint8_t {Left, Right};
sf::Font font;

const int g_font_size = 25;

void add_tree_node(std::vector<Hop> v, std::vector<shapetype> & s, std::string content)
{
	int hops = v.size();
	int base_width = g_radius_circles * 12;
	int y = (int)((g_radius_circles * 4) * (float)hops);
	int x = win_width / 2;

	for (int i = 0; i < hops; ++i) {
		if (v[i] == Left)
			x -= base_width / ((i+1) / 1.3f);
		else
			x += base_width / ((i+1) / 1.3f);
	}

	sf::CircleShape *circleShape = new sf::CircleShape;
	circleShape->setRadius(g_radius_circles);
	circleShape->setFillColor(sf::Color(255, y, y/2));
	circleShape->setPosition((float)x, (float)y);
	sf::Text *text = new sf::Text;

	text->setFont(font);
	text->setString(content);
	text->setCharacterSize(g_font_size);
	text->setOrigin(-10,-10);
	text->setPosition(x ,y);
	text->setFillColor(sf::Color(0,255,255));
	text->setStyle(sf::Text::Bold);

	s.push_back(circleShape);
	s.push_back(text);
}

typedef ft::map_node<std::pair<const int, std::string> > tree;



void trav_tree(tree & root, std::vector<Hop> v, std::vector<shapetype> & s)
{
	if(root.left_) {
		std::vector<Hop> l (v.begin(), v.end());
		l.push_back(Left);
		trav_tree(*root.left_, l , s);
	}

	if(root.right_) {
		std::vector<Hop> r_hops (v.begin(), v.end());
		r_hops.push_back(Right);
		trav_tree(*root.right_,  r_hops, s);
	}

	add_tree_node(v,s,std::to_string(root.pair_.first));
}

void draw(std::vector<shapetype> & v, sf::RenderWindow & w)
{
	for (ittype it = v.begin(); it != v.end(); it++)
		w.draw(*(*it));
}

typedef ft::map<int, std::string>::iterator map_iter;

int	drwning(ft::map<int, std::string>& ref) {
	std::vector<shapetype> v;
	std::vector<Hop> h(0);
	tree & t = *(ref.root_);
	trav_tree(t, h, v);

	sf::RenderWindow sfmlWin(sf::VideoMode(win_width, win_height), "Hello World SFML Window");

	//You need to pass the font file location
	if (!font.loadFromFile("/Library/Fonts/Arial.ttf")) {
		return -1;
	}

	while (sfmlWin.isOpen()) {

		sf::Event e;
		while (sfmlWin.pollEvent(e)) {

			switch (e.type) {
				case sf::Event::EventType::Closed:
					sfmlWin.close();
					break;
			}
		}

		sfmlWin.clear();
		draw(v, sfmlWin);
		sfmlWin.display();
	}
	return 0;
}


int		main() {

	ft::map<int, std::string> k;
//	read_from_stdin(k);

	k.insert(std::pair<int, std::string>(100, "smth"));
	k.insert(std::pair<int, std::string>(200, "smth"));
	k.insert(std::pair<int, std::string>(300, "smth"));
	k.insert(std::pair<int, std::string>(400, "smth"));
	k.insert(std::pair<int, std::string>(500, "smth"));
	k.insert(std::pair<int, std::string>(600, "smth"));
	k.insert(std::pair<int, std::string>(700, "smth"));
	k.insert(std::pair<int, std::string>(800, "smth"));
	k.insert(std::pair<int, std::string>(900, "smth"));
	k.insert(std::pair<int, std::string>(1000, "smth"));
	k.insert(std::pair<int, std::string>(1100, "smth"));
	k.insert(std::pair<int, std::string>(1200, "smth"));
	k.insert(std::pair<int, std::string>(1300, "smth"));
	k.insert(std::pair<int, std::string>(80, "smth"));
	k.insert(std::pair<int, std::string>(70, "smth"));

	ft::map<int, std::string> k1;
	k1.insert(k.begin(), k.end());
	std::map<int, std::string> k2;
	k2.insert(k.begin(), k.end());
	std::cout << (k1.lower_bound(150))->first << std::endl;
	std::cout << (k2.lower_bound(150))->first << std::endl;
	std::cout << (k2.lower_bound(150))->first << std::endl;
//	k1.erase(70);
//	k1.erase(200);
//	k1.erase(300);
//	k1.erase(400);
//	k1.erase(500);
//	k1.erase(100);
//	k1.erase(80);
//	k1.erase(1000);
//	k1.erase(700);
//	k1.erase(600);
//	k1.erase(1000);
//	k1.erase(1100);
//	k1.erase(900);
//	k1.erase(1200);
//	k1.erase(800);
//	k1.erase(1300);
//	k1.clear();
	drwning(k1);
	return 0;
}