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

#include <string>
#include <map>
#include <vector>
#include <set>
#include <list>

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>	//MS���� ���� SIMD������ ����ϴ� �Լ����� �������� �� �ִ�.	
//SIMD(Single Instruction Multiple Data): �ѹ��� ���÷�, ���ĵ� ���� ������ ����ϴ� ������ ���ÿ� ó���ϴ� ��ɾ� ����.
//�뷮�� �ܼ� ��Ģ������� ������ ó���� �� �����Ƿ� 3D�������̳� �ӽŷ��� ���� �����Ҷ� ����������.
#include <DirectXCollision.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")

