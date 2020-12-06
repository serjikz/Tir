#pragma once
#include "Tank.h"
#include "Cloud.h"
#include "Enemy.h"
#include "Interface.h"
#include "BkgConcreteCreators.h"
#include "Messenger.h"
///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///
class GameFieldWidget : public GUI::Widget
{
private:
	constexpr static int MIN_Y_SHOT = 50;
	Interface::HardPtr _gui;
	Tank::HardPrt _tank;
	std::vector <Enemy::HardPtr> _enemies;
	size_t _enemiesToHit;
	Render::Target* _targetX;
	Render::Target* _targetY;
	Render::ShaderProgramPtr _blurShaderX;
	Render::ShaderProgramPtr _blurShaderY;
	void initShaders();
	void createNewEnemies();
	void createBackground(rapidxml::xml_node<>* root);
	void drawWithBlur();
	std::string getTargetsLeft() const;
	std::vector<BkgObject::HardPtr> _backGround;
	Messenger::HardPtr _messenger;
public:
	GameFieldWidget(const std::string& name, rapidxml::xml_node<>* elem);
	void Draw() override;
	void Update(float dt) override;
	void AcceptMessage(const Message& message) override;
	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void KeyPressed(int keyCode) override;
};
