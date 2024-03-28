#pragma once

class Environment : public Singleton<Environment>
{
private:
	friend class Singleton;

	Environment();
	~Environment();

public:
	void Update();
	void RenderUI();

	Camera* GetMainCamera() { return mainCamera; }

private:
	void CreateProjection();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();

private:	
	Camera* mainCamera;

	MatrixBuffer* projectionBuffer;
	MatrixBuffer* uiViewBuffer;

	ID3D11SamplerState* samplerState;
	ID3D11BlendState* blendState;
	ID3D11RasterizerState* rasterizerState;

};