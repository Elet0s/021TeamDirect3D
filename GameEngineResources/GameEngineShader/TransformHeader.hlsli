//cbuffer: 상수 버퍼(Constant Buffer) 구조체.
//각 상수 버퍼는 최대 4096개의 16 * n바이트 크기의 벡터를 보유할 수 있다. 
//각 벡터에는 최대 4개의 32비트 값을 포함할 수 있다. 

//상수버퍼는 최소 16바이트 이상의 크기를 가져야 하는 이유가 무엇??
//->MSDN에도 빈번한 액세스와 업데이트에 맞춰 최적화시켰기 때문이라고만 한다.

//상수버퍼는 프로그램 내부에서 전역변수처럼 사용된다.
cbuffer TransformData : register(b0) //<-register(b0): 렌더링 파이프라인 0번 슬롯에 연결되는 상수 버퍼라는 의미.
    //t: 텍스쳐, c: 버퍼 오프셋, s: 샘플러, u: unordered access view.
    //register(ps_5_0, b0) <-이런 식으로 특정 셰이더나 hlsl컴파일러 버전을 지목해서 사용할 수도 있다고 한다.
{
    float4 localScaleVector_;    //로컬 좌표상 크기. 크기가 0인 물체는 존재할 수 없으므로 기본값이 1이 되어야 한다.
    float4 localRotationVector_; //로컬 좌표상 자전(각도).
    float4 localPositionVector_; //로컬 좌표상 이동(위치).

    float4x4 localScaleMatrix_;    //크기행렬.
    float4x4 localRotationMatrix_; //자전행렬(각도).
    float4x4 localPositionMatrix_; //이동행렬(위치).

    float4x4 localWorldMatrix_;
	//오브젝트의 크기, 자전, 이동행렬이 반영된, 부모 오브젝트의 로컬월드상에서의 월드행렬. 행렬의 중간정산.


    float4 worldScaleVector_; //월드좌표상 크기. 이동하지 않으므로 w는 0으로 설정한다.
    float4 worldRotationVector_; //월드좌표상 회전량. 이동하지 않으므로 w는 0으로 설정한다.
    float4 worldPositionVector_; //월드좌표상 위치. 이동량을 반영해야 하므로 w는 1으로 설정한다.


    float4x4 worldWorldMatrix_;
	//오브젝트의 로컬 크기, 로컬 자전, 로컬 이동행렬에 부모의 월드행렬까지 반영된 최종 월드 행렬.
	//여기에 카메라 컴포넌트의 뷰행렬과 투영행렬까지 거치고 나야 비로소 모니터에 띄울 수 있게 된다.

    float4x4 viewMatrix_; //뷰행렬.
    float4x4 projectionMatrix_; //투영행렬.

    float4x4 worldViewMatrix_; //월드행렬에 뷰행렬이 적용된 행렬.
    float4x4 worldViewProjectionMatrix_; //월드행렬에 뷰행렬 + 투영행렬까지 적용된 행렬.
};

struct InstTransformData
{
    float4 localScaleVector_; //로컬 좌표상 크기. 크기가 0인 물체는 존재할 수 없으므로 기본값이 1이 되어야 한다.
    float4 localRotationVector_; //로컬 좌표상 자전(각도).
    float4 localPositionVector_; //로컬 좌표상 이동(위치).

    float4x4 localScaleMatrix_; //크기행렬.
    float4x4 localRotationMatrix_; //자전행렬(각도).
    float4x4 localPositionMatrix_; //이동행렬(위치).

    float4x4 localWorldMatrix_;
	//오브젝트의 크기, 자전, 이동행렬이 반영된, 부모 오브젝트의 로컬월드상에서의 월드행렬. 행렬의 중간정산.


    float4 worldScaleVector_; //월드좌표상 크기. 이동하지 않으므로 w는 0으로 설정한다.
    float4 worldRotationVector_; //월드좌표상 회전량. 이동하지 않으므로 w는 0으로 설정한다.
    float4 worldPositionVector_; //월드좌표상 위치. 이동량을 반영해야 하므로 w는 1으로 설정한다.

    float4x4 worldWorldMatrix_;
	//오브젝트의 로컬 크기, 로컬 자전, 로컬 이동행렬에 부모의 월드행렬까지 반영된 최종 월드 행렬.
	//여기에 카메라 컴포넌트의 뷰행렬과 투영행렬까지 거치고 나야 비로소 모니터에 띄울 수 있게 된다.

    float4x4 viewMatrix_; //뷰행렬.
    float4x4 projectionMatrix_; //투영행렬.

    float4x4 worldViewMatrix_; //월드행렬에 뷰행렬이 적용된 행렬.
    float4x4 worldViewProjectionMatrix_; //월드행렬에 뷰행렬 + 투영행렬까지 적용된 행렬.
};

StructuredBuffer<InstTransformData> allInstancingTransformDataBuffer : register(t12);