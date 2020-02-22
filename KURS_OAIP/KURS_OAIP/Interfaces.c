#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include "framework.h"
#include "resource.h"
#include <CommCtrl.h>
#include <objbase.h>
#include "Calculate.h"
#include <stdio.h>
#include <tgmath.h>

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

///
/// GLOBAL VALUE
///
HINSTANCE hInst;
HWND hwndEdit;
HWND hwndcombobox1;
HWND hwndcombobox2;
TCHAR ListArray[1000];
TCHAR valuesY_s[2][10] =
{
	TEXT("0.0001"), TEXT("0.00001")
};
double valuesY_i[2] =
{
	0.0001, 0.00001
};
TCHAR valuesU_s[3][10] =
{
	TEXT("0.5"), TEXT("1"), TEXT("1.5")
};
double valuesU_i[3] =
{
	0.5, 1, 1.5
};


///
/// INIT FUNCTIONS
///
#pragma region INIT_FUNCTIONS
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void button_calculate();
#pragma endregion



BOOL InitInstance(TCHAR szWindowClass[MAX_LOADSTRING], TCHAR szTitle[MAX_LOADSTRING], HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, (WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME), 300, 300, 325, 400, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
	CreateWindow(TEXT("BUTTON"), TEXT("Calculate"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 40, 75, 20, hWnd, IDC_BUTTON_CALCULATE, WM_COMMAND, NULL);
#pragma region combobox1
	hwndcombobox1 = CreateWindow(WC_COMBOBOX, TEXT(""), CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 10, 10, 100, 100, hWnd, NULL, HINST_THISCOMPONENT, NULL);
	TCHAR A[16];
	int  k = 0;
	memset(&A, 0, sizeof(A));
	for (k = 0; k <= 1; k += 1)
	{
		wcscpy_s(A, sizeof(A) / sizeof(TCHAR), (TCHAR*)valuesY_s[k]);
		SendMessage(hwndcombobox1, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
	}

	// Send the CB_SETCURSEL message to display an initial item 
	//  in the selection field  
	SendMessage(hwndcombobox1, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
#pragma endregion

#pragma region combobox2
	hwndcombobox2 = CreateWindow(WC_COMBOBOX, TEXT(""), CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 200, 10, 100, 100, hWnd, NULL, HINST_THISCOMPONENT, NULL);
	k = 0;
	memset(&A, 0, sizeof(A));
	for (k = 0; k <= 2; k += 1)
	{
		wcscpy_s(A, sizeof(A) / sizeof(TCHAR), (TCHAR*)valuesU_s[k]);
		SendMessage(hwndcombobox2, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
	}
	SendMessage(hwndcombobox2, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
#pragma endregion

#pragma region EDIT BOX
	hwndEdit = CreateWindowEx(
		0, L"EDIT",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL |
		ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
		10, 80, 280, 230,
		hWnd,
		NULL,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);
#pragma endregion

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


double round1(double value)
{
	return floor(value);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDC_BUTTON_CALCULATE:
			button_calculate();
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
TCHAR ListEdit[1000];
void button_calculate()
{
	int ItemIndexY = SendMessage((HWND)hwndcombobox1, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	double Y = valuesY_i[ItemIndexY];
	int ItemIndexU = SendMessage((HWND)hwndcombobox2, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	double U = valuesU_i[ItemIndexU];
	Calc(Y, U);	
	_snwprintf(ListEdit, 1000, L"");
	for (int i = 0; i < 25; i += 1)
	{
		double num = round1(D[i] * 100.0) / 100.0;
		_snwprintf(ListEdit, 1000, L"%s%f\r\n", ListEdit, num);
	}
	SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)ListEdit);
}
