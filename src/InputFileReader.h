#pragma once

// Данный класс обеспечивает считывание входных параметров из файла .txt
// Создается в единственном экземпляре
class InputFileReader
{
	const std::string INPUT_FILE_NAME = "input.txt";
	const std::string COUNT_ENEMIES = "CountTarget=";
	const std::string SPEED = "Speed=";
	const std::string TIME = "Time=";
	const std::string MISSILES = "Missiles=";
	constexpr static size_t MAX_ENEMIES_COUNT = 50;
	size_t _countEnemies;
	size_t _speed;
	size_t _time;
	size_t _missiles;
	size_t getParamValue(std::ifstream& file, const std::string& paramName);
public:
	typedef boost::shared_ptr<InputFileReader> HardPtr;
protected:
	InputFileReader();
	static InputFileReader::HardPtr inputFileReader_;
public:
	InputFileReader(InputFileReader& other) = delete;
	void operator = (const InputFileReader&) = delete;
	static InputFileReader::HardPtr getInstance();
	size_t getEnemiesCount() { return _countEnemies; }
	size_t getMissileSpeed() { return _speed; }
	size_t getGameTime() { return _time; }
	size_t getMissilesAvailable() { return _missiles; }
};
