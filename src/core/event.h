#pragma once
#include <vector>
#include <functional>
#include <unordered_map>

class event {
public:
	event() = default;
	~event() = default;
	
	int addListener(std::function<void()> callback);
	void removeListener(int id);
	void removeAllListeners();
	void notify();

private:
	std::unordered_map<int, std::function<void()>> listeners;
	int nextId = 0;
};
