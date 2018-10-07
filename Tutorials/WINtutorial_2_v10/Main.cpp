////////////////////////////////////////////////////////////////////
//	Windows programming: part 2
//
//  Something more, manage the menu, draw a rectangle, move the
//	rectangle using the keyboard arrows keys.
//
//	TO DO:
//	1) understand the code
//  2) Stop the motion on the window borders
//	3) Use one or more menu buttons to change the rectangle color
//	4) Use one or more menu buttons to change the rectangle size
//  4) change the backgriond colofr of the window
//  5) Make the rectangle leave a trace of its movement (like a "snake" program)
//  6) Use one menu button to activate the trace, and another to erase
//	  the trace.
//	You need to define a suitable data structure for memorize the rectangle trace.
//
//////////////////////////////////////////////////////////////////////
//	Esercitazione per windows n. 2
//
//	Qualcosa in piu`:
//      gestione del menu
//      disegno di un quadretto
//      gestione della tastiera
//      gestione del movimento
//
//  Se nella esercitazione 1 avete creato qualcosa di interessante
//  provate ad integrare con le nuove funzionalita`
//
//  1)  Capire il codice
//  2)  Bloccare il movimento ai limiti della finestra
//  3)  Usare uno o piu` tasti del menu per cambiare colore al pallino
//  4)  Usare uno o piu` tasti del menu per cambiare dimensione al pallino
//  5)  Fare in modo che il pallino lasci tracca di se sullo schermo
//  6)  Creare un tasto del menu per attvare la traccia e un'altro
//      per cancellare tutto.
//
//  Per lasciare traccia serve memorizzare le vecchie posizioni in un
//  vettore o lista..


#include <stdlib.h>
#include <string>
#include <windows.h>
#include <fstream>
#include "resource.h"

using namespace std;

//	Funzioni usate prima di essere definite
//	Two routines declared before they are defined
LRESULT CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM);
bool RegistraClasse(HINSTANCE hInstance);

//  Dati per gestione
//	Global data, add here the rectangle dimensions and
//	a vector for draw the trace.
typedef struct {
  int xc, yc;
  int dim;
  int tail[2][10] ;
  COLORREF col;
} data_1;
data_1 Data;

static void norm_pos(int l, int r, int b, int t, data_1* point) {
	
	if (point->xc < l + 5)
	{
		point->xc = l;
	}
	if (Data.xc > r - 5)
	{
		Data.xc = r;
	}
	if (Data.yc < t + 5)
	{
		Data.yc = t;
	}
	if (Data.yc > b - 5)
	{
		Data.yc = b;
	}
	
}

static void updateTail(int x,int y, data_1* data) {
	for (int k = 8; k >= 0; k--)
	{
		data->tail[0][k + 1] = data->tail[0][k];
		data->tail[1][k + 1] = data->tail[1][k];
	}
	data->tail[0][0] = x;
	data->tail[1][0] = y;
}

//	MAIN routine
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
   HWND hwnd;
   MSG  msg;
   
	 //	Registrazione finestra / register a window
	 if( !RegistraClasse(hInstance) ) return 1;

   // Init dati / data initialization
   Data.xc = Data.yc = 100;
   Data.col = RGB(255,0,0);
   Data.dim = 0;
   for (int i=1;i<2;i++)
   {
	   for (int j = 1; j < 10; j++) {
		   Data.tail[i][j]=0;
	   }
   }

	 //	Creazione finestra / create the window
	 hwnd = CreateWindow ("FinPrincipale", "WIN esercitazione 2",
		 WS_OVERLAPPEDWINDOW, 100, 100, 400, 300, NULL,
		 NULL, hInstance, NULL) ;

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
// Before creating a window you need to define it
// This function return true if all is ok, or false in case of errors.
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
  wndclass.hIcon         = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ICON1));
  wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
  wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
  wndclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);
  wndclass.lpszClassName = "FinPrincipale";
 if (!RegisterClass (&wndclass)) return false;
 return true;
}

//	CALLBACK
LRESULT CALLBACK MainWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static char *ll = "Usa le frecce per muovere";
	switch (message) {

		//	Questo gestisce i comandi da menu
		//	The "WM_COMMAND" must be used to respond to the menu
		case WM_COMMAND:
		{
		  int cid = LOWORD (wParam);
		  if( cid == ID_FILE_ESCI ) DestroyWindow(hwnd);
		  if (cid == ID_COLORE_VERDE) {
			  Data.col = RGB(0, 255, 0); 

		  }
		  if (cid == ID_COLORE_BLU) {
			  Data.col = RGB(0, 0, 255); 
		  }
		  if (cid == ID_COLORE_ROSSO) {
			  Data.col = RGB(255, 0, 0);
		  }
		  if (cid == ID_DIMENSIONE_5) {
			  Data.dim = 0;
		  }
		  if (cid == ID_DIMENSIONE_POMENOPIKKOLO) {
			  Data.dim = 5;
		  }
		  if (cid == ID_DIMENSIONE_GROSSO) {
			  Data.dim = 20;
		  }
		  InvalidateRect(hwnd, NULL, TRUE);
		}
		return 0 ;

		//	Questo gestisce le frecce (versione semplice)
		//	How to respond to the arrow keys
    case WM_KEYDOWN:
      {
			
			RECT rt;
			GetClientRect(hwnd, &rt);     // "usare per fermare il quadrattino"
			int max_x;
			int max_y;
			int min_x;
			int min_y;
			max_y = rt.bottom;
			max_x = rt.right;
			min_y = rt.top;
			min_x = rt.left;			//	Use the "rt" data to stop the rectangle motion

			updateTail(Data.xc, Data.yc, &Data);

 		    int id = (TCHAR) wParam;
			if (id == 37) {
				norm_pos(min_x, max_x, max_y, min_y, &Data);
				Data.xc -= 5;

				norm_pos(min_x, max_x, max_y, min_y, &Data);
				

				

				InvalidateRect(hwnd, NULL, TRUE);
			}
		    if( id == 39 ) {			// ->
				
				norm_pos(min_x, max_x, max_y, min_y, &Data);
				Data.xc += 5;
				norm_pos(min_x, max_x, max_y, min_y, &Data);
				
				InvalidateRect(hwnd, NULL, TRUE);
		    }
		    if( id == 38 ) {			// UP
				
				norm_pos(min_x, max_x, max_y, min_y, &Data);
				Data.yc -= 5;
				norm_pos(min_x, max_x, max_y, min_y, &Data);
			
				InvalidateRect(hwnd, NULL, TRUE);
		    }
		    else if( id == 40 ) {			// DOWN
				
				norm_pos(min_x, max_x, max_y, min_y, &Data);
				Data.yc += 5;
				norm_pos(min_x, max_x, max_y, min_y, &Data);
			
				InvalidateRect(hwnd, NULL, TRUE);
		    }
		    break;

			
      }

		case WM_SIZE:
			{
			RECT rt;
			GetClientRect(hwnd, &rt);     // "usare per fermare il quadrattino"
			int max_x;
			int max_y;
			int min_x;
			int min_y;
			max_y = rt.bottom;
			max_x = rt.right;
			min_y = rt.top;
			min_x = rt.left;			//	Use the "rt" data to stop the rectangle motion
			norm_pos(min_x, max_x, max_y, min_y, &Data);
			}

		//	Questo disegna il pallino
		//	Drawing
		case WM_PAINT:
			{
			std::ofstream outfile;

			outfile.open("test.txt", std::ios_base::app);
			string sx,sy;
			
			



				PAINTSTRUCT ps;
				HDC dc = BeginPaint(hwnd, &ps);
				RECT rt;
				GetClientRect(hwnd, &rt);
				DrawText(dc, ll, strlen(ll), &rt, DT_CENTER);
				//per cambiare penna è necessario salvare la precedente e poi 
				//resettarla alla fine delle operazioni
				HPEN Pen = CreatePen(PS_SOLID,Data.dim,Data.col);
				HPEN OPen = (HPEN) SelectObject(dc,(HGDIOBJ) Pen);
				int x0, y0, x1, y1;
				x0 = Data.xc - 5; y0 = Data.yc - 5;
				x1 = Data.xc + 5; y1 = Data.yc + 5;
				for(int y=y0; y <= y1; y++) {
    					MoveToEx(dc,x0,y,NULL); LineTo(dc,x1,y);
			}
				for (int k = 1; k < 10; k++) {
					outfile << to_string(k)+"\n";
					sx ="SX"+to_string(Data.tail[0][k])+ "\n";
					outfile << sx;
					sy = "SY" + to_string(Data.tail[1][k]) + "\n";
					outfile << sy;
					if (Data.tail[0][k] == 0 && Data.tail[1][k] == 0)
					{
						break;
					}
					x0 = Data.tail[0][k] - 5; y0 = Data.tail[1][k] - 5;
					x1 = Data.tail[0][k] + 5; y1 = Data.tail[1][k] + 5;
					

					
					

					for (int y = y0; y <= y1; y++) {
						MoveToEx(dc, x0, y, NULL); LineTo(dc, x1, y);
					}
				}
    	  SelectObject(dc, OPen);
		    DeleteObject((HGDIOBJ) Pen);
				EndPaint(hwnd, &ps);
			}
			break;

		case WM_DESTROY: PostQuitMessage(0); break;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
