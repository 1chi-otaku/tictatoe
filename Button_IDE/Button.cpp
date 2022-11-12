#include <windows.h>
#include <tchar.h>
#include "resource.h"

HWND hb[9];
HWND hStartNewGame;

HBITMAP o;
HBITMAP x;


BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC)DlgProc); 
}

void Restart(HWND h[], short comb[3][3]) {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			comb[i][j] = 0;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		SendMessage(h[i], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), NULL);
		EnableWindow(h[i], TRUE);
	}

}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static short combitnation[3][3];
	static bool end = false;
	static int move = 0;
	if (end) {
		move = 0;
		end = false;
	}
	if (combitnation[0][0] == 1 && combitnation[0][1] == 1 && combitnation[0][2] == 1 ||
		combitnation[1][0] == 1 && combitnation[1][1] == 1 && combitnation[1][2] == 1 ||
		combitnation[2][0] == 1 && combitnation[2][1] == 1 && combitnation[2][2] == 1 ||
		combitnation[0][0] == 1 && combitnation[1][0] == 1 && combitnation[2][0] == 1 ||
		combitnation[0][1] == 1 && combitnation[1][1] == 1 && combitnation[2][1] == 1 ||
		combitnation[0][2] == 1 && combitnation[1][2] == 1 && combitnation[2][2] == 1 ||
		combitnation[0][0] == 1 && combitnation[1][1] == 1 && combitnation[2][2] == 1 ||
		combitnation[2][0] == 1 && combitnation[1][1] == 1 && combitnation[0][2] == 1 ||
		combitnation[0][0] == 2 && combitnation[0][1] == 2 && combitnation[0][2] == 2 ||
		combitnation[1][0] == 2 && combitnation[1][1] == 2 && combitnation[1][2] == 2 ||
		combitnation[2][0] == 2 && combitnation[2][1] == 2 && combitnation[2][2] == 2 ||
		combitnation[0][0] == 2 && combitnation[1][0] == 2 && combitnation[2][0] == 2 ||
		combitnation[0][1] == 2 && combitnation[1][1] == 2 && combitnation[2][1] == 2 ||
		combitnation[0][2] == 2 && combitnation[1][2] == 2 && combitnation[2][2] == 2 ||
		combitnation[0][0] == 2 && combitnation[1][1] == 2 && combitnation[2][2] == 2 ||
		combitnation[2][0] == 2 && combitnation[1][1] == 2 && combitnation[0][2] == 2
		)
	{
		Restart(hb, combitnation);
		end = true;
		if (move % 2) {
			MessageBox(hWnd, TEXT("X-player won!"), TEXT("Game over!"), MB_OK | MB_ICONINFORMATION);
		}
		else {
			MessageBox(hWnd, TEXT("0-player won!"), TEXT("Game over!"), MB_OK | MB_ICONINFORMATION);
		}
		move = 0;
		
	}
	else if (move == 9) {
		move = 0;
		MessageBox(hWnd, TEXT("Dead heat!"), TEXT("Game over!"), MB_OK | MB_ICONINFORMATION);
		end = true;
		
	}

	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG: {

		for (int i = 0; i < 9; i++)
		{
			hb[i] = GetDlgItem(hWnd, IDC_B1+i);
		}
		hStartNewGame = GetDlgItem(hWnd, IDOK);

		o = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP6));
		x = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP7));
		return TRUE;

	}
		case WM_COMMAND: {			
			switch (LOWORD(wParam))
			{
			case IDC_B1:
				move++;
				EnableWindow(hb[0], FALSE);

				if (move % 2 == 0) {
					SendMessage(hb[0], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(x));
					combitnation[0][0] = 1;
				}
				else {
					SendMessage(hb[0], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(o));
					combitnation[0][0] = 2;
				}
				
				break;
			case IDC_B2:
				move++;
				EnableWindow(hb[1], FALSE);
				if (move % 2 == 0) {
					SendMessage(hb[1], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(x));
					combitnation[0][1] = 1;
				}
				else {
					SendMessage(hb[1], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(o));
					combitnation[0][1] = 2;
				};
				break;
			case IDC_B3:
				move++;
				EnableWindow(hb[2], FALSE);
				if (move % 2 == 0) {
					SendMessage(hb[2], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(x));
					combitnation[0][2] = 1;
				}
				else {
					SendMessage(hb[2], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(o));
					combitnation[0][2] = 2;
				}
				break;
			case IDC_B4:
				EnableWindow(hb[3], FALSE);
				move++;
				if (move % 2 == 0) {
					SendMessage(hb[3], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(x));
					combitnation[1][0] = 1;
				}
				else {
					SendMessage(hb[3], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(o));
					combitnation[1][0] = 2;
				}
				break;
			case IDC_B5:
				EnableWindow(hb[4], FALSE);
				move++;
				if (move % 2 == 0) {
					SendMessage(hb[4], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(x));
					combitnation[1][1] = 1;
				}
				else {
					SendMessage(hb[4], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(o));
					combitnation[1][1] = 2;
				}
				break;
			case IDC_B6:
				EnableWindow(hb[5], FALSE);
				move++;
				if (move % 2 == 0) {
					SendMessage(hb[5], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(x));
					combitnation[1][2] = 1;
				}
				else {
					SendMessage(hb[5], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(o));
					combitnation[1][2] = 2;
				}
				break;
			case IDC_B7:
				EnableWindow(hb[6], FALSE);
				move++;
				if (move % 2 == 0) {
					SendMessage(hb[6], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(x));
					combitnation[2][0] = 1;
				}
				else {
					SendMessage(hb[6], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(o));
					combitnation[2][0] = 2;
				}
				break;
			case IDC_B8:
				EnableWindow(hb[7], FALSE);
				move++;
				if (move % 2 == 0) {
					SendMessage(hb[7], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(x));
					combitnation[2][1] = 1;
				}
				else {
					SendMessage(hb[7], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(o));
					combitnation[2][1] = 2;
				}
				break;
			case IDC_B9:
				EnableWindow(hb[8], FALSE);
				move++;
				if (move % 2 == 0) {
					SendMessage(hb[8], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(x));
					combitnation[2][2] = 1;
				}
				else {
					SendMessage(hb[8], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(o));
					combitnation[2][2] = 2;
				}
				break;
			case IDOK:
				Restart(hb, combitnation);
				end = true;
				move = 0;
				break;

			}
		}			
			return TRUE;

	}
	return FALSE;
}