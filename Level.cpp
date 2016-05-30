//
// Created by blackdartq on 5/24/16.
//

#include "Level.h"
#include "Audio.h"


Character character;
Spider spider;
Spider spider2;
Tools tools;
Screen screen;
Entity entity;
SDL_Event event;
Audio audio1;


Level::Level() {


}

//used in a thread to move the character
void Level::moveCharacter() {
    //const Uint8 *state = SDL_GetKeyboardState(NULL);
    while (tools.checkIfRunning()) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_D:
                        //cout << "right" << character.entityRect.x << endl;
                        if (character.entityRect.x >= 600) {
                            //screen.moveScreenLeft();character.

                        } else {
                            character.moveEntityRight(character.characterStandingRight, character.entityRect,
                                                      character.facingRight, character.attackingRight);
                        }

                        //screen.moveScreen(character.entityRect);
                        //screen.moveGround(character.entityRect);
                        screen.moveScene(character.entityRect);
                        break;

                    case SDL_SCANCODE_A:
                        //cout << "Left" << character.entityRect.x << endl;

                        if (character.entityRect.x == 0 && screen.backgroundRect.x >= 0) {


                        } else if (character.entityRect.x == 0) {
                            //screen.moveScreenRight();

                        } else {
                            character.moveEntityLeft("Img/CharacterStandingLeft.bmp", character.entityRect,
                                                     character.facingRight, character.attackingRight);
                        }
                        //screen.moveScreen(character.entityRect);
                        //screen.moveGround(character.entityRect);
                        screen.moveScene(character.entityRect);
                        break;

                    case SDL_SCANCODE_W:
                        //cout << "jump" << character.entityRect.x << endl;
                        character.moveEntityJump(character.characterStandingRight, character.entityRect,
                                                 character.facingRight,
                                                 character.attackingRight);

                        break;

                    case SDL_SCANCODE_SPACE:
                        //cout << "Attacking" << endl;
                        character.shadowBlast("Img/Character.bmp", character.entityRect, character.facingRight,
                                              character.attackingRight);


                        break;

                    case SDL_SCANCODE_ESCAPE:
                        cout << "Pressed escape" << endl;
                        audio1.stopMusic();
                        screen.quitSDL();
                        tools.quit();
                        break;

                }

            }

        }
    }
    cout << "out of While loop";
}

//creates the screen, renderer, and loads the loading screen.
void Level::createScreen() {

    //Creates screen
    screen.createScreen();

    //Creates the renderer
    screen.createRenderer();
    screen.createRectangles();

    //renders the loading screen
    //and delays SDL to give time for the window to open
    //screen.loadAndRenderBmp("Img/Loading1.bmp");
    SDL_Delay(300);
    screen.backgroundRect.w = 1200;
    screen.changeBackground("Img/Loading1.bmp");
    SDL_RenderPresent(screen.renderer);
    SDL_Delay(1000);

    //Creates the thread and delays SDL to load the thread
    SDL_Delay(3000);

}

void Level::startMenu() {


}

void Level::level1() {


    character.setEntityPosition(0, 800);
    spider.setEntityPosition(500, 800);
    spider2.setEntityPosition(399, 800);
    screen.backgroundRect.w = 5000;
    while (tools.checkIfRunning()) { //Main loop for the game

        //Clears the Renderer
        SDL_RenderClear(screen.renderer);

        //loads background image and the ground
        screen.changeBackground("Img/SkyBlueBackground.bmp");
        screen.changeGroundWithBmp("Img/BrickGround.bmp");

        //load Health, and Mana bars
        screen.loadHealthAndManaBar(character.healthBar, character.manaBar);

        //checks to see what direction the character is facing and then loads the character image
        screen.loadAndRenderBmp(entity.checkIfCharacterIsFacingRight(character.facingRight, character.attackingRight),
                                character.entityRect);



        if (!spider.checkIfAlive()) {

            spider.killEntity(spider.entityRect);


        }else if (!spider2.checkIfAlive()) {

            spider2.killEntity(spider2.entityRect);

        }



        screen.loadAndRenderBmp("Img/CharacterStandingLeft.bmp", spider.entityRect);
        screen.loadAndRenderBmp("Img/CharacterStandingLeft.bmp", spider2.entityRect);


        //loads characters attack rectangle
        screen.loadAndRenderBmp("Img/Shadow.bmp", character.attackRect);


        //renders everything above
        SDL_RenderPresent(screen.renderer);


        if (entity.gotHit(character.attackRect, spider.entityRect)) {

            SDL_Delay(50);
            spider.setHealth(spider.getHealth() - character.getAttack());
            //cout << spider.getHealth() << endl;



            //character.attackRect.x = 0;
            //character.attackRect.y = 0;
        }else if (entity.gotHit(character.attackRect, spider2.entityRect)) {

            SDL_Delay(10);
            spider2.setHealth(spider2.getHealth() - character.getAttack());
            //cout << spider2.getHealth() << endl;



            //character.attackRect.x = 0;
            //character.attackRect.y = 0;
        }


    }

}



