#include <Engine.h>
#include "Presenter.h"
#include "InputManager.h"
#include "Player.h"
#include "DialogueTree.h"
#include "LevelCounter.h"
#include <TextBox.h>
#include "SoundManager.h"
#include "Animator.h"
class LevelLoader {

public:
    std::vector<Drawable> Levelobjects;
    void levelInit();

    template<typename... Args>
    void objectAdder(const Args&... newObjects);

    void LevelRenderer();
    void Levelloader();
    void level1();
    void level2();
    void level3();
    Player player;
    Animator playerAnimator;
    Animation playerTalk;
    Drawable background;
    DialogueTree dg;

    int init = 0;
    int init2 = 0;
    int level = 1;
    int Level = 1;
    TextBox txtbox;
    Drawable txtBox;
    bool timerPassed = false;

};


