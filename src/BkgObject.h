#pragma once


class BkgObject
{
protected:
	Render::Texture* _tex;
	short int _x, _y;
public:
	BkgObject() {};
	virtual void draw() = 0;
	virtual void update(float dt) = 0;
	typedef boost::shared_ptr<BkgObject> HardPtr;
};
