#pragma once
class brightness : public CDialog
{
	DECLARE_DYNAMIC(brightness)
public:
	brightness(CWnd* pParent = nullptr);
	virtual ~brightness();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_brightness};
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double input1;
};

