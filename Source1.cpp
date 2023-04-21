#include "stdafx.h"
#include "olegdi+.h"
CDlgPrintSetup::CDlgPrintSetup(LPRECT p){    m_hDlg = NULL;    m_pRect = p;}
CDlgPrintSetup::~CDlgPrintSetup(){}
int CDlgPrintSetup::Create(HWND hwndParent){
	HINSTANCE hInst;
	hInst = (HINSTANCE)GetModuleHandle(NULL);
	return DialogBoxParam(hInst,MAKEINTRESOURCE(IDD_PRINTSETUP),hwndParent,
	DlgProc,(LPARAM)this);
}
BOOL CALLBACK CDlgPrintSetup::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    if(message==WM_INITDIALOG)        SetWindowLong(hwnd,-21,lParam);    
    CDlgPrintSetup *pDlg = (CDlgPrintSetup*)GetWindowLong(hwnd,-21);    
    if(!pDlg)       return FALSE;    
    switch(message)    {
        case WM_INITDIALOG:         return pDlg->MsgInitDialog(hwnd,wParam,lParam);
        case WM_COMMAND:            return pDlg->MsgCommand(hwnd,wParam,lParam);        
        case WM_VSCROLL:            return pDlg->MsgVScroll(hwnd,wParam,lParam); 
        case WM_SYSCOMMAND:         return pDlg->MsgSysCommand(wParam);
    }
    return FALSE;
}
BOOL CDlgPrintSetup::MsgInitDialog(HWND hwnd, WPARAM wParam, LPARAM lParam){    
    int i, j;
    m_hDlg = hwnd;        
    for(i = IDC_UD_LEFT, j=0; i<=IDC_UD_HEIGHT; i++, j++)    {
        SendDlgItemMessage(hwnd, i, UDM_SETBUDDY, (WPARAM)GetDlgItem(hwnd, i-4), 0);
        SendDlgItemMessage(hwnd, i-4, EM_LIMITTEXT, 3, 0);
        SendDlgItemMessage(hwnd, i, UDM_SETRANGE, 0, MAKELONG(cstMargin[j][1],cstMargin[j][0]));
    }
    m_pRect->left = max(cstMargin[0][0], min(cstMargin[0][1], m_pRect->left));
    m_pRect->top = max(cstMargin[1][0], min(cstMargin[1][1], m_pRect->top));
    m_pRect->right = max(cstMargin[2][0], min(cstMargin[2][1], m_pRect->right));
    m_pRect->bottom = max(cstMargin[3][0], min(cstMargin[3][1], m_pRect->bottom));
    SendDlgItemMessage(hwnd, IDC_UD_LEFT, UDM_SETPOS, 0, MAKELONG(m_pRect->left,0));
    SetDlgItemInt(hwnd, IDC_EDIT_LEFT, m_pRect->left, FALSE);
    SendDlgItemMessage(hwnd, IDC_UD_TOP, UDM_SETPOS, 0, MAKELONG(m_pRect->top,0));
    SetDlgItemInt(hwnd, IDC_EDIT_TOP, m_pRect->top, FALSE);
    SendDlgItemMessage(hwnd, IDC_UD_WIDTH, UDM_SETPOS, 0, MAKELONG(m_pRect->right,0));
    SetDlgItemInt(hwnd, IDC_EDIT_WIDTH, m_pRect->right, FALSE);
    SendDlgItemMessage(hwnd, IDC_UD_HEIGHT, UDM_SETPOS, 0, MAKELONG(m_pRect->bottom,0));
    SetDlgItemInt(hwnd, IDC_EDIT_HEIGHT, m_pRect->bottom, FALSE);
    return FALSE;
}
BOOL CDlgPrintSetup::MsgVScroll(HWND hwnd, WPARAM wParam, LPARAM lParam){
    int id = GetWindowLong((HWND)lParam, GWL_ID);
    if((id<IDC_UD_LEFT)||(id>IDC_UD_HEIGHT)) return FALSE;
    if(LOWORD(wParam)==SB_THUMBPOSITION)  SetDlgItemInt(hwnd, id-4, HIWORD(wParam), FALSE);        
    return FALSE;
}
BOOL CDlgPrintSetup::MsgCommand(HWND hwnd, WPARAM wParam, LPARAM lParam){    
    int val;
    switch(LOWORD(wParam))    {
        case IDC_EDIT_LEFT:		if(HIWORD(wParam)==EN_KILLFOCUS) {val = GetDlgItemInt(hwnd, LOWORD(wParam), NULL, TRUE);m_pRect->left = max(cstMargin[0][0], min(cstMargin[0][1], val));SendDlgItemMessage(hwnd, IDC_UD_LEFT, UDM_SETPOS, 0, MAKELONG(m_pRect->left,0));SetDlgItemInt(hwnd, IDC_EDIT_LEFT, m_pRect->left, FALSE);}  break;
        case IDC_EDIT_TOP:      if(HIWORD(wParam)==EN_KILLFOCUS) {val = GetDlgItemInt(hwnd, LOWORD(wParam), NULL, TRUE);m_pRect->top = max(cstMargin[1][0], min(cstMargin[1][1], val));SendDlgItemMessage(hwnd, IDC_UD_TOP, UDM_SETPOS, 0, MAKELONG(m_pRect->top,0));SetDlgItemInt(hwnd, IDC_EDIT_TOP, m_pRect->top, FALSE);}break;
        case IDC_EDIT_WIDTH:    if(HIWORD(wParam)==EN_KILLFOCUS) {val = GetDlgItemInt(hwnd, LOWORD(wParam), NULL, TRUE);m_pRect->right = max(cstMargin[2][0], min(cstMargin[2][1], val));SendDlgItemMessage(hwnd, IDC_UD_WIDTH, UDM_SETPOS, 0, MAKELONG(m_pRect->right,0));SetDlgItemInt(hwnd, IDC_EDIT_WIDTH, m_pRect->right, FALSE);}break;
        case IDC_EDIT_HEIGHT:	if(HIWORD(wParam)==EN_KILLFOCUS) {val = GetDlgItemInt(hwnd, LOWORD(wParam), NULL, TRUE);m_pRect->bottom = max(cstMargin[3][0], min(cstMargin[3][1], val));SendDlgItemMessage(hwnd, IDC_UD_HEIGHT, UDM_SETPOS, 0, MAKELONG(m_pRect->bottom,0));SetDlgItemInt(hwnd, IDC_EDIT_HEIGHT, m_pRect->bottom, FALSE);}break;
        case IDOK:            CmdOk(hwnd);            break;
        case IDCANCEL:            EndDialog(m_hDlg, 0);
	}                            
    return FALSE;
}
BOOL CDlgPrintSetup::MsgSysCommand(WPARAM wParam){ switch(LOWORD(wParam)){case SC_CLOSE:EndDialog(m_hDlg, 0);return TRUE;  }return FALSE;}
void CDlgPrintSetup::CmdOk(HWND hwnd){
    m_pRect->left = GetDlgItemInt(hwnd, IDC_EDIT_LEFT, NULL, TRUE);
    m_pRect->top = GetDlgItemInt(hwnd, IDC_EDIT_TOP, NULL, TRUE);
    m_pRect->right = GetDlgItemInt(hwnd, IDC_EDIT_WIDTH, NULL, TRUE);
    m_pRect->bottom = GetDlgItemInt(hwnd, IDC_EDIT_HEIGHT, NULL, TRUE);
    EndDialog(m_hDlg, 1);
}
int InsererControleCodeBarre(HINSTANCE hExterne, HWND hConteneur, COLORREF CouleurCB, HBRUSH Arrierplan){
	hCBArrierplan=Arrierplan;
	hCBConteneur=hConteneur;
	hCBExterne=hExterne;
	hCouleurCB= CouleurCB;
	return 0;
}

LRESULT CALLBACK ModuleCBProcedure(HWND hDlg , UINT Message, WPARAM wParam, LPARAM lParam){
	HDC hStatic = (HDC)wParam;
    switch (Message)    {
		case WM_CREATE:{
			LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
			SetWindowLong(hDlg, -21,(LONG)lpcs->lpCreateParams);
				SendMessage(hDlg, WM_SETFONT, (WPARAM)GetStockObject(18), 1L);
				}break;
        
        case WM_DESTROY:{
            PostQuitMessage (0);
            }break;
       case WM_COMMAND:{
		char szBuf[256];
		int digit;
			switch(LOWORD(wParam))			{
				case IDC_DECODE:{
						GetDlgItemText(hDlg, IDC_EDIT, szBuf, 255);
					m_bitSize = Decode(szBuf);
					InvalidateRect(GetDlgItem(hDlg, IDC_IMAGE), NULL, TRUE);
					EnableWindow(GetDlgItem(hDlg, IDC_BINARY), (BOOL)m_bitSize);
					for(int i=IDC_PRINT; i<=IDC_VZOOMDOWN; i++)
						EnableWindow(GetDlgItem(hDlg, i),(BOOL)m_bitSize );
					SetResultCode(hDlg);
					if(!m_bitSize)
						MessageBox(hDlg,ErrorString(GetAppLastError()),"Integration Module CodeBarre", 64);            
						}break;
				case IDC_BINARY:
					GetDlgItemText(hDlg, IDC_BINARY, szBuf, 64);
					if(!lstrcmp(szBuf, TEXT_BTN1))
						SetDlgItemText(hDlg, IDC_BINARY, TEXT_BTN2);
					else
						SetDlgItemText(hDlg, IDC_BINARY, TEXT_BTN1);
					SetResultCode(hDlg);
					break;
				case IDC_CHECKDIGIT:
					GetDlgItemText(hDlg, IDC_EDIT, szBuf, 255);
					digit = CheckDigit(szBuf, FALSE);
					wsprintf(szBuf, "Le checkdigit est %i", digit);
					MessageBox(hDlg, szBuf, "Integration Module CodeBarre", 64);
					break;
				case IDC_HZOOMUP:
					m_step = min(4, m_step+1);
					InvalidateRect(GetDlgItem(hDlg, IDC_IMAGE), NULL, TRUE);
					if(!IsWindowEnabled(GetDlgItem(hDlg, IDC_COPY)))
						EnableWindow(GetDlgItem(hDlg, IDC_COPY), TRUE);
						EnableWindow(GetDlgItem(hDlg, IDC_FILEHELP), TRUE);
					break;
				case IDC_HZOOMDOWN:
					m_step = max(1, m_step-1);
					InvalidateRect(GetDlgItem(hDlg, IDC_IMAGE), NULL, TRUE);
					if(!IsWindowEnabled(GetDlgItem(hDlg, IDC_COPY)))
						EnableWindow(GetDlgItem(hDlg, IDC_COPY), TRUE);
						EnableWindow(GetDlgItem(hDlg, IDC_FILEHELP), TRUE);
					break;
				case IDC_VZOOMUP:
					m_height = min(140, m_height+5);
					InvalidateRect(GetDlgItem(hDlg, IDC_IMAGE), NULL, TRUE);
					if(!IsWindowEnabled(GetDlgItem(hDlg, IDC_COPY)))
						EnableWindow(GetDlgItem(hDlg, IDC_COPY), TRUE);
						EnableWindow(GetDlgItem(hDlg, IDC_FILEHELP), TRUE);
					break;
				case IDC_VZOOMDOWN:
					HDC hdc;
					hdc = GetWindowDC(hDlg);
					m_height = max(GetMinimalHeight(hdc, m_step), m_height-5);
					ReleaseDC(hDlg, hdc);
					InvalidateRect(GetDlgItem(hDlg, IDC_IMAGE), NULL, TRUE);
					if(!IsWindowEnabled(GetDlgItem(hDlg, IDC_COPY)))
						EnableWindow(GetDlgItem(hDlg, IDC_FILEHELP), TRUE);
					break;        
				case IDC_PRINT:{
					CDlgPrintSetup * pDlg;    
					pDlg = new CDlgPrintSetup(&m_rcPrint);
					if(!pDlg)        return 2;
					if(!pDlg->Create(hDlg))    {delete pDlg; return 2;}
					delete pDlg;
					PRINTDLG prd;
					DOCINFO di;
					HDC hdcPrn;
					POINT ptLog;
					POINTFLOAT ptFloat; // nbre de pixel pour 1mm
					BOOL bOk, bEnd;
					ZeroMemory(&di, sizeof(DOCINFO));
					di.cbSize = sizeof(DOCINFO);
					di.lpszDocName = "Impression Code barre";
					ZeroMemory(&prd, sizeof(PRINTDLG));
					prd.lStructSize = sizeof(PRINTDLG);
					prd.hwndOwner = hDlg;
					prd.Flags = PD_RETURNDC|PD_NOPAGENUMS|PD_NOSELECTION|PD_HIDEPRINTTOFILE;
					if(!PrintDlg(&prd))        return 1;
					if((hdcPrn=prd.hDC)==NULL)        return 1;
					ptLog.x = GetDeviceCaps(hdcPrn, LOGPIXELSX);
					ptLog.y = GetDeviceCaps(hdcPrn, LOGPIXELSY);
					ptFloat.x = (float)ptLog.x/25.4f;
					ptFloat.y = (float)ptLog.y/25.4f;
					bOk = StartDoc(hdcPrn, &di);
					SetMapMode(hdcPrn, MM_TEXT);
					SetBkMode(hdcPrn, TRANSPARENT);
					bEnd = FALSE;
					while((bOk)&&(!bEnd))    {
						StartPage(hdcPrn);        
						bEnd = PreparePrint(hdcPrn, ptFloat, &m_rcPrint);
						bEnd = TRUE;
						bOk = EndPage(hdcPrn);
					}
					if(bOk) EndDoc(hdcPrn);
					else
						AbortDoc(hdcPrn);
					return DeleteDC(hdcPrn);
							   }break;
				case IDC_COPY:{
					HWND hMain;
					HBITMAP hBmp;
					HDC     hMem, hdc;
					POINT   pt;
					RECT    rc;    
					hMain = GetParent(GetParent(hDlg));
					if(!OpenClipboard(hMain))          return 3;
					EmptyClipboard();
					hdc = GetDC(hMain);
					hBmp = CreateCompatibleBitmap(hdc, GetApproximateWidth(m_step), m_height);
					if(!hBmp)  {        CloseClipboard();        return 4;    }
					hMem = CreateCompatibleDC(hdc);
					if(!hMem)    {        CloseClipboard();        DeleteObject(hBmp);        return 5;    }
					pt.x = pt.y = 0;
					rc.left = rc.top = 0;
					rc.right = GetApproximateWidth(m_step);
					rc.bottom = m_height;
					SelectObject(hMem, hBmp);
					FillRect(hMem, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
					Draw(hMem, pt, m_height, m_step);
					SetClipboardData(CF_BITMAP, hBmp);
					DeleteDC(hMem);
					ReleaseDC(hMain, hdc);    
					DeleteObject(hBmp);
					CloseClipboard();
					EnableWindow(GetDlgItem(hDlg, IDC_COPY), FALSE);
							  }break;
				case IDC_FILEHELP:{
					HWND hMain;
					HBITMAP hBmp;
					HDC     hMem, hdc;
					POINT   pt;
					RECT    rc;    
					GetDlgItemText(hDlg,IDC_EDIT,buffer,128);
					hMain = GetParent(GetParent(hDlg));
					if(!OpenClipboard(hMain))          return 3;
					EmptyClipboard();
					hdc = GetDC(hMain);
					hBmp = CreateCompatibleBitmap(hdc, GetApproximateWidth(m_step), m_height);
					if(!hBmp)  {        CloseClipboard();        return 4;    }
					hMem = CreateCompatibleDC(hdc);
					if(!hMem)    {        CloseClipboard();        DeleteObject(hBmp);        return 5;    }
					pt.x = pt.y = 0;
					rc.left = rc.top = 0;
					rc.right = GetApproximateWidth(m_step);
					rc.bottom = m_height;
					SelectObject(hMem, hBmp);
					FillRect(hMem, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
					Draw(hMem, pt, m_height, m_step);
					SetClipboardData(CF_BITMAP, hBmp);
					char szTmp[260];
					char buffer2[260];
					wsprintf(szTmp,"%s\\%s.BMP",szApp,buffer);
					wsprintf(buffer2,"Voulez vous sauvegarder le codebarre graphique pour %s sous: \n%s ?",buffer,szTmp);
					if(MsgBox(wincl.hInstance,hDlg,buffer2,"Sauvegarde Graphique",MB_YESNO|MB_DEFBUTTON2,103)==0x06){CreateBMPFile(hMain,szTmp , CreateBitmapInfoStruct(hMain,hBmp),hBmp,hMem);}
					DeleteDC(hMem);
					ReleaseDC(hMain, hdc);    
					DeleteObject(hBmp);
					EmptyClipboard();
					CloseClipboard();
								  }break;
				case IDC_ABOUTHELP:{
					MSGBOXPARAMS  mbp;    
					mbp.cbSize      = sizeof(MSGBOXPARAMS);
					mbp.dwStyle     = MB_USERICON;
					mbp.hInstance   = wincl.hInstance;
					mbp.hwndOwner   = hDlg;
					mbp.lpszIcon    = MAKEINTRESOURCE(IDI_ICON1);
					mbp.lpszCaption = " A propos de...";
					char buf[128];
					wsprintf(buf,"      Code barre       Version 1.8 \n\tNoyau OLEGDI: v:%s \n\n    ©Patrice Waechter-Ebling 2019-2020\n",GetDLLVersion());

					mbp.lpszText    = buf;
				   return  MessageBoxIndirect(&mbp);
								   }break;
				case IDC_FILECLOSE:
					PostMessage((hDlg), WM_CLOSE, 0, 0);
					break;
			}
					   }return 0;
		case WM_DRAWITEM:{    
			LPDRAWITEMSTRUCT lpdis;
			POINT pt;	
			lpdis = (LPDRAWITEMSTRUCT)lParam;
			if(lpdis->CtlID!=IDC_IMAGE)	    return 0;
			FillRect(lpdis->hDC, &lpdis->rcItem, CreateSolidBrush(RGB(0,128,0)));
			SetBkMode(lpdis->hDC, TRANSPARENT);
			pt.x = (lpdis->rcItem.right - GetApproximateWidth(m_step))/2;
			pt.y = (lpdis->rcItem.bottom - m_height)/2;
			Draw(lpdis->hDC, pt, m_height, m_step);/**/
						 }return 0;
		case WM_TIMER:{GetLocalTime(&st);wsprintf(buffer,"Nous sommes %s, le %2d %s %4d il est %.2d:%.2d:%.2d",jours[st.wDayOfWeek],st.wDay,mois[st.wMonth-1],st.wYear,st.wHour,st.wMinute,st.wSecond);SetDlgItemText(hDlg,6000,buffer);}break;
		case WM_CTLCOLORSTATIC:{SetTextColor( hStatic, RGB(128,128, 0xFF) );SetBkMode( hStatic, TRANSPARENT ); }return (LONG)wincl.hbrBackground;
		case WM_CTLCOLOREDIT:{SetTextColor( hStatic, RGB(120,0,0xAA ) );SetBkMode( hStatic, TRANSPARENT ); }return (LONG)wincl.hbrBackground;
		case WM_CTLCOLORLISTBOX:{SetTextColor( hStatic, RGB(0,255, 255) );SetBkMode( hStatic, TRANSPARENT ); }return (LONG)wincl.hbrBackground;
		case WM_CTLCOLORBTN:{SetTextColor( hStatic, RGB(0,255, 255) );	SetBkMode( hStatic, TRANSPARENT ); }return (LONG)wincl.hbrBackground;
		case WM_CTLCOLORMSGBOX:	return (long)wincl.hbrBackground;
			break;
        default:
            return DefWindowProc (hDlg, Message, wParam, lParam);
    }
    return 0;
}
void SetBits(char **lppData, int * lpPos, WORD wCode, int len){
    if((!lppData)||(!lpPos)||(*lpPos>=8)||(len>16)||(len<0)||(*lpPos<0))        return;
    WORD wBuf;
    char byBuf; 
    BYTE byMask;
    int i, k;
    do{
        wBuf = wCode << (16 - len);
        byBuf = (BYTE)(wBuf >> (*lpPos + 8));
        byMask = 0xFF>>(*lpPos);
        **lppData = ((**lppData) & (~byMask)) | (byBuf & byMask);
        k = len + (*lpPos) - 8;
        if(k>=0) {*lpPos = 0;(*lppData)++;  } else  (*lpPos) += len;
        len = k;            
    }while(len>0);
}
int Decode(const char * pszCode){
	ZeroMemory(m_szData, sizeof(m_szData));
	m_nbBits = 0;
	if(!pszCode){m_iError = ERR_VAR_CODE_NULL;return 0;}    
	int len, i, j;
	len = lstrlen(pszCode);
	for(i=0; i<len; i++){if(SetIndex(pszCode[i])==-1){m_iError = ERR_CODE_INCOMPATIBLE;return 0;}}
	if(pszCode[0]=='*'){pszCode++;len--;}
	if(pszCode[len-1]=='*'){len--;}
	if(len==0){m_iError = ERR_VAR_CODE_NULL;return 0;}
	m_iError = ERR_NONE;
	int count = 0;
	int pos = 0;
	char * pData = m_szData;
	SetBits(&pData, &pos, cstTable128[39], 12);
	SetBits(&pData, &pos, 0, 1);count = 13;
	for(i=0; i<len; i++){SetBits(&pData, &pos, cstTable128[SetIndex(pszCode[i])], 12);SetBits(&pData, &pos, 0, 1);count += 13;}
	SetBits(&pData, &pos, cstTable128[39], 12);
	count += 12;
	m_nbBits = count;
	return count;
}
int GetApproximateStep(int width){return  (int)(width/(m_nbBits+20));}
void errhandler(LPCTSTR Texte,HWND hwnd){MsgBox(hInst,hwnd,(char*)Texte,"Gestionnaire d'erreur",0,100);}
void SetResultCode(HWND hwnd){
    char szBuf[32], szBin[2048];
    int i;
    BYTE mask;
    const char * p = GetCodeString();    
    GetDlgItemText(hwnd, IDC_BINARY, szBuf, 64);
    if(!lstrcmp(szBuf, TEXT_BTN1))
        SetDlgItemText(hwnd, IDC_EDITRES, GetCodeString());
    else {
        szBin[0] = 0;
        for(i=0; i<m_bitSize; i++){
            mask = 0x80 >> (i%8);
            if(p[i/8] & mask)
                szBin[i] = '1';
            else
                szBin[i] = '0';
        }
        szBin[i] = 0;
        SetDlgItemText(hwnd, IDC_EDITRES, szBin);
    }
}
BOOL PreparePrint(HDC hdc, POINTFLOAT ptf, LPRECT lprc){
    POINT pt;
    int step, cy;    
    if(!m_bitSize)       return TRUE;
    pt.x = (int)(lprc->left*ptf.x);
    pt.y = (int)(lprc->top*ptf.y);
    step = GetApproximateStep((int)(lprc->right*ptf.x));
    cy = max((int)(lprc->bottom*ptf.y), GetMinimalHeight(hdc, step));
    Draw(hdc, pt, cy, step);
    return TRUE;
}
const char* ErrorString(int error){
    switch(error)    {
        case ERR_NONE:				 return "Pas d'erreur";
        case ERR_VAR_CODE_NULL:      return "Variable code ne devrait pas être nulle";
        case ERR_CODE_INCOMPATIBLE:  return "Code incompatible";
        case ERR_BAD_FORMAT_SIZE:    return "La taille de code barre est incompatible";
        case ERR_SIZE_LESS:          return "Taille de variable insuffisante";
        case ERR_CODE_TRUNCATE:      return "Le code barre est tronqué";
        default:					 return "Erreur inconnue";
    }
}

PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp){ 
    PBITMAPINFO pbmi; 
    WORD    cClrBits; 
    if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&btmp)) 
        errhandler("GetObject", hwnd); 
    cClrBits = (WORD)(btmp.bmPlanes * btmp.bmBitsPixel); 
    if (cClrBits == 1)         cClrBits = 1; 
    else if (cClrBits <= 4)    cClrBits = 4; 
    else if (cClrBits <= 8)    cClrBits = 8; 
    else if (cClrBits <= 16)   cClrBits = 16; 
    else if (cClrBits <= 24)   cClrBits = 24; 
    else cClrBits = 32; 
    if (cClrBits != 24)  pbmi = (PBITMAPINFO) LocalAlloc(LPTR,sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<< cClrBits));      else          pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER)); 
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmi->bmiHeader.biWidth = btmp.bmWidth; 
    pbmi->bmiHeader.biHeight = btmp.bmHeight; 
    pbmi->bmiHeader.biPlanes = btmp.bmPlanes; 
    pbmi->bmiHeader.biBitCount = btmp.bmBitsPixel; 
    if (cClrBits < 24) pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 
    pbmi->bmiHeader.biCompression = BI_RGB; 
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8* pbmi->bmiHeader.biHeight; 
    pbmi->bmiHeader.biClrImportant = 0; 
    return pbmi; 
}
void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,HBITMAP hBMP, HDC hDC) { 
     HANDLE hf;
	 BITMAPFILEHEADER hdr;
	 PBITMAPINFOHEADER pbih;
	 LPBYTE lpBits;
	 DWORD dwTotal,cb,dwTmp; 
	 BYTE *hp; 
	 pbih = (PBITMAPINFOHEADER) pbi; 
	 lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);
	 if (!lpBits)          errhandler("Alloction des tempons globaux", hwnd); 
	 if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi,DIB_RGB_COLORS)) {     errhandler("Détection des bist couleur de l'image", hwnd);     }
     hf = CreateFile(pszFile,GENERIC_READ | GENERIC_WRITE, (DWORD) 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL); 
     if (hf == INVALID_HANDLE_VALUE) errhandler("Création du fichier Image", hwnd); 
     hdr.bfType = 0x4d42;
     hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD) + pbih->biSizeImage); 
     hdr.bfReserved1 = 0; 
     hdr.bfReserved2 = 0; 
     hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof (RGBQUAD); 
     if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), (LPDWORD) &dwTmp,  NULL)){ errhandler("Écriture du fichier Image", hwnd); }
     if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) + pbih->biClrUsed * sizeof (RGBQUAD), (LPDWORD) &dwTmp, ( NULL)) )   errhandler("Écriture du fichier Image", hwnd); 
     dwTotal = cb = pbih->biSizeImage; 
     hp = lpBits; 
     if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL))    errhandler("Écriture du fichier Image", hwnd); 
     if (!CloseHandle(hf))     errhandler("Fermeture de la main", hwnd); 
	 GlobalFree((HGLOBAL)lpBits);
}
int GetMinimalHeight(HDC hdc, int step){
    POINT ptLog;
    POINTFLOAT ptFloat;
    ptLog.y = GetDeviceCaps(hdc, LOGPIXELSY);
    ptFloat.y = (float)ptLog.y/25.4f;    
    return  (int)(ptFloat.y*7);
}
int GetAppLastError(){    return m_iError;}
const char* GetCodeString(){    return m_szData;}
void Draw(HDC hdc, POINT pt, int height, int step){
    int len, i, j, count;
    RECT rect;
    BYTE mask;
    POINT ptLog;
    POINTFLOAT ptFloat;
    len = lstrlen(m_szData);
    if(len==0) return;
    step = max(1, step);
    ptLog.x = GetDeviceCaps(hdc, LOGPIXELSX);
    ptLog.y = GetDeviceCaps(hdc, LOGPIXELSY);
    ptFloat.x = (float)ptLog.x/25.4f;
    ptFloat.y = (float)ptLog.y/25.4f;
    SetRect(&rect, pt.x, pt.y, GetApproximateWidth(step) + pt.x, height + pt.y);    
    FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
    pt.y += (int)(ptFloat.y*2.f);
    height -= (int)(ptFloat.y*4.f);
    rect.top = pt.y;
    for(i=0; i<len; i++)  {
        for(j=0; j<8; j++){
            mask = 0x80 >> j;
            rect.left = pt.x + step*10 + step*(8*i+j);
            rect.right = rect.left + step;
            rect.bottom = pt.y + height;            
            if(m_szData[i] & mask){
                FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            }
        }
    }
}
int SetIndex(char car){
    if((car>=48)&&(car<=57))        return (car-48);
    else if((car>=65)&&(car<=90))   return (car-55);
    else if((car>=97)&&(car<=122))  return (car-87);
    else if(car=='-')		        return 36;
    else if(car=='.')		        return 37;
    else if(car==' ')		        return 38;
    else if(car=='*')		        return 39;
    else if(car=='$')		        return 40;
    else if(car=='/')		        return 41;
    else if(car=='+')		        return 42;
    else if(car=='%')		        return 43;
    return -1;
}

int GetApproximateWidth(int step){    if(!m_nbBits) return 0;     return (m_nbBits+20)*step;}
int CheckDigit(const char * pszCode, BOOL bComplet){    return 0;}

