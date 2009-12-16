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


/**
 * @brief simple menu item
 *
 * has a text and a position, only needed by Menu
 */
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

/**
 * @brief class for creating basic menus
 */
class Menu {
private:
	std::vector<MenuItem*> items;

	int selectedItem;
public:

	Menu();

	Menu* parent;

	YGETimeSpace::YGEEntity* pos;

	YGETimeSpace::YGEEntity* children;

	/**
	 * @brief create a menuitem for this menu
	 * @param text text of the item
	 * @param command command of the menuitem that will be passed to the engine core on selection
	 */
	void addItem(std::string text, std::string command);

	/**
	 * @brief add another menu to this menu
	 *
	 * on selection, the other menu will be displayed and this will be hidden
	 */
	void addSubmenu(std::string text, Menu* sub);

	void up();

	void down();

	void left();

	void right();


	Menu* select();


};

#endif