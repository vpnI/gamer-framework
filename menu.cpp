#include "menu.h"
#include <random>
#include <conio.h>
#include <iostream>


void menu::draw()
{
	toggle_reset_key(VK_INSERT, VK_END);
	set_menu_name("skate.bored");

	if (!m_opened)
		return;

	render();

	if (page_index == 0) {
		if (auto tab1 = std::make_shared<controls::tab>("rage group", bound(100, 130, 190, 350))) {
			tab1->checkbox("fake", &config::get().test1);
			tab1->slider("fakelag", &config::get().test7, 0, 14);
		}
	}
	if (page_index == 1) {

	}
	if (page_index == 2) {

	}
	if (page_index == 3) {

	}
}


void menu::init() {

	interfaces::inputsystem->enable_input(!m_opened);
	handle_input();
	draw();
}