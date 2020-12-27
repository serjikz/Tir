#include "stdafx.h"

Background::Background()
{
	// Создаем фон
	_bkgObjects.push_back((new BackgroundPictureCreator())->getObject());
	rapidxml::xml_node<>* cloud = XmlSettings::getInstance()->getCloudsNode();
	while (cloud) {
		_bkgObjects.push_back((new CloudCreator(cloud))->getObject());
		cloud = cloud->next_sibling();
	}
}

void Background::draw() {
	for (const auto& bkgObj : _bkgObjects) {
		bkgObj->draw();
	}
}

void Background::update(float dt) {
	for (const auto& bkgObj : _bkgObjects) {
		bkgObj->update(dt);
	}
}