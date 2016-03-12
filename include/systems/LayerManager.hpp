#pragma once

#ifndef WG_SYSTEMS_LAYERS_LAYERMANAGER_HPP
#define WG_SYSTEMS_LAYERS_LAYERMANAGER_HPP

#include <systems/Scene.hpp>
#include <string>

namespace wg {
	namespace systems {
		namespace layers {
			//static class
			/// <summary>
			///		レイヤーの管理を行うクラス。
			///		使用状況が分からない公式レイヤーに関して、
			///		どこからでもアクセスしやすいようにポインタを管理する。
			/// </summary>
			class LayerManager {
			private:
				struct _Lps {
					LayerBase * p;
					std::string n;
				};
				
				static std::vector<_Lps> _lsv;

			public:
				template<typename T>
				static inline T * get(const std::string name);
				static LayerBase * set(LayerBase * layer, std::string name);
				static void del(LayerBase * layer);
			};

			template <typename Of, typename What>
			inline bool instanceof(const What w)
			{
				return dynamic_cast<const Of*>(w) != 0;
			}
		};
	};
};

#endif /* --- end of LayerManager --- */