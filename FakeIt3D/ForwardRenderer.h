#pragma once
#include <d3d11.h>
#include "Object.h"

class ForwardRenderer
{
private:
	HRESULT createDepthBufferStencil();
	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11RenderTargetView* m_pRenderTargetView; 
	ID3D11InputLayout* m_pInputLayout; 

	ID3D11VertexShader* m_pVertexShader; 
	ID3D11PixelShader* m_pPixelShader; 
	void createInputDescription(ID3DBlob* pVS, ID3DBlob* pPS);

	void createShaders(); 

	Object* tempObject;

public:
	ForwardRenderer();
	~ForwardRenderer();

	void draw(); 

	Object* getObject(); 
}; 