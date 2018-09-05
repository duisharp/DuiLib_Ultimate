#ifndef GifAnimUI_h__
#define GifAnimUI_h__

#pragma once

namespace DuiLib {
	class UILIB_API CGifAnimUI: public CControlUI {
		enum {
			EVENT_TIEM_ID = 100,
		};
		DECLARE_DUICONTROL (CGifAnimUI)
	public:
		CGifAnimUI (void);
		virtual ~CGifAnimUI (void);

		LPCTSTR	GetClass () const;
		LPVOID	GetInterface (LPCTSTR pstrName);
		void	DoInit ();
		bool	DoPaint (HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
		void	DoEvent (TEventUI& event);
		void	SetVisible (bool bVisible = true);
		void	SetAttribute (LPCTSTR pstrName, LPCTSTR pstrValue);
		void	SetBkImage (LPCTSTR pStrImage);
		LPCTSTR GetBkImage ();

		void	SetAutoPlay (bool bIsAuto = true);
		bool	IsAutoPlay () const;
		void	SetAutoSize (bool bIsAuto = true);
		bool	IsAutoSize () const;
		void	PlayGif ();
		void	PauseGif ();
		void	StopGif ();

	private:
		void	InitGifImage ();
		void	DeleteGif ();
		void    OnTimer (UINT_PTR idEvent);
		void	DrawFrame (HDC hDC);		// ����GIFÿ֡

	private:
		Gdiplus::Image			*m_pGifImage		= nullptr;
		UINT					m_nFrameCount		= 0;		// gifͼƬ��֡��
		UINT					m_nFramePosition	= 0;		// ��ǰ�ŵ��ڼ�֡
		Gdiplus::PropertyItem	*m_pPropertyItem	= nullptr;	// ֡��֮֡����ʱ��

		CDuiString				m_sBkImage;
		bool					m_bIsAutoPlay		= true;		// �Ƿ��Զ�����gif
		bool					m_bIsAutoSize		= false;	// �Ƿ��Զ�����ͼƬ���ô�С
		bool					m_bIsPlaying		= false;
	};
}

#endif // GifAnimUI_h__
