/** \file enum.h
 * \brief Enumeration file for the Flying String Defence project
 *
 * \author Tim Boundy
 * \date May 2007
 */
#ifndef ENUM_H
#define ENUM_H

#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//Basic Window values
#define FPS 60.0
#define TIMESCALE 1.0
#define TIMESTEP TIMESCALE/FPS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define GROUND_HEIGHT 60
#define TIMER_CALLBACK 65535
#define SEPARATION 200

//Window
#define MAX_BASES 10
#define MAX_GUNS 5
#define MAX_SHELLS 20
#define MAX_MISSILES 40

//Colours
#define FL_DARK_GREY 39
#define SKY_BLUE fl_rgb_color(170, 213, 255)
#define GRASS fl_rgb_color(32, 156, 18)
#define GREY fl_rgb_color(85, 68, 63)

//Game state
enum {INITIALISE = 0,NORMAL, GAMEOVER, PAUSED};
#define SCORE_NEXT_LEVEL 20
#define LEVEL_SCALE (0.8 + level*0.2)

//Gun
#define BARREL_WIDTH 10
#define BARREL_LENGTH 40
#define GUN_BASE_RADIUS 40

//Shell
#define SHELL_VELOCITY 1500.0
#define SHELL_BLAST_FACTOR 8
#define SCATTER_FACTOR(width) (rand()%(int)width*SHELL_BLAST_FACTOR - width*SHELL_BLAST_FACTOR/2)

//ShellExplode
#define SE_INITIAL_PERIOD 0.1

//Missile
#define MISSILE_VELOCITY (((rand()%100+50)+(rand()%100+50)+(rand()%100+50))/3) //Approximate gaussian probability
#define MISSILE_SPAWN_FACTOR 50 // The higher the number, the less often the missiles spawn

//UFO
#define UFO_VELOCITY 100
#define UFO_SPAWN_FACTOR 500
#define UFO_FIRE_RATE 100

// Radius for collision detection
#define GUN_RADIUS 20.0
#define BASE_RADIUS 25.0
#define MISSILE_RADIUS 2.0
#define UFO_RADIUS 25

using std::list;
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

#endif

