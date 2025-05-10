#include "pch.h"
#include "scale.h"
#include "teamprojectQC.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(scale, CDialog)

scale::scale(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_scale, pParent)
	, input1(0)
{

}
scale::~scale()
{
}
void scale::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_scale1, input1);
}

BEGIN_MESSAGE_MAP(scale, CDialog)
END_MESSAGE_MAP()
