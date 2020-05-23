#ifndef _THREAD_H_
#define _THREAD_H_

#include "wx/wx.h"

// the ID we'll use to identify our event
const int NUMBER_UPDATE_ID = 100000;

// a thread class that will periodically send events to the GUI thread
class MyThread : public wxThread
{
	wxFrame* m_parent;
public:
	MyThread(wxFrame* parent)
	{
		m_parent = parent;
	}

	virtual ExitCode Entry();
};

#endif