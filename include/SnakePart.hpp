#ifndef _SNAKEPART_HPP_
#define _SNAKEPART_HPP_

namespace samaya{
    class SnakePart{

        public:

            enum PartType{
                HEAD,
                BODY,
                TAIL
            };

            enum Direction{
                UP,
                DOWN,
                LEFT,
                RIGHT
            };

            SnakePart(PartType type, int row, int col, int color, Direction direction);
            ~SnakePart();
            void setMaxRowCol(int maxRow, int maxCol);
            void copyPrev();
            void addToTail();
            bool checkCaptureMouse();
            bool checkCaptureMouse(int rowIdx, int colIdx);
            bool checkTailBite();
            bool changeDirection(Direction direction);
            void moveCoord();
            void move();
            void copyNext();


            SnakePart *prev = nullptr;
            SnakePart *next = nullptr;
            

            static constexpr int PART_WIDTH = 30; 
            static constexpr int PART_HEIGHT = 30;



            PartType part_type;
            int color;
            Direction direction;
   
            int curRow;
            int curCol;
            int maxRow;
            int maxCol;
            int diff = 30;
            

    };
}

#endif