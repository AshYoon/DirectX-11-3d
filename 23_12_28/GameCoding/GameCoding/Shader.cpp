#include "pch.h"
#include "Shader.h"

Shader::Shader(ComPtr<ID3D11Device> device)
	:_device(device)
{

}

Shader::~Shader()
{

}

void Shader::LoadShaderFromFile(const wstring& path, const string& name, const string& version)
{
	_path = path;

	_name = name;

	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION; // 디버그용도 , 최적화는 건너뛰겠다는뜻

	//pch 에서 d3dcompiler.h 에서 지원해준다 
	HRESULT hr = ::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		_blob.GetAddressOf(), // 우리가만든 blob객체에 채워준다 
		nullptr
	);
	//LPCWSTR , 즉 W string을 (W캐릭터포인터) 받고있고 그다음부터는 W가없이그냥 STR

//이제 이걸 범용적으로 사용하면된다 
	CHECK(hr);



}

VertexShader::VertexShader(ComPtr<ID3D11Device> device) : Super(device)
{
}

VertexShader::~VertexShader()
{
}

void VertexShader::Create(const wstring& path, const string& name, const string& version)
{
	LoadShaderFromFile(path, name, version);
		HRESULT hr = _device->CreateVertexShader(_blob->GetBufferPointer(),
			_blob->GetBufferSize(),
		nullptr,
		_vertexShader.GetAddressOf()
		);
	CHECK(hr);

}

PixelShader::PixelShader(ComPtr<ID3D11Device> device) : Super(device)
{
}

PixelShader::~PixelShader()
{
}

void PixelShader::Create(const wstring& path, const string& name, const string& version)
{
	LoadShaderFromFile(path, name, version);

	HRESULT hr = _device->CreatePixelShader(
		_blob->GetBufferPointer(),
		_blob->GetBufferSize(),
		nullptr,
		_PixelShader.GetAddressOf()
	);
	CHECK(hr);
}
