//Created Branch Praneel
//NOTE TO GROUP on 23 March 2016:
//Hi guys. I've completed the spaceship declarations and definition files. I've also designed the main.cpp file
//to test out its updation and rendering onscreen. Feel free to copy this layout to test the rendering of your own
//assigned class objects. However do your testing in your OWN branch and do not merge to master without consulting.
//DO NOT ALTER THE CODE IN MY BRANCH ;-)  --PRANEEL MISTHRY 23/3/16

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <list>

#include "Global.h"
#include "BaseObject.h"
#include "Spaceship.h"

using namespace std;
 
bool keys[] = { false, false, false, false, false };
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE }; //Enumeration for key input array

//===========================================================================================================
//globals for main.cpp
//============================================================================================================

Spaceship *ship1 = new Spaceship();  //Created our spaceship object pointer in memory heap

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
	//Initialize Necessary Project images and addons
	//=============================================================================================

	font18 = al_load_font("arial.ttf", 18, 0);  //NB Add the font file arial.ttf in your soln folder
	//Can access the font files from windows control panel
	//Add in the Spaceship Image 
	shipImage = al_load_bitmap("spaceship_by_arboris.png");
	al_convert_mask_to_alpha(shipImage, al_map_rgb(255, 0, 255));
	ship1->Init(shipImage);

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
		//======================================================================================================
		//RENDER==>UPDATE THE OBJECT'S POSITION ON SCREEN AND DRAW IT ACCORDINGLY
		//======================================================================================================

		if (render && al_is_event_queue_empty(event_queue)) //ONLY DRAW WHEN EVENT QUE IS EMPTY FOR SMOOTH GAMEPLAY
		{
			render = false;
			al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 25, 0, "FPS: %i", gameFPS); //display FPS on screen
			                                                        //NB can be removed later. I just wanted to check
			                                                        //our actual FPS--PM.

			//BEGIN PROJECT RENDERING

			al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Player has %i lives left. Player has destroyed %i objects",
			ship1->getTries(), ship1->getScore());

			//Draw the ship
			ship1->UpdateObject();
			ship1->RenderObject();

			//FLIP BUFFERS
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}

	//Release Resources============================================================================================
	//NB Whatever resources you add later in the project must be removed here to prevent
	//memory leaks. -- PM==========================================================================================

	al_destroy_bitmap(shipImage);
	al_destroy_font(font18);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

	return 0;
}


