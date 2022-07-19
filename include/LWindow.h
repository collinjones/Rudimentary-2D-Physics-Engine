#ifndef _LWindow_
#define _LWindow_

//https://lazyfoo.net/tutorials/SDL/36_multiple_windows/index.php

//Using SDL, standard IO, strings, and string streams
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "toggleButton.h"
#include "displayPanel.h"
#include "slider.h"
#include "button.h"

//Screen dimension constants
const int SCREEN_WIDTH = 200;
const int SCREEN_HEIGHT = 80;

//Total windows
const int TOTAL_WINDOWS = 4;

class LWindow
{
	public:
		//Intializes internals
		LWindow();

		//Creates window
		//1 for grav, 2 for circle, 3 for line, 4 for rect
        bool init1();
        bool init2();
        bool init3();
        bool init4();
		//Handles window events
		void handleEvent( SDL_Event& e );

		//Focuses on window
		void focus();

		//Shows windows contents
		//void render();

		//Deallocates internals
		void free();

		//Window dimensions
		int getWidth();
		int getHeight();

		//Window focii
		bool hasMouseFocus();
		bool hasKeyboardFocus();
		bool isMinimized();
		bool isShown();

        SDL_Renderer* getRenderer();
        SDL_Window* getWindow();
        void LWUIHandler(TTF_Font* font);
        void LWRenderPresent();
        void LWFillScreen();
        int LWLeftClick(SDL_MouseButtonEvent& b);
        int handleButtonClick(SDL_Event& e);
	private:
		//Window data
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;
		unsigned int mWindowID; //made unsigned
		//Window dimensions
		int mWidth;
		int mHeight;

		//Window focus
		bool mMouseFocus;
		bool mKeyboardFocus;
		bool mFullScreen;
		bool mMinimized;
		bool mShown;

		vector<Button*> LWButtons;
		vector<ToggleButton*> LWToggleButtons;
        vector<DisplayPanel*> LWDisplays;
        vector<Slider*> LWSliders;
};

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//Our custom windows
LWindow gWindows[ TOTAL_WINDOWS ];

LWindow::LWindow()
{
	//Initialize non-existant window
	mWindow = NULL;
	mRenderer = NULL;

	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mShown = false;
	mWindowID = -1;
	mWidth = 0;
	mHeight = 0;
}

bool LWindow::init1()
{
   //Create window
   	mWindow = SDL_CreateWindow( "Physics Engine",  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    SDL_Color c = {.r = 100, .g=100, .b=0, .a=255};
   	if( mWindow != NULL )
   	{
   		mMouseFocus = true;
   		mKeyboardFocus = true;
   		mWidth = SCREEN_WIDTH;
   		mHeight = SCREEN_HEIGHT;

   		//Create renderer for window
   		mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED );
   		if( mRenderer == NULL )
   		{
   			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
   			SDL_DestroyWindow( mWindow );
   			mWindow = NULL;
   		}
   		else
   		{
   			//Initialize renderer color
   			SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

   			//Grab window identifier
   			mWindowID = SDL_GetWindowID( mWindow );
   			//Flag as opened
   			mShown = true;

            LWToggleButtons.push_back(new ToggleButton(50, 20, 100, 25, c, c, "Gravity Status: ON", "Gravity Status: OFF",-1));
            SDL_SetWindowPosition(mWindow, 85,110);

   		}
   	}
   	else
   	{
   		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
   	}

   	return mWindow != NULL && mRenderer != NULL;
}

bool LWindow::init2()
{
	//Create window
   	mWindow = SDL_CreateWindow( "Physics Engine",  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT+50, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    SDL_Color c = {.r = 100, .g=100, .b=0, .a=255};
	if( mWindow != NULL )
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;

		//Create renderer for window
		mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
		if( mRenderer == NULL )
		{
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			SDL_DestroyWindow( mWindow );
			mWindow = NULL;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			//Grab window identifier
			mWindowID = SDL_GetWindowID( mWindow );
			//Flag as opened
			mShown = true;
			LWButtons.push_back(new Button(20, 20, 150, 25, c, c, "Add Normal Circle",2));
			LWButtons.push_back(new Button(20, 50, 150, 25, c, c, "Add Attracter Circle",3));
			LWButtons.push_back(new Button(20, 80, 150, 25, c, c, "Add Repeler Circle",4));
			SDL_SetWindowPosition(mWindow, 85,280);
		}
	}
	else
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	return mWindow != NULL && mRenderer != NULL;
}

bool LWindow::init3()
{
	//Create window
   	mWindow = SDL_CreateWindow( "Physics Engine",  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    SDL_Color c = {.r = 100, .g=100, .b=0, .a=255};
	if( mWindow != NULL )
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;

		//Create renderer for window
		mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
		if( mRenderer == NULL )
		{
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			SDL_DestroyWindow( mWindow );
			mWindow = NULL;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			//Grab window identifier
			mWindowID = SDL_GetWindowID( mWindow );
			//Flag as opened
			mShown = true;
			LWButtons.push_back(new Button(20, 20, 150, 25, c, c, "Add line",5));
			SDL_SetWindowPosition(mWindow, 85,480);
		}
	}
	else
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	return mWindow != NULL && mRenderer != NULL;
}

bool LWindow::init4()
{
	//Create window
   	mWindow = SDL_CreateWindow( "Physics Engine",  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    SDL_Color c = {.r = 100, .g=100, .b=0, .a=255};
	if( mWindow != NULL )
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;

		//Create renderer for window
		mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
		if( mRenderer == NULL )
		{
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			SDL_DestroyWindow( mWindow );
			mWindow = NULL;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			//Grab window identifier
			mWindowID = SDL_GetWindowID( mWindow );
			//Flag as opened
			mShown = true;
			LWButtons.push_back(new Button(20, 20, 150, 25, c, c, "Add box",6));
			SDL_SetWindowPosition(mWindow, 85,600);
		}
	}
	else
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	return mWindow != NULL && mRenderer != NULL;
}

int LWindow:: LWLeftClick(SDL_MouseButtonEvent& b) {
  if(b.button == SDL_BUTTON_LEFT){
      int posX;
      int posY;
      SDL_GetMouseState(&posX, &posY);

      for (int i = 0; i < (int) LWButtons.size(); i++) {
          int temp = LWButtons[i]->ProcessClick(posX, posY, LWButtons[i]->getID());
          if (temp!=-1)
          {
            return temp;
          }
      }

      for (int i = 0; i < (int) LWToggleButtons.size(); i++) {
          int temp = LWToggleButtons[i]->ProcessClick(posX, posY);
          if (temp!=-1)
            {
              return temp;
            }
      }
  }
 return -1;
}

int LWindow::handleButtonClick(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN && e.window.windowID == mWindowID) {
        return LWLeftClick(e.button);
    }
    return -1;
}

void LWindow::handleEvent( SDL_Event& e )
{
	//If an event was detected for this window

	if( e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID )
	{
		//Caption update flag
		bool updateCaption = false;

		switch( e.window.event )
		{

			//Window appeared
			case SDL_WINDOWEVENT_SHOWN:
			mShown = true;
			break;

			//Window disappeared
			case SDL_WINDOWEVENT_HIDDEN:
			mShown = false;
			break;

			//Get new dimensions and repaint
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			SDL_RenderPresent( mRenderer );
			break;

			//Repaint on expose
			case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent( mRenderer );
			break;

			//Mouse enter
			case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			updateCaption = true;
			break;

			//Mouse exit
			case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			updateCaption = true;
			break;

			//Keyboard focus gained
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			updateCaption = true;
			break;

			//Keyboard focus lost
			case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			updateCaption = true;
			break;

			//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
            mMinimized = true;
            break;

			//Window maxized
			case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
            break;

			//Window restored
			case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
            break;

			//Hide on close
			case SDL_WINDOWEVENT_CLOSE:
			SDL_HideWindow( mWindow );
			break;


		}

		//Update window caption with new data
		if( updateCaption )
		{
			std::stringstream caption;
			caption << "Physics Engine - ID: " << mWindowID << " MouseFocus:" << ( ( mMouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( mKeyboardFocus ) ? "On" : "Off" );
			SDL_SetWindowTitle( mWindow, caption.str().c_str() );
		}
	}
}

void LWindow::LWUIHandler(TTF_Font* font) {
    SDL_Color White = {255, 255, 255};
    int posX;
    int posY;
    SDL_GetMouseState(&posX, &posY);

    for (int i = 0; i < (int) LWButtons.size(); i++) {
      LWButtons[i]->Update(mRenderer, posX, posY, White, font, mWindow);
    }

    for (int i = 0; i < (int) LWToggleButtons.size(); i++) {
      LWToggleButtons[i]->Update(mRenderer, posX, posY, White, font, mWindow);
    }

}
void LWindow::focus()
{
	//Restore window if needed
	if( !mShown )
	{
		SDL_ShowWindow( mWindow );
	}

	//Move window forward
	SDL_RaiseWindow( mWindow );
}

void LWindow::LWFillScreen()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
}

void LWindow::LWRenderPresent()
{
    SDL_RenderPresent( mRenderer );
}


void LWindow::free()
{
	if( mWindow != NULL )
	{
		SDL_DestroyWindow( mWindow );
	}

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

int LWindow::getWidth()
{
	return mWidth;
}

int LWindow::getHeight()
{
	return mHeight;
}

bool LWindow::hasMouseFocus()
{
	return mMouseFocus;
}

bool LWindow::hasKeyboardFocus()
{
	return mKeyboardFocus;
}

bool LWindow::isMinimized()
{
	return mMinimized;
}

bool LWindow::isShown()
{
	return mShown;
}

SDL_Renderer* LWindow::getRenderer()
{
    return mRenderer;
}
SDL_Window* LWindow::getWindow() { 
    return mWindow;
};
 #endif
