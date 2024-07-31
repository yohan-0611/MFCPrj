
// MFCPrjDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCPrj.h"
#include "MFCPrjDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCPrjDlg 대화 상자



CMFCPrjDlg::CMFCPrjDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPRJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_EDIT_TRYNUMBER, m_EditTryNumber);
	DDX_Control(pDX, IDC_STATIC_Center, m_StaticCenter);
}

BEGIN_MESSAGE_MAP(CMFCPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_Random, &CMFCPrjDlg::OnBnClickedBtnRandom)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CMFCPrjDlg::OnBnClickedBtnLoad)
END_MESSAGE_MAP()


// CMFCPrjDlg 메시지 처리기

BOOL CMFCPrjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCPrjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCPrjDlg::OnBnClickedBtnRandom()
{
	// 0.2초의 딜레이를 위해
	const int delay = 200; // 200ms = 0.2초

	// 화면의 클라이언트 영역 크기 가져오기
	CRect rect;
	GetClientRect(&rect);
	int nWidth = rect.Width();
	int nHeight = rect.Height();
	

	// 여백을 추가하여 실제 그리기 영역의 높이를 계산합니다.
	int nImageHeight = nHeight - 50; // 50 픽셀의 여백

	int nBpp = 8;



	// 이미지를 생성합니다.
	if (m_Image == NULL) {
		m_Image.Create(nWidth, -nImageHeight, nBpp);
	}
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_Image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	// `GetWindowText`로부터 값을 얻어옵니다.
	CString strTryNumber;
	m_EditTryNumber.GetWindowText(strTryNumber);
	int nTryNumber = _ttoi(strTryNumber);

	// 모든 원을 그리기 전에 초기화
	memset(fm,0x00, nWidth * nImageHeight);

	for (int i = 0; i < nTryNumber; i++) {
		// 원의 랜덤한 반지름과 위치 설정
		int nRadius = rand() % 50 + 10; // 10부터 60까지의 랜덤한 반지름
		int x = rand() % (nWidth - 2 * nRadius);
		int y = rand() % (nImageHeight - 2 * nRadius); // 높이에서 여백을 고려

		int nColor = rand() % 256;

		CString g_strFileImage = _T("c:\\image\\save.bmp");
		g_strFileImage.Format(_T("c:\\image\\save%d.bmp"), i);

		// 이미지 초기화
		memset(fm, 0x00, nWidth * nImageHeight);

		// 원 그리기
		drawCircle(fm, x, y, nRadius, nColor);

		// 화면 갱신
		updateDisplay();

		// 딜레이
		Sleep(delay);

		//저장
		m_Image.Save(g_strFileImage);
	}
}





void CMFCPrjDlg::updateDisplay()
{
	CClientDC dc(this);
	m_Image.Draw(dc, 0, 50);
}

void CMFCPrjDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_Image.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = nGray;
		}
	}
}

BOOL CMFCPrjDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;
	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}

void CMFCPrjDlg::OnBnClickedBtnLoad()
{
	// CFileDialog 객체를 생성합니다. (열기 대화 상자)
	CFileDialog fileDlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Bitmap Files (*.bmp)|*.bmp||"));

	// 파일 대화 상자를 표시합니다.
	if (fileDlg.DoModal() == IDOK) {
		// 선택한 파일의 경로를 가져옵니다.
		CString strFilePath = fileDlg.GetPathName();

		TRACE(_T("Selected file path: %s\n"), strFilePath);

		// m_Image가 이미 초기화되어 있다면 해제합니다.
		if (m_Image.GetWidth() > 0 && m_Image.GetHeight() > 0) {
			m_Image.Destroy(); // 이전 이미지 해제
		}

		// 선택한 이미지를 로드하여 m_Image에 저장합니다.
		HRESULT hr = m_Image.Load(strFilePath);


		// 디버깅을 위한 이미지 크기 로깅
		TRACE(_T("Image loaded successfully: Width=%d, Height=%d\n"), m_Image.GetWidth(), m_Image.GetHeight());

		// 원의 중심과 반지름을 찾습니다.
		int centerX, centerY;
		double radius;
		if (detectCircleInImage(centerX, centerY, radius)) {
			// 원을 찾은 경우, 이미지에 중심과 반지름을 표시합니다.
			drawCircleInfo(centerX, centerY, radius);

		}
		else {
			AfxMessageBox(_T("원 탐지 실패"));
		}

		// 디스플레이 업데이트
		updateDisplay();
	}
}

bool CMFCPrjDlg::detectCircleInImage(int& centerX, int& centerY, double& radius)
{
	// 이미지 정보 가져오기
	int width = m_Image.GetWidth();
	int height = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();
	unsigned char* pPixels = (unsigned char*)m_Image.GetBits();

	// 중심 좌표와 반지름 초기화
	centerX = 0;
	centerY = 0;
	radius = 0.0;

	// 회색 원 탐지를 위한 임계값
	const int grayThreshold = 30; // 회색과 검은색을 구분하는 기준값
	int xSum = 0, ySum = 0, count = 0;

	// 원의 경계 및 중심 계산
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			// 픽셀 값을 가져옵니다.
			int pixel = pPixels[y * nPitch + x];

			// 회색 영역 탐지
			if (pixel >= grayThreshold) { // 회색으로 간주
				xSum += x;
				ySum += y;
				++count;
			}
		}
	}

	if (count == 0) return false; // 경계가 없음

	// 원의 중심 계산
	centerX = xSum / count;
	centerY = ySum / count;

	// 반지름 계산 (중심에서 경계까지의 평균 거리)
	double radiusSum = 0.0;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int pixel = pPixels[y * nPitch + x];
			if (pixel >= grayThreshold) { // 회색 영역에 대해 거리 계산
				double dist = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
				radiusSum += dist;
			}
		}
	}

	radius = radiusSum / count;
	return true;
}

void CMFCPrjDlg::drawCircleInfo(int centerX, int centerY, double radius)
{
	// CImage를 CPaintDC로 그리기 위해 DC를 가져옵니다.
	CDC* pDC = CDC::FromHandle(m_Image.GetDC());

	// 중심을 기준으로 선을 그립니다.
	CPen pen(PS_DASH, 1, RGB(255, 255, 255)); // 흰색 점선
	CPen* pOldPen = pDC->SelectObject(&pen);

	// 수평, 수직 중심선 그리기 (좌측과 위쪽만 그리기)
	pDC->MoveTo(centerX, 0);
	pDC->LineTo(centerX, centerY); // 위쪽으로 선을 그립니다.
	pDC->MoveTo(0, centerY);
	pDC->LineTo(centerX, centerY); // 좌측으로 선을 그립니다.

	// 반지름 표시를 위한 선을 그립니다.
	CPen redPen(PS_SOLID, 2, RGB(255, 0, 0)); // 빨간색 실선
	pDC->SelectObject(&redPen);
	pDC->MoveTo(centerX, centerY);
	pDC->LineTo(centerX + static_cast<int>(radius), centerY);

	// 정보 표시를 위한 텍스트 출력
	CString info;
	info.Format(_T("Radius: %.2f"), radius);

	// 텍스트 색상 및 위치 설정
	pDC->SetTextColor(RGB(0, 255, 0)); // 녹색 텍스트
	pDC->SetBkMode(TRANSPARENT); // 배경 투명
	pDC->TextOut(centerX + static_cast<int>(radius) + 10, centerY - 10, info); // 원의 우측에 텍스트 출력

	// Static Text에 중심 좌표 설정
	CString centerText;
	centerText.Format(_T("=(%d, %d)"), centerX, centerY);
	SetDlgItemText(IDC_STATIC_Center, centerText);

	// 변경된 DC를 반환
	pDC->SelectObject(pOldPen);
	m_Image.ReleaseDC();
}









