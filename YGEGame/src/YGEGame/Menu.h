#ifndef _MENU_H_
#define _MENU_H_

#include "YGEText.h"
#include <string>
#include <vector>

class MenuListener {
public:
	virtual void menuItemSelected(std::string item) = 0;
};

class Menu;

class MenuItem {
public:
	MenuItem(std::string itemtext){
		text = new YGEGraphics::YGEText(itemtext);
		pos = new YGETimeSpace::YGEEntity();
		pos->addAsset(text);
		isCommand = true;
	}

	YGEGraphics::YGEText* text;
	YGETimeSpace::YGEEntity* pos;

	bool isCommand;
	std::string command;
	Menu* submenu;
};
	
class Menu {
private:
	std::vector<MenuItem*> items;

	int selectedItem;
public:
//	void addSubMenuItem(std::string text, Menu* submenu);
//	void addMenuListenerItem(std::string text, MenuListener* listener);

	Menu();

	Menu* parent;

	YGETimeSpace::YGEEntity* pos;

	YGETimeSpace::YGEEntity* children;

	void addItem(std::string text, std::string command);

	void addSubmenu(std::string text, Menu* sub);

	void up();

	void down();

	void left();

	void right();

	Menu* select();


};

#endif