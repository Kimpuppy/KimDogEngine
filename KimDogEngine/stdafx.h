// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <windowsx.h>
#include "Resource.h"

// C 런타임 헤더 파일
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>
#include <wrl.h>

// C++ 런타임 헤더 파일
#include <string>
#include <list>
#include <vector>
#include <map>
#include <stack>
#include <functional>
#include <algorithm>
#include <memory>

// Direct3D 관련 헤더 파일
#include <d3d9.h>
#include <d3dx9.h>

// ComPtr 사용을 위한 구문
using Microsoft::WRL::ComPtr;

// 매크로 관련 헤더 파일
#include "Core.h"

// 매니져 관련 헤더 파일
#include "Input.h"
#include "Time.h"
#include "Scene.h"
#include "SceneManager.h"

// 오브젝트, 컴포넌트 관련 헤더 파일
#include "GameObject.h"
#include "Timer.h"
#include "Transform.h"
#include "CameraComponent.h"
#include "Camera.h"
#include "SpriteRenderer.h"