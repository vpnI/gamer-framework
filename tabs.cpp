#include "../menu.h"

///////////////////////////////////////////////////////////////////
controls::tab::tab(std::string name, bound _bound) {
	m_tabpos = vec2(menu::get().m_pos.x + _bound.x, menu::get().m_pos.y + _bound.y);
	m_optionpos = vec2(m_tabpos.x - 60, m_tabpos.y + 20);
	render(name, _bound);
}

void controls::tab::render(std::string name, bound _bound) {

	auto bruh = render::get().GetTextSize2(render::get().menu_font, name.c_str());
	render::get().draw_filled_rect(m_tabpos.x - 71, m_tabpos.y - 1, _bound.w + 2, _bound.h + 2, color(0, 0, 0, 220));
	render::get().draw_filled_rect(m_tabpos.x - 70, m_tabpos.y, _bound.w, _bound.h, color(40, 40, 40, 220));
	render::get().draw_filled_rect(m_tabpos.x - 77 + bruh.left, m_tabpos.y - 1, bruh.left, 1, color(40, 40, 40, 220));
	render::get().draw_text(m_tabpos.x + 25, m_tabpos.y - 7, render::get().menu_font, name, true, color(255, 255, 255, 220));
}

void controls::tab::checkbox(std::string name, bool * val) {

	static bool clicked = false;

	if (!GetAsyncKeyState(VK_LBUTTON) && menu::get().mouse_in_params(m_optionpos.x, m_optionpos.y, 180, 15)) {
		if (clicked)
			*val = !*val;
		clicked = false;
	}

	if (GetAsyncKeyState(VK_LBUTTON) && menu::get().mouse_in_params(m_optionpos.x, m_optionpos.y, 180, 15) && !clicked)
		clicked = true;

	render::get().draw_filled_rect(m_optionpos.x - 1, m_optionpos.y - 1, 11, 11, color(80, 80, 80, 255));
	render::get().draw_filled_rect(m_optionpos.x, m_optionpos.y, 9, 9, color(20, 20, 20, 220));
	render::get().draw_filled_rect(m_optionpos.x + 1, m_optionpos.y + 1, 7, 7, *val ? color(255, 240, 240, 255) : color(20, 20, 20, 220));

	render::get().draw_text(m_optionpos.x + 20, m_optionpos.y - 3, render::get().menu_font, name, false, color(255, 255, 255, 220));
	m_optionpos.y += 20;
}

void controls::tab::slider(std::string name, int *val, int min, int max) {

	float size = 150;
	float real_size = max / size;

	if (*val > max)
		*val = max;
	else if (val < 0)
		val = 0;

	if (GetAsyncKeyState(VK_LBUTTON) && menu::get().mouse_in_params(m_optionpos.x + 20, m_optionpos.y + 15, size + 1, 15)) // shrugggh
		*val = abs(menu::get().mouse_pos_().x - (m_optionpos.x + 20)) * real_size;

	render::get().draw_filled_rect(m_optionpos.x + 20, m_optionpos.y + 20, 150, 3, color(80, 80, 80, 255));
	render::get().draw_filled_rect(m_optionpos.x + 20, m_optionpos.y + 20, (*val / real_size), 3, color(255, 240, 240, 255));
	render::get().draw_filled_outlined_rect(m_optionpos.x + 18 + (*val / real_size), m_optionpos.y + 20, 3, 3, color(255, 240, 240, 255), color(20, 20, 20, 255));
	render::get().draw_filled_rect(m_optionpos.x + 19 + (*val / real_size), m_optionpos.y + 20, 1, 3, color(20, 20, 20, 255));
	render::get().draw_text(m_optionpos.x + 20, m_optionpos.y - 3, render::get().menu_font, name, false, color(240, 240, 240, 220));
	render::get().draw_text(m_optionpos.x + 150, m_optionpos.y - 3, render::get().menu_font, std::to_string( *val ), false, color(240, 240, 240, 220));
	m_optionpos.y += 34;
}
