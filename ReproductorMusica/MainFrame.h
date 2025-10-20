#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<wx/wx.h>
#include<SFML/Audio.hpp>
using namespace std;


//Declaracion de la clase MainFrame que hereda de wxFrame

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
private:

	/*Definicion de variables de audio*/

	bool f;
	sf::Music sfSong;
	sf::Time time;
	int songSeconds;
	int songMinutes;
	float currentTime;

	//Declararacion de cola, pila y arreglo para la playlist

	bool c;
	queue<string> playlistQueue;
	stack<string> historyStack;
	vector<string> searcherArray;
	vector<string> temporal;
	string currentSong;

	//Definicion del temporizador para actualizar la barra de progreso

	wxTimer* timer;

	/*Definicion de controladores de wxFrame
	Botones de pausa, anterior y siguiente
	Sliders de volumen y barra de reproduccion*/

	bool p;
	wxButton* historyButton;
	wxButton* playlistButton;

	wxBitmapButton* play;
	wxBitmapButton* next;
	wxBitmapButton* prev;

	wxSlider* progressBar;
	wxSlider* volume;

	wxListBox* repertory;
	wxListBox* playlist;
	wxListBox* history;

	wxStaticText* songText;
	wxStaticText* songProgress;

	/*Definicion de variables de control
	Valor de barra de progreso
	Valor del volumen*/

	int barProgress;
	int volumeVal;

	/*Definicion de controladores de eventos para los controladores definidos*/

	void OnPlaylistButton(wxCommandEvent& evt);
	void OnHistoryButton(wxCommandEvent& evt);
	void OnPausingButton(wxCommandEvent& evt); 
	void OnPreviousButton(wxCommandEvent& evt);
	void OnNextButton(wxCommandEvent& evt);

	void OnChangedVolBar(wxCommandEvent& evt);
	void OnChangedProgBar(wxCommandEvent& evt);

	void OnClickedSongs(wxCommandEvent& evt);

	void OnTimer(wxTimerEvent& evt);
	
};
