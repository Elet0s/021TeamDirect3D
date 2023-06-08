#pragma once

#include <assert.h>
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <random>

#include <math.h>
#include <float.h>

#include <filesystem>

#include <algorithm>

#include <functional>

#include <thread>
#include <atomic>
#include <mutex>

#include <string>
#include <string_view>
#include <map>
#include <vector>
#include <set>
#include <list>
#include <queue>
#include <deque>

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>	//MS에서 만든 SIMD연산을 사용하는 함수들을 제공받을 수 있다.	
//SIMD(Single Instruction Multiple Data): 한번의 지시로, 정렬된 여러 값들을 취급하는 연산을 동시에 처리하는 명령어 집합.
//대량의 단순 사칙연산들을 빠르게 처리할 수 있으므로 3D렌더링이나 머신러닝 등을 구현할때 유리해진다.
#include <DirectXCollision.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")

