#include <iostream>
#include "app_window.h"

#define NUM_RECTS 3

AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   _markx = 0;
   _marky = 0;
   _markx_prev = 0;
   _marky_prev = 0;
   addMenuEntry ( "Option 0", evOption0 );
   addMenuEntry ( "Option 1", evOption1 );
   f = Field(4);
   f.initialize();   
 }

// mouse events are in window coordinates, but your scene is in [0,1]x[0,1],
// so make here the conversion when needed
void AppWindow::windowToScene ( float& x, float &y )
 {
   x = (2.0f*(x/float(_w))) - 1.0f;
   y = 1.0f - (2.0f*(y/float(_h)));
 }

// Called every time there is a window event
void AppWindow::handle ( const Event& e )
 {
   bool rd=true;

   if ( e.type==Keyboard ){ 
    switch ( e.key )
    { case ' ': // space bar
        std::cout << "Space pressed.\n";
            _markx = 1.5;
            _marky = 1.5;
            redraw();
        break;
    case 27: // Esc was pressed
        exit(1);
        break;
     }
    }
   if ( e.type==Menu )
    { std::cout<<"Menu Event: "<<e.menuev<<std::endl;
      rd=false; // no need to redraw
    }

   if ( e.type==SpecialKey ){
    switch ( e.key )
    { case GLUT_KEY_LEFT:  
		f.move(LEFT);	
	break;
	case GLUT_KEY_RIGHT: 
		f.move(RIGHT); 
	break;
	case GLUT_KEY_UP:    
		f.move(UP);
	break; 
	case GLUT_KEY_DOWN:
		f.move(DOWN);
		break;
      	default: rd=false; // no redraw
		redraw();
        break;
    case 27: // Esc was pressed
        exit(1);
        break;
     }
    }
   if ( e.type==Menu )
    { std::cout<<"Menu Event: "<<e.menuev<<std::endl;
      rd=false; // no need to redraw
    }
   if (rd) redraw(); // ask the window to be rendered when possible
}

void AppWindow::resize ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }

// here we will redraw the scene according to the current state of the application.
void AppWindow::draw ()
 {
   // Clear the rendering window
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // Clear the trasnformation stack
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();
   f.draw();
   // Set drawing color to yellow
   // Swap buffers
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the fron

}
