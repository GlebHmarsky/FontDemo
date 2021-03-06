
// FontDemoDoc.cpp : implementation of the CFontDemoDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "FontDemo.h"
#endif

#include "FontDemoDoc.h"
#include "CFormat.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFontDemoDoc

IMPLEMENT_DYNCREATE(CFontDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CFontDemoDoc, CDocument)
	ON_COMMAND(ID_TEXT_FORMAT, &CFontDemoDoc::OnTextFormat)
END_MESSAGE_MAP()


// CFontDemoDoc construction/destruction

CFontDemoDoc::CFontDemoDoc() noexcept
{
	// TODO: add one-time construction code here
	m_Bold = FALSE;
	m_Italic = FALSE;
	m_Justify = JUSTIFY_LEFT;
	m_Pitch = PITCH_VARIABLE;
	m_Spacing = 1;
	m_Underline = FALSE;

}

CFontDemoDoc::~CFontDemoDoc()
{
}

BOOL CFontDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CFontDemoDoc serialization

void CFontDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CFontDemoDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CFontDemoDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CFontDemoDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CFontDemoDoc diagnostics

#ifdef _DEBUG
void CFontDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFontDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFontDemoDoc commands


void CFontDemoDoc::OnTextFormat()
{
	// TODO: Add your command handler code here
	// ���������� ������� ������ ����������� ����:
	CFormat FormatDlg;

	// ������������� ���������� ������:
	FormatDlg.m_Bold = m_Bold;
	FormatDlg.m_Italic = m_Italic;
	FormatDlg.m_Justify = m_Justify;
	FormatDlg.m_Pitch = m_Pitch;
	FormatDlg.m_Spacing = m_Spacing;
	FormatDlg.m_Underline = m_Underline;
	// ����������� ����������� ����:   
	if (FormatDlg.DoModal() == IDOK)
	{
		// ���������� ������������� ��������:
		m_Bold = FormatDlg.m_Bold;
		m_Italic = FormatDlg.m_Italic;
		m_Justify = FormatDlg.m_Justify;
		m_Pitch = FormatDlg.m_Pitch;
		m_Spacing = FormatDlg.m_Spacing;
		m_Underline = FormatDlg.m_Underline;

		// ����������� ������:
		UpdateAllViews(NULL);
	}

}
