#ifndef _APP_HPP_
#define _APP_HPP_

#include <vector>
#include <list>
#include "GamePage.hpp"
#include "Task.hpp"

namespace samaya{
    class App{
        public:
            App(int, int, const char*);
            ~App();
            App& run();
            void processInput();
            void update();
            void paint();

        private:
            int width;
            int height;
            const char* title;
            bool isAppShuttingDown;
            std::vector<AppPage> pages;
            int currentPageIdx;
            GamePage game;


            
    };
}

#endif