#pragma once

struct Settings {
	bool settingOne = false;
	bool settingTwo = false;
	bool settingThree = false;

	void saveConfig(Settings setting, std::string configName);
	void loadConfig(Settings setting);
};