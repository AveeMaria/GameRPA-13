#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "Iceberg.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Utils.hpp"
#include "Cursor.hpp"
#include "Titlescreen.hpp"
#include "Whaler.hpp"
#include "Deathscreen.hpp"
#include "Atol.hpp"
#include "Replay.hpp"
#include "Leaderboards.hpp"

Player* player;

Map* map;
Cursor* cursor;

Titlescreen* titlescreen;
Deathscreen* deathscreen;

Leaderboards* leaderboards;

std::vector<Whaler*> Kitolovci;

std::vector<Iceberg*> LedeneGore;
std::vector<Enemy*> Sovrazniki;
std::vector<Atol*> Atoli;

Replay* replay;
bool GameObject::showHitboxes = false;
int Whaler::counter = 0; int Iceberg::counter = 0;

int targetX, targetY;

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	//damo ime playerja
	std::cout << "enter player name: ";
	std::cin >> playername;
	
	//leaderboards->DeleteRecords();//spuca cel file

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	leaderboards = new Leaderboards();
	replay = new Replay();
	cursor = new Cursor();
	player = new Player("assets/player.png", 0, 0);
	map = new Map();
	titlescreen = new Titlescreen();
	deathscreen = new Deathscreen();
	
	SpawnIcebergs(); SpawnKitolovci();
}

void Game::handleEvents() {
	SDL_PumpEvents();
	//utils/settings
	if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}
	
	if (currentKeyStates[SDL_SCANCODE_F1]) {
		paused = !paused;
		std::cout << paused << "\n";
	}
	if (currentKeyStates[SDL_SCANCODE_F3]) {
		GameObject::showHitboxes = !GameObject::showHitboxes;
	}
	if (currentKeyStates[SDL_SCANCODE_F4]) {
		keyboardMovement = !keyboardMovement;
	}

	//ce je paused game se nemors premikat
	if (paused) { return; }

	//controls
	if(keyboardMovement) {
	if (currentKeyStates[SDL_SCANCODE_W]) {
		//std::cout << "W\n";
		SDL_Rect playerFutureRect;
		playerFutureRect = player->GetPlayerRect();
		playerFutureRect.y -= player->GetPlayerStep();
		if (!map->LandCollision(playerFutureRect, Direction::Up)) {
			player->moveUp();
		}
	}
	if (currentKeyStates[SDL_SCANCODE_S]) {
		//std::cout << "S\n";
		SDL_Rect playerFutureRect;
		playerFutureRect = player->GetPlayerRect();
		playerFutureRect.y += player->GetPlayerStep();
		if (!map->LandCollision(playerFutureRect, Direction::Down)) {
			player->moveDown();
		}
	}
	if (currentKeyStates[SDL_SCANCODE_A]) {
		//std::cout << "A\n";
		SDL_Rect playerFutureRect;
		playerFutureRect = player->GetPlayerRect();
		playerFutureRect.x -= player->GetPlayerStep();
		if (!map->LandCollision(playerFutureRect, Direction::Left)) {
			player->moveLeft();
		}
	}
	if (currentKeyStates[SDL_SCANCODE_D]) {
		//std::cout << "D\n";
		SDL_Rect playerFutureRect;
		playerFutureRect = player->GetPlayerRect();
		playerFutureRect.x += player->GetPlayerStep();
		if (!map->LandCollision(playerFutureRect, Direction::Right)) {
			player->moveRight();
		}
	}
	}

	//kys mode
	if (currentKeyStates[SDL_SCANCODE_X]) {
		if (!titlescreen->GetVisible()) {
			targetX = (float)0;
			targetY = (float)0;
			player->KYS();
		}
	}

	if (currentKeyStates[SDL_SCANCODE_SPACE]) {
		//da ne kaze vec titlescreena
		titlescreen->SetVisible(false);
	}

	//switcha med levli
	if (currentKeyStates[SDL_SCANCODE_1]) {
		map->LoadMapLVLselect(1);
		SpawnIcebergs(); SpawnKitolovci();
	}
	if (currentKeyStates[SDL_SCANCODE_2]) {
		map->LoadMapLVLselect(2);
		SpawnGusarji(); SpawnKitolovci();
	}
	if (currentKeyStates[SDL_SCANCODE_3]) {
		map->LoadMapLVLselect(3);
		SpawnAtoli(); SpawnKitolovci();
	}
	if (currentKeyStates[SDL_SCANCODE_I]) {
		player->ToggleImmortalMode();
	}
	//izpise leaderboards
	if (currentKeyStates[SDL_SCANCODE_L]) {
		leaderboards->IzpisDatoteke();
	}
		
	//player gre nekam
	int mouseX, mouseY;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&mouseX, &mouseY);
				std::cout << "Mouse Clicked at: (" << mouseX << ", " << mouseY << ")" << std::endl;
				//pristejemo 25 kar je polovica plajer w/h
				targetX = (float)mouseX;
				targetY = (float)mouseY;
			}
			break;
		}
	}

	// Move towards the target coordinates
	if (targetX - 25 != -1 && targetY - 25 != -1) {
		cursor->setXY(targetX - 25, targetY - 25);
		if (!keyboardMovement) {
			player->moveTowardsCoords(targetX - 25, targetY - 25,map);
		}		
	}
}

void Game::update() {
	if (titlescreen->GetVisible()) {
		titlescreen->Update();
		return;
	}

	if (deathscreen->GetVisible()) {
		//ce je prvi gumb je respawn
		if (deathscreen->CheckButtonClick(targetX, targetY)==1) {
			//std::cout << "button 2 clicked\n";

			deathscreen->SetVisible(false);
			map->LoadMapLVLselect(1);
			SpawnIcebergs();
			
			//player->SetHealth(100);
		}
		//ce je drugi je titlescreen
		else if(deathscreen->CheckButtonClick(targetX, targetY)==2) {
			//std::cout << "button 2 clicked\n";

			titlescreen->SetVisible(true);
		}
		else {
			//std::cout << "button not clicked\n";
		}
		player = new Player("assets/player.png", 0, 0);
		deathscreen->Update();
		return;
	}

	//ce je player mrtev
	if (!player->alive()) {
		//k player umre narise deathscreen

		if (player->getSui()) {
			leaderboards->SortiranVpis(Zapis{ playername,player->GetScore() /* / (int)cnt */ });//vpise score in playjerja
		}
		leaderboards->IzpisDatoteke();//izpise leaderboards
		deathscreen->SetVisible(true);return;
	}
	//ce je ziv player
	else {
		replay->ReplaySave(player->GetPlayerRect());//recorda playerja not

	}
	//trentuno gameenda, drgac klice death screen
	
	player->Update();
	cursor->Update();
	
	/*
	if (map->LandCollision(player->GetPlayerRect())) {
		std::cout << cnt << "collided\n"; ++cnt;
	}*/

	//Player-Iceberg //in Whaler-Iceberg Collision
	if (map->GetcurrLvl() == 1) {
		for (auto it = LedeneGore.begin(); it != LedeneGore.end(); ++it) {
			Iceberg* i = *it;
			//detecta collision z playerjem
			if (player->collision(i->GetIcebergRect())) {
				player->takeDamage(25);
				player->Addscore(-25);
				std::cout << "player collided with ID: " << i->ReturnID() << "\n";
				LedeneGore.erase(it);
				break;
			}
			else {
				i->move(map);
				i->Update();
			}
			//tega kinda nerabm kr gusarji pa icebergni niso na istih levlih tkoda se ne collidajo
			/*
			bool EnemyIcebergCollided = false;
			//detecta collision z Iceberg-Whaler
			for (auto it2 = Sovrazniki.begin(); it2 != Sovrazniki.end(); ++it2) {
				Enemy* e = *it2;
				if (e->collision(i->GetIcebergRect())) {
					EnemyIcebergCollided = true;
					e->takeDamage(25);
					std::cout << "enemy collided with ID: " << i->ReturnID() << "\n";
					LedeneGore.erase(it);
					break;
				}
				else {
					e->Update();
				}
			}
			if (EnemyIcebergCollided) {
				break;
			}*/
			
		}
	}

	//enemy = gusar
	if (map->GetcurrLvl() == 2) {
		for (auto it = Sovrazniki.begin(); it != Sovrazniki.end(); ++it) {
			Enemy* e = *it;
			//ce je enemy ziv gre prot playerju
			if (e->alive()) {
				e->moveTowardsPlayer(player->getX(), player->getY(),map);
				if (player->collision(e->GetEnemyRect())) {
					player->takeDamage(1000);//pac crknes lol
					player->Addscore(player->GetScore());//score na 0
				}
				e->Update();
			}
			//ce je enemy mrtev ga deleta iz vectorja
			else {
				Sovrazniki.erase(it);
				break;
			}
		}
	}

	for (auto it = Kitolovci.begin(); it != Kitolovci.end(); ++it) {
		Whaler* w = *it;
		
		//ce je whaler mrtev ga deleta iz vectorja
		if(player->collision(w->GetWhalerRect())) {
				std::cout<<"Player collided with whaler\n";
				w->takeDamage(100);
				player->Addscore(100);			
			Kitolovci.erase(it);
			break;
		}
		//ce je whaler ziv zacne wanderat
		else if(w->alive()) {
			if (w->distance(player->getX(), player->getY()) > w->getTriggerDistance()) {
				w->move(map);
			}
			else {
				w->moveAwayFromPlayer(player->getX(), player->getY(),map);
			}		
			w->Update();
		}
	}

	for (auto it = Atoli.begin(); it != Atoli.end(); ++it) {
		Atol* a = *it;

		//ce zadanes atol zgine al neki whaler ga nemore zadet kr cene bi ga prehit unicu
		if (player->collision(a->GetAtolRect())) {
			std::cout << "Player collided with whaler\n";
			player->takeDamage(25);
			player->Addscore(-25);
			//player->Addscore(player->GetScore());//score na 0
			Atoli.erase(it);
			break;
		}
		a->TryToGrow();
		a->Update();
	}
}

void Game::render() {
	++cnt;
	//std::cout << cnt << "\n";

	SDL_RenderClear(renderer);
	//ne rise stvari ce je naslovnica odprta
	if (titlescreen->GetVisible()) {
		titlescreen->Render();
		SDL_RenderPresent(renderer);
		return;
	}

	//ne rise stvari ce je deathscreen on=playermrtev
	if (deathscreen->GetVisible()) {
		player->ReplayMode(replay);
		deathscreen->Render();
		SDL_RenderPresent(renderer);
		return;
	}

	map->DrawMap();
	player->Render();
	
	switch (map->GetcurrLvl()) {
	case 1:
		//std::cout << "risem ledene gore\n";
		for (Iceberg* i : LedeneGore) {
			i->Render();
		}
		break;
	case 2:
		//std::cout << "risem gusarje\n";
		for (Enemy* e : Sovrazniki) {
			e->Render();
		}
		break;
	case 3:
		//std::cout << "risem atole\n";
		for (Atol* e : Atoli) {
			e->Render();
		}
		break;
	default:
		std::cout << "tuki neki ne stima :3\n";
	}
	
	for (auto w : Kitolovci) {
		//ce je predelec ga ne rendera
		if (w->distance(player->getX(), player->getY()) <= player->getRenderDistance()) {
			w->Render();
		}
	}
	//mjav
	cursor->Render();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	//std::cout << "\nscore: " << (int) player->GetScore() / cnt << "\n";
	//Leaderboards::WriteSortedLeaderboards("leaderboard.txt", playername, score);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned\n";
}


void Game::SpawnIcebergs()
{
	LedeneGore.clear();
	//ustvari 10 ledenih gor
	for (int i = 0; i < 15; ++i) {
		Iceberg* ledenagora;
		do {
			//nardi nov iceberg
			ledenagora = new Iceberg;//((rand() % 16) * 50, (rand() % 12) * 50);
			//ledenagora->izpis();
			//ce se spawna v del landa ga prestavi?
		} while (map->LandCollision(ledenagora->GetIcebergRect()));

		ledenagora->izpis();
		LedeneGore.emplace_back(ledenagora);
	}
	std::cout << "\n";
}

void Game::SpawnGusarji()
{
	Sovrazniki.clear();
	//spawna enemyje
	for (int i = 0; i < 2 * (map->GetcurrLvl()) + 1; ++i) {
		Enemy* enemy;

		do {
			//nardi novga enemyja
			enemy = new Enemy;
			//ce se spawna v del landa ga prestavi?
		} while (map->LandCollision(enemy->GetEnemyRect()));

		Sovrazniki.push_back(enemy);
		//Sovrazniki.emplace_back(enemy);
	}
}

void Game::SpawnAtoli()
{
	Atoli.clear();
	//spawna enemyje
	for (int i = 0; i < 2 * (map->GetcurrLvl()) + 1; ++i) {
		Atol* atol;

		do {
			//nardi novga enemyja
			atol = new Atol();
			//ce se spawna v del landa ga prestavi?
		} while (map->LandCollision(atol->GetAtolRect()));

		Atoli.emplace_back(atol);
	}
}

void Game::SpawnKitolovci() {
	Kitolovci.clear();
	//spawna whalerje
	for (int i = 0; i < 2 * (map->GetcurrLvl()) + 1; ++i) {
		Whaler* whaler;

		do {
			whaler = new Whaler;
			//ce se spawna v del landa ga prestavi?
		} while (map->LandCollision(whaler->GetWhalerRect()));

		Kitolovci.emplace_back(whaler);
	}
}

//k ubijs use kitolovce gres na nov level
void Game::NextLevel()
{

	if (map->GetcurrLvl() >= 1 && map->GetcurrLvl() <= 3) {
		switch (Kitolovci.size()) {
		case 1:
			map->LoadMapLVLselect(1);
			SpawnIcebergs(); SpawnKitolovci();
			break;
		case 2:
			map->LoadMapLVLselect(2);
			SpawnGusarji(); SpawnKitolovci();
			break;
		case 3:
			map->LoadMapLVLselect(3);
			SpawnAtoli(); SpawnKitolovci();
			break;
		default:
			break;
		};
	}
}
