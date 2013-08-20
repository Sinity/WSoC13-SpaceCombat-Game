#pragma once
#include "render.h"
#include "resource_manager.h"
#include "logger.h"
#include "game.h"
#include "object.h"
#include "profiler.h"

class ServiceLocator : public ezo::Object
{
public:
	Renderer* getRender() { return render; }
	Logger* getLogger() { return logger; }
	ResourceManager* getResourceManager() { return resourceManager; }
	Game*			getEngine() { return engine; }
    Profiler*       getProfiler() { return profiler; }
	
	
	void setRender(Renderer* render) { this->render = render; }
	void setLogger(Logger* logger) { this->logger = logger; }
	void setResourceManager(ResourceManager* rMgr) { resourceManager = rMgr; }
	void setEngine(Game* engine) { this->engine = engine; }
    void setProfiler(Profiler* profiler) {  this->profiler = profiler; }

private:
	Renderer* render;
	Logger* logger;
	ResourceManager* resourceManager;
	Game* engine;
    Profiler* profiler;
	
public:
	ServiceLocator() :
		render(nullptr),
		logger(nullptr),
		resourceManager(nullptr),
		engine(nullptr)
	{}
};

extern ServiceLocator servLoc;
