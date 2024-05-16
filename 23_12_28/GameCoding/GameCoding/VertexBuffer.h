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


	//vertices 뿐만아니라 다양한용도로 사용하기위해 템플릿으로 선언 ㄴ

	template<typename T>
	void Create(const vector<T>& _vertices)
	{
		//새로운 리소스 만들어야하니 device에서 create buffer
		//Input Assembler단계에서 vertex buffer를넣어주고있는거

		_stride = sizeof(T);
		_count = static_cast<uint32>(_vertices.size());


		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE; // 세팅해준거 고칠일없어서 immutable
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // vertex buffer bind 용도로 사용할꺼다
		desc.ByteWidth = (uint32)(_stride*_count); // Vertex 메모리 size x vertices vector size()
		// 버퍼 묘사 끝 

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertices.data(); // vertex 배열의 첫번째의 시작주소 

		// 설정한 값을 기반으로 gpu쪽에 버퍼가 만들어지면서 초기값이 복사가된다 
		//그다음은 gpu만 read only로 작동이된다 , 이게 정점 버퍼 
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

