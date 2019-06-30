#pragma once
#pragma once
#include <vector>
#include <memory>
#include <random>
#include <iostream>
#include <ShlObj_core.h>
#include <functional>
#include "../../dependencies/utilities/render.hpp"
#include "../../dependencies/common_includes.hpp"
#include "config.h"

class bound {
public:
	float x, y, w, h;

	bound() {
		x = 0; y = 0; w = 0; h = 0;
	};
	bound(float _x, float _y, float _w, float _h) {
		x = _x; y = _y; w = _w; h = _h;
	};
};

class menu : public singleton<menu> {
public:
	bool m_opened = NULL, m_click = NULL;
	int m_vk1 = NULL, m_vk2 = NULL, page_index = NULL, tab_amount = NULL;
	int last_control = NULL, test = NULL;
	vec2 m_pos = vec2(500, 500), m_size = vec2(460, 500);
	std::string m_menuname = "";
	std::string tabs[4] = {"Rage","Visuals","Misc","Config"};
	vec2 mouse_pos_()
	{
		POINT mouse_position;
		GetCursorPos(&mouse_position);
		ScreenToClient(FindWindow(0, "Counter-Strike: Global Offensive"), &mouse_position);
		return { static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y) };
	}
	bool mouse_in_params(int x, int y, int w, int h) {
		if (mouse_pos_().x > x&& mouse_pos_().y > y&& mouse_pos_().x < w + x && mouse_pos_().y < h + y)
			return true;
		return false;
	}
	void toggle_reset_key(const int vk1, const int vk2) {
		m_vk1 = vk1; m_vk2 = vk1;
	}
	void set_menu_name(std::string menu_name) {
		m_menuname = menu_name;
	}
	void init();
	void handle_input() {
		m_click = GetAsyncKeyState(VK_LBUTTON) ? true : false;

		static vec2 drag_pos = vec2(0, 0);
		static bool dragging = false, _static = false, pressed_index = false;
		int sizeoftab = sizeof(tabs) / sizeof(tabs[0]);

		if (!_static && GetAsyncKeyState(m_vk1))
			_static = true;
		else if (_static && !GetAsyncKeyState(m_vk1))
		{
			_static = false;
			m_opened = !m_opened;
		}
		else if (mouse_in_params(m_pos.x + m_size.x - 15, m_pos.y + 5, 8, 8) && m_click) {
			_static = false;
			m_opened = false;
		}

		if (dragging && !m_click)
			dragging = false;

		if (dragging && m_click)
			m_pos = mouse_pos_() - drag_pos;

		if (mouse_in_params(m_pos.x, m_pos.y, m_size.x, 15)) {
			dragging = true;
			drag_pos = mouse_pos_() - m_pos;
		}

		static bool pressed_neg = false, pressed_pos = false;
		if (!GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(m_pos.x + m_size.x - 95, m_pos.y + m_size.y - 7, 10, 10)) {
			if (pressed_neg && page_index > 0)
				page_index--;
			pressed_neg = false;
		}


		if (!GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(m_pos.x + m_size.x - 30, m_pos.y + m_size.y - 7, 10, 10)) {
			if (pressed_pos && page_index < tabs->size() - 1)
				page_index++;
			pressed_pos = false;
		}

		if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(m_pos.x + m_size.x - 95, m_pos.y + m_size.y - 7, 10, 10) && !pressed_neg)
			pressed_neg = true;
		if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(m_pos.x + m_size.x - 30, m_pos.y + m_size.y - 7, 10, 10) && !pressed_pos)
			pressed_pos = true;


	}
	void render() {
		render::get().draw_filled_rect(m_pos.x, m_pos.y, m_size.x, 20, color(40, 40, 40, 255));
		render::get().draw_x_rect(m_pos.x + m_size.x - 15, m_pos.y + 5, 8, 8, color(255, 255, 255, 255));
		render::get().draw_text(m_pos.x + 5, m_pos.y + 2, render::get().menu_font, m_menuname, false, color(255, 255, 255, 255));
		render::get().draw_filled_rect(m_pos.x, m_pos.y + 20, m_size.x, m_size.y, color(40, 40, 40, 215));
		render::get().draw_filled_rect(m_pos.x + 10, m_pos.y + 30, m_size.x - 20, m_size.y / 6, color(40, 40, 40, 255));
		render::get().draw_filled_rect(m_pos.x + 10, m_pos.y + m_size.y / 6 + 30, m_size.x - 20, m_size.y - (m_size.y / 6 + 20), color(20, 20, 20, 220));
		render::get().draw_text(m_pos.x + m_size.x - 60, m_pos.y + m_size.y - 12, render::get().menu_font, tabs[page_index], true, color(255, 255, 255, 255));
		render::get().draw_text(m_pos.x + m_size.x - 30, m_pos.y + m_size.y - 12, render::get().menu_font, ">", false, color(255, 255, 255, 255));
		render::get().draw_text(m_pos.x + m_size.x - 95, m_pos.y + m_size.y - 12, render::get().menu_font, "<", false, color(255, 255, 255, 255));
	}
	void draw();

};

namespace controls {
	class tab {
	public:
		vec2 m_tabpos = vec2(0, 0), m_optionpos = vec2(0, 0);
		tab(std::string name, bound _bound);
		void render(std::string name, bound _bound);
	public:
		virtual void checkbox(std::string name, bool *val);
		virtual void slider(std::string name, int *val, int min, int max);
	};
}