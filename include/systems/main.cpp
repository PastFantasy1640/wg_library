#include "systems/WG_systems.hpp"
#include <SFML/Graphics.hpp>
#include "GameMain.hpp"

using namespace wg;

int main(int argc, char* argv[]) {

	//�E�B���h�E�ݒ�
	systems::Scene::Init(new warships::TitleScene());

	//�ŏ��ɋN������̂�Title
	systems::Scene::Process();
	
	return 0;
}