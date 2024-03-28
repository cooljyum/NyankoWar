#include "Framework.h"

Quad::Quad(Vector2 size, bool isAdd) : size(size), GameObject(isAdd)
{
	tag = "Quad";

	mesh = new Mesh<VertexUV>();
	MakeMesh();
	mesh->CreateMesh();
}

Quad::Quad(wstring textureFile, bool isAdd, Vector2 startUV, Vector2 endUV, Vector2 pos)
{
	tag = "Quad";

	material->SetTexture(textureFile);
	size = material->GetTexture()->GetSize();

	mesh = new Mesh<VertexUV>();
	MakeMesh(startUV, endUV, pos);
	mesh->CreateMesh();
}

Quad::Quad(wstring textureFile, float x, float y, float width, float height)
{
	tag = "Quad";

	material->SetTexture(textureFile);
	size = material->GetTexture()->GetSize();

	Vector2 startUV = Vector2(x, y) / size;
	Vector2 cutSize = Vector2(width, height) / size;
	Vector2 endUV = startUV + cutSize;

	mesh = new Mesh<VertexUV>();
	MakeMesh(startUV, endUV);
	mesh->CreateMesh();
}

Quad::~Quad()
{
	delete mesh;
}

void Quad::Update()
{
	UpdateWorld();
}

void Quad::Render()
{
	if (!IsActive()) return;

	worldBuffer->Set(world);
	worldBuffer->SetVS(0);

	material->Set();
	mesh->Draw();
}

void Quad::SetTexture(wstring textureFile)
{
	material->SetTexture(textureFile);
	size = material->GetTexture()->GetSize();
	MakeMesh();
	mesh->UpdateVertices();
}

void Quad::MakeMesh(Vector2 startUV, Vector2 endUV, Vector2 pos)
{
	float left = pos.x - size.x * 0.5f;
	float right = pos.x + size.x * 0.5f;
	float top = pos.y + size.y * 0.5f;
	float bottom = pos.y - size.y * 0.5f;

	vector<VertexUV>& vertices = mesh->GetVertices();

	vertices.clear();
	vertices.emplace_back(left, top, startUV.x, startUV.y);
	vertices.emplace_back(right, top, endUV.x, startUV.y);
	vertices.emplace_back(left, bottom, startUV.x, endUV.y);
	vertices.emplace_back(right, bottom, endUV.x, endUV.y);

	vector<UINT>& indices = mesh->GetIndices();

	indices = { 0, 1, 2, 2, 1, 3 };
}