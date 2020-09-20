#include "stdafx.h"
#include "GameFieldWidget.h"

GameFieldWidget::GameFieldWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _curTex(0)
	, _timer(0)
	, _angle(0)
	, _scale(0.f)
	, _enemiesToHit(0)
	, _targetX(0)
	, _targetY(0)
{
	Init();
}

void GameFieldWidget::Init()
{
	_bkg = Core::resourceManager.Get<Render::Texture>("Background");
	_curTex = 0;
	_angle = 0;
	Xml::RapidXmlDocument settingsXml("Settings.xml");
	rapidxml::xml_node<>* root = settingsXml.first_node();
	_tank = Tank::HardPrt(new Tank(root));
	rapidxml::xml_node<>* cloud = root->first_node("Clouds")->first_node("Cloud");
	while (cloud) {
		_clouds.push_back(Cloud::HardPtr(new Cloud(cloud)));
		cloud = cloud->next_sibling();
	}
	createNewEnemies();
	_gui = Interface::HardPtr(new Interface(root->first_node("GUI")));
	_gui->setState(Interface::State::TAP_TO_PLAY);
	std::string params;
	std::ifstream in("input.txt");
	std::string paramToFound = "Speed=";
	if (in.is_open())
	{
		while (getline(in, params)) {
			if (params.substr(0, std::string(paramToFound).length()) == paramToFound) {
				int speed = stoi(params.substr(paramToFound.length(), params.length() - 1));
				_tank->setMissileSpeed(speed);
			}
		}		
	}
	in.close();
	_targetX = Render::device.CreateRenderTarget(1024, 1024);
	_targetY = Render::device.CreateRenderTarget(1024, 1024);
	_blurShaderX = Core::resourceManager.Get<Render::ShaderProgram>("blurX");
	_blurShaderY = Core::resourceManager.Get<Render::ShaderProgram>("blurY");
} 

void GameFieldWidget::Draw()
{
	if (_gui->getState() != Interface::State::PLAY) {
		drawWithBlur();
	}
	else {

		_bkg->Draw();
		for (int i = 0; i < (int)_clouds.size(); i++) {
			_clouds[i]->draw();
		}
		_effCont.Draw();
		if (_gui->getState() == Interface::State::PLAY) {
			for (int i = 0; i < (int)_enemies.size(); i++) {
				_enemies[i]->draw();
			}
		}
		_tank->draw();
		_gui->draw();
	}
}
void GameFieldWidget::drawWithBlur() {
	Render::device.BeginRenderTo(_targetX);
	_bkg->Draw();
	for (int i = 0; i < (int)_clouds.size(); i++) {
		_clouds[i]->draw();
	}
	_effCont.Draw();
	if (_gui->getState() == Interface::State::IS_OVER) {
		for (int i = 0; i < (int)_enemies.size(); i++) {
			_enemies[i]->draw();
		}
	}
	_tank->draw();
	Render::device.EndRenderTo();
	Render::device.BeginRenderTo(_targetY);
	_blurShaderX->Bind();
	_targetX->Draw(FPoint(0.0, 0.0));
	_blurShaderX->Unbind();
	Render::device.EndRenderTo();
	_blurShaderY->Bind();
	_targetY->Draw(FPoint(0.0, 0.0));
	_blurShaderY->Unbind();
	_gui->draw();
}

void GameFieldWidget::Update(float dt)
{
	_effCont.Update(dt);
	for (int i = 0; i < (int)_clouds.size(); i++) {
		_clouds[i]->update(dt);
	}
	_gui->update(dt);
	_tank->update(dt, _enemies);
	//if (_gui->getState() == Interface::State::PLAY) {
		for (int i = 0; i < (int)_enemies.size(); i++) {
			_enemies[i]->update(dt);
		}
		if ((int)_enemies.size() == 0 && _gui->getTime() > 0) {
			Message msg = Message("Interface", "Victory");
			AcceptMessage(msg);
			return;
		}
		for (int i = 0; i < (int)_enemies.size(); i++) {
			for (int j = i + 1; j < (int)_enemies.size(); j++) {
				if (_enemies[i]->isIntersect(_enemies[j])) {
					_enemies[i]->bounceWith(_enemies[j]);
				}
			}
		} if (_tank->isAllRocketsExploaded()) {
			Message msg = Message(Message("Interface", "RocketsIsOver"));
			AcceptMessage(msg);
		}
	//}
}

bool GameFieldWidget::MouseDown(const IPoint &mouse_pos)
{
	switch (_gui->getState()) {
	case Interface::State::TAP_TO_PLAY:
		_gui->setState(Interface::State::PLAY);
		break;
	case Interface::State::PLAY:
		if (mouse_pos.y > MIN_Y_SHOT) {
			_tank->shot();
			_gui->decreaseRockets();
		}
		break;
	case Interface::State::IS_OVER:
		_gui->mouseDown(mouse_pos);
		break;
	}
	return false;
}

void GameFieldWidget::MouseMove(const IPoint &mouse_pos) {
	if (_gui->getState() == Interface::State::IS_OVER) {
		_gui->mouseMove(mouse_pos);
	}
}

void GameFieldWidget::AcceptMessage(const Message& message)
{
	if (message.is("Interface", "TimeIsOver")) {
		_gui->setState(Interface::State::IS_OVER);
		_gui->setStatisticsMsg("TIME IS OVER!\n\n\nTargets left to hit:\n" +
			std::to_string((int) _enemies.size()) + "/" + std::to_string(_enemiesToHit));
	} if (message.is("Interface", "RocketsIsOver")) {
		_gui->setState(Interface::State::IS_OVER);
		_gui->setStatisticsMsg("Rockets is over!\n\n\nTargets left to hit:\n" +
			std::to_string((int)_enemies.size()) + "/" + std::to_string(_enemiesToHit));
	}
	else if (message.is("Interface", "SetStateTapToPlay")) {
		_gui->setState(Interface::State::TAP_TO_PLAY);
		createNewEnemies();
	}
	else if (message.is("Interface", "Victory")) {
		_gui->setState(Interface::State::IS_OVER);
		_gui->setStatisticsMsg("CONGRATULATIONS!\n\nYou win!\n\nAll targets defeated");
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
	std::string params;
	std::ifstream in("input.txt"); 
	int enemies = 0;
	std::string paramToFound = "CountTarget=";
	if (in.is_open())
	{
		while (getline(in, params)) {
			if (params.substr(0, std::string(paramToFound).length()) == paramToFound) {
				enemies = math::clamp(0, MAX_ENEMIES_COUNT, stoi(params.substr(paramToFound.length(), params.length() - 1)));
			}
		}
	}
	in.close(); 
	Xml::RapidXmlDocument tankSettingsXml("Settings.xml");
	rapidxml::xml_node<>* root = tankSettingsXml.first_node();
	rapidxml::xml_node<>* enemy = root->first_node("Enemies")->first_node("Enemy");
	_enemies.clear();
	_enemiesToHit = 0;
	while (enemy && _enemiesToHit < enemies) {
		_enemies.push_back(Enemy::HardPtr(new Enemy(enemy)));
		enemy = enemy->next_sibling();
		_enemiesToHit++;
	}
	_tank->reloadRockets();
}