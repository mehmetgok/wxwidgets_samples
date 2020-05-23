#include "thread.h"

wxThread::ExitCode MyThread::Entry()
{
	int n=0;

	for (;;)
	{
		this->Sleep(50);

		// notify the main thread
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, NUMBER_UPDATE_ID);
		event.SetInt(n);  // pass some data along the event, a number in this case
		m_parent->GetEventHandler()->AddPendingEvent(event);

		n++;
	}
	return 0;
}