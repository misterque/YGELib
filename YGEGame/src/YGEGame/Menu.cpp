#include "YGEEntity.h"
#include "Menu.h"
#include "GameManager.h"

Menu::Menu(){
	pos = new YGETimeSpace::YGEEntity();
	children = new YGETimeSpace::YGEEntity();
	pos->addChild(children);
	parent = NULL;
}

void Menu::addItem(std::string text, std::string command){
	MenuItem* item = new MenuItem(text);
	
	item->pos->translate3d(0, 40*items.size(), 0);
	items.push_back(item);
	children->addChild(item->pos);
	item->isCommand = true;
	item->command = command;

	if(items.size() == 1) {
		selectedItem = 0;
		item->text->setColor(1, 0, 0);
	}
}

void Menu::addSubmenu(std::string text, Menu* sub){

	addItem(text, "");
	items.back()->submenu = sub;
	items.back()->isCommand = false;
	items.back()->submenu->parent = this;

}

void Menu::up(){
	items[selectedItem]->text->setColor(1,1,0);
	selectedItem--;
	selectedItem %= items.size();
	items[selectedItem]->text->setColor(1,0,0);

}

void Menu::down(){
	items[selectedItem]->text->setColor(1,1,0);
	selectedItem++;
	selectedItem %= items.size();
	items[selectedItem]->text->setColor(1,0,0);

}

Menu* Menu::select(){
	if(items[selectedItem]->isCommand) {
		if( items[selectedItem]->command == "back" ) {
			parent->pos->addChild(parent->children);
			parent->pos->removeChild(pos);
			return parent;
		} else {
			GameManager::getInstance()->getCore()->processCommand(items[selectedItem]->command.c_str());
		}
	} else {
		pos->removeChild(children);
		pos->addChild(items[selectedItem]->submenu->pos);
		return items[selectedItem]->submenu;

	}


}

void Menu::left(){
}

void Menu::right(){
}