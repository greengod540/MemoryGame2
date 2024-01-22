#include "LevelLoader.h"
#include "SoundManager.h"

SoundManager soundMan;

template<typename... Args>
void LevelLoader::objectAdder(const Args&... newObjects) {
    Levelobjects.clear();
    (Levelobjects.push_back(newObjects), ...);
}

void LevelLoader::levelInit()
{

    levels.push_back(std::bind(&LevelLoader::level1, this));
    levels.push_back(std::bind(&LevelLoader::level2, this));
    
}

void LevelLoader::LevelRenderer() {
    for (int i = 0; i < Levelobjects.size(); i++) {
        drawObject(Levelobjects[i]);
    }
}
void LevelLoader::Levelloader()
{


	if (Level > 0 && Level <= levels.size()) {

		levels[Level - 1]();

	}
	else {
		std::cout << "Cannot load level: " << Level << std::endl;
	}
}
void LevelLoader::level1()
{

	
	if (init == 0) {
		background.rect = { 0, 0, 1920, 1080 };
		background.texture = loadTexture(BACKGROUND_FOLDER + "Background1.bmp");
		player.init();
		init = 1;
	}
	

	drawObject(background);
	player.draw();
	player.update();
	if (isMouseInRect(InputManager::m_mouseCoor, player.m_player.rect) && InputManager::isMousePressed())
	{
		dialogue_engaged = true;
		dg.filenameStart = "playerone.txt";
	}
	if (dialogue_engaged) {
		player.playerHidden = true;
		background.rect = { 0, 0, 0, 0 };
		dg.conversation = true;
		dg.readFile(DIALOGUE_FOLDER + dg.filenameStart); // 571 0 700 300
		dg.optionInteract();
	}
	if (!dg.conversation) {
		dialogue_engaged = false;
		player.playerHidden = false;
		background.rect = { 0, 0, 1920, 1080 };
		

	}
	if (isRobotTriggered) {
		SoundManager::playSound(ALARM);
	}
	if (colliding(player.m_player.rect, { 571, 0, 700, 100 }, 0, 0)) {
		player.destroy();
		SDL_DestroyTexture(background.texture);
		Level++;
		playerAnimator.resetFrame();
		std::cout << "Collision Detected! Level increased." << std::endl;
		
	}
	std::cout << "X: " << InputManager::m_mouseCoor.x << " " << "Y: " << InputManager::m_mouseCoor.y << std::endl;
}

void LevelLoader::level2()
{
	soundMan.init();

	
	if (init2 == 0) {
		playerTalk.animation = playerAnimator.init("ClayHeads\\Player\\Talking\\", 6, ".bmp");
		background.texture = loadTexture("Interiors\\Level2\\Lobby.bmp");
		txtBox.texture = loadTexture("TextBox.bmp");
		txtBox.rect = { 500, 700, 900, 300 };
		
		init2 = 1;
	}

	// Check if the timer has expired
	

	// Continue with other code
	string text = "Why is the lobby empty?";
	Presenter::drawObject(background);
	if (Timer(2)) {
		
		playerTalk.object.rect = { txtBox.rect.x - 200, txtBox.rect.y + txtBox.rect.h / 2, 200, 200 };
		playerTalk.object.texture = playerAnimator.returnFrame(playerTalk.animation, true);
		Presenter::drawObject(playerTalk.object);
		Presenter::drawObject(txtBox);
		Text_Creator::TextCreate("font\\BulzingItalic.ttf", 27, txtBox.rect.x + txtBox.rect.w / 2 - 400, 700 + txtBox.rect.h / 2, 800, 50, text.c_str(), { 255, 255, 255, 255 });

	}
	else if(!Timer(2)){
		SDL_DestroyTexture(playerTalk.object.texture);
		playerTalk.object.rect = { 0, 0, 0, 0 };
	}
	if (isMouseInRect(InputManager::m_mouseCoor, { 500, 233, 500, 600 }) && InputManager::isRMousePressed()) {
		dg.filenameStart = "RobotGuard1.txt";
		dialogue_engaged = true;
		dg.conversation = true;
		
	
	
	}
	if (dg.conversation) {
		dg.readFile(DIALOGUE_FOLDER + dg.filenameStart);
		dg.optionInteract();

	}

	if (dg.filenameStart == "RobotGuardTriggered.txt") {
		isRobotTriggered = true;
	}
	if (isRobotTriggered == true) {
		SoundManager::playSound(ALARM);
		std::cout << SoundManager::Alarm;
		isRobotTriggered = false;
	}
	
	





	
}
