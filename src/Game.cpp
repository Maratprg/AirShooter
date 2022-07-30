#include "Game.h"

////implamantation of world constant
sf::Vector2f world_S(1200.f,900.f);
sf::Vector2f landscapeWH(1200.f,2200.f); // landscape 0,0,1200,2200 boss_Chunk 0,0,1200,400

////implementation of constant class values
const float Game::playerSpeed = 200.f; // player moving Speed in game
const sf::Time Game::timePerFrame = sf::seconds(1.f/60.f);  //FPS value - 60Hz driving fraps

//implementation of constructor and destructor of the game class
Game::Game() : mWindow(sf::VideoMode(world_S.x, world_S.y), "AirShooter")
, player()
, isBoss(false)
, is_PlFlick(false)
, is_PlColor(false)
, is_PlSpin(false)
, lVelo (0.f,+0.025)
, airEnemyCControl(0) // bullets time variable
, bossEnemyCControll(0)  // bullets time variable

{
// ini of random function with the time
srand(time(nullptr));

// update of system joystick
sf::Joystick::update();

// check game pad supported data file and it recreation if it lost
if (!checkGamePad_Data_File())
{
    this->updateGamePad_Data_File_By_Default();
    std::cout << "Game Pad DATA FILE Updated!" << std::endl;
}

// read the values from game pad supported data file
this->readGamePad_Data_File();

// initialization of globall enum first view
globalScene = S_STAGES::STRT;

// variables for seeking game pad port
silenceCheckGamePad = false;
counterCheckGamePad = 0;

// initialization of blinking first and last view texts
gameText.setBlinkStart(iternal_clk.getElapsedTime().asMilliseconds()/100, 8);
gameText.setBlinkRedifine(iternal_clk.getElapsedTime().asMilliseconds()/100, 8);
gameText.setBlinkFinal(iternal_clk.getElapsedTime().asMilliseconds()/100, 8);

// initialization of first view texture
mFavoriteTV.setTexture(ReS.getTextureScene(specific_Texture::ID_scene::Start));

// initialization of top cloude and botom cloud sprites and its grathic shape matrix
cloud.cloudSp[0].setTexture(ReS.getTextureAir(specific_Texture::ID_air::Cloud));
cloud.cloudSp[1].setTexture(ReS.getTextureAir(specific_Texture::ID_air::Cloud));
cloud.cloudSp[2].setTexture(ReS.getTextureAir(specific_Texture::ID_air::Cloud));
cloud.autoSetIntRects();
cloud.autoSetSpCurr();
cloud.autoTranseCloude();
cloud.autoSetThreeClouds();

// island with botom and top atmosphere
specific_Texture::ID_air island_ID  = specific_Texture::ID_air::IslandTopF;
island.islandSp.setTexture(ReS.getTextureAir(island_ID));
island.setWH(ReS.getEnemySize(island_ID).x, ReS.getEnemySize(island_ID).y);
island.setPosXY(800.f,700.f); // к моменту вызвова позикса он должен все знать о размерах спрайта

// player initialization
player.sP.setTexture(ReS.getTextureAir(specific_Texture::ID_air::Eagle));
player.autoSetPositionStart();

// text string values initialization
gameText.autoSetPosition(world_S);

// initialization of boss scale vector
sclx[0].x = 1.f;
sclx[0].y = 1.f;

sclx[1].x = 0.6f;
sclx[1].y = 0.6f;

sclx[2].x = 0.8f;
sclx[2].y = 0.8f;


// initialization of music and array of short sounds
this->ReS.getMusic().setVolume(50.f);
this->ReS.getMusic().setLoop(true);
this->ReS.getMusic().play();

sound[0].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::bossBurn));
sound[1].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::bossDamage));
sound[2].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::enemyDamage));
sound[3].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::enemyKill));
sound[4].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::enemyShoot));
sound[5].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::playerDamage));
sound[6].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::playerGass));
sound[7].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::playerShoot));
sound[8].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::redifine));
sound[9].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::start));
sound[10].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::bossShoot));
sound[11].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::playerRotate));
sound[12].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::playerShadow));
sound[13].setBuffer(ReS.getSndBuff(specific_Soundbuff::ID::bossBorn));

for (int s=0; s<14; s++)
{
 serviceSound[s] = false;
 sound[s].setVolume(40);
}

}//end of ctor

Game::~Game(){}

//implementation of the run function --- it is a general stick of the game (GENERAL GAME LOOP).
//speceffects such as flicing, rotation and change color, and also event for generating new stage in this place.
void Game::run()
{
    clock.restart();
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // mechanics speceffects flags
    float careANGL = 0; // ungl of rotation
    int colorMark; // mark time of color changing

    while (mWindow.isOpen())
    {
       //global mechanic time clock  very important!
       int32_t t = iternal_clk.getElapsedTime().asMilliseconds()/100;

          processEvents();

          if (globalScene == S_STAGES::STG_ONE || globalScene == S_STAGES::STG_TWO || globalScene == S_STAGES::STG_THREE)
          {
             processEnenmyBullets(t);
          };//end of if


        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
          timeSinceLastUpdate -= timePerFrame;

          processEvents();

            if (globalScene == S_STAGES::STG_ONE || globalScene == S_STAGES::STG_TWO || globalScene == S_STAGES::STG_THREE)
            {
                processEnenmyBullets(t);
                update(timePerFrame);
                brainwishCollide();
            };
        }
        playSounds();
        drawAll();

            //*****SPEC EFFECTS******
            // mechanics of fliking player
            if (player.countFLK > 0)
                    {
                        if (player.repeatCControl != t)
                            {
                                player.repeatCControl = t;
                                if(t% (player.moduleFLK)) player.swapVisible();
                                player.countFLK = player.countFLK - 1;
                            }
                    }
            else {  player.setVisible(true);  player.setTrigerable(true); };

            // mechanics of rotating player
            if (player.countROT >0)
                    {
                        if (careANGL >= 360.f )
                            {
                                careANGL = 0;
                                player.countROT = player.countROT - 1;
                            }
                        else
                            {
                                careANGL = careANGL + player.uRotANGL;
                                player.sP.rotate(player.uRotANGL);
                            };
                    };

            // mechanics of player color changing
            if ((player.markTi + player.colorTiRg) > t)
                    {
                        player.sP.setColor(player.col);
                    }
            else { player.sP.setColor(sf::Color::White); };

            // mechanics of boss color changing
            if (boss.isAlive)
            {
               //boss born sound
               if (!boss.soundBorn) { serviceSound[13] = true; boss.soundBorn = true; }

                if (boss.toChColor > t)
                {
                    boss.bSp.setColor(sf::Color(255,66,51,120));
                }
                else { boss.bSp.setColor(sf::Color::White); };

            }//end of if

            // mechanics of flicking text in first and the last views
            if (!silenceCheckGamePad)
            {
              if (t > gameText.timeStart)
              {
                gameText.timeStart = t + gameText.periodStart;
                if (gameText.visible_BStart)
                    {
                     gameText.visible_BStart = false;
                     gameText.visible_BRedifine = false;
                     gameText.visible_BFinal = false;
                    }
                else {
                      gameText.visible_BStart = true;
                      gameText.visible_BRedifine = true;
                      gameText.visible_BFinal = true;
                     };//end of if else
              }//end of if
            }//end of if

           // mechanics of flicking text that show stage and the winner state in game
           if (gameText.swch_VCheck)
           {
                if (gameText.timeCControllerStage < t)
                    {
                    gameText.visible_Stage = false;
                    gameText.swch_VCheck = false;
                    };
           };//end of if

           // mechanics of the boss burning when the shapes vector goes around of him
           if (boss.bossIsBurn)
           {
            gameText.setShowWin(2);
            if (boss.burnCController != t)
            {
               boss.burnCController = t;
               if(t%10 == 0)
               {
                  if(boss.burnCounter > 0)
                  {
                  boss.burnAutoSetPositionBoss();
                  boss.burnCounter = boss.burnCounter - 1;
                  serviceSound[0] = true;
                  }
                  else if(boss.burnCounter == 0)
                  {

                        this->isBoss = false;
                        boss.isAlive = false;
                        boss.soundBorn = false;

                        if (globalScene == S_STAGES::STG_ONE)
                        {
                        this->setGameStageEntities(2); // goes to make new stage in this place
                        globalScene = S_STAGES::STG_TWO;
                        }
                        else if (globalScene == S_STAGES::STG_TWO)
                        {
                        this->setGameStageEntities(3); // goes to make new stage in this place
                        globalScene = S_STAGES::STG_THREE;
                        }
                        else if (globalScene == S_STAGES::STG_THREE)
                        {
                         boss.isAlive = false;
                         boss.bossIsBurn = false;
                         this->isBoss = false;
                         globalScene = S_STAGES::STRT;
                         mFavoriteTV.setTexture(ReS.getTextureScene(specific_Texture::ID_scene::Start));
                         this->ReS.getMusic().play();
                         player.isDOWN, player.isLEFT, player.isRIGHT, player.isUP = false;
                        }
                        else{};
                  }
                  else{}; //end of if else
               }//end of if
            }//end of if

          }//end of if

    }//end of while
}//end run


//implementation of the event (input) controlling function of the game class (INPUT CONTROLS)
void Game::processEvents()
{
    sf:: Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::JoystickMoved:
                handlePlayerInput(event);
                break;
             case sf::Event::JoystickButtonPressed:
                 handlePlayerInput(event);
                 break;
             case sf::Event::JoystickButtonReleased:
                 handlePlayerInput(event);
                 break;
            case sf::Event::MouseButtonReleased:
                handleMouseButton();
                break;
             case sf::Event::KeyPressed:
                 handlePlayerInput (event);
                 break;
             case sf::Event::KeyReleased:
                 handlePlayerInput (event);
                 break;
            case sf::Event::Closed:
                mWindow.close();
                break;
        }//end of switch
    }//end of while
}//end of void

//implementation how the bullets must born in game entities
void Game::processEnenmyBullets(int32_t t)
{

  if (t%35 == 0)
  {

    if (airEnemyCControl != t)
    {
         airEnemyCControl = t; // this variable need to keep the new time to born the bullets in scene node

         if (nodeEY.sceneVec.size() > 0)
         {
             for (int i=0; i<nodeEY.sceneVec.size(); i++)
             {
                float isViewX = nodeEY.sceneVec[i].sP.getPosition().x + nodeEY.sceneVec[i].getW();
                float isViewY = nodeEY.sceneVec[i].sP.getPosition().y + nodeEY.sceneVec[i].getH();
                if (isViewX > 0 && isViewX < world_S.x && isViewY > 0 && isViewY < world_S.y)
                {
                   nodeEY.sceneVec[i].startBullet();
                   serviceSound[4] = true;
                }//end of if
             }//end of for
         }//end of if
    };//end of second if
  };//end of first if

  if(boss.isAlive && !boss.bossIsBurn)
  {
      if (t%15 == 0)
      {
          if (bossEnemyCControll != t)
          {
              bossEnemyCControll = t;
              if (boss.replCounter < 4)
              {
               boss.startBullet(boss.stageCounter, world_S);
               serviceSound[10] = true;
               boss.replCounter++;
              }//end of if
              else
              {
               boss.autoSetPosition(world_S);
               boss.replCounter = 0;
               boss.toChColor = t + 8;
              }//end of if
          }//end of if
      } //end of if
  }//end of if

}//end of void

//implementation of the update function of the game class (LOGIC BLOCK OF THE GAME)
void Game::update(sf::Time elapsedTime)
{
    if (globalScene == S_STAGES::STRT)
    {

    }//end of if
    else if (globalScene == S_STAGES::STG_ONE || globalScene == S_STAGES::STG_TWO || globalScene == S_STAGES::STG_THREE)
    {
        // moving player
        sf::Vector2f movement (0.f, 0.f);

        if (player.isUP) {movement.y -= playerSpeed; };
        if (player.isDOWN) {movement.y += playerSpeed; };
        if (player.isLEFT) {movement.x -= playerSpeed; };
        if (player.isRIGHT) {movement.x += playerSpeed; };

        player.sP.move(movement * elapsedTime.asSeconds());
        player.autoSetBlameBehind();

        // moving bullets
        if (player.bulletVec.size() > 0)
            {
                for (int i = 0; i < player.bulletVec.size(); i++)
                {
                  player.bulletVec.at(i).move(0.f, player.getBV());
                }
            }

        // moving the scene node vector array
        if (nodeEY.sceneVec.size() > 0)
            {
                for (int i=0; i<nodeEY.sceneVec.size(); i++)
                {
                    float toX = nodeEY.sceneVec.at(i).getVelocity().x;
                    float toY = nodeEY.sceneVec.at(i).getVelocity().y;
                    nodeEY.sceneVec.at(i).sP.move(sf::Vector2f(toX,toY));
                }
            }

        // moving the test entity bullets
        float goX = 0.f; // goes directly down
        float goXL = -2.5; // goes with left deviation
        float goXR = +2.5; // goes with right deviation
        float where = goX; // variable witch keep the bullet direction value

        if (testAirEnemy.bulletVec.size() > 0)
            {
                for (int i = 0; i < testAirEnemy.bulletVec.size(); i++)
                {
                    testAirEnemy.bulletVec.at(i).move(where, testAirEnemy.getBV());

                    if (where == goX) { where = goXL; }
                    else if(where == goXL) {where = goXR;}
                    else if(where == goXR) {where = goX;}
                    else{};
                }
            }

        // moving the scene node bullets which are linked on such (goX goXL goXR, where) variables
        if (nodeEY.sceneVec.size() > 0)
        {
            for (int i=0; i<nodeEY.sceneVec.size(); i++)
            {
                if (nodeEY.sceneVec[i].bulletVec.size()>0)
                {
                    for (int b=0; b<nodeEY.sceneVec[i].bulletVec.size(); b++)
                    {
                        nodeEY.sceneVec[i].bulletVec.at(b).move(where, nodeEY.sceneVec[i].getBV());

                        if (where == goX) { where = goXL; }
                        else if(where == goXL) {where = goXR;}
                        else if(where == goXR) {where = goX;}
                        else{};
                    }// end of for
                }//end of if
            }//end of for
        }//end of if

        // moving the boss bullets
        if (boss.isAlive)
        {
            if(boss.bulletVec.size() > 0)
            {
                int uV = 0; // variable for iterration of the bullets direction loop
                for (int b=0; b<boss.bulletVec.size(); b++)
                {
                    if (uV == 0)
                    {
                        boss.bulletVec[b].move(boss.threeUvec[0]);
                        uV = 1;
                    }
                    else if (uV == 1)
                    {
                        boss.bulletVec[b].move(boss.threeUvec[1]);
                        uV = 2;
                    }
                    else
                    {
                        boss.bulletVec[b].move(boss.threeUvec[2]);
                        uV = 0;
                    }//end of if
                }//end of for
            }//end of if

            if (boss.burnVec.size()>0)
            {
                for(int bu=0; bu<boss.burnVec.size(); bu++)
                {
                    boss.burnVec[bu].move( boss.burnUVec[bu].x * 20.f, boss.burnUVec[bu].y * 20.f);
                }//end of for
            }//end of if

        }//end of if

        // updating of boss lifes
        if (boss.isAlive && !boss.bossIsBurn)
            {
                if (boss.getHealth() < 0)
                {
                 boss.bossIsBurn = true;
                 boss.burnCounter = 8;
                }

            }//end of if

         // updating of player lifes
        if (player.getHealth() < 0)
            {
                    globalScene = S_STAGES::GAME_OVER;
                    this->isBoss = false;
                    boss.isAlive = false;
                    boss.soundBorn = false;

                    player.setHealth(4);

                    player.isDOWN, player.isLEFT, player.isRIGHT, player.isUP = false;

                    mFavoriteTV.setTexture(ReS.getTextureScene(specific_Texture::ID_scene::Stop));
                    this->ReS.getMusic().play();

                    std::string f_scr = std::to_string(player.getScore()); //????
                    gameText.f_Score.setString(f_scr);
                    player.setScore(0);


                if (nodeEY.sceneVec.size() > 0)
                {
                    for (int sV=0; sV<nodeEY.sceneVec.size(); sV++)
                    {
                    auto iter = nodeEY.sceneVec.begin() + sV;
                    nodeEY.dettachEnemy(iter);
                    }//end of for
                }//end of if
          }//end of if

        // moving the cloude with it matrix (passing isBoss value)
        cloud.updateMovex(world_S, isBoss);
        // moving the island with it matrix (passing isBoss value)
        island.updateMovex(world_S, isBoss);
    }//end of if

    else if (globalScene == S_STAGES::GAME_OVER)
    {

    }// end of if

    else {};

}//end of void

// scrolling landscape funcion which upadate and draw landscape
void Game::upDateAndDrawLandscape(bool mBoss)
    {
       if (!mBoss) // если босс дезактивирован
            {
                //std::cout << " Values yI|yII ::: " <<static_cast<int>(mLandscapeFirst.getPosition().y)
                //<< " | " << static_cast <int>(mLandscapeSecond.getPosition().y) << endl;

                //mLandscapeFirst.move(lVelo);

                // блок обработки джампов српайта
                if (static_cast<int>(mLandscapeFirst.getPosition().y) == -850)
                    {
                        mLandscapeSecond.setPosition(sf::Vector2f(0.f, - 2200.f - 400.f));
                    }
                else if (static_cast<int>(mLandscapeSecond.getPosition().y) == -850)
                    {
                        mLandscapeFirst.setPosition(sf::Vector2f(0.f, - 2200.f - 400.f));
                    }
                else;

               // блок обработки остановки прокрутки внутри которых блоки проверки первого
               if (static_cast<int>(mLandscapeFirst.getPosition().y) == 450)
                    {
                            // принцип покажи противоположного
                            mLandscapeSecond.move(lVelo);
                                mWindow.draw(mLandscapeSecond);

                    }
               else if (static_cast<int>(mLandscapeSecond.getPosition().y) == 450)
                    {
                            // принцип покажи противоположного
                            mLandscapeFirst.move(lVelo);
                                mWindow.draw(mLandscapeFirst);
                    }

               else {
                       if (mLandscapeFirst.getPosition().y < mLandscapeSecond.getPosition().y)
                            {
                                // потайна€ функци€ скрыти€ боса в спрайте
                                mLandscapeSecond.move(lVelo);
                                mLandscapeFirst.move(lVelo);
                                    // если кто то из этих реб€т отрицательнее его надо рисовать вторым
                                    mWindow.draw(mLandscapeSecond);
                                    mWindow.draw(mLandscapeFirst);
                            }
                       else
                            {
                                // потайна€ функци€ скрыти€ боса в спрайте
                                mLandscapeSecond.move(lVelo);
                                mLandscapeFirst.move(lVelo);
                                    mWindow.draw(mLandscapeFirst);
                                    mWindow.draw(mLandscapeSecond);
                            }
                    };

            }
       else     // тут если босс активирован!!!! происходит раскрытие босса
            {
               // std::cout << " Values yI|yII ::: " <<static_cast<int>(mLandscapeFirst.getPosition().y)
               // << " | " << static_cast <int>(mLandscapeSecond.getPosition().y) << endl;

                // управл€ющий алгоритм узнает ведущего и доводит ведомого и ступорит его
                if (mLandscapeFirst.getPosition().y < mLandscapeSecond.getPosition().y)

                            {
                                // хорошо ведущий ѕервый. ƒвигатс€ ѕервый отрисовыветс€ первый до боса
                                if (static_cast<int>(mLandscapeSecond.getPosition().y) == 450)
                                        {
                                          if (static_cast<int>(mLandscapeFirst.getPosition().y) != 0)
                                                {
                                                    mLandscapeFirst.move(lVelo);
                                                    mWindow.draw(mLandscapeFirst);
                                                }
                                          else { mWindow.draw(mLandscapeFirst);  this->boss.isAlive = true; }; //добавил рож бос
                                        }
                                else   // здесь доведение второго и в дальнейшем запуск второго (отрис ¬торой ѕервый)
                                        {
                                          mLandscapeFirst.move(lVelo);
                                          mLandscapeSecond.move(lVelo);
                                              mWindow.draw(mLandscapeSecond);
                                              mWindow.draw(mLandscapeFirst);
                                        };

                                    // если кто то из этих реб€т отрицательнее его надо рисовать вторым
                            }
                else // в данном случае наоборот ведущий второй
                            {
                                // хорошо ведущий второй. ƒвигатс€ ¬торой отрисовыветс€ ¬торой до боса
                                if (static_cast<int>(mLandscapeFirst.getPosition().y) == 450)
                                        {
                                          if(static_cast<int>(mLandscapeSecond.getPosition().y) != 0)
                                                {
                                                    mLandscapeSecond.move(lVelo);
                                                    mWindow.draw(mLandscapeSecond);
                                                }
                                          else  {mWindow.draw(mLandscapeSecond); this->boss.isAlive = true; }; //добавил рож бос

                                        }
                                else   // здесь доведение первого и запуск второго. ƒвигаютс€ оба отрис ѕервый ¬торой
                                        {
                                          mLandscapeFirst.move(lVelo);
                                          mLandscapeSecond.move(lVelo);
                                               mWindow.draw(mLandscapeFirst);
                                               mWindow.draw(mLandscapeSecond);
                                        };

                           }; // конец ифа второго управл€ющего алгоритма

            }; // конец корневого ифа
    }

//implementation of the render function of the game class (DRAW OBJECTS)
//*************************
//******* DRAW ALL *******
//***********************
void Game::drawAll()
{
    mWindow.clear();

    // first view
    if (globalScene == S_STAGES::STRT)
    {
        mWindow.draw(mFavoriteTV);
        if (gameText.visible_BStart) mWindow.draw(gameText.b_Start);
        if (gameText.visible_BRedifine) mWindow.draw(gameText.b_Redifine);
    }

    // stages views
    else if (globalScene == S_STAGES::STG_ONE || globalScene == S_STAGES::STG_TWO || globalScene == S_STAGES::STG_THREE)
    {

        // the first step is
        this->upDateAndDrawLandscape(isBoss);

        // bottom clouds
        if(cloud.getVisible()) {
            for (int i=0; i<3; i++) if(cloud.threeClouds[i] < 33 ) mWindow.draw(cloud.cloudSp[i]);
            for (int i=0; i<3; i++) if(cloud.threeClouds[i] > 66 ) mWindow.draw(cloud.cloudSp[i]);
            }

        // flying island with island bottom matrix
        if(island.getVisible()) mWindow.draw(island.islandSp);
        if(island.getVisible()) {  for(int i=0; i<organicNebula; i++) mWindow.draw(island.organicIB[i]);  }

        // render the boss if its alive
        if (boss.isAlive) mWindow.draw(boss.bSp);

        if (boss.bulletVec.size() > 0) for (int b=0; b<boss.bulletVec.size(); b++) {  mWindow.draw(boss.bulletVec[b]);  };

        if (boss.burnVec.size() > 0) for (int bu=0; bu<boss.burnVec.size(); bu++) {  mWindow.draw(boss.burnVec[bu]);  };

        // airenemys render place
        mWindow.draw(testAirEnemy.sP);

        // render scene node and its bullets
        if (nodeEY.sceneVec.size()>0)
            {
                for (int i=0; i<nodeEY.sceneVec.size(); i++)
                {
                    mWindow.draw(nodeEY.sceneVec.at(i).sP);
                    if (nodeEY.sceneVec.at(i).bulletVec.size()>0)
                    {
                        for (int b=0; b<nodeEY.sceneVec.at(i).bulletVec.size(); b++)
                        {
                        mWindow.draw(nodeEY.sceneVec.at(i).bulletVec[b]);
                        }//end of for
                    }//end of if
                }//end of for
            }//end of if

        // render player
        if (player.getVisible()) mWindow.draw(player.sP);

        // the blame out of player ship
        if (player.getVisible())
            {
                if (player.blameVisibleUP || player.blameVisibleDOWN || player.blameVisibleLEFT || player.blameVisibleRIGHT)
                {
                    for (int blm=0;blm<15;blm++) {  mWindow.draw(player.blameBehind[blm]);  };
                }; //end of if
            };//end of if

        //draw a player bullets
        for (int i = 0; i<player.bulletVec.size(); i++) {  mWindow.draw(player.bulletVec.at(i)); };

        //draw a player enemy bullets
        for (int i = 0; i<testAirEnemy.bulletVec.size(); i++) {  mWindow.draw(testAirEnemy.bulletVec.at(i)); };

        // island top matrix
        if(island.getVisible()) {  for(int i=0; i<organicNebula; i++) mWindow.draw(island.organicIT[i]);  }

        // the clouds top sprite and top matrix
        if(cloud.getVisible()) {
            for (int i= 0; i<organicCloudsNumbers; i++) {  mWindow.draw(cloud.cloudOrganic[i]); }
            for (int i=0; i<3; i++) if(cloud.threeClouds[i] > 33 && cloud.threeClouds[i] < 66) mWindow.draw(cloud.cloudSp[i]);
            }

        // game text rendering
        if(gameText.visible_Stage)  mWindow.draw(gameText.stage);

        std::string health = "HEALTH: " + std::to_string(player.getHealth());
        std::string score = "SCORE: " + std::to_string(player.getScore());
        std::string boss_hth = "BOSS_H: " + std::to_string(boss.getHealth());
        gameText.health.setString(health);
        gameText.score.setString(score);
        gameText.boss_health.setString(boss_hth);

        mWindow.draw(gameText.health);
        mWindow.draw(gameText.score);
        mWindow.draw(gameText.boss_health);
    }//end of if
    else if (globalScene == S_STAGES::GAME_OVER)
    {
      mWindow.draw(mFavoriteTV);
      if (gameText.visible_BStart) mWindow.draw(gameText.f_Score);

    }//end of if
    else {};


    mWindow.display();
}

//implementation of the function in the class witch keep the event from processEvents void
void Game::handlePlayerInput(sf::Event event)
{
   if (globalScene == S_STAGES::STRT)
   {
       if (counterCheckGamePad == 9) { silenceCheckGamePad = false; this->updateGamePad_Data_File(); }

       if (event.type == sf::Event::KeyPressed)
        {
          if (event.key.code == sf::Keyboard::Enter && !silenceCheckGamePad)
          {
            // goes girst stage
            this->setGameStageEntities(1);
            globalScene = S_STAGES::STG_ONE;
            serviceSound[9] = true;
          }
          else if (event.key.code == sf::Keyboard::Space && !silenceCheckGamePad)
          {
            // goes redifine gamepad buttons
            silenceCheckGamePad = true;
            counterCheckGamePad = 0;
            gameText.visible_BRedifine = true;
            gameText.visible_BStart = true;
            serviceSound[8] = true;
            updateStructOfGamePad(event);
          }
          else {};
        }//end of if

      // reeding and check start button
      if (event.type == sf::Event::JoystickButtonPressed &&
           event.joystickButton.joystickId == gamePad_Data.port && !silenceCheckGamePad)
      {
          if (event.joystickButton.button == gamePad_Data.start)
          {
            this->setGameStageEntities(1);
            globalScene = S_STAGES::STG_ONE;
            serviceSound[9] = true;
          }//end of if
      }//end of if

      // reeding the axis and buttons in silence mode when the port are seeking.
      if (silenceCheckGamePad)
      {
        if (event.type == sf::Event::JoystickMoved)
        {
          if(counterCheckGamePad == 2 || counterCheckGamePad == 3)
          {
           updateStructOfGamePad(event);
          };
        }//end of if

        if (event.type == sf::Event::JoystickButtonPressed)
        {
           if(counterCheckGamePad != 2 || counterCheckGamePad != 3)
           {
            updateStructOfGamePad(event);
           };
        }// end of if
      }//end of if
   }//end of long if whith else
   else if (globalScene == S_STAGES::STG_ONE || globalScene == S_STAGES::STG_TWO || globalScene == S_STAGES::STG_THREE)
   {
    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
    {
        bool value;
        if (event.type == sf::Event::KeyPressed) { value = true; }
        else if (event.type == sf::Event::KeyReleased) { value = false; }
        else{};

        if (event.key.code == sf::Keyboard::Up) {player.isUP = value; player.blameVisibleUP = value; }
        else if(event.key.code == sf::Keyboard::Down) {player.isDOWN = value; player.blameVisibleDOWN = value; }
        else if(event.key.code == sf::Keyboard::Left) {player.isLEFT = value; player.blameVisibleLEFT = value; }
        else if (event.key.code == sf::Keyboard::Right) {player.isRIGHT = value; player.blameVisibleRIGHT = value; }
        else {};

        if (event.key.code == sf::Keyboard::Space) { };
        if (event.key.code == sf::Keyboard::F) { this->flickPl(40, 2); };
        if (event.key.code == sf::Keyboard::R) { if (value) { this->spinPl(4, 0.5); if (value) serviceSound[11] = true; }; };
        if (event.key.code == sf::Keyboard::C) { if (value) { this->changePlCol(sf::Color(255,170,229,100), 100); serviceSound[12] = true; }; };
        if (event.key.code == sf::Keyboard::B) { if (player.getTrigerable() == true) { this->player.startBullet();  serviceSound[7] = true; }; };
        if (event.key.code == sf::Keyboard::W) { boss.burnAutoSetPositionBoss(); };
    }
    else
    {
      if (event.type == sf::Event::JoystickMoved)
      {
        if (event.joystickMove.joystickId == gamePad_Data.port)
        {
        //entering values from axis
        float X = sf::Joystick::getAxisPosition(gamePad_Data.port, sf::Joystick::X);
        float Y = sf::Joystick::getAxisPosition(gamePad_Data.port, sf::Joystick::Y);

        //we check each axis separately
        if (Y < -10.f) {player.isUP = true; player.blameVisibleUP = true; }
        else if (10.f < Y) {player.isDOWN = true; player.blameVisibleDOWN = true; }
        else if (-10 < Y < 10.f){
             player.isUP = false;
             player.isDOWN = false;
             player.blameVisibleUP = false;
             player.blameVisibleDOWN = false; }
        else {};

        if (X < -10.f) {player.isLEFT = true; player.blameVisibleLEFT = true; }
        else if (10.f < X) {player.isRIGHT = true; player.blameVisibleRIGHT = true; }
        else if (-10.f < X < 10.f) {
                player.isLEFT = false;
                player.isRIGHT = false;
                player.blameVisibleLEFT = false;
                player.blameVisibleRIGHT = false; }
        else {};
        }//end of if
      }//end of if

      if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::JoystickButtonReleased)
      {
        bool value;
        if (event.type == sf::Event::JoystickButtonPressed) { value = true; }
        else if (event.type == sf::Event::JoystickButtonReleased) { value = false; }
        else {};

        if (event.joystickButton.joystickId == gamePad_Data.port)
          {
            if (event.joystickButton.button == gamePad_Data.fire)  { if (player.getTrigerable() == true) { this->player.startBullet(); serviceSound[7] = true; }; }
            if (event.joystickButton.button == gamePad_Data.rotation) { if(value) { this->spinPl(4, 0.5); serviceSound[11] =  true; }; }
            if (event.joystickButton.button == gamePad_Data.chColor) { if(value) { this->changePlCol(sf::Color(255,170,229,100), 100); serviceSound[12] = true;} }
          }//end of if
      }// end of if
    }//end of else

        //make event of blame visible sound
        if (player.blameVisibleUP == true || player.blameVisibleDOWN == true ||
            player.blameVisibleLEFT == true || player.blameVisibleRIGHT == true || event.type == sf::Event::KeyPressed) {  serviceSound[6] = true; }

   }//end of global stage else if
   else if (globalScene == S_STAGES::GAME_OVER)
   {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter && !silenceCheckGamePad)
            {
                 // start first stage
                 this->setGameStageEntities(1);
                 globalScene = S_STAGES::STG_ONE;
                 serviceSound[9] = true;
            };// end of if
        };//end of if


        // start first stage by gamepad
        if (event.type == sf::Event::JoystickButtonPressed &&
              event.joystickButton.joystickId == gamePad_Data.port && !silenceCheckGamePad)
        {
            if (event.joystickButton.button == gamePad_Data.start)
            {
                 this->setGameStageEntities(1);
                 globalScene = S_STAGES::STG_ONE;
                 serviceSound[9] = true;
            };//end of if
        };//end of if
   }
   else {};//end of else

}//end of void

//output in std::cout the mouse button coordinates
void Game::handleMouseButton()
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(mWindow);
    std::cout << " MOUSE:::: X " << localPosition.x << " Y " << localPosition.y << std::endl;
}

void Game::resetPlayerMoveBools()
{
   player.isUP = false;
   player.isDOWN = false;
   player.isLEFT = false;
   player.isRIGHT = false;

   player.blameVisibleUP = false;
   player.blameVisibleDOWN = false;
   player.blameVisibleLEFT = false;
   player.blameVisibleRIGHT = false;
}

bool Game::checkGamePad_Data_File()
{
    std::ifstream in_f("gamePad.data");
    if(in_f.is_open()) { in_f.close(); return true; }
    else
    {
    in_f.close();
    return false;
    };
}

void Game::readGamePad_Data_File()
{
    std::ifstream in_f("gamePad.data");
    if(in_f.is_open())
    {
        in_f >> gamePad_Data.port >> gamePad_Data.start >> gamePad_Data.fire >> gamePad_Data.rotation >>
         gamePad_Data.chColor >> gamePad_Data.maxX >> gamePad_Data.maxY >> gamePad_Data.rngX >> gamePad_Data.rngY;
     in_f.close();
    }
    else
    {
      in_f.close();
      std::cout << "SORRY but i cant find the gamePad.data file!" << std::endl;
    }
}

void Game::updateGamePad_Data_File()
{
    if(checkGamePad_Data_File())
        {
        std::ofstream out_f("gamePad.data");
        if (out_f.is_open())
            {
            out_f << gamePad_Data.port << std::endl;
            out_f << gamePad_Data.start << std::endl;
            out_f << gamePad_Data.fire << std::endl;
            out_f << gamePad_Data.rotation << std::endl;
            out_f << gamePad_Data.chColor << std::endl;
            out_f << gamePad_Data.maxX << std::endl;
            out_f << gamePad_Data.maxY << std::endl;
            out_f << gamePad_Data.rngX << std::endl;
            out_f << gamePad_Data.rngY << std::endl;
            }//end of if
        out_f.close();
        }//end of if
}//end of void

void Game::updateGamePad_Data_File_By_Default()
{
        // making game pad struct values by default
        gamePad_Data.port = 0;
        gamePad_Data.start = 8;
        gamePad_Data.fire = 1;
        gamePad_Data.rotation = 2;
        gamePad_Data.chColor = 3;
        gamePad_Data.maxX = 100.f;
        gamePad_Data.maxY = 100.f;
        gamePad_Data.rngX = 15.f;
        gamePad_Data.rngY = 15.f;

        // making file if it dose not exist
        std::ofstream out_f("gamePad.data");
        if (out_f.is_open())
        {
        out_f << gamePad_Data.port << std::endl;
        out_f << gamePad_Data.start << std::endl;
        out_f << gamePad_Data.fire << std::endl;
        out_f << gamePad_Data.rotation << std::endl;
        out_f << gamePad_Data.chColor << std::endl;
        out_f << gamePad_Data.maxX << std::endl;
        out_f << gamePad_Data.maxY << std::endl;
        out_f << gamePad_Data.rngX << std::endl;
        out_f << gamePad_Data.rngY << std::endl;
        }//end of if
        out_f.close();
}//end of void

void Game::updateStructOfGamePad(sf::Event event)
{
  if (counterCheckGamePad == 0)
  {
    // goes seeking usb port
    gameText.b_Start.setCharacterSize(50);
    gameText.b_Start.setString("seek port...");
    gameText.b_Redifine.setString("press Joy Button");
    counterCheckGamePad = 1;
  }
  else if (counterCheckGamePad == 1)
  {

    // write the port in struct and check x axis (from marked port)
    if (event.joystickButton.joystickId != 57){
    gamePad_Data.port = event.joystickButton.joystickId;
    std::string s_port = "seek port " + std::to_string(gamePad_Data.port) + "...";
    gameText.b_Start.setString(s_port);
    gameText.b_Redifine.setString("press Y Axis");
    counterCheckGamePad = 2;

    }
  }
  else if (counterCheckGamePad == 2)
  {
    // make sure that value of x from marked port and check y axis
    std::string s_port = "seek port " + std::to_string(gamePad_Data.port) + "...";
    gameText.b_Start.setString(s_port);

    if (event.joystickButton.joystickId == gamePad_Data.port && event.joystickMove.axis == sf::Joystick::Y)
    {
      gameText.b_Redifine.setString("press X Axis");
      counterCheckGamePad = 3;
    }
  }
  else if (counterCheckGamePad == 3)
  {
    if (event.joystickButton.joystickId == gamePad_Data.port && event.joystickMove.axis == sf::Joystick::X)
    {
    // make sure that value of y from marked port and check start button
    std::string s_port = "seek port " + std::to_string(gamePad_Data.port) + "...";
    gameText.b_Start.setString(s_port);
    gameText.b_Redifine.setString("press Start Button");
    counterCheckGamePad = 4;
    }
  }
  else if (counterCheckGamePad == 4)
  {
    // write start button in struct and check fire button (from marked port)
    if (event.joystickButton.joystickId == gamePad_Data.port)
        {
          gamePad_Data.start = event.joystickButton.button;

          std::string s_port = "seek port " + std::to_string(gamePad_Data.port) + "...";
          gameText.b_Start.setString(s_port);
          gameText.b_Redifine.setString("press Fire Button");

          counterCheckGamePad = 5;
        }
  }
  else if (counterCheckGamePad == 5)
  {
    // write fire button in struct and check rotation button (from marked port)
    if (event.joystickButton.joystickId == gamePad_Data.port)
        {
          gamePad_Data.fire = event.joystickButton.button;

          std::string s_port = "seek port " + std::to_string(gamePad_Data.port) + "...";
          gameText.b_Start.setString(s_port);
          gameText.b_Redifine.setString("press R-tion Button");

          counterCheckGamePad = 6;
        }
  }
  else if (counterCheckGamePad == 6)
  {
    // write rotation button in struct and check shadow button (from marked port)
    if (event.joystickButton.joystickId == gamePad_Data.port)
        {
          gamePad_Data.rotation = event.joystickButton.button;

          std::string s_port = "seek port " + std::to_string(gamePad_Data.port) + "...";
          gameText.b_Start.setString(s_port);
          gameText.b_Redifine.setString("press Shadow Button");

          counterCheckGamePad = 7;
        }
  }
  else if (counterCheckGamePad == 7)
  {
    // write shadow button in struct and check the button button (from marked port) to update data file
    if (event.joystickButton.joystickId == gamePad_Data.port)
        {
          gamePad_Data.chColor = event.joystickButton.button;

          std::string s_port = "seek port " + std::to_string(gamePad_Data.port) + "...";
          gameText.b_Start.setString(s_port);
          gameText.b_Redifine.setString("succsess press Any");

          counterCheckGamePad = 8;
        }
  }
  else if (counterCheckGamePad == 8)
  {
    // return blinking strings back to its place
    if (event.joystickButton.joystickId == gamePad_Data.port)
        {
          gameText.b_Start.setCharacterSize(55);
          gameText.b_Start.setString("START ENTER");
          gameText.b_Redifine.setString("SPACE -> GamePad");

          counterCheckGamePad = 9;
        }
  }

  else{};

}//end of void

void Game::resetAllTrigers()
{
 is_PlFlick = false;
 is_PlColor = false;
 is_PlSpin = false;
}

void Game::flickPl(int countFLICK, int moduleFLICK)
{
  player.countFLK = countFLICK;
  player.moduleFLK = moduleFLICK;
  player.setTrigerable(false);
}

void Game::spinPl(int countROTAT, float uRotANGLUS)
{
  player.countROT = countROTAT;
  player.uRotANGL = uRotANGLUS;
}

void Game::changePlCol(sf::Color c, int rangeI)
{
player.col = c;
player.colorTiRg = rangeI;
player.markTi = iternal_clk.getElapsedTime().asMilliseconds()/100;
}

//***********************************
//*******BRAIN_WISH_COLLIDE*********
//*********************************

void Game::brainwishCollide()
{
    // player bullet with wall and airenemy
    if (player.bulletVec.size() > 0)
    {
      for (int i=0; i < player.bulletVec.size(); i++)
      {
        if (nodeEY.sceneVec.size() > 0)
           {
              for(int enm=0; enm<nodeEY.sceneVec.size(); enm++)
              {
                float findX = abs( (player.bulletVec.at(i).getPosition().x + 2.5) - (nodeEY.sceneVec[enm].sP.getPosition().x + nodeEY.sceneVec[enm].getW()/2) );
                float findY = abs( (player.bulletVec.at(i).getPosition().y + 2.5) - (nodeEY.sceneVec[enm].sP.getPosition().y + nodeEY.sceneVec[enm].getH()/2) );
                float Hayze = sqrt(pow(findX, 2) + pow(findY, 2));

                if (Hayze < 50.f)
                        {
                         // pass the bullet to unvisible x place
                         player.bulletVec.at(i).setPosition(sf::Vector2f(-50.f, player.bulletVec.at(i).getPosition().y)); // уичтожение пули игрока
                         serviceSound[2] = true;

                         nodeEY.sceneVec[enm].setHealth(nodeEY.sceneVec[enm].getHealth() - 1);

                         if (nodeEY.sceneVec[enm].getHealth() < 0)
                                {
                                player.setScore(player.getScore()+1);
                                auto iter = nodeEY.sceneVec.begin() + enm;
                                nodeEY.dettachEnemy(iter);
                                serviceSound[3] = true;
                                } //end of if
                        }//end of if
              }//end of for
            }//end of if

        //player bullet with alive boss
        if (boss.isAlive)
            {
              float findX = abs( (player.bulletVec.at(i).getPosition().x + 2.5) - (boss.bSp.getPosition().x + boss.getW()/2) );
              float findY = abs( (player.bulletVec.at(i).getPosition().y + 2.5) - (boss.bSp.getPosition().y + boss.getH()/2) );
              float Hayze = sqrt(pow(findX, 2) + pow(findY, 2));

              if (Hayze < 50.f)
              {
                //pass bulet closer to unvisible x place
                player.bulletVec.at(i).setPosition(sf::Vector2f(-world_S.x, player.bulletVec.at(i).getPosition().y)); // уичтожение пули игрока
                boss.setHealth(boss.getHealth() - 1);
                serviceSound[1] = true;
              }//end of if

            }//end of if

        //player bullets destroyer
        if ( player.bulletVec.at(i).getPosition().y > world_S.y || player.bulletVec.at(i).getPosition().y < 0 )
           {
           auto iter = player.bulletVec.begin() + i;
           player.dettachBullet(iter);
           }//end of if
      }//end of for
    }//end of if

    // testAirEnemy bullet with wall
    for (int i=0; i < testAirEnemy.bulletVec.size(); i++)
    {
      if ( testAirEnemy.bulletVec.at(i).getPosition().y > world_S.y || testAirEnemy.bulletVec.at(i).getPosition().y < 0 )
        {
        auto iter = testAirEnemy.bulletVec.begin() + i;
        testAirEnemy.dettachBullet(iter);
        }
    }

    // scene node airenemy bullet with wall and player
    if (nodeEY.sceneVec.size() > 0)
    {
        for (int i=0; i<nodeEY.sceneVec.size(); i++)
        {
            if (nodeEY.sceneVec[i].bulletVec.size()>0)
            {
               for (int b=0; b<nodeEY.sceneVec[i].bulletVec.size(); b++)
               {
                 //with player
                 float findX = abs( (player.sP.getPosition().x) - (nodeEY.sceneVec[i].bulletVec.at(b).getPosition().x + 2.5) );
                 float findY = abs( (player.sP.getPosition().y) - (nodeEY.sceneVec[i].bulletVec.at(b).getPosition().y + 2.5) );
                 float Hayze = sqrt(pow(findX, 2) + pow(findY, 2));

                 if (Hayze < 50.f)
                        {
                        flickPl(40, 2);
                        player.setHealth(player.getHealth() - 1);
                        nodeEY.sceneVec[i].bulletVec.at(b).setPosition(nodeEY.sceneVec[i].bulletVec.at(b).getPosition().x, world_S.y + (float)i);
                        serviceSound[5] = true;
                        }

                 if (nodeEY.sceneVec[i].bulletVec.at(b).getPosition().y > world_S.y + 100.f || nodeEY.sceneVec[i].bulletVec.at(b).getPosition().y < 0)
                 {
                 auto iter = nodeEY.sceneVec[i].bulletVec.begin() + b;
                 nodeEY.sceneVec[i].dettachBullet(iter);
                 }//end of if
               }// end of for
            }//end of if
        }//end of for
    }//end of if

    //scene node air enemy with wall and with player
    for (int i=0; i < nodeEY.sceneVec.size(); i++)
    {
       if ( nodeEY.sceneVec.at(i).sP.getPosition().y > world_S.y + 20.f)
          {
          auto iter = nodeEY.sceneVec.begin() + i;
          nodeEY.dettachEnemy(iter);
          }

       float findX = abs( (player.sP.getPosition().x) - (nodeEY.sceneVec[i].sP.getPosition().x + nodeEY.sceneVec[i].getW()/2) );
       float findY = abs(  (player.sP.getPosition().y) - (nodeEY.sceneVec[i].sP.getPosition().y + nodeEY.sceneVec[i].getH()/2) );
       float Hayze = sqrt(pow(findX, 2) + pow(findY, 2));

       if (Hayze < 130.f && player.getTrigerable() == true)
          {
          flickPl(40, 2);
          player.setHealth(player.getHealth() - 1);
          serviceSound[5] = true;
          }
    }//end of for

    //boss bullets with wall and player
    if (boss.bulletVec.size() > 0)
    {
      for(int b=0; b<boss.bulletVec.size(); b++)
      {
        // with player
        float findX = abs( (player.sP.getPosition().x) - (boss.bulletVec.at(b).getPosition().x + 2.5) );
        float findY = abs( (player.sP.getPosition().y) - (boss.bulletVec.at(b).getPosition().y + 2.5) );
        float Hayze = sqrt(pow(findX, 2) + pow(findY, 2));

        if (Hayze < 50.f)
                        {
                        flickPl(40, 2);
                        player.setHealth(player.getHealth() - 1);
                        boss.bulletVec.at(b).setPosition(boss.bulletVec.at(b).getPosition().x, world_S.y + (float)b);
                        serviceSound[5] = true;
                        }

        if ( boss.bulletVec.at(b).getPosition().y > world_S.y + 100.f || boss.bulletVec.at(b).getPosition().y < 0 )
        {
            auto iter = boss.bulletVec.begin() + b;
            boss.dettachBullet(iter);
        }// end of if
      }// end of for
    }//end of if

    //boss burn shapes with wall
    if(boss.burnVec.size() > 0)
    {
        for (int bu=0; bu<boss.burnVec.size(); bu++)
        if (boss.burnVec.at(bu).getPosition().y > world_S.y || boss.burnVec.at(bu).getPosition().y < 0.f ||
              boss.burnVec.at(bu).getPosition().x > world_S.x || boss.burnVec.at(bu).getPosition().x < 0.f)
        {
            auto iter = boss.burnVec.begin() + bu;
            auto iterBurn = boss.burnUVec.begin() + bu;
            boss.dettachBurn(iter, iterBurn);

        }//end of if
    }//end of if

    // borning a boss, next step of activation in updateLandScape
    if(nodeEY.sceneVec.size() == 0) this->isBoss = true;
}//end of void


//***********************
//*****NODES_MATH*******
//*********************

//FIL--UP-- SceneNode nodeEY
void  Game::nodeFilUp(int stage)
{
   //default values
   specific_Texture::ID_air idEnemyOne = specific_Texture::ID_air::Defeater;
   specific_Texture::ID_air idEnemyTwo = specific_Texture::ID_air::Raptor;
   specific_Texture::ID_air idEnemyThree = specific_Texture::ID_air::Combat;


   //fill up texture variables by the names
   if (stage ==  1)
        {
         idEnemyOne = specific_Texture::ID_air::Defeater;
         idEnemyTwo = specific_Texture::ID_air::Raptor;
         idEnemyThree = specific_Texture::ID_air::Combat;
        }//end of
   else if (stage ==  2)
        {
         idEnemyOne = specific_Texture::ID_air::ComRap;
         idEnemyTwo = specific_Texture::ID_air::SRD;
         idEnemyThree = specific_Texture::ID_air::NRD;
        }//end of
   else if (stage ==  3)
        {
         idEnemyOne = specific_Texture::ID_air::NRDC;
         idEnemyTwo = specific_Texture::ID_air::SRD;
         idEnemyThree = specific_Texture::ID_air::NRD;
        }//end of
   else {};//end of construction

   //texture rectangle variables
   float filW = 0.f;
   float filH = 0.f;

   if (nodeEY.sceneVec.size() > 0)
          {
            for (int i=0; i<nodeEY.sceneVec.size(); i++)
                {
                   int who = rand() % 300;
                   //std::cout << "FILL UP VALUE ---> " << who << std::endl;
                   float sclX = 0.8;
                   float sclY = 0.8;

                   if (who < 100) {
                        nodeEY.sceneVec[i].sP.setTexture(ReS.getTextureAir(idEnemyOne));
                        filW = ReS.getEnemySize(idEnemyOne).x;
                        filH = ReS.getEnemySize(idEnemyOne).y;
                        nodeEY.sceneVec[i].sP.setTextureRect(sf::IntRect(filW, filH, -filW, -filH));

                        nodeEY.sceneVec[i].setWH(ReS.getEnemySize(idEnemyOne).x * sclX, ReS.getEnemySize(idEnemyOne).y * sclY); // filling enemySIZE!
                        nodeEY.sceneVec[i].sP.setScale(sclX,sclY);
                   }
                   else if (who < 200 && who > 100){
                        nodeEY.sceneVec[i].sP.setTexture(ReS.getTextureAir(idEnemyTwo));
                        filW = ReS.getEnemySize(idEnemyTwo).x;
                        filH = ReS.getEnemySize(idEnemyTwo).y;
                        nodeEY.sceneVec[i].sP.setTextureRect(sf::IntRect(filW, filH, -filW, -filH));

                        nodeEY.sceneVec[i].setWH(ReS.getEnemySize(idEnemyTwo).x * sclX, ReS.getEnemySize(idEnemyTwo).y * sclY); // filling enemySIZE!
                        nodeEY.sceneVec[i].sP.setScale(sclX,sclY);
                   }
                   else {
                        nodeEY.sceneVec[i].sP.setTexture(ReS.getTextureAir(idEnemyThree));
                        filW = ReS.getEnemySize(idEnemyThree).x;
                        filH = ReS.getEnemySize(idEnemyThree).y;
                        nodeEY.sceneVec[i].sP.setTextureRect(sf::IntRect(filW, filH, -filW, -filH));

                        nodeEY.sceneVec[i].setWH(ReS.getEnemySize(idEnemyThree).x * sclX, ReS.getEnemySize(idEnemyThree).y * sclY); // filling enemySIZE!
                        nodeEY.sceneVec[i].sP.setScale(sclX,sclY);
                   };//end of if else
                }//end of for
          }//end of if
}//end of void

void Game::nodeFilNearView(int stage) { };

// FIL--UP-- Boss
void Game::bossFill(int stage)
{
  boss.bSp.setScale(1.f, 1.f);

  if (stage == 1)
    {
       boss.stageCounter = stage; // organization of a boss level variable
       boss.replCounter = 0; // organization of a level counter
       boss.setThreeUVec(stage); // organization of the boss bullet directions
       specific_Texture::ID_air idAir = specific_Texture::ID_air::ComRap; // organization of the texture
       boss.bSp.setTexture(ReS.getTextureAir(idAir));
       boss.setWH(ReS.getEnemySize(idAir).x, ReS.getEnemySize(idAir).y); // initialization of width and height of sprite
       boss.bSp.setTextureRect(sf::IntRect(0, 0, +boss.getW(), +boss.getH()));
       boss.bSp.setPosition(480.f,20.f); // organization of boss position
    }//end of if
  else if (stage == 2)
    {
       float sclX = 0.6;
       float sclY = 0.6;

       boss.stageCounter = stage; // organization of a boss level variable
       boss.replCounter = 0; // organization of a level counter
       boss.setThreeUVec(stage); // organization of the boss bullet directions
       specific_Texture::ID_air idAir = specific_Texture::ID_air::ComRapDeaf; // organization of the texture
       boss.bSp.setTexture(ReS.getTextureAir(idAir));
       boss.setWH(ReS.getEnemySize(idAir).x, ReS.getEnemySize(idAir).y); // initial initialization of width and height of sprite
       boss.bSp.setTextureRect(sf::IntRect(boss.getW(), boss.getH(), -boss.getW(), -boss.getH()));
       boss.bSp.setPosition(480.f,20.f); // organization of boss position

       // and in the case of scaling, the length and width are reassigned additionally
       boss.bSp.setScale(sclX, sclY);
       boss.setWH(ReS.getEnemySize(idAir).x * sclX, ReS.getEnemySize(idAir).y * sclY);

    }//end of if
  else if (stage == 3)
    {
       boss.stageCounter = stage; // organization of a boss level variable
       boss.replCounter = 0; // organization of a level counter
       boss.setThreeUVec(stage); // organization of the boss bullet directions
       specific_Texture::ID_air idAir = specific_Texture::ID_air::Boss; // organization of the texture
       boss.bSp.setTexture(ReS.getTextureAir(idAir));
       boss.setWH(ReS.getEnemySize(idAir).x, ReS.getEnemySize(idAir).y); // initial  initialization of width and height of sprite
       boss.bSp.setTextureRect(sf::IntRect(0, 0, +boss.getW(), +boss.getH()));
       boss.bSp.setPosition(470.f,20.f); // organization of boss position

        // and in the case of scaling, the length and width are reassigned additionally
       boss.bSp.setScale(0.8, 0.8);
       boss.setWH(ReS.getEnemySize(idAir).x * 0.8, ReS.getEnemySize(idAir).y * 0.8); //организаци€ длины и ширины спрайта
    }//end of if
  else {}; //end of construction

}

void Game::setGameStageEntities(int stg)
{
    // first view music stop
    this->ReS.getMusic().stop();

    // initialization of stage showing text
    gameText.setShowStage(iternal_clk.getElapsedTime().asMilliseconds()/100, stg);

    // initialization of scrolling landscape textures
    specific_Texture::ID_scene scroll;
    if (stg == 1)
    {
     scroll = specific_Texture::ID_scene::Stage_1;
    }
    else if(stg == 2)
    {
    scroll = specific_Texture::ID_scene::Stage_2;
    }
    else if (stg == 3)
    {
    scroll = specific_Texture::ID_scene::Stage_3;
    }
    else {};

    mLandscapeFirst.setTexture(ReS.getTextureScene(scroll));
    mLandscapeFirst.setTextureRect(sf::IntRect(0.f, 0.f, 1200.f, 2200.f));

    mLandscapeSecond.setTexture(ReS.getTextureScene(scroll));
    mLandscapeSecond.setTextureRect(sf::IntRect(0.f, 0.f, 1200.f, 2200.f));

    mLandscapeFirst.setPosition(sf::Vector2f(0.f, -1300.f));
    mLandscapeSecond.setPosition(sf::Vector2f(0.f, +400.f));


    // initialization of scene node
    nodeEY.setSceneF(-200.f);

    if (stg == 1)
    {
    nodeEY.autoGenerateSceneNode(40, 1100.f, world_S.x);
    }
    else if (stg == 2)
    {
    nodeEY.autoGenerateSceneNode(60, 800.f, world_S.x);
    }
    else if (stg == 3)
    {
    nodeEY.autoGenerateSceneNode(80, 550.f, world_S.x);
    }
    else{};

    this->nodeFilUp(stg);

    // initialization of boss
    bossFill(stg);
    boss.isAlive = false;
    boss.bossIsBurn = false;
    this->isBoss = false;
    boss.setHealth(100);
}

void Game::playSounds()
{
  for (int s=0; s<14; s++)
  {
    if (serviceSound[s])
    {
    sound[s].play();
    serviceSound[s] = false;
    };//end of if
  }//end of for
}//end of void

