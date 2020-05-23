#include "wx/spinctrl.h"

#include "thread.h"

class MyFrame : public wxFrame
{
	wxSpinCtrl* m_spinner;

public:

	MyFrame() : wxFrame(NULL, wxID_ANY, wxT("Hello wxWidgets"), wxPoint(50, 50), wxSize(800, 600))
	{
		wxPanel* panel = new wxPanel(this);

		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		m_spinner = new wxSpinCtrl(panel);
		m_spinner->SetMax(10000);

		sizer->Add(m_spinner);
		panel->SetSizer(sizer);

		
	}

	// this is called when the event from the thread is received
	void onNumberUpdate(wxCommandEvent& evt)
	{
		// get the number sent along the event and use it to update the GUI
		m_spinner->SetValue(evt.GetInt());
	}

	DECLARE_EVENT_TABLE()
};

// catch the event from the thread
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_COMMAND(NUMBER_UPDATE_ID, wxEVT_COMMAND_TEXT_UPDATED, MyFrame::onNumberUpdate)
END_EVENT_TABLE()


class MyApp : public wxApp
{
	wxFrame* m_frame;
public:

	bool OnInit()
	{
		m_frame = new MyFrame();
		m_frame->Show();

		// create the thread
		MyThread* t = new MyThread(m_frame);
		wxThreadError err = t->Create();

		if (err != wxTHREAD_NO_ERROR)
		{
			wxMessageBox(_("Couldn't create thread!"));
			return false;
		}

		err = t->Run();

		if (err != wxTHREAD_NO_ERROR)
		{
			wxMessageBox(_("Couldn't run thread!"));
			return false;
		}

		return true;
	}

};

IMPLEMENT_APP(MyApp)