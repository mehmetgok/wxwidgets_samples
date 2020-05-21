#pragma once

#include <wx/wx.h>
#include <wx/glcanvas.h>


// include OpenGL
#ifdef __WXMAC__
#include "OpenGL/glu.h"
#include "OpenGL/gl.h"
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#ifndef WIN32
#include <unistd.h> // FIXME: ¿This work/necessary in Windows?
//Not necessary, but if it was, it needs to be replaced by process.h AND io.h
#endif

class wxGLCanvasSubClass : public wxGLCanvas {
	void Render();
public:
	wxGLContext*	m_context;
	
	wxGLCanvasSubClass(wxFrame* parent, int* args);
	virtual ~wxGLCanvasSubClass();

	void resized(wxSizeEvent& evt);

	void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);

	
	int getWidth();
	int getHeight();


	void Paintit(wxPaintEvent& event);
protected:
	DECLARE_EVENT_TABLE()
};