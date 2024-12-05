#ifndef _APP_PAGE_HPP_
#define _APP_PAGE_HPP_

namespace samaya{
    class AppPage{        
        public:            
            AppPage( int width, int height);
            virtual void paint() = 0;
            virtual void update(float) = 0;
            virtual void processInput() = 0;
        protected:  
            int width;
            int height;
    };    
}

#endif