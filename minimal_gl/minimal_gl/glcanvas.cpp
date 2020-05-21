#include "glcanvas.h"

BEGIN_EVENT_TABLE(wxGLCanvasSubClass, wxGLCanvas)
EVT_PAINT(wxGLCanvasSubClass::Paintit)
END_EVENT_TABLE()

wxGLCanvasSubClass::wxGLCanvasSubClass(wxFrame *parent, int* args)
	:wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas")) {

	m_context = new wxGLContext(this);

}


wxGLCanvasSubClass::~wxGLCanvasSubClass()
{
	delete m_context;
}

void wxGLCanvasSubClass::Paintit(wxPaintEvent& WXUNUSED(event)) {
	Render();
}

void wxGLCanvasSubClass::Render()
{
	// if (!IsShown()) return;

	SetCurrent(*m_context);
	wxPaintDC(this);
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	// glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);

	 // ------------- draw some 2D ----------------
	prepare2DViewport(0, 0, getWidth() / 2, getHeight());
	glLoadIdentity();

	/*glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glColor3f(0.4, 0.5, 0.4);
	glVertex2f(0.0, -0.8);
	glEnd();*/

	glColor4f(1, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(getWidth() / 8, getHeight() / 3, 0);
	glVertex3f(getWidth() * 3 / 8, getHeight() / 3, 0);
	glVertex3f(getWidth() * 3 / 8, getHeight() * 2 / 3, 0);
	glVertex3f(getWidth() / 8, getHeight() * 2 / 3, 0);
	glEnd();



	

	glFlush();
	SwapBuffers();
}

/** Inits the OpenGL viewport for drawing in 2D. */
void wxGLCanvasSubClass::prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
	glEnable(GL_TEXTURE_2D);   // textures
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(topleft_x, topleft_y, bottomrigth_x - topleft_x, bottomrigth_y - topleft_y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(topleft_x, bottomrigth_x, bottomrigth_y, topleft_y);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void wxGLCanvasSubClass::resized(wxSizeEvent& evt)
{
	//	wxGLCanvas::OnSize(evt);

	Refresh();
}


int wxGLCanvasSubClass::getWidth()
{
	return GetSize().x;
}

int wxGLCanvasSubClass::getHeight()
{
	return GetSize().y;
}
