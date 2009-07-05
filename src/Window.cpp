/** \file Window.cpp
 * \brief Code implementation for Window class
 *
 * \author Tim Boundy
 * \date May 2007
 */
#include "Window.h"

#include <Fl/Fl.H>
#include <Fl/fl_draw.h>
#include <Fl/Fl_Timer.H>
#include <math.h>
#include <time.h>

#ifdef WIN32
#include <windows.h>
#endif

#include "Gun.h"
#include "Base.h"
#include "Shell.h"
#include "Missile.h"
#include "UFO.h"
#include "ShellExplosion.h"

/** \brief Constructor for Window
 *
 * The constructor seeds the random number generator, initialises some strings and
 * sets the gamestate to INITIALISE, as well as creating the Fl_Double_Window.
 */
Window::Window(int w, int h, const char *l = 0) : Fl_Double_Window(w, h, l)
{
	srand(time(NULL));
	strlvl = "Level: ";
	strscr = "Score: ";
	gamestate = INITIALISE;
}

/** \brief Destructor for Window
 *
 * The destructor calls the cleanup routine.
 */
Window::~Window()
{
	cleanup();
}

/* \brief A function to start the game.
 *
 * This routine starts the game by initialising the score and level, spawning the
 * PlayerItem objects and setting the start time to current time.
 */
void Window::start_game()
{
	gamestate = NORMAL;
	lasttime = get_time();
	score = 0;
	level = 1;
	new Base(WIN_WIDTH/2 + SEPARATION/2, WIN_HEIGHT - GROUND_HEIGHT);
	new Base(WIN_WIDTH/2 - SEPARATION/2, WIN_HEIGHT - GROUND_HEIGHT);
	new Base(WIN_WIDTH/2 + 3*SEPARATION/2, WIN_HEIGHT - GROUND_HEIGHT);
	new Base(WIN_WIDTH/2 - 3*SEPARATION/2, WIN_HEIGHT - GROUND_HEIGHT);
	new Gun(WIN_WIDTH/2, WIN_HEIGHT-GROUND_HEIGHT, BARREL_WIDTH);
	new Gun(WIN_WIDTH/2 + SEPARATION, WIN_HEIGHT-GROUND_HEIGHT, BARREL_WIDTH);
	new Gun(WIN_WIDTH/2 - SEPARATION, WIN_HEIGHT-GROUND_HEIGHT, BARREL_WIDTH);
}

/** \brief Cleanup function.
 *
 * This function deletes all objects from the game.
 */
void Window::cleanup()
{
	int i = 0;
	while(PlayerItem::playeritems().size() > 0)
	{
		delete *PlayerItem::playeritems().begin();
#ifdef DEBUG
		cout << "deleted shootable " << i << endl;
		i++;
#endif
	}
	i = 0;
	while(Projectile::projectiles().size() > 0)
	{
		delete *Projectile::projectiles().begin();
#ifdef DEBUG
		cout << "deleted projectile " << i << endl;
		i++;
#endif
	}
	i = 0;
	while(Explosion::explosions().size() > 0)
	{
		delete *Explosion::explosions().begin();
#ifdef DEBUG
		cout << "deleted explosion " << i << endl;
		i++;
#endif
	}
}

/** \brief Drawing routine for the game.
 *
 * This routine draws the Window and calls the draw functions for all
 * the objects in the game. It also draws some messages to the screen
 * depending on the current state of the game.
 */
void Window::draw()
{
	fl_color(SKY_BLUE);
	fl_rectf(0, 0, WIN_WIDTH, WIN_HEIGHT);

	if (gamestate == INITIALISE)
	{
		int x = 0;
		int y = 0;
		strstatus = "Press Esc to start a new game.";
		fl_color(FL_BLACK);
		fl_font(FL_HELVETICA,30);
		fl_measure(strstatus.c_str(), x, y);
		fl_draw(strstatus.c_str(), (WIN_WIDTH-x)/2,(WIN_HEIGHT+y-30)/2);
		strstatus = "Press Esc during the game to pause.";
		x = 0;
		y = 0;
		fl_measure(strstatus.c_str(), x, y);
		fl_draw(strstatus.c_str(), (WIN_WIDTH-x)/2,(WIN_HEIGHT+y+30)/2);
	}
	else if (gamestate == GAMEOVER)
	{
		int x = 0;
		int y = 0;
		strstatus = "You Lose! Press Esc to start a new game.";
		fl_color(FL_BLACK);
		fl_font(FL_HELVETICA,30);
		fl_measure(strstatus.c_str(), x, y);
		fl_draw(strstatus.c_str(), (WIN_WIDTH-x)/2,(WIN_HEIGHT+y-30)/2);
		oss.str("");
		oss << "Score was " << score << ", died on level " << level << ".";
		x = 0;
		y = 0;
		fl_measure(oss.str().c_str(), x, y);
		fl_draw(oss.str().c_str(), (WIN_WIDTH-x)/2,(WIN_HEIGHT+y+30)/2);
	}
	else // normal game operation
	{
		for (unsigned int i = 0; i < Projectile::projectiles().size(); i++)
		{
			Projectile::projectiles()[i]->draw();
		}
		
		for (unsigned int i = 0; i < Explosion::explosions().size(); i++)
		{
			Explosion::explosions()[i]->draw();
		}
		
		fl_color(GRASS);
		fl_rectf(0, WIN_HEIGHT-GROUND_HEIGHT, WIN_WIDTH, WIN_HEIGHT);

		for (unsigned int i = 0; i < PlayerItem::playeritems().size(); i++)
		{
			PlayerItem::playeritems()[i]->draw();
		}

		fl_color(FL_BLACK);
		fl_font(FL_HELVETICA,20);
		level = 1 + score / SCORE_NEXT_LEVEL;
		oss.str("");
		oss << strlvl << level;
		fl_draw(oss.str().c_str(), 40,40);
		oss.str("");
		oss << strscr << score;
		fl_draw(oss.str().c_str(), 40,60);

		if (gamestate == PAUSED)
		{
			int x = 0;
			int y = 0;
			strstatus = "Paused... Press Esc to Continue.";
			fl_color(FL_BLACK);
			fl_font(FL_HELVETICA,30);
			fl_measure(strstatus.c_str(), x, y);
			fl_draw(strstatus.c_str(), (WIN_WIDTH-x)/2,(WIN_HEIGHT+y)/2);
		}
	}
}

/** \brief Animation function for the game.
 *
 * This function calls the animate and collision routines for the various objects in the game.
 */
void Window::animate()
{
	currenttime = get_time();
	//Spawn UFO
	if (rand() % (int)UFO_SPAWN_FACTOR/LEVEL_SCALE == 0)
	{
		new UFO(0, 100, WIN_WIDTH + 50, 100, UFO_VELOCITY*LEVEL_SCALE);
	}
	//Spawn Missile
	if ((Missile::missiles().size() < MAX_MISSILES) && (rand() % (int)(MISSILE_SPAWN_FACTOR/LEVEL_SCALE) == 0))
	{
		if (PlayerItem::playeritems().size() != 0)
		{
			int index = rand() % PlayerItem::playeritems().size();
			PlayerItem *target = PlayerItem::playeritems()[index];
			new Missile((double)(rand() % WIN_WIDTH), 0.0, target->x(), target->y(), MISSILE_VELOCITY*LEVEL_SCALE);
		}
	}
	//UFO action
	for (int i = 0; i < (int)UFO::ufos().size(); i++)
	{
		if (UFO::ufos()[i]->animate(currenttime - lasttime, level))
		{
			delete UFO::ufos()[i];
			i--;
		}
	}
	//Missile action
	for (int i = 0; i < (int)Missile::missiles().size(); i++)
	{
		if ((Missile::missiles()[i]->collision_detect() == true) || (Missile::missiles()[i]->animate(currenttime - lasttime)))
		{
#ifdef DEBUG2
			cout << "missile " << i << " action" << endl;
#endif
			Missile::missiles()[i]->on_death();
			delete Missile::missiles()[i];
			i--;
		}
	}
	//Shell action
	for (int i = 0; i < (int)Shell::shells().size(); i++)
	{
		if (Shell::shells()[i]->animate(currenttime - lasttime))
		{
#ifdef DEBUG2
			cout << "shell " << i << " action" << endl;
#endif
			Shell::shells()[i]->on_death();
			delete Shell::shells()[i];
			i--;
		}
	}
	//Explosion animate
	for (int i = 0; i < (int)Explosion::explosions().size(); i++)
	{
		if (Explosion::explosions()[i]->animate(currenttime - lasttime))
		{
			delete Explosion::explosions()[i];
			i--;
		}
	}
	//ShellExplosion collision
	for (int i = 0; i < (int)ShellExplosion::shellexplosions().size(); i++)
	{
		score = ShellExplosion::shellexplosions()[i]->collision_detect(score);
		if (ShellExplosion::shellexplosions()[i]->timealive() > 1)
		{
			delete ShellExplosion::shellexplosions()[i];
		}
	}
	lasttime = currenttime;
}

/** \brief Hanler function for the game.
 *
 * This function handles the various events that FLTK generates as well as the
 * timer event generated in main.cpp. The Esc key is used as a rudimentary menu
 * system and the mouse controls the Gun objects.
 * \param e Event number
 * \return Returns 1 if event handled, otherwise return what Fl_Group::handle returned
 */
int Window::handle(int e)
{
	int ret = Fl_Group::handle(e);

#ifdef DEBUG // toggle gun powerup with tab button in debug mode
	if ((e == FL_KEYDOWN) && (Fl::event_key() == FL_Tab))
	{
		for (int i = 0; i < Gun::guns().size(); i++)
		{
			Gun::guns()[i]->barrel_width(30-Gun::guns()[i]->barrel_width());
		}
	}
#endif

	if ((e == FL_KEYDOWN) && (Fl::event_key() == FL_Escape))
	{
		switch (gamestate)
		{
			case INITIALISE: // start game
				start_game();
				break;
			case NORMAL: // pause game
				gamestate = PAUSED;
				break;
			case PAUSED: // unpause game
				gamestate = NORMAL;
				// reset last time because a large period of time may have passed in pause mode that shouldn't be counted
				lasttime = get_time();
				break;
			case GAMEOVER: // restart game
				cleanup();
				start_game();
				break;
			default:
				break;
		}
		damage(FL_DAMAGE_ALL);
		return 1;
	}

	// if player has run out of guns or bases, game over
	if (((Gun::guns().size() == 0) || (Base::bases().size() == 0)) && (gamestate == NORMAL))
	{
		gamestate = GAMEOVER;
		cleanup();
		damage(FL_DAMAGE_ALL);
		return 1;
	}
	
	if (gamestate == NORMAL) // handle mouse and timer events
	{
		switch (e)
		{
			case TIMER_CALLBACK:
				animate();
				damage(FL_DAMAGE_ALL);
				return 1;
			case FL_DRAG:
				//do the same for move and drag
			case FL_MOVE:
				for (unsigned int i = 0; i < Gun::guns().size(); i++)
				{
					Gun::guns()[i]->target(Fl::event_x(), Fl::event_y());
				}
				damage(FL_DAMAGE_ALL);
				return 1;
			case FL_PUSH:
				for (unsigned int i = 0; i < Gun::guns().size(); i++)
				{
					if ((Gun::guns()[i]->target_valid() == true) && (Shell::shells().size() < MAX_SHELLS))
					{
						double width = Gun::guns()[i]->barrel_width();
						new Shell(Gun::guns()[i]->x(), Gun::guns()[i]->y(), Fl::event_x()+i*SCATTER_FACTOR(width), Fl::event_y()+i*SCATTER_FACTOR(width), width/2);
					}
				}
				damage(FL_DAMAGE_ALL);
				return 1;
			default:
				return ret;
		}
	}
	else
	{
		return ret;
	}
}
