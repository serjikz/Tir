#pragma once

class Enemy
{
private:	
	float _x, _y;
	EffectsContainer _effCont;
	Render::Texture* _texture;
	FPoint _textureCenter;
	FPoint _vecMove;
	void checkGameFieldCollision();
public:
	Enemy(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Enemy> HardPtr;
	void draw();
	void update(float dt);
};

