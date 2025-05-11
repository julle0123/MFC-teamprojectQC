
// teamprojectQCView.cpp: CteamprojectQCView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "teamprojectQC.h"
#endif

#include "teamprojectQCDoc.h"
#include "teamprojectQCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define TWO_IMAGES 1 
#define THREE_IMAGES 2 
#define ZOOM_IMAGES 1 
#define result2_IMAGES 3
int viewMode;

// CteamprojectQCView

IMPLEMENT_DYNCREATE(CteamprojectQCView, CView)

BEGIN_MESSAGE_MAP(CteamprojectQCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CteamprojectQCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_Difference, &CteamprojectQCView::OnDifference)
	ON_COMMAND(ID_BinaryDiff, &CteamprojectQCView::OnBinarydiff)
	ON_COMMAND(ID_Sharpening, &CteamprojectQCView::OnSharpening)
	ON_COMMAND(ID_Expansion, &CteamprojectQCView::OnExpansion)
	ON_COMMAND(ID_Erosion, &CteamprojectQCView::OnErosion)
	ON_COMMAND(ID_Opening, &CteamprojectQCView::OnOpening)
	ON_COMMAND(ID_closing, &CteamprojectQCView::Onclosing)
	ON_COMMAND(ID_ZoomIn, &CteamprojectQCView::OnZoomin)
	ON_COMMAND(ID_brightness, &CteamprojectQCView::Onbrightness)
	ON_COMMAND(ID_Embossing, &CteamprojectQCView::OnEmbossing)
END_MESSAGE_MAP()

// CteamprojectQCView 생성/소멸

CteamprojectQCView::CteamprojectQCView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CteamprojectQCView::~CteamprojectQCView()
{
}

BOOL CteamprojectQCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CteamprojectQCView 그리기

void CteamprojectQCView::OnDraw(CDC* pDC)
{
	CRect rect(500, 500, 1000, 1000);
	GetClientRect(&rect);
	CteamprojectQCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->depth == 1) { // 흑백 영상 출력
		for (int y = 0; y < pDoc->imageHeight; y++) // 입력 영상 출력
			for (int x = 0; x < pDoc->imageWidth; x++)
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x],
					pDoc->inputImg[y][x], pDoc->inputImg[y][x]));

		if (viewMode == THREE_IMAGES) {

			rect = CRect(255, 0, 2000, 2000);
			CBrush brush(RGB(255, 255, 255));
			pDC->FillRect(&rect, &brush);

			rect = CRect(0, 255, 2000, 2000);
			pDC->FillRect(&rect, &brush);

			for (int y = 0; y < pDoc->imageHeight; y++) // 두번째 입력 영상 출력
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x]));


			for (int y = 0; y < pDoc->imageHeight; y++)  // 결과 영상 출력
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y,
						RGB(pDoc->resultImg[y][x],
							pDoc->resultImg[y][x],
							pDoc->resultImg[y][x]));

		}

		else if (viewMode == result2_IMAGES) {

			rect = CRect(255, 0, 2000, 2000);
			CBrush brush(RGB(255, 255, 255));
			pDC->FillRect(&rect, &brush);

			rect = CRect(0, 255, 2000, 2000);
			pDC->FillRect(&rect, &brush);



			for (int y = 0; y < pDoc->imageHeight; y++) // 두번째 입력 영상 출력
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x]));

			for (int y = 0; y < pDoc->imageHeight; y++) // 결과 영상 출력
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x, y + pDoc->imageHeight,
						RGB(pDoc->resultImg[y][x],
							pDoc->resultImg[y][x],
							pDoc->resultImg[y][x]));
			for (int y = 0; y < pDoc->imageHeight; y++) // 2번째 결과 영상 출력
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth+30, y + pDoc->imageHeight,
						RGB(pDoc->resultImg2[y][x],
							pDoc->resultImg2[y][x],
							pDoc->resultImg2[y][x]));
		}
		else if (viewMode == ZOOM_IMAGES) {

			rect = CRect(255, 0, 2000, 2000);
			CBrush brush(RGB(255, 255, 255));
			pDC->FillRect(&rect, &brush);

			rect = CRect(0, 255, 2000, 2000);
			pDC->FillRect(&rect, &brush);

			pDC->FillRect(&rect, &brush);
			for (int y = 0; y < pDoc->imageHeight; y++) // 두번째 입력 영상 출력
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x]));

			for (int y = 0; y < pDoc->OutimageHeight; y++) // zoom결과 영상 출력
				for (int x = 0; x < pDoc->OutimageWidth; x++)
					pDC->SetPixel(x , y+ pDoc ->imageHeight,
						RGB(pDoc->resultImg[y][x],
							pDoc->resultImg[y][x],
							pDoc->resultImg[y][x]));

			for (int y = 0; y < pDoc->OutimageHeight; y++) // 2번째 결과 영상 출력
				for (int x = 0; x < pDoc->OutimageWidth; x++)
					pDC->SetPixel(x + pDoc->OutimageWidth + 30, y + pDoc->imageHeight,
						RGB(pDoc->resultImg2[y][x],
							pDoc->resultImg2[y][x],
							pDoc->resultImg2[y][x]));
		}
		else
		{
			rect = CRect(255, 0, 2000, 2000);
			CBrush brush(RGB(255, 255, 255));
			pDC->FillRect(&rect, &brush);

			rect = CRect(0, 255, 2000, 2000);
			pDC->FillRect(&rect, &brush);

			for (int y = 0; y < pDoc->imageHeight; y++) // 결과 영상 출력
				for (int x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x + pDoc->imageWidth + 60, y,
						RGB(pDoc->resultImg[y][x],
							pDoc->resultImg[y][x],
							pDoc->resultImg[y][x]));
		}
	}

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CteamprojectQCView 인쇄


void CteamprojectQCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CteamprojectQCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CteamprojectQCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CteamprojectQCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CteamprojectQCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CteamprojectQCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CteamprojectQCView 진단

#ifdef _DEBUG
void CteamprojectQCView::AssertValid() const
{
	CView::AssertValid();
}

void CteamprojectQCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CteamprojectQCDoc* CteamprojectQCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CteamprojectQCDoc)));
	return (CteamprojectQCDoc*)m_pDocument;
}
#endif //_DEBUG


// CteamprojectQCView 메시지 처리기


void CteamprojectQCView::OnDifference() //영상차
{
	CteamprojectQCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	viewMode = THREE_IMAGES;
	pDoc->Difference();
	Invalidate(FALSE);
}


void CteamprojectQCView::OnBinarydiff() //이진차
{
	CteamprojectQCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->BinaryDiff();
	viewMode = result2_IMAGES;
	Invalidate(FALSE);
}


void CteamprojectQCView::OnSharpening() //선명화
{
	CteamprojectQCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Sharpening();
	viewMode = result2_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CteamprojectQCView::OnExpansion() //팽창
{
	CteamprojectQCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Expansion();
	viewMode = result2_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CteamprojectQCView::OnErosion() //침식
{
	CteamprojectQCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Erosion();
	viewMode = result2_IMAGES;
	Invalidate(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CteamprojectQCView::OnOpening() //열림
{
	CteamprojectQCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Opening();
	viewMode = result2_IMAGES;
	Invalidate(FALSE);
}


void CteamprojectQCView::Onclosing() //닫힘
{
	CteamprojectQCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Closing();
	viewMode = result2_IMAGES;
	Invalidate(FALSE);
}


void CteamprojectQCView::OnZoomin() //확대
{
	CteamprojectQCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->ZoomIn();
	viewMode = ZOOM_IMAGES;
	Invalidate(FALSE);
}


void CteamprojectQCView::Onbrightness() //명암
{
	CteamprojectQCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	viewMode = result2_IMAGES;
	pDoc->Contrast();
	Invalidate(FALSE);
}


void CteamprojectQCView::OnEmbossing()
{
	CteamprojectQCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	viewMode = result2_IMAGES;
	pDoc->Embossing();
	Invalidate(FALSE);
}
