#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <wx/wx.h>

//Declaracion de la clase App que hereda de wxApp

class App : public wxApp
{
public:
	virtual bool OnInit() override; //Declaracion del metodo OnInit que se sobreescribe y se ejecuta al iniciar la aplicacion
};

