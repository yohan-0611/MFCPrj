
// MFCPrjDlg.h: 헤더 파일
//

#pragma once


// CMFCPrjDlg 대화 상자
class CMFCPrjDlg : public CDialogEx
{
// 생성입니다.
private:
	CImage m_Image;
public:
	CMFCPrjDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPRJ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	CStatic m_StaticCenter;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRandom();
	void updateDisplay();
	void drawCircle(unsigned char* fm, int i, int j, int nRadius, int nGray);
	BOOL isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	bool detectCircleInImage(int& centerX, int& centerY, double& radius);
	void drawCircleInfo(int centerX, int centerY, double radius);

	CEdit m_EditTryNumber;
	afx_msg void OnBnClickedBtnLoad();	
};
