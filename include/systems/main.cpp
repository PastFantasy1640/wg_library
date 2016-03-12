#include "systems/WG_systems.hpp"
#include <SFML/Graphics.hpp>
#include "GameMain.hpp"

using namespace wg;

int main(int argc, char* argv[]) {

	//ウィンドウ設定
	systems::Scene::Init(new warships::TitleScene());

	//最初に起動するのはTitle
	systems::Scene::Process();
	
	return 0;
}