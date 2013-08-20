#include "console.h"
#include "service_locator.h"

Console::Console()
: console_thread(nullptr),
conLogger(nullptr) {
}

void Console::RunParallel() {
    servLoc.getLogger()->log(POS, "Console will run in other thread(parallel)");
    console_thread = new sf::Thread(&Console::Run, this);
    console_thread->launch();
}

void Console::Run() {
    conLogger = new Logger("console_log");

    servLoc.getLogger()->log(POS, "Console not implemented yet...", LogType::Information, LogOutput::TxtFile);
    return;

    while (true) {
        sf::sleep(sf::seconds(1));
        char s[2048];
        while (1) {
            conLogger->log(POS, (char*)ezo::string::format("In: %s", s));
            WriteLn((char*)ezo::string::format("I can't interpret \"%s\"!", s));
        }
    }
}

Console::~Console(void) {
    servLoc.getLogger()->log(POS, "Console instance destructed!");
    if (console_thread != nullptr)
        console_thread->terminate(),
        delete console_thread;
    delete conLogger;
}

void Console::Write(const char* s) {
    conLogger->log(POS, (char*)ezo::string::format("Out: %s", s));
}

void Console::WriteLn(const char* s) {
    conLogger->log(POS, (char*)ezo::string::format("Out: %s\\n", s));
}