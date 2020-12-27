#pragma once
#include "stdafx.h"

Messenger::Messenger() {
	// Формируем библиотеку сообщений
	Xml::RapidXmlDocument settingsXml(INPUT_FILE);
	rapidxml::xml_node<>* root = settingsXml.first_node();
	rapidxml::xml_node<>* msg = root->first_node("Msg");
	while (msg) {
		std::string id = Xml::GetStringAttribute(msg, "id");
		std::string text = Xml::GetStringAttribute(msg, "text");
		_map.insert({id, text});
		msg = msg->next_sibling();
	}
}

const std::string& Messenger::getText(const std::string& id) const {
	// Поиск нужного сообщения по id
	auto search = _map.find(id);
	if (search != _map.end()) {
		return search->second;
	}
	else {
		assert(false);
	}
}