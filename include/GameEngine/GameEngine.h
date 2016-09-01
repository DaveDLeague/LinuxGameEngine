#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "GameEngine/Renderer.h"
#include "GameEngine/AudioPlayer.h"
#include "GameEngine/GameWindow.h"
#include "GameEngine/Game.h"

class GameEngine{
public:
	virtual ~GameEngine();

	const static int ENTER_KEY;
	const static int BACKSPACE_KEY;
	const static int SPACE_KEY;
	const static int UP_KEY;
	const static int DOWN_KEY;
	const static int LEFT_KEY;
	const static int RIGHT_KEY;
	const static int W_KEY;
	const static int A_KEY;
	const static int S_KEY;
	const static int D_KEY;

	static bool GAMEPAD1_A;
	static bool GAMEPAD1_B;
	static bool GAMEPAD1_X;
	static bool GAMEPAD1_Y;
	static bool GAMEPAD1_BACK;
	static bool GAMEPAD1_START;
	static bool GAMEPAD1_UP;
	static bool GAMEPAD1_DOWN;
	static bool GAMEPAD1_LEFT;
	static bool GAMEPAD1_RIGHT;
	static bool GAMEPAD1_LB;
	static bool GAMEPAD1_RB;
	static bool GAMEPAD1_L3;
	static bool GAMEPAD1_R3;
	static float GAMEPAD1_LT;
	static float GAMEPAD1_RT;
	static float GAMEPAD1_AXIS_LEFT_X;
	static float GAMEPAD1_AXIS_LEFT_Y;
	static float GAMEPAD1_AXIS_RIGHT_X;
	static float GAMEPAD1_AXIS_RIGHT_Y;

	static bool GAMEPAD2_A;
	static bool GAMEPAD2_B;
	static bool GAMEPAD2_X;
	static bool GAMEPAD2_Y;
	static bool GAMEPAD2_BACK;
	static bool GAMEPAD2_START;
	static bool GAMEPAD2_UP;
	static bool GAMEPAD2_DOWN;
	static bool GAMEPAD2_LEFT;
	static bool GAMEPAD2_RIGHT;
	static bool GAMEPAD2_LB;
	static bool GAMEPAD2_RB;
	static bool GAMEPAD2_L3;
	static bool GAMEPAD2_R3;
	static float GAMEPAD2_LT;
	static float GAMEPAD2_RT;
	static float GAMEPAD2_AXIS_LEFT_X;
	static float GAMEPAD2_AXIS_LEFT_Y;
	static float GAMEPAD2_AXIS_RIGHT_X;
	static float GAMEPAD2_AXIS_RIGHT_Y;	

	static GameEngine* getInstance();
	
	static const Uint8* getKeyState();

	static void setColor(int r, int g, int b);
	static void setColor(float r, float g, float b);
	static void setBackgroundColor(int r, int g, int b);
	static void setBackgroundColor(float r, float g, float b);
	static void fillRect(int x, int y, int w, int h);
	static void drawRect(int x, int y, int w, int h);
	static void fillOval(int x, int y, int w, int h);
	static void drawImage(std::string imageName, int x, int y, int w, int h);
	static void drawText(std::string text, int x, int y, float scale);
	static void loadImage(std::string textureName, std::string textureLoc, bool hasTransparency);
	static void loadFont(std::string fontName, std::string fontLoc);
	static void setFont(std::string font);
	static void setRotationRad(float f);
	static void setRotationDeg(int d);

	static void loadSoundEffect(std::string name, std::string loc);
	static void playSoundEffect(std::string effect);
	static void loadSong(std::string name, std::string loc);
	static void playSong(std::string song);

	static int getWindowWidth();
	static int getWindowHeight();
	static int getCurrentGameWidth();
	static int getCurrentGameHeight();

	void startGame();
	void stopGame();

	void loadGame(Game* game);

	const Uint8* getKeys();

	int getDeltaTime(){ return deltaTime; }

	Renderer* getRenderer(){ return renderer; }
	AudioPlayer* getAudioPlayer(){ return audioPlayer; }
	GameWindow* getGameWindow(){ return window; }

	int getGameWidth(){ return currentGameWidth; }
	int getGameHeight(){ return currentGameHeight; }

private:
	float deltaTime;
	int currentGameWidth;
	int currentGameHeight;

	Game* currentGame;	

	Renderer* renderer;
	GameWindow* window;
	AudioPlayer* audioPlayer;

	static GameEngine* gameEngineInstance;
	Uint8* keyState;	

	SDL_GameController* controller1;
	SDL_GameController* controller2;

	void initSDL();
	void initGameWindow();
	void initGLEW();
	void runGameLoop();
	void initGameControllers();

	void handleControllerButtonEvent();
	void handleControllerAxisEvent();
	void handleWindowEvent(SDL_Event e);
	void handleWindowResizeEvent();

	GameEngine();

};
