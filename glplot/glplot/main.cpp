// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "frmMain.h"
#include "glcanvas.h"

class MinimalGL : public wxApp
{
public:
	wxGLCanvas * MyGLCanvas;
	virtual bool OnInit();
};

wxIMPLEMENT_APP(MinimalGL);

bool MinimalGL::OnInit()
{
	int args[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0 };

	frmMain *frame = new frmMain("Hello World", wxPoint(50, 50), wxSize(450, 340));
	MyGLCanvas = new wxGLCanvasSubClass((wxFrame* )frame, args);
	frame->Show(true);

	return true;
}

