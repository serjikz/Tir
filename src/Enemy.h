#pragma once

class Enemy
{
public:
	typedef boost::shared_ptr<Enemy> HardPtr;
private:	
	const float MAX_SPEED = 200.f;
	const float FRICTION = 0.98f;
	const int TIME_TO_BOUNCE = 8;
	float _x, _y, _m;
	float _t;
	float _scale;
	float _angle;
	FPoint _speed;
	float _rotationSpeed;
	EffectsContainer _effCont;
	Render::Texture* _texture;
	FPoint _textureCenter;
	FPoint _vecMove;
	void checkScreenBounce();	
	bool _isBounced;
	int _health;
	Enemy::HardPtr _enemyLastBounced;
public:
	Enemy(rapidxml::xml_node<>* settings);
	void draw();
	void update(float dt);
	IRect getTextureRect() const;
	bool isIntersect(Enemy::HardPtr anotherEnemy);
	void bounceWith(Enemy::HardPtr anotherEnemy);
	FPoint getCenterPos() const;
	FPoint getMoveVec() const;
	float getScale() const;
	void setMoveVec(float x, float y);
	float getMass();
	void reduceHealth();
	int getHealth();
};

