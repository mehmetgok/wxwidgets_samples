#pragma once

#include <wx/wx.h>
#include <wx/glcanvas.h>

#ifndef WIN32
#include <unistd.h> // FIXME: ¿This work/necessary in Windows?
//Not necessary, but if it was, it needs to be replaced by process.h AND io.h
#endif

class wxGLCanvasSubClass : public wxGLCanvas {
	void Render();
public:
	wxGLContext*	m_context;
	wxGLCanvasSubClass(wxFrame* parent, int* args);
	void Paintit(wxPaintEvent& event);
protected:
	DECLARE_EVENT_TABLE()
};