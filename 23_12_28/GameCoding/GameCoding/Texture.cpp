#include "pch.h"
#include "Texture.h"

Texture::Texture(ComPtr<ID3D11Device> device)
	:_device(device)
{


}

Texture::~Texture()
{
}

void Texture::Create(const wstring& path)
{

	//이미지를 가져오는 함수는 여러개가있다 
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;

	HRESULT	hr = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &md, img);
	CHECK(hr);
	//여기까지하면 이미지를 로드한것 

	//shader resource view 라는걸 만들어야한다 
	hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView.GetAddressOf());

	CHECK(hr);
}
