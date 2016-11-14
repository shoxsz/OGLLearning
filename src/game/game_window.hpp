#ifndef _GAME_WINDOW_HPP_
#define _GAME_WINDOW_HPP_

class GameWindow : public SDLWindow{
public:
    ~GameWindow();

	void preLoop();
	void process(milliseconds delta);
	void render(milliseconds delta);
	void posLoop();
	void closed();

private:
};

#endif