#include "MouseWheel.hpp"

int wg::io::MouseWheel::delta = 0;

void wg::io::MouseWheel::_Event(const int delta)
{
	MouseWheel::delta = delta;
}

int wg::io::MouseWheel::get(void)
{
	int t = MouseWheel::delta;
	MouseWheel::delta = 0;
	return t;
}

