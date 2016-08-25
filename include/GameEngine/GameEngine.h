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

	static void loadSoundEffect(std::string name, std::string loc);
	static void playSoundEffect(std::string effect);
	static void loadSong(std::string name, std::string loc);
	static void playSong(std::string song);

	static int getWindowWidth();
	static int getWindowHeight();

	void startGame();
	void stopGame();

	void loadGame(Game* game);

	const Uint8* getKeys();

	const static int ENTER_KEY;
	const static int SPACE_KEY;
	const static int UP_KEY;
	const static int DOWN_KEY;
	const static int LEFT_KEY;
	const static int RIGHT_KEY;
	const static int W_KEY;
	const static int A_KEY;
	const static int S_KEY;
	const static int D_KEY;

	int getDeltaTime(){ return deltaTime; }

	Renderer* getRenderer(){ return renderer; }
	AudioPlayer* getAudioPlayer(){ return audioPlayer; }
	GameWindow* getGameWindow(){ return window; }

private:
	float deltaTime;

	Game* currentGame;	

	Renderer* renderer;
	GameWindow* window;
	AudioPlayer* audioPlayer;

	static GameEngine* gameEngineInstance;
	Uint8* keyState;	

	void initSDL();
	void initGameWindow();
	void initGLEW();
	void runGameLoop();

	GameEngine();

};
