// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include <Commctrl.h>
#include <Shellapi.h>
#include <stdio.h>

#include "resource.h"

#pragma comment(lib, "comctl32.lib")

HWND mainhwnd;

HWND hwndStatus;

HWND hwndListView1;

HWND hwndListView2;

LV_COLUMN lvc;

LV_ITEM lvi;

HWND hwndToolBar;

HWND hwndTreeView;

HWND hwndComboBox1;

HWND hwndComboBox2;

HWND hwndEdit;

HINSTANCE hInst;


WNDPROC hEditProc;

bool MyTree = 0;

bool first = 1;

char CurentDiskName[3];

char CurrDir1[1024];

char CurrDir2[1024];

int index1;

int index2;

int a, b, c;

LPNMHDR   pNotifMessageHeader; //указатель на структуру уведомляющего сообщения

RECT   statusRect;    //размер строки состояния

UINT   wStatID;   //идентификатор окна состояния

LPNMTREEVIEW ptrNotifMessageTreeView; //указатель на уведомляющее сообщение от узла TreeView

int ComboInd;

HMENU hMenu, hMenupopup;

const int IDM_COPY = 100;

const int IDM_RENAME = 101;

const int IDM_MKDIR = 102;

const int IDM_DELETE = 103;

const int IDM_ABOUT1 = 104;

const int IDM_REFRESH = 105;

const int IDM_MOVE = 106;

const int ID_TIMER1 = 1000;

const int ID_SB = 1001;

const int ID_LISTVIEW1 = 1002;

const int ID_LISTVIEW2 = 1003;

const int ID_TREEVIEW = 1004;

const int ID_TOOLBAR = 1005;

const int ID_COMBOBOX1 = 1006;

const int ID_COMBOBOX2 = 1007;

const int ID_EDIT = 1009;


const int IDI_TREE = 2001;
const int IDI_NEW = 2002;
const int IDI_COPY = 2003;
const int IDI_RENAME = 2004;
const int IDI_DELETE = 2005;
const int IDI_MOVE = 2006;
const int IDI_REFRESH = 2007;

const int IDM_CGFOLDER = 3001;
const int IDM_CYFOLDER = 3002;
const int IDM_UPARROW = 3003;
const int IDM_YFOLDER = 3004;


HIMAGELIST hilLarge;

HIMAGELIST himlSmall1;

HIMAGELIST himlSmall2;

char DirName[1024];

unsigned long ChSize = 0;

void OnResize();

void RefreshComboInf(HWND hwndCombo);

void DiskBrows();

void CreateFoldersOnDisk(HWND hwnd);

LPSTR FindFullPath(LPSTR strDrive/*[out]*/, HWND hwndTreeView, HTREEITEM htreeItem);

bool AddChildren(HWND hwndTreeView, HTREEITEM hTreeItem, LPCSTR ParentDir);

bool DelChildren(HWND hwndTreeView, HTREEITEM hTreeItem);

bool CollapseChildren(HWND hwndTreeView, HTREEITEM hTreeItem);


void FillListView(HWND hwndlv, LPCSTR ParentDir, HIMAGELIST himlSmall);

unsigned long GetFolderSize(LPCSTR ParentDir);

void OnDblClick(HWND hwndlv, char* CurrentDirectory, HIMAGELIST himlSmall);

void CreateNewFolder(HWND hwndlv, LPCSTR CurrDir, HIMAGELIST himlSmall);

void DeleteFile(HWND hwndlv, LPCSTR CurrDir);

void Renamefile(HWND hwndlv);



void CopyFile(HWND hwndlv1, HWND hwndlv2, LPCSTR CurrD1, LPCSTR CurrD2, HIMAGELIST himlSmall);

void CutFile(HWND hwndlv1, HWND hwndlv2, LPCSTR CurrD1, LPCSTR CurrD2, HIMAGELIST himlSmall);

void PasteFile(HWND hwndlv1, HWND hwndlv2, LPCSTR CurrDir,

	HIMAGELIST himlSmall, LPCSTR csFileNameCopy, LPCSTR csNF, bool cut, int index);



LRESULT EditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



void GoTo(HWND hwndlv, char* CurrentDirectory, HIMAGELIST himlSmall);

void Activate();

void DisActivate();



LRESULT CALLBACK WindowFunc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);


typedef struct _FLAGDISK

{

	DWORD dwFlag;

	char* cDisk;

} FLAGDISK;



FLAGDISK FlagDisk[26] =

{

	0x1, "A:\\",

	0x2, "B:\\",

	0x4, "C:\\",

	0x8, "D:\\",

	0x10, "E:\\",

	0x20, "F:\\",

	0x40, "G:\\",

	0x80, "H:\\",

	0x100, "I:\\",

	0x200, "J:\\",

	0x400, "K:\\",

	0x800, "L:\\",

	0x1000, "M:\\",

	0x2000, "N:\\",

	0x4000, "O:\\",

	0x8000, "P:\\",

	0x10000, "Q:\\",

	0x20000, "R:\\",

	0x40000, "S:\\",

	0x80000, "T:\\",

	0x100000, "U:\\",

	0x200000, "V:\\",

	0x400000, "W:\\",

	0x800000, "X:\\",

	0x1000000, "Y:\\",

	0x2000000, "Z:\\"

};



BOOL IsDiskInDrive(LPTSTR lpszDrive);



char szWinName[] = "File Manager"; // имя класса окна



int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)

{

	HWND hwnd;

	MSG  msg;

	WNDCLASSEX wcl;



	HICON hIcon; //for toolbar

	TBBUTTON btns[9];



	hInst = hThisInst;



	InitCommonControls();



	//определение класса окна



	wcl.hInstance = hThisInst;          //работа с данным экземпляром


	wcl.lpfnWndProc = WindowFunc;       // оконная функция

	wcl.style = CS_HREDRAW | CS_VREDRAW;  // стиль 

	wcl.lpszClassName = szWinName;

	wcl.cbSize = sizeof(WNDCLASSEX);    //установка размера



	wcl.hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDI_WIN32PROJECT1));

	wcl.hIconSm = LoadIcon(hThisInst, MAKEINTRESOURCE(IDI_SMALL));



	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);    //стиль курсора

	wcl.lpszMenuName = NULL;                      //нет меню



	wcl.cbClsExtra = 0;                           //дополнительной

	wcl.cbWndExtra = 0;                           //информации нет



	wcl.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);  //фон окна 



	//регистрация окна

	if (!RegisterClassEx(&wcl)) return 0;



	//класс окна зарегистрирован, создаем окно

	hwnd = CreateWindow(

		szWinName,

		"My_Comander",

		WS_OVERLAPPEDWINDOW,

		100,

		100,

		800,

		600,

		HWND_DESKTOP,

		NULL,

		hThisInst,

		NULL

		);



	if (!hwnd)

	{

		MessageBox(NULL, "Cannot create window", "Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;

	}



	mainhwnd = hwnd; // глобальная переменная HWND

	//menu

	hMenu = CreateMenu();

	hMenupopup = CreateMenu();

	AppendMenu(hMenupopup, MF_STRING, IDM_COPY, "Copy");

	AppendMenu(hMenupopup, MF_STRING, IDM_MOVE, "Move");

	AppendMenu(hMenupopup, MF_STRING, IDM_RENAME, "Rename");

	AppendMenu(hMenupopup, MF_STRING, IDM_MKDIR, "MakeDir");

	AppendMenu(hMenupopup, MF_STRING, IDM_DELETE, "Delete");

	AppendMenu(hMenupopup, MF_SEPARATOR, 0, NULL);

	AppendMenu(hMenupopup, MF_STRING, IDM_REFRESH, "Refresh");

	AppendMenu(hMenu, MF_POPUP, (UINT)hMenupopup, "File");



	AppendMenu(hMenu, MF_STRING, IDM_ABOUT1, "About");



	SetMenu(hwnd, hMenu);

	//end menu





	RECT rcClient;

	char *ToolTipText1 = "Icon";//подсказка



	// Create the status bar. 

	hwndStatus = CreateWindowEx(

		0,                       // no extended styles 

		STATUSCLASSNAME,         // name of status bar class 

		(LPCTSTR)NULL,          // no text when first created 

		SBARS_SIZEGRIP |         // includes a sizing grip 

		WS_CHILD | WS_VISIBLE | SBT_TOOLTIPS, // creates a child window 

		0, 0, 0, 0,              // ignores size and position 

		mainhwnd,              // handle to parent window 

		(HMENU)ID_SB,       // child window identifier 

		hThisInst,                   // handle to application instance 

		NULL

		);                   // no window creation data 



	//begin TOOLBAR!//-----------------------------------------------------

	hwndToolBar = CreateToolbarEx(

		hwnd,

		WS_CHILD | WS_VISIBLE |

		TBSTYLE_TOOLTIPS | TBSTYLE_FLAT |

		WS_BORDER, ID_TOOLBAR,

		3, NULL, 0,

		NULL,

		0,

		0, 0, 0, 0,

		sizeof(TBBUTTON)

		);



	hilLarge = ImageList_Create(20, 20, ILC_COLOR32 | ILC_MASK, 9, 0);





	hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDI_TREE));

	UINT iTree = ImageList_AddIcon(hilLarge, hIcon);

	DeleteObject(hIcon);



	hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDI_NEW));

	UINT iNew = ImageList_AddIcon(hilLarge, hIcon);

	DeleteObject(hIcon);



	hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDI_COPY));

	UINT iCopy = ImageList_AddIcon(hilLarge, hIcon);

	DeleteObject(hIcon);



	hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDI_RENAME));

	UINT iRename = ImageList_AddIcon(hilLarge, hIcon);

	DeleteObject(hIcon);



	hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDI_DELETE));

	UINT iDel = ImageList_AddIcon(hilLarge, hIcon);

	DeleteObject(hIcon);



	hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDI_MOVE));

	UINT iMove = ImageList_AddIcon(hilLarge, hIcon);

	DeleteObject(hIcon);



	hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDI_REFRESH));

	UINT iRef = ImageList_AddIcon(hilLarge, hIcon);

	DeleteObject(hIcon);





	btns[0].iBitmap = iTree;

	btns[0].idCommand = IDI_TREE;

	btns[0].fsState = TBSTATE_ENABLED;

	btns[0].fsStyle = BYTE(TBSTYLE_BUTTON);

	btns[0].dwData = NULL;


	char s1[] = "Tree";

	btns[0].iString = (INT_PTR)s1;



	btns[1].iBitmap = 0;

	btns[1].idCommand = 0;

	btns[1].fsState = TBSTATE_ENABLED;

	btns[1].fsStyle = BYTE(TBSTYLE_SEP);

	btns[1].dwData = NULL;

	btns[1].iString = 0;



	btns[2].iBitmap = iNew;

	btns[2].idCommand = IDI_NEW;

	btns[2].fsState = TBSTATE_ENABLED;

	btns[2].fsStyle = BYTE(TBSTYLE_BUTTON);

	btns[2].dwData = NULL;


	char s2[] = "NEW";

	btns[2].iString = (INT_PTR)s2;
	

	btns[3].iBitmap = iCopy;

	btns[3].idCommand = IDI_COPY;

	btns[3].fsState = TBSTATE_ENABLED;

	btns[3].fsStyle = BYTE(TBSTYLE_BUTTON);

	btns[3].dwData = NULL;

	char s3[] = "COPY";

	btns[3].iString = (INT_PTR)s3;



	btns[4].iBitmap = iRename;

	btns[4].idCommand = IDI_RENAME;

	btns[4].fsState = TBSTATE_ENABLED;

	btns[4].fsStyle = BYTE(TBSTYLE_BUTTON);

	btns[4].dwData = NULL;

	char s4[] = "Rename";

	btns[4].iString = (INT_PTR)s4;



	btns[5].iBitmap = iDel;

	btns[5].idCommand = IDI_DELETE;

	btns[5].fsState = TBSTATE_ENABLED;

	btns[5].fsStyle = BYTE(TBSTYLE_BUTTON);

	btns[5].dwData = NULL;

	char s5[] = "DEL";

	btns[5].iString = (INT_PTR)s5;



	btns[6].iBitmap = iMove;

	btns[6].idCommand = IDI_MOVE;

	btns[6].fsState = TBSTATE_ENABLED;

	btns[6].fsStyle = BYTE(TBSTYLE_BUTTON);

	btns[6].dwData = NULL;

	char s6[] = "MOVE";

	btns[6].iString = (INT_PTR)s6;



	btns[7].iBitmap = 0;

	btns[7].idCommand = 0;

	btns[7].fsState = TBSTATE_ENABLED;

	btns[7].fsStyle = BYTE(TBSTYLE_SEP);

	btns[7].dwData = NULL;

	btns[7].iString = 0;



	btns[8].iBitmap = iRef;

	btns[8].idCommand = IDI_REFRESH;

	btns[8].fsState = TBSTATE_ENABLED;

	btns[8].fsStyle = BYTE(TBSTYLE_BUTTON);

	btns[8].dwData = NULL;
	char s[] = "Refresh";

	btns[8].iString = (INT_PTR)s;



	//SendMessage(hwndToolBar, TB_SETIMAGELIST, 0, LPARAM(hilLarge));



	SendMessage(hwndToolBar, TB_ADDBUTTONS, 9, LPARAM(btns));



	//end TOOLBAR!//---------------------------------------------------   



	// Get the coordinates of the parent window's client area. 

	GetClientRect(mainhwnd, &rcClient);





	//Создание ComboBox-ов

	hwndComboBox1 = CreateWindowEx(

		0, "COMBOBOX", NULL,

		WS_BORDER | WS_VISIBLE | CBS_DROPDOWNLIST |

		WS_CHILD | CBS_DROPDOWN,

		// No size yet--resize after setting image list.

		25,      // Vertical position of Combobox

		0,      // Horizontal position of Combobox

		0,      // Sets the width of Combobox

		100,    // Sets the height of Combobox

		mainhwnd,

		NULL,

		hThisInst,

		NULL);



	hwndComboBox2 = CreateWindowEx(

		0, "COMBOBOX", NULL,

		WS_BORDER | WS_VISIBLE | CBS_DROPDOWNLIST |

		WS_CHILD | CBS_DROPDOWN,

		// No size yet--resize after setting image list.

		0,      // Vertical position of Combobox

		0,      // Horizontal position of Combobox

		0,      // Sets the width of Combobox

		0,    // Sets the height of Combobox

		mainhwnd,

		NULL,

		hThisInst,

		NULL);







	//Создание list view

	hwndListView1 = CreateWindowEx(

		WS_EX_CLIENTEDGE,

		WC_LISTVIEW, NULL,

		WS_CHILD | LVS_REPORT | LVS_EDITLABELS | LVS_SINGLESEL |

		WS_VISIBLE | WS_BORDER | WS_OVERLAPPED,

		0, 100, 200, 300,

		mainhwnd,

		(HMENU)ID_LISTVIEW1,

		hThisInst,

		NULL

		);



	hwndListView2 = CreateWindow(

		//WS_EX_CLIENTEDGE,

		WC_LISTVIEW, NULL,

		WS_CHILD | LVS_REPORT | LVS_EDITLABELS | LVS_SINGLESEL |

		WS_VISIBLE | WS_BORDER | WS_OVERLAPPED,

		200, 100, 400, 300,

		mainhwnd,

		(HMENU)ID_LISTVIEW2,

		hThisInst,

		NULL

		);



	ListView_SetExtendedListViewStyle(hwndListView1, LVS_EX_FULLROWSELECT);

	ListView_SetExtendedListViewStyle(hwndListView2, LVS_EX_FULLROWSELECT);



	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 0;

	lvc.pszText = "Name";

	lvc.cx = 150;

	lvc.fmt = LVCFMT_LEFT;

	ListView_InsertColumn(hwndListView1, 0, &lvc);



	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 1;

	lvc.pszText = "Type";

	lvc.cx = 50;

	lvc.fmt = LVCFMT_LEFT;

	ListView_InsertColumn(hwndListView1, 1, &lvc);



	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 2;

	lvc.pszText = "Size";

	lvc.cx = 65;

	lvc.fmt = LVCFMT_LEFT;

	ListView_InsertColumn(hwndListView1, 2, &lvc);



	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 3;

	lvc.pszText = "Date of creation";

	lvc.cx = 100;

	lvc.fmt = LVCFMT_LEFT;

	ListView_InsertColumn(hwndListView1, 3, &lvc);



	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 0;

	lvc.pszText = "Name";

	lvc.cx = 150;

	lvc.fmt = LVCFMT_LEFT;

	ListView_InsertColumn(hwndListView2, 0, &lvc);



	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 1;

	lvc.pszText = "Type";

	lvc.cx = 50;

	lvc.fmt = LVCFMT_LEFT;

	ListView_InsertColumn(hwndListView2, 1, &lvc);



	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 2;

	lvc.pszText = "Size";

	lvc.cx = 65;

	lvc.fmt = LVCFMT_LEFT;

	ListView_InsertColumn(hwndListView2, 2, &lvc);



	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 3;

	lvc.pszText = "Date of creation";

	lvc.cx = 100;

	lvc.fmt = LVCFMT_LEFT;

	ListView_InsertColumn(hwndListView2, 3, &lvc);



	// Создаем списки изображений

	himlSmall1 = ImageList_Create(GetSystemMetrics(SM_CXSMICON),

		GetSystemMetrics(SM_CYSMICON), ILC_COLOR24 | ILC_MASK, 8, 1);

	himlSmall2 = ImageList_Create(GetSystemMetrics(SM_CXSMICON),

		GetSystemMetrics(SM_CYSMICON), ILC_COLOR24 | ILC_MASK, 8, 1);

	// Добавляем в списки пиктограммы

	// изображений папок

	hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDM_CGFOLDER));

	a = ImageList_AddIcon(himlSmall1, hIcon);

	a = ImageList_AddIcon(himlSmall2, hIcon);



	hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDM_CYFOLDER));

	b = ImageList_AddIcon(himlSmall1, hIcon);

	b = ImageList_AddIcon(himlSmall2, hIcon);



	hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDM_UPARROW));

	c = ImageList_AddIcon(himlSmall1, hIcon);

	c = ImageList_AddIcon(himlSmall2, hIcon);


	//Добавляем эти ImageList-ы



	ListView_SetImageList(hwndListView1, himlSmall1, LVSIL_SMALL);

	ListView_SetImageList(hwndListView2, himlSmall2, LVSIL_SMALL);





	// конец описания List View



	//TreeView 



	hwndTreeView = CreateWindowEx(

		WS_EX_CLIENTEDGE,

		WC_TREEVIEW, NULL,

		WS_CHILD | LVS_REPORT |

		WS_VISIBLE | WS_BORDER | WS_OVERLAPPED | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT,

		0, 0, 0, 0,

		mainhwnd,

		(HMENU)ID_TREEVIEW,

		hThisInst,

		NULL

		);



	HIMAGELIST himl;  // handle to image list 



	// Create the image list. 



	himl = ImageList_Create(GetSystemMetrics(SM_CXSMICON),

		GetSystemMetrics(SM_CYSMICON), ILC_COLOR24 | ILC_MASK, 8, 1);



	hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDM_YFOLDER));

	ImageList_AddIcon(himl, hIcon);



	hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDM_CYFOLDER));

	ImageList_AddIcon(himl, hIcon);



	// Associate the image list with the tree-view control. 

	TreeView_SetImageList(hwndTreeView, himl, TVSIL_NORMAL);



	//end of TreeView definition



	//описание Edit

	hwndEdit = CreateWindow(

		"EDIT",     // predefined class 

		NULL,       // no window title 

		WS_CHILD | WS_VISIBLE |

		ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL,

		0, 0, 0, 0, // set size in WM_SIZE message 

		mainhwnd,       // parent window 

		(HMENU)ID_EDIT, // edit control ID 

		hThisInst,

		NULL);                // pointer not needed 



	hEditProc = (WNDPROC)SetWindowLong(hwndEdit, GWL_WNDPROC, (LONG)EditWndProc);



	OnResize();

	DiskBrows();

	strcat(CurrDir2, "C:\\");

	strcat(CurrDir1, "C:\\");



	index1 = 1;

	index2 = 1;



	SendMessage(hwndComboBox1, CB_SETCURSEL, index1, 0);//выбираем Диск С:

	SendMessage(hwndComboBox2, CB_SETCURSEL, index2, 0);//выбираем Диск С:

	SetWindowText(hwndEdit, CurrDir2);

	SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)0 | 0, (LPARAM) "Ready"); //отображаем в строке состояния готовность

	ShowWindow(hwnd, nWinMode);

	FillListView(hwndListView1, CurrDir1, himlSmall1);

	FillListView(hwndListView2, CurrDir2, himlSmall2);



	UpdateWindow(hwnd);



	while (GetMessage(&msg, NULL, 0, 0))

	{

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}

	return msg.wParam;

}







LRESULT CALLBACK WindowFunc(HWND hwnd, UINT message, WPARAM wParam,

	LPARAM lParam)

{

	static RECT   Rect;

	TV_ITEM    TV_Item;

	HWND    hSender; //дескриптор элемента, от которого пришло сообщение

	char    LongPath[1000]; //полное имя файла

	char    strRootDrive[100]; //корневой диск для файла

	char    Drive[4];

	HTREEITEM   hSelectedItem;

	LV_DISPINFO *pdi;

	char csName[256], csFirst[256], csSDir[] = "<DIR>", csNameFile[256];

	int iError;



	switch (message)

	{

	case WM_CREATE:

		SetTimer(hwnd, ID_TIMER1, 100, (TIMERPROC)NULL);

		hInst = ((LPCREATESTRUCT)lParam)->hInstance;



		break;

	case WM_SIZE:

		SendMessage(hwndToolBar, message, wParam, lParam);

		SendMessage(hwndStatus, message, wParam, lParam);

		OnResize();

		break;



	case WM_COMMAND:

		if (LOWORD(wParam) == IDM_ABOUT)

			MessageBox(mainhwnd,

			"Курсовая работа:\n"

			"Файловый менеджер\n", "About", MB_ICONINFORMATION);

		if (LOWORD(wParam) == IDI_TREE) //for toolbar

		{

			MyTree = !(MyTree);

			OnResize();

			if (MyTree)

			{

				RefreshComboInf(hwndComboBox1);//определение выбранного диска

				CreateFoldersOnDisk(hwnd);//построение нового дерева

				hSelectedItem = TreeView_GetRoot(hwndTreeView);//сообщение TreeView

				TreeView_Expand(        //что у него развёрнут корень

					hwndTreeView,

					hSelectedItem,

					TVE_EXPAND

					);

				first = 0;

			}

			if (!MyTree)

				FillListView(hwndListView1, CurrDir1, himlSmall1);



		}

		if (LOWORD(wParam) == IDI_NEW || LOWORD(wParam) == IDM_MKDIR)

		{

			if (GetFocus() == hwndListView1)

				CreateNewFolder(hwndListView1, CurrDir1, himlSmall1);

			if (GetFocus() == hwndListView2)

				CreateNewFolder(hwndListView2, CurrDir2, himlSmall2);

		}

		if (LOWORD(wParam) == IDI_DELETE || LOWORD(wParam) == IDM_DELETE)

		{

			if (GetFocus() == hwndListView1)

				DeleteFile(hwndListView1, CurrDir1);

			if (GetFocus() == hwndListView2)

				DeleteFile(hwndListView2, CurrDir2);

		}

		if (LOWORD(wParam) == IDI_RENAME || LOWORD(wParam) == IDM_RENAME)

		{

			if (GetFocus() == hwndListView1)

				Renamefile(hwndListView1);

			if (GetFocus() == hwndListView2)

				Renamefile(hwndListView2);

		}

		if (LOWORD(wParam) == IDI_COPY || LOWORD(wParam) == IDM_COPY)

		{

			if (GetFocus() == hwndListView1)

				CopyFile(hwndListView1, hwndListView2, CurrDir1, CurrDir2, himlSmall2);

			if (GetFocus() == hwndListView2)

				CopyFile(hwndListView2, hwndListView1, CurrDir2, CurrDir1, himlSmall1);

		}

		if (LOWORD(wParam) == IDI_MOVE || LOWORD(wParam) == IDM_MOVE)

		{

			if (GetFocus() == hwndListView1)

				CutFile(hwndListView1, hwndListView2, CurrDir1, CurrDir2, himlSmall2);

			if (GetFocus() == hwndListView2)

				CutFile(hwndListView2, hwndListView1, CurrDir2, CurrDir1, himlSmall1);

		}

		if (LOWORD(wParam) == IDI_REFRESH || LOWORD(wParam) == IDM_REFRESH)

		{

			FillListView(hwndListView1, CurrDir1, himlSmall1);

			FillListView(hwndListView2, CurrDir2, himlSmall2);

		}

		if (HWND(lParam) == hwndComboBox1)  //источник - ComboBox1

		{

			if (HIWORD(wParam) == CBN_SELCHANGE)

			{

				strcpy(Drive, CurentDiskName);

				RefreshComboInf(hwndComboBox1);//определение выбранного диска

				if (IsDiskInDrive(CurentDiskName))

				{

					strcpy(CurrDir1, CurentDiskName);

					index1 = SendMessage(hwndComboBox1, CB_GETCURSEL, 0, 0);

					SetWindowText(hwndEdit, CurrDir1);

					if (MyTree)

					{

						TreeView_DeleteAllItems(hwndTreeView);//удаление элементов из TreeView

						CreateFoldersOnDisk(hwnd);//построение нового дерева

						hSelectedItem = TreeView_GetRoot(hwndTreeView);//сообщение TreeView

						TreeView_Expand(        //что у него развёрнут корень

							hwndTreeView,

							hSelectedItem,

							TVE_EXPAND

							);

					}

					else

					{

						FillListView(hwndListView1, CurrDir1, himlSmall1);



					}

				}

				else

				{

					MessageBox(NULL,

						"Диск не готов",

						"Ошибка",

						MB_ICONERROR | MB_OK | MB_TASKMODAL);

					strcpy(CurentDiskName, Drive);

					SendMessage(hwndComboBox1, CB_SETCURSEL, index1, 0);

				}

			};

		};

		if (HWND(lParam) == hwndComboBox2)  //источник - ComboBox2

		{

			if (HIWORD(wParam) == CBN_SELCHANGE)

			{

				strcpy(Drive, CurentDiskName);

				RefreshComboInf(hwndComboBox2);

				if (IsDiskInDrive(CurentDiskName))

				{

					strcpy(CurrDir2, CurentDiskName);

					index2 = SendMessage(hwndComboBox2, CB_GETCURSEL, 0, 0);

					FillListView(hwndListView2, CurrDir2, himlSmall2);

					SetWindowText(hwndEdit, CurrDir2);

				}

				else

				{



					strcpy(CurentDiskName, Drive);

					SendMessage(hwndComboBox2, CB_SETCURSEL, index2, 0);

					MessageBox(NULL,

						"Диск не готов",

						"Ошибка",

						MB_ICONERROR | MB_OK | MB_TASKMODAL);

				}

			};

		};

		break;



	case WM_NOTIFY:  //сообщение об изменении состояния элемента

		pNotifMessageHeader = (LPNMHDR)lParam;  //определяем структуру сообщения

		hSender = pNotifMessageHeader->hwndFrom; //определяем элемент-источник



		switch (pNotifMessageHeader->code)

		{

		case TTN_NEEDTEXT:

			LPTOOLTIPTEXT lpToolTipText;

			lpToolTipText = (LPTOOLTIPTEXT)lParam;

			lpToolTipText->hinst = hInst;

			lpToolTipText->lpszText = MAKEINTRESOURCE(lpToolTipText->hdr.idFrom);

			break;

		}

		if (hSender == hwndTreeView)  //источник - TreeView

		{

			switch (pNotifMessageHeader->code)

			{

			case TVN_ITEMEXPANDING: //разворачивание или сворачивание узла



				SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)0, (LPARAM) "Scanning directory structure..."); //отображаем в строке состояния процесс поиска

				ptrNotifMessageTreeView = (LPNMTREEVIEW)lParam; //получаем указатель на узел

				if (ptrNotifMessageTreeView->action == TVE_EXPAND) //разворачивание узла

				{

					hSelectedItem = TreeView_GetChild(hwndTreeView, ptrNotifMessageTreeView->itemNew.hItem);  //берём первого потомка

					TV_Item.mask = TVIF_HANDLE | TVIF_TEXT | TVIF_IMAGE;

					TV_Item.hItem = hSelectedItem;

					TV_Item.pszText = LongPath;

					TV_Item.cchTextMax = 1000;

					TV_Item.iImage = (1);

					TV_Item.iSelectedImage = (0);

					TreeView_GetItem(hwndTreeView, &TV_Item);

					AddChildren(hwndTreeView, hSelectedItem, LongPath);



					hSelectedItem = TreeView_GetNextSibling(hwndTreeView, hSelectedItem); //берём следующий узел на данном уровне

					TV_Item.hItem = hSelectedItem;

					TV_Item.pszText = LongPath;

					TV_Item.cchTextMax = 1000;

					TV_Item.iImage = (1);

					TV_Item.iSelectedImage = (0);

					TreeView_GetItem(hwndTreeView, &TV_Item);



					while (hSelectedItem)

					{

						AddChildren(hwndTreeView, hSelectedItem, LongPath);

						hSelectedItem = TreeView_GetNextSibling(hwndTreeView, hSelectedItem); //берём следующий узел на данном уровне

						TV_Item.hItem = hSelectedItem;

						TV_Item.pszText = LongPath;

						TV_Item.iImage = (1);

						TV_Item.iSelectedImage = (0);

						TV_Item.cchTextMax = 1000;

						TreeView_GetItem(hwndTreeView, &TV_Item);

					}



				}



				if (ptrNotifMessageTreeView->action == TVE_COLLAPSE) //сворачивание узла

				{

					CollapseChildren(hwndTreeView, ptrNotifMessageTreeView->itemNew.hItem);

					hSelectedItem = TreeView_GetChild(hwndTreeView, ptrNotifMessageTreeView->itemNew.hItem);  //берём первого потомка



					while (hSelectedItem)

					{

						DelChildren(hwndTreeView, hSelectedItem);

						hSelectedItem = TreeView_GetNextSibling(hwndTreeView, hSelectedItem); //берём следующий узел на данном уровне

					}



				}



				SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)0 | 0, (LPARAM) "Ready"); //отображаем в строке состояния готовность

				break;



			case TVN_SELCHANGED: //выбор узла

				ptrNotifMessageTreeView = (LPNMTREEVIEW)lParam; //получаем указатель на узел

				hSelectedItem = ptrNotifMessageTreeView->itemNew.hItem;

				TV_Item.mask = TVIF_HANDLE | TVIF_TEXT | TVIF_IMAGE;

				TV_Item.hItem = hSelectedItem;

				TV_Item.pszText = strRootDrive;

				TV_Item.cchTextMax = 99;

				TV_Item.iImage = (1);

				TV_Item.iSelectedImage = (0);

				TreeView_GetItem(hwndTreeView, &TV_Item);
				char ddd[1024];

				strcpy(ddd, FindFullPath("", hwndTreeView, hSelectedItem));

				SetWindowText(hwndEdit, ddd);

				strcpy(CurrDir1, ddd);

				break;



			}

		}

		else if (hSender == hwndListView1)  //источник - ListView1

		{

			switch (((NMHDR*)lParam)->code)

			{

			case NM_DBLCLK:

				OnDblClick(hwndListView1, CurrDir1, himlSmall1);

				break;



			case NM_SETFOCUS:

				SetWindowText(hwndEdit, CurrDir1);

				SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_NEW, TRUE);

				if (ListView_GetSelectionMark(hwndListView1) != -1)

					Activate();

				break;



			case LVN_ITEMCHANGED:

				Activate();

				break;



			case NM_KILLFOCUS:

				DisActivate();

				SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_NEW, FALSE);

				break;



			case LVN_COLUMNCLICK:

				NMLISTVIEW *NMLV;

				NMLV = (NMLISTVIEW *)lParam;

				if (CurrDir1[0] != '\0')

					ListView_SortItems(hwndListView1, CompareFunc, NMLV->iSubItem);

				break;



			case LVN_ENDLABELEDIT:

				if (pdi->item.pszText != NULL)

				{

					ListView_GetItemText(hwndListView1, ListView_GetSelectionMark(hwndListView1), 0, csNameFile, 90);

					strcpy(csFirst, CurrDir1);

					strcat(csFirst, pdi->item.pszText);

					strcpy(pdi->item.pszText, csFirst);

					strcpy(csFirst, CurrDir1);

					strcat(csFirst, csNameFile);

					strcpy(csName, csFirst);

					ListView_GetItemText(hwndListView1, ListView_GetSelectionMark(hwndListView1), 1, csFirst, 90);

					if (strcmp(csFirst, csSDir) != 0)

					{

						strcat(pdi->item.pszText, ".");

						strcat(pdi->item.pszText, csFirst);

						strcat(csName, ".");

						strcat(csName, csFirst);

					}

					iError = rename(csName, pdi->item.pszText);

					if (iError == 0)  // --------------  EACCES 

					{

						if (strrchr(pdi->item.pszText, '.') != NULL)

							strrchr(pdi->item.pszText, '.')[0] = '\0';

						pdi->item.pszText = strrchr(pdi->item.pszText, '\\');

						for (int i = 1; pdi->item.pszText[i - 1] != '\0'; i++)

							pdi->item.pszText[i - 1] = pdi->item.pszText[i];

						ListView_SetItemText(hwndListView1, pdi->item.iItem, 0, pdi->item.pszText);

					}

					else

					{

						::MessageBox(NULL,

							"Невозможно задать такое  имя папки",

							"Ошибка",

							MB_ICONERROR | MB_OK | MB_TASKMODAL);

						strcpy(pdi->item.pszText, csNameFile);

					}

				}

				break;

			}



		}

		else if (hSender == hwndListView2)  //источник - ListView2

		{

			pdi = (LV_DISPINFO *)lParam;

			switch (((NMHDR*)lParam)->code)

			{

			case NM_DBLCLK:

				OnDblClick(hwndListView2, CurrDir2, himlSmall2);

				break;



			case NM_SETFOCUS:

				SetWindowText(hwndEdit, CurrDir2);

				SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_NEW, TRUE);

				if (ListView_GetSelectionMark(hwndListView2) != -1)

					Activate();

				break;



			case LVN_ITEMCHANGED:

				Activate();

				break;



			case NM_KILLFOCUS:

				DisActivate();

				SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_NEW, FALSE);

				break;



			case LVN_COLUMNCLICK:

				NMLISTVIEW *NMLV2;

				NMLV2 = (NMLISTVIEW *)lParam;

				if (CurrDir2[0] != '\0')

					ListView_SortItems(hwndListView2, CompareFunc, NMLV2->iSubItem);

				break;



			case LVN_ENDLABELEDIT:

				if (pdi->item.pszText != NULL)

				{

					ListView_GetItemText(hwndListView2, ListView_GetSelectionMark(hwndListView2), 0, csNameFile, 90);

					strcpy(csFirst, CurrDir2);

					strcat(csFirst, pdi->item.pszText);

					strcpy(pdi->item.pszText, csFirst);

					strcpy(csFirst, CurrDir2);

					strcat(csFirst, csNameFile);

					strcpy(csName, csFirst);

					ListView_GetItemText(hwndListView2, ListView_GetSelectionMark(hwndListView2), 1, csFirst, 90);

					if (strcmp(csFirst, csSDir) != 0)

					{

						strcat(pdi->item.pszText, ".");

						strcat(pdi->item.pszText, csFirst);

						strcat(csName, ".");

						strcat(csName, csFirst);

					}

					iError = rename(csName, pdi->item.pszText);

					if (iError == 0)  // --------------  EACCES 

					{

						if (strrchr(pdi->item.pszText, '.') != NULL)

							strrchr(pdi->item.pszText, '.')[0] = '\0';

						pdi->item.pszText = strrchr(pdi->item.pszText, '\\');

						for (int i = 1; pdi->item.pszText[i - 1] != '\0'; i++)

							pdi->item.pszText[i - 1] = pdi->item.pszText[i];

						ListView_SetItemText(hwndListView2, pdi->item.iItem, 0, pdi->item.pszText);

					}

					else

					{

						::MessageBox(NULL,

							"Невозможно задать такое  имя папки",

							"Ошибка",

							MB_ICONERROR | MB_OK | MB_TASKMODAL);

						strcpy(pdi->item.pszText, csNameFile);

					}

				}

				break;

			}



		}

		return 0;

		break;



	case WM_TIMER:



		SYSTEMTIME iTime;

		LPSTR timeget;

		GetLocalTime(&iTime);



		timeget = (LPSTR)GlobalAlloc(GPTR, 20);

		GetTimeFormat(

			LOCALE_SYSTEM_DEFAULT,              // locale

			LOCALE_NOUSEROVERRIDE | TIME_FORCE24HOURFORMAT,            // options

			NULL, // time

			NULL,         // time format string

			timeget,         // formatted string buffer

			20               // size of string buffer

			);



		SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)1 | 0, (LPARAM)(LPSTR)timeget);



		return 0;





		break;



	case WM_DESTROY:

		PostQuitMessage(0);

		break;

	default:

		return DefWindowProc(hwnd, message, wParam, lParam);

	}

	return 0;

}



LRESULT EditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)

{

	if (uMsg == WM_KEYDOWN && wParam == VK_RETURN)

	{

		GoTo(hwndListView1, CurrDir1, himlSmall1);

		return 0;

	}

	else

	{

		return CallWindowProc(hEditProc, hWnd, uMsg, wParam, lParam);

	};

};



void OnResize()

{

	RECT r;

	RECT cr;

	INT piParts[2];



	GetClientRect(mainhwnd, &cr);



	piParts[1] = cr.right - GetSystemMetrics(SM_CXVSCROLL);

	piParts[0] = piParts[1] - 80;



	SendMessage(hwndStatus, SB_SETPARTS, 2, (LPARAM)piParts);



	GetWindowRect(hwndToolBar, &r);

	cr.top += (r.bottom - r.top);

	GetWindowRect(hwndStatus, &r);

	cr.bottom -= (r.bottom - r.top);



	MoveWindow(hwndComboBox1, cr.left, cr.top, (cr.right - cr.left) / 2, cr.bottom - cr.top, TRUE);

	MoveWindow(hwndComboBox2, cr.left + (cr.right - cr.left) / 2, cr.top, (cr.right - cr.left) / 2, cr.bottom - cr.top, TRUE);

	GetWindowRect(hwndComboBox1, &r);

	cr.top += (r.bottom - r.top);

	GetWindowRect(hwndStatus, &r);

	cr.bottom -= (r.bottom - r.top);



	MoveWindow(hwndTreeView, cr.left, cr.top, (cr.right - cr.left) / 2, cr.bottom - cr.top, TRUE);

	MoveWindow(hwndListView1, cr.left, cr.top, (cr.right - cr.left) / 2, cr.bottom - cr.top, TRUE);

	ShowWindow(hwndListView1, MyTree ? SW_HIDE : SW_SHOW);

	ShowWindow(hwndTreeView, MyTree ? SW_SHOW : SW_HIDE);

	MoveWindow(hwndListView2, cr.left + (cr.right - cr.left) / 2, cr.top, (cr.right - cr.left) / 2, cr.bottom - cr.top, TRUE);

	MoveWindow(hwndEdit, cr.left + 2, cr.bottom, cr.right - cr.left - 2, 20, TRUE);

};



//помещает имена дисков в  ComboBox-ы

void DiskBrows()

{

	DWORD    dwDisks;

	TV_INSERTSTRUCT  TV_InsertStruct;

	TV_ITEM    TV_Item;

	dwDisks = GetLogicalDrives();  //получаем информацию о дисках

	TV_InsertStruct.hInsertAfter = TVI_SORT; //тип вставки - в алфавитном порядке

	TV_Item.mask = TVIF_TEXT;  //информация содержится в полях pszText и cchTextMax

	for (int i = 0; i < 26; i++)   //26 возможных логических дисков

	{



		if (dwDisks & FlagDisk[i].dwFlag)

		{

			SendMessage(hwndComboBox1, CB_ADDSTRING,

				0, (LPARAM)FlagDisk[i].cDisk

				);

			SendMessage(hwndComboBox2, CB_ADDSTRING,

				0, (LPARAM)FlagDisk[i].cDisk

				);

		}

	}

}

//////////////////////////////////////

////////Процедуры для TreeView////////

//////////////////////////////////////

void CreateFoldersOnDisk(HWND hwnd)

{

	TV_INSERTSTRUCT  TV_InsertStruct;

	TV_ITEM    TV_Item;

	DWORD    dwDisks;  //информация о дисках в системе

	WIN32_FIND_DATA  FileData; //данные о найденных файлах

	HANDLE    FileHandle; //хэндл найденных файлов

	char    FileName[260]; //имя файла



	SendMessage(hwndTreeView, TVM_DELETEITEM, 0, (LPARAM)(HTREEITEM)TVI_ROOT);





	dwDisks = GetLogicalDrives();  //получаем информацию о дисках

	TV_InsertStruct.hInsertAfter = TVI_SORT; //тип вставки - в алфавитном порядке

	TV_Item.mask = TVIF_TEXT | TVIF_IMAGE;  //информация содержится в полях pszText и cchTextMax

	TV_InsertStruct.hParent = TVI_ROOT;  //вставляем в корень



	TV_Item.pszText = CurentDiskName; //название диска

	TV_Item.cchTextMax = lstrlen(CurentDiskName);

	TV_Item.iImage = (1);

	TV_Item.iSelectedImage = (0);

	TV_InsertStruct.item = TV_Item;   //структура для вставки



	TV_InsertStruct.hParent = TreeView_InsertItem(hwndTreeView, &TV_InsertStruct);  //устанавливаем родителем элемента самого себя, чтобы вставлять на следующий уровень



	char cCurrDir[4];



	lstrcpy(cCurrDir, CurentDiskName);//создаём имя корневой директории





	if (!SetCurrentDirectory(cCurrDir)) //устанавливаем текущий диск

	{

		MessageBox(hwnd, "Cannot set current directory!", "Error", MB_OK);

	}



	FileHandle = FindFirstFile("*", &FileData); //ищем все файлы в текущей директории



	if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

	{

		lstrcpy(FileName, FileData.cFileName);

		TV_Item.mask = TVIF_TEXT | TVIF_IMAGE;  //информация содержится в полях pszText и cchTextMax

		TV_Item.pszText = FileName;   //текст для вставки

		TV_Item.cchTextMax = lstrlen(FileName);

		TV_Item.iImage = (1);

		TV_Item.iSelectedImage = (0);

		TV_InsertStruct.item = TV_Item;  //структура для вставки



		TreeView_InsertItem(hwndTreeView, &TV_InsertStruct);

	}



	while (FindNextFile(FileHandle, &FileData)) //продолжаем поиск

	{

		if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

		{

			lstrcpy(FileName, FileData.cFileName);

			TV_Item.mask = TVIF_TEXT | TVIF_IMAGE;  //информация содержится в полях pszText и cchTextMax

			TV_Item.pszText = FileName;   //текст для вставки

			TV_Item.cchTextMax = lstrlen(FileName);

			TV_Item.iImage = (1);

			TV_Item.iSelectedImage = (0);

			TV_InsertStruct.item = TV_Item;  //структура для вставки



			TreeView_InsertItem(hwndTreeView, &TV_InsertStruct);

		}

	}

};



LPSTR FindFullPath(LPSTR strDrive, HWND hwndTreeView, HTREEITEM htreeItem)

{

	char CurrText[200];

	char ParentText[200];

	TV_ITEM TV_Item;



	TV_Item.mask = TVIF_HANDLE | TVIF_TEXT | TVIF_IMAGE;

	TV_Item.hItem = htreeItem;

	TV_Item.pszText = CurrText;

	TV_Item.cchTextMax = 99;

	TV_Item.iImage = (1);

	TV_Item.iSelectedImage = (0);

	TreeView_GetItem(hwndTreeView, &TV_Item);



	for (int i = 0; i < 26; i++)

	{

		if (lstrcmp(CurrText, FlagDisk[i].cDisk) == 0)

			return CurrText;



	}



	char cTemp[200];



	lstrcpyn(cTemp, CurrText, 2);

	lstrcat(cTemp, '\0');



	if (lstrcmp(cTemp, "\\") != 0) //если выбран файл, то добавляем слэш в начало

	{

		lstrcpy(cTemp, "\\");

		lstrcat(cTemp, CurrText);

		lstrcpy(CurrText, cTemp);

	}



	TV_Item.pszText = ParentText;

	TV_Item.hItem = TreeView_GetParent(hwndTreeView, TV_Item.hItem);

	TV_Item.iImage = (1);

	TV_Item.iSelectedImage = (0);

	TreeView_GetItem(hwndTreeView, &TV_Item);



	lstrcat(FindFullPath(CurrText, hwndTreeView, TV_Item.hItem), CurrText);

}



bool AddChildren(HWND hwndTreeView, HTREEITEM hTreeItem, LPCSTR ParentDir)

{

	char    cCurrDir[1000];  //текущий путь

	char    FileName[1000];  //имя файла

	char    tmpParentDir[1000];

	WIN32_FIND_DATA  FileData;   //данные о найденных файлах

	HANDLE    FileHandle;   //хэндл найденных файлов

	TV_INSERTSTRUCT  TV_InsertStruct; //структура для вставки

	TV_ITEM    TV_Item;   //содержимое вставляемого элемента



	lstrcpy(tmpParentDir, ParentDir);



	for (int i = 0; i < 26; i++)

	{

		if (lstrcmp(tmpParentDir, FlagDisk[i].cDisk) == 0)

		{

			lstrcat(tmpParentDir, "\\");  //создаём имя корневой директории

		}

	}



	lstrcpy(cCurrDir, FindFullPath(tmpParentDir, hwndTreeView, hTreeItem));



	if (!SetCurrentDirectory(cCurrDir)) //устанавливаем текущую директорию

		return false;



	FileHandle = FindFirstFile("*", &FileData); //ищем все файлы в текущей директории



	if (FileHandle == INVALID_HANDLE_VALUE) //текущая директоря пустая

		return true;



	if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) //если файл является директорией

	{

		lstrcpy(FileName, FileData.cFileName);

		TV_InsertStruct.hInsertAfter = TVI_SORT; //тип вставки - в алфавитном порядке

		TV_InsertStruct.hParent = hTreeItem;  //элемент, который будет являться родителем вставляемых элементов

		TV_Item.mask = TVIF_TEXT | TVIF_IMAGE;   //информация содержится в полях pszText и cchTextMax



		if ((lstrcmp(FileName, ".") != 0) && (lstrcmp(FileName, "..") != 0))

		{

			TV_Item.pszText = FileName;   //текст для вставки

			TV_Item.cchTextMax = lstrlen(FileName);

			TV_Item.iImage = (1);

			TV_Item.iSelectedImage = (0);

			TV_InsertStruct.item = TV_Item;  //структура для вставки

			TreeView_InsertItem(hwndTreeView, &TV_InsertStruct);

		}

	}

	while (FindNextFile(FileHandle, &FileData)) //продолжаем поиск

	{

		if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) //если файл является директорией

		{

			lstrcpy(FileName, FileData.cFileName);



			TV_InsertStruct.hInsertAfter = TVI_SORT; //тип вставки - в алфавитном порядке

			TV_InsertStruct.hParent = hTreeItem;  //элемент, который будет являться родителем вставляемых элементов

			TV_Item.mask = TVIF_TEXT | TVIF_IMAGE;   //информация содержится в полях pszText и cchTextMax



			if (lstrcmp(FileName, ".") != 0 && lstrcmp(FileName, "..") != 0)

			{

				TV_Item.pszText = FileName;   //текст для вставки

				TV_Item.cchTextMax = lstrlen(FileName);

				TV_Item.iImage = (1);

				TV_Item.iSelectedImage = (0);

				TV_InsertStruct.item = TV_Item;  //структура для вставки

				TreeView_InsertItem(hwndTreeView, &TV_InsertStruct);

			}

		}

	}



	FindClose(FileHandle);

	return true;

}



bool DelChildren(HWND hwndTreeView, HTREEITEM hTreeItem)

{

	HTREEITEM   hItem;



	hItem = TreeView_GetChild(hwndTreeView, hTreeItem);  //берём потомка



	if (!hItem && !hTreeItem) //нет потомков

		return false;



	while (hItem) //пока не удалим всех потомков

	{

		TreeView_DeleteItem(hwndTreeView, hItem);

		hItem = TreeView_GetChild(hwndTreeView, hTreeItem);  //берём потомка

	}

	return true;

}



bool CollapseChildren(HWND hwndTreeView, HTREEITEM hTreeItem)

{

	HTREEITEM hItem;



	hItem = TreeView_GetChild(hwndTreeView, hTreeItem);  //берём потомка

	if (hItem)

		CollapseChildren(hwndTreeView, hItem);



	TreeView_Expand(hwndTreeView, hItem, TVE_COLLAPSE);



	hItem = TreeView_GetNextSibling(hwndTreeView, hTreeItem);  //берём потомка

	if (hItem)

		CollapseChildren(hwndTreeView, hItem);



	TreeView_Expand(hwndTreeView, hItem, TVE_COLLAPSE);



	return true;

}

////////////////////////////////////////////////////////

/////////Процедуры для ListView/////////////////////////

////////////////////////////////////////////////////////







void FillListView(HWND hwndlv, LPCSTR ParentDir, HIMAGELIST himlSmall)

{

	WIN32_FIND_DATA FileData;

	char DirName[1024];

	SHFILEINFO fi;

	HICON hIcon;



	int count = ListView_GetItemCount(hwndlv);

	for (int i = 0; i < count; i++)

	{

		LVITEM lvi;

		lvi.mask = LVIF_PARAM;

		lvi.iItem = i;

		lvi.iSubItem = 0;

		ListView_GetItem(hwndlv, &lvi);

		delete (void*)lvi.lParam;

	};



	SendMessage(hwndlv, LVM_DELETEALLITEMS, 0l, 0);



	SetCurrentDirectory(ParentDir);

	ImageList_SetImageCount(himlSmall, 3);

	HANDLE hFile = FindFirstFile("*", &FileData);

	LV_ITEM item;

	int d = 0;



	DisActivate();

	if (hFile != INVALID_HANDLE_VALUE)

	{

		SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)0, (LPARAM) "Scanning directory structure..."); //отображаем в строке состояния процесс поиска

		item.iItem = 0;

		// Вставляем строки



		char csText[256];

		char csCopyText[256];

		SYSTEMTIME stTime;



		do

		{

			WIN32_FIND_DATA * pData = new WIN32_FIND_DATA;

			*pData = FileData;

			item.mask = LVIF_IMAGE | LVIF_TEXT | LVIF_PARAM;

			if (strcmp(FileData.cFileName, ".") != 0 && lstrcmp(FileData.cFileName, "..") != 0)

			{

				//////////////////item0/////////////////////

				item.iSubItem = 0;

				if (FileData.dwFileAttributes &   FILE_ATTRIBUTE_DIRECTORY)

				{

					item.pszText = FileData.cFileName;

					strcpy(DirName, ParentDir);

					strcat(DirName, FileData.cFileName);

					strcat(DirName, "\\");

					if (GetFolderSize(DirName) < 1450000)

					{



						item.iImage = a;

					}

					else

						item.iImage = b;

					SetCurrentDirectory(ParentDir);

				}

				else

				{

					SHGetFileInfo(FileData.cFileName, 0, &fi, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_SMALLICON);

					d = ImageList_AddIcon(himlSmall, fi.hIcon);

					//DestroyIcon(hIcon);

					if (strrchr(FileData.cFileName, '.') != NULL)

					{

						strcpy(csCopyText, FileData.cFileName);

						strrchr(csCopyText, '.')[0] = '\0';

						item.pszText = csCopyText;

					}

					else

						item.pszText = FileData.cFileName;

					item.iImage = d;



				}





				item.lParam = (LPARAM)pData;

				ListView_InsertItem(hwndlv, &item);



				//////////////////item1/////////////////////

				item.iSubItem = 1;

				item.mask = LVIF_TEXT;

				if (FileData.dwFileAttributes &   FILE_ATTRIBUTE_DIRECTORY)

					strcpy(csText, "<DIR>");

				else

				{

					if (strchr(FileData.cFileName, '.') == NULL)

					{

						strcpy(csText, "<?>");

					}

					else

						strcpy(csText, strrchr(FileData.cFileName, '.') + 1);

				}

				item.pszText = (LPTSTR)(LPCTSTR)csText;

				ListView_SetItem(hwndlv, &item);

				//////////////////item2/////////////////////

				item.iSubItem = 2;

				if (FileData.dwFileAttributes &  FILE_ATTRIBUTE_DIRECTORY)

					strcpy(csText, "");

				else

				if (FileData.nFileSizeLow < 1024)

					wsprintf(csText, "%d b", FileData.nFileSizeLow);

				else

					wsprintf(csText, "%d Kb", FileData.nFileSizeLow / 1024);

				item.pszText = (LPTSTR)(LPCTSTR)csText;

				ListView_SetItem(hwndlv, &item);

				//////////////////item3/////////////////////

				item.iSubItem = 3;

				FILETIME ft = FileData.ftLastWriteTime;

				FileTimeToLocalFileTime(&ft, &ft);

				FileTimeToSystemTime(&ft, &stTime);

				wsprintf(csText,

					"%02d.%02d.%04d %02d:%02d", stTime.wDay, stTime.wMonth, stTime.wYear,

					stTime.wHour, stTime.wMinute);

				item.pszText = (LPTSTR)(LPCTSTR)csText;

				ListView_SetItem(hwndlv, &item);

				item.iItem++;

			}

			if (lstrcmp(FileData.cFileName, "..") == 0)

			{

				item.iSubItem = 0;

				item.iImage = c;
				item.pszText = "..";

				item.lParam = (LPARAM)pData;

				ListView_InsertItem(hwndlv, &item);

				item.mask = LVIF_TEXT;

				item.iSubItem = 1;

				item.pszText = "<DIR>";

				ListView_SetItem(hwndlv, &item);

				item.iSubItem = 2;

				item.pszText = " ";

				ListView_SetItem(hwndlv, &item);

				item.iSubItem = 3;

				item.pszText = " ";

				ListView_SetItem(hwndlv, &item);

				item.iItem++;

			}

		}

		while (FindNextFile(hFile, &FileData));

	}

	FindClose(hFile);

	SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)0, (LPARAM) "Ready"); //отображаем в строке состояния готовность

}



unsigned long GetFolderSize(LPCSTR ParentDir)

{

	WIN32_FIND_DATA FData;

	SetCurrentDirectory(ParentDir);

	HANDLE h_File = FindFirstFile("*", &FData);



	if (h_File != INVALID_HANDLE_VALUE)

	{

		do

		{

			if (lstrcmp(FData.cFileName, "..") != 0 && strcmp(FData.cFileName, ".") != 0)

			{

				if (FData.dwFileAttributes &   FILE_ATTRIBUTE_DIRECTORY)

				{

					strcpy(DirName, ParentDir);

					strcat(DirName, FData.cFileName);

					strcat(DirName, "\\");

					if (strlen(DirName) < 1024)

					{

						ChSize = GetFolderSize(DirName);

						SetCurrentDirectory(ParentDir);

					}

					else

						ChSize = 9999999;

					if (ChSize > 1450000)

						return 9999999;

				}

				else

				{

					ChSize = ChSize + FData.nFileSizeLow;

					if (ChSize > 1450000)

						return 9999999;

				}

			}

		}

		while (FindNextFile(h_File, &FData));

	}

	FindClose(h_File);

	return ChSize;

}



void OnDblClick(HWND hwndlv, char* CurrentDirectory, HIMAGELIST himlSmall)

{

	char csSDir[] = "<DIR>";

	char csName[128];

	char csCopy[1024];

	char CopyCurrDir[1024];

	int iError;

	int iNumber;

	strcpy(CopyCurrDir, CurrentDirectory);

	iNumber = ListView_GetNextItem(hwndlv, -1, LVNI_SELECTED);

	ListView_GetItemText(hwndlv, iNumber, 1, csName, 80);

	if (strcmp(csName, csSDir) == 0)

	{

		ListView_GetItemText(hwndlv, iNumber, 0, csName, 80);

		if (strcmp(csName, "..") != 0)

		{

			//открываем подпапку

			strcpy(csCopy, CurrentDirectory);

			strcat(csCopy, csName);

			strcat(csCopy, "\\");

			strcpy(CurrentDirectory, csCopy);

		}

		else

		{

			//возвращаемся на уровень выше

			char* rez;

			int irez;

			CurrentDirectory[strlen(CurrentDirectory) - 1] = 0;

			rez = strrchr(CurrentDirectory, '\\');

			irez = rez - CurrentDirectory + 1;

			CurrentDirectory[irez] = 0;

		}

		iError = SetCurrentDirectory(CurrentDirectory);

		if (iError != 0)

		{

			FillListView(hwndlv, CurrentDirectory, himlSmall);

			SetWindowText(hwndEdit, CurrentDirectory);

		}

		else

		{

			MessageBox(NULL,

				"Не удалось открыть папку",

				"Ошибка",

				MB_ICONERROR | MB_OK | MB_TASKMODAL);

			strcpy(CurrentDirectory, CopyCurrDir);

		}



	}

	else

	{

		ListView_GetItemText(hwndlv, iNumber, 0, csName, 80);

		strcpy(csCopy, CurrentDirectory);

		strcat(csCopy, csName);

		strcat(csCopy, ".");

		ListView_GetItemText(hwndlv, ListView_GetSelectionMark(hwndlv), 1, csName, 90);

		strcat(csCopy, csName);

		ShellExecute(mainhwnd, NULL, csCopy, NULL, NULL, SW_SHOWNORMAL);

	}



}



int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)

{

	char *cs1, *cs2;

	WIN32_FIND_DATA *item1;

	item1 = (WIN32_FIND_DATA *)lParam1;

	WIN32_FIND_DATA *item2;

	item2 = (WIN32_FIND_DATA *)lParam2;

	int rez;

	switch (lParamSort)

	{

	case 0:

		if (lstrcmpi(item1->cFileName, "..") == 0)

			rez = -1;

		else

		if (lstrcmpi(item2->cFileName, "..") == 0)

			rez = 1;

		else

		if ((item1->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&

			(item2->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))

			rez = strcmpi((item1->cFileName), (item2->cFileName));

		else

		{

			if (item1->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

				rez = -1;

			else

			if (item2->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

				rez = 1;

			else

				rez = strcmpi((item1->cFileName), (item2->cFileName));

		}

		return rez;

		break;

	case 1:

		if (lstrcmpi(item1->cFileName, "..") == 0)

			rez = -1;

		else

		if (lstrcmpi(item2->cFileName, "..") == 0)

			rez = 1;

		else

		if (!(item1->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&

			!(item2->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))

		{

			cs1 = strrchr(item1->cFileName, '.');

			cs2 = strrchr(item2->cFileName, '.');

			if ((cs1 != NULL) && (cs2 != NULL))

			{

				cs1 = _strlwr(cs1);

				cs2 = _strlwr(cs2);

				rez = strcmp(cs1, cs2);

			}

			else

			if ((cs1 == NULL)&&(cs2 != NULL))

				rez = -1;

			else

			if ((cs2 == NULL)&&(cs1 != NULL))

				rez = 1;

			else

				rez = 0;

		}

		else

		{

			if (item1->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

				rez = -1;

			else

			if (item2->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

				rez = 1;

		}



		return rez;

		break;

	case 2:

		if (lstrcmpi(item1->cFileName, "..") == 0)

			rez = -1;

		else

		if (lstrcmpi(item2->cFileName, "..") == 0)

			rez = 1;

		else

		if (!(item1->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&

			!(item2->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))

			rez = item1->nFileSizeLow - item2->nFileSizeLow;

		else

		{

			if (item1->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

				rez = -1;

			else

			if (item2->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

				rez = 1;

		}

		return rez;

		break;

	case 3:

		if (lstrcmpi(item1->cFileName, "..") == 0)

			rez = -1;

		else

		if (lstrcmpi(item2->cFileName, "..") == 0)

			rez = 1;

		else

		if ((item1->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&

			(item2->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))

			rez = CompareFileTime(&item1->ftLastWriteTime, &item2->ftLastWriteTime);

		else

		{

			if (item1->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

				rez = -1;

			else

			if (item2->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

				rez = 1;

			else

				rez = CompareFileTime(&item1->ftLastWriteTime, &item2->ftLastWriteTime);

		}

		return rez;

		break;

	default:

		return 0;

	};



}



//Проверка диска во флопике

BOOL IsDiskInDrive(LPTSTR lpszDrive)

{

	UINT errmode;

	TCHAR szVolName[256];

	DWORD dwMaxComSize;

	DWORD dwFlags;

	TCHAR szFS[256];

	BOOL bRes;



	errmode = SetErrorMode(SEM_FAILCRITICALERRORS);

	//если не сделать SetErrorMode - выскочит стандартное окошко "Drive Not Ready"

	bRes = GetVolumeInformation(lpszDrive,

		szVolName,

		sizeof(szVolName),

		NULL,

		&dwMaxComSize,

		&dwFlags,

		szFS,

		sizeof(szFS));

	SetErrorMode(errmode);

	return bRes;

}



void RefreshComboInf(HWND hwndCombo) //считывание выбранного элемента

{

	ComboInd = SendMessage(

		(HWND)hwndCombo,        // handle to destination window 

		CB_GETCURSEL,       // message to send

		0,    // not used; must be zero

		0     // not used; must be zero

		);



	SendMessage(

		(HWND)hwndCombo,       // handle to destination window 

		CB_GETLBTEXT,    // message to send

		(WPARAM)ComboInd,   // item index

		LPARAM(CurentDiskName)    // not used; must be zero

		);

}



void CreateNewFolder(HWND hwndlv, LPCSTR CurrDir, HIMAGELIST himlSmall)

{

	char csName[256], csN[6], csN2[256];

	int hope;

	strcpy(csName, CurrDir);

	strcat(csName, "New Floder");

	strcpy(csN2, csName);

	int iError = 0;

	for (hope = 0; (hope < 101)&&(iError == 0); hope++)

	{

		iError = CreateDirectory(csN2, NULL);

		if (iError == 0)

		{

			strcpy(csN, "(");

			wsprintf(csN2, "%d", hope);

			strcat(csN, csN2);

			strcat(csN, ")");

			strcpy(csN2, csName);

			strcat(csN2, csN);

		}

	}

	if (iError != 0)

	{

		if (strcmp(CurrDir1, CurrDir2) == 0)

		{

			FillListView(hwndListView1, CurrDir1, himlSmall1);

			FillListView(hwndListView2, CurrDir2, himlSmall2);

		}

		else

			FillListView(hwndlv, CurrDir, himlSmall);

	}

	else

		MessageBox(NULL,

		"Неудалось создать новую  папку",

		"Ошибка",

		MB_ICONERROR | MB_OK | MB_TASKMODAL);

}



void DeleteFile(HWND hwndlv, LPCSTR CurrDir)

{

	char csName[256], csFirst[256], csSDir[] = "<DIR>", csNameFile[256];

	int iError;

	SHFILEOPSTRUCT *lpFileOp;

	ListView_GetItemText(hwndlv, ListView_GetSelectionMark(hwndlv), 0, csFirst, 90);

	ListView_GetItemText(hwndlv, ListView_GetSelectionMark(hwndlv), 1, csNameFile, 90);

	strcpy(csName, CurrDir);

	strcat(csName, csFirst);

	if (strcmp(csNameFile, csSDir) != 0)

	{

		strcat(csName, ".");

		strcat(csName, csNameFile);

	}

	csName[strlen(csName) + 1] = '\0';

	lpFileOp = new(SHFILEOPSTRUCT);

	lpFileOp->hwnd = mainhwnd;

	lpFileOp->wFunc = FO_DELETE;

	lpFileOp->pFrom = csName;

	lpFileOp->pTo = NULL;

	lpFileOp->fFlags = FOF_CONFIRMMOUSE | FOF_ALLOWUNDO;

	iError = SHFileOperation(lpFileOp);

	if ((iError == 0)&&(lpFileOp->fAnyOperationsAborted == 0))

	{

		if (strcmp(CurrDir1, CurrDir2) == 0)

		{

			FillListView(hwndListView1, CurrDir1, himlSmall1);

			FillListView(hwndListView2, CurrDir2, himlSmall2);

		}

		else

			ListView_DeleteItem(hwndlv, ListView_GetSelectionMark(hwndlv));

	}

}



void Renamefile(HWND hwndlv)

{

	ListView_EditLabel(hwndlv, ListView_GetSelectionMark(hwndlv));

}



void CopyFile(HWND hwndlv1, HWND hwndlv2, LPCSTR CurrD1, LPCSTR CurrD2, HIMAGELIST himlSmall)

{

	char csName[256], csFirst[256], csSDir[] = "<DIR>", csNameFile[256];

	char csNF[90];

	ListView_GetItemText(hwndlv1, ListView_GetSelectionMark(hwndlv1), 0, csFirst, 90);

	ListView_GetItemText(hwndlv1, ListView_GetSelectionMark(hwndlv1), 1, csNameFile, 90);

	strcpy(csName, CurrD1);

	strcat(csName, csFirst);

	strcpy(csNF, csFirst);

	if (strcmp(csNameFile, csSDir) != 0)

	{

		strcat(csName, ".");

		strcat(csName, csNameFile);

		strcat(csNF, ".");

		strcat(csNF, csNameFile);

	}

	csName[strlen(csName) + 1] = '\0';



	PasteFile(hwndlv1, hwndlv2, CurrD2, himlSmall, csName, csNF, 0, 0);

}



void CutFile(HWND hwndlv1, HWND hwndlv2, LPCSTR CurrD1, LPCSTR CurrD2, HIMAGELIST himlSmall)

{

	char csName[256], csFirst[256], csSDir[] = "<DIR>", csNameFile[256];

	char csNF[90];

	int index;

	ListView_GetItemText(hwndlv1, ListView_GetSelectionMark(hwndlv1), 0, csFirst, 90);

	ListView_GetItemText(hwndlv1, ListView_GetSelectionMark(hwndlv1), 1, csNameFile, 90);

	strcpy(csName, CurrD1);

	strcat(csName, csFirst);

	strcpy(csNF, csFirst);

	if (strcmp(csNameFile, csSDir) != 0)

	{

		strcat(csName, ".");

		strcat(csName, csNameFile);

		strcat(csNF, ".");

		strcat(csNF, csNameFile);

	}

	csName[strlen(csName) + 1] = '\0';

	index = ListView_GetSelectionMark(hwndlv1);

	PasteFile(hwndlv1, hwndlv2, CurrD2, himlSmall, csName, csNF, 1, index);

}



void PasteFile(HWND hwndlv1, HWND hwndlv2, LPCSTR CurrDir,

	HIMAGELIST himlSmall, LPCSTR csFileNameCopy, LPCSTR csNF, bool cut, int index)

{

	char csName[256], csFirst[256], csSDir[] = "<DIR>", csNameFile[256];

	SHFILEOPSTRUCT *lpFileOp;

	int iError;

	strcpy(csNameFile, CurrDir);

	strcat(csNameFile, csNF);

	csNameFile[strlen(csNameFile) + 1] = '\0';

	lpFileOp = new(SHFILEOPSTRUCT);

	lpFileOp->hwnd = mainhwnd;

	lpFileOp->pFrom = csFileNameCopy;

	lpFileOp->pTo = csNameFile;

	lpFileOp->fFlags = FOF_ALLOWUNDO;

	if (cut)

		lpFileOp->wFunc = FO_MOVE;

	else

		lpFileOp->wFunc = FO_COPY;

	iError = SHFileOperation(lpFileOp);

	if ((iError == 0)&&(!lpFileOp->fAnyOperationsAborted))

	{

		FillListView(hwndlv2, CurrDir, himlSmall);

		if (cut)

			ListView_DeleteItem(hwndlv1, index);

	}

}



void GoTo(HWND hwndlv, char* CurrentDirectory, HIMAGELIST himlSmall)//передаётся папка до переходаб чтобы можно было откатить

{

	char csText[256];

	int iError;

	GetWindowText(hwndEdit, csText, 256);

	if (csText[strlen(csText) - 1] != '\\')

		strcat(csText, "\\");

	iError = SetCurrentDirectory(csText);

	if (iError != 0)

	{

		strcpy(CurrentDirectory, csText);

		FillListView(hwndlv, CurrentDirectory, himlSmall);

		SetWindowText(hwndEdit, CurrentDirectory);

	}

	else

	{

		MessageBox(NULL,

			"Не удалось открыть папку",

			"Ошибка",

			MB_ICONERROR | MB_OK | MB_TASKMODAL);

		SetWindowText(hwndEdit, CurrentDirectory);

	}

}

void Activate()

{

	SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_NEW, TRUE);

	SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_COPY, TRUE);

	SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_MOVE, TRUE);

	SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_RENAME, TRUE);

	SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_DELETE, TRUE);



	EnableMenuItem(hMenu, IDM_MKDIR, MF_ENABLED);

	EnableMenuItem(hMenu, IDM_COPY, MF_ENABLED);

	EnableMenuItem(hMenu, IDM_MOVE, MF_ENABLED);

	EnableMenuItem(hMenu, IDM_RENAME, MF_ENABLED);

	EnableMenuItem(hMenu, IDM_DELETE, MF_ENABLED);

}

void DisActivate()

{

	SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_NEW, FALSE);

	SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_COPY, FALSE);

	SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_MOVE, FALSE);

	SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_RENAME, FALSE);

	SendMessage(hwndToolBar, TB_ENABLEBUTTON, IDI_DELETE, FALSE);



	EnableMenuItem(hMenu, IDM_MKDIR, MF_GRAYED);

	EnableMenuItem(hMenu, IDM_COPY, MF_GRAYED);

	EnableMenuItem(hMenu, IDM_MOVE, MF_GRAYED);

	EnableMenuItem(hMenu, IDM_RENAME, MF_GRAYED);

	EnableMenuItem(hMenu, IDM_DELETE, MF_GRAYED);

}

 