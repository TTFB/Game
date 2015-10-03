#pragma once

#include <TTFB_Subscription.h>

void TTFB_Subscription::subscribe(std::function<void()> _onPublish) {
	subscribers.push_back(_onPublish);
}

void TTFB_Subscription::publish() {
	for(unsigned long int i = 0; i < subscribers.size(); ++i){
		if(subscribers[i] != nullptr){
			subscribers[i]();
		}
	}
}