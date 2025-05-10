#include "pch.h"
#include "brightness.h"
#include "teamprojectQC.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(brightness, CDialog)

brightness::brightness(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_brightness, pParent)
	, input1(0)
{

}
brightness::~brightness()
{
}
void brightness::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_num, input1);
}

BEGIN_MESSAGE_MAP(brightness, CDialog)
END_MESSAGE_MAP()
