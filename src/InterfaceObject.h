#pragma once


class InterfaceObject
{
protected:
	Render::Texture* _tex;
	short int _x, _y;
public:
	InterfaceObject()
		:_x(0),
		 _y(0)
	{};
	virtual void draw() = 0;
	virtual void update(float dt) {};
	typedef boost::shared_ptr<InterfaceObject> HardPtr;
};

                 