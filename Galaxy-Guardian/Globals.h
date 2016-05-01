#pragma once

//GLOBAL VARIABLES FOR THE ENTIRE PROJECT

const int width = 800;
const int height = 600;
enum ID{ PLAYER, ENEMY, BULLET, BORDER, MISC, EXPLOSION, POWER, ALIEN, ALIENBULLET, BOSS }; //ID array for player and other objects
enum STATE{ INTRO, TITLE, PLAYING, LOST, LEVEL, CREDITS }; //3 stage finite state machine array. To be used later in development
//To add levelling add to this state machine