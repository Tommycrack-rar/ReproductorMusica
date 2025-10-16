#pragma once
#include <wx/wx.h>
#include <SFML/Audio.hpp>

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
private:

	bool f = 1;
	sf::Music song;
	sf::Time time;
	float songTime;

	wxBitmapButton* play;
	wxBitmapButton* next;
	wxBitmapButton* prev;

	wxSlider* progressBar;
	wxSlider* volume;

	int barProgress;
	int volumeVal;

	void OnPausingButton(wxCommandEvent& evt); 
	void OnPreviousButton(wxCommandEvent& evt);
	void OnChangedVolBar(wxCommandEvent& evt);
	void OnChangedProgBar(wxCommandEvent& evt);
};

