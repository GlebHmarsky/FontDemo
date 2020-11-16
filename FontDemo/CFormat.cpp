// CFormat.cpp : implementation file
//

#include "pch.h"
#include "FontDemo.h"
#include "CFormat.h"
#include "afxdialogex.h"


// CFormat dialog

IMPLEMENT_DYNAMIC(CFormat, CDialog)

CFormat::CFormat(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_Bold(FALSE)
	, m_Italic(FALSE)
	, m_Underline(FALSE)
	, m_Pitch(0)
	, m_Justify(0)
	, m_Spacing(0)
{

}

CFormat::~CFormat()
{
}

void CFormat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_BOLD, m_Bold);
	DDX_Check(pDX, IDC_ITALIC, m_Italic);
	DDX_Check(pDX, IDC_UNDERLINE, m_Underline);
	DDX_Radio(pDX, IDC_VARIABLE, m_Pitch);
	DDX_Radio(pDX, IDC_LEFT, m_Justify);
	DDX_Text(pDX, IDC_SPACING, m_Spacing);
	DDV_MinMaxInt(pDX, m_Spacing, 1, 3);
	DDX_Control(pDX, IDC_SPACING, m_SpacingEdit);
}


BEGIN_MESSAGE_MAP(CFormat, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BOLD, &CFormat::OnClickedBold)
	ON_BN_CLICKED(IDC_ITALIC, &CFormat::OnClickedItalic)
	ON_BN_CLICKED(IDC_LEFT, &CFormat::OnClickedLeft)
	ON_EN_CHANGE(IDC_SPACING, &CFormat::OnChangeSpacing)
	ON_BN_CLICKED(IDC_UNDERLINE, &CFormat::OnClickedUnderline)
	ON_BN_CLICKED(IDC_VARIABLE, &CFormat::OnClickedVariable)
	ON_COMMAND(IDC_CENTER, &CFormat::OnCenter)
	ON_COMMAND(IDC_FIXED, &CFormat::OnFixed)
	ON_COMMAND(IDC_RIGHT, &CFormat::OnRight)
END_MESSAGE_MAP()


// CFormat message handlers




BOOL CFormat::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&m_RectSample);
	ScreenToClient(&m_RectSample);
	m_SpacingEdit.LimitText(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CFormat::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
	CFont Font;
	LOGFONT LF;
	int LineHeight;
	CFont* PtrOldFont;
	int X, Y;

	// заполнение структуры LF свойствами
	// стандартного системного шрифта:
	CFont TempFont;
	if (m_Pitch == PITCH_VARIABLE)
		TempFont.CreateStockObject(SYSTEM_FONT);
	else
		TempFont.CreateStockObject(SYSTEM_FIXED_FONT);
	TempFont.GetObject(sizeof(LOGFONT), &LF);
	// инициализируем поля lfWeight, lfItalic и lfUnderline:
	if (m_Bold)
		LF.lfWeight = FW_BOLD;
	if (m_Italic)
		LF.lfItalic = 1;
	if (m_Underline)
		LF.lfUnderline = 1;

	// создание и выбор шрифта:
	Font.CreateFontIndirect(&LF);
	PtrOldFont = dc.SelectObject(&Font);
	// задаем выравнивание:
	switch (m_Justify)
	{
	case JUSTIFY_LEFT:
		dc.SetTextAlign(TA_LEFT);
		X = m_RectSample.left + 5;
		break;
	case JUSTIFY_CENTER:
		dc.SetTextAlign(TA_CENTER);
		X = (m_RectSample.left + m_RectSample.right) / 2;
		break;
	case JUSTIFY_RIGHT:
		dc.SetTextAlign(TA_RIGHT);
		X = m_RectSample.right - 5;
		break;
	}
	// установка режима отображения фона:
	dc.SetBkMode(TRANSPARENT); // прозрачный

	// вывод строк текста:
	LineHeight = LF.lfHeight * m_Spacing;
	Y = m_RectSample.top + 15;
	dc.TextOut(X, Y, _T("AaBbCdDdEeFf"));
	Y += LineHeight;
	dc.TextOut(X, Y, _T("GhHhIiJjKkLl"));
	Y += LineHeight;
	dc.TextOut(X, Y, _T("MmNnOoPpQqRr"));

	// отмена выбора шрифта:
	dc.SelectObject(PtrOldFont);

					   // Do not call CDialog::OnPaint() for painting messages
}

void CFormat::OnClickedBold()
{
	// TODO: Add your control notification handler code here
	m_Bold = !m_Bold;
	InvalidateRect(&m_RectSample);
	UpdateWindow();

}

void CFormat::OnClickedItalic()
{
	// TODO: Add your control notification handler code here
	m_Italic = !m_Italic;
	InvalidateRect(&m_RectSample);
	UpdateWindow();

}

void CFormat::OnClickedUnderline()
{
	// TODO: Add your control notification handler code here
	m_Underline = !m_Underline;
	InvalidateRect(&m_RectSample);
	UpdateWindow();
}

void CFormat::OnClickedLeft()
{
	// TODO: Add your control notification handler code here
	if (IsDlgButtonChecked(IDC_LEFT))
	{
		m_Justify = JUSTIFY_LEFT;
		InvalidateRect(&m_RectSample);
		UpdateWindow();
	}

}

void CFormat::OnCenter()
{
	// TODO: Add your command handler code here
	if (IsDlgButtonChecked(IDC_CENTER))
	{
		m_Justify = JUSTIFY_CENTER;
		InvalidateRect(&m_RectSample);
		UpdateWindow();
	}

}

void CFormat::OnRight()
{
	// TODO: Add your command handler code here
	if (IsDlgButtonChecked(IDC_RIGHT))
	{
		m_Justify = JUSTIFY_RIGHT;
		InvalidateRect(&m_RectSample);
		UpdateWindow();
	}

}

void CFormat::OnChangeSpacing()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here	
	m_Spacing = (int)GetDlgItemInt(IDC_SPACING);
	InvalidateRect(&m_RectSample);
	UpdateWindow();
	
}

void CFormat::OnClickedVariable()
{
	// TODO: Add your control notification handler code here
	if (IsDlgButtonChecked(IDC_VARIABLE))
	{
		m_Pitch = PITCH_VARIABLE;
		InvalidateRect(&m_RectSample);
		UpdateWindow();
	}
}

void CFormat::OnFixed()
{
	// TODO: Add your command handler code here
	if (IsDlgButtonChecked(IDC_FIXED))
	{
		m_Pitch = PITCH_FIXED;
		InvalidateRect(&m_RectSample);
		UpdateWindow();
	}
}



