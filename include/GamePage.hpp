#ifndef _GAMEPAGE_HPP_
#define _GAMEPAGE_HPP_

#include "AppPage.hpp"
#include <string>
#include<vector>
#include <raylib.h>
#include "SnakePart.hpp"
#include "Task.hpp"

namespace samaya{
    class GamePage : public AppPage {
        public:
        enum GameState
            {
                STATE_NONE,
                STATE_LOAD,
                STATE_INIT_NEW_GAME,
                STATE_STARTED,
                STATE_PAUSED,
                STATE_GAMEOVER,
                STATE_END
            };
            GamePage(int width, int height);
            ~GamePage();
            void paint() override;
            void update(float) override;
            void processInput() override;
            void loadGame();
            void loadImages();
            void unloadImages();
            void initGame();
            void createSnake();
            void deleteSnake();
            void generateMouse();
            void checkhit();
            void drawControlPanel();
            void drawTimer();
            void drawSnake();
            void drawMouse();
            void drawOverlay();
            bool onKey(int keyCode);
            bool onMouseClick(int x, int y, int button);
        
        private:

            

            std::string str;
	        Font systemFont, gameFont;
            GameState state = STATE_NONE;
            int playAreaX, playAreaY, playAreaWidth, playAreaHeight;
            //StringBuffer strbuf;
	
            Texture2D timeBg, bgImg, overlay, about;	
            Texture2D upArrow, downArrow, leftArrow, rightArrow;	
            Texture2D yellowRound, greenRound;
            Texture2D headDown, headLeft, headRight, headUp;

            Texture2D mouseImg;
            Texture2D resumeButton, pauseButton, newButton;
            Texture2D reverseDesl, reverseSel;
	
            int alertw, alerth;
            int alertx, alerty;
            
            int buttonW, buttonH;
            int bgW, bgH;
            int timerBgX, timerBgY,timerBgW, timerBgH; 
            float timerStrX, timerStrY;
            
            
            int overlayW, overlayH;
            
            float totalTime, prevTime;    
    
    
            //Random rand;
            
            Color bgColor;
                
            Task  task_move_snake, time_task;
            
            SnakePart* head = nullptr;
            
            int maxRow,maxCol;
            
            std::vector<int> mouse;
            int totalMouseCapture;

            bool isReverse;
            bool check_game;
            
            int upButtonX, upButtonY;
            int downButtonX, downButtonY;
            int leftButtonX, leftButtonY;
            int rightButtonX, rightButtonY;
            int reverseButtonX, reverseButtonY; 
            int reverseButtonW, reverseButtonH; 
            int newButtonX, newButtonY;
            int pauseButtonX, pauseButtonY;
            int npButtonW, npButtonH;
            int controlPanelY;
            
            int gONewButtonX, gONewButtonY;
            int resumeButtonX, resumeButtonY;



            
            static constexpr long MIN_IN_MILLIS =  60 * 1000;
            static constexpr long HRS_IN_MILLIS = 60 * MIN_IN_MILLIS;
            
            
            // static constexpr int TASKID_INITGAME = Application._LAST_APP_TASK_  + 1;
            // static constexpr int TASKID_TIME = Application._LAST_APP_TASK_  + 2;
            // static constexpr int TASKID_MOVESNAKE = Application._LAST_APP_TASK_  + 3;


       
            
            // static constexpr int STATE_NONE = 0;
            
            // static constexpr int STATE_INIT = 1;
            // static constexpr int STATE_STARTED = 2;
            // static constexpr int STATE_PAUSED = 3;
            // static constexpr int STATE_GAMEOVER = 4;
            // static constexpr int STATE_END = 5;
            
            
            static constexpr int LEFT_MARGIN = 24;
            static constexpr int TOP_MARGIN = 42;
            
            static constexpr int GRID_BORDER = 1;
            
            static constexpr int GRID_WIDTH = 270;
            static constexpr int GRID_HEIGHT = 330;
            
            static constexpr int CELL_WIDTH = 30;
            static constexpr int CELL_HEIGHT = 30;
            static const std::string gameOverStr;
            static const std::string pausedStr;            

    };    
} // namespace samaya

#endif