////////////////////////////////////////////////////////////////////
//	Windows programming: part 1
//
//  The minimum windows program, an "hello world" application.
//	How to: open a window, define a title on the top bar, add an icon,
//	        write something in the window, create a menu
//
//	TO DO:
//	1) understand the code, how to compile and run inside visual studio
//  2) change the title of the main window and the text inside the window
//	3) change position and size of the window
//  4) change the background color of the window
//  5) create an use a newly created icon
//       Resource View -> E1.rc
//       Call it "IDI_ICON1" and modify the "RegistraClasse" routine.
//  6) create a menu with "File -> Exit" and "Help" and show it. Only show it, do not
//     make it working! Call it "IDR_MENU1" and modify the
//		 "RegistraClasse" routine.
//
////////////////////////////////////////////////////////////////////
//	Esercitazione per windows n. 1
//
//	Il minimo: aprire una finestra, inserire il titolo,
//	           inserire una icona, scrivere qualcosa sulla finestra
//
//	Help: premendo il tasto F1 sul nome di una funzione di sistema
//			  appare l'help della funzione (se installato correttamente)
//
//
////	DA FARE:
////  1) capire il codice come è, compilare ed eseguire;
////  2) cambiare il titolo della finestra principale e della scritta;
////  3) cambiare posizione e dimensioni della finestra
////  4) cambiare il colore di sfondo della finestra
////  5) creare una icona ed usarla nella barra del titolo:
////       Resource View -> E1.rc
////  6) creare un menu che abbia "File->Esci" e "Help", chiamarlo "IDR_MENU1" ed
////     associarlo alla finestra del main (vedi "wndclass.lpszMenuName").
////     Non è richiesta la gestione del menù (appare ma i tasti non fanno nulla)

#include <windows.h>

//	Include per usare le "risorse" (icona, menu,...)
//	Include file needed to use the resources (icon, menu, ...)
#include "resource.h"

//	Funzioni usate prima di essere definite
//	Two routines declared before they are defined
LRESULT CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM);
bool RegistraClasse(HINSTANCE hInstance);

//	MAIN routine
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
   HWND hwnd;
   MSG  msg;

	 //	Registrazione finestra / register a window
	 if( !RegistraClasse(hInstance) ) return 1;

	 //	Creazione finestra / create the window
	 // QUI si possono cambiare dimensioni, posizione e titolo, vedi help
	 // HERE: you can change dimensions, position and title of the window (see Help)
	 // i primi due campi identificano la posizione della finestra, immagino in termini di pixel
	 // i secondi due invece identificano lunghezza e altezza della finestra
	 hwnd = CreateWindow ("FinPrincipale", "Titolo Nuovo", WS_OVERLAPPEDWINDOW,
          100, 100, 400, 300, NULL, NULL, hInstance, NULL) ;

   ShowWindow(hwnd, iCmdShow);
   UpdateWindow(hwnd);

	 //	Loop dei messaggi
	 // Message Loop
   while (GetMessage (&msg, NULL, 0, 0)) {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
   }
	return msg.wParam ;
}

//	Registra una classe di nome FinPrincipale.
//	Torna true se la registrazione ha avuto successo, false sennò
//	QUI si possono definire icona e menu` (dopo averli inseriti nelle
//      risorse) e si puo` cambiare il colore di sfondo.
//      ( vedi righe commentate ) 
// Before creating a window you need to define it
// This function return true if all is ok, or false in case of errors.
// Here you can change the icon and add the menu (after defining them as resources)

static bool RegistraClasse(HINSTANCE hInstance)
{
	static bool registrata = false;
	if( registrata ) return true;
	registrata = true;
  WNDCLASS     wndclass ;
  wndclass.style         = CS_HREDRAW | CS_VREDRAW;
  wndclass.lpfnWndProc   = MainWndProc;
  wndclass.cbClsExtra    = 0;
  wndclass.cbWndExtra    = 0;
  wndclass.hInstance     = hInstance ;
  wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
  //wndclass.hIcon         = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ICON1));
  wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
  //wndclass.hbrBackground = (HBRUSH) GetStockObject (GRAY_BRUSH);
  wndclass.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
  //wndclass.hbrBackground = NULL;
  wndclass.lpszMenuName  = NULL;
//  wndclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);
  wndclass.lpszClassName = "FinPrincipale";
 if (!RegisterClass (&wndclass)) return false;
 return true;
}

//	CALLBACK
LRESULT CALLBACK MainWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static char *ll = "Nuovo Testo";
	switch (message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC dc = BeginPaint(hwnd, &ps);
				RECT rt;
				GetClientRect(hwnd, &rt);
				DrawText(dc, ll, strlen(ll), &rt, DT_CENTER);
				// Provare a cambiare la posizione del testo
				// Try to change text position
				EndPaint(hwnd, &ps);
			}
			break;

		case WM_DESTROY: PostQuitMessage(0); break;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
