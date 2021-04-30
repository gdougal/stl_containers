//
// Created by Gilberto Dougal on 4/30/21.
//

#ifndef FT_MAP_DRAWER_HPP
#define FT_MAP_DRAWER_HPP
#include <SFML/Graphics.hpp>
#include "../ft_map.hpp"
#include <vector>
#include <cmath>
#include <thread>

enum Hop : bool {Left, Right};
typedef std::shared_ptr<sf::Drawable>		 shapetype;
typedef std::vector<shapetype>::iterator ittype;
typedef map_util::map_node<std::pair<const int, std::string> > tree;

template<typename T, typename T1>
class 	tree_data {
	typedef map_util::map_node<std::pair<T, T1> > tree;
	float	TREE_MAX_WIDTH;
	float	TREE_MAX_HEIGHT;
	tree*	root_tree_;

public:
	explicit tree_data(const ft::map<T, T1>& ref) {
		root_tree_ = (tree *) ref.root_ret();
		std::cout << root_tree_->pair_.first << std::endl;
		TREE_MAX_HEIGHT = ref.height_ret();
		TREE_MAX_WIDTH = std::pow(2,  TREE_MAX_HEIGHT);
	}

	float	getTreeMaxWidth() const		{ return TREE_MAX_WIDTH; }
	float	getTreeMaxHeight() const	{ return TREE_MAX_HEIGHT; }
	tree	*getRootTree() const			{ return root_tree_; }

	void	reload_data(const ft::map<T, T1>& ref) {
		root_tree_ = (tree *) ref.root_ret();
		TREE_MAX_HEIGHT = ref.height_ret();
		TREE_MAX_WIDTH = std::pow(2,  TREE_MAX_HEIGHT);
	}
};

class	window_data	{
	float			win_width_; /*4000.f*/;
	float			win_height_;
	float			radius_circles_;
	int				font_size_;
	sf::Font	font;

public:
	window_data(float win_width, const std::string& font_name) :
					win_width_(win_width) {
		win_height_ = win_width_ / 2.35f;
		radius_circles_ = win_height_/100.f;
		font_size_ = static_cast<int>((win_height_)/100.f);
		font.loadFromFile(font_name);
	}
	float getWinWidth() const {return win_width_;}
	float getWinHeight() const {return win_height_;}
	float getRadiusCircles() const {return radius_circles_;}
	int getFontSize() const {return font_size_;}
	const sf::Font &getFont() const {return font;}
};

template<typename T, typename T1>
class	content_maker {
	typedef map_util::map_node<std::pair<T, T1> > tree;
	window_data							windowData;
	tree_data<T, T1>				treeData;
	std::vector<shapetype>	draw_data_;

public:
	float													getWindowWidth()		const {return windowData.getWinWidth();}
	float													getWindowHeight()		const {return windowData.getWinHeight();}
	const std::vector<shapetype>	&getDrawData()			const { return draw_data_; }

	content_maker(float win_width, const std::string& font_name, const ft::map<T, T1>& ref):
					windowData(win_width, font_name),
					treeData(ref) {
		trav_tree(*treeData.getRootTree(), std::vector<Hop>(0));
	}

	void	reload_tree_data(const ft::map<T, T1>& ref) {
		draw_data_.clear();
		treeData.reload_data(ref);
		trav_tree(*treeData.getRootTree(), std::vector<Hop>(0));
	}

private:
	void add_tree_node(const std::vector<Hop>& v, const std::string& content, int i)
	{
		float win_height = windowData.getWinHeight();
		float win_width = windowData.getWinWidth();
		float	radius_x2 = 2*windowData.getRadiusCircles();
		int hops = v.size();
		int y = (int)(((win_height * (float)hops - 2*radius_x2)/(treeData.getTreeMaxHeight())) + radius_x2);
		float x = win_width/2;
		for (int i = 0; i < hops; ++i) {
			if (v[i] == Left) {
				x -= (float)pow(2, hops - 1)/((float)i+1) * radius_x2;
			}
			else {
				x += (float)pow(2, hops - 1)/((float)i+1) * radius_x2;
			}
		}

		std::shared_ptr<sf::CircleShape> circleShape(new sf::CircleShape);
		circleShape->setRadius(windowData.getRadiusCircles());
		circleShape->setFillColor(sf::Color((y)%255, 150, 80));
		circleShape->setPosition((float)x, (float)y);
		std::shared_ptr<sf::Text> text(new sf::Text);

		text->setFont(windowData.getFont());
		text->setString(content);
		text->setCharacterSize(windowData.getFontSize());
		text->setOrigin(-10,-10);
		text->setPosition(x , y);
		text->setFillColor(sf::Color(255,255,255));
		text->setStyle(sf::Text::Bold);

		draw_data_.push_back(circleShape);
		draw_data_.push_back(text);
	}

	void trav_tree(const tree& root, std::vector<Hop> v, int i = 0) {
		if (root.left_) {
			++i;
			std::vector<Hop> l(v.begin(), v.end());
			l.push_back(Left);
			trav_tree(*root.left_, l);
		}

		if (root.right_) {
			++i;
			std::vector<Hop> r_hops(v.begin(), v.end());
			r_hops.push_back(Right);
			trav_tree(*root.right_, r_hops);
		}
		std::string content(std::to_string(root.pair_.first) + "\n" + std::to_string(root.height_));
		content += "\np: " + (root.parent_ ? std::to_string(root.parent_->pair_.first) : std::string("null"));
		content += "\nl: " + (root.left_ ? std::to_string(root.left_->pair_.first) : std::string("null"));
		content += "\nr: " + (root.right_ ? std::to_string(root.right_->pair_.first) : std::string("null"));
		add_tree_node(v, content, i);
	}
};

template<typename T, typename T1>
class	drawer {
	sf::RenderWindow*			sfmlWin;
	content_maker<T, T1>	content;
	ft::map<T, T1>*				ref_;
public:
	drawer(float win_width, const std::string& font_name, ft::map<T, T1>& ref):
					content(win_width, font_name, ref) {
		sfmlWin = new sf::RenderWindow(sf::VideoMode(content.getWindowWidth(), content.getWindowHeight()), "Hello World SFML Window");
		sfmlWin->setFramerateLimit(30);
		ref_ = &ref;
	}

	int	drwning() {
		content.reload_tree_data(*ref_);
		sfmlWin->clear();
		draw();
		sfmlWin->display();
		return 0;
	}


	virtual ~drawer() {
		delete sfmlWin;
	}

	sf::RenderWindow *getSfmlWin() const { return sfmlWin; }

private:
	void draw()
	{
		const std::vector<shapetype> &fo_draw = content.getDrawData();
		for (auto it = fo_draw.begin(); it != fo_draw.end(); it++)
			sfmlWin->draw(*(*it));
	}
};


#endif //FT_MAP_DRAWER_HPP
