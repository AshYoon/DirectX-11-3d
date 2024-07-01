#pragma once

// � ���ҽ��� ����ҋ� ��� ����ϴ��� ��Ī�ϴ� �뵵 
enum ShaderScope
{
	SS_None = 0,
	SS_VertexShader = (1 << 0), //��Ʈ�÷��� ( 0 0 0 1 )
	SS_PixelShader = (1 << 1), // ( 0 0 1 0 )
	SS_Both = SS_VertexShader | SS_PixelShader // ( 0 0 1 1 ) �� ��Ȳ�� ���� 

};

class Shader
{


public:
	Shader(ComPtr<ID3D11Device> device);
	virtual ~Shader();

	// �����Լ��� ���� �ڽĵ��� override �ؼ� �˾Ƽ� ���� ����� 
	virtual void Create(const wstring& path, const string& name, const string& version) abstract;

	ComPtr<ID3DBlob> GetBlob() { return _blob; }

protected:
	// blob�� ���ο� �����ϴ� path , name , version 3���� �־��ָ�ȴ�.
	void LoadShaderFromFile(const wstring& path, const string& name, const string& version);


protected:

	wstring _path;
	string _name;

	ComPtr<ID3D11Device> _device;

	ComPtr<ID3DBlob> _blob;
};

class VertexShader : public Shader
{
	using Super = Shader;

public:

	VertexShader(ComPtr<ID3D11Device> device);
	~VertexShader();

	ComPtr<ID3D11VertexShader> GetComPtr() { return _vertexShader; };

	virtual void Create(const wstring& path, const string& name, const string& version) override;
						// ���̴� ��� ,       �� ������ �̸�,    ���̴� ���� , blob �̷� �ָ� ��µ� �װ� ��  

private:

protected:


	ComPtr<ID3D11VertexShader> _vertexShader;


	

};


class PixelShader : public Shader
{
	using Super = Shader;

public:

	PixelShader(ComPtr<ID3D11Device> device);
	~PixelShader();

	ComPtr<ID3D11PixelShader> GetComPtr() { return _PixelShader; };

	virtual void Create(const wstring& path, const string& name, const string& version) override;


private:

protected:


	ComPtr<ID3D11PixelShader> _PixelShader;



};

