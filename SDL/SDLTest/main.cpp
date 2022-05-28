// specific headers
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
// main io header
#include <iostream>
// start of the program
int main(int argc,char* args[])
{
    // initialise SDL everything in it
    SDL_Init(SDL_INIT_EVERYTHING);

    // Assign OpenGL memory usage
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8 );
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32 );
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1 );

    // The Window Caption
    SDL_WM_SetCaption("SDLTest", NULL );

    // set the window size
    SDL_SetVideoMode(600,400,32,SDL_OPENGL );
    // SDL_SetVideoMode( PixelsWide , PixelsHigh , NumberColours , SDL_OPENGL | SDL_FULLSCREEN );
    // Most games will run at 60 frames per second
    // glClearColor(RED,GREEN,BLUE,ALPHA);
    // glViewPort(UpperX,UpperY,LowerX,LowerY);
    // Clear to a white screen
    // setting the clear color
    glClearColor(1,1,1,1);

    // What portion of the screen are we using
    glViewport(0,0,600,400);
    // set the gradient to smooth
    glShadeModel(GL_SMOOTH);
    // set it to 2d
    glMatrixMode(GL_PROJECTION);
    // save everything
    glLoadIdentity();
    // disable 3d functions
    glDisable(GL_DEPTH_TEST);
    std::cout << "OpenGL is running\n";
    std::cout << "Main Loop has started\n";
    // this handles the main loop
    bool isRunning =true;
    // this handles the evens
    SDL_Event event;
    // main game loop
    while (isRunning)
    {
        // EVENTS
        while(SDL_PollEvent(&event))
        {
            //Logic that should happen for a certain event
            // has the close crooss been pressed
            if ( event.type==SDL_QUIT)
            {
                isRunning = false;
            }
            // if a key is released and the key is escape
            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
        }
        // LOGIC
        // RENDER to SCREEN
        glClear(GL_COLOR_BUFFER_BIT);
        // Start phase of rendering
        glPushMatrix();
        // we set the matric to match our window size
        glOrtho(0,600,400,0,-1,1);
        glColor4ub(255,0,0,255); //red
        // draw a line
        glBegin(GL_LINES);
        glVertex2f(0,0);        //top left corner
        glVertex2f(600,400);    //bottom right corner
        glEnd();

        // draw a quad
        glBegin(GL_QUADS);
        glVertex2f(5,5);        //top left corner
        glVertex2f(595,5);    //bottom right corner
        glColor4ub(0,255,0,255); //red
        glVertex2f(595,395);        //top left corner
        glVertex2f(5,395);    //bottom right corner
        glEnd();

        glBegin(GL_LINES);
        glColor4ub(0,0,0,255); //black
        glVertex2f(5,5);        //top left corner
        glVertex2f(595,395);        //top left corner
        glEnd();

                glBegin(GL_LINES);
        glColor4ub(0,0,0,255); //black
        glVertex2f(595,5);        //top left corner
        glVertex2f(5,395);        //top left corner
        glEnd();
        //GL_POINTS plot a point
        //GL_LINES draw a line
        //GL_LINE_STRIP
        //GL_LINE_LOOP
        //GL_QUADS - quadrangle
        //GL_TRIANGLE
        //GL_POLYGON

        // End phase of rendering
        glPopMatrix();
        SDL_GL_SwapBuffers();
    }
    std::cout << "Main Loop has finished\n";
    // delay for 5 second
    // SDL_Delay(5000);
    SDL_Quit();
    return 0;
}
