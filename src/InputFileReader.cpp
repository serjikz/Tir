#pragma once
#include "stdafx.h"

InputFileReader::HardPtr InputFileReader::inputFileReader_ = nullptr;

InputFileReader::InputFileReader()
	:_countEnemies(1),
	_speed(500),
	_time(20),
	_missiles(5)
{
	std::ifstream file(INPUT_FILE_NAME);
	size_t enemies = 0;
	if (file.is_open())
	{
		_countEnemies = math::clamp((size_t)0, MAX_ENEMIES_COUNT, getParamValue(file, COUNT_ENEMIES));
		_speed = getParamValue(file, SPEED);
		_time = getParamValue(file, TIME);
		_missiles = getParamValue(file, MISSILES);
		file.close();
	}
	else {
		assert(false);
	}
}

size_t InputFileReader::getParamValue(std::ifstream& file, const std::string& paramName){
	// Поиск нужного параметра в файле
	std::string params;
	while (getline(file, params)) {
		if (params.substr(0, paramName.length()) == paramName) {
			return stoi(params.substr(paramName.length(), params.length() - 1));
		}
	}
	assert(false);
}

InputFileReader::HardPtr InputFileReader::getInstance() {
	if (inputFileReader_ == nullptr) {
		inputFileReader_ = InputFileReader::HardPtr(new InputFileReader());
	}
	return inputFileReader_;
}