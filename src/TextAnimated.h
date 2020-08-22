#pragma once

class TextAnimated
{
private:	
	const float SPEED = 4.f;
	const float DELTA_SCALE = 0.05f;
	short int _x, _y;
	float _scale;
	float _t;
	std::string _text;
public:
	TextAnimated(const std::string& text, int x, int y);
	typedef boost::shared_ptr<TextAnimated> HardPtr;
	void draw();
	void update(float dt);
};