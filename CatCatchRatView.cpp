// CatCatchRatView.cpp : implementation of the CCatCatchRatView class
//

#include "stdafx.h"
#include "CatCatchRat.h"

#include "CatCatchRatDoc.h"
#include "CatCatchRatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCatCatchRatView

IMPLEMENT_DYNCREATE(CCatCatchRatView, CView)

BEGIN_MESSAGE_MAP(CCatCatchRatView, CView)
	//{{AFX_MSG_MAP(CCatCatchRatView)
	ON_WM_TIMER()
	ON_COMMAND(ID_Restart, OnRestart)
	ON_COMMAND(ID_Start, OnStart)
	ON_COMMAND(ID_Stop, OnStop)
	ON_WM_KEYDOWN()
	ON_UPDATE_COMMAND_UI(ID_Stop, OnUpdateStop)
	ON_COMMAND(ID_SELECT, OnSelect)
	ON_UPDATE_COMMAND_UI(ID_Start, OnUpdateStart)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCatCatchRatView construction/destruction

CCatCatchRatView::CCatCatchRatView()
{
	// TODO: add construction code here
	//����è�������λͼ��Դ
	m_bmCat[0].LoadBitmap(IDB_CatUp);
	m_bmCat[1].LoadBitmap(IDB_CatDown);
	m_bmCat[2].LoadBitmap(IDB_CatLeft);
	m_bmCat[3].LoadBitmap(IDB_CatRight);
	m_bmRat[0].LoadBitmap(IDB_RatUp);
	m_bmRat[1].LoadBitmap(IDB_RatDown);
	m_bmRat[2].LoadBitmap(IDB_RatLeft);
	m_bmRat[3].LoadBitmap(IDB_RatRight);
	//����è������λͼ�ĸ�Ϳ�
	BITMAP bmCat;
	m_bmCat[2].GetBitmap(&bmCat);
	m_nCatw=bmCat.bmWidth;
	m_nCath=bmCat.bmHeight;
	BITMAP bmRat[4];
	m_bmRat[0].GetBitmap(&bmRat[0]);
	m_bmRat[1].GetBitmap(&bmRat[1]);
	m_bmRat[2].GetBitmap(&bmRat[2]);
	m_bmRat[3].GetBitmap(&bmRat[3]);
	m_nRatw=bmRat[0].bmWidth;
	m_nRath=bmRat[0].bmHeight;
	//���ؾ��κ�������Ŀ����
	m_rectClient=CRect(20,20,380,380);
	m_nRat=RATMAX;
	StartFlag=-1;
	//����è������λͼ�ĳ�ʱλ�ú��˶�����
	m_nCatx=m_rectClient.left+m_rectClient.Width()/2;
	m_nCaty=m_rectClient.top+m_rectClient.Height()/2;
	m_rectCat=CRect(m_nCatx,m_nCaty,m_nCatx+m_nCatw,m_nCaty+m_nCath);
	m_nCatDirection=2;
	srand((unsigned)time(NULL));
	for(int i=0;i<RATMAX;i++)
	{
		m_nRatx[i]=m_rectClient.left+rand()%(m_rectClient.Width()-m_nRatw);
		m_nRaty[i]=m_rectClient.top+rand()%(m_rectClient.Height()-m_nRath);
		m_rectRat[i]=CRect(m_nRatx[i],m_nRaty[i],m_nRatx[i]+m_nRatw,m_nRaty[i]+m_nRath);
		m_nRatDirection[i]=rand()%4;
		m_bRatLive[i]=TRUE;
	}/*FOR*/
	//��ʼ�Ѷ���Ϊ��
	m_nDifficulty=1;
	m_timeWork=m_timeSet=20;//��Ϸʱ��20��
	m_nCatSpeed=5;
	m_nRatSpeed=3;
	m_nWinFlag=-1;

}

CCatCatchRatView::~CCatCatchRatView()
{
}

BOOL CCatCatchRatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCatCatchRatView drawing

void CCatCatchRatView::OnDraw(CDC* pDC)
{
	CCatCatchRatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->Rectangle(CRect(19,19,381,381));
	//��ʾ��Ϸ״̬
	CString strTime;
	CString strRat;
	strTime.Format("ʣ��ʱ��: %2d:%2d:%2d",m_timeWork.GetHours(),m_timeWork.GetMinutes(),m_timeWork.GetSeconds());
	strRat.Format("��ץ����:%3d",m_nRat);
	pDC->TextOut(410,100,strTime);
	pDC->TextOut(410,140,strRat);
	//��ʾè������
	CDC memDC[RATMAX];
	CDC memCatDC;
	CBitmap *pOldDC;
	memCatDC.CreateCompatibleDC(NULL);
	pOldDC=memCatDC.SelectObject(&m_bmCat[m_nCatDirection]);
	pDC->BitBlt(m_nCatx,m_nCaty,m_nCatw,m_nCath,&memCatDC,0,0,SRCAND);
	memCatDC.SelectObject(pOldDC);
	
	//CRect r;
	//r.left=m_nCatx;r.top=m_nCaty;r.right=r.left+m_nCatw;r.bottom=r.top+m_nCath;
	//DrawTransparentBitmap(pDC,m_bmCat[m_nCatDirection],r,RGB(255,255,255));

	for(int i=0;i<RATMAX;i++)
	{
		if(m_bRatLive[i])
		{
			memDC[i].CreateCompatibleDC(NULL);
			pOldDC=memDC[i].SelectObject(&m_bmRat[m_nRatDirection[i]]);
			pDC->BitBlt(m_nRatx[i],m_nRaty[i],m_nRatw,m_nRath,&memDC[i],0,0,SRCAND);
			memDC[i].SelectObject(pOldDC);
		}/*if*/
	}/*for*/
	//��Ϸ����
	if(StartFlag==2)
	{
		pDC->TextOut(50,50,"Game Over!");
		if(m_nWinFlag==0)
		{
			pDC->TextOut(50,100,"è��ʤ!");
		}/*if*/
		if(m_nWinFlag==1)
		{
			pDC->TextOut(50,100,"�����ʤ!");
		}/*if*/
		m_nWinFlag=-1;
	}/*if*/
	
}
	
/////////////////////////////////////////////////////////////////////////////
// CCatCatchRatView drawing funtions
void CCatCatchRatView::DrawTransparentBitmap(CDC *pDC,CBitmap &Image,
											 CRect &rect, COLORREF rgbMask)
{
	CDC ImageDC,MaskDC;
	CBitmap *pOldImage;
	CBitmap maskBitmap,*pOldMaskDCBitmap ;
	
	//Image.LoadBitmap(IDImage);
	ImageDC.CreateCompatibleDC(pDC);
	pOldImage=ImageDC.SelectObject(&Image);
	MaskDC.CreateCompatibleDC(pDC);
	maskBitmap.CreateBitmap( rect.Width(), rect.Height(), 1, 1, NULL );
	pOldMaskDCBitmap = MaskDC.SelectObject( &maskBitmap );
	ImageDC.SetBkColor(rgbMask);
	MaskDC.BitBlt(0,0, rect.Width(), rect.Height(), &ImageDC, 0, 0, SRCCOPY );

	ImageDC.SetBkColor(RGB(255,255,255));
	ImageDC.SetTextColor(RGB(0,0,0));
	ImageDC.BitBlt(0,0, rect.Width(), rect.Height(), &MaskDC, 0, 0, SRCAND);
	pDC->BitBlt(rect.left,rect.top,rect.Width(), rect.Height(), &MaskDC, 0, 0, SRCAND);
	pDC->BitBlt(rect.left,rect.top,rect.Width(), rect.Height(), &ImageDC, 0, 0,SRCPAINT);
	MaskDC.SelectObject(pOldMaskDCBitmap);
	ImageDC.SelectObject(pOldImage);

}
/////////////////////////////////////////////////////////////////////////////
// CCatCatchRatView printing

BOOL CCatCatchRatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCatCatchRatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCatCatchRatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCatCatchRatView diagnostics

#ifdef _DEBUG
void CCatCatchRatView::AssertValid() const
{
	CView::AssertValid();
}

void CCatCatchRatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCatCatchRatDoc* CCatCatchRatView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCatCatchRatDoc)));
	return (CCatCatchRatDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCatCatchRatView message handlers

void CCatCatchRatView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(m_nRat>0)
	{
		//������δ��ץס
		srand((unsigned)time(NULL));
		for(int i=0;i<RATMAX;i++)
		{
			if(m_bRatLive[i])
			{
				//��δ��ץס��������д���
				switch(nIDEvent)
				{
					case 2://�ñ������˶�����
						m_nRatDirection[i]=rand()%4;
						break;
					case 1: //�ı�����λ��
						InvalidateRect(m_rectRat[i]);
						int nRatMoveStep=m_nRatSpeed+rand()%5;//�����ƶ��ľ���
						if((abs(m_nRatx[i]-m_nCatx)<3*m_nRatw) 
									&& (abs(m_nRaty[i]-m_nCaty)<3*m_nRath))
						{	//������󿿽���è�͸ı䷽��
							m_nRatDirection[i]=rand()%4;
						}/*if*/
						switch(m_nRatDirection[i])
						{
							case 0:  //�����ƶ�
								if(m_rectRat[i].top-nRatMoveStep>m_rectClient.top)
								{
									m_rectRat[i].top-=nRatMoveStep;
									m_rectRat[i].bottom-=nRatMoveStep;
									m_nRaty[i]-=nRatMoveStep;
								}/*if*/
								else
								{//�˶����߽��ı䷽��
									m_nRatDirection[i]=rand()%4;
								}/*else*/ 
								break;

							case 1:  //�����ƶ�
								if(m_rectRat[i].bottom+nRatMoveStep<m_rectClient.bottom)
								{
									m_rectRat[i].top+=nRatMoveStep;
									m_rectRat[i].bottom+=nRatMoveStep;
									m_nRaty[i]+=nRatMoveStep;
								}/*if*/
								else
								{//�˶����߽��ı䷽��
									m_nRatDirection[i]=rand()%4;
								}/*else*/ 
								break;
							case 2:  //�����ƶ�
								if(m_rectRat[i].left-nRatMoveStep>m_rectClient.left)
								{
									m_rectRat[i].left-=nRatMoveStep;
									m_rectRat[i].right-=nRatMoveStep;
									m_nRatx[i]-=nRatMoveStep;
								}/*if*/
								else
								{//�˶����߽��ı䷽��
									m_nRatDirection[i]=rand()%4;
								}/*else*/ 
								break;
							case 3:  //�����ƶ�
								if(m_rectRat[i].right+nRatMoveStep<m_rectClient.right)
								{
									m_rectRat[i].left+=nRatMoveStep;
									m_rectRat[i].right+=nRatMoveStep;
									m_nRatx[i]+=nRatMoveStep;
								}/*if*/
								else
								{//�˶����߽��ı䷽��
									m_nRatDirection[i]=rand()%4;
								}/*else*/ 
								break;
						}/*swicth*/
				}/*switch*/
				//�ж��˶����Ƿ�èץס
				if((abs(m_nRatx[i]-m_nCatx)<m_nRatw) && (abs(m_nRaty[i]-m_nCaty)<m_nRath))
				{
					m_nRat--;
					m_bRatLive[i]=false;
				}/*if*/
				InvalidateRect(m_rectRat[i]);
			}/*if*/
		}/*for*/
	
		//������Ϸʣ��ʱ��
		m_timeEnd=m_timeEnd.GetCurrentTime();
		m_timeWork=m_timeSet-(m_timeEnd-m_timeStart);
		InvalidateRect(CRect(410,100,560,160));
		if(!(m_timeWork.GetTotalSeconds()))
		{
			KillTimer(1);
			KillTimer(2);
			StartFlag=2;
			if(m_nRat>0)
			{
				//��Ϸʱ���Ե�������ûץ�꣬ʧ��
				m_nWinFlag=1;
				//MessageBox("è��һ�ߣ����һ��!");
			}/*if*/
			else
			{
				//��Ϸʱ��δ���������Ѿ�ץ�꣬�ɹ�
				m_nWinFlag=0;
				//MessageBox("���һ�ߣ�è��һ��!");
			}/*else*/
			Invalidate();
		}/*if*/
	}/*if*/
	else if(m_timeWork.GetTotalSeconds())
	{
		KillTimer(1);
		KillTimer(2);
		StartFlag=2;
		Invalidate();
		m_nWinFlag=0;
		//MessageBox("���һ�ߣ�è��һ��!");
	}/*else if*/
	
	CView::OnTimer(nIDEvent);
}

void CCatCatchRatView::OnRestart() 
{
	// TODO: Add your command handler code here
	//���¿�ʼ��Ϸ�ĳ�ʼ�����������ó�ʼ����
	StartFlag=-1;
	m_nRat=RATMAX;
	m_timeWork=m_timeSet;
	m_nCatDirection=2;
	
	//����è������λͼ�ĳ�ʱλ�ú��˶�����
	m_nCatx=m_rectClient.left+m_rectClient.Width()/2;
	m_nCaty=m_rectClient.top+m_rectClient.Height()/2;
	m_rectCat=CRect(m_nCatx,m_nCaty,m_nCatx+m_nCatw,m_nCaty+m_nCath);
	srand((unsigned)time(NULL));
	for(int i=0;i<RATMAX;i++)
	{
		m_nRatx[i]=m_rectClient.left+rand()%(m_rectClient.Width()-m_nRatw);
		m_nRaty[i]=m_rectClient.top+rand()%(m_rectClient.Height()-m_nRath);
		m_rectRat[i]=CRect(m_nRatx[i],m_nRaty[i],m_nRatx[i]+m_nRatw,m_nRaty[i]+m_nRath);
		m_nRatDirection[i]=rand()%4;
		m_bRatLive[i]=TRUE;
	}/*FOR*/
	Invalidate();

}

void CCatCatchRatView::OnStart() 
{
	// TODO: Add your command handler code here
	if(StartFlag)
	{
		m_timeStart=m_timeStart.GetCurrentTime();
	}/*if*/
	SetTimer(1,100,NULL);
	SetTimer(2,8000,NULL);
	StartFlag=1;

}

void CCatCatchRatView::OnStop() 
{
	// TODO: Add your command handler code here
	KillTimer(1);
	KillTimer(2);
	StartFlag=0;
}

void CCatCatchRatView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(StartFlag==1)
	{
		//��Ϸ��ʼʱè�ſ����ƶ�
		InvalidateRect(m_rectCat,TRUE);
		switch(nChar)
		{
			case VK_UP:   //�����ƶ�
				if(m_rectCat.top-m_nCatSpeed>m_rectClient.top)
				{
					m_rectCat.top-=m_nCatSpeed;
					m_rectCat.bottom-=m_nCatSpeed;
					m_nCaty-=m_nCatSpeed;
					m_nCatDirection=0;
				}/*if*/
				break;
			case VK_DOWN:   //�����ƶ�
				if(m_rectCat.bottom-m_nCatSpeed<m_rectClient.bottom)
				{
					m_rectCat.top+=m_nCatSpeed;
					m_rectCat.bottom+=m_nCatSpeed;
					m_nCaty+=m_nCatSpeed;
					m_nCatDirection=1;
				}/*if*/
				break;
			case VK_LEFT:   //�����ƶ�
				if(m_rectCat.left-m_nCatSpeed>m_rectClient.left)
				{
					m_rectCat.left-=m_nCatSpeed;
					m_rectCat.right-=m_nCatSpeed;
					m_nCatx-=m_nCatSpeed;
					m_nCatDirection=2;
				}/*if*/
				break;
			case VK_RIGHT:   //�����ƶ�
				if(m_rectCat.right+m_nCatSpeed<m_rectClient.right)
				{
					m_rectCat.left+=m_nCatSpeed;
					m_rectCat.right+=m_nCatSpeed;
					m_nCatx+=m_nCatSpeed;
					m_nCatDirection=3;
				}/*if*/
				break;
		}/*switch*/
		InvalidateRect(m_rectCat,FALSE);
		//�ж�è���ƶ����Ƿ�ץס����
		for(int i=0; i<RATMAX; i++)
		{
			if(m_bRatLive[i] && (abs(m_nRatx[i]-m_nCatx)<m_nRatw) && (abs(m_nRaty[i]-m_nCaty)<m_nRath))
			{
				m_bRatLive[i]=FALSE;
				m_nRat--;
				InvalidateRect(m_rectRat[i]);
				InvalidateRect(CRect(410,100,560,160));
			}/*if*/
		}/*for*/
	}/*if*/

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCatCatchRatView::OnUpdateStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//��Ϸ�����п���ѡֹͣ�˵�
	pCmdUI->Enable(StartFlag==1);
}

void CCatCatchRatView::OnSelect() 
{
	// TODO: Add your command handler code here
	CSelectDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_nDifficulty=dlg.m_nDifficulty;
		switch(m_nDifficulty)
		{
			case 2:
				m_nCatSpeed=8;
				m_nRatSpeed=2;
				m_timeSet=40;
				break;
			case 1:
				m_nCatSpeed=5;
				m_nRatSpeed=3;
				m_timeSet=20;
				break;
			case 0:
				m_nCatSpeed=6;
				m_nRatSpeed=8;
				m_timeSet=10;
				break;
			default:
				AfxMessageBox("Difficulty select error!");
		}/*switch*/

	}/*if*/
}

void CCatCatchRatView::OnUpdateStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(StartFlag<1);
}
