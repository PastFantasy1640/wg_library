#pragma once

#ifndef WG_IO_MOUSEWHEEL_HPP
#define WG_IO_MOUSEWHEEL_HPP

namespace wg {
	namespace io {
		class MouseWheel {
		public:
			static void _Event(const int delta);
			static int get(void);
		private:
			static int delta;
		};
	};
};

#endif