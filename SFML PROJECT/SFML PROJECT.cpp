#include<SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>
#include<string>
#include<fstream>

/*FUNCTION TO WRITE IN FILE*/
void writeToFile(const std::string& filename, const std::string& content) {
	std::ofstream file(filename, std::ios::app);
	if (file.is_open()) {
		file << content << std::endl;
		file.close();
	}
	else {
		std::cout << "Error: Could not open file." << std::endl;
	}
}
/*FUNCTION TO READ THE RESULTS FROM FILE*/
void viewGameResults(const std::string& filename) {
	std::ifstream file(filename);
	std::string line;

	if (file.is_open()) {
		std::cout << "\n--- Game Results History ---\n";
		bool hasResults = false;
		while (std::getline(file, line)) {
			std::cout << line << std::endl;
			hasResults = true;
		}
		if (!hasResults) {
			std::cout << "No past game results found.\n";
		}
		std::cout << "--------------------------\n";
		file.close();
	}
	else {
		std::cout << "\nNo game results file found. Play a game to create one!\n";
	}
}

// Function to delete game results from file
void deleteGameResults(const std::string& filename) {
	std::cout << "\nAre you sure you want to delete all game results? (y/n): ";
	char choice;
	std::cin >> choice;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

	if (choice == 'y' || choice == 'Y') {
		std::ofstream file(filename, std::ios::trunc); 
		if (file.is_open()) {
			std::cout << "Game results have been cleared.\n";
			file.close();
		}
		else {
			std::cout << "Error: Could not access game results file to clear.\n";
		}
	}
	else {
		std::cout << "Deletion cancelled.\n";
	}
}


int main() {


	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "window", sf::Style::Fullscreen);


	sf::Text startButton, exitButton;

	sf::Font font;
	if (!font.loadFromFile("Kenney Future Narrow.ttf")) {
		std::cout << "Failed to load font!" << std::endl;
		return -1;
	}


	/*START BUTTON*/
	startButton.setFont(font);
	startButton.setString("Start Game");
	startButton.setCharacterSize(60);
	startButton.setOutlineColor(sf::Color::Black);
	startButton.setOutlineThickness(10);
	startButton.setFillColor(sf::Color::Green);
	startButton.setPosition(760, 600);
	/*EXIT BUTTON*/
	exitButton.setFont(font);
	exitButton.setString("Exit");
	exitButton.setCharacterSize(60);
	exitButton.setFillColor(sf::Color::Red);
	exitButton.setOutlineColor(sf::Color::Black);
	exitButton.setOutlineThickness(10);
	exitButton.setPosition(870, 690);
	/* MENU BACKGROUND*/
	sf::Texture bgtexture;
	bgtexture.loadFromFile("dbzbg.PNG");
	sf::Sprite bgsprite;
	bgsprite.setTexture(bgtexture);
	sf::Vector2u asize = window.getSize();
	float scaleX = static_cast<float>(asize.x) / bgtexture.getSize().x;
	float scaleY = static_cast<float>(asize.y) / bgtexture.getSize().y;
	bgsprite.setScale(scaleX, scaleY);
	/*GAME BACKGROUND*/
	sf::Texture gamebgtexture;
	gamebgtexture.loadFromFile("namek.PNG");
	sf::Sprite gamebgsprite;
	gamebgsprite.setTexture(gamebgtexture);
	sf::Vector2u bsize = window.getSize();
	float scaleA = static_cast<float>(bsize.x) / gamebgtexture.getSize().x;
	float scaleB = static_cast<float>(bsize.y) / gamebgtexture.getSize().y;
	gamebgsprite.setScale(scaleA, scaleB);

	/*GOKU MOVEMENTS*/
	sf::Texture Goku_idle;
	Goku_idle.loadFromFile("goku_idle.PNG");
	sf::Sprite Gokusprite;
	Gokusprite.setTexture(Goku_idle);
	Gokusprite.setScale(0.6f, 0.6f);
	Gokusprite.setPosition(100, 300);
	/*RIGHT*/
	sf::Texture Goku_right;
	Goku_right.loadFromFile("goku_right.PNG");
	sf::Sprite GokuRightSprite;
	GokuRightSprite.setTexture(Goku_right);
	GokuRightSprite.setScale(0.6f, 0.6f);
	/*LEFT*/
	sf::Texture Goku_left;
	Goku_left.loadFromFile("goku_left.PNG");
	sf::Sprite GokuLeftSprite;
	GokuLeftSprite.setTexture(Goku_left);
	GokuLeftSprite.setScale(0.7f, 0.7f);
	/*UP*/
	sf::Texture Goku_up;
	Goku_up.loadFromFile("goku_right.PNG");
	sf::Sprite GokuupSprite;
	GokuupSprite.setTexture(Goku_up);
	GokuupSprite.setScale(0.6f, 0.6f);
	/*DOWN*/
	sf::Texture Goku_down;
	Goku_down.loadFromFile("goku_left.PNG");
	sf::Sprite GokuDownSprite;
	GokuDownSprite.setTexture(Goku_down);
	GokuDownSprite.setScale(0.7f, 0.7f);
	/*GOKU ATTACKS*/
	/*PUNCH*/
	sf::Texture Goku_Punch;
	Goku_Punch.loadFromFile("Gpunch.PNG");
	sf::Sprite GokuPunchSprite;
	GokuPunchSprite.setTexture(Goku_Punch);
	GokuPunchSprite.setScale(1.3f, 1.3f);
	/*DOUBLE KICK*/
	sf::Texture D_kick;
	D_kick.loadFromFile("d_kick.PNG");
	sf::Sprite DkickSprite;
	DkickSprite.setTexture(D_kick);
	DkickSprite.setScale(1.3f, 1.3f);
	/*PUNCH 1*/
	sf::Texture Gpunch1;
	Gpunch1.loadFromFile("Gpunch1.PNG");
	sf::Sprite Gpunch1Sprite;
	Gpunch1Sprite.setTexture(Gpunch1);
	Gpunch1Sprite.setScale(1.3f, 1.3f);
	/*KICK*/
	sf::Texture Kick;
	Kick.loadFromFile("kick.PNG");
	sf::Sprite KickSprite;
	KickSprite.setTexture(Kick);
	KickSprite.setScale(1.3f, 1.3f);


	/*VEGETA MOVEMENTS*/
	sf::Texture Vegeta_idle;
	Vegeta_idle.loadFromFile("Vegeta_idle.PNG");
	sf::Sprite VegetaSprite;
	VegetaSprite.setTexture(Vegeta_idle);
	VegetaSprite.setScale(0.75f, 0.75f);
	VegetaSprite.setPosition(800, 300);




	sf::Texture Vegetaleft;
	Vegetaleft.loadFromFile("Vegeta_left.PNG");
	sf::Sprite VegetaLeftSprite;
	VegetaLeftSprite.setTexture(Vegetaleft);
	VegetaLeftSprite.setScale(1.2f, 1.2f);

	sf::Texture Vegetadown;
	Vegetadown.loadFromFile("Vegeta_left.PNG");
	sf::Sprite VegetaDownSprite;
	VegetaDownSprite.setTexture(Vegetadown);
	VegetaDownSprite.setScale(1.2f, 1.2f);


	sf::Texture VegetaRight;
	VegetaRight.loadFromFile("Vegeta_right.PNG");
	sf::Sprite VegetaRightSprite;
	VegetaRightSprite.setTexture(VegetaRight);
	VegetaRightSprite.setScale(1.2f, 1.2f);

	sf::Texture VegetaUp;
	VegetaUp.loadFromFile("Vegeta_right.PNG");
	sf::Sprite VegetaUpSprite;
	VegetaUpSprite.setTexture(VegetaUp);
	VegetaUpSprite.setScale(1.2f, 1.2f);



	/*VEGETA ATTACKS*/
	/*PUNCH*/
	sf::Texture Vpunch;
	Vpunch.loadFromFile("Vpunch.PNG");
	sf::Sprite VpunchSprite;
	VpunchSprite.setTexture(Vpunch);
	VpunchSprite.setScale(1.6f, 1.6f);
	/*PUNCH 1*/
	sf::Texture Vpunch1;
	Vpunch1.loadFromFile("Vpunch1.PNG");
	sf::Sprite Vpunch1Sprite;
	Vpunch1Sprite.setTexture(Vpunch1);
	Vpunch1Sprite.setScale(1.6f, 1.6f);
	/*Kick*/
	sf::Texture v_kick;
	v_kick.loadFromFile("vkick.PNG");
	sf::Sprite VKickSprite;
	VKickSprite.setTexture(v_kick);
	VKickSprite.setScale(1.6f, 1.6f);
	/*Double Kick*/
	sf::Texture v_dkick;
	v_dkick.loadFromFile("vdkick.PNG");
	sf::Sprite VDKickSprite;
	VDKickSprite.setTexture(v_dkick);
	VDKickSprite.setScale(1.9f, 1.9f);



	/*GAME OVER */
	sf::Text gameOver;
	gameOver.setFont(font);
	gameOver.setFillColor(sf::Color::Red);
	gameOver.setOutlineColor(sf::Color::Black);
	gameOver.setCharacterSize(60);
	gameOver.setOutlineThickness(3);
	gameOver.setPosition(750,400);
	gameOver.setString("Game Over !!");


	/*BOOLEAN VARIABELS*/
	bool gameover = false;
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	bool idle = true;
	bool punch = false;
	bool dkick = false;
	bool punch1 = false;
	bool kick = false;

	bool gokuHealthReduced = false;
	bool vegetaHealthReduce = false;


	//Vegeta bools//
	bool vup = false;
	bool vdown = false;
	bool vleft = false;
	bool vright = false;
	bool vidle = false;



	/*VEGETA ATTACKS*/
	/*PUNCH*/
	bool vpunch = false;
	/*PUNCH 1*/
	bool vpunch1 = false;
	/*KICK*/
	bool vkick = false;
	/*Double kick*/
	bool vd_kick = false;

	


	/*POSITION OF IDLE STATE GOKU*/
	sf::Vector2f gokuPosition = Gokusprite.getPosition();
	/*POSITION OF IDLE STATE VEGETA*/
	sf::Vector2f vegetaPosition = VegetaSprite.getPosition();


	int gokuHealth = 100;
	const int maxHealth = 100;

	sf::RectangleShape healthBarBack(sf::Vector2f(200.f, 20.f));
	healthBarBack.setFillColor(sf::Color::Red);
	healthBarBack.setOutlineThickness(3);
	healthBarBack.setOutlineColor(sf::Color::Black);
	healthBarBack.setPosition(50.f, 50.f);

	sf::RectangleShape healthBarFront(sf::Vector2f(200.f, 20.f));
	healthBarFront.setFillColor(sf::Color::Green);
	healthBarFront.setPosition(50.f, 50.f);


	sf::RectangleShape VhealthBarBack(sf::Vector2f(200.f, 20.f));
	VhealthBarBack.setFillColor(sf::Color::Red);
	VhealthBarBack.setOutlineThickness(3);
	VhealthBarBack.setOutlineColor(sf::Color::Black);
	VhealthBarBack.setPosition(1650.f, 50.f);

	sf::RectangleShape VhealthBarFront(sf::Vector2f(200.f, 20.f));
	VhealthBarFront.setFillColor(sf::Color::Green);
	VhealthBarFront.setPosition(1650.f, 50.f);



	int count = 0;

	int vegetahealth = 100;

	const int vMaxhealth = 100;

	/*Engery bar*/
	int GokuEnergy = 0;
	int MaxEnergy = 100;

	int VegetaEnergy = 0;

	sf::RectangleShape EnergyBarBack(sf::Vector2f(200.f, 20.f));
	EnergyBarBack.setFillColor(sf::Color::White);
	EnergyBarBack.setOutlineThickness(3);
	EnergyBarBack.setOutlineColor(sf::Color::Black);
	EnergyBarBack.setPosition(50.f, 100.f);

	sf::RectangleShape EnergyBarFront(sf::Vector2f(200.f, 20.f));
	EnergyBarFront.setFillColor(sf::Color::Blue);
	EnergyBarFront.setPosition(50.f, 100.f);


	sf::RectangleShape VEnergyBarBack(sf::Vector2f(200.f, 20.f));
	VEnergyBarBack.setFillColor(sf::Color::White);
	VEnergyBarBack.setOutlineThickness(3);
	VEnergyBarBack.setOutlineColor(sf::Color::Black);
	VEnergyBarBack.setPosition(1650.f, 100.f);

	sf::RectangleShape VEnergyBarFront(sf::Vector2f(200.f, 20.f));
	VEnergyBarFront.setFillColor(sf::Color::Blue);
	VEnergyBarFront.setPosition(1650.f, 100.f);

	

	sf::Clock GokuChargeClock;
	sf::Time gokuEnergyChargeInterval = sf::seconds(0.1f);

	sf::Clock VegetaChargeClock;
	sf::Time VegetaEnergyChargeInterval = sf::seconds(0.1f);

	sf::Clock GokuEnergyDepletion;
	sf::Time  GokuEnergyDepletionInterval = sf::seconds(0.05f);

	sf::Clock EnergyDepletion;
	sf::Time  EnergyDepletionInterval = sf::seconds(0.05f);

	

	/*Adding sounds to the game */

	/*DBZ THEME SONG*/
	sf::SoundBuffer theme;
	theme.loadFromFile("dbz_theme_song.mp3");

	sf::Sound themesong;
	themesong.setBuffer(theme);
	themesong.play();

	/*FLYING/MOVEMENT SOUND (GOKU)*/

	bool ismoving = false;  /*To check wether the player is in motion or not */

	sf::SoundBuffer flying;
	flying.loadFromFile("Flying.mp3");

	sf::Sound Flying;
	Flying.setBuffer(flying);

	/*ATTACK*/

	bool ispunching = false;  /*To check wether the player is Attacking or not */

	sf::SoundBuffer punching;
	punching.loadFromFile("punch.mp3");

	sf::Sound Punching;
	Punching.setBuffer(punching);

	/*ADDING SOUND (VEGETA)*/

	 /*FLYING/MOVEMENT SOUND*/

	bool isvmoving = false;

	sf::SoundBuffer vflying;
	vflying.loadFromFile("Flying.mp3");

	sf::Sound VFlying;
	VFlying.setBuffer(vflying);

	/*ATTACKING SOUNDS VEGETA*/

	bool isvattacking = false;

	sf::SoundBuffer vattacksound;
	vattacksound.loadFromFile("punch.mp3");

	sf::Sound VAttackSound;
	VAttackSound.setBuffer(vattacksound);






	/*GAME OVER SOUND*/

	sf::SoundBuffer GameOversound;
	GameOversound.loadFromFile("gameover.mp3");

	sf::Sound GameOverSound;
	GameOverSound.setBuffer(GameOversound);
	GameOverSound.setVolume(100);



	/*DECLARING THE WINNER */

	bool gokuwins = false;
	bool vegetawins = false;
	bool gokudead = false;
	bool vegetadead = false;


	sf::Text gokuWins;
	gokuWins.setFont(font);
	gokuWins.setFillColor(sf::Color(255, 165, 0)); //ORANGE
	gokuWins.setOutlineColor(sf::Color::Blue);
	gokuWins.setCharacterSize(80);
	gokuWins.setOutlineThickness(2);
	gokuWins.setPosition(700, 500);
	gokuWins.setString("GOKU WINS !!");


	sf::Text Vegetawins;
	Vegetawins.setFont(font);
	Vegetawins.setFillColor(sf::Color(220, 220, 220)); // Light Gray
	Vegetawins.setOutlineColor(sf::Color::Blue);
	Vegetawins.setCharacterSize(80);
	Vegetawins.setOutlineThickness(3);
	Vegetawins.setPosition(650, 500);
	Vegetawins.setString("VEGETA WINS !!");

	/*Goku Dead Sprite*/

	sf::Texture GokuDead;
	GokuDead.loadFromFile("goku-dead.PNG");

	sf::Sprite GokuDeadSprite;
	GokuDeadSprite.setTexture(GokuDead);
	GokuDeadSprite.setScale(1.5f, 1.5f);

	/*Veget Dead Sprite*/

	sf::Texture VegetaDead;
	VegetaDead.loadFromFile("vegeta-dead.PNG");

	sf::Sprite VegetaDeadSprite;
	VegetaDeadSprite.setTexture(VegetaDead);
	VegetaDeadSprite.setScale(1.2f, 1.2f);

	/*RETURN TO MAIN MENU BUTTON*/
	sf::Text mainMenuButton;
	mainMenuButton.setFont(font);
	mainMenuButton.setString("Return To Main Menu");
	mainMenuButton.setCharacterSize(70);
	mainMenuButton.setFillColor(sf::Color::Green);
	mainMenuButton.setOutlineColor(sf::Color::Black);
	mainMenuButton.setOutlineThickness(2);
	mainMenuButton.setPosition(550, 650);

	
	/*Goku and Vegeta Speed */
	float gokuspeed = 0.8f;
	float vegetaspeed = 0.8f;

	/*Special attacks*/
	bool Gspecial = false;

	sf::Texture GSpecial;
	GSpecial.loadFromFile("Gspecial.PNG");

	sf::Sprite GSpecialSprite;
	GSpecialSprite.setTexture(GSpecial);
	GSpecialSprite.setScale(1.5f, 1.5f);

	sf::Texture GAttack;
	GAttack.loadFromFile("G_Attack.PNG");

	sf::Sprite GAttackSprite;
	GAttackSprite.setTexture(GAttack);
	GAttackSprite.setScale(1.5f, 1.5f);

	bool Vspecial = false;

	sf::Texture VSpecial;
	VSpecial.loadFromFile("VSpecial.PNG");

	sf::Sprite VSpecialSprite;
	VSpecialSprite.setTexture(VSpecial);
	VSpecialSprite.setScale(1.2f, 1.2f);

	sf::Texture VAttack;
	VAttack.loadFromFile("V_Attack.PNG");

	sf::Sprite VAttackSprite;
	VAttackSprite.setTexture(VAttack);
	VAttackSprite.setScale(1.5f, 1.5f);

	/*Special Attack Sound*/

	sf::SoundBuffer SpecialAttack;
	SpecialAttack.loadFromFile("SpecialAttack.MP3");

	sf::Sound SpecialAttackSound;
	SpecialAttackSound.setBuffer(SpecialAttack);
	SpecialAttackSound.setVolume(100);



	//Special Attack Clocks
	sf::Clock GokuAttack;
	sf::Time GokuAttackInterval = sf::seconds(0.5f);

	sf::Clock VegetaAttack;
	sf::Time VegetaAttackInterval = sf::seconds(0.5f);



	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
				if (startButton.getGlobalBounds().contains(mousePos)) {
					themesong.stop();
					//This part resests the flags and positions
					gameover = false;
					gokuwins = false;
					vegetawins = false;
					gokudead = false;
					vegetadead = false;
					GokuEnergy = 0;
					GokuEnergy = 0;
					gokuHealth = 100;
					vegetahealth = 100;
					gokuPosition = sf::Vector2f(100, 300);
					vegetaPosition = sf::Vector2f(800, 300);

					//IT IS THE MOST IMPORTANT PART FOR RETURN TO MENU BUTTON


					while (window.isOpen()) {
						sf::Event gameEvent;



						if (!gameover) {
							
												//If you want to make game faster
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
								gokuspeed = 2.f;
								vegetaspeed = 2.f;
							}
							
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
								gokuPosition.y -= gokuspeed;
								up = true;
								down = false;
								right = false;
								left = false;
								idle = false;
								punch = false;
								dkick = false;
								punch1 = false;
								kick = false;
								ismoving = true;
								ispunching = false;
								


							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
								gokuPosition.y += gokuspeed;
								up = false;
								down = true;
								right = false;
								left = false;
								idle = false;
								punch = false;
								dkick = false;
								punch1 = false;
								kick = false;
								ismoving = true;
								ispunching = false;
								


							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
								gokuPosition.x += gokuspeed;
								up = false;
								down = false;
								right = true;
								left = false;
								idle = false;
								punch = false;
								dkick = false;
								punch1 = false;
								kick = false;
								ismoving = true;
								ispunching = false;
								

							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
								gokuPosition.x -= gokuspeed;
								up = false;
								down = false;
								right = false;
								left = true;
								idle = false;
								punch = false;
								dkick = false;
								punch1 = false;
								kick = false;
								ismoving = true;
								ispunching = false;
								

							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
								up = false;
								down = false;
								right = false;
								left = false;
								idle = false;
								punch = true;
								dkick = false;
								punch1 = false;
								kick = false;
								ismoving = false;
								ispunching = true;
								

							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
								up = false;
								down = false;
								right = false;
								left = false;
								idle = false;
								punch = false;
								dkick = true;
								punch1 = false;
								kick = false;
								ismoving = false;
								ispunching = true;
								
							}

							if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
								up = false;
								down = false;
								right = false;
								left = false;
								idle = false;
								punch = false;
								dkick = false;
								punch1 = true;
								kick = false;
								ismoving = false;
								ispunching = true;
								


							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
								up = false;
								down = false;
								right = false;
								left = false;
								idle = false;
								punch = false;
								dkick = false;
								punch1 = false;
								kick = true;
								ismoving = false;
								ispunching = true;



							}
							
							// Reset to idle if no key is pressed
							if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::Z) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::E) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {

								up = down = left = right = punch = dkick = punch1 = kick = ismoving = ispunching =  false;
								idle = true;
							}
											//SOUND LOGICS
							if (ismoving && Flying.getStatus() != sf::Sound::Playing) {
								Flying.play();
							}
							else if (!ismoving && Flying.getStatus() == sf::Sound::Playing) {
								Flying.stop();
							}
							if (ispunching && Punching.getStatus() != sf::Sound::Playing) {

								Punching.play();
							}
							else if (!ispunching && Punching.getStatus() == sf::Sound::Playing) {
								Punching.stop();
							}

							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

								vegetaPosition.y += vegetaspeed;
								vdown = true;
								vup = false;
								vleft = false;
								vright = false;
								vidle = false;
								vpunch1 = false;
								vpunch = false;
								vkick = false;
								vd_kick = false;
								isvmoving = true;
								isvattacking = false;


							}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

								vegetaPosition.y -= vegetaspeed;
								vdown = false;
								vup = true;
								vleft = false;
								vright = false;
								vidle = false;
								vpunch1 = false;
								vpunch = false;
								vkick = false;
								vd_kick = false;
								isvmoving = true;
								isvattacking = false;


							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

								vegetaPosition.x -= vegetaspeed;
								vdown = false;
								vup = false;
								vleft = true;
								vright = false;
								vidle = false;
								vpunch1 = false;
								vpunch = false;
								vkick = false;
								vd_kick = false;
								isvmoving = true;
								isvattacking = false;


							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

								vegetaPosition.x += vegetaspeed;
								vdown = false;
								vup = false;
								vleft = false;
								vright = true;
								vidle = false;
								vpunch1 = false;
								vpunch = false;
								vkick = false;
								vd_kick = false;
								isvmoving = true;
								isvattacking = false;


							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {


								vdown = false;
								vup = false;
								vleft = false;
								vright = false;
								vidle = false;
								vpunch1 = true;;
								vpunch = false;
								vkick = false;
								vd_kick = false;
								isvmoving = false;
								isvattacking = true;


							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {


								vdown = false;
								vup = false;
								vleft = false;
								vright = false;
								vidle = false;
								vpunch1 = false;;
								vpunch = true;
								vkick = false;
								vd_kick = false;
								isvmoving = false;
								isvattacking = true;


							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {


								vdown = false;
								vup = false;
								vleft = false;
								vright = false;
								vidle = false;
								vpunch1 = false;;
								vpunch = false;
								vkick = true;
								vd_kick = false;
								isvmoving = false;
								isvattacking = true;

							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {


								vdown = false;
								vup = false;
								vleft = false;
								vright = false;
								vidle = false;
								vpunch1 = false;;
								vpunch = false;
								vkick = false;
								vd_kick = true;
								isvmoving = false;
								isvattacking = true;


							}
							// Reset to idle if no key is pressed
							if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::I) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::L) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::O) &&
								!sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {

								vup = vdown = vleft = vright = vpunch = vd_kick = vpunch1 = vkick = isvmoving = isvattacking = false;
								vidle = true;
							}
							
							
							


							//The Block of code below is used to Keep the characters in bound
							
							float windowWidth = static_cast<float>(window.getSize().x);
							float windowHeight = static_cast<float>(window.getSize().y);

							//  For Goku
							// Get Goku's current bounds (position and size)
							sf::FloatRect gokuBounds = Gokusprite.getGlobalBounds();

							// Clamp Goku's X position
							if (gokuPosition.x < 0) {
								gokuPosition.x = 0;
							}
							else if (gokuPosition.x + gokuBounds.width > windowWidth) {
								gokuPosition.x = windowWidth - gokuBounds.width;
							}

							// Clamp Goku's Y position
							if (gokuPosition.y < 0) {
								gokuPosition.y = 0;
							}
							else if (gokuPosition.y + gokuBounds.height > windowHeight) {
								gokuPosition.y = windowHeight - gokuBounds.height;
							}

							// For Vegeta 

							sf::FloatRect vegetaBounds = VegetaSprite.getGlobalBounds();

							// Clamp Vegeta's X position
							if (vegetaPosition.x < 0) {
								vegetaPosition.x = 0;
							}
							else if (vegetaPosition.x + vegetaBounds.width > windowWidth) {
								vegetaPosition.x = windowWidth - vegetaBounds.width;
							}

							// Clamp Vegeta's Y position
							if (vegetaPosition.y < 0) {
								vegetaPosition.y = 0;
							}
							else if (vegetaPosition.y + vegetaBounds.height > windowHeight) {
								vegetaPosition.y = windowHeight - vegetaBounds.height;
							}
							if (isvmoving && VFlying.getStatus() != sf::Sound::Playing) {
								VFlying.play();
							}
							else if (!isvmoving && VFlying.getStatus() == sf::Sound::Playing) {
								VFlying.stop();
							}



							if (isvattacking && VAttackSound.getStatus() != sf::Sound::Playing) {

								VAttackSound.play();
							}
							else if (!isvattacking && VAttackSound.getStatus() == sf::Sound::Playing) {
								VAttackSound.stop();
							}

							if (punch && GokuPunchSprite.getGlobalBounds().intersects(VegetaSprite.getGlobalBounds()) ||
								punch1 && Gpunch1Sprite.getGlobalBounds().intersects(VegetaSprite.getGlobalBounds()) ||
								(dkick && DkickSprite.getGlobalBounds().intersects(VegetaSprite.getGlobalBounds())) ||
								(kick && KickSprite.getGlobalBounds().intersects(VegetaSprite.getGlobalBounds()))) {
								if (!vegetaHealthReduce) {
									vegetahealth -= 5.f;
									vegetaHealthReduce = true;
								}
							}
							else {
								vegetaHealthReduce = false;
							}


							if ((vpunch && VpunchSprite.getGlobalBounds().intersects(Gokusprite.getGlobalBounds())) ||
								(vpunch1 && Vpunch1Sprite.getGlobalBounds().intersects(Gokusprite.getGlobalBounds())) ||
								(vkick && VKickSprite.getGlobalBounds().intersects(Gokusprite.getGlobalBounds())) ||
								(vd_kick && VDKickSprite.getGlobalBounds().intersects(Gokusprite.getGlobalBounds()))) {

								if (!gokuHealthReduced) {
									count++;
									gokuHealth -= 5.f;
									gokuHealthReduced = true;
									
								}

							}
							else {

								gokuHealthReduced = false;
							}

							
							
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
								
								if (GokuChargeClock.getElapsedTime() >= gokuEnergyChargeInterval) {
									
									
									if (GokuEnergy < MaxEnergy) {
										GokuEnergy += 2; 
									}

									GokuChargeClock.restart();
								}
							}

							if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {

								if (VegetaChargeClock.getElapsedTime() >= VegetaEnergyChargeInterval) {
									
									if (VegetaEnergy < MaxEnergy) {
										VegetaEnergy += 2;
									}
									

									VegetaChargeClock.restart();
								}

							}
							if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::X))) {
								if (GokuEnergyDepletion.getElapsedTime() >= EnergyDepletionInterval) {
									if (GokuEnergy > 0) {
										GokuEnergy -= 1;
									}
									GokuEnergyDepletion.restart();
								}
							}
							if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::M))){
								if (EnergyDepletion.getElapsedTime() >= EnergyDepletionInterval) {
									if (VegetaEnergy > 0) {
										VegetaEnergy -= 1;
									}
									EnergyDepletion.restart();
								}
							}
							

							if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && GokuEnergy >= MaxEnergy && GokuAttack.getElapsedTime() >= GokuAttackInterval) {
								
								Gspecial = true;
								vegetahealth -= 50;
								GokuEnergy = 0; 
								SpecialAttackSound.play();
								GokuAttack.restart(); 

								up = down = right = left = idle = punch = dkick = punch1 = kick =  false;
							}

							
							if (Gspecial && GokuAttack.getElapsedTime() >= GokuAttackInterval) {
								Gspecial = false; 
								idle = true;   
								SpecialAttackSound.stop();
							}

							if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && VegetaEnergy >= MaxEnergy && VegetaAttack.getElapsedTime() >= VegetaAttackInterval) {

								Vspecial = true;
								gokuHealth -= 50;
								VegetaEnergy = 0;
								SpecialAttackSound.play();
								VegetaAttack.restart();

								vup= vdown = vright = vleft = vidle = vpunch = vd_kick = vpunch1 = vkick = false;
							}


							if (Vspecial && VegetaAttack.getElapsedTime() >= VegetaAttackInterval) {
								Vspecial = false;
								idle = true;
								SpecialAttackSound.stop();
							}


							if (gokuHealth == 0) {
								vegetawins = true;
								gameover = true;
								gokudead = true;
								up = down = right = left = punch = punch1 = kick = dkick = idle = false;
								writeToFile("GAME_RESULTS.txt", "VEGETA WON ");
							}
							if (vegetahealth == 0) {
								gokuwins = true;
								gameover = true;
								vegetadead = true;
								vup = vdown = vright = vleft = vpunch = vpunch1 = vd_kick = vkick = vidle = false;

								writeToFile("GAME_RESULTS.txt", "GOKU WON ");
							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))) {
								break;
							}
							if (gokuHealth == 0 || vegetahealth == 0) {
								GameOverSound.play();
							}
						}
						float healthPercent = static_cast<float>(gokuHealth) / maxHealth;
						healthBarFront.setSize(sf::Vector2f(200.f * healthPercent, 20.f));

						float VhealthPercent = static_cast<float>(vegetahealth) / vMaxhealth;
						VhealthBarFront.setSize(sf::Vector2f(200.f * VhealthPercent, 20.f));

						float EnergyPercent = static_cast<float>(GokuEnergy) / MaxEnergy;
						EnergyBarFront.setSize(sf::Vector2f(200.f * EnergyPercent, 20.f));

						float VEnergyPercent = static_cast<float>(VegetaEnergy) / MaxEnergy;
						VEnergyBarFront.setSize(sf::Vector2f(200.f * VEnergyPercent, 20.f));







						while (window.pollEvent(gameEvent)) {
							if (gameEvent.type == sf::Event::Closed)
								window.close();
						}



						window.clear();
						window.draw(gamebgsprite);
						window.draw(healthBarBack);
						window.draw(healthBarFront);
						window.draw(VhealthBarBack);
						window.draw(VhealthBarFront);
						window.draw(EnergyBarBack);
						window.draw(EnergyBarFront);
						window.draw(VEnergyBarBack);
						window.draw(VEnergyBarFront);
						if (gokuwins) {
							window.draw(gokuWins);
						}
						if (vegetawins) {
							window.draw(Vegetawins);
						}
						if (gokudead) {
							GokuDeadSprite.setPosition(gokuPosition);
							window.draw(GokuDeadSprite);
						}
						else if (Gspecial) {
							GSpecialSprite.setPosition(gokuPosition);
							window.draw(GSpecialSprite);

							GAttackSprite.setPosition(vegetaPosition);
							window.draw(GAttackSprite);
						}
						else if (right) {
							GokuRightSprite.setPosition(gokuPosition);
							window.draw(GokuRightSprite);
						}
						else if (left) {
							GokuLeftSprite.setPosition(gokuPosition);
							window.draw(GokuLeftSprite);
						}
						else if (up) {
							GokuupSprite.setPosition(gokuPosition);
							window.draw(GokuupSprite);
						}
						else if (down) {
							GokuDownSprite.setPosition(gokuPosition);
							window.draw(GokuDownSprite);
						}
						else if (punch) {
							GokuPunchSprite.setPosition(gokuPosition);
							window.draw(GokuPunchSprite);
						}
						else if (dkick) {
							DkickSprite.setPosition(gokuPosition);
							window.draw(DkickSprite);
						}
						else if (punch1) {
							Gpunch1Sprite.setPosition(gokuPosition);
							window.draw(Gpunch1Sprite);
						}
						else if (kick) {
							KickSprite.setPosition(gokuPosition);
							window.draw(KickSprite);
						}
						
						else {
							Gokusprite.setPosition(gokuPosition);
							window.draw(Gokusprite);
						}
						
						if (vegetadead) {
							VegetaDeadSprite.setPosition(vegetaPosition);
							window.draw(VegetaDeadSprite);
						}

						else {
							if (vright) {
								VegetaRightSprite.setPosition(vegetaPosition);
								window.draw(VegetaRightSprite);

							}
							else if (Vspecial) {
								VSpecialSprite.setPosition(vegetaPosition);
								window.draw(VSpecialSprite);

								VAttackSprite.setPosition(gokuPosition);
								window.draw(VAttackSprite);
							}

							else if (vleft) {
								VegetaLeftSprite.setPosition(vegetaPosition);
								window.draw(VegetaLeftSprite);


							}
							else if (vup) {
								VegetaUpSprite.setPosition(vegetaPosition);
								window.draw(VegetaUpSprite);

							}
							else if (vdown) {
								VegetaDownSprite.setPosition(vegetaPosition);
								window.draw(VegetaDownSprite);

							}
							else if (vpunch) {
								VpunchSprite.setPosition(vegetaPosition);
								window.draw(VpunchSprite);
							}
							else if (vpunch1) {
								Vpunch1Sprite.setPosition(vegetaPosition);
								window.draw(Vpunch1Sprite);

							}
							else if (vkick) {
								VKickSprite.setPosition(vegetaPosition);
								window.draw(VKickSprite);
							}
							else if (vd_kick) {
								VDKickSprite.setPosition(vegetaPosition);
								window.draw(VDKickSprite);
							}



							else {
								VegetaSprite.setPosition(vegetaPosition);
								window.draw(VegetaSprite);
							}
						}
						
						if (gameover) {
							window.draw(gameOver);
							window.draw(mainMenuButton);
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
								sf::Vector2f mousePosGame(sf::Mouse::getPosition(window));
								if (mainMenuButton.getGlobalBounds().contains(mousePosGame)) {
									break;
								}
							}
						}

						themesong.play();

						window.display();
					}
				}

				else if (exitButton.getGlobalBounds().contains(mousePos)) {
					window.close();
				}
			}
		}
		

		window.clear();
		window.draw(bgsprite);
		window.draw(startButton);
		window.draw(exitButton);
		window.display();
	}

	viewGameResults("Game_Results.txt");
	deleteGameResults("Game_Results.txt");


	return 0;


}









