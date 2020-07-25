#pragma once

class Enemy
{
private:	
	float _x, _y, _m;
	FPoint _speed;
	EffectsContainer _effCont;
	Render::Texture* _texture;
	FPoint _textureCenter;
	FPoint _vecMove;
	void checkScreenBounce();
	float _t;
	bool _isBounced;
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
	void setMoveVec(float x, float y);
	float getMass();
};

