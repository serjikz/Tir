#pragma once
#include "Panel.h"
#include <ctime> 

// Панель отображения остатка снарядов
class MissilesPanel : public Panel
{
private:	
	std::string _text;
	short int _missilesAvailable;
	short int _missiles;
	short int _textX;
	short int _textY;
public:
	MissilesPanel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<MissilesPanel> HardPtr;
	virtual void draw();
	virtual void update(float dt);
	virtual void setState(InterfaceState newState);
	virtual void acceptVisitor(InterfaceObjVisitor::HardPtr visitor);
	void decreaseMissiles();
	int getRocketsCount();
};