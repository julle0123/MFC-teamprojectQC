
// teamprojectQCDoc.h: CteamprojectQCDoc 클래스의 인터페이스
//


#pragma once


class CteamprojectQCDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CteamprojectQCDoc() noexcept;
	DECLARE_DYNCREATE(CteamprojectQCDoc)

// 특성입니다.
public:
	unsigned char** inputImg; // 입력 영상의 기억 장소에 대한 포인터 변수
	unsigned char** inputImg2; // 입력 영상의 기억 장소에 대한 포인터 변수
	unsigned char** resultImg; // 출력 영상의 기억 장소에 대한 포인터 변수
	unsigned char** resultImg2; // 출력 영상의 기억 장소에 대한 포인터 변수
	int imageWidth; // 영상의 가로 크기
	int imageHeight; // 영상의 세로 크기
	int OutimageWidth; // 출력영상의 가로 크기
	int OutimageHeight; // 출력영상의 세로 크기
	int depth; // 1 = 흑백 영상, 3 = 컬러 영상
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CteamprojectQCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void LoadImageFile(CArchive& ar);
	void LoadSecondImageFile(CArchive& ar);
	void LoadTwoImages();
	void Difference();
	void BinaryDiff();
	void Sharpening();
	void Convolve(float mask[][3]);
	double** malloc_2D_double(int a, int b);
	void Expansion();
	void Erosion();
	void Ero();
	void Ero2();
	void Exp();
	void Exp2();
	void Opening();
	void Closing();
	void CopyResultToInput();
	void CopyResultToInput2();
	void ZoomIn();
	unsigned char** malloc2D(int a, int b);
	void Contrast();
	void Embossing();
};
