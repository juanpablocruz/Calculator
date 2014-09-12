
// CalculadoraDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calculadora.h"
#include "CalculadoraDlg.h"
#include "afxdialogex.h"
#include <math.h>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculadoraDlg dialog

BEGIN_DHTML_EVENT_MAP(CCalculadoraDlg)
	DHTML_EVENT_CLASS(DISPID_HTMLELEMENTEVENTS_ONCLICK, _T("number_button"),typeNum)
	DHTML_EVENT_ONCLICK(_T("suma"), suma)
	DHTML_EVENT_ONCLICK(_T("resta"), resta)
	DHTML_EVENT_ONCLICK(_T("multi"), multiplicacion)
	DHTML_EVENT_ONCLICK(_T("div"), division)
	DHTML_EVENT_ONCLICK(_T("igual"), igual)
	DHTML_EVENT_ONCLICK(_T("raiz"), raiz)
	DHTML_EVENT_ONCLICK(_T("porcen"), porcen)
	DHTML_EVENT_ONCLICK(_T("erase"), erase)
	DHTML_EVENT_ONCLICK(_T("mod"), mod)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()


CCalculadoraDlg::CCalculadoraDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CCalculadoraDlg::IDD, CCalculadoraDlg::IDH, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculadoraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalculadoraDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CCalculadoraDlg message handlers

BOOL CCalculadoraDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculadoraDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculadoraDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

// convert a BSTR to a std::string. 
std::string& BstrToStdString(const BSTR bstr, std::string& dst, int cp = CP_UTF8)
{
	if (!bstr)
	{
		// define NULL functionality. I just clear the target.
		dst.clear();
		return dst;
	}

	// request content length in single-chars through a terminating
	//  nullchar in the BSTR. note: BSTR's support imbedded nullchars,
	//  so this will only convert through the first nullchar.
	int res = WideCharToMultiByte(cp, 0, bstr, -1, NULL, 0, NULL, NULL);
	if (res > 0)
	{
		dst.resize(res);
		WideCharToMultiByte(cp, 0, bstr, -1, &dst[0], res, NULL, NULL);
	}
	else
	{    // no content. clear target
		dst.clear();
	}
	return dst;
}


BSTR Convert(const std::string& s) { return CComBSTR(s.c_str()).Detach(); }

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculadoraDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CCalculadoraDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CCalculadoraDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}

HRESULT CCalculadoraDlg::typeNum(IHTMLElement* pElement)
{
	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		BSTR bstrText, text_field;
		textArea->get_innerText(&text_field);
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		pElement->get_innerText(&bstrText);
		BSTR zero_s = _bstr_t("0");
		if (*val.bstrVal == *zero_s || this->res == OPERADOR_IGUAL){
			textArea->put_innerText(_bstr_t(bstrText));
			this->res = 1;
		}
		else {

			textArea->put_innerText(val.bstrVal + _bstr_t(bstrText));
		}
	}
	
	return S_OK;
}

HRESULT CCalculadoraDlg::suma(IHTMLElement* pElement)
{
	this->operador = OPERADOR_SUMA;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::resta(IHTMLElement* pElement)
{
	this->operador = OPERADOR_RESTA;
	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::multiplicacion(IHTMLElement* pElement)
{
	this->operador = OPERADOR_MULTI;
	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::division(IHTMLElement* pElement)
{
	this->operador = OPERADOR_DIV;
	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::raiz(IHTMLElement* pElement)
{
	this->operador = OPERADOR_RAIZ;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);

		textArea->put_innerText(_bstr_t(sqrt(this->leftValue)));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::porcen(IHTMLElement* pElement)
{
	this->operador = OPERADOR_PORCEN;
	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::mod(IHTMLElement* pElement)
{
	this->operador = OPERADOR_MOD;
	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::erase(IHTMLElement* pElement)
{
	this->operador = OPERADOR_PORCEN;
	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		SAFEARRAY* vect;
		
		std::string str,st;

		// convert directly into str-allocated buffer.
		BstrToStdString(val.bstrVal, str);
		if (str.size() > 2)
			st = str.substr(0, str.size() - 2);
		else
			st = "0";
		textArea->put_innerText(Convert(st));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::igual(IHTMLElement* pElement)
{
	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL){

		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->rightValue);

		switch (this->operador) {
		case OPERADOR_SUMA:
			textArea->put_innerText(_bstr_t(this->leftValue + this->rightValue));
			break;
		case OPERADOR_RESTA:
			textArea->put_innerText(_bstr_t(this->leftValue - this->rightValue));
			break;
		case OPERADOR_MULTI:
			textArea->put_innerText(_bstr_t(this->leftValue * this->rightValue));
			break;
		case OPERADOR_DIV:
			textArea->put_innerText(_bstr_t(this->leftValue / this->rightValue));
			break;
		case OPERADOR_PORCEN:
			textArea->put_innerText(_bstr_t((this->leftValue *100 )/ this->rightValue));
			break;
		case OPERADOR_MOD:
			textArea->put_innerText(_bstr_t(((INT)this->leftValue) % (INT)this->rightValue));
			break;
		}
	}
	this->res = OPERADOR_IGUAL;
	
	return S_OK;
}
