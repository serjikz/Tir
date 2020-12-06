#include "stdafx.h"

GameFieldWidget::GameFieldWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _blurEff(new BlurWidgetEffect())
	, _enemiesToHit(0)
	, _messenger(new Messenger())
	, _bkg(new Background())
{
	Xml::RapidXmlDocument settingsXml("Settings.xml");
	rapidxml::xml_node<>* root = settingsXml.first_node();
	_tank = Tank::HardPtr(new Tank(root));
	createNewEnemies();
	_gui = Interface::HardPtr(new Interface(root->first_node("GUI")));
}

void GameFieldWidget::Draw()
{
	if (_gui->getState() != InterfaceState::PLAY) {
		_blurEff->draw(_bkg, _enemies, _tank);		
	}
	else {
		_bkg->draw();
		if (_gui->getState() == InterfaceState::PLAY) {
			for (const auto &enemy: _enemies ) {
				enemy->draw();
			}
		}
		_tank->draw();
	}
	_gui->draw();
}

void GameFieldWidget::Update(float dt)
{
	_bkg->update(dt);
	_gui->update(dt);
	_tank->update(dt, _enemies);
	for (const auto& enemy : _enemies) {
		enemy->update(dt);
	}
	for (size_t i = 0; i < _enemies.size(); i++) {
		for (size_t j = i + 1; j < _enemies.size(); j++) {
			if (_enemies[i]->isIntersect(_enemies[j])) {
				_enemies[i]->bounceWith(_enemies[j]);
			}
		}
	} 
	// TODO:
	if (_gui->getState() == InterfaceState::PLAY) {
		if (_enemies.empty() && _gui->getTime() > 0) {
			Message msg = Message("ShowStats", "Victory");
			AcceptMessage(msg);
			return;
		}
	}
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
		if (_gui->getState() == InterfaceState::IS_OVER) {
			return;
		}
		_gui->setState(InterfaceState::IS_OVER); 
		std::string event = message.getData();
		std::string text;
		if (event == "TimeIsOver") {
			text = _messenger->getText("TIME_IS_OVER") + getTargetsLeft();
		} else if (event == "MissilesAreOver") {
			text = _messenger->getText("MISSILES_ARE_OVER") + getTargetsLeft();
		}
		else {
			text = _messenger->getText("CONGRATULATIONS");
		}
		_gui->setStatisticsMsg(text);
	} else if (message.is("Interface", "SetStateTapToPlay")) {
		_gui->setState(InterfaceState::TAP_TO_PLAY);
		createNewEnemies();
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

void GameFieldWidget::createNewEnemies() {
	// todo class factory?
	Xml::RapidXmlDocument tankSettingsXml("Settings.xml");
	rapidxml::xml_node<>* root = tankSettingsXml.first_node();
	rapidxml::xml_node<>* enemy = root->first_node("Enemies")->first_node("Enemy");
	_enemies.clear();
	_enemiesToHit = 0;
	size_t enemiesCount = InputFileReader::getInstance()->getEnemiesCount();
	while (enemy && _enemiesToHit < enemiesCount) {
		_enemies.push_back(Enemy::HardPtr(new Enemy(enemy)));
		enemy = enemy->next_sibling();
		_enemiesToHit++;
	}
	_tank->reloadRockets();
}

std::string GameFieldWidget:: getTargetsLeft() const {
	return std::to_string((size_t)_enemies.size()) + "/" + std::to_string(_enemiesToHit);
}