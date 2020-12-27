#pragma once
#include <map>

// Данный класс обеспечивает создание текстовых сообщений в окне статистики

class Messenger
{
	const std::string INPUT_FILE = "Messages.xml";
	std::map<std::string, std::string> _map;
public:
	Messenger();
	const std::string& getText(const std::string& id) const;
	typedef boost::shared_ptr<Messenger> HardPtr;
};

