#include "stdafx.h"
#include "GameFieldWidget.h"

GameFieldWidget::GameFieldWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _curTex(0)
	, _timer(0)
	, _angle(0)
	, _eff(NULL)
	, _scale(0.f)
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
	}
} 

void GameFieldWidget::Draw()
{
	_bkg->Draw();
	for (int i = 0; i < (int)_clouds.size(); i++) {
		_clouds[i]->draw();
	}
		
	_effCont.Draw();
	for (int i = 0; i < (int)_enemies.size(); i++) {
		_enemies[i]->draw();
	}
	_tank->draw();
}

void GameFieldWidget::Update(float dt)
{
	_effCont.Update(dt);
	for (int i = 0; i < (int)_clouds.size(); i++) {
		_clouds[i]->update(dt);
	}
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

	//
	// dt - значение времени в секундах, прошедшее от предыдущего кадра.
	// Оно может принимать разные значения, в зависимости от производительности системы
	// и сложности сцены.
	//
	// Для того, чтобы наша анимация зависела только от времени, и не зависела от
	// производительности системы, мы должны рассчитывать её от этого значения.
	//
	// Увеличиваем наш таймер с удвоенной скоростью.
	//
	_timer += dt * 2;
	
	//
	// Зацикливаем таймер в диапазоне (0, 2п).
	// Это нужно делать для предотвращения получения некорректных значений,
	// если вдруг переполнится разрядная сетка (float переполнился) или задержка
	// от предыдущего кадра была слишкой большой (система тормози-и-ит).
	//
	// Диапазон значений выбран равным (0, 2п), потому что мы используем это значение
	// для расчёта синуса, и большие значения будут просто периодически повторять результат.
	//
	while (_timer > 2 * math::PI)
	{
		_timer -= 2 * math::PI;
	}
	
	//
	// Анимирование параметра масштабирования в зависимости от таймера.
	//
	_scale = 0.8f + 0.25f * sinf(_timer);
}

bool GameFieldWidget::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseRightButton())
	{
		//
		// При нажатии на правую кнопку мыши, создаём эффект шлейфа за мышкой.
		//
		_eff = _effCont.AddEffect("Iskra");
		_eff->posX = mouse_pos.x + 0.f;
		_eff->posY = mouse_pos.y + 0.f;
		_eff->Reset();
		
		//
		// И изменяем угол наклона текстуры.
		//
		_angle += 25;
		while (_angle > 360)
		{
			_angle -= 360;
		}
	}
	else
	{
		_tank->shot();
		//
		// При нажатии на левую кнопку мыши, создаём временный эффект, который завершится сам.
		//
		ParticleEffectPtr eff = _effCont.AddEffect("FindItem2");
		eff->posX = mouse_pos.x + 0.f;
		eff->posY = mouse_pos.y + 0.f;
		eff->Reset();

		//
		// Изменяем значение с 0 на 1 и наоборот.
		//
		_curTex = 1 - _curTex;
	}
	return false;
}

void GameFieldWidget::MouseMove(const IPoint &mouse_pos)
{
	if (_eff)
	{
		//
		// Если эффект создан, то перемещаем его в позицию мыши.
		//
		_eff->posX = mouse_pos.x + 0.f;
		_eff->posY = mouse_pos.y + 0.f;
	}
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
	//
	// Виджету могут посылаться сообщения с параметрами.
	//

	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();
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

void GameFieldWidget::CharPressed(int unicodeChar)
{

}
