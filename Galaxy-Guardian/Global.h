#pragma once

//GLOBAL VARIABLES FOR THE ENTIRE PROJECT

const int width = 800;
const int height = 400;
enum ID{ PLAYER, ENEMY, BULLET, BORDER, MISC, EXPLOSION }; //ID array for player and other objects
enum STATE{ TITLE, PLAYING, LOST }; //3 stage finite state machine array. To be used later in development
