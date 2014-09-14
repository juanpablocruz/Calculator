
// CalculadoraDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calculadora.h"
#include "CalculadoraDlg.h"
#include "afxdialogex.h"
#include <math.h>
#include <vector>
#include "calc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.14159265359


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
	DHTML_EVENT_ONCLICK(_T("suma"), typeNum)
	DHTML_EVENT_ONCLICK(_T("resta"), typeNum)
	DHTML_EVENT_ONCLICK(_T("multi"), typeNum)
	DHTML_EVENT_ONCLICK(_T("div"), typeNum)
	DHTML_EVENT_ONCLICK(_T("igual"), igual)
	DHTML_EVENT_ONCLICK(_T("raiz"), raiz)
	DHTML_EVENT_ONCLICK(_T("porcen"), porcen)
	DHTML_EVENT_ONCLICK(_T("erase"), erase)
	DHTML_EVENT_ONCLICK(_T("mod"), mod)
	DHTML_EVENT_ONCLICK(_T("standard"), standardMode)
	DHTML_EVENT_ONCLICK(_T("cient"), cientMode)
	DHTML_EVENT_ONCLICK(_T("powe"), powe_func)
	DHTML_EVENT_ONCLICK(_T("pow"), pow_func)
	DHTML_EVENT_ONCLICK(_T("pi"), show_pi)
	DHTML_EVENT_ONCLICK(_T("square"), square)
	DHTML_EVENT_ONCLICK(_T("sin"), sin_func)
	DHTML_EVENT_ONCLICK(_T("cos"), cos_func)
	DHTML_EVENT_ONCLICK(_T("arctan"), arctan_func)
	DHTML_EVENT_ONCLICK(_T("arcsin"), arcsin_func)
	DHTML_EVENT_ONCLICK(_T("arccos"), arccos_func)
	DHTML_EVENT_ONCLICK(_T("tan"), tan_func)
	DHTML_EVENT_ONCLICK(_T("deg"), changeAngle)
	DHTML_EVENT_ONCLICK(_T("neper"), neper)
	DHTML_EVENT_ONCLICK(_T("log"), log_func)
	DHTML_EVENT_ONCLICK(_T("factorial"), fact_func)
	DHTML_EVENT_ONCLICK(_T("lPar"), typeNum)
	DHTML_EVENT_ONCLICK(_T("rPar"), typeNum)
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

float round(float f, float pres)
{
	return (float)round(f*pow(10, pres+1)) / pow(10, pres+1);
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
	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		if (this->res != OPERADOR_IGUAL) {
			_variant_t val;
			textArea->getAttribute(_bstr_t("value"), 0, &val);

			std::string str, st;

			// convert directly into str-allocated buffer.
			BstrToStdString(val.bstrVal, str);
			if (str.size() > 2)
				st = str.substr(0, str.size() - 2);
			else
				st = "0";
			textArea->put_innerText(Convert(st));
		}
		else {
			textArea->put_innerText(_bstr_t("0"));
		}
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
		std::string str, st;

		// convert directly into str-allocated buffer.
		BstrToStdString(val.bstrVal, str);

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
			if (this->rightValue != 0)
			textArea->put_innerText(_bstr_t(this->leftValue / this->rightValue));
			else
				textArea->put_innerText(_bstr_t("Inf"));
			break;
		case OPERADOR_PORCEN:
			textArea->put_innerText(_bstr_t((this->leftValue *100 )/ this->rightValue));
			this->res = OPERADOR_IGUAL;
			break;
		case OPERADOR_MOD:
			textArea->put_innerText(_bstr_t(((INT)this->leftValue) % (INT)this->rightValue));
			this->res = OPERADOR_IGUAL;
			break;
		case OPERADOR_POW:
			textArea->put_innerText(_bstr_t(pow(this->leftValue, this->rightValue)));
			this->res = OPERADOR_IGUAL;
			break;
		case OPERADOR_2EXP:
			textArea->put_innerText(_bstr_t((this->rightValue)*(this->rightValue)));
			this->res = OPERADOR_IGUAL;
			break;
		default:
			textArea->put_innerText(_bstr_t(calculate(str.c_str())));
			break;
		}
	}
	
	return S_OK;
}

HRESULT CCalculadoraDlg::cientMode(IHTMLElement* pElement)
{
	pElement->put_className(_bstr_t("active"));
	IHTMLElement* active = NULL;
	if (GetElement(_T("standard"), &active) == S_OK && active != NULL){
		active->removeAttribute(_bstr_t("className"), 1, 0);
	}
	IHTMLElement* cien = NULL;
	if (GetElement(_T("cientific"), &cien) == S_OK && cien != NULL){
		cien->put_className(_bstr_t("active"));
	}
	return S_OK;
}

HRESULT CCalculadoraDlg::standardMode(IHTMLElement* pElement)
{

	pElement->put_className(_bstr_t("active"));
	IHTMLElement* active = NULL;
	if (GetElement(_T("cient"), &active) == S_OK && active != NULL){
		active->removeAttribute(_bstr_t("className"), 1,0);
	}
	IHTMLElement* cien = NULL;
	if (GetElement(_T("cientific"), &cien) == S_OK && cien != NULL){
		cien->removeAttribute(_bstr_t("className"), 1, 0);
	}
	return S_OK;
}

// CIENTIFIC FUNCTIONS

HRESULT CCalculadoraDlg::powe_func(IHTMLElement* pElement)
{
	this->operador = OPERADOR_POWE;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);

		textArea->put_innerText(_bstr_t(exp(this->leftValue)));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::pow_func(IHTMLElement* pElement)
{
	this->operador = OPERADOR_POW;
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

HRESULT CCalculadoraDlg::show_pi(IHTMLElement* pElement)
{
	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		FLOAT t;
		VarR4FromStr(val.bstrVal, 0, 0, &t);

		if (t == (FLOAT)0)
			textArea->put_innerText(_bstr_t(PI));
		else
			textArea->put_innerText(val.bstrVal + _bstr_t(PI));
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::square(IHTMLElement *pElement) {
	this->operador = OPERADOR_2EXP;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);

		textArea->put_innerText(_bstr_t((this->leftValue)*(this->leftValue)));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::sin_func(IHTMLElement *pElement) {
	this->operador = OPERADOR_SIN;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);

		double angulo;
		switch (system_grad){

		case RAD:
			angulo = this->leftValue;
			break;
		case DEG:
			angulo = this->leftValue * PI / 180;
			break;
		case GRAD:
			angulo = this->leftValue * PI / 200;
			break;
		}

		textArea->put_innerText(_bstr_t(round(sin(angulo),2)));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::cos_func(IHTMLElement *pElement) {
	this->operador = OPERADOR_COS;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);

		double angulo;
		switch (system_grad){

		case RAD:
			angulo = this->leftValue;
			break;
		case DEG:
			angulo = this->leftValue * PI / 180;
			break;
		case GRAD:
			angulo = this->leftValue * PI / 200;
			break;
		}

		textArea->put_innerText(_bstr_t(round(cos(angulo), 2)));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::tan_func(IHTMLElement *pElement) {
	this->operador = OPERADOR_TAN;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);

		double angulo;
		switch (system_grad){

		case RAD:
			angulo = this->leftValue;
			break;
		case DEG:
			angulo = this->leftValue * PI / 180;
			break;
		case GRAD:
			angulo = this->leftValue * PI / 200;
			break;
		}

		textArea->put_innerText(_bstr_t(round(tan(angulo), 2)));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}
HRESULT CCalculadoraDlg::arcsin_func(IHTMLElement *pElement) {
	this->operador = OPERADOR_ASIN;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);

		double angulo;
		switch (system_grad){

		case RAD:
			angulo = asin(this->leftValue);
			break;
		case DEG:
			angulo = asin(this->leftValue) * 180 / PI;
			break;
		case GRAD:
			angulo = asin(this->leftValue) * 200 / PI;
			break;
		}
		textArea->put_innerText(_bstr_t(angulo));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::arccos_func(IHTMLElement *pElement) {
	this->operador = OPERADOR_ACOS;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);

		double angulo;
		switch (system_grad){

		case RAD:
			angulo = acos(this->leftValue);
			break;
		case DEG:
			angulo = acos(this->leftValue) * 180 / PI;
			break;
		case GRAD:
			angulo = acos(this->leftValue) * 200 / PI;
			break;
		}
		textArea->put_innerText(_bstr_t(angulo));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::arctan_func(IHTMLElement *pElement) {
	this->operador = OPERADOR_ATAN;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);

		double angulo;
		switch (system_grad){

		case RAD:
			angulo = atan(this->leftValue);
			break;
		case DEG:
			angulo = atan(this->leftValue) * 180 / PI;
			break;
		case GRAD:
			angulo = atan(this->leftValue) * 200 / PI;
			break;
		}
		textArea->put_innerText(_bstr_t(angulo));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::changeAngle(IHTMLElement* pElement)
{
	IHTMLElement* next = NULL;
	IHTMLElement* prev = NULL;
	LPCTSTR type = NULL;
	LPCTSTR type2 = NULL;
	switch (system_grad){
	case RAD:
		type = _T("grad_angle");
		type2 = _T("rad_angle");
		system_grad = GRAD;
		break;
	case DEG:
		type = _T("rad_angle");
		type2 = _T("deg_angle");
		system_grad = RAD;
		break;
	case GRAD:
		type = _T("deg_angle");
		type2 = _T("grad_angle");
		system_grad = DEG;
		break;
	}
	if (GetElement(type, &next) == S_OK &&
		next != NULL)
	{
		next->put_className(_bstr_t("active_angle"));
	}
	if (GetElement(type2, &prev) == S_OK &&
		prev != NULL)
	{
		prev->removeAttribute(_bstr_t("className"), 1, 0);
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::neper(IHTMLElement *pElement) {
	this->operador = OPERADOR_NEPER;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);

		
		textArea->put_innerText(_bstr_t(log(this->leftValue)));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::log_func(IHTMLElement *pElement) {
	this->operador = OPERADOR_LOG;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);


		textArea->put_innerText(_bstr_t(log10(this->leftValue)));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::fact_func(IHTMLElement *pElement) {
	this->operador = OPERADOR_FACT;

	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		VarR4FromStr(val.bstrVal, 0, 0, &this->leftValue);

		long long factorial = 1;
		for (int i = 1; i <= (int)round(this->leftValue); i++){
			factorial *= i;
		}

		textArea->put_innerText(_bstr_t(factorial));
		this->res = OPERADOR_IGUAL;
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::lPar(IHTMLElement *pElement) {
	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
			_variant_t val;
			textArea->getAttribute(_bstr_t("value"), 0, &val);
			FLOAT t;
			VarR4FromStr(val.bstrVal, 0, 0, &t);

			if (t == (FLOAT)0)
				textArea->put_innerText(_bstr_t("("));
			else
				textArea->put_innerText(val.bstrVal + _bstr_t("("));
	}

	return S_OK;
}

HRESULT CCalculadoraDlg::rPar(IHTMLElement *pElement) {
	IHTMLElement* textArea = NULL;
	if (GetElement(_T("textArea"), &textArea) == S_OK &&
		textArea != NULL)
	{
		_variant_t val;
		textArea->getAttribute(_bstr_t("value"), 0, &val);
		FLOAT t;
		VarR4FromStr(val.bstrVal, 0, 0, &t);

		if (t == (FLOAT)0)
			textArea->put_innerText( _bstr_t(")"));
		else
			textArea->put_innerText(val.bstrVal + _bstr_t(")"));
	}

	return S_OK;
}