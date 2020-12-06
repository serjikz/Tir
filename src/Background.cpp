#include "stdafx.h"

Background::Background()
{
	Xml::RapidXmlDocument settingsXml("Settings.xml");
	rapidxml::xml_node<>* root = settingsXml.first_node();
	_bkgObjects.push_back((new BackgroundPictureCreator())->getObject());
	rapidxml::xml_node<>* cloud = root->first_node("Clouds")->first_node("Cloud");
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