#pragma once

#include <TTFB_ResourceManager.h>

Scenario * TTFB_ResourceManager::scenario = nullptr;

void TTFB_ResourceManager::init(){
	scenario = new Scenario("assets/scenario.json");
	resources.push_back(scenario);
}