#include "Task.hpp"
#include <stdio.h>

namespace samaya
{
    Task::Task(int task_type, float nextExecTime, float period){
        this->task_type = task_type;
        this->nextExecTime = nextExecTime;
        this->period = period;
    }

    Task::~Task(){
    }
    
    bool Task::isTimeUp(float delta){
        bool isArrived = false;
        if(!this->isClose){
            this->nextExecTime -= delta;
            if(this->nextExecTime <= 0.0f){
                if(this->period == 0.0f){
                    this->isClose = true;
                } else{
                    this->nextExecTime = this->period;
                }                
                isArrived = true;
            }
        }
        return isArrived;
    }

    void Task::Close(){
        this->isClose = true;
    }

    bool Task::isTaskClose(){
        return this->isClose;
    }
    
} // namespace samaya
