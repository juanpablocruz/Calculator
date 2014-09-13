
// CalculadoraDlg.h : header file
//

#pragma once


// CCalculadoraDlg dialog
class CCalculadoraDlg : public CDHtmlDialog
{
// Construction
public:
	CCalculadoraDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CALCULADORA_DIALOG, IDH = IDR_HTML_CALCULADORA_DIALOG };
	FLOAT leftValue, rightValue;
	int operador,res=0;
	enum {DEG,RAD,GRAD};
	int system_grad = DEG;
	enum { OPERADOR_SUMA, OPERADOR_RESTA, OPERADOR_MULTI, OPERADOR_DIV, OPERADOR_IGUAL, 
		OPERADOR_RAIZ, OPERADOR_PORCEN, OPERADOR_MOD, OPERADOR_POWE, OPERADOR_POW, OPERADOR_2EXP,
		OPERADOR_SIN, OPERADOR_COS, OPERADOR_TAN, OPERADOR_ASIN, OPERADOR_ACOS, OPERADOR_ATAN,
		OPERADOR_DEC,OPERADOR_NEPER, OPERADOR_LOG, OPERADOR_FACT,
	};
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
	HRESULT typeNum(IHTMLElement *pElement);
	HRESULT suma(IHTMLElement *pElement);
	HRESULT resta(IHTMLElement *pElement);
	HRESULT multiplicacion(IHTMLElement *pElement);
	HRESULT division(IHTMLElement *pElement);
	HRESULT igual(IHTMLElement *pElement);
	HRESULT raiz(IHTMLElement *pElement);
	HRESULT porcen(IHTMLElement *pElement);
	HRESULT erase(IHTMLElement *pElement);
	HRESULT mod(IHTMLElement *pElement);

	HRESULT cientMode(IHTMLElement *pElement);
	HRESULT standardMode(IHTMLElement *pElement);

	HRESULT powe_func(IHTMLElement *pElement);
	HRESULT pow_func(IHTMLElement *pElement);
	HRESULT show_pi(IHTMLElement *pElement);
	HRESULT square(IHTMLElement *pElement);
	HRESULT sin_func(IHTMLElement *pElement);
	HRESULT cos_func(IHTMLElement *pElement);
	HRESULT tan_func(IHTMLElement *pElement);
	HRESULT arcsin_func(IHTMLElement *pElement);
	HRESULT arccos_func(IHTMLElement *pElement);
	HRESULT arctan_func(IHTMLElement *pElement);
	HRESULT changeAngle(IHTMLElement *pElement);
	HRESULT neper(IHTMLElement *pElement);
	HRESULT log_func(IHTMLElement *pElement);
	HRESULT fact_func(IHTMLElement *pElement);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
