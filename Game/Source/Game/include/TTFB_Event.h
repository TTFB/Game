#pragma once

#include<functional>

class TTFB_Event {
public:
	TTFB_Event(long _doAt, std::function<void()> _func);
	~TTFB_Event();

	void call();
	int  getFuncCallCount();	
	long getDoAtTime();

private:
	long doAt;
	std::function<void()> func;
	int funcCallCount;
};