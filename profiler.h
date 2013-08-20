#pragma once
#include <cstring>
#include <string>

namespace sf {
class Time;
class Clock;
}
class Profile;
class Profiler
{
public:
    Profiler(const char* filename = "profiler.txt");
    ~Profiler();

    void start(const char* name);
    void stop();
    void saveResults();

private:
    Profile* main;
    Profile* current;

    char filename[80];

public:
    void saveSamples(Profile* profile, bool childsToo);

};
