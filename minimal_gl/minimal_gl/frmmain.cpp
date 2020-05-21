#pragma once

#include "frmmain.h"

wxBEGIN_EVENT_TABLE(frmMain, wxFrame)
EVT_MENU(ID_Hello, frmMain::OnHello)
EVT_MENU(wxID_EXIT, frmMain::OnExit)
EVT_MENU(wxID_ABOUT, frmMain::OnAbout)
wxEND_EVENT_TABLE()

frmMain::frmMain(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	
	SetMenuBar(menuBar);
	
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");
}

void frmMain::OnExit(wxCommandEvent& event)
{
	Close(true);
}
void frmMain::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets' Hello world sample",
		"About Hello World", wxOK | wxICON_INFORMATION);
}
void frmMain::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}