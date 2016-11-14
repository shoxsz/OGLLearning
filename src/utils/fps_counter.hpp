#ifndef _FPS_COUNTER_HPP_
#define _FPS_COUNTER_HPP_

#include <chrono>
#include <thread>

using namespace std::chrono;

class FPSCounter{
public:

	FPSCounter() :fps(0){}
	FPSCounter(unsigned int fps){ setFPS(fps); }

	void start(){
		startT = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	}

	void delay(){
		milliseconds spent =
			duration_cast<milliseconds>(system_clock::now().time_since_epoch()) - startT;
		milliseconds toSleep(fpsDelay);
		if (excess.count() > 0){
			excess -= toSleep;
			if (excess.count() <= 0)
				excess.zero();
		}
		else{
			if (toSleep > spent){
				std::this_thread::sleep_for(toSleep - spent);
			}
			else{
				excess += spent - toSleep;
			}
		}
	}

	bool shouldRender(){
		return excess.count() <= 0;
	}

	void setFPS(unsigned int fps){ 
		this->fps = fps; 
		fpsDelay = 1000 / fps;
	}
	unsigned int getFPS()const{ return fps; }

private:
	milliseconds startT, excess;
	unsigned int fps;
	unsigned int fpsDelay;
};

#endif