#ifndef _TASK_HPP_
#define _TASK_HPP_

namespace samaya
{
    class Task
    {   private:
            int task_type;
            float nextExecTime;
            float period;  
            bool isClose;
        public:
            Task(int, float, float);
            ~Task();             
            bool isTimeUp(float);
            void Close();
            bool isTaskClose();

    };    
} // namespace samaya


#endif
