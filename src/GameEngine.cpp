
#include "GameEngine/GameEngine.h"
#include "GameEngine/GameObject.h"
#include "PongPaddle.h"
#include "PongBall.h"

const int GameEngine::UP_KEY = SDL_SCANCODE_UP;
const int GameEngine::DOWN_KEY = SDL_SCANCODE_DOWN;
const int GameEngine::LEFT_KEY = SDL_SCANCODE_LEFT;
const int GameEngine::RIGHT_KEY = SDL_SCANCODE_RIGHT;
const int GameEngine::W_KEY = SDL_SCANCODE_W;
const int GameEngine::A_KEY = SDL_SCANCODE_A;
const int GameEngine::S_KEY = SDL_SCANCODE_S;
const int GameEngine::D_KEY = SDL_SCANCODE_D;

GameEngine* GameEngine::gameEngineInstance;

GameEngine::GameEngine() {
	deltaTime = 0;	
	window = NULL;
	renderer = NULL;	

	initSDL();
	initGameWindow();
	initGLEW();	

	renderer = new Renderer(window);
}

GameEngine::~GameEngine() {
	delete window;
	delete renderer;
	delete gameEngineInstance;
	SDL_Quit();
}

GameEngine* GameEngine::getInstance() {
	if (!gameEngineInstance) {
		gameEngineInstance = new GameEngine();
	}
	return gameEngineInstance;
}

void GameEngine::initSDL(){
	if(0 != SDL_Init(SDL_INIT_EVERYTHING)){
		std::cout << "Error initializing SDL/n";
	}
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

void GameEngine::loadGame(Game* game){
	currentGame = game;
	int w = currentGame->getWidth();
	int h = currentGame->getHeight();
	window->setWindowSize(w, h);
	renderer->setDimensions((float)w, (float)h);
	window->setWindowTitle(currentGame->getTitle());
	window->setBackgroundColor(0.0f, 1.0f, 0.0f);
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
	
		int startTime = 0;
		int endTime = 0;

    	while(!quit){
			startTime = SDL_GetTicks();
	
			SDL_PumpEvents();
			const Uint8* keys = SDL_GetKeyboardState(NULL);

			if(keys[SDL_SCANCODE_ESCAPE]){
				quit = true;
			}		

			while(SDL_PollEvent(&event)){
            	if( event.type == SDL_QUIT ){
            		quit = true;
           		}

			}

			window->refresh();
			currentGame->update();	

			endTime = SDL_GetTicks();
			deltaTime = (float)(startTime - endTime) / 1000.0f;
		}
}

const Uint8* GameEngine::getKeyState(){
	return SDL_GetKeyboardState(NULL);
}

int GameEngine::getWindowWidth(){
	return window->getWindowWidth();
}

int GameEngine::getWindowHeight(){
	return window->getWindowHeight();
}





















