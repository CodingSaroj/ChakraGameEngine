#include "Editor.hpp"
#include "implot/implot.h"

static std::ostringstream m_Log;

std::ostream & GetLogOStream()
{
    return m_Log;
}

Chakra::Application * GetApplication()
{
    return new Chakra::Editor();
}

namespace Chakra
{
    template <typename ComponentType>
    static inline void DrawComponent(std::function<void()> draw, const std::string & name)
    {

    }

    void Application::OnCreate()
    {
    }

    void Application::OnUpdate()
    {
    }

    void Application::OnDestroy()
    {
    }

    void Application::OnResize(int width, int height)
    {
    }

    void Application::OnImGuiRender()
    {
    }

    Editor::Editor()
        : Application(Chakra::WindowAttribs(1280, 720, "Chakra Editor", true))
    {
    }

    void Editor::OnCreate()
    {
        AssetManager::Load<MeshAsset, MeshAssetImportSettings>("Square", "Plane.chkmesh", {true});
        AssetManager::Load<ShaderAsset, ShaderAssetImportSettings>("Shader", "hello", {true, false, false, false, true, false});
        AssetManager::Load<TextureAsset, TextureData>("Texture", "hello.png", TextureData
        {
            TextureFormat::ChannelRGBA,
            TextureFormat::WrapRepeat,
            TextureFormat::WrapRepeat,
            TextureFormat::FilterLinear,
            TextureFormat::FilterLinear
        });

        m_CameraEntity = m_Scene.AddEntity("Main Camera");
        m_CameraEntity.AddComponent<TransformComponent>(glm::identity<glm::mat4>());

        m_CameraEntity.AddComponent<CameraComponent>(true, m_2D ? CameraComponent::CameraType::ORTHOGRAPHIC : CameraComponent::CameraType::PERSPECTIVE);

        class Controller : public Scripting::NativeScript
        {
        public:
            glm::vec2 cursorPos{0.0f, 0.0f};

            void OnUpdate() override
            {
                if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
                {
                    if (cursorPos.x > Input::GetCursorPosX())
                    {
                        GetComponent<TransformComponent>().Translate(-0.1, 0.0, 0.0);
                    }
                    else if (cursorPos.x < Input::GetCursorPosX())
                    {
                        GetComponent<TransformComponent>().Translate(0.1, 0.0, 0.0);
                    }
                    
                    if (cursorPos.y > Input::GetCursorPosY())
                    {
                        GetComponent<TransformComponent>().Translate(0.0, -0.1, 0.0);
                    }
                    else if (cursorPos.y < Input::GetCursorPosY())
                    {
                        GetComponent<TransformComponent>().Translate(0.0, 0.1, 0.0);
                    }
                }

                if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
                {
                    if (Input::IsKeyPressed(GLFW_KEY_A))
                    {
                        GetComponent<TransformComponent>().Translate(0.1, 0.0, 0.0);
                    }
                    else if (Input::IsKeyPressed(GLFW_KEY_D))
                    {
                        GetComponent<TransformComponent>().Translate(-0.1, 0.0, 0.0);
                    }

                    if (Input::IsKeyPressed(GLFW_KEY_W))
                    {
                        GetComponent<TransformComponent>().Translate(0.0, -0.1, 0.0);
                    }
                    else if (Input::IsKeyPressed(GLFW_KEY_S))
                    {
                        GetComponent<TransformComponent>().Translate(0.0, 0.1, 0.0);
                    }
                }

                if (Input::IsKeyPressed(GLFW_KEY_ENTER))
                {
                    GetComponent<CameraComponent>().PerspectiveFOV++;
                }

                if (Input::GetScrollOffsetY() != 0.0)
                {
                    GetComponent<TransformComponent>().Translate(0.0, 0.0, Input::GetScrollOffsetY() / 100.0);
                }
                
                cursorPos.x = Input::GetCursorPosX();
                cursorPos.y = Input::GetCursorPosY();
            }
        };

        m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<Controller>();

        m_SceneFramebuffer.Create(800, 600);
        
        auto & io = ImGui::GetIO();

        io.Fonts->AddFontFromFileTTF("Ubuntu-M.ttf", 15);
    }

    void Editor::OnUpdate()
    {
        m_SceneFramebuffer.Use();

        if (!m_CameraEntity.IsValid())
        {
            for (auto & entity : m_Scene.GetAllEntities())
            {
                if (entity.HasComponent<CameraComponent>())
                {
                    entity.GetComponent<CameraComponent>().MainCamera = true;
                    m_CameraEntity = entity;
                    m_CameraEntity.GetComponent<CameraComponent>().Recalculate(m_SceneW, m_SceneH);
                    break;
                }
            }
        }
    }

    void Editor::OnDestroy()
    {
        m_SceneFramebuffer.Destroy();
    }

    void Editor::OnResize(int width, int height)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, width, height);
    }

    void Editor::OnImGuiRender()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ImGui::DockSpaceOverViewport();

        RenderMenubar();

        if (m_HierarchyOpen)
        {
            RenderHierarchy();
        }

        if (m_PropertyOpen)
        {
            RenderProperties();
        }

        if (m_SceneOpen)
        {
            RenderScene();
        }

        if (m_LogOpen)
        {
            RenderLog();
        }

        if (m_ProfileOpen)
        {
            RenderProfilerWindow();
        }

        RenderEditorState();
    }

    void Editor::RenderMenubar()
    {
        ImGui::BeginMainMenuBar();

        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::BeginMenu("Open..."))
            {
                if (ImGui::Selectable("Scene##Open"))
                {
                    std::ifstream in("hello.chksrlz", std::ios_base::ate);

                    size_t size = in.tellg();
                    std::string data;
                    data.resize(size);

                    in.seekg(0);
                    in.read((char *)data.c_str(), size);

                    in.close();

                    m_Scene.~Scene();

                    Serializer serializer;
                    serializer.DeserializeScene(m_Scene, std::move(data));
                    m_CameraEntity = Entity();
                }

                ImGui::EndMenu();
            }

            if (ImGui::Selectable("Close"))
            {
                Quit();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            ImGui::Checkbox("Scene", &m_SceneOpen);
            ImGui::Checkbox("Hierarchy", &m_HierarchyOpen);
            ImGui::Checkbox("Properties", &m_PropertyOpen);
            ImGui::Checkbox("Log", &m_LogOpen);
            ImGui::Checkbox("Profiler", &m_ProfileOpen);

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    void Editor::RenderScene()
    {
        ImGui::Begin("Scene", &m_SceneOpen);

        if (ImGui::Button(m_2D ? "2D" : "3D"))
        {
            m_2D = !m_2D;

            m_CameraEntity.GetComponent<CameraComponent>().Type = m_2D ? CameraComponent::CameraType::ORTHOGRAPHIC : CameraComponent::CameraType::PERSPECTIVE;
            m_CameraEntity.GetComponent<CameraComponent>().Recalculate(m_SceneW, m_SceneH);
        }

        ImGui::SameLine();

        if (ImGui::Combo("Resolution", &m_CurrentResolution, "800x600\0001280x720\0001920x1080\0"))
        {
            switch (m_CurrentResolution)
            {
                case 0:
                {
                    m_SceneW = 800;
                    m_SceneH = 600;
                    break;
                }

                case 1:
                {
                    m_SceneW = 1280;
                    m_SceneH = 720;
                    break;
                }

                case 2:
                {
                    m_SceneW = 1920;
                    m_SceneH = 1080;
                    break;
                }
            }
            
            m_SceneFramebuffer.Resize(m_SceneW, m_SceneH);

            m_CameraEntity.GetComponent<CameraComponent>().Type = m_2D ? CameraComponent::CameraType::ORTHOGRAPHIC : CameraComponent::CameraType::PERSPECTIVE;
            m_CameraEntity.GetComponent<CameraComponent>().Recalculate(m_SceneW, m_SceneH);
        }

        ImGui::Image((void *)m_SceneFramebuffer.GetColorAttachment(), {(float)m_SceneFramebuffer.GetWidth(), (float)m_SceneFramebuffer.GetHeight()});

        if (ImGui::IsItemHovered())
        {
            auto & io = ImGui::GetIO();

            io.WantCaptureKeyboard = false;
            io.WantCaptureMouse = false;
        }
        else
        {
            auto & io = ImGui::GetIO();

            io.WantCaptureKeyboard = true;
            io.WantCaptureMouse = true;
        }

        ImGui::End();
    }

    void Editor::RenderHierarchy()
    {
        ImGui::Begin("Hierarchy", &m_HierarchyOpen);

        ImGui::OpenPopupOnItemClick("Hierarchy Menu");

        for (auto entity : m_Scene.GetAllEntities())
        {
            if (ImGui::Selectable(entity.GetComponent<TagComponent>().Tag.c_str(), false))
            {
                m_SelectedEntity = entity;
            }

            if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
            {
                m_SelectedEntity = entity;
                ImGui::OpenPopup("Hierarchy Entity Menu");
            }
        }

        if (ImGui::BeginPopup("Hierarchy Menu"))
        {
            if (ImGui::Selectable("New Entity"))
            {
                m_SelectedEntity = m_Scene.AddEntity("NewEntity");
            }

            if (ImGui::Selectable("Serialize"))
            {
                std::ofstream out("hello.chksrlz");
                Serializer serializer;
                out<<serializer.Serialize(m_Scene);
                out.close();
            }

            if (ImGui::Selectable("Deserialize"))
            {
                std::ifstream in("hello.chksrlz", std::ios_base::ate);
                Serializer serializer;
                size_t size = in.tellg();
                std::string data;
                data.resize(size);
                in.seekg(0);
                in.read((char *)data.c_str(), size);
                in.close();
                m_Scene.~Scene();
                serializer.DeserializeScene(m_Scene, std::move(data));
                m_CameraEntity = Entity();
            }


            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("Hierarchy Entity Menu"))
        {
            if (ImGui::Selectable("Duplicate") && m_SelectedEntity.IsValid())
            {
                m_Scene.AddEntity(m_SelectedEntity.GetComponent<TagComponent>().Tag + "1");
            }

            if (ImGui::Selectable("Remove") && m_SelectedEntity.IsValid())
            {
                m_Scene.RemoveEntity(m_SelectedEntity);
            }

            ImGui::EndPopup();
        }

        ImGui::End();
    }

    void Editor::RenderProperties()
    {
        ImGui::Begin("Properties", &m_PropertyOpen);

        if (m_SelectedEntity.IsValid())
        {
            auto & tag = m_SelectedEntity.GetComponent<TagComponent>();

            char buffer[256];

            strcpy((char *)buffer, (char *)tag.Tag.c_str());

            ImGui::AlignTextToFramePadding();
            ImGui::Text("Name");
            ImGui::AlignTextToFramePadding();
            ImGui::SameLine();
            if (ImGui::InputText("##Name", buffer, 256))
            {
                tag.Tag = std::move(std::string(buffer));
            }

            if (m_SelectedEntity.HasComponent<TransformComponent>())
            {
                auto & transform = m_SelectedEntity.GetComponent<TransformComponent>();

                if (ImGui::TreeNode("Transform"))
                {
                    glm::vec3 previousRotation(glm::degrees(glm::eulerAngles(transform.Rotation)));
                    glm::vec3 rotation(previousRotation);
                    glm::vec3 scale(transform.Transform[0][0], transform.Transform[1][1], transform.Transform[2][2]);

                    ImGui::Columns(2);

                    ImGui::AlignTextToFramePadding();
                    ImGui::Text("Position");
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text("Rotation");
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text("Scale");
                    ImGui::AlignTextToFramePadding();

                    ImGui::NextColumn();

                    ImGui::DragFloat3("##Position", glm::value_ptr(transform.Transform[3]));
                    
                    if (ImGui::DragFloat3("##Rotation", glm::value_ptr(rotation)))
                    {
                        glm::vec3 rotationDifference = rotation - previousRotation;
                        transform.Rotate(rotationDifference);
                    }
                    
                    if (ImGui::DragFloat3("##Scale", glm::value_ptr(scale)))
                    {
                        transform.Transform[0][0] = scale.x;
                        transform.Transform[1][1] = scale.y;
                        transform.Transform[2][2] = scale.z;
                    }

                    ImGui::Columns(1);

                    if (ImGui::Button("Remove"))
                    {
                        m_SelectedEntity.RemoveComponent<TransformComponent>();
                    }

                    ImGui::TreePop();
                }
            }

            if (m_SelectedEntity.HasComponent<MaterialComponent>())
            {
                auto & material = m_SelectedEntity.GetComponent<MaterialComponent>();

                if (ImGui::TreeNode("Material"))
                {
                    ImGui::Columns(2, "0");

                    ImGui::AlignTextToFramePadding();
                    ImGui::Text("Mesh");
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text("Shader");
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text("Uniform Block Name");
                    ImGui::AlignTextToFramePadding();

                    ImGui::NextColumn();

                    char buffer[256];

                    strcpy((char *)buffer, (char *)material.Mesh.Key.c_str());

                    if (ImGui::InputText("##Mesh", buffer, 256))
                    {
                        material.Mesh.Key = std::move(std::string(buffer));
                    }

                    strcpy((char *)buffer, (char *)material.Shader.Key.c_str());

                    if (ImGui::InputText("##Shader", buffer, 256))
                    {
                        material.Shader.Key = std::move(std::string(buffer));
                    }

                    strcpy((char *)buffer, (char *)material.UniformName.c_str());

                    if (ImGui::InputText("##Uniform Block Name", buffer, 256))
                    {
                        material.UniformName = std::move(std::string(buffer));
                    }

                    ImGui::Columns(1);

                    ImGui::NewLine();

                    ImGui::Columns(2, "1");

                    ImGui::NextColumn();

                    size_t textureIndex = 0;

                    for (auto & uniformFormat : AssetManager::Get<ShaderAsset>(material.Shader.Key)->GetShader().GetUniformFormats())
                    {
                        if (uniformFormat.Type.basetype == spirv_cross::SPIRType::BaseType::SampledImage)
                        {
                            if (material.Textures.size() <= textureIndex)
                            {
                                material.Textures.resize(textureIndex + 1);
                            }

                            ImGui::NextColumn();
                    
                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(uniformFormat.Name.c_str() + 2);
                            ImGui::AlignTextToFramePadding();

                            ImGui::NextColumn();

                            strcpy((char *)buffer, (char *)material.Textures[textureIndex].Key.c_str());

                            if (ImGui::InputText(("##" + uniformFormat.Name).c_str(), buffer, 256))
                            {
                                material.Textures[textureIndex].Key = std::move(std::string(buffer));
                            }

                            textureIndex++;
                        }
                        else if (uniformFormat.Name == material.UniformName)
                        {
                            size_t offset = 0;

                            if (material.UniformData.size() != uniformFormat.Size)
                            {
                                material.UniformData.resize(uniformFormat.Size);
                            }

                            for (auto & member : uniformFormat.Members)
                            {
                                if (member.Type.basetype == spirv_cross::SPIRType::BaseType::Float && member.Type.columns == 0)
                                {
                                    ImGui::NextColumn();

                                    ImGui::AlignTextToFramePadding();
                                    ImGui::TextUnformatted(member.Name.c_str() + 2);
                                    ImGui::AlignTextToFramePadding();

                                    ImGui::NextColumn();

                                    ImGui::DragFloat(("##" + member.Name).c_str(), (float *)(material.UniformData.data() + offset), 0.01f);
                                }
                                else if (member.Type.columns == 1)
                                {
                                    if (member.Type.vecsize == 2)
                                    {
                                        ImGui::NextColumn();

                                        ImGui::AlignTextToFramePadding();
                                        ImGui::TextUnformatted(member.Name.c_str() + 2);
                                        ImGui::AlignTextToFramePadding();

                                        ImGui::NextColumn();

                                        ImGui::DragFloat2(("##" + member.Name).c_str(), (float *)(material.UniformData.data() + offset), 0.01f);
                                    }
                                    else if (member.Type.vecsize == 3)
                                    {
                                        ImGui::NextColumn();

                                        ImGui::AlignTextToFramePadding();
                                        ImGui::TextUnformatted(member.Name.c_str() + 2);
                                        ImGui::AlignTextToFramePadding();

                                        ImGui::NextColumn();

                                        ImGui::DragFloat3(("##" + member.Name).c_str(), (float *)(material.UniformData.data() + offset), 0.01f);
                                        ImGui::ColorEdit3(("##" + member.Name).c_str(), (float *)(material.UniformData.data() + offset));
                                    }
                                    else if (member.Type.vecsize == 4)
                                    {
                                        ImGui::NextColumn();

                                        ImGui::AlignTextToFramePadding();
                                        ImGui::TextUnformatted(member.Name.c_str() + 2);
                                        ImGui::AlignTextToFramePadding();

                                        ImGui::NextColumn();

                                        ImGui::DragFloat4(("##" + member.Name).c_str(), (float *)(material.UniformData.data() + offset), 0.01f);
                                        ImGui::ColorEdit4(("##" + member.Name).c_str(), (float *)(material.UniformData.data() + offset));
                                    }
                                }

                                ImGui::NewLine();
                                
                                offset += member.Size;
                            }
                        }
                    }

                    ImGui::Columns(1);

                    if (ImGui::Button("Remove"))
                    {
                        m_SelectedEntity.RemoveComponent<MaterialComponent>();
                    }

                    ImGui::TreePop();
                }
            }

            if (m_SelectedEntity.HasComponent<CameraComponent>())
            {
                auto & camera = m_SelectedEntity.GetComponent<CameraComponent>();

                if (ImGui::TreeNode("Camera"))
                {
                    ImGui::Checkbox("Main Camera", &camera.MainCamera);

                    ImGui::Columns(2);

                    ImGui::AlignTextToFramePadding();
                    ImGui::Text("Projection Type");
                    ImGui::AlignTextToFramePadding();

                    ImGui::NextColumn();

                    if (ImGui::BeginCombo("##Projection Type", camera.Type == CameraComponent::CameraType::PERSPECTIVE ? "Perspective" : "Orthographic"))
                    {
                        if (ImGui::Selectable("Perspective", camera.Type == CameraComponent::CameraType::PERSPECTIVE))
                        {
                            camera.Type = CameraComponent::CameraType::PERSPECTIVE;
                            camera.Recalculate(m_SceneW, m_SceneH);
                        }

                        if (ImGui::Selectable("Orthographic", camera.Type == CameraComponent::CameraType::ORTHOGRAPHIC))
                        {
                            camera.Type = CameraComponent::CameraType::ORTHOGRAPHIC;
                            camera.Recalculate(m_SceneW, m_SceneH);
                        }

                        ImGui::EndCombo();
                    }

                    ImGui::NextColumn();

                    if (camera.Type == CameraComponent::CameraType::PERSPECTIVE)
                    {
                        ImGui::AlignTextToFramePadding();
                        ImGui::Text("Field of View (FOV)");
                        ImGui::AlignTextToFramePadding();
                        ImGui::Text("Near plane");
                        ImGui::AlignTextToFramePadding();
                        ImGui::Text("Far plane");
                        ImGui::AlignTextToFramePadding();

                        ImGui::NextColumn();

                        if (ImGui::DragFloat("##Field Of View (FOV)", &camera.PerspectiveFOV)) { camera.Recalculate(m_SceneW, m_SceneH); }
                        if (ImGui::DragFloat("##Near plane", &camera.PerspectiveNear)) { camera.Recalculate(m_SceneW, m_SceneH); }
                        if (ImGui::DragFloat("##Far plane", &camera.PerspectiveFar)) { camera.Recalculate(m_SceneW, m_SceneH); }
                    }
                    else
                    {
                        ImGui::AlignTextToFramePadding();
                        ImGui::Text("Scale");
                        ImGui::AlignTextToFramePadding();
                        ImGui::Text("Near plane");
                        ImGui::AlignTextToFramePadding();
                        ImGui::Text("Far plane");
                        ImGui::AlignTextToFramePadding();

                        ImGui::NextColumn();

                        if (ImGui::DragFloat("##Scale", &camera.OrthographicScale)) { camera.Recalculate(m_SceneW, m_SceneH); }
                        if (ImGui::DragFloat("##Near plane", &camera.OrthographicNear)) { camera.Recalculate(m_SceneW, m_SceneH); }
                        if (ImGui::DragFloat("##Far plane", &camera.OrthographicFar)) { camera.Recalculate(m_SceneW, m_SceneH); }
                    }

                    ImGui::Columns(1);

                    if (ImGui::Button("Remove"))
                    {
                        m_SelectedEntity.RemoveComponent<CameraComponent>();
                    }

                    ImGui::TreePop();
                }
            }

            if (ImGui::Button("AddComponent"))
            {
                ImGui::OpenPopup("ComponentSelector");
            }

            if (ImGui::BeginPopup("ComponentSelector"))
            {
                ImGuiTextFilter filter;

                filter.Draw("Filter");

                if (filter.PassFilter("TransformComponent"))
                {
                    if (ImGui::Selectable("TransformComponent"))
                    {
                        m_SelectedEntity.AddComponent<TransformComponent>(glm::identity<glm::mat4>());
                    }
                }
                
                if (filter.PassFilter("MaterialComponent"))
                {
                    if (ImGui::Selectable("MaterialComponent"))
                    {
                        m_SelectedEntity.AddComponent<MaterialComponent>(AssetReference{"Square"}, AssetReference{"Shader"}, "u_MaterialData", std::vector<uint8_t>(16));
                    }
                }

                if (filter.PassFilter("CameraComponent"))
                {
                    if (ImGui::Selectable("CameraComponent"))
                    {
                        m_SelectedEntity.AddComponent<CameraComponent>();
                    }
                }
                
                ImGui::EndPopup();
            }
        }

        ImGui::End();
    }

    void Editor::RenderLog()
    {
        ImGui::Begin("Log", &m_LogOpen);

        if (ImGui::Button(m_LogCollapse ? "Expand" : "Collapse"))
        {
            if (m_LogCollapse)
            {
                m_LogCollapse = false;
            }
            else
            {
                m_LogCollapse = true;
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Clear"))
        {
            size_t size = m_Log.tellp();
            m_Log.seekp(0);

            std::vector<char> spaces(size);

            std::fill(spaces.begin(), spaces.end(), ' ');

            m_Log.write(spaces.data(), size);

            m_Log.seekp(0);
        }

        std::string log = m_Log.str();

        std::vector<std::string> logs;

        std::string currentStr;

        for (auto c : log)
        {
            if (c == '\n')
            {
                logs.emplace_back(currentStr);
                currentStr.clear();
            }
            else
            {
                currentStr += c;
            }
        }

        if (m_LogCollapse)
        {
            std::unordered_map<std::string, uint32_t> collapsedLogs;

            for (auto & log : logs)
            {
                collapsedLogs[log]++;
            }

            logs.resize(collapsedLogs.size());

            std::transform(collapsedLogs.begin(), collapsedLogs.end(), logs.begin(), [](auto & collapsedLog)->std::string
            {
                return std::move("(" + std::to_string(collapsedLog.second) + ")" + collapsedLog.first);
            });
        }

        if (ImGui::BeginChild("LogData"))
        {
            for (auto & log : logs)
            {
                if (log[0] == '(')
                {
                    if (log.find_first_of('E') != std::string::npos && std::string(log.data() + log.find_first_of('E'), 5) == "Error")
                    {
                        ImGui::TextColored({1.0f, 0.0f, 0.0f, 1.0f}, log.c_str());
                    }
                    else if (log.find_first_of('W') != std::string::npos && std::string(log.data() + log.find_first_of('W'), 7) == "Warning")
                    {
                        ImGui::TextColored({1.0f, 1.0f, 0.0f, 1.0f}, log.c_str());
                    }
                    else if (log.find_first_of('I') != std::string::npos && std::string(log.data() + log.find_first_of('I'), 4) == "Info")
                    {
                        ImGui::TextColored({0.0f, 1.0f, 1.0f, 1.0f}, log.c_str());
                    }
                    else
                    {
                        ImGui::TextUnformatted(log.c_str());
                    }
                }
                else
                {
                    if (std::string(log.data(), 5) == "Error")
                    {
                        ImGui::TextColored({1.0f, 0.0f, 0.0f, 1.0f}, log.c_str());
                    }
                    else if (std::string(log.data(), 7) == "Warning")
                    {
                        ImGui::TextColored({1.0f, 1.0f, 0.0f, 1.0f}, log.c_str());
                    }
                    else if (std::string(log.data(), 4) == "Info")
                    {
                        ImGui::TextColored({0.0f, 1.0f, 1.0f, 1.0f}, log.c_str());
                    }
                    else
                    {
                        ImGui::TextUnformatted(log.c_str());
                    }
                }
            }
        }

        ImGui::EndChild();

        ImGui::End();
    }

    void Editor::RenderProfilerWindow()
    {
        static std::array<float, 250> data;
        static std::array<float, 250> fpsdata;
        static std::array<float, 250> memdata;
        static size_t cursor = 0;
        static size_t fpscursor = 0;
        static size_t memcursor = 0;
        
        ImGui::Begin("ProfileWindow", &m_ProfileOpen);

        if (cursor >= 250)
        {
            for (auto iter = data.begin() + 1; iter != data.end(); ++iter)
            {
                *(iter - 1) = *iter;
            }

            cursor = 249;
        }
        else
        {
            cursor++;
        }

        data[cursor] = s_ProfilerStats.FrameTime;

        if (fpscursor >= 250)
        {
            for (auto iter = fpsdata.begin() + 1; iter != fpsdata.end(); ++iter)
            {
                *(iter - 1) = *iter;
            }

            fpscursor = 249;
        }
        else
        {
            fpscursor++;
        }

        fpsdata[fpscursor] = s_ProfilerStats.FPS;

        if (memcursor >= 250)
        {
            for (auto iter = memdata.begin() + 1; iter != memdata.end(); ++iter)
            {
                *(iter - 1) = *iter;
            }

            memcursor = 249;
        }
        else
        {
            memcursor++;
        }
        memdata[memcursor] = s_ProfilerStats.MemoryUsage;

        ImPlot::SetNextPlotLimits(0.0, 250.0, 0.0, 50.0);

        if (ImPlot::BeginPlot("Framtime", nullptr, nullptr, ImVec2(0, 0), ImPlotFlags_NoMousePos | ImPlotFlags_NoLegend))
        {
            ImPlot::PlotLineG("Frametime", [](void * data, int index)->ImPlotPoint
            {
                double current = ((float *)data)[index];

                return {(double)index, current};
            }, data.data(), data.size());
            ImPlot::EndPlot();
        }

        ImPlot::SetNextPlotLimits(0.0, 250.0, 0.0, 100.0);

        if (ImPlot::BeginPlot("FPS", nullptr, nullptr, ImVec2(0, 0), ImPlotFlags_NoMousePos | ImPlotFlags_NoLegend))
        {
            ImPlot::PlotLineG("FPS", [](void * data, int index)->ImPlotPoint
            {
                double current = ((float *)data)[index];

                return {(double)index, current};
            }, fpsdata.data(), fpsdata.size());
            ImPlot::EndPlot();
        }

        ImPlot::SetNextPlotLimits(0.0, 250.0, 0.0, 20.0);

        if (ImPlot::BeginPlot("MemoryUsage (MB)", nullptr, nullptr, ImVec2(0, 0), ImPlotFlags_NoMousePos | ImPlotFlags_NoLegend))
        {
            ImPlot::PlotLineG("MemoryUsage", [](void * data, int index)->ImPlotPoint
            {
                double current = ((float *)data)[index] / (1024.0 * 1024.0);

                return {(double)index, current};
            }, memdata.data(), memdata.size());
            ImPlot::EndPlot();
        }

        ImGui::End();
    }

    void Editor::RenderEditorState()
    {
        ImGui::Begin("EditorState");

        ImGui::Text("Mode: %s", m_2D ? "2D" : "3D");
        ImGui::Text("Log Mode: %s", m_LogCollapse ? "Collapse" : "Expand");
        ImGui::Text("Width: %lu", m_SceneW);
        ImGui::Text("Height: %lu", m_SceneH);
        ImGui::Text("Selected Entity: %s", m_SelectedEntity.IsValid() ? m_SelectedEntity.GetComponent<TagComponent>().Tag.c_str() : "null");

        ImGui::End();
    }
}
