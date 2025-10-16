#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/statline.h>
#include <SFML/Audio.hpp>

MainFrame::MainFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(-1, -1)) {
	
	wxArrayString playlistArr;
	playlistArr.Add("Song 1");
	playlistArr.Add("Song 2");
	playlistArr.Add("Song 3");

	song.openFromFile("Whiplash.wav");
	time = song.getDuration();
	songTime = time.asSeconds();
	
	wxImage::AddHandler(new wxPNGHandler);

	wxBitmap playBmp("resources/play.png", wxBITMAP_TYPE_PNG);
	wxBitmap pauseBmp("resources/pause.png", wxBITMAP_TYPE_PNG);
	wxBitmap prevBmp("resources/previous.png", wxBITMAP_TYPE_PNG);
	wxBitmap nextBmp("resources/next.png", wxBITMAP_TYPE_PNG);

	wxPanel* panel = new wxPanel(this);

	wxListBox* playlist = new wxListBox(panel, wxID_ANY, wxPoint(20, 20), wxSize(860, 360), playlistArr);

	wxStaticLine* separator = new wxStaticLine(panel, wxID_ANY, wxPoint(20,400), wxSize(860,-1));
	wxStaticText* songText = new wxStaticText(panel, wxID_ANY, "Song - Artist", wxPoint(300,430), wxSize(300, 25), wxALIGN_CENTRE_HORIZONTAL);
	wxStaticText* progress = new wxStaticText(panel, wxID_ANY, "0:00", wxPoint(300, 540), wxSize(300, 25), wxALIGN_CENTRE_HORIZONTAL);

	play = new wxBitmapButton(panel, wxID_ANY, playBmp, wxPoint(430, 455), wxSize(40, 40));
	prev = new wxBitmapButton(panel, wxID_ANY, prevBmp, wxPoint(200, 455), wxSize(40, 40));
	next = new wxBitmapButton(panel, wxID_ANY, nextBmp, wxPoint(660, 455), wxSize(40, 40));

	play->Bind(wxEVT_BUTTON,&MainFrame::OnPausingButton, this);
	prev->Bind(wxEVT_BUTTON, &MainFrame::OnPreviousButton, this);
	CreateStatusBar();

	progressBar = new wxSlider(panel, wxID_ANY, 0, 0, songTime, wxPoint(200,510), wxSize(500,100), wxSL_VALUE_LABEL);
	volume = new wxSlider(panel, wxID_ANY, 100, 0, 100, wxPoint(70,480), wxSize(20, 70), wxSL_VERTICAL | wxSL_VALUE_LABEL | wxSL_INVERSE);

	volume->Bind(wxEVT_SLIDER, &MainFrame::OnChangedVolBar, this);
	progressBar->Bind(wxEVT_SLIDER, &MainFrame::OnChangedProgBar, this);
}

void MainFrame::OnPausingButton(wxCommandEvent& evt){
	if (f) {
		wxLogStatus("Playing");
		play->SetBitmap(wxBitmap("resources/pause.png", wxBITMAP_TYPE_PNG));
		song.play();
		f = !f;
		if (barProgress == 0) {
			progressBar->SetValue(1);
			barProgress = progressBar->GetValue();
		}
	}
	else {
		wxLogStatus("Paused");
		play->SetBitmap(wxBitmap("resources/play.png", wxBITMAP_TYPE_PNG));
		song.pause();
		f = !f;
	};
}

void MainFrame::OnPreviousButton(wxCommandEvent& evt) {
	wxLogStatus("Rewinded");
	song.stop();
	play->SetBitmap(wxBitmap("resources/play.png", wxBITMAP_TYPE_PNG));
	progressBar->SetValue(0);
	barProgress = 0;
	f = !f;
}

void MainFrame::OnChangedVolBar(wxCommandEvent& evt){
	volumeVal = volume->GetValue();
	song.setVolume(volumeVal);
}

void MainFrame::OnChangedProgBar(wxCommandEvent& evt){
	barProgress = progressBar->GetValue();
	song.setPlayingOffset(sf::seconds(barProgress));
}