#pragma once

class Enemy
{
private:	
	float _x, _y, _m;
	float _t;
	float _scale;
	float _angle;
	FPoint _speed;
	float _rotationSpeed;
	int _rotateDirection;
	EffectsContainer _effCont;
	Render::Texture* _texture;
	FPoint _textureCenter;
	FPoint _vecMove;
	void checkScreenBounce();	
	bool _isBounced;
	int _health;
public:
	Enemy(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Enemy> HardPtr;
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

