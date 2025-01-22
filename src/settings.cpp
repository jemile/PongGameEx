#include <iostream>
#include <fstream>
#include <filesystem>

#include "settings.h"

using namespace::std;

// check if the settings path exists already this will be added somewhere else in the future
filesystem::path getDirectory()
{
	filesystem::path curPath = filesystem::current_path();

	if (!filesystem::exists(curPath / "settings"))
	{
		filesystem::create_directories(curPath / "settings");
	}

	return curPath / "settings";
}

// passes in settings from the frame so it uses the same logic, saves the variables to a file
void Settings::saveConfig(Settings setting, string configName)
{
	// this function will later take a second string to allow a user to create mutiple configs
	filesystem::path savePath = getDirectory() / "settings.ini";

	// output file
	ofstream configFile;
	configFile.open(savePath);

	// variables added to the config file
	if (configFile.is_open())
	{
		// booleans usually just give a 1 or 0 which would suffice but im using tertnary
		configFile << "settingOne:" << (setting.settingOne ? "true" : "false") << "\n";
		configFile << "settingTwo:" << (setting.settingTwo ? "true" : "false") << "\n";
		configFile << "settingThree:" << (setting.settingThree ? "true" : "false") << "\n";

		configFile.close();
	}

}

void Settings::loadConfig(Settings setting)
{

}