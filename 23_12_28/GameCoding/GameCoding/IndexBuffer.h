#pragma once
class IndexBuffer
{

public:
	IndexBuffer(ComPtr<ID3D11Device> device);
	~IndexBuffer();

	ComPtr<ID3D11Buffer> GetComPtr() { return _indexBuffer; };
	uint32 GetStride() { return _stride; };
	uint32 GetOffset() { return _offset; };
	uint32 GetCount() { return _count; };
	

	//인덱스 버퍼는 uint32 가 일반적이라 굳이 템플릿으로 안만들어도됨

	void Create(const vector<uint32>& indices);



private:

	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11Buffer> _indexBuffer;

	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;
};

