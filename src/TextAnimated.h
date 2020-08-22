#pragma once

class TextAnimated
{
private:	
	Render::Texture* _tex;
	short int _x, _y;
	std::string _text;
public:
	TextAnimated(std::string text, int x, int y);
	typedef boost::shared_ptr<TextAnimated> HardPtr;
	void draw();
	void update(float dt);
};