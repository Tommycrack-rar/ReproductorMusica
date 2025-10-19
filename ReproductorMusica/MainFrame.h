#pragma once
#include <wx/wx.h>
#include <SFML/Audio.hpp>

//Declaracion de la clase MainFrame que hereda de wxFrame

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
private:

	/*Definicion de variables de audio*/

	bool f;
	sf::Music song;
	sf::Time time;
	int songTime;

	//Definicion del temporizador para actualizar la barra de progreso

	wxTimer* timer;

	/*Definicion de controladores de wxFrame
	Botones de pausa, anterior y siguiente
	Sliders de volumen y barra de reproduccion*/

	wxBitmapButton* play;
	wxBitmapButton* next;
	wxBitmapButton* prev;

	wxSlider* progressBar;
	wxSlider* volume;

	/*Definicion de variables de control
	Valor de barra de progreso
	Valor del volumen*/

	int barProgress;
	int volumeVal;

	/*Definicion de controladores de eventos para los controladores definidos*/

	void OnPausingButton(wxCommandEvent& evt); 
	void OnPreviousButton(wxCommandEvent& evt);
	void OnChangedVolBar(wxCommandEvent& evt);
	void OnChangedProgBar(wxCommandEvent& evt);
	void OnTimer(wxTimerEvent& evt);

};
