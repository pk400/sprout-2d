#include "src/Game.hpp"
#include "src/tinytoml/toml.h"
#include <fstream>
#include <unistd.h>

// Main entry-point to initialize game and load settings.
int main() {
	Settings settings;

	// Read settings from configuration file.
	// File location is relative to the location of the binary after
	// running make.
	std::ifstream ifs("../config.toml");
	toml::ParseResult pr = toml::parse(ifs);

	if (!pr.valid()) {
	    std::cout << pr.errorReason << std::endl;
	    return 0;
	}

	const toml::Value& config_data = pr.value;

	settings.title = (config_data.find("game.title"))->as<string>();
	settings.debug = (config_data.find("game.debug"))->as<bool>();
	settings.width = (config_data.find("game.width"))->as<int>();
	settings.height = (config_data.find("game.height"))->as<int>();
	settings.frame_rate = (config_data.find("game.frame_rate"))->as<int>();
	settings.vertical_sync = (config_data.find("game.vertical_sync"))->as<bool>();

	// Initialize game variables with setting variables
    Game game(settings);

    // Setup screen with values from settings
    game.setup();

    return game.gameRun();
}