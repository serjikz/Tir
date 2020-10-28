#pragma once
#include "Tank.h"
#include "Cloud.h"
#include "Enemy.h"
#include "Interface.h"
#include "BkgConcreteCreators.h"
///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///
class GameFieldWidget : public GUI::Widget
{
private:
	const int MIN_Y_SHOT = 50;
	const int MAX_ENEMIES_COUNT = 50;
	Interface::HardPtr _gui;
	Tank::HardPrt _tank;
	float _timer;
	float _scale;
	std::vector <Enemy::HardPtr> _enemies;
	int _enemiesToHit;
	Render::Target* _targetX;
	Render::Target* _targetY;
	Render::ShaderProgramPtr _blurShaderX;
	Render::ShaderProgramPtr _blurShaderY;
	void Init();
	void createNewEnemies();
	void drawWithBlur();
	std::vector<BkgObject::HardPtr> _backGround;
public:
	GameFieldWidget(const std::string& name, rapidxml::xml_node<>* elem);
	void Draw() override;
	void Update(float dt) override;
	void AcceptMessage(const Message& message) override;
	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void KeyPressed(int keyCode) override;
};
