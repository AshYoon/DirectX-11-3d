#pragma once
// vertexshader 뿐만아니라 pixel shader단계에서도 적용가능하지만
// 그럼에도 불구하고 처음 배웠을때 가장 일반적으로 사용하는게
//vertex shader 단계여서 VS에 배치 


template<typename T>
class ConstantBuffer
{
public:

	//cpu에있는 메모리를 gpu에 던져줘야하는데 , 먼저 CreateConstatntBuffer 로 버퍼 생성 
	// 상수버퍼를 어떤 용도로 사용할지 정해지지않았기때문에 템플릿을 써야함 



	ConstantBuffer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
		: _device(device) , _deviceContext(deviceContext)
	{

	}
	~ConstantBuffer() {}

	void Create()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_DYNAMIC; // cpu_write + gpu_read
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(T);//TransformData가 명확하지 않기때문에 템플릿 사용 
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = _device->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
		CHECK(hr);
	}

	void CopyData(const T& data)
	{
		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));

		// map으로 데이터를 받아주고 , 이 데이터를 memcpy로 고속복사하고 unmap으로 닫아주기 
		_deviceContext->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		::memcpy(subResource.pData, &data, sizeof(T));
		_deviceContext->Unmap(_constantBuffer.Get(), 0);
	}


	ComPtr<ID3D11Buffer> GetComPtr() { return _constantBuffer; };

private:

	ComPtr<ID3D11Device> _device;

	ComPtr<ID3D11DeviceContext> _deviceContext;


	ComPtr<ID3D11Buffer> _constantBuffer; 







};

