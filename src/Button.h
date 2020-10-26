#pragma once
#include "InterfaceObject.h"

class Button : public InterfaceObject
{
protected:	
	const float DELTA_SCALE = 0.05f;
	Render::Texture* _tex;
	float _scale;
	float _t;
	float _speed;
	FPoint _textureCenter;
public:
	enum class State {
		NORMAL,
		OVER
	} _state;
	Button(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Button> HardPtr;
	void draw();
	void update(float dt);
	void mouseDown(const IPoint& mouse_pos);
	void mouseMove(const IPoint& mouse_pos);
	void setState(State newState);
};