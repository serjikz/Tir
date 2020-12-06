#pragma once

// singleton
class XmlSettings
{
	const std::string INPUT_FILE_NAME = "Settings.xml";
	const char* ENEMIES_NODE = "Enemies";
	const char* CONCRETE_ENEMY_NODE = "Enemy";
	const char* GUI_NODE = "GUI";
	const char* TANK_NODE = "Tank";
	Xml::RapidXmlDocument _doc;
	rapidxml::xml_node<>* _root;
	rapidxml::xml_node<>* _enemyNode;
	rapidxml::xml_node<>* _guiNode;
	rapidxml::xml_node<>* _tankNode;
public:
	typedef boost::shared_ptr<XmlSettings> HardPtr;
protected:
	XmlSettings();
	static XmlSettings::HardPtr xmlSettings_;
public:
	XmlSettings(InputFileReader& other) = delete;
	void operator = (const XmlSettings&) = delete;
	static XmlSettings::HardPtr getInstance();
	rapidxml::xml_node<>* getRoot();
	rapidxml::xml_node<>* getEnemiesNode();
	rapidxml::xml_node<>* getGUINode();
	rapidxml::xml_node<>* getTankNode();

};
