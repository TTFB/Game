#pragma once

#include <functional>
#include <vector>

class TTFB_Subscription {
public:
	void subscribe(std::function<void()> _onPublish);
	void publish();
private:
	std::vector<std::function<void()>> subscribers;
};

