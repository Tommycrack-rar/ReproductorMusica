#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);//Llamada al macro que implementa la aplicacion

//Definicion del metodo OnInit que se ejecuta al iniciar la aplicacion

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("REPRODUCTOR"); //Definicion del objeto mainFrame de la clase MainFrame
	mainFrame->SetClientSize(900, 600); //Establece el tamano del cliente de la ventana principal
	mainFrame->Center(); //Centra la ventana en la pantalla
	mainFrame->Show(true); //Muestra la ventana principal
	return true; //Retorna true para indicar que la inicializacion fue exitosa
}
