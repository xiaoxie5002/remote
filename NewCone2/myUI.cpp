#include "myUI.h"
GLUI *glui;
extern  char *windowName[];
extern int winID[5]; // window id
void GLUI_INITs()
{
	// float version = GLUI_Master.get_version();
	glui = GLUI_Master.create_glui("DEVELOP",winID[0]);
	glui->set_main_gfx_window(winID[0]);
	//glui->create_subwindow(winID[0], GLUI_SUBWINDOW_TOP);
	glui->add_button("Cone", 0);
	glui->add_button("Cylinder", 1);
	glui->add_button("Torus", 2);
}
void control_cb( int control )
{
	//if(control == BUTTON_OPEN_TO_PANEL_ID)
	{
	}
}