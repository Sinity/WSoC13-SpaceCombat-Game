#pragma once
#include <SFML/System.hpp>

class Logger;

class Console
{
public:
	Console();
	~Console(void);

	void Run();
	void RunParallel();

	void Write(const char* s);
	void WriteLn(const char* s);

private:
	sf::Thread* console_thread;
	Logger* conLogger;
};
