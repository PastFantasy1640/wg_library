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
			///		���C���[�̊Ǘ����s���N���X�B
			///		�g�p�󋵂�������Ȃ��������C���[�Ɋւ��āA
			///		�ǂ�����ł��A�N�Z�X���₷���悤�Ƀ|�C���^���Ǘ�����B
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