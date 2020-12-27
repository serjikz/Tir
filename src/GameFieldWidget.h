#pragma once
#include "Tank.h"
#include "Cloud.h"
#include "EnemiesController.h"
#include "Interface.h"
#include "BkgConcreteCreators.h"
#include "Messenger.h"
#include "BlurWidgetEffect.h"
#include "Background.h"
///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///
class GameFieldWidget : public GUI::Widget
{
private:
	constexpr static int MIN_Y_SHOT = 50;
	Interface::HardPtr _gui;
	Tank::HardPtr _tank;
	BlurWidgetEffect::HardPtr _blurEff;
	Messenger::HardPtr _messenger;
	Background::HardPtr _bkg;
	EnemiesController::HardPtr _enemiesController;
	std::string getTargetsLeft() const;
	void showStatistics(const std::string& eventName);
	void checkVictoryState();
	void checkMissilesHit();
public:
	GameFieldWidget(const std::string& name, rapidxml::xml_node<>* elem);
	void Draw() override;
	void Update(float dt) override;
	void AcceptMessage(const Message& message) override;
	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void KeyPressed(int keyCode) override;
};
