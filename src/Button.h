#pragma once

class Button
{
protected:	
	const float DELTA_SCALE = 0.05f;
	Render::Texture* _tex;
	short int _x, _y;
	float _scale;
	float _t;
	float _speed;
	FPoint _textureCenter;
	enum class State {
		NORMAL,
		OVER
	} _state;
public:
	Button(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Button> HardPtr;
	void draw();
	void update(float dt);
	void mouseDown(const IPoint& mouse_pos);
	void mouseMove(const IPoint& mouse_pos);
};