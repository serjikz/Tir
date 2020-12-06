#pragma once
#include "stdafx.h"

XmlSettings::HardPtr XmlSettings::xmlSettings_ = nullptr;

XmlSettings::XmlSettings()
	:_doc(INPUT_FILE_NAME),
	_root(_doc.first_node()),
	_enemyNode(_root->first_node(ENEMIES_NODE)->first_node(CONCRETE_ENEMY_NODE)),
	_guiNode(_root->first_node(GUI_NODE)),
	_tankNode(_root)
{
	
}

XmlSettings::HardPtr XmlSettings::getInstance() {
	if (xmlSettings_ == nullptr) {
		xmlSettings_ = XmlSettings::HardPtr(new XmlSettings());
	}
	return xmlSettings_;
}

rapidxml::xml_node<>* XmlSettings::getRoot() {
	return _root;
}

rapidxml::xml_node<>* XmlSettings::getEnemiesNode() {
	return _enemyNode;
}

rapidxml::xml_node<>* XmlSettings::getGUINode() {
	return _guiNode;
}

rapidxml::xml_node<>* XmlSettings::getTankNode() {
	return _tankNode;
}