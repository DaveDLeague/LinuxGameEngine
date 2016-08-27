
#include "GameEngine/GameEngine.h"
#include "GameEngine/GameObject.h"
#include "PongPaddle.h"
#include "PongBall.h"

const int GameEngine::ENTER_KEY = SDL_SCANCODE_RETURN;
const int GameEngine::SPACE_KEY = SDL_SCANCODE_SPACE;
const int GameEngine::UP_KEY = SDL_SCANCODE_UP;
const int GameEngine::DOWN_KEY = SDL_SCANCODE_DOWN;
const int GameEngine::LEFT_KEY = SDL_SCANCODE_LEFT;
const int GameEngine::RIGHT_KEY = SDL_SCANCODE_RIGHT;
const int GameEngine::W_KEY = SDL_SCANCODE_W;
const int GameEngine::A_KEY = SDL_SCANCODE_A;
const int GameEngine::S_KEY = SDL_SCANCODE_S;
const int GameEngine::D_KEY = SDL_SCANCODE_D;

bool GameEngine::GAMEPAD1_A;
bool GameEngine::GAMEPAD1_B;
bool GameEngine::GAMEPAD1_X;
bool GameEngine::GAMEPAD1_Y;
bool GameEngine::GAMEPAD1_BACK;
bool GameEngine::GAMEPAD1_START;
bool GameEngine::GAMEPAD1_UP;
bool GameEngine::GAMEPAD1_DOWN;
bool GameEngine::GAMEPAD1_LEFT;
bool GameEngine::GAMEPAD1_RIGHT;
bool GameEngine::GAMEPAD1_LB;
bool GameEngine::GAMEPAD1_RB;
bool GameEngine::GAMEPAD1_L3;
bool GameEngine::GAMEPAD1_R3;
float GameEngine::GAMEPAD1_LT;
float GameEngine::GAMEPAD1_RT;
float GameEngine::GAMEPAD1_AXIS_LEFT_X;
float GameEngine::GAMEPAD1_AXIS_LEFT_Y;
float GameEngine::GAMEPAD1_AXIS_RIGHT_X;
float GameEngine::GAMEPAD1_AXIS_RIGHT_Y;

bool GameEngine::GAMEPAD2_A;
bool GameEngine::GAMEPAD2_B;
bool GameEngine::GAMEPAD2_X;
bool GameEngine::GAMEPAD2_Y;
bool GameEngine::GAMEPAD2_BACK;
bool GameEngine::GAMEPAD2_START;
bool GameEngine::GAMEPAD2_UP;
bool GameEngine::GAMEPAD2_DOWN;
bool GameEngine::GAMEPAD2_LEFT;
bool GameEngine::GAMEPAD2_RIGHT;
bool GameEngine::GAMEPAD2_LB;
bool GameEngine::GAMEPAD2_RB;
bool GameEngine::GAMEPAD2_L3;
bool GameEngine::GAMEPAD2_R3;
float GameEngine::GAMEPAD2_LT;
float GameEngine::GAMEPAD2_RT;
float GameEngine::GAMEPAD2_AXIS_LEFT_X;
float GameEngine::GAMEPAD2_AXIS_LEFT_Y;
float GameEngine::GAMEPAD2_AXIS_RIGHT_X;
float GameEngine::GAMEPAD2_AXIS_RIGHT_Y;

GameEngine* GameEngine::gameEngineInstance;

const Uint8* getKeyState();

void setColor(int r, int g, int b);
void setColor(float r, float g, float b);
void setBackgroundColor(int r, int g, int b);
void setBackgroundColor(float r, float g, float b);
void fillRect(int x, int y, int w, int h);
void drawRect(int x, int y, int w, int h);
void fillOval(int x, int y, int w, int h);
void drawImage(std::string imageName, int x, int y, int w, int h);
void drawText(std::string text, int x, int y, float scale);
void loadImage(std::string textureName, std::string textureLoc, bool hasTransparency);
void loadFont(std::string fontName, std::string fontLoc);
void setFont(std::string font);

void loadSoundEffect(std::string name, std::string loc);
void playSoundEffect(std::string effect);
void loadSong(std::string name, std::string loc);
void playSong(std::string song);

int getWindowWidth();
int getWindowHeight();

GameEngine::GameEngine() {
	deltaTime = 0;	
	window = NULL;
	renderer = NULL;
	controller1 = NULL;
	controller2 = NULL;	

	initSDL();
	initGameWindow();
	initGLEW();	
	initGameControllers();

	renderer = new Renderer(window);
	audioPlayer = new AudioPlayer();
}

GameEngine::~GameEngine() {
	delete window;
	delete renderer;
	delete audioPlayer;
	delete gameEngineInstance;
	if(controller1 != NULL){ SDL_GameControllerClose(controller1); }
	if(controller2 != NULL){ SDL_GameControllerClose(controller2); }
	
	SDL_Quit();
}

void GameEngine::initGameWindow(){
	window = new GameWindow(0, 0, "");
	window->setVisible(false);
}

void GameEngine::initGLEW(){
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
  		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void GameEngine::initGameControllers(){
	for(int i = 0; i < SDL_NumJoysticks(); i++){
		if(SDL_IsGameController(i)){
			if(controller1 == NULL){
				controller1 = SDL_GameControllerOpen(i);
			}else if(controller2 == NULL){
				controller2 = SDL_GameControllerOpen(i);
			}else{
				break;
			}
		}
	}
}

void GameEngine::loadGame(Game* game){
	currentGame = game;
	int w = currentGame->getWidth();
	int h = currentGame->getHeight();
	window->setWindowSize(w, h);
	renderer->setDimensions((float)w, (float)h);
	window->setWindowTitle(currentGame->getTitle());
	window->centerWindow();
	window->setVisible(true);
}

void GameEngine::startGame() {
	if(currentGame == NULL){
		std::cerr << "ERROR: Game not loaded.\nMust call GameEngine::loadGame(Game) " << 
					 "before calling GameEngine::startGame()." << std::endl;
	}else{
		runGameLoop();
	}
}


void GameEngine::runGameLoop(){
	bool quit = false;
		 
	SDL_Event event;

	clock_t strt = clock();
	int fps = CLOCKS_PER_SEC / 60;

	while(!quit){
		SDL_PumpEvents();
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		if(keys[SDL_SCANCODE_ESCAPE]){
			quit = true;
		}		
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_QUIT: 
				quit = true;
				break;
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
				handleControllerButtonEvent();
				break;
			case SDL_CONTROLLERAXISMOTION:
				handleControllerAxisEvent();
				break;
			}
		}
		if(clock() - strt >= fps){
			window->refresh();
			currentGame->update();	
			strt = clock();
		}
		deltaTime = (float)(clock() - strt) / (float)CLOCKS_PER_SEC;
	}
}

void GameEngine::handleControllerButtonEvent(){
	GAMEPAD1_A = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_A);
	GAMEPAD1_B = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_B);
	GAMEPAD1_X = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_X);
	GAMEPAD1_Y = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_Y);
	GAMEPAD1_BACK = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_BACK);
	GAMEPAD1_START = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_START);
	GAMEPAD1_UP = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_DPAD_UP);
	GAMEPAD1_DOWN = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	GAMEPAD1_LEFT = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	GAMEPAD1_RIGHT = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	GAMEPAD1_LB = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	GAMEPAD1_RB = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	GAMEPAD1_L3 = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_LEFTSTICK);
	GAMEPAD1_R3 = SDL_GameControllerGetButton(controller1, SDL_CONTROLLER_BUTTON_RIGHTSTICK);

	GAMEPAD2_A = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_A);
	GAMEPAD2_B = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_B);
	GAMEPAD2_X = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_X);
	GAMEPAD2_Y = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_Y);
	GAMEPAD2_BACK = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_BACK);
	GAMEPAD2_START = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_START);
	GAMEPAD2_UP = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_DPAD_UP);
	GAMEPAD2_DOWN = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	GAMEPAD2_LEFT = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	GAMEPAD2_RIGHT = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	GAMEPAD2_LB = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	GAMEPAD2_RB = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	GAMEPAD2_L3 = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_LEFTSTICK);
	GAMEPAD2_R3 = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
}

void GameEngine::handleControllerAxisEvent(){
	GAMEPAD1_LT = SDL_GameControllerGetAxis(controller1, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / 32767.0f;
	GAMEPAD1_RT = SDL_GameControllerGetAxis(controller1, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / 32767.0f;
	GAMEPAD1_AXIS_LEFT_X = SDL_GameControllerGetAxis(controller1, SDL_CONTROLLER_AXIS_LEFTX) / 32767.0f;
	GAMEPAD1_AXIS_LEFT_Y = SDL_GameControllerGetAxis(controller1, SDL_CONTROLLER_AXIS_LEFTY) / 32767.0f;
	GAMEPAD1_AXIS_RIGHT_X = SDL_GameControllerGetAxis(controller1, SDL_CONTROLLER_AXIS_RIGHTX) / 32767.0f;
	GAMEPAD1_AXIS_RIGHT_Y = SDL_GameControllerGetAxis(controller1, SDL_CONTROLLER_AXIS_RIGHTY) / 32767.0f;

	GAMEPAD2_LT = SDL_GameControllerGetAxis(controller2, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / 32767.0f;
	GAMEPAD2_RT = SDL_GameControllerGetAxis(controller2, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / 32767.0f;
	GAMEPAD2_AXIS_LEFT_X = SDL_GameControllerGetAxis(controller2, SDL_CONTROLLER_AXIS_LEFTX) / 32767.0f;
	GAMEPAD2_AXIS_LEFT_Y = SDL_GameControllerGetAxis(controller2, SDL_CONTROLLER_AXIS_LEFTY) / 32767.0f;
	GAMEPAD2_AXIS_RIGHT_X = SDL_GameControllerGetAxis(controller2, SDL_CONTROLLER_AXIS_RIGHTX) / 32767.0f;
	GAMEPAD2_AXIS_RIGHT_Y = SDL_GameControllerGetAxis(controller2, SDL_CONTROLLER_AXIS_RIGHTY) / 32767.0f;
}

const Uint8* GameEngine::getKeys(){
	return SDL_GetKeyboardState(NULL);
}

GameEngine* GameEngine::getInstance() {
	if (!gameEngineInstance) {
		gameEngineInstance = new GameEngine();
	}
	return gameEngineInstance;
}

const Uint8* GameEngine::getKeyState(){
	return GameEngine::getInstance()->getKeys();
}

void GameEngine::setColor(int r, int g, int b){
	GameEngine::getInstance()->getRenderer()->setColor(r, g, b);
}

void GameEngine::setColor(float r, float g, float b){
	GameEngine::getInstance()->getRenderer()->setColor(r, g, b);
}

void GameEngine::setBackgroundColor(int r, int g, int b){
	GameEngine::getInstance()->getGameWindow()->setBackgroundColor(r, g, b);
}

void GameEngine::setBackgroundColor(float r, float g, float b){
	GameEngine::getInstance()->getGameWindow()->setBackgroundColor(r, g, b);
}

void GameEngine::fillRect(int x, int y, int w, int h){
	GameEngine::getInstance()->getRenderer()->fillRect(x, y, w, h);
}

void GameEngine::drawRect(int x, int y, int w, int h){
	GameEngine::getInstance()->getRenderer()->drawRect(x, y, w, h);
}

void GameEngine::fillOval(int x, int y, int w, int h){
	GameEngine::getInstance()->getRenderer()->fillOval(x, y, w, h);
}

void GameEngine::drawImage(std::string imageName, int x, int y, int w, int h){
	GameEngine::getInstance()->getRenderer()->drawImage(imageName, x, y, w, h);
}

void GameEngine::drawText(std::string text, int x, int y, float scale){
	GameEngine::getInstance()->getRenderer()->drawText(text, x, y, scale);
}

void GameEngine::loadImage(std::string textureName, std::string textureLoc, bool hasTransparency){
	GameEngine::getInstance()->getRenderer()->loadImage(textureName, textureLoc, hasTransparency);
}

void GameEngine::loadFont(std::string fontName, std::string fontLoc){
	GameEngine::getInstance()->getRenderer()->loadFont(fontName, fontLoc);
}

void GameEngine::setFont(std::string font){
	GameEngine::getInstance()->getRenderer()->setFont(font);
}

void GameEngine::loadSoundEffect(std::string name, std::string loc){
	GameEngine::getInstance()->getAudioPlayer()->loadSoundEffect(name, loc);
}

void GameEngine::playSoundEffect(std::string effect){
	GameEngine::getInstance()->getAudioPlayer()->playSoundEffect(effect);
}

void GameEngine::loadSong(std::string name, std::string loc){
	GameEngine::getInstance()->getAudioPlayer()->loadSong(name, loc);
}

void GameEngine::playSong(std::string song){
	GameEngine::getInstance()->getAudioPlayer()->playSong(song);
}

int GameEngine::getWindowWidth(){
	return GameEngine::getInstance()->getGameWindow()->getWindowWidth();
}

int GameEngine::getWindowHeight(){
	return GameEngine::getInstance()->getGameWindow()->getWindowHeight();
}

void GameEngine::initSDL(){
	if(0 != SDL_Init(SDL_INIT_EVERYTHING)){
		std::cout << "Error initializing SDL/n";
	}
}


















