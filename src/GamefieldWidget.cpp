#include "stdafx.h"
#include "GameFieldWidget.h"

GameFieldWidget::GameFieldWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _curTex(0)
	, _timer(0)
	, _angle(0)
	, _eff(NULL)
	, _scale(0.f)
	, _enemiesToHit(0)
{
	Init();
}

void GameFieldWidget::Init()
{
	_tank = Tank::HardPrt(new Tank());
	_bkg = Core::resourceManager.Get<Render::Texture>("Background");
	_curTex = 0;
	_angle = 0;

	spline.addKey(0.0f, FPoint(100.0f, 100.0f));
	spline.addKey(0.25f, FPoint(150.0f, 300.0f));
	spline.addKey(0.5f, FPoint(500.0f, 300.0f));
	spline.addKey(0.75f, FPoint(630.0f, 450.0f));
	spline.addKey(1.0f, FPoint(600.0f, 550.0f));
	spline.CalculateGradient();

	Xml::RapidXmlDocument tankSettingsXml("Settings.xml");
	rapidxml::xml_node<>* root = tankSettingsXml.first_node();
	rapidxml::xml_node<>* cloud = root->first_node("Clouds")->first_node("Cloud");
	while (cloud) {
		_clouds.push_back(Cloud::HardPtr(new Cloud(cloud)));
		cloud = cloud->next_sibling();
	}
	rapidxml::xml_node<>* enemy = root->first_node("Enemies")->first_node("Enemy");
	while (enemy) {
		_enemies.push_back(Enemy::HardPtr(new Enemy(enemy)));
		enemy = enemy->next_sibling();
		_enemiesToHit++;
	}
	_gui = Interface::HardPtr(new Interface(root->first_node("GUI")));
	_gui->setState(Interface::State::TAP_TO_PLAY);
} 

void GameFieldWidget::Draw()
{
	_bkg->Draw();
	for (int i = 0; i < (int)_clouds.size(); i++) {
		_clouds[i]->draw();
	}
	_effCont.Draw();
	
	switch (_gui->getState()) {
	case Interface::State::TAP_TO_PLAY:

		break;
	case Interface::State::PLAY:
		for (int i = 0; i < (int)_enemies.size(); i++) {
			_enemies[i]->draw();
		}
		break;
	case Interface::State::IS_OVER:

		break;
	}
	_tank->draw();
	_gui->draw();
}

void GameFieldWidget::Update(float dt)
{
	_effCont.Update(dt);
	for (int i = 0; i < (int)_clouds.size(); i++) {
		_clouds[i]->update(dt);
	}
	
	_gui->update(dt);
	switch (_gui->getState()) {
	case Interface::State::TAP_TO_PLAY:

		break;
	case Interface::State::PLAY:
		for (int i = 0; i < (int)_enemies.size(); i++) {
			_enemies[i]->update(dt);
		}
		_tank->update(dt, _enemies);
		for (int i = 0; i < (int)_enemies.size(); i++) {
			for (int j = i + 1; j < (int)_enemies.size(); j++) {
				if (_enemies[i]->isIntersect(_enemies[j])) {
					_enemies[i]->bounceWith(_enemies[j]);
				}
			}
		}
		break;
	case Interface::State::IS_OVER:

		break;
	}
}

bool GameFieldWidget::MouseDown(const IPoint &mouse_pos)
{
	switch (_gui->getState()) {
	case Interface::State::TAP_TO_PLAY:
		_gui->setState(Interface::State::PLAY);
		break;
	case Interface::State::PLAY:
		_tank->shot();
		break;
	case Interface::State::IS_OVER:

		break;
	}
	return false;
}

void GameFieldWidget::MouseMove(const IPoint &mouse_pos)
{
}

void GameFieldWidget::MouseUp(const IPoint &mouse_pos)
{
	if (_eff)
	{
		//
		// Если эффект создан, то при отпускании мыши завершаем его.
		//
		_eff->Finish();
		_eff = NULL;
	}
}

void GameFieldWidget::AcceptMessage(const Message& message)
{
	if (message.is("Interface", "TimeIsOver")) {
		_gui->setState(Interface::State::IS_OVER);
		_gui->showStatistics("TIME IS OVER!\n\nYour score is: \n\nTargets left to hit: " + 
			std::to_string((int) _enemies.size()) + "/" + std::to_string(_enemiesToHit));
	}
}

void GameFieldWidget::KeyPressed(int keyCode)
{	
	if (keyCode == VK_LEFT || keyCode == VK_A) {
		_tank->moveLeft();
	}
	else if (keyCode == VK_RIGHT || keyCode == VK_D) {
		_tank->moveRight();
	}
	else if (keyCode == VK_ESCAPE) {
		_gui->setState(Interface::State::IS_OVER);
	}
	else if (keyCode == VK_1) {
		_gui->setState(Interface::State::TAP_TO_PLAY);
	}
}

void GameFieldWidget::CharPressed(int unicodeChar)
{

}
