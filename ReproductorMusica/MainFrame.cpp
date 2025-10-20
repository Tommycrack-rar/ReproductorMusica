#define _CRT_SECURE_NO_WARNINGS
#include "MainFrame.h"
#include<iostream>
#include<wx/wx.h>
#include<wx/statline.h>
#include<SFML/Audio.hpp>

using namespace std;
namespace fs = std::filesystem;

//Definicion de la clase MainFrame

MainFrame::MainFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {


	/* Creacion del panel principal de la ventana
	   Y cambio de color con codigo RGB*/

	wxPanel* panel = new wxPanel(this);

	//

	std::string path_string = "resources/songs";

	try {
		for (const auto& entry : fs::directory_iterator(path_string)) {
			if (fs::is_regular_file(entry.status())) {
				searcherArray.push_back(entry.path().filename().stem().string());
			}
		}
	}
	catch (const fs::filesystem_error& e) {
		// Handle potential errors, e.g., directory not found
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// Carga de la cancion y guarda su duracion en segundos

	wxImage::AddHandler(new wxPNGHandler); //Inicializa el manejador de imagenes PNG
	wxBitmap pauseBmp("resources/pause.png", wxBITMAP_TYPE_PNG); //Define el bitmap del boton de pausa

	//Creacion de los elementos de la interfaz grafica

	repertory = new wxListBox(panel, wxID_ANY, wxPoint(20, 50), wxSize(530, 360), searcherArray);//Canciones a elegir en forma de ListBox
	playlist = new wxListBox(panel, wxID_ANY, wxPoint(580, 50), wxSize(300, 360));
	history = new wxListBox(panel, wxID_ANY, wxPoint(580, 50), wxSize(300, 360));
	history->Show(false);

	c = true;
	p = false;

	wxStaticLine* separator = new wxStaticLine(panel, wxID_ANY, wxPoint(20, 430), wxSize(860, -1)); //Linea separadora

	songText = new wxStaticText(panel, wxID_ANY, "Song - Artist", wxPoint(300, 440), wxSize(300, 25), wxALIGN_CENTRE_HORIZONTAL); //Titulo y artista de la cancion actual
	songProgress = new wxStaticText(panel, wxID_ANY, "0:00", wxPoint(150, 540), wxSize(600, 25), wxALIGN_CENTRE_HORIZONTAL); //Duracion de la cancion

	//Definiion de los botones de historial y fila de reproduccion

	playlistButton = new wxButton(panel, wxID_ANY, "Playlist", wxPoint(580, 25), wxSize(130, 25));
	historyButton = new wxButton(panel, wxID_ANY, "Historial", wxPoint(750, 25), wxSize(130, 25));

	/*Definicion de los botones de control de reproduccion
	  Cambio de color de sus fondos*/
	play = new wxBitmapButton(panel, wxID_ANY, wxBitmap("resources/play.png", wxBITMAP_TYPE_PNG), wxPoint(430, 465), wxSize(40, 40), wxBORDER_NONE);
	prev = new wxBitmapButton(panel, wxID_ANY, wxBitmap("resources/previous.png", wxBITMAP_TYPE_PNG), wxPoint(200, 465), wxSize(40, 40), wxBORDER_NONE);
	next = new wxBitmapButton(panel, wxID_ANY, wxBitmap("resources/next.png", wxBITMAP_TYPE_PNG), wxPoint(660, 465), wxSize(40, 40), wxBORDER_NONE);

	//Definicion de los sliders de volumen y barra de reproduccion

	progressBar = new wxSlider(panel, wxID_ANY, 0, 0, 100, wxPoint(200, 510), wxSize(500, 100));
	volume = new wxSlider(panel, wxID_ANY, 100, 0, 100, wxPoint(70, 480), wxSize(20, 70), wxSL_VERTICAL | wxSL_VALUE_LABEL | wxSL_INVERSE);

	f = true;
	barProgress = 0;

	//Vinculacion de los elementos de la interfaz a sus controladores de eventos

	play->Bind(wxEVT_BUTTON, &MainFrame::OnPausingButton, this);
	prev->Bind(wxEVT_BUTTON, &MainFrame::OnPreviousButton, this);
	next->Bind(wxEVT_BUTTON, &MainFrame::OnNextButton, this);
	playlistButton->Bind(wxEVT_BUTTON, &MainFrame::OnPlaylistButton, this);
	historyButton->Bind(wxEVT_BUTTON, &MainFrame::OnHistoryButton, this);

	volume->Bind(wxEVT_SLIDER, &MainFrame::OnChangedVolBar, this);
	progressBar->Bind(wxEVT_SLIDER, &MainFrame::OnChangedProgBar, this);

	repertory->Bind(wxEVT_LISTBOX, &MainFrame::OnClickedSongs, this);

	timer = new wxTimer(this, wxID_ANY);
	Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);

	CreateStatusBar();
}

//Definicion del controlador de eventos para el boton de playlist

void MainFrame::OnPlaylistButton(wxCommandEvent& evt) {
	if (p) {
		playlist->Show(true);
		history->Show(false);
		p = !p;
	};
}

//Definicion del controlador de eventos para el boton de historial

void MainFrame::OnHistoryButton(wxCommandEvent& evt) {
	if (!p) {
		playlist->Show(false);
		history->Show(true);
		p = !p;
	};
}

//Definicion del controlador de eventos para el boton de pausa/reproduccion

void MainFrame::OnPausingButton(wxCommandEvent& evt) {
	if (f) {
		wxLogStatus("Playing");
		play->SetBitmap(wxBitmap("resources/pause.png", wxBITMAP_TYPE_PNG));
		timer->Start(250);
		sfSong.play();
		barProgress = progressBar->GetValue();
		f = false;
	}
	else {
		wxLogStatus("Paused");
		play->SetBitmap(wxBitmap("resources/play.png", wxBITMAP_TYPE_PNG));
		sfSong.pause();
		timer->Stop();
		f = true;
	};
}

//Definicion del controlador de eventos para el boton de retroceso

void MainFrame::OnPreviousButton(wxCommandEvent& evt) {
	if (currentTime <= 2) {
		playlistQueue.front() = historyStack.top();
		historyStack.pop();

		sfSong.openFromFile("resources/songs/" + playlistQueue.front() + ".wav");
		songText->SetLabel(playlistQueue.front());

		play->SetBitmap(wxBitmap("resources/pause.png", wxBITMAP_TYPE_PNG));

		time = sfSong.getDuration();
		songSeconds = time.asSeconds();
		progressBar->SetRange(0, songSeconds);
		progressBar->SetValue(0);
		barProgress = 0;

		sfSong.stop();
		sfSong.play();
	}
	else {
		wxLogStatus("Rewinded");
		play->SetBitmap(wxBitmap("resources/play.png", wxBITMAP_TYPE_PNG));
		sfSong.pause();
		timer->Stop();
		progressBar->SetValue(0);
		barProgress = 0;
		songProgress->SetLabel("0:00");
		f = true;

	};
}

//Definicion del controlador de eventos para el boton de siguiente

void MainFrame::OnNextButton(wxCommandEvent& evt) {
	if (playlistQueue.size() > 1) {
		
		historyStack.push(playlistQueue.front());
		history->Insert(wxString(playlistQueue.front()), 0);
		history->Refresh();
		history->Update();

		if (history->GetCount() > 23) {
			history->Delete(history->GetCount() - 1);
		};

		playlistQueue.pop();
		playlist->Delete(0);

		sfSong.openFromFile("resources/songs/" + playlistQueue.front() + ".wav");
		songText->SetLabel(playlistQueue.front());

		play->SetBitmap(wxBitmap("resources/pause.png", wxBITMAP_TYPE_PNG));

		time = sfSong.getDuration();
		songSeconds = time.asSeconds();
		progressBar->SetRange(0, songSeconds);
		progressBar->SetValue(0);
		barProgress = 0;
		songProgress->SetLabel("0:00");

		sfSong.stop();
		sfSong.play();
		timer->Start(250);
	}
}

//Definicion del controlador de eventos para el slider de volumen

void MainFrame::OnChangedVolBar(wxCommandEvent& evt) {
	volumeVal = volume->GetValue();
	sfSong.setVolume(volumeVal);
}

//Definicion del controlador de eventos para la barra de reproduccion

void MainFrame::OnChangedProgBar(wxCommandEvent& evt) {
	barProgress = progressBar->GetValue();
	sfSong.setPlayingOffset(sf::seconds(barProgress));
}

//Definicion del controlador de eventos para el temporizador

void MainFrame::OnTimer(wxTimerEvent& evt) {
	wxLogStatus("Playing...");
	currentTime = sfSong.getPlayingOffset().asSeconds();
	progressBar->SetValue(static_cast<int>(currentTime));
	songMinutes = static_cast<int>(currentTime) / 60;
	songProgress->SetLabel(wxString::Format("%d:%02d", songMinutes, static_cast<int>(currentTime) % 60));

	if (currentTime >= songSeconds) {
		historyStack.push(playlistQueue.front());
		history->Insert(wxString(playlistQueue.front()), 0);
		history->Refresh();
		history->Update();
		if (!playlistQueue.empty()) {
			if (playlistQueue.size() > 1) {

				playlistQueue.pop();
				playlist->Delete(0);

				sfSong.openFromFile("resources/songs/" + playlistQueue.front() + ".wav");
				songText->SetLabel(playlistQueue.front());

				play->SetBitmap(wxBitmap("resources/pause.png", wxBITMAP_TYPE_PNG));

				time = sfSong.getDuration();
				songSeconds = time.asSeconds();
				progressBar->SetRange(0, songSeconds);
				progressBar->SetValue(0);
				barProgress = 0;

				sfSong.stop();
				sfSong.play();
				timer->Start(250);
			}
			else {
				sfSong.stop();
				timer->Stop();
				play->SetBitmap(wxBitmap("resources/play.png", wxBITMAP_TYPE_PNG));
				progressBar->SetValue(0);
				barProgress = 0;
				f = true;
			};
		};
		if (history->GetCount() > 23){
			history->Delete(history->GetCount() - 1);
		};
	};
}


//Definicion del controlador de eventos para la seleccion de canciones para iniciar la playlist
void MainFrame::OnClickedSongs(wxCommandEvent& evt) { 
	wxLogStatus("Selected");
	
	playlistQueue.push(searcherArray[repertory->GetSelection()]);
	playlist->Append(searcherArray[repertory->GetSelection()]);

	if (c) {
		sfSong.openFromFile("resources/songs/" + searcherArray[repertory->GetSelection()] + ".wav");
		songText->SetLabel(searcherArray[repertory->GetSelection()]);

		play->SetBitmap(wxBitmap("resources/pause.png", wxBITMAP_TYPE_PNG));

		time = sfSong.getDuration();
		songSeconds = time.asSeconds();
		progressBar->SetRange(0, songSeconds);
		progressBar->SetValue(0);
		barProgress = 0;
		
		sfSong.stop();
		sfSong.play();
		timer->Start(250);
		c = false;
	}
	f = false;
}

