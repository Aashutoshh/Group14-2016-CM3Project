
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <ctime>

#include "BaseObject.h"
#include "Global.h"
#include "Alien.h"
#include "Spaceship.h"
#include "Bullet.h"
#include "AlienBullet.h"
#include "PowerUp.h"
#include "Explosion.h"
#include "Background.h"
#include "Asteroid.h"
#include "SubBoss.h"
#include <list>

using namespace std;
 
bool keys[] = { false, false, false, false, false };
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE }; //Enumeration for key input array

//===========================================================================================================
//globals for main.cpp
//============================================================================================================

Spaceship *ship1;  //Created our spaceship object pointer

//Create the updation list of objects
list < BaseObject *> gameObjects;   //Created a list of BaseObject type called gameObjects

//Lists are different from arrays. We need more than just for loops to iterate. To iterate through a list we create iterators
list < BaseObject *>::iterator itr1;  //created an iterator of BaseObject type called itr1
list < BaseObject *>::iterator itr2;  //created an iterator of BaseObject type called itr2

//======================================================================================================================
//prototypes
/*Insert prototypes of necessary global functions here for main.cpp*/
//======================================================================================================================

int main()
{
	//================================================================================================================
	//Temp or Shell Variables
	//================================================================================================================

	bool done = false;
	bool render = false;

	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;

	//====================================================================================================================
	//Project Variables Here
	//====================================================================================================================
	ship1 = new Spaceship; //Using dynamic memory to create our player ship from the heap

	ALLEGRO_BITMAP *shipImage = NULL;

	//=================================================================================================================
	//Allegro Variables Here
	//=================================================================================================================

	ALLEGRO_DISPLAY *display = NULL;   //Create and initialize allegro display object
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;  //Create and initialize allegro event que
	ALLEGRO_TIMER *timer;          //Create Allegro timer object to cap the FPS to playable game speed ie 60 FPS standard
	ALLEGRO_FONT *font18;         //Font variable for outputting text. Size 18

	//===============================================================================================================
	//Initialize Allegro Functions
	//=================================================================================================================

	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if (!display)										//test display object
		return -1;

	//===============================================================================================================
	//Install Necessary Allegro Addons
	//NB I added all addons I thought we woud need later on as well
	//===============================================================================================================

	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();

	//==========================================================================================
	//Initialize Necessary Project images and addons -- PROJECT INIT SECTION
	//=============================================================================================

	font18 = al_load_font("arial.ttf", 18, 0);  //NB Add the font file arial.ttf in your soln folder
	//Can access the font files from windows control panel
	//Add in the Spaceship Image 
	shipImage = al_load_bitmap("spaceship_by_arboris.png");
	al_convert_mask_to_alpha(shipImage, al_map_rgb(255, 0, 255)); //Make the background of sprite image transparent
	ship1->Init(shipImage); //Initialize ship by sending an image to init function

	//AFTER INITIALIZING AN OBJECT LIKE THE SHIP PUSH IT TO OUR LIST
	gameObjects.push_back(ship1);  // Pushed the ship to back of our list
	                              //Shows inheritance and polymorphism. Better than an array since we don't know how big
	                               //our array should be. With a list of base type objects we can just push and pop --PM.


	//========================================================================================================
	//INITIALIZE THE TIMER FOR TIMED EVENTS IN THE MAIN GAME LOOP
	//HELPS PROVIDE SMOOTH GAMEPLAY AT 60 FPS
	//==========================================================================================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();

	//========================================================================================================
	/**************************************MAIN GAME LOOP STARTS HERE*************************************/
	//========================================================================================================
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//==============================================
		//CHECK FOR KEY INPUT
		//==============================================
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;  //Use the space key for bullets once bullet code is done
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		//==========================================================================================
		//GAME UPDATE ==>UPDATE THE FPS AND FRAMES ACCORDINGLY FOR SMOOTH GAMEPLAY
		//==========================================================================================
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//UPDATE FPS===========
			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			//=====================


			if (keys[UP])
				ship1->mvUp();
			else if (keys[DOWN])
				ship1->mvDOWN();
			else
				ship1->animationReset(1);  //Refer to sprite sheet -- PM

			if (keys[LEFT])
				ship1->mvLEFT();
			else if (keys[RIGHT])
				ship1->mvRIGHT();
			else
				ship1->animationReset(0);  //Refer to sprite sheet -- PM

		}

		//=========================================================================================================//
		//                       UPDATE OBJECTS USING THE LIST
		//=========================================================================================================//
		for (itr1 = gameObjects.begin(); itr1 != gameObjects.end(); ++itr1)
		{
			(*itr1)->UpdateObject();
		}

		//COLLISIONS CONSIDERATIONS FOR UPDATING
		for (itr1 = gameObjects.begin(); itr1 != gameObjects.end(); ++itr1)
		{
			if (!(*itr1)->onScreenCollide()) //if object is both not on screen and collidable move on to the next one
				continue;
			for (itr2 = itr1; itr2 != gameObjects.end(); ++itr2) //itr2 starts pointing at itr1 object upon collision detection
			{
				if (!(*itr2)->onScreenCollide()) // again if object is both not on screen and collidable move on to the next one
					continue;
				if ((*itr1)->getObjType() == (*itr2)->getObjType())  //We don't care if alike objects collide with each other
					continue;
				if ((*itr1)->getCollision((*itr2))) //Check if the objects of differing types have collided
				{
					(*itr1)->Collided((*itr2)->getObjType());
					(*itr2)->Collided((*itr1)->getObjType()); //Tell the 2 objects that they collided into each other
				}

			}
		}

		//FREE UP MEMORY AS SOON AS AN OBJECT GOES OFF SCREEN
		//HELPS US PUT MORE AND MORE OBJECTS ON SCREEN WITHOUT AFFECTING MEMORY TOO MUCH
		for (itr1 = gameObjects.begin(); itr1 != gameObjects.end();)  //we leave out the ++itr1 part here since the body updates
		{
			if (!(*itr1)->getOnScreen())
			{
				delete (*itr1);
				itr1 = gameObjects.erase(itr1);  //NB We don't call the destroy method here since we don't 
			}                                    //want to destroy the bitmap images at this stage
			else
			{
				itr1++;
			}
		}                               


		//======================================================================================================
		//RENDER==>UPDATE THE OBJECT'S POSITION ON SCREEN AND DRAW IT ACCORDINGLY
		//======================================================================================================

		if (render && al_is_event_queue_empty(event_queue)) //ONLY DRAW WHEN EVENT QUE IS EMPTY FOR SMOOTH GAMEPLAY
		{
			render = false;
			al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 25, 0, "FPS: %i", gameFPS); //display FPS on screen
			                                                        //NB can be removed later. I just wanted to check
			                                                        //our actual FPS--PM.

			
		//=========================================================================================================//
		//                       RENDER OBJECTS USING THE LIST
		//=========================================================================================================//
			for (itr1 = gameObjects.begin(); itr1 != gameObjects.end(); ++itr1)
			{
				(*itr1)->RenderObject();
			}

			al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Player has %i lives left. Player has destroyed %i objects",
			ship1->getTries(), ship1->getEnemiesDestroyed());

			//Draw the ship
			//ship1->UpdateObject();
			//ship1->RenderObject(); =================We don't need these anymore due to the slick list ;-)

			//FLIP BUFFERS
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}

	//============================================================================================================//                                                                 
	//                                 DESTROY ANY PROJECT OBJECTS USED   
	//Release Resources============================================================================================//
	//NB Whatever resources you add later in the project must be removed here to prevent
	//memory leaks. -- PM==========================================================================================//

	for (itr1 = gameObjects.begin(); itr1 != gameObjects.end();)  //we leave out the ++itr1 part here since the body updates
	{
		(*itr1)->DestroyObject();
		delete (*itr1);                  //Delete the objects themselves
		itr1 = gameObjects.erase(itr1);  //Remove this index of itr1 completely then return back to the next
	}                                    //Loop updation in body 



	//=======================================================================================================//
	//                    DESTROY SHELL OBJECTS USED BY ALLEGRO LIBRARIES                                    //
	//=========================================================================================================//
	al_destroy_bitmap(shipImage);
	al_destroy_font(font18);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

	return 0;
}


