#include "SnakePart.hpp"

namespace samaya
{

     SnakePart::SnakePart(PartType type, int row, int col, int color, Direction direction) {
      this->part_type = type;
      this->curRow = row;
      this->curCol = col;
      this->color = color;
      this->direction = direction;
   }

   SnakePart::~SnakePart() {
      // if (this->part_type == 2) {
      //    delete this->prev;
      // }
   }

    void SnakePart::setMaxRowCol(int maxRow, int maxCol) {
      this->maxRow = maxRow;
      this->maxCol = maxCol;
   }

    void SnakePart::copyPrev() {
      if (this->prev != nullptr) {
         this->curRow = this->prev->curRow;
         this->curCol = this->prev->curCol;
         this->direction = this->prev->direction;
      }

   }

    void SnakePart::addToTail() {
      if (this->part_type == TAIL) {
         SnakePart *bp = new SnakePart(BODY, this->curRow, this->curCol, this->color, this->direction);
         bp->prev = this->prev;
         bp->next = this;
         this->prev->next = bp;
         this->prev = bp;
         switch (this->direction) {
            case UP:
               ++this->curRow;
               break;
            case DOWN:
               --this->curRow;
               break;
            case LEFT:
               ++this->curCol;
               break;
            case RIGHT:
               --this->curCol;
               break;
         }
      }

   }

    bool SnakePart::checkCaptureMouse(int rowIdx, int colIdx) {
      bool retVal = false;
      if (this->part_type == HEAD) {
         retVal = (rowIdx == this->curRow && colIdx == this->curCol);
      }

      return retVal;
   }

    bool SnakePart::checkTailBite() {
      bool retVal = false;
      if (this->part_type == HEAD) {
         for(SnakePart* parse = this->next; parse != nullptr; parse = parse->next) {
            retVal = this->curRow == parse->curRow && this->curCol == parse->curCol;
            if (retVal) {
               break;
            }
         }
      }

      return retVal;
   }

    bool SnakePart::changeDirection(Direction direction) {
      bool handled = false;
      if (this->part_type == HEAD && this->direction != direction &&  
      (direction == LEFT && this->direction != RIGHT || 
       direction == RIGHT && this->direction != LEFT ||
       direction == UP && this->direction != DOWN ||
       direction == DOWN && this->direction != UP )){
         SnakePart* tail = this->prev;

         for(SnakePart* parse = tail; parse != this; parse = parse->prev) {
            parse->copyPrev();
         }

         this->direction = direction;
         this->moveCoord();
         handled = true;
      }

      return handled;
   }

   void SnakePart::moveCoord() {
      switch (this->direction) {
         case UP:
            --this->curRow;
            if (this->curRow < 0) {
               this->curRow = this->maxRow;
            }
            break;
         case DOWN:
            ++this->curRow;
            if (this->curRow > this->maxRow) {
               this->curRow = 0;
            }
            break;
         case LEFT:
            --this->curCol;
            if (this->curCol < 0) {
               this->curCol = this->maxCol;
            }
            break;
         case RIGHT:
            ++this->curCol;
            if (this->curCol > this->maxCol) {
               this->curCol = 0;
            }
            break;
      }

   }

    void SnakePart::move() {
      if (this->part_type == HEAD) {
         SnakePart* tail = this->prev;

         for(SnakePart* parse = tail; parse != this; parse = parse->prev) {
            parse->copyPrev();
         }

         this->moveCoord();
      }

   }

    void SnakePart::copyNext() {
      if (this->next != nullptr) {
         this->curRow = this->next->curRow;
         this->curCol = this->next->curCol;
         this->direction = this->next->direction;
      }

   }

    
} // namespace samaya
