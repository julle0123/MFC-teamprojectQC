
// teamprojectQCDoc.cpp: CteamprojectQCDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "teamprojectQC.h"
#endif
#include "brightness.h"
#include "scale.h"
#include "teamprojectQCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CteamprojectQCDoc

IMPLEMENT_DYNCREATE(CteamprojectQCDoc, CDocument)

BEGIN_MESSAGE_MAP(CteamprojectQCDoc, CDocument)
END_MESSAGE_MAP()


// CteamprojectQCDoc 생성/소멸

CteamprojectQCDoc::CteamprojectQCDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CteamprojectQCDoc::~CteamprojectQCDoc()
{
}

BOOL CteamprojectQCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CteamprojectQCDoc serialization

void CteamprojectQCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		LoadImageFile(ar);
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CteamprojectQCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CteamprojectQCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CteamprojectQCDoc::SetSearchContent(const CString& value)
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

// CteamprojectQCDoc 진단

#ifdef _DEBUG
void CteamprojectQCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CteamprojectQCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CteamprojectQCDoc 명령


void CteamprojectQCDoc::LoadImageFile(CArchive& ar)
{
	int i, maxValue;
	char type[20], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	// 파일의 헤더 읽기
	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".PGM") == 0 || strcmp(strrchr(fname, '.'), ".pgm") == 0)
	{
		ar.ReadString(type, 15);
		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imageWidth, &imageHeight);
		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);
		if (strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;

	}
	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 ||
		strcmp(strrchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
			return;
		}
		imageWidth = 256;
		imageHeight = 256;
		depth = 1;
	}
	inputImg = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	resultImg = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	for (i = 0; i < imageHeight; i++) {
		inputImg[i] = (unsigned char*)malloc(imageWidth * depth);
		resultImg[i] = (unsigned char*)malloc(imageWidth * depth);
	}
	// 영상 데이터 읽기
	for (i = 0; i < imageHeight; i++)
		ar.Read(inputImg[i], imageWidth * depth);
	// TODO: 여기에 구현 코드 추가.
}


void CteamprojectQCDoc::LoadSecondImageFile(CArchive& ar)
{
	int i, maxValue;
	char type[20], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	// 파일의 헤더 읽기
	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 ||
		strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".PGM") == 0 ||
		strcmp(strrchr(fname, '.'), ".pgm") == 0)
	{
		ar.ReadString(type, 15);
		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imageWidth, &imageHeight);
		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);
		if (strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;
	}
	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 ||
		strcmp(strrchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
			return;
		}
		imageWidth = 256;
		imageHeight = 256;
		depth = 1;
	}
	// 기억장소 할당
	inputImg2 = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	resultImg2 = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	for (i = 0; i < imageHeight; i++) {
		inputImg2[i] = (unsigned char*)malloc(imageWidth * depth);
		resultImg2[i] = (unsigned char*)malloc(imageWidth * depth);
	}
	// 영상 데이터 읽기
	for (i = 0; i < imageHeight; i++)
		ar.Read(inputImg2[i], imageWidth * depth);
	// TODO: 여기에 구현 코드 추가.
}


void CteamprojectQCDoc::LoadTwoImages()
{
	CFile file;
	CFileDialog dlg(TRUE);
	AfxMessageBox("Select the First Image");
	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		LoadImageFile(ar);
		file.Close();
	}
	AfxMessageBox("Select the Second Image");
	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		LoadSecondImageFile(ar);
		file.Close();
	}
}

double** CteamprojectQCDoc::malloc_2D_double(int a, int b) //화소연산값
{
	double** retMemory;


	retMemory = new double* [a];
	for (int i = 0; i < a; i++)
		retMemory[i] = new double[b];

	return retMemory;
}

unsigned char** CteamprojectQCDoc::malloc2D(int a, int b) //출력 크기 저장 함수
{
	unsigned char** retMemory;
	retMemory = new unsigned char* [a];
	for (int i = 0; i < a; i++)
		retMemory[i] = new unsigned char[b];
	return retMemory;
}

void CteamprojectQCDoc::Difference() //영상차
{
	LoadTwoImages();
	int value = 0;
	int m = 0;
	int n = 0;

	for (int x = 0; x < imageHeight; x++) {
		for (int y = 0; y < imageWidth; y++) {
			value = inputImg[x][y] - inputImg2[x][y];
			resultImg[x][y] = ((value >= 0) ? value : -value);
			//? 앞에 조건식에따라 결과값이 참이면 반환값1이 반환하고, 결과값이 거짓이면 반환값 2가 반환됨
		}
	}

	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if (inputImg[y][x] != inputImg2[y][x])
			{
				AfxMessageBox(_T("다른 사진"));
				return;
			}
		}
	}
	AfxMessageBox(_T("같은 사진"));
}


void CteamprojectQCDoc::BinaryDiff() //2진차
{
	LoadTwoImages();
	int x, y, temp, temp1;
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++)
		{
			temp = inputImg[y][x];
			if (temp > 128) temp = 255;
			else temp = 0;
			resultImg[y][x] = (unsigned char)temp;
			temp1 = inputImg2[y][x];
			if (temp1 > 128) temp1 = 255;
			else temp1 = 0;
			resultImg2[y][x] = (unsigned char)temp1;
		}

	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if (resultImg[y][x] != resultImg2[y][x])
			{
				AfxMessageBox(_T("다른 사진"));
				return;
			}
		}
	}
	AfxMessageBox(_T("같은 사진"));
}


void CteamprojectQCDoc::Sharpening() //선명화 차이
{
	LoadTwoImages();
	float kernel[3][3] = { {0, -1, 0}, {-1, 5, -1}, {0, -1, 0} };
	Convolve(kernel);
	// TODO: 여기에 구현 코드 추가.
}


void CteamprojectQCDoc::Convolve(float mask[][3]) //회선연산
{
	int i, j, x, y;
	int sum = 0;
	double** tmpImg = malloc_2D_double(imageHeight + 2, imageWidth + 2);
	for (x = 0; x < imageHeight + 2; x++)
		for (y = 0; y < imageWidth + 2; y++)
			tmpImg[x][y] = 0;
	for (x = 1; x < imageHeight + 1; x++)
		for (y = 1; y < imageWidth + 1; y++)
			tmpImg[x][y] = inputImg[x - 1][y - 1];
	for (x = 0; x < imageHeight; x++)
		for (y = 0; y < imageWidth; y++)
		{
			sum = 0;
			for (i = 0; i < 3; i++)
				for (j = 0; j < 3; j++)
					sum += (int)(tmpImg[x + i][y + j] * mask[i][j]);
			if (sum > 256) sum = 255;
			if (sum < 0) sum = 0;
			resultImg[x][y] = (unsigned char)sum;
		}
	int a, b, c, d;
	int sum2 = 0;
	double** tmpimage = malloc_2D_double(imageHeight + 2, imageWidth + 2);
	for (a = 0; a < imageHeight + 2; a++)
		for (b = 0; b < imageWidth + 2; b++)
			tmpimage[a][b] = 0;
	for (a = 1; a < imageHeight + 1; a++)
		for (b = 1; b < imageWidth + 1; b++)
			tmpimage[a][b] = inputImg2[a - 1][b - 1];
	for (a = 0; a < imageHeight; a++)
		for (b = 0; b < imageWidth; b++)
		{
			sum2 = 0;
			for (c = 0; c < 3; c++)
				for (d = 0; d < 3; d++)
					sum2 += (int)(tmpimage[a + c][b + d] * mask[c][d]);
			if (sum2 > 256) sum2 = 255;
			if (sum2 < 0) sum2 = 0;
			resultImg2[a][b] = (unsigned char)sum2;
		}
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if (resultImg[y][x] != resultImg2[y][x])
			{
				AfxMessageBox(_T("다른 사진"));
				return;
			}
		}
	}
	AfxMessageBox(_T("같은 사진"));
}





void CteamprojectQCDoc::Expansion() //팽창
{
	LoadTwoImages();

	int x, y, max;
	for (y = 1; y < imageWidth - 1; y++)
		for (x = 1; x < imageHeight - 1; x++) {
			max = 0;
			if (inputImg[y - 1][x - 1] > max) max = inputImg[y - 1][x - 1];
			if (inputImg[y - 1][x] > max) max = inputImg[y - 1][x];
			if (inputImg[y - 1][x + 1] > max) max = inputImg[y - 1][x + 1];
			if (inputImg[y][x - 1] > max) max = inputImg[y][x - 1];
			if (inputImg[y][x] > max) max = inputImg[y][x];
			if (inputImg[y][x + 1] > max) max = inputImg[y][x + 1];
			if (inputImg[y + 1][x - 1] > max) max = inputImg[y + 1][x - 1];
			if (inputImg[y + 1][x] > max) max = inputImg[y + 1][x];
			if (inputImg[y + 1][x + 1] > max) max = inputImg[y + 1][x + 1];
			resultImg[y][x] = max; // 최대값을 결과 영상에 저장
		}


	int x1, y1, max1;
	for (y1 = 1; y1 < imageWidth - 1; y1++)
		for (x1 = 1; x1 < imageHeight - 1; x1++) {
			max1 = 0;
			if (inputImg2[y1 - 1][x1 - 1] > max1) max1 = inputImg2[y1 - 1][x1 - 1];
			if (inputImg2[y1 - 1][x1] > max1) max1 = inputImg2[y1 - 1][x1];
			if (inputImg2[y1 - 1][x1 + 1] > max1) max1 = inputImg2[y1 - 1][x1 + 1];
			if (inputImg2[y1][x1 - 1] > max1) max1 = inputImg2[y1][x1 - 1];
			if (inputImg2[y1][x1] > max1) max1 = inputImg2[y1][x1];
			if (inputImg2[y1][x1 + 1] > max1) max1 = inputImg2[y1][x1 + 1];
			if (inputImg2[y1 + 1][x1 - 1] > max1) max1 = inputImg2[y1 + 1][x1 - 1];
			if (inputImg2[y1 + 1][x1] > max1) max1 = inputImg2[y1 + 1][x1];
			if (inputImg2[y1 + 1][x1 + 1] > max1) max1 = inputImg2[y1 + 1][x1 + 1];
			resultImg2[y1][x1] = max1; // 최대값을 결과 영상에 저장
		}
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if (resultImg[y][x] != resultImg2[y][x])
			{
				AfxMessageBox(_T("다른 사진"));
				return;
			}
		}
	}
	AfxMessageBox(_T("같은 사진"));
}


void CteamprojectQCDoc::Erosion() //침식
{
	LoadTwoImages();
	int x, y, min;
	for (y = 1; y < imageWidth - 1; y++)
		for (x = 1; x < imageHeight - 1; x++) {
			min = imageWidth - 1;
			if (inputImg[y - 1][x - 1] < min) min = inputImg[y - 1][x - 1];
			if (inputImg[y - 1][x] < min) min = inputImg[y - 1][x];
			if (inputImg[y - 1][x + 1] < min) min = inputImg[y - 1][x + 1];
			if (inputImg[y][x - 1] < min) min = inputImg[y][x - 1];
			if (inputImg[y][x] < min) min = inputImg[y][x];
			if (inputImg[y][x + 1] < min) min = inputImg[y][x + 1];
			if (inputImg[y + 1][x - 1] < min) min = inputImg[y + 1][x - 1];
			if (inputImg[y + 1][x] < min) min = inputImg[y + 1][x];
			if (inputImg[y + 1][x + 1] < min) min = inputImg[y + 1][x + 1];
			resultImg[y][x] = min; // 최소값을 결과 영상에 저장
		}

	int x1, y1, min1;
	for (y1 = 1; y1 < imageWidth - 1; y1++)
		for (x1 = 1; x1 < imageHeight - 1; x1++) {
			min1 = imageWidth - 1;
			if (inputImg2[y1 - 1][x1 - 1] < min1) min1 = inputImg2[y1 - 1][x1 - 1];
			if (inputImg2[y1 - 1][x1] < min1) min1 = inputImg2[y1 - 1][x1];
			if (inputImg2[y1 - 1][x1 + 1] < min1) min1 = inputImg2[y1 - 1][x1 + 1];
			if (inputImg2[y1][x1 - 1] < min1) min1 = inputImg2[y1][x1 - 1];
			if (inputImg2[y1][x1] < min1) min1 = inputImg2[y1][x1];
			if (inputImg2[y1][x1 + 1] < min1) min1 = inputImg2[y1][x1 + 1];
			if (inputImg2[y1 + 1][x1 - 1] < min1) min1 = inputImg2[y1 + 1][x1 - 1];
			if (inputImg2[y1 + 1][x1] < min1) min1 = inputImg2[y1 + 1][x1];
			if (inputImg2[y1 + 1][x1 + 1] < min1) min1 = inputImg2[y1 + 1][x1 + 1];
			resultImg2[y1][x1] = min1; // 최소값을 결과 영상에 저장
		}
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if (resultImg[y][x] != resultImg2[y][x])
			{
				AfxMessageBox(_T("다른 사진"));
				return;
			}
		}
	}
	AfxMessageBox(_T("같은 사진"));
}


void CteamprojectQCDoc::Ero()
{
	int x, y, min;
	for (y = 1; y < imageWidth - 1; y++)
		for (x = 1; x < imageHeight - 1; x++) {
			min = imageWidth - 1;
			if (inputImg[y - 1][x - 1] < min) min = inputImg[y - 1][x - 1];
			if (inputImg[y - 1][x] < min) min = inputImg[y - 1][x];
			if (inputImg[y - 1][x + 1] < min) min = inputImg[y - 1][x + 1];
			if (inputImg[y][x - 1] < min) min = inputImg[y][x - 1];
			if (inputImg[y][x] < min) min = inputImg[y][x];
			if (inputImg[y][x + 1] < min) min = inputImg[y][x + 1];
			if (inputImg[y + 1][x - 1] < min) min = inputImg[y + 1][x - 1];
			if (inputImg[y + 1][x] < min) min = inputImg[y + 1][x];
			if (inputImg[y + 1][x + 1] < min) min = inputImg[y + 1][x + 1];
			resultImg[y][x] = min; // 최소값을 결과 영상에 저장
		}
}


void CteamprojectQCDoc::Ero2()
{
	int x1, y1, min1;
	for (y1 = 1; y1 < imageWidth - 1; y1++)
		for (x1 = 1; x1 < imageHeight - 1; x1++) {
			min1 = imageWidth - 1;
			if (inputImg2[y1 - 1][x1 - 1] < min1) min1 = inputImg2[y1 - 1][x1 - 1];
			if (inputImg2[y1 - 1][x1] < min1) min1 = inputImg2[y1 - 1][x1];
			if (inputImg2[y1 - 1][x1 + 1] < min1) min1 = inputImg2[y1 - 1][x1 + 1];
			if (inputImg2[y1][x1 - 1] < min1) min1 = inputImg2[y1][x1 - 1];
			if (inputImg2[y1][x1] < min1) min1 = inputImg2[y1][x1];
			if (inputImg2[y1][x1 + 1] < min1) min1 = inputImg2[y1][x1 + 1];
			if (inputImg2[y1 + 1][x1 - 1] < min1) min1 = inputImg2[y1 + 1][x1 - 1];
			if (inputImg2[y1 + 1][x1] < min1) min1 = inputImg2[y1 + 1][x1];
			if (inputImg2[y1 + 1][x1 + 1] < min1) min1 = inputImg2[y1 + 1][x1 + 1];
			resultImg2[y1][x1] = min1; // 최소값을 결과 영상에 저장
		}
}


void CteamprojectQCDoc::Exp()
{
	int x, y, max;
	for (y = 1; y < imageWidth - 1; y++)
		for (x = 1; x < imageHeight - 1; x++) {
			max = 0;
			if (inputImg[y - 1][x - 1] > max) max = inputImg[y - 1][x - 1];
			if (inputImg[y - 1][x] > max) max = inputImg[y - 1][x];
			if (inputImg[y - 1][x + 1] > max) max = inputImg[y - 1][x + 1];
			if (inputImg[y][x - 1] > max) max = inputImg[y][x - 1];
			if (inputImg[y][x] > max) max = inputImg[y][x];
			if (inputImg[y][x + 1] > max) max = inputImg[y][x + 1];
			if (inputImg[y + 1][x - 1] > max) max = inputImg[y + 1][x - 1];
			if (inputImg[y + 1][x] > max) max = inputImg[y + 1][x];
			if (inputImg[y + 1][x + 1] > max) max = inputImg[y + 1][x + 1];
			resultImg[y][x] = max; // 최대값을 결과 영상에 저장
		}
}


void CteamprojectQCDoc::Exp2()
{
	int x, y, max;
	for (y = 1; y < imageWidth - 1; y++)
		for (x = 1; x < imageHeight - 1; x++) {
			max = 0;
			if (inputImg2[y - 1][x - 1] > max) max = inputImg2[y - 1][x - 1];
			if (inputImg2[y - 1][x] > max) max = inputImg2[y - 1][x];
			if (inputImg2[y - 1][x + 1] > max) max = inputImg2[y - 1][x + 1];
			if (inputImg2[y][x - 1] > max) max = inputImg2[y][x - 1];
			if (inputImg2[y][x] > max) max = inputImg2[y][x];
			if (inputImg2[y][x + 1] > max) max = inputImg2[y][x + 1];
			if (inputImg2[y + 1][x - 1] > max) max = inputImg2[y + 1][x - 1];
			if (inputImg2[y + 1][x] > max) max = inputImg2[y + 1][x];
			if (inputImg2[y + 1][x + 1] > max) max = inputImg2[y + 1][x + 1];
			resultImg2[y][x] = max; // 최대값을 결과 영상에 저장
		}
}

void CteamprojectQCDoc::CopyResultToInput()
{
	int x, y;
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++)
			inputImg[y][x] = resultImg[y][x];
}


void CteamprojectQCDoc::CopyResultToInput2()
{
	int x, y;
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++)
			inputImg2[y][x] = resultImg2[y][x];
}

void CteamprojectQCDoc::Opening() //열림
{
	LoadTwoImages();
	int x, y;
	double** tmpImg = malloc_2D_double(imageHeight, imageWidth);
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++)
			tmpImg[y][x] = inputImg[y][x];
	Ero();
	for (y = 0; y < 2; y++)
	{
		CopyResultToInput();
		Ero();
	}
	for (y = 0; y < 3; y++)
	{
		CopyResultToInput();
		Exp();
	}
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++)
			inputImg[y][x] = tmpImg[y][x];

	int x1, y1;
	double** tmpImg1 = malloc_2D_double(imageHeight, imageWidth);
	for (y1 = 0; y1 < imageHeight; y1++)
		for (x1 = 0; x1 < imageWidth; x1++)
			tmpImg1[y1][x1] = inputImg2[y1][x1];
	Ero2();
	for (y1 = 0; y1 < 2; y1++)
	{
		CopyResultToInput2();
		Ero2();
	}
	for (y1 = 0; y1 < 3; y1++)
	{
		CopyResultToInput2();
		Exp2();
	}
	for (y1 = 0; y1 < imageHeight; y1++)
		for (x1 = 0; x1 < imageWidth; x1++)
			inputImg2[y1][x1] = tmpImg1[y1][x1];
	// TODO: 여기에 구현 코드 추가.
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if (resultImg[y][x] != resultImg2[y][x])
			{
				AfxMessageBox(_T("다른 사진"));
				return;
			}
		}
	}
	AfxMessageBox(_T("같은 사진"));
}


void CteamprojectQCDoc::Closing() //닫힘
{
	LoadTwoImages();
	int x, y;
	double** tmpImg = malloc_2D_double(imageHeight, imageWidth);
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++)
			tmpImg[y][x] = inputImg[y][x];
	Exp();
	for (y = 0; y < 2; y++)
	{
		CopyResultToInput();
		Exp();
	}
	for (y = 0; y < 3; y++)
	{
		CopyResultToInput();
		Ero();
	}
	for (y = 0; y < imageHeight; y++)
		for (x = 0; x < imageWidth; x++)
			inputImg[y][x] = tmpImg[y][x];

	int x1, y1;
	double** tmpImg1 = malloc_2D_double(imageHeight, imageWidth);
	for (y1 = 0; y1 < imageHeight; y1++)
		for (x1 = 0; x1 < imageWidth; x1++)
			tmpImg1[y1][x1] = inputImg2[y1][x1];
	Exp2();
	for (y = 0; y < 2; y++)
	{
		CopyResultToInput2();
		Exp2();
	}
	for (y = 0; y < 3; y++)
	{
		CopyResultToInput2();
		Ero2();
	}
	for (y1 = 0; y1 < imageHeight; y1++)
		for (x1 = 0; x1 < imageWidth; x1++)
			inputImg2[y1][x1] = tmpImg1[y1][x1];
	// TODO: 여기에 구현 코드 추가.
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if (resultImg[y][x] != resultImg2[y][x])
			{
				AfxMessageBox(_T("다른 사진"));
				return;
			}
		}
	}
	AfxMessageBox(_T("같은 사진"));
}





void CteamprojectQCDoc::ZoomIn() //확대
{
	LoadTwoImages();
	scale dlg;
	if (dlg.DoModal() != IDOK)
		return;
	int value = (int)dlg.input1;
	OutimageWidth = imageWidth * value;
	OutimageHeight = imageHeight * value;
	resultImg = malloc2D(OutimageWidth, OutimageHeight);
	for (int y = 0; y < OutimageHeight; y++) {
		for (int x = 0; x < OutimageWidth; x++) {
			resultImg[y][x] = inputImg[y / value][x / value];
		}
	}
	OutimageWidth = imageWidth * value;
	OutimageHeight = imageHeight * value;
	resultImg2 = malloc2D(OutimageWidth, OutimageHeight);
	for (int y1 = 0; y1 < OutimageHeight; y1++) {
		for (int x1 = 0; x1 < OutimageWidth; x1++) {
			resultImg2[y1][x1] = inputImg2[y1 / value][x1 / value];
		}
	}
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if (resultImg[y][x] != resultImg2[y][x])
			{
				AfxMessageBox(_T("다른 사진"));
				return;
			}
		}
	}
	AfxMessageBox(_T("같은 사진"));
}




void CteamprojectQCDoc::Contrast() //명암
{
	LoadTwoImages();
	brightness dlg;
	if (dlg.DoModal() != IDOK)
		return;
	int num = (int)dlg.input1;
	int value = 0;
	int value2 = 0;
	for (int x = 0; x < imageWidth; x++) {
		for (int y = 0; y < imageHeight; y++) {
			value = inputImg[x][y] + num;
			if (value > 255) resultImg[x][y] = 255;
			else resultImg[x][y] = value;
		}
	}
	for (int x = 0; x < imageWidth; x++) {
		for (int y = 0; y < imageHeight; y++) {
			value2 = inputImg2[x][y] + num;
			if (value2 > 255) resultImg2[x][y] = 255;
			else resultImg2[x][y] = value2;
		}
	}
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if (resultImg[y][x] != resultImg2[y][x])
			{
				AfxMessageBox(_T("다른 사진"));
				return;
			}
		}
	}
	AfxMessageBox(_T("같은 사진"));
}


void CteamprojectQCDoc::Embossing() //엠보싱
{
	LoadTwoImages();
	int i, j;
	const int ma = 3;
	double** intmpImg = malloc_2D_double(imageHeight+2, imageWidth+2);
	double** outtmpImg = malloc_2D_double(imageHeight+2, imageWidth+2);
	double mask[ma][ma] = { {-1,0,0}, {0,0,0}, {0,0,1} };
	//임시입력 ->0
	for (int i = 0; i < imageHeight + 2; i++)
		for (int j = 0; j < imageWidth + 2; j++)
			intmpImg[i][j] = 0;
	//입력영상 -> 임시입력영상으로
	for (int i = 0; i < imageHeight; i++)
		for (int j = 0; j < imageWidth; j++)
			intmpImg[i + 1][j + 1] = inputImg[i][j];
	//회선연산(모든 입력 화소값에 대해 이동하면서 수행하는 것을 회선이라고 함)
	double S;//합계
	for (int i = 0; i < imageHeight; i++) {
		for (int j = 0; j < imageWidth; j++) {
			S = 0;
			for (int m = 0; m < ma; m++) {
				for (int n = 0; n < ma; n++) {
					S += intmpImg[i + m][j + n] * mask[m][n];
				}
			}
			outtmpImg[i][j] = S;//여기까지는 선명화랑 똑같음.
		}
	}
	//후처리
	for (int i = 0; i < imageHeight; i++) {
		for (int j = 0; j < imageWidth; j++) {
			outtmpImg[i][j] += 127;
		}
	}
	//출력
	for (int i = 0; i < imageHeight; i++)
		for (int j = 0; j < imageWidth; j++) {
			double v = outtmpImg[i][j];
			if (v > 255)
				v = 255;
			else if (v < 0)
				v = 0;
			resultImg[i][j] = v;
		}
	int x, y;
	const int maa = 3;
	double** intmpImg2 = malloc_2D_double(imageHeight+2, imageWidth+2);
	double** outtmpImg2 = malloc_2D_double(imageHeight+2, imageWidth+2);
	double mamask[maa][maa] = { {-1,0,0}, {0,0,0}, {0,0,1} };
	//임시입력 ->0
	for (int x = 0; x < imageHeight + 2; x++)
		for (int y = 0; y < imageWidth + 2; y++)
			intmpImg2[x][y] = 0;
	//입력영상 -> 임시입력영상으로
	for (int x = 0; x < imageHeight; x++)
		for (int y = 0; y < imageWidth; y++)
			intmpImg2[x + 1][y + 1] = inputImg2[x][y];
	//회선연산(모든 입력 화소값에 대해 이동하면서 수행하는 것을 회선이라고 함)
	double Sum;//합계
	for (int x = 0; x < imageHeight; x++) {
		for (int y = 0; y < imageWidth; y++) {
			Sum = 0;
			for (int m1 = 0; m1 < maa; m1++) {
				for (int n1 = 0; n1 < maa; n1++) {
					Sum += intmpImg2[x + m1][y + n1] * mask[m1][n1];
				}
			}
			outtmpImg2[x][y] = Sum;//여기까지는 선명화랑 똑같음.
		}
	}
	//후처리
	for (int x = 0; x < imageHeight; x++) {
		for (int y = 0; y < imageWidth; y++) {
			outtmpImg2[x][y] += 127;
		}
	}
	//출력
	for (int x = 0; x < imageHeight; x++)
		for (int y = 0; y < imageWidth; y++) {
			double Vv = outtmpImg2[x][y];
			if (Vv > 255)
				Vv = 255;
			else if (Vv < 0)
				Vv = 0;
			resultImg2[x][y] = Vv;
		}
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if (resultImg[y][x] != resultImg2[y][x])
			{
				AfxMessageBox(_T("다른 사진"));
				return;
			}
		}
	}
	AfxMessageBox(_T("같은 사진"));
}
