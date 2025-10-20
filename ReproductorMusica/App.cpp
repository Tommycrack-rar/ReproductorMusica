/**
 * @file App.cpp
  * @author JOHAN MUÑOZ (johmunozma@unal.edu.co) and TOMAS SUAREZ()
 * @brief Implementación de la clase App - Punto de entrada de la aplicación
 * @version 0.1
 * @date 2025-10-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#define _CRT_SECURE_NO_WARNINGS
#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

//Definicion del metodo OnInit que se ejecuta al iniciar la aplicacion
/**
 * @brief Macro que implementa la aplicación wxWidgets
 * 
 * Este macro es esencial para aplicaciones wxWidgets y realiza las siguientes funciones:
 * - Crea el punto de entrada main() para la aplicación
 * - Inicializa el sistema wxWidgets
 * - Crea una instancia de la clase App
 * - Establece el loop principal de eventos
 * 
 * @note Este macro debe aparecer exactamente una vez en toda la aplicación
 */
wxIMPLEMENT_APP(App);//Llamada al macro que implementa la aplicacion

/**
 * @brief Implementación del método de inicialización de la aplicación
 * 
 * Este método es llamado automáticamente después de que wxWidgets haya inicializado
 * sus sistemas internos. Aquí se crea y configura la ventana principal de la aplicación.
 * 
 * Flujo de ejecución:
 * 1. Crea la ventana principal (MainFrame) con el título "REPRODUCTOR"
 * 2. Establece el tamaño del área cliente a 900x600 píxeles
 * 3. Centra la ventana en la pantalla
 * 4. Hace visible la ventana
 * 5. Retorna true para indicar éxito en la inicialización
 * 
 * @return true La inicialización fue exitosa y la aplicación puede continuar
 * @return false La inicialización falló y la aplicación terminará
 * 
 * @see MainFrame
 * @note El tamaño 900x600 se refiere al área cliente (excluyendo bordes y barra de título)
 */
bool App::OnInit() {
	/**
     * @brief Crea la ventana principal de la aplicación
     * 
     * Instancia un objeto MainFrame que servirá como ventana principal
     * del reproductor de música.
     * 
     * @param "REPRODUCTOR" Título que aparecerá en la barra de título de la ventana
     */
	MainFrame* mainFrame = new MainFrame("REPRODUCTOR"); //Definicion del objeto mainFrame de la clase MainFrame
	
	/**
     * @brief Establece el tamaño del área cliente de la ventana
     * 
     * El área cliente es la parte de la ventana que excluye bordes, 
     * barra de título y barras de scroll. 900x600 píxeles proporciona
     * un espacio adecuado para los controles del reproductor.
     */
	mainFrame->SetClientSize(900, 600); //Establece el tamano del cliente de la ventana principal
	
	/**
     * @brief Centra la ventana en la pantalla principal
     * 
     * Calcula automáticamente la posición para que la ventana
     * aparezca centrada en el monitor primario.
     */
	mainFrame->Center(); //Centra la ventana en la pantalla

	 /**
     * @brief Hace visible la ventana principal
     * 
     * @param true Hace la ventana visible y permite la interacción del usuario
     */
	mainFrame->Show(true); //Muestra la ventana principal

	/**
     * @brief Indica que la inicialización fue exitosa
     * 
     * Retornar true permite que la aplicación continúe con la ejecución
     * y entre en el loop principal de eventos de wxWidgets.
     */
	return true; //Retorna true para indicar que la inicializacion fue exitosa
}
