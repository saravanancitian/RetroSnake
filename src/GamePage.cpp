#include "GamePage.hpp"
#include <stdexcept>
namespace samaya
{
    const std::string GamePage::gameOverStr = "GAME OVER";
    const std::string GamePage::pausedStr = "PAUSED";

    GamePage::GamePage( int width, int height)
        : AppPage( width, height),task_move_snake(1, .500f, .250f),time_task(2, 1.0f, 1.0f){
            SetRandomSeed(100);
			state = STATE_LOAD;
    }

	GamePage::~GamePage(){
		unloadImages();
		UnloadFont(gameFont);
		deleteSnake();
	}


	
     
	void GamePage::loadGame()
	{
		try
		{
			//loadFont 
			gameFont = LoadFont("../res/TOONEYNO.TTF");
			
			loadImages();

			playAreaX = LEFT_MARGIN + GRID_BORDER;
			playAreaY = TOP_MARGIN + GRID_BORDER;
			playAreaWidth = GRID_WIDTH;
			playAreaHeight = GRID_HEIGHT;
			
			maxRow = (GRID_HEIGHT - 2)/CELL_HEIGHT;
			maxCol = (GRID_WIDTH - 2)/CELL_WIDTH;
			
			timerBgX = LEFT_MARGIN;
			timerBgY = playAreaY - timerBgH - 1 ;
			
			
			timerStrX = timerBgX + 9;
			timerStrY = timerBgY + 9;
			
			controlPanelY = playAreaY + playAreaHeight + 2; 
			upButtonY =  controlPanelY + 4;
			
			reverseButtonY = upButtonY + buttonH;
			
			leftButtonY = rightButtonY = reverseButtonY  + ((reverseButtonH - buttonH)>>1);		 
			downButtonY =  reverseButtonY +  reverseButtonH ;
			
			rightButtonX = bgW - (buttonW<<1);
			
			reverseButtonX = rightButtonX - reverseButtonW;
			
			upButtonX = downButtonX = reverseButtonX + ((reverseButtonW - buttonW)>>1);
			
			leftButtonX = reverseButtonX - buttonW ;
			
			pauseButtonX = leftButtonX - npButtonW - (buttonW>>1);
			pauseButtonY = leftButtonY;//controlPanelY + ((bgH - controlPanelY) >> 1);
			
			newButtonX = pauseButtonX- npButtonW -  (buttonW>>2);
			newButtonY= leftButtonY;

        	//state = STATE_INIT_NEW_GAME;
			initGame();
			
		}
		catch(std::exception& e)
		{
			printf("Exception: %s\n", e.what());
		   //Application.debug("Unable to load resource");	
		}
	}

	void GamePage::unloadImages(){
		UnloadTexture(timeBg);
		UnloadTexture(bgImg);
		UnloadTexture(overlay);
		UnloadTexture(about);	
        UnloadTexture(upArrow);
		UnloadTexture(downArrow);
		UnloadTexture(leftArrow);
		UnloadTexture(rightArrow);	
        UnloadTexture(yellowRound);
		UnloadTexture(greenRound);
        UnloadTexture(headDown);
		UnloadTexture(headLeft);
		UnloadTexture(headRight);
		UnloadTexture(headUp);

        UnloadTexture(mouseImg);
    	UnloadTexture(resumeButton);
		UnloadTexture(pauseButton);
		UnloadTexture(newButton);
        UnloadTexture(reverseDesl);
		UnloadTexture(reverseSel);
	}

    
	void GamePage::loadImages()	{

		 about = LoadTexture("../res/about.png");
		 bgImg = LoadTexture("../res/bg.png");
		 
		  bgW = bgImg.width;
		  bgH= bgImg.height;

		 downArrow = LoadTexture("../res/down_arrow.png");
		 greenRound = LoadTexture("../res/green_round.png");
		 
		 headDown = LoadTexture("../res/head_down.png");
		 
		 headLeft = LoadTexture("../res/head_left.png");
		 
		 headRight = LoadTexture("../res/head_right.png");
		 
		 headUp = LoadTexture("../res/head_up.png");
		 
		 leftArrow = LoadTexture("../res/left_arrow.png");
		 
		 mouseImg = LoadTexture("../res/mouse_img.png");
		 
		 newButton = LoadTexture("../res/new_button.png");

		 pauseButton = LoadTexture("../res/pause_button.png");
		 
		 resumeButton = LoadTexture("../res/resume_button.png");
		 
		 npButtonW  = resumeButton.width;
		 npButtonH = resumeButton.height;
	 
		 reverseDesl = LoadTexture("../res/reverse_desl.png");
		 
		 reverseSel = LoadTexture("../res/reverse_sel.png");

		 reverseButtonW = reverseSel.width;
		 reverseButtonH = reverseSel.height;
		 
		 rightArrow = LoadTexture("../res/right_arrow.png");
		 
		 timeBg = LoadTexture("../res/time_bg.png");
		 
		 timerBgW = timeBg.width;
		 timerBgH = timeBg.height;
		 
		 upArrow = LoadTexture("../res/up_arrow.png");
		 
		 buttonW = upArrow.width;
		 buttonH = upArrow.height;
		 
		 yellowRound = LoadTexture("../res/yellow_round.png");
		 
		 overlay = LoadTexture("../res/overlay.png");

		 alertw = overlayW = overlay.width;
		 alerth =  overlayH = overlay.height;
		 
		 alertx = (width - alertw) >> 1;
		 alerty = (height - alerth) >> 1;
		 
	}



    void GamePage::initGame()
    {
        check_game = false;
        isReverse = false;
        totalMouseCapture = 0;
        totalTime = 0;
        prevTime = 0;
		deleteSnake();
        createSnake();
        generateMouse();		
        state = STATE_STARTED;
    }


    void GamePage::createSnake()
    {

        head = new SnakePart(SnakePart::HEAD, 0, 0, 0, SnakePart::RIGHT );
        
        SnakePart* bp1 = new SnakePart(SnakePart::BODY, -1, -1, 0,  SnakePart::RIGHT );
        bp1->prev = head;
        head->next = bp1;
        
        SnakePart* bp2 = new SnakePart(SnakePart::BODY, -1, -1, 0,  SnakePart::RIGHT );
        bp2->prev = bp1;
        bp1->next = bp2;
        
        SnakePart* tail = new SnakePart(SnakePart::TAIL, -1, -1, 0,  SnakePart::RIGHT );
        tail->prev = bp2;
        bp2->next = tail;
        
        head->prev = tail;
        head->setMaxRowCol(maxRow, maxCol);
    
    }


	void GamePage::deleteSnake()
	{
		SnakePart* parse = head;
		while(parse != nullptr)
		{
			SnakePart* next = parse->next;
			delete parse;
			parse = next;
		}
		head = nullptr;
	}


    void GamePage::generateMouse()
	{
		bool found = true;
		int row = 0, col = 0 ;
		int count = 0;
		
		int randRow = maxRow - 1;
		int randCol = maxCol - 1;
		do
		{

			row = GetRandomValue(0, randRow);
			col = GetRandomValue(0, randCol);
			
			if(row < 0)
			{
				row = -row;
			}

			if(col < 0)
			{
				col = -col;
			}

			SnakePart *parse = head;
			while(parse != nullptr)
			{
				int spRow = parse->curRow;
				int spCol = parse->curCol;
				if(spCol >= 0 && spCol <= maxCol && spRow >= 0 && spRow <= maxRow)
				{
					if(spRow == row && spCol == col)
					{
						found = false;
						break;
					}
				}
				if(parse->part_type == SnakePart::TAIL)
				{
					break;
				}
				parse = parse->next;
			}
			count++;
			if(count == 30)
			{
				break;
			}            
		}
		while(!found);

		mouse.clear();
		mouse.push_back(row);
		mouse.push_back(col);
	}

	void GamePage::checkhit(){
		
				if(head->checkTailBite())
				{
					state = STATE_GAMEOVER;
				}
				else if(mouse.size() > 0)
				{
					if(head->checkCaptureMouse(mouse[0] , mouse[1]))
					{
						totalMouseCapture++;
						SnakePart* tail = head->prev;
						tail->addToTail();
						generateMouse(); 
					}
				}
	}


        
		void GamePage::paint()
		{
			
            DrawTexture(bgImg, 0, 0, WHITE);
			drawMouse();
			drawSnake();
			drawControlPanel();
			drawTimer();
			
			DrawTexture(mouseImg ,timerBgX + timerBgW , timerBgY,WHITE);

            std::string tmc = std::to_string(totalMouseCapture);
			Vector2 tmcp = {timerBgX + timerBgW + CELL_WIDTH, timerBgY + 6};
            DrawTextEx(gameFont, tmc.c_str(), tmcp, 20, 0, WHITE);
			
			if(state == STATE_GAMEOVER)
			{
				drawOverlay();

                
                Vector2 m = MeasureTextEx(gameFont, gameOverStr.c_str(), 20.0f,0);
				int strW = m.x;
				int strH = m.y;
				
				
				int strX = (width - strW)>>1;
	            int strY = (height - strH)>>1;	
				Vector2 pos ={strX, strY};
				DrawTextEx(gameFont, gameOverStr.c_str(),pos  , 20,0, WHITE);

	
				gONewButtonX = (width - npButtonW)>>1;
				gONewButtonY = (strY + strH);
			
				DrawTexture(newButton, gONewButtonX, gONewButtonY, WHITE);
			}
			else if(state == STATE_PAUSED)
			{
				drawOverlay();
                Vector2 m = MeasureTextEx(gameFont, pausedStr.c_str(), 20.0f,0);
				int strW = m.x;
				int strH = m.y;
				
				
				int strX = (width - strW)>>1;
	            int strY = (height - strH)>>1;	
				Vector2 pos ={strX, strY};
				
                DrawTextEx(gameFont, pausedStr.c_str(),pos  , 20,0, WHITE);
			}
	    }



        void GamePage::drawControlPanel()
		{
            DrawTexture(upArrow, upButtonX, upButtonY, WHITE);
			DrawTexture(downArrow, downButtonX, downButtonY, WHITE);
			
			DrawTexture(leftArrow, leftButtonX, leftButtonY, WHITE);
			DrawTexture(rightArrow, rightButtonX, rightButtonY, WHITE);
			
			DrawTexture((isReverse)? reverseSel : reverseDesl, reverseButtonX, reverseButtonY, WHITE);
			
			
			DrawTexture((state == STATE_PAUSED)? resumeButton : pauseButton, pauseButtonX, pauseButtonY, WHITE);
			DrawTexture(newButton, newButtonX, newButtonY, WHITE);
			
		}


    void GamePage::drawTimer()
	{
		DrawTexture(timeBg, timerBgX, timerBgY, WHITE);
		int hours = static_cast<int>(totalTime) / 3600;
		int minutes = (static_cast<int>(totalTime) % 3600) / 60;
		int seconds = totalTime - (hours * 3600) - (minutes * 60);
		char time[9];
		sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
		Vector2 pos = {timerStrX, timerStrY};
		DrawTextEx(gameFont, time, pos, 15, 0, WHITE);
		
	}


    void GamePage::drawSnake()
	{
        SnakePart* parse = head;
        if(parse != nullptr)
        {
            do
            {
            	if(parse->curCol >= 0 && parse->curCol <= maxCol && parse->curRow >= 0 && parse->curRow <= maxRow)
            	{
            		int x = playAreaX + parse->curCol * CELL_WIDTH;
            		int y = playAreaY + parse->curRow * CELL_HEIGHT;
	                if(parse->part_type == SnakePart::HEAD)
	                {
	                	Texture2D* head = nullptr;
	                	if(parse->direction == SnakePart::UP){
	                		head = &headUp;
	                	}
	                	else if(parse->direction == SnakePart::DOWN){
	                		head = &headDown;
	                	}
	                	else if(parse->direction == SnakePart::LEFT)
	                	{
	                		head = &headLeft;
	                	}
	                	else if(parse->direction == SnakePart::RIGHT)
	                	{
	                		head = &headRight;
	                	}
	                	
	                	DrawTexture(*head, x, y, WHITE);
	                }
	                else
	                {
	                	if(!(parse->curRow == head->curRow && parse->curCol == head->curCol))
	                	{
			                if(parse->part_type == SnakePart::BODY)
			                {
			                	DrawTexture(greenRound, x, y, WHITE);
			                }
			                else if(parse->part_type == SnakePart::TAIL)
			                {
			                	DrawTexture(yellowRound, x, y, WHITE);
			                }
	                	}
	                }
            	}
            	
            	if(parse->part_type == SnakePart::TAIL)
            	{
            		break;
            	}
                parse = parse->next;
                
            }while(true);
        }
	}



    void GamePage::drawMouse()
	{
		 if(mouse.size() > 0)
         {
     		int x = playAreaX + mouse[1] * CELL_WIDTH;
     		int y = playAreaY + mouse[0] * CELL_HEIGHT;
             DrawTexture(mouseImg ,x , y, WHITE);
         }
	}
	
	void  GamePage::drawOverlay()
	{
		for(int i = 0 ; i < height; i+= overlayH)
		{
			for(int j = 0; j < width; j+=overlayW)
			{
				DrawTexture(overlay, j, i, GRAY);
			}
		}
	}

	void GamePage::update(float delta){
		switch (state)
		{

		case STATE_LOAD:
			loadGame();
			break;
		case STATE_INIT_NEW_GAME:
			initGame();
			break;		
		case STATE_STARTED:

			if(task_move_snake.isTimeUp(delta)){
				if(check_game){
					checkhit();
				}	else{				
					head->move();
				}
				check_game = !check_game;	
			}

			if(time_task.isTimeUp(delta)){
				totalTime += 1.0f;
			}

			break;	
		case STATE_GAMEOVER:
			break;	
		case STATE_PAUSED:
			break;	
		case STATE_END:
			break;				
		
		default:
			break;
		}		
	}


	void GamePage::processInput(){

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			onMouseClick(GetMouseX(), GetMouseY(), MOUSE_BUTTON_LEFT);
		} else{
			onKey(GetKeyPressed());
		}

	}
	

	
	bool GamePage::onKey(int keyCode)
	{
		 bool handled = false;
		if(state == STATE_STARTED)
		{
			switch(keyCode)
			{
				case KEY_LEFT:
				{
					handled = head->changeDirection(isReverse ?SnakePart::RIGHT :  SnakePart::LEFT);
				}
				break;
				
				case KEY_RIGHT:
				{
					handled = head->changeDirection(isReverse ? SnakePart::LEFT : SnakePart::RIGHT);
				}
				break;
				
				case KEY_UP:
				{
					handled = head->changeDirection(isReverse ? SnakePart::DOWN : SnakePart::UP);
				}
				break;
				case KEY_DOWN:
				{
					handled = head->changeDirection(isReverse ?  SnakePart::UP : SnakePart::DOWN);
				}
				break;
			
			}
	        if(handled)
	        {
	        	checkhit();    
	        }
		}
		return handled;
	}



	bool GamePage::onMouseClick(int x, int y, int button)
	{
		bool handled = false;
		
			if(state == STATE_GAMEOVER)
			{				
				if((x> gONewButtonX  && x < (gONewButtonX + npButtonW)) && (y > gONewButtonY && y < (gONewButtonY + npButtonH)))
				{
					initGame();
					handled = true;				
				}
			}
			else
			{
			
				if(y > controlPanelY)
				{
					if((x> newButtonX  && x < (newButtonX + npButtonW)) && (y > newButtonY && y < (newButtonY + npButtonH)))
					{
						initGame();
						handled = true;
					}
					else if((x> pauseButtonX  && x < (pauseButtonX + npButtonW)) && (y > pauseButtonY && y < (pauseButtonY + npButtonH)))
					{
						state = (state == STATE_STARTED)? STATE_PAUSED : STATE_STARTED;
						handled = true;
					}
					else if(state == STATE_STARTED)
					{
						if((x> upButtonX  && x < (upButtonX + buttonW)) && (y > upButtonY && y < (upButtonY + buttonH)))
						{
							handled =onKey(KEY_UP);
							
						}
						else if((x> downButtonX  && x < (downButtonX + buttonW)) && (y > downButtonY && y < (downButtonY + buttonH)))
						{
							handled=onKey(KEY_DOWN);
							
						}
						else if((x> leftButtonX  && x < (leftButtonX + buttonW)) && (y > leftButtonY && y < (leftButtonY + buttonH)))
						{
							handled = onKey(KEY_LEFT);
							
						}
						else if((x> rightButtonX  && x < (rightButtonX + buttonW)) && (y > rightButtonY && y < (rightButtonY + buttonH)))
						{
							handled= onKey(KEY_RIGHT);
							 
						}
						else if((x> reverseButtonX  && x < (reverseButtonX + reverseButtonW)) && (y > reverseButtonY && y < (reverseButtonY + reverseButtonH)))
						{
							 isReverse = !isReverse;
							 handled= true;
						}
					}
	
				}
			}
		return handled;
	}

   
} // namespace samaya


