#include "GameEngine/GameEngine.h"
#include "PongGame.h"

int main(){
	PongGame g;
	GameEngine::getInstance()->loadGame(&g);
	GameEngine::getInstance()->startGame();
	
	return 0;
}

/*#include <iostream>
#include "SDL2/SDL.h"

int main(){
	SDL_Init(SDL_INIT_EVERYTHING);	
		
	SDL_GameController *controller = NULL;
		
	SDL_Window* window = SDL_CreateWindow("test", 0, 0, 0, 0, SDL_WINDOW_SHOWN);
	SDL_RaiseWindow(window);

	for(int i = 0; i < SDL_NumJoysticks(); i++){
		if(SDL_IsGameController(i)){
			controller = SDL_GameControllerOpen(i);
			break;
		}
	}
	
	

	bool running = true;
	SDL_Event e;

	while(running){
		while(SDL_PollEvent(&e) != 0){
			
			if(e.type == SDL_CONTROLLERBUTTONDOWN){
				if(e.cbutton.button == SDL_CONTROLLER_BUTTON_A){
					std::cout << "HOLLA!!\n";
				}else if(e.cbutton.button == SDL_CONTROLLER_BUTTON_B){
					running = false;
				}
			}
		}
	}
	
	SDL_GameControllerClose(controller);
	return 0;
}*/
 
