#pragma once

#include <ResourceManager.h>
#include <scenario\Scenario.h>

class TTFB_ResourceManager : public ResourceManager{
public:
	static Scenario * scenario;
	static void init();
};