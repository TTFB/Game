#pragma once

#include <TTFB_Subscription.h>

void TTFB_Subscription::subscribe(std::function<void()> _onPublish) {
	subscribers.push_back(_onPublish);
}

void TTFB_Subscription::publish() {
	for(auto subscriber : subscribers){
		if(subscriber != nullptr){
			subscriber();
		}
	}
}