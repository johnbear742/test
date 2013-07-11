// CatCatchRatView.h : interface of the CCatCatchRatView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CATCATCHRATVIEW_H__B4196808_4145_49DF_99D0_45F38E4512CB__INCLUDED_)
#define AFX_CATCATCHRATVIEW_H__B4196808_4145_49DF_99D0_45F38E4512CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SelectDlg.h"

#define RATMAX 5 //�궨�壬�����������
class CCatCatchRatView : public CView
{
public:
	CBitmap    m_bmCat[4],m_bmRat[4];                   //è�������λͼ
	int        StartFlag; //��������״̬����1:����״̬��0:��Ϸ��ͣ��1:��Ϸ��ʼ��2:��Ϸ����
	bool       m_bRatLive[RATMAX];                      //�������־
	int        m_nCatw,m_nCath;                         //èλͼ�Ŀ�͸�
	int        m_nCatx,m_nCaty;                         //èλͼ�����Ͻ�����
	int        m_nRatDirection[RATMAX],m_nCatDirection; //è��������˶�����
	int        m_nRatw,m_nRath;                         //����λͼ�Ŀ�͸�
	int        m_nRatx[RATMAX],m_nRaty[RATMAX];         //����λͼ�����Ͻ�����
	CRect      m_rectClient;                            //���ؾ���
	CRect      m_rectRat[RATMAX],m_rectCat;             //è������λͼ�ľ���
	int        m_nRat;                                  //��ץ������
	int        m_nRatSpeed,m_nCatSpeed;                 //�˶��ٶ�
	CTime      m_timeStart,m_timeEnd;                   //��Ϸ��ʼ�ͽ���ʱ��
	CTimeSpan  m_timeWork,m_timeSet;                    //��Ϸʣ��ʱ����趨ʱ��
	int        m_nDifficulty;                           //�Ѷȣ�0:�ͣ�1:�У�2:��
	int        m_nWinFlag;                              //��Ϸ��ʤ�ߣ�0:è��ʤ��1:�����ʤ

protected: // create from serialization only
	CCatCatchRatView();
	DECLARE_DYNCREATE(CCatCatchRatView)

// Attributes
public:
	CCatCatchRatDoc* GetDocument();

// Operations
public:

protected:
	/*
����һ��������͸��λͼ�ĺ���
CDC *pDC ��Ҫ��λͼ��CDCָ��
UINT IDImage λͼ��ԴID
Crect &rect ָ��λͼ��pDC�е�λ��
COLORREF rgbMask λͼ��͸��ɫ

*/
void DrawTransparentBitmap(CDC *pDC,CBitmap &Image,CRect &rect, COLORREF rgbMask);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCatCatchRatView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCatCatchRatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCatCatchRatView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRestart();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnSelect();
	afx_msg void OnUpdateStart(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CatCatchRatView.cpp
inline CCatCatchRatDoc* CCatCatchRatView::GetDocument()
   { return (CCatCatchRatDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATCATCHRATVIEW_H__B4196808_4145_49DF_99D0_45F38E4512CB__INCLUDED_)
