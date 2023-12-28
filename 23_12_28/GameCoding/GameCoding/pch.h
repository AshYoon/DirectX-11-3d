#pragma once
#include "Types.h"
#include "Values.h"
#include "Struct.h"

//공용으로 사용할 기능들 
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
//원래는 2010년도에서 2014년도 학원을 다녔으면 별도로 라이브러리르 받아서 외부에서 받아서 헤더파일이랑 연동했어야했는데 이제는 
// direcx 가 범용적으로 사용되기떄문에 아예 MS에서 표준키트에 추가를 해놓았다 Win 10 이상이면 포함이 되어있다

#include <d3d11.h> // 굳이 다운할필요가없다
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>

// direct x tex ? 얘또한 ms 에서 만들어서 비공식으로 지원을 해주는것 
// 프로젝트 속성에 일반 ( general ) 에서 출력 디렉토리- 결과물을 저장할 장소 
// 중간 디렉터리는 스킵 
// C++ 일반에 라이브러리를 사용하겠다하면 실제로 라이브러리를 모아놓은 include 폴더랑 lib 파일이들어가있는 경로도 
// 추가포함 디렉터리에 들어가서 binari가 아니라 Libraries / include 
// 빌드 결과물이 binaries 에 들어가고 Include , Lib 에 우리 라이브러리




