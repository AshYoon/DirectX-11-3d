#pragma once
#include "Types.h"
#include "Values.h"
#include "Struct.h"

//�������� ����� ��ɵ� 
//STL
#include <vector>
#include <unordered_map>
#include <map>
#include <list>

using namespace std;

// Win
#include <windows.h>
#include <assert.h>

//DX 
//������ 2010�⵵���� 2014�⵵ �п��� �ٳ����� ������ ���̺귯���� �޾Ƽ� �ܺο��� �޾Ƽ� ��������̶� �����߾���ߴµ� ������ 
// direcx �� ���������� ���Ǳ⋚���� �ƿ� MS���� ǥ��ŰƮ�� �߰��� �س��Ҵ� Win 10 �̻��̸� ������ �Ǿ��ִ�

#include <d3d11.h> // ���� �ٿ����ʿ䰡����
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>

// direct x tex ? ����� ms ���� ���� ��������� ������ ���ִ°� 
// ������Ʈ �Ӽ��� �Ϲ� ( general ) ���� ��� ���丮- ������� ������ ��� 
// �߰� ���͸��� ��ŵ 
// C++ �Ϲݿ� ���̺귯���� ����ϰڴ��ϸ� ������ ���̺귯���� ��Ƴ��� include ������ lib �����̵��ִ� ��ε� 
// �߰����� ���͸��� ���� binari�� �ƴ϶� Libraries / include 
// ���� ������� binaries �� ���� Include , Lib �� �츮 ���̺귯��




