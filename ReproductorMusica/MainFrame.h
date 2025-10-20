/**
 * @file MainFrame.h
 * @author 
 * @brief Clase principal que representa la ventana del reproductor de música
 * @version 0.1
 * @date 2025-10-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */
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
/**
 * @brief Clase principal que representa la ventana del reproductor de música
 * 
 * Hereda de wxFrame y gestiona la interfaz gráfica y funcionalidad del reproductor
 */
class MainFrame : public wxFrame {
public:
	/**
     * @brief Constructor de MainFrame
     * @param title Título de la ventana
     */	
	MainFrame(const wxString& title);
private:

	
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

	//Estos son los controladores de los eventos
	
	
    /**
     * @brief Maneja el evento del botón de playlist
     * @param evt Evento de comando
     */
	void OnPlaylistButton(wxCommandEvent& evt);
	
	/**
     * @brief Maneja el evento del botón de historial
     * @param evt Evento de comando
     */
	void OnHistoryButton(wxCommandEvent& evt);
	
	/**
     * @brief Maneja el evento del botón de Pausa
     * @param evt Evento de comando
     */
	void OnPausingButton(wxCommandEvent& evt); 
	
	/**
     * @brief Maneja el evento del botón de Previo
     * @param evt Evento de comando
     */
	void OnPreviousButton(wxCommandEvent& evt);

	/**
     * @brief Maneja el evento del botón de next
     * @param evt Evento de comando
     */
	void OnNextButton(wxCommandEvent& evt);

	/**
     * @brief Maneja el evento del cambio en la barra de volumen
     * @param evt Evento de comando
     */
	void OnChangedVolBar(wxCommandEvent& evt);
	
	/**
     * @brief Maneja el evento del cambio en la barra del progreso
     * @param evt Evento de comando
     */
	void OnChangedProgBar(wxCommandEvent& evt);

	/**
     * @brief Maneja el evento al clickear en una cancion
     * @param evt Evento de comando
     */
	void OnClickedSongs(wxCommandEvent& evt);

	/**
     * @brief Maneja el evento del temporizador y actualiza en la UI
     * @param evt Evento de temporizador
     */
	void OnTimer(wxTimerEvent& evt);
	
};
