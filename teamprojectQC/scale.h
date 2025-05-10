#pragma once
class scale : public CDialog
{
	DECLARE_DYNAMIC(scale)
public:
	scale(CWnd* pParent = nullptr);
	virtual ~scale();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_scale};
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double input1;
};

