#pragma once

#ifndef WG_OBJECT2D_SCRIPT_HPP
#define WG_OBJECT2D_SCRIPT_HPP

#include "SFML/Graphics.hpp"
#include "Bezier2D.hpp"
//#include "Object2D.hpp"
#include <vector>



namespace wg {
	namespace object2D {


		class TimeLine {
		public:
			sf::Clock * script_start_time;
			std::vector<sf::Texture *> * tex;
			sf::Sprite * sp_lp;
			unsigned int id;
			void Update();
		};


		namespace script {
			class Speed : public wg::object2D::Bezier2D3 {
			public:
				Speed();
				Speed(double s_power, double s_rate, double e_power, double e_rate);
				virtual ~Speed();
				void setSpeed(double s_power, double s_rate, double e_power, double e_rate);
				static const Speed Lerp;
			};
		}


		class Script {
		private:

			//bool is_init;
			
		protected:
			unsigned int time_ms;	//èäóvéûä‘
			unsigned int start_ms;
			unsigned int id;

		public:

			Script();
			//Script(const Script & copy);
			virtual ~Script();
			virtual void setSpriteAttribute(std::vector<wg::object2D::TimeLine> * tl) = 0;

		
			unsigned int getID(void) const;
		};

		namespace script {

			class Texture : public Script {
			private:
				std::size_t texture_no;

			public:
				Texture();
				Texture(const unsigned int id, const unsigned int start_ms, const unsigned int time_ms, size_t texture_no);
				virtual ~Texture();

				void set(const unsigned int id, const unsigned int start_ms, const unsigned int time_ms, size_t texture_no);
				virtual void setSpriteAttribute(std::vector<wg::object2D::TimeLine> * tl) override;
			};

			class Position : public Script {
			private:
				wg::object2D::Bezier2D3 pos;
				wg::object2D::script::Speed sp;
			public:
				Position();
				Position(const unsigned int id, const unsigned int start_ms, unsigned int time_ms, const wg::object2D::Bezier2D3 positions, const wg::object2D::script::Speed speed = wg::object2D::script::Speed::Lerp);
				virtual ~Position();

				void set(const unsigned int id, const unsigned int start_ms, unsigned int time_ms, const wg::object2D::Bezier2D3 positions, const wg::object2D::script::Speed speed = wg::object2D::script::Speed::Lerp);
				virtual void setSpriteAttribute(std::vector<wg::object2D::TimeLine> * tl) override;
			};

			class Rotation : public Script {
			private:
			public:
				Rotation();
				virtual ~Rotation();

				void set(const unsigned int id, const unsigned int start_ms, unsigned int time_ms, const float s_degree, const float e_degree, const wg::object2D::script::Speed speed = wg::object2D::script::Speed::Lerp);
				virtual void setSpriteAttribute(std::vector<wg::object2D::TimeLine> * tl) override;
			};

			class Expansion : public Script {
			private:
			public:
				Expansion();
				virtual ~Expansion();

				void set(const unsigned int id, const unsigned int start_ms, unsigned int time_ms, const double s_ex, const double e_ex, const wg::object2D::script::Speed speed = wg::object2D::script::Speed::Lerp);
				virtual void setSpriteAttribute(std::vector<wg::object2D::TimeLine> * tl) override;
			};


			class Repeat : public Script {
			private:
			public:
				Repeat();
				Repeat(const unsigned int id, const unsigned int start_ms);
				virtual ~Repeat();

				void set(const unsigned int id, const unsigned int start_ms);
				virtual void setSpriteAttribute(std::vector<wg::object2D::TimeLine> * tl) override;
			};

			class Stop : public Script {
			private:
				unsigned int target_id;
			public:
				Stop();
				virtual ~Stop();

				void set(const unsigned int id, const unsigned int start_ms, const unsigned int target_id);
				virtual void setSpriteAttribute(std::vector<wg::object2D::TimeLine> * tl) override;

			};

			class Start : public Script {
			private:
				unsigned int target_id;
			public:
				Start();
				virtual ~Start();

				void set(const unsigned int id, const unsigned int start_ms, const unsigned int target_id);
				virtual void setSpriteAttribute(std::vector<wg::object2D::TimeLine> * tl) override;

			};


		}
	}
}

#endif