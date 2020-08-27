#pragma once
#include "Tank.h"
#include "Cloud.h"
#include "Enemy.h"
#include "Interface.h"
///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///
class GameFieldWidget : public GUI::Widget
{
private:
	Interface::HardPtr _gui;
	Tank::HardPrt _tank;
	std::vector<Cloud::HardPtr> _clouds;
	float _timer;
	float _scale;
	float _angle;
	int _curTex;
	Render::Texture* _bkg;
	EffectsContainer _effCont;
	std::vector <Enemy::HardPtr> _enemies;
	int _enemiesToHit;
	void Init();
	void createNewEnemies();
public:
	GameFieldWidget(const std::string& name, rapidxml::xml_node<>* elem);
	void Draw() override;
	void Update(float dt) override;
	void AcceptMessage(const Message& message) override;
	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;
	void KeyPressed(int keyCode) override;
	void CharPressed(int unicodeChar) override;
};
