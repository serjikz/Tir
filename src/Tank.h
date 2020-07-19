#pragma once

class Tank
{
private:
	Render::Texture* _tank;
	short int _x, _y;
public:
	Tank();
	typedef boost::shared_ptr<Tank> HardPrt;
	void draw();
};

