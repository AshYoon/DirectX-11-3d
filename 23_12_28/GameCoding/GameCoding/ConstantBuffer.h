#pragma once
// vertexshader �Ӹ��ƴ϶� pixel shader�ܰ迡���� ���밡��������
// �׷����� �ұ��ϰ� ó�� ������� ���� �Ϲ������� ����ϴ°�
//vertex shader �ܰ迩�� VS�� ��ġ 


template<typename T>
class ConstantBuffer
{
public:

	//cpu���ִ� �޸𸮸� gpu�� ��������ϴµ� , ���� CreateConstatntBuffer �� ���� ���� 
	// ������۸� � �뵵�� ������� ���������ʾұ⶧���� ���ø��� ����� 



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
		desc.ByteWidth = sizeof(T);//TransformData�� ��Ȯ���� �ʱ⶧���� ���ø� ��� 
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = _device->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
		CHECK(hr);
	}

	void CopyData(const T& data)
	{
		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));

		// map���� �����͸� �޾��ְ� , �� �����͸� memcpy�� ��Ӻ����ϰ� unmap���� �ݾ��ֱ� 
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

