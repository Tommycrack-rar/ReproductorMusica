/**
 * @file App.h
 * @author JOHAN MUÑOZ (johmunozma@unal.edu.co) and TOMAS SUAREZ()
 * @brief Clase principal de la aplicación wxWidgets - Punto de entrada del reproductor de música
 * @version 0.1
 * @date 2025-10-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <wx/wx.h>

//Declaracion de la clase App que hereda de wxApp
/**
 * @brief Clase principal de la aplicación que hereda de wxApp
 * 
 * Esta clase representa la aplicación wxWidgets y sirve como punto de entrada.
 * Se encarga de inicializar el framework wxWidgets y crear la ventana principal
 * de la aplicación.
 * 
 * @see wxApp
 */
class App : public wxApp
{
public:
	/**
     * @brief Método de inicialización de la aplicación
     * 
     * Este método es llamado automáticamente por wxWidgets cuando la aplicación
     * comienza. Se sobreescribe para proporcionar la inicialización personalizada
     * de la aplicación.
     * 
     * Responsabilidades:
     * - Crear y mostrar la ventana principal (MainFrame)
     * - Inicializar recursos de la aplicación
     * - Establecer el loop principal de eventos
     * 
     * @return true Si la inicialización fue exitosa
     * @return false Si hubo un error en la inicialización (la aplicación terminará)
     * 
     * @note Este método es el punto de entrada equivalente a main() en aplicaciones wxWidgets
     */
	virtual bool OnInit() override; //Declaracion del metodo OnInit que se sobreescribe y se ejecuta al iniciar la aplicacion
};

