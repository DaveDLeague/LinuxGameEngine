
#include "GameEngine/GameEngine.h"
#include "GameEngine/GameObject.h"

GameEngine* GameEngine::gameEngineInstance;

GameEngine::GameEngine() {
	if(0 != SDL_Init(SDL_INIT_EVERYTHING)){
		std::cout << "Error initializing SDL/n";
	}

	window = new GameWindow(900, 700, "PONG");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
  		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	
	renderer = new Renderer();
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
	
	GameObject o(50, 50, 200, 200);
	GameObject g(50, 300, 100, 240);
	bool quit = false;
    	while(!quit){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
                	if( event.type == SDL_QUIT ){
                		quit = true;
               		}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			}

		}
		window->refresh();
		//renderer->refresh();
		o.draw(renderer);
		g.draw(renderer);
		o.update();
		g.update();
	}
}
