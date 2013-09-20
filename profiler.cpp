#include "profiler.h"
#include <fstream>
#include <limits>
#include <SFML/System.hpp>
#include "ezolib.h"


class Profile
{
public:
    std::string calculateResults(unsigned int depth);
    std::string dumpSamples();
    Profile(const char* name, Profile* parent = nullptr) : name(name), parent(parent)
    {
        clock.restart();
    }

    ~Profile()
    {
        for(unsigned int i = 0; i < childs.size(); i++)
            delete childs[i];
    }

    std::string name;
    sf::Clock clock;
    std::vector<sf::Time> samples;
    std::vector<Profile*> childs;

    Profile* const parent;
};

std::string Profile::calculateResults(unsigned int depth)
{
    //calculate indents
    std::string indent;
    for(unsigned int i = 0; i < depth; i++)
        indent += '\t';

    //calculate min, max, average and total
    sf::Time avg, min, max, total;
    avg = sf::milliseconds(0);
    min = sf::milliseconds(__INT32_MAX__);
    max = sf::milliseconds(-(__INT32_MAX__-1));
    total = sf::milliseconds(0);
    for(unsigned int i = 0; i < samples.size(); i++)
    {
        total += samples[i];
        if(samples[i] < min)
            min = samples[i];
        if(samples[i] > max)
            max = samples[i];
    }
    avg = total / (sf::Int64)samples.size();

    //calculate participation in parent time
    sf::Time parentTotal;
    for(sf::Time sample : parent->samples)
        parentTotal += sample;
    double parentParticipation = (1.0 / (parentTotal.asSeconds() / total.asSeconds())) * 100;

    //calculate min/max % of average
    double minPartOfAverage = (1.0 / (avg.asSeconds() / min.asSeconds())) * 100;
    double maxPartOfAverage = (1.0 / (avg.asSeconds() / max.asSeconds())) * 100;

    //format stats
    std::string result = ezo::string::format("%sName: %s\n"
                                  "%sSamples: %d\n"
                                  "%sParticipation in parent time: %f%%\n"
                                  "%sAverage: %fs (%lldus)\n"
                                  "%sMin: %fs (%lldus) - %f%% of average\n"
                                  "%sMax: %fs (%lldus) - %f%% of average\n"
                                  "%sTotal: %fs (%lldus)\n\n",
                                  indent.c_str(), name.c_str(),
                                  indent.c_str(), samples.size(),
                                  indent.c_str(), parentParticipation,
                                  indent.c_str(), avg.asSeconds(), avg.asMicroseconds(),
                                  indent.c_str(), min.asSeconds(), min.asMicroseconds(), minPartOfAverage,
                                  indent.c_str(), max.asSeconds(), max.asMicroseconds(), maxPartOfAverage,
                                  indent.c_str(), total.asSeconds(), total.asMicroseconds()).c();


    //repeat in childrens
    depth++;
    for(unsigned int i = 0; i < childs.size(); i++)
        result += childs[i]->calculateResults(depth);

    return result;
}

std::string Profile::dumpSamples()
{
    std::string result;
    for(unsigned int i = 0; i < samples.size(); i++)
        result += ezo::string::format("%d. %fs (%ll us)\n", i+1, samples[i].asSeconds(), samples[i].asMicroseconds());
    return result;
}


Profiler::Profiler(const char* filename) :
    main(new Profile("main", nullptr)),
    current(main)
{
    strcpy(this->filename, filename);
}

void Profiler::start(const char* name)
{
    //search for existing profile
    for(unsigned int i = 0; i < current->childs.size(); i++)
        if(current->childs[i]->name == name)
        {
            current = current->childs[i];
            current->clock.restart();
            return;
        }

    //not found; it's new
    current->childs.push_back(new Profile(name, current));
    current = current->childs.back();
}

void Profiler::stop()
{
    sf::Time currTime = current->clock.getElapsedTime();
    current->samples.push_back(currTime);
    current = current->parent;
}

void Profiler::saveResults()
{
    std::string result;

    //calculate main time
    sf::Time maintime = main->clock.restart();
    main->samples.push_back(maintime);
    result += ezo::string::format("Main: %fs (%lldus)\n",
                                  maintime.asSeconds(),
                                  maintime.asMicroseconds());

    //calculate childrens stats
    for(Profile* child : main->childs)
        result += child->calculateResults(1);


    //save to file
    std::ofstream resFile;
    resFile.open(filename);
    if(!resFile.is_open())
        return;
    resFile << result;
    resFile.close();
}

void Profiler::saveSamples(Profile *profile, bool childsToo)
{
    //generate filename
    std::string filename = ezo::string::format("%s_dmp", profile->name.c_str()).c();
    for(Profile* ancestor = profile->parent; ancestor != nullptr; ancestor = ancestor->parent)
        filename += ezo::string::format(".%s", ancestor->name.c_str()).c();
    filename += ".txt";

    //save samples to file
    std::ofstream file;
    file.open(filename);
    if(!file.is_open())
        return;
    file << profile->dumpSamples();
    file.close();

    //repeat in childs if required
    if(childsToo)
        for(auto child : profile->childs)
            saveSamples(child, true);
}

Profiler::~Profiler()
{
    saveResults();
    //saveSamples(main, true);
    delete main;
}

