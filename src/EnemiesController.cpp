#pragma once
#include "stdafx.h"

EnemiesController::EnemiesController()
	:_enemiesToHit(0)
{
	createNewEnemies();
}

void EnemiesController::createNewEnemies() {
	_enemies.clear();
	_enemiesToHit = 0;
	rapidxml::xml_node<>* enemy = XmlSettings::getInstance()->getEnemiesNode();
	size_t enemiesCount = InputFileReader::getInstance()->getEnemiesCount();
	while (enemy && _enemiesToHit < enemiesCount) {
		_enemies.push_back(Enemy::HardPtr(new Enemy(enemy)));
		enemy = enemy->next_sibling();
		_enemiesToHit++;
	}
}

void EnemiesController::update(float dt) {
	for (const auto& enemy : _enemies) {
		enemy->update(dt);
	}
	_effCont.Update(dt);
	checkEnemiesCollision();
}

void EnemiesController::draw() {
	for (const auto& enemy : _enemies) {
		enemy->draw();
	}
	_effCont.Draw();
}

void EnemiesController::checkEnemiesCollision() {
	for (size_t i = 0; i < _enemies.size(); i++) {
		for (size_t j = i + 1; j < _enemies.size(); j++) {
			if (_enemies[i]->isIntersect(_enemies[j])) {
				_enemies[i]->bounceWith(_enemies[j]);
			}
		}
	}
}

const std::vector <Enemy::HardPtr>& EnemiesController::getObjects() const {
	return _enemies;
}

void EnemiesController::checkMissilesHit(std::vector<Missile::HardPtr>& missiles) {
	for (auto missilesIt = missiles.begin(); missilesIt != missiles.end();) {
		tryHitSomeEnemy((*missilesIt));
		missilesIt++;
	}		
}

void EnemiesController::tryHitSomeEnemy(Missile::HardPtr& missile) {
	for (auto enemiesIt = _enemies.begin(); enemiesIt != _enemies.end();) {
		FPoint interactionVec = missile->getCenterPos() - (*enemiesIt)->getCenterPos();
		float sqrLen = pow(interactionVec.x, 2) + pow(interactionVec.y, 2);
		float r = missile->getTextureHeight() / 2.f + (*enemiesIt)->getTextureRect().Width() / 2.f;
		if (sqrLen < r * r) {
			missile->bounceWith(*enemiesIt);
			(*enemiesIt)->reduceHealth();
			if ((*enemiesIt)->getHealth() <= 0) {
				FPoint enemyPos = (*enemiesIt)->getCenterPos();
				explodeEnemy(enemyPos);
				enemiesIt = _enemies.erase(enemiesIt);
			}
			explodeMissile(missile->getCenterPos());
			return;
		}
		else {
			enemiesIt++;
		}
	}
}

void EnemiesController::explodeEnemy(const FPoint& pos) {
	_eff = _effCont.AddEffect(ENEMY_EXPL_EFF);
	_eff->posX = pos.x;
	_eff->posY = pos.y;
	_eff->Reset();
}

void EnemiesController::explodeMissile(const FPoint& pos) {
	_eff = _effCont.AddEffect(MISSILE_EXPL_EFF);
	_eff->posX = pos.x;
	_eff->posY = pos.y;
	_eff->Reset();
}

size_t EnemiesController::getEnemiesToHit() {
	return _enemiesToHit;
}

