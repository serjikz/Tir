#pragma once
#include "IntObjVisitor.h"

enum class InterfaceState {
	TAP_TO_PLAY,
	PLAY,
	IS_OVER
};

class InterfaceObject
{
protected:
	Render::Texture* _tex;
	short int _x, _y;
	float _direction;
	enum class State {
		HIDEN,
		NORMAL,
		APEARENCE,
		DISSAPEARENCE
	} _state;
public:
	InterfaceObject()
		:_x(0),
		 _y(0),
		_tex(0)
	{};
	virtual void draw() = 0;
	virtual void setState(InterfaceState newState) = 0;
	virtual void acceptVisitor(InterfaceObjVisitor::HardPtr visitor) {};
	virtual void update(float dt) {};
	typedef boost::shared_ptr<InterfaceObject> HardPtr;
};

