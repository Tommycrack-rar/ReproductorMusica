#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/statline.h>
#include <SFML/Audio.hpp>

//Definicion de la clase MainFrame

MainFrame::MainFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(-1, -1)) {

	/* Creacion del panel principal de la ventana
	   Y cambio de color con codigo RGB*/

	wxPanel* panel = new wxPanel(this);
	panel->SetBackgroundColour(wxColour(233, 72, 13));

	// Creacion de la playlist en forma de cola (por cambiar)

	wxArrayString playlistArr;
	playlistArr.Add("Song 1");
	playlistArr.Add("Song 2");
	playlistArr.Add("Song 3");

	// Carga de la cancion y guarda su duracion en segundos

	song.openFromFile("Whiplash.wav");
	time = song.getDuration();
	songTime = time.asSeconds();

	wxImage::AddHandler(new wxPNGHandler); //Inicializa el manejador de imagenes PNG
	wxBitmap pauseBmp("resources/pause.png", wxBITMAP_TYPE_PNG); //Define el bitmap del boton de pausa

	//Creacion de los elementos de la interfaz grafica

	wxListBox* playlist = new wxListBox(panel, wxID_ANY, wxPoint(20, 20), wxSize(860, 360), playlistArr);//Playlist en forma de ListBox

	wxStaticLine* separator = new wxStaticLine(panel, wxID_ANY, wxPoint(20, 400), wxSize(860, -1)); //Linea separadora

	wxStaticText* songText = new wxStaticText(panel, wxID_ANY, "Song - Artist", wxPoint(300, 430), wxSize(300, 25), wxALIGN_CENTRE_HORIZONTAL); //Titulo y artista de la cancion actual
	wxStaticText* progress = new wxStaticText(panel, wxID_ANY, "0:00", wxPoint(300, 540), wxSize(300, 25), wxALIGN_CENTRE_HORIZONTAL); //Duracion de la cancion

	/*Definicion de los botones de control de reproduccion
	  Cambio de color de sus fondos*/
	play = new wxBitmapButton(panel, wxID_ANY, wxBitmap("resources/play.png", wxBITMAP_TYPE_PNG), wxPoint(430, 455), wxSize(40, 40), wxBORDER_NONE);
	prev = new wxBitmapButton(panel, wxID_ANY, wxBitmap("resources/previous.png", wxBITMAP_TYPE_PNG), wxPoint(200, 455), wxSize(40, 40), wxBORDER_NONE);
	next = new wxBitmapButton(panel, wxID_ANY, wxBitmap("resources/next.png", wxBITMAP_TYPE_PNG), wxPoint(660, 455), wxSize(40, 40), wxBORDER_NONE);

	play->SetBackgroundColour(wxColour(233, 72, 13));
	prev->SetBackgroundColour(wxColour(233, 72, 13));
	next->SetBackgroundColour(wxColour(233, 72, 13));;

	//Definicion de los sliders de volumen y barra de reproduccion

	progressBar = new wxSlider(panel, wxID_ANY, 0, 0, static_cast<int>(songTime), wxPoint(200, 510), wxSize(500, 100), wxSL_VALUE_LABEL);
	volume = new wxSlider(panel, wxID_ANY, 100, 0, 100, wxPoint(70, 480), wxSize(20, 70), wxSL_VERTICAL | wxSL_VALUE_LABEL | wxSL_INVERSE);

	f = true;
	barProgress = 0;

	//Vinculacion de los elementos de la interfaz a sus controladores de eventos

	play->Bind(wxEVT_BUTTON, &MainFrame::OnPausingButton, this);
	prev->Bind(wxEVT_BUTTON, &MainFrame::OnPreviousButton, this);
	volume->Bind(wxEVT_SLIDER, &MainFrame::OnChangedVolBar, this);
	progressBar->Bind(wxEVT_SLIDER, &MainFrame::OnChangedProgBar, this);
	CreateStatusBar();

	timer = new wxTimer(this, wxID_ANY);
	Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);
	timer->Start(250);
}

//Definicion del controlador de eventos para el boton de pausa/reproduccion

void MainFrame::OnPausingButton(wxCommandEvent& evt) {
	if (f) {
		play->SetBitmap(wxBitmap("resources/pause.png", wxBITMAP_TYPE_PNG));
		song.play();
		barProgress = progressBar->GetValue();
		f = false;
	}
	else {
		wxLogStatus("Paused");
		play->SetBitmap(wxBitmap("resources/play.png", wxBITMAP_TYPE_PNG));
		song.pause();
		timer->Stop();
		f = true;
	};
}

//Definicion del controlador de eventos para el boton de retroceso

void MainFrame::OnPreviousButton(wxCommandEvent& evt) {
	wxLogStatus("Rewinded");
	song.stop();
	play->SetBitmap(wxBitmap("resources/play.png", wxBITMAP_TYPE_PNG));
	progressBar->SetValue(0);
	barProgress = 0;
	f = true;
}

//Definicion del controlador de eventos para el slider de volumen

void MainFrame::OnChangedVolBar(wxCommandEvent& evt) {
	volumeVal = volume->GetValue();
	song.setVolume(volumeVal);
}

//Definicion del controlador de eventos para la barra de reproduccion

void MainFrame::OnChangedProgBar(wxCommandEvent& evt) {
	barProgress = progressBar->GetValue();
	song.setPlayingOffset(sf::seconds(barProgress));
}

//Definicion del controlador de eventos para el temporizador

void MainFrame::OnTimer(wxTimerEvent& evt) {
	wxLogStatus("Timer tick");
	float current = song.getPlayingOffset().asSeconds();
	progressBar->SetValue(static_cast<int>(current));
}