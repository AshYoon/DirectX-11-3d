#pragma once

// 어떤 리소스를 사용할떄 어디서 사용하는지 지칭하는 용도 
enum ShaderScope
{
	SS_None = 0,
	SS_VertexShader = (1 << 0), //비트플래그 ( 0 0 0 1 )
	SS_PixelShader = (1 << 1), // ( 0 0 1 0 )
	SS_Both = SS_VertexShader | SS_PixelShader // ( 0 0 1 1 ) 의 상황을 묘사 

};

class Shader
{


public:
	Shader(ComPtr<ID3D11Device> device);
	virtual ~Shader();

	// 가상함수로 만들어서 자식들이 override 해서 알아서 파일 만들게 
	virtual void Create(const wstring& path, const string& name, const string& version) abstract;

	ComPtr<ID3DBlob> GetBlob() { return _blob; }

protected:
	// blob은 내부에 존재하니 path , name , version 3개만 넣어주면된다.
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
						// 쉐이더 경로 ,       이 파일의 이름,    쉐이더 버전 , blob 이런 애를 뱉는데 그걸 줘  

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

