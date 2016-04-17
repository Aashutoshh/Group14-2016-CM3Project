
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <ctime>

#include "BaseObject.h"
#include "Spaceship.h"
#include "Globals.h"
#include <list>


using namespace std;
 
bool keys[] = { false, false, false, false, false };
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE };

//globals
Spaceship *ship1;

//Create the updation list of objects
list < BaseObject *> gameObjects;   //Created a list of BaseObject type called gameObjects

list < BaseObject *>::iterator itr1;  //created an iterator of BaseObject type called itr1
list < BaseObject *>::iterator itr2;  //created an iterator of BaseObject type called itr2

//prototypes

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
	float tempX = 0;
	float tempY = 0;

	int temprandX = 0;
	int temprandY = 0;

	//====================================================================================================================
	//Project Variables Here
	//====================================================================================================================

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
	//NB I added all addons I thought we would need later on as well
	//===============================================================================================================

	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();

	//==========================================================================================
	//Initialize Necessary Project images and addons
	//=============================================================================================

	font18 = al_load_font("arial.ttf", 18, 0);

	//=============================================================================================
	// Add in objects here
	//=============================================================================================
	ship1 = new Spaceship;
	shipImage = al_load_bitmap("spaceship_by_arboris.png");
	al_convert_mask_to_alpha(shipImage, al_map_rgb(255, 0, 255));
	ship1->Init(shipImage);
	//AFTER INITIALIZING AN OBJECT LIKE THE SHIP PUSH IT TO OUR LIST
	gameObjects.push_back(ship1);

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

		//===========================================================================================
		//CHECK FOR KEY INPUT
		//==========================================================================================
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
			{
				keys[SPACE] = true;              //Use the space key for bullets once bullet code is done
			}
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

		//==========================================================================================================
		//GAME UPDATE ==>UPDATE THE FPS AND FRAMES ACCORDINGLY FOR SMOOTH GAMEPLAY
		//=========================================================================================================
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



			//=======================================================================================================
			//  MOVE THE SHIP ACCORDINGLY //
			//=========================================================================================================
			if (keys[UP])
			{
				ship1->mvUp();
			}
			else if (keys[DOWN])
			{
				ship1->mvDOWN();
			}
			else
			{
				ship1->animationReset(1);
			}  //Refer to sprite sheet -- PM

			if (keys[LEFT])
			{
				ship1->mvLEFT();
			}
			else if (keys[RIGHT])
			{
				ship1->mvRIGHT();
			}
			else
			{
				ship1->animationReset(0);
			}  //Refer to sprite sheet -- PM

			   //=========================================================================================================//
			   //                       UPDATE OBJECTS USING THE LIST
			   //=========================================================================================================//
			for (itr1 = gameObjects.begin(); itr1 != gameObjects.end(); ++itr1)
			{
				(*itr1)->UpdateObject();
			}


			//======================================================================================================
			//RENDER==>UPDATE THE OBJECT'S POSITION ON SCREEN AND DRAW IT ACCORDINGLY
			//======================================================================================================

			if (render && al_is_event_queue_empty(event_queue)) //ONLY DRAW WHEN EVENT QUE IS EMPTY FOR SMOOTH GAMEPLAY
			{
				render = false;
				al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 25, 0, "FPS: %i", gameFPS); //display FPS on screen

				//=========================================================================================================//
				//                       RENDER OBJECTS USING THE LIST
				//=========================================================================================================//

				for (itr1 = gameObjects.begin(); itr1 != gameObjects.end(); ++itr1)
				{
					(*itr1)->RenderObject();
				}

				 
				//FLIP BUFFERS
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}

		}
	}
	return 0;
}
