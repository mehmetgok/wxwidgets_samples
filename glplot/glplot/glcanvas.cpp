#include "glcanvas.h"

BEGIN_EVENT_TABLE(wxGLCanvasSubClass, wxGLCanvas)
    EVT_PAINT(wxGLCanvasSubClass::Paintit)
END_EVENT_TABLE()

wxGLCanvasSubClass::wxGLCanvasSubClass(wxFrame *parent, int* args)
	:wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas")) 
{
	
	m_context = new wxGLContext(this);

	fSineData = (double *)malloc(sizeof(double) * 2000);

	double Fs = 10000.0;
	double Ws = Fs / 2000.0;
	double T = 1.0 / Ws;
	double deger[3600];

	for (int i = 0; i < 3600; i++)
		deger[i] = 100.0 * sin(50.0*2.0*(i/100.0)*M_PI / 180.0) + 100.0;

	int k = 0;

	for (int i = 0; i < 2000; i++)
	{
		int newPos = map(i, 0, 2000, 0, 3600);
		fSineData[k] = deger[newPos];
		k++;
	}



	/*for (int i = 0; i < 2000; i++) {
		
		fSineData[i] = 100.0 * sin(2.0*i*M_PI/180.0) + 100.0;

		
	}*/

}

wxGLCanvasSubClass::~wxGLCanvasSubClass()
{


	delete m_context;

	delete fSineData;
}

void wxGLCanvasSubClass::Paintit(wxPaintEvent& WXUNUSED(event)) 
{
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
	prepare2DViewport( 0, 0, getWidth(), getHeight() );
	//glLoadIdentity();

	glPushAttrib(GL_ENABLE_BIT);

	glColor3f(0.5, 0.4, 0.3);
	glPointSize(1);

	glLineStipple(1, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);

	for (int i = 0; i < 201; i += 10)
	{
		glVertex2f(0, i);
		glVertex2f(2000, i);
	}

	for (int i = 0; i < 2001; i += 200)
	{
		glVertex2f(i, 0);
		glVertex2f(i, 200);
	}

	glEnd();

	glPopAttrib();

	glPointSize(2);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS | GL_LINE_STRIP);
	for (int i = 0; i < 2000; i++)
		// x, y
		glVertex2f((float)i, fSineData[i]);
	glEnd();
	
	glPointSize(2);
	glColor3f(0.0, 1.0, 1.0);

	/*
	glBegin(GL_POINTS | GL_LINE_STRIP);
	for (int i = 0; i < 2000; i++)
		// x, y
		glVertex2f((float)i, fSineData[i] - 20);
	glEnd();
	*/
	
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

	glViewport(5, 0, getWidth()-10, getHeight()-5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// gluOrtho2D(topleft_x, bottomrigth_x, bottomrigth_y, topleft_y);
	gluOrtho2D(-5, 2001, -5, 201);
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

int wxGLCanvasSubClass::map(int x, int in_min, int in_max, int out_min, int out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
