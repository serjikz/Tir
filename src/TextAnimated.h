#pragma once

class TextAnimated
{
private:	
	short int _x, _y;
	std::string _text;
public:
	TextAnimated(const std::string& text, int x, int y);
	typedef boost::shared_ptr<TextAnimated> HardPtr;
	void draw();
	void update(float dt);
};