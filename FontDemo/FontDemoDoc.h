
// FontDemoDoc.h : interface of the CFontDemoDoc class
//


#pragma once


class CFontDemoDoc : public CDocument
{
public:
	BOOL m_Bold;
	BOOL m_Italic;
	int m_Justify;
	int m_Pitch;
	int m_Spacing;
	BOOL m_Underline;

protected: // create from serialization only
	CFontDemoDoc() noexcept;
	DECLARE_DYNCREATE(CFontDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CFontDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnTextFormat();
};
