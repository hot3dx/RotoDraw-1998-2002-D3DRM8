#pragma once
#include "pch.h"
#include "d3dx12.h"

namespace DX
{
	// Provides an interface for an application that owns DeviceResources to be notified of the device being lost or created.
	interface IDeviceNotify
	{
		virtual void OnDeviceLost() = 0;
		virtual void OnDeviceRestored() = 0;
	};

	static const UINT c_frameCount = 3;		// Use triple buffering.
	
	// Controls all the DirectX device resources.
	class DeviceResources
	{
	public:
		DeviceResources();// (DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D32_FLOAT);
		void SetWindow(Windows::UI::Core::CoreWindow^ window);
		void SetLogicalSize(Windows::Foundation::Size logicalSize);
		void SetCurrentOrientation(Windows::Graphics::Display::DisplayOrientations currentOrientation);
		void SetDpi(float dpi);
		void ValidateDevice();
		void Present();
		void WaitForGpu();
		void UpdateStereoState();
		void HandleDeviceLost();
		void RegisterDeviceNotify(IDeviceNotify* deviceNotify);
		void Trim();
		void CheckStereoEnabledStatus();


		// The size of the render target, in pixels.
		Windows::Foundation::Size	GetOutputSize() const				{ return m_outputSize; }

		// The size of the render target, in dips.
		Windows::Foundation::Size	GetLogicalSize() const				{ return m_logicalSize; }

		// Get the render target size
		Windows::Foundation::Size GetRenderTargetSize() const { return m_d3dRenderTargetSize; }
		bool                      GetStereoState() const { return m_stereoEnabled; }
		float						GetDpi() const						{ return m_effectiveDpi; }
		bool						IsDeviceRemoved() const				{ return m_deviceRemoved; }

		// D3D Accessors.
		ID3D12Device*				GetD3DDevice() const				{ return m_d3dDevice.Get(); }
		IDXGISwapChain3*			GetSwapChain() const				{ return m_swapChain.Get(); }
		IDXGISwapChain1*			GetSwapChain1() const               { return m_swapChain1.Get(); }
		ID3D12Resource*				GetRenderTarget() const				{ return m_renderTargets[m_currentFrame].Get(); }
		ID3D12Resource*				GetDepthStencil() const				{ return m_depthStencil.Get(); }
		ID3D12CommandQueue*			GetCommandQueue() const				{ return m_commandQueue.Get(); }
		ID3D12CommandAllocator*		GetCommandAllocator() const			{ return m_commandAllocators[m_currentFrame].Get(); }
		DXGI_FORMAT					GetBackBufferFormat() const			{ return m_backBufferFormat; }
		DXGI_FORMAT					GetDepthBufferFormat() const		{ return m_depthBufferFormat; }
		D3D12_VIEWPORT				GetScreenViewport() const			{ return m_screenViewport; }
		DirectX::XMFLOAT4X4			GetOrientationTransform3D() const	{ return m_orientationTransform3D; }
		UINT						GetCurrentFrameIndex() const		{ return m_currentFrame; }

		CD3DX12_CPU_DESCRIPTOR_HANDLE GetRenderTargetView() const
		{
			return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_currentFrame, m_rtvDescriptorSize);
		}
		CD3DX12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const
		{
			return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_dsvHeap->GetCPUDescriptorHandleForHeapStart());
		}

		// D3D11
		// This is the DPI that will be reported back to the app. It takes into account whether the app supports high resolution screens or not.
		float											m_effectiveDpi;
		D3D11_VIEWPORT                                  m_screenViewport11;
		// Transforms used for display orientation.
		DirectX::XMFLOAT4X4								m_orientationTransform3D;
		DirectX::XMFLOAT4X4								m_orientationTransform3D11;


		// New stuff from game

		 // D3D Accessors.
		ID3D11Device2*          GetD3D11Device() const { return m_d3d11Device.Get(); }
		ID3D11Device*           GetD3D11Dev() const { return m_d3d11Dev.Get(); }
		ID3D11DeviceContext2*   GetD3D11DeviceContext() const { return m_d3d11Context.Get(); }
		ID3D11On12Device*       GetD3D11On12Device() const { return m_d3d11On12Device.Get(); }
		IDXGISwapChain1*        GetSwap11Chain() const { return m_swapChain1.Get(); }
		
		D3D_FEATURE_LEVEL       GetDevice11FeatureLevel() const { return m_d3dFeatureLevel; }
		ID3D11RenderTargetView* GetBackBufferRenderTargetView11() const { return m_d3dRenderTargetView.Get(); }
		ID3D11RenderTargetView* GetBackBufferRenderTargetViewRight11() const { return m_d3dRenderTargetViewRight.Get(); }
		ID3D11DepthStencilView* GetDepthStencilView11() const { return m_d3dDepthStencilView.Get(); }
		D3D11_VIEWPORT          GetScreenViewport11() const { return m_screenViewport11; }
		DirectX::XMFLOAT4X4     GetOrientationTransform3D11() const { return m_orientationTransform3D11; }

		// D2D Accessors.
		ID2D1Factory2*          GetD2DFactory() const { return m_d2dFactory.Get(); }
		ID2D1Device1*           GetD2DDevice() const { return m_d2dDevice.Get(); }
		ID2D1DeviceContext1*    GetD2DDeviceContext() const { return m_d2dContext.Get(); }
		ID2D1Bitmap1*           GetD2DTargetBitmap() const { return m_d2dTargetBitmap.Get(); }
		ID2D1Bitmap1*           GetD2DTargetBitmapRight() const { return m_d2dTargetBitmapRight.Get(); }
		IDWriteFactory2*        GetDWriteFactory() const { return m_dwriteFactory.Get(); }
		IWICImagingFactory2*    GetWicImagingFactory() const { return m_wicFactory.Get(); }
		D2D1::Matrix3x2F        GetOrientationTransform2D() const { return m_orientationTransform2D; }

	private:
		// D3D12
		void CreateDeviceIndependentResources();
		void CreateDeviceResources();
		void CreateDeviceResources12();
		void CreateWindowSizeDependentResources();
		void UpdateRenderTargetSize();
		void MoveToNextFrame();
		DXGI_MODE_ROTATION ComputeDisplayRotation();
		void GetHardwareAdapter(IDXGIAdapter1** ppAdapter);

		UINT											m_currentFrame;

		// Direct3D objects.
		Microsoft::WRL::ComPtr<ID3D12Device>			m_d3dDevice;
		Microsoft::WRL::ComPtr<IDXGIFactory4>			m_dxgiFactory;
		Microsoft::WRL::ComPtr<IDXGISwapChain3>			m_swapChain;
		Microsoft::WRL::ComPtr<IDXGISwapChain1>			m_swapChain1;
		Microsoft::WRL::ComPtr<ID3D12Resource>			m_renderTargets[c_frameCount];
		Microsoft::WRL::ComPtr<ID3D12Resource>			m_depthStencil;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	m_rtvHeap;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	m_dsvHeap;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>		m_commandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>	m_commandAllocators[c_frameCount];
		DXGI_FORMAT										m_backBufferFormat;
		DXGI_FORMAT										m_depthBufferFormat;
		D3D12_VIEWPORT									m_screenViewport;
		UINT											m_rtvDescriptorSize;
		bool											m_deviceRemoved;

		// CPU/GPU Synchronization.
		Microsoft::WRL::ComPtr<ID3D12Fence>				m_fence;
		UINT64											m_fenceValues[c_frameCount];
		HANDLE											m_fenceEvent;

		// Cached reference to the Window.
		Platform::Agile<Windows::UI::Core::CoreWindow>	m_window;

		// Cached device properties.
		Windows::Foundation::Size						m_d3dRenderTargetSize;
		Windows::Foundation::Size						m_outputSize;
		Windows::Foundation::Size						m_logicalSize;
		Windows::Graphics::Display::DisplayOrientations	m_nativeOrientation;
		Windows::Graphics::Display::DisplayOrientations	m_currentOrientation;
		float											m_dpi;

		
	    
		// D3D11
		void CreateDeviceIndependentResources11();
		void CreateDeviceResources11();
		void CreateWindowSizeDependentResources11();
		DXGI_MODE_ROTATION ComputeDisplayRotation11();
		void CheckStereoEnabledStatus11();

		// Direct3D objects.
		Microsoft::WRL::ComPtr<ID3D11Device2>           m_d3d11Device;
		Microsoft::WRL::ComPtr<ID3D11Device>            m_d3d11Dev;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext2>    m_d3d11Context;

		///
		/// Needed for D3D11)n12
		////

		Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3d11DeviceContext;
		Microsoft::WRL::ComPtr<ID3D11On12Device>        m_d3d11On12Device;
		Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain11;

		// Direct3D rendering objects. Required for 3D.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_d3dRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_d3dRenderTargetViewRight;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_d3dDepthStencilView;
		// twice D3D11_VIEWPORT                                  m_screenViewport11;

		// Direct2D drawing components.
		Microsoft::WRL::ComPtr<ID2D1Factory2>           m_d2dFactory;
		Microsoft::WRL::ComPtr<ID2D1Device1>            m_d2dDevice;
		Microsoft::WRL::ComPtr<ID2D1DeviceContext1>     m_d2dContext;
		Microsoft::WRL::ComPtr<ID2D1Bitmap1>            m_d2dTargetBitmap;
		Microsoft::WRL::ComPtr<ID2D1Bitmap1>            m_d2dTargetBitmapRight;

		// DirectWrite drawing components.
		Microsoft::WRL::ComPtr<IDWriteFactory2>         m_dwriteFactory;
		Microsoft::WRL::ComPtr<IWICImagingFactory2>     m_wicFactory;
		Microsoft::WRL::ComPtr<ID2D1Bitmap1>            m_d2dRenderTarget;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>    m_textBrush;
		Microsoft::WRL::ComPtr<IDWriteTextFormat>       m_textFormat;
		Microsoft::WRL::ComPtr<IDWriteTextFormat>       m_smallTextFormat;

		// Cached reference to the Window.
	
		// Cached device properties.
		D3D_FEATURE_LEVEL                               m_d3dFeatureLevel;
		bool                                            m_stereoEnabled;

		// Transforms used for display orientation.
		D2D1::Matrix3x2F                                m_orientationTransform2D;
		
		// The IDeviceNotify can be held directly as it owns the DeviceResources.
		IDeviceNotify*                                  m_deviceNotify;
	};
}
