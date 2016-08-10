
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
	if(0 != SDL_Init(SDL_INIT_EVERYTHING)){
		std::cout << "Error initializing SDL/n";
	}

	window = new GameWindow(900, 700, "PONG");
	window->setBackgroundColor(0.0f, 1.0f, 0.0f);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
  		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	
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

void GameEngine::startGame() {
	PongPaddle p(100, 500, 50, 200);	
	PongBall b(500, 500, 30, 30);	

	bool quit = false;
	 
	SDL_Event event;

    	while(!quit){
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
		p.update();
		b.update();
		p.draw(renderer);
		b.draw(renderer);
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






















