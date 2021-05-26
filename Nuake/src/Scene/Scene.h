#pragma once
#include "../Rendering/Camera.h"
#include "Lighting/Environment.h"
#include <vector>
#include "entt/entt.hpp"
#include "../Rendering/SkyboxHDR.h"
#include "../Rendering/GBuffer.h"
#include "../Rendering/ProceduralSky.h"
#include "../Core/Core.h"
#include "EditorCamera.h"
#include "../Resource/Serializable.h"
#include "src/UI/UserInterface.h"

class Entity;
class Scene : public ISerializable
{
	friend Entity;

private:
	std::string Name;
	bool has_changed = true;

	std::vector<Ref<UI::UserInterface>> m_Interfaces;
	entt::registry m_Registry;
	Ref<Environment> m_Environement;
	Ref<EditorCamera> m_EditorCamera;

public:
	std::string Path = "";
	static Ref<Scene> New();

	Scene();
	~Scene();

	std::string GetName();
	bool SetName(std::string& newName);

	void Init();
	void OnInit();
	void OnExit();
	void Update(Timestep ts);
	void EditorUpdate(Timestep ts);

	// TODO: Maybe move this to Renderer::DrawScene() ?
	void DrawShadows();
	void Draw();
	void EditorDraw();

	std::vector<Entity> GetAllEntities();
	Entity GetEntity(const std::string& name);

	// TODO: This shouldnt be allowed
	Entity CreateEmptyEntity();
	Entity CreateEntity(const std::string& name);

	// TODO: Could be moved to transform component directly.
	glm::vec3 GetGlobalPosition(Entity ent);
	void DestroyEntity(Entity entity); // TODO: Could return bool

	// TODO: Add multiple camera support.
	Ref<Camera> GetCurrentCamera();
	Ref<Environment> GetEnvironment();

	bool Save();
	bool SaveAs(const std::string& path);

	void AddInterface(Ref<UI::UserInterface> interface);

	json Serialize() override;
	bool Deserialize(const std::string& str) override;
};