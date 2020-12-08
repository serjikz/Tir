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

void EnemiesController::checkMissilesHit(std::vector<Missile::HardPtr> missiles) {
	for (auto missilesIt = missiles.begin(); missilesIt != missiles.end(); missilesIt++) {
		for (auto enemiesIt = _enemies.begin(); enemiesIt != _enemies.end();) {
			FPoint interactionVec = (*missilesIt)->getCenterPos() - (*enemiesIt)->getCenterPos();
			float sqrLen = pow(interactionVec.x, 2) + pow(interactionVec.y, 2);
			float r = (*missilesIt)->getTextureHeight() / 2.f + (*enemiesIt)->getTextureRect().Width() / 2.f;
			if (sqrLen < r * r) {
				(*missilesIt)->bounceWith(*enemiesIt);
				(*enemiesIt)->reduceHealth();
				if ((*enemiesIt)->getHealth() <= 0) {
					FPoint enemyPos = (*enemiesIt)->getCenterPos();
					explode(enemyPos);
					enemiesIt = _enemies.erase(enemiesIt);
				}
				else {
					enemiesIt++;
					//? in missile? _missileExplEff->reset(this->getCenterPos().x, this->getCenterPos().y);
				}
			}
			else {
				enemiesIt++;
			}
		}
	}
}

void EnemiesController::explode(const FPoint& pos) {
	_eff = _effCont.AddEffect(ENEMY_EXPL_EFF);
	_eff->posX = pos.x;
	_eff->posY = pos.y;
	_eff->Reset();
}