#pragma once
class VertexBuffer
{
public:
	VertexBuffer(ComPtr<ID3D11Device> device);
	~VertexBuffer();

	ComPtr<ID3D11Buffer> GetComptr() { return _vertexBuffer; };

	uint32 GetStride() { return _stride; };
	uint32 GetOffset() { return _offset; };
	uint32 GetCount() { return _count; };


	//vertices �Ӹ��ƴ϶� �پ��ѿ뵵�� ����ϱ����� ���ø����� ���� ��

	template<typename T>
	void Create(const vector<T>& _vertices)
	{
		//���ο� ���ҽ� �������ϴ� device���� create buffer
		//Input Assembler�ܰ迡�� vertex buffer���־��ְ��ִ°�

		_stride = sizeof(T);
		_count = static_cast<uint32>(_vertices.size());


		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE; // �������ذ� ��ĥ�Ͼ�� immutable
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // vertex buffer bind �뵵�� ����Ҳ���
		desc.ByteWidth = (uint32)(_stride*_count); // Vertex �޸� size x vertices vector size()
		// ���� ���� �� 

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertices.data(); // vertex �迭�� ù��°�� �����ּ� 

		// ������ ���� ������� gpu�ʿ� ���۰� ��������鼭 �ʱⰪ�� ���簡�ȴ� 
		//�״����� gpu�� read only�� �۵��̵ȴ� , �̰� ���� ���� 
		HRESULT hr = _graphics->GetDevice()->CreateBuffer(&desc, &data, _vertextBuffer.GetAddressOf());
		CHECK(hr);
	}

private:

	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11Buffer> _vertexBuffer;

	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;

};

