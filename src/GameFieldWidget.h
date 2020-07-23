#pragma once
#include "Tank.h"
#include "Cloud.h"
#include "Enemy.h"
///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///
class GameFieldWidget : public GUI::Widget
{
private:
	Tank::HardPrt _tank;
	std::vector<Cloud::HardPtr> _clouds;
	float _timer;
	float _scale;
	float _angle;
	int _curTex;
	Render::Texture* _bkg;
	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
	TimedSpline<FPoint> spline;
	std::vector <Enemy::HardPtr> _enemies;
	void Init();
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
