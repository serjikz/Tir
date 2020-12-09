#include "stdafx.h"

GameFieldWidget::GameFieldWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _gui(new Interface())
	, _tank(new Tank())
	, _blurEff(new BlurWidgetEffect())
	, _messenger(new Messenger())
	, _bkg(new Background())
	, _enemiesController(new EnemiesController())
{

}

void GameFieldWidget::Draw()
{
	if (_gui->getState() == InterfaceState::IS_OVER) {
		_blurEff->draw(_bkg, _enemiesController, _tank);
	}
	else {
		_bkg->draw();
		_enemiesController->draw();
		_tank->draw();
	}
	_gui->draw();
}

void GameFieldWidget::Update(float dt)
{
	_bkg->update(dt);
	_gui->update(dt);
	_tank->update(dt);
	_enemiesController->update(dt);
	checkMissilesHit();
	checkVictoryState();
}

bool GameFieldWidget::MouseDown(const IPoint &mouse_pos)
{
	switch (_gui->getState()) {
	case InterfaceState::TAP_TO_PLAY:
		_gui->setState(InterfaceState::PLAY);
		break;
	case InterfaceState::PLAY:
		if (mouse_pos.y > MIN_Y_SHOT) {
			_tank->shot();
			_gui->decreaseMissiles();
		}
		break;
	case InterfaceState::IS_OVER:
		_gui->mouseDown(mouse_pos);
		break;
	}
	return false;
}

void GameFieldWidget::MouseMove(const IPoint &mouse_pos) {
	if (_gui->getState() == InterfaceState::IS_OVER) {
		_gui->mouseMove(mouse_pos);
	}
}

void GameFieldWidget::AcceptMessage(const Message& message)
{	
	if (message.getPublisher() == "ShowStats") {
		_gui->setState(InterfaceState::IS_OVER); 
		std::string eventName = message.getData();
		showStatistics(eventName);
	} else if (message.is("Interface", "SetStateTapToPlay")) {
		_gui->setState(InterfaceState::TAP_TO_PLAY);
		_enemiesController->createNewEnemies();
		_tank->reloadMissiles();
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
}

std::string GameFieldWidget::getTargetsLeft() const {
	int enemiesCount = _enemiesController->getObjects().size();
	size_t enemiesToHit = _enemiesController->getEnemiesToHit();
	return std::to_string(enemiesCount) + "/" + std::to_string(enemiesToHit);
}

void GameFieldWidget::showStatistics(const std::string& eventName) {
	std::string text;
	if (eventName == "TimeIsOver") {
		text = _messenger->getText("TIME_IS_OVER") + getTargetsLeft();
	}
	else if (eventName == "MissilesAreOver") {
		text = _messenger->getText("MISSILES_ARE_OVER") + getTargetsLeft();
	}
	else {
		text = _messenger->getText("CONGRATULATIONS");
	}
	_gui->setStatisticsMsg(text);
}

void GameFieldWidget::checkVictoryState() {
	if (_gui->getState() == InterfaceState::PLAY) {
		int enemiesCount = _enemiesController->getObjects().size();
		if (enemiesCount == 0 && _gui->getTime() > 0) {
			Message msg = Message("ShowStats", "Victory");
			AcceptMessage(msg);
		}
	}
}

void GameFieldWidget::checkMissilesHit() {
	_enemiesController->checkMissilesHit(_tank->getMissiles());
}