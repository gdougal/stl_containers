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

const float g_radius_circles = 20.f;
const float win_width = 4500.f;
const float win_height = win_width / 1.5f;

typedef sf::Drawable* shapetype;
typedef std::vector<shapetype>::iterator ittype;
enum Hop : uint8_t {Left, Right};
sf::Font font;
float 			TREE_MAX_WIDTH;
float 			TREE_MAX_HEIGHT;

const int g_font_size = 20;

void add_tree_node(std::vector<Hop> v, std::vector<shapetype> & s, std::string content)
{
	int hops = v.size();
	int y = (int)(((win_height * (float)hops - 4*g_radius_circles)/(TREE_MAX_HEIGHT)) + 2*g_radius_circles);
	double x = win_width/2;
	float base_width = (x/((TREE_MAX_WIDTH)/hops))*std::log2(y) * (TREE_MAX_WIDTH - hops);
	for (int i = 0; i < hops; ++i) {
		if (v[i] == Left) {
			x -= (base_width / ((i + 1)));
		}
		else {
			x += (base_width / ((i + 1)));
		}
	}

	sf::CircleShape *circleShape = new sf::CircleShape;
	circleShape->setRadius(g_radius_circles);
	circleShape->setFillColor(sf::Color(y%100, y%120, y%80));
	circleShape->setPosition((float)x, (float)y);
	sf::Text *text = new sf::Text;

	text->setFont(font);
	text->setString(content);
	text->setCharacterSize(g_font_size);
	text->setOrigin(-10,-10);
	text->setPosition(x ,y);
	text->setFillColor(sf::Color(255,255,255));
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
	std::string content(std::to_string(root.pair_.first) + "\n" + std::to_string(root.height_));
	content += "\np: " + (root.parent_ ? std::to_string(root.parent_->pair_.first) : std::string("null"));
	content += "\nl: " + (root.left_ ? std::to_string(root.left_->pair_.first) : std::string("null"));
	content += "\nr: " + (root.right_ ? std::to_string(root.right_->pair_.first) : std::string("null"));
	add_tree_node(v,s, content);
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


	k.insert(std::pair<int, std::string>(70, "smth"));
	k.insert(std::pair<int, std::string>(80, "smth"));
	k.insert(std::pair<int, std::string>(200, "smth"));
	k.insert(std::pair<int, std::string>(300, "smth"));
	k.insert(std::pair<int, std::string>(4300, "smth"));
	k.insert(std::pair<int, std::string>(400, "smth"));
	k.insert(std::pair<int, std::string>(1100, "smth"));
	k.insert(std::pair<int, std::string>(1300, "smth"));
	k.insert(std::pair<int, std::string>(1400, "smth"));
	k.insert(std::pair<int, std::string>(3800, "smth"));
	k.insert(std::pair<int, std::string>(3900, "smth"));
	k.insert(std::pair<int, std::string>(4000, "smth"));
	k.insert(std::pair<int, std::string>(4100, "smth"));
	k.insert(std::pair<int, std::string>(4400, "smth"));
	k.insert(std::pair<int, std::string>(1200, "smth"));
	k.insert(std::pair<int, std::string>(4500, "smth"));
	k.insert(std::pair<int, std::string>(4600, "smth"));
	k.insert(std::pair<int, std::string>(4700, "smth"));
	k.insert(std::pair<int, std::string>(4200, "smth"));
	k.insert(std::pair<int, std::string>(100, "smth"));
	k.insert(std::pair<int, std::string>(4900, "smth"));
	k.insert(std::pair<int, std::string>(4800, "smth"));
	k.insert(std::pair<int, std::string>(1700, "smth"));
	k.insert(std::pair<int, std::string>(1800, "smth"));
	k.insert(std::pair<int, std::string>(1600, "smth"));
	k.insert(std::pair<int, std::string>(2100, "smth"));
	k.insert(std::pair<int, std::string>(1900, "smth"));
	k.insert(std::pair<int, std::string>(1500, "smth"));
	k.insert(std::pair<int, std::string>(5000, "smth"));
	k.insert(std::pair<int, std::string>(2200, "smth"));
	k.insert(std::pair<int, std::string>(2000, "smth"));
	k.insert(std::pair<int, std::string>(600, "smth"));
	k.insert(std::pair<int, std::string>(2300, "smth"));
	k.insert(std::pair<int, std::string>(2400, "smth"));
	k.insert(std::pair<int, std::string>(700, "smth"));
	k.insert(std::pair<int, std::string>(2600, "smth"));
	k.insert(std::pair<int, std::string>(500, "smth"));
	k.insert(std::pair<int, std::string>(2500, "smth"));
	k.insert(std::pair<int, std::string>(800, "smth"));
	k.insert(std::pair<int, std::string>(2700, "smth"));
	k.insert(std::pair<int, std::string>(900, "smth"));
	k.insert(std::pair<int, std::string>(3100, "smth"));
	k.insert(std::pair<int, std::string>(2800, "smth"));
	k.insert(std::pair<int, std::string>(3200, "smth"));
	k.insert(std::pair<int, std::string>(3300, "smth"));
	k.insert(std::pair<int, std::string>(2900, "smth"));
	k.insert(std::pair<int, std::string>(3000, "smth"));
	k.insert(std::pair<int, std::string>(3400, "smth"));
	k.insert(std::pair<int, std::string>(3500, "smth"));
	k.insert(std::pair<int, std::string>(3600, "smth"));
	k.insert(std::pair<int, std::string>(3700, "smth"));
	k.insert(std::pair<int, std::string>(1000, "smth"));

//	k.clear();
//	ft::map<int, std::string> k1(k);
//		k1 = k;
//	k1.insert(k.begin(), k.end());
//	k.erase(700);
//	k.erase(70);
//	k.erase(200);
//	k.erase(300);
//	k.erase(400);
//	k.erase(500);
//	k.erase(100);
//	k.erase(80);
//	k.erase(1000);
//	k.erase(700);
//	k.erase(600);
//	k.erase(1000);
//	k.erase(1100);
//	k.erase(900);
//	k.erase(1200);
//	k.erase(800);
//	k.erase(1300);
//	k.clear();
//	for (auto i = k.begin(); i != k.end() ; ++i) {
//		std::cout << i->first << std::endl;
//	}
	TREE_MAX_HEIGHT = std::log2(k.size()) + 1;
	TREE_MAX_WIDTH = std::pow(2,  (TREE_MAX_HEIGHT + 1));
	drwning(k);
	return 0;
}