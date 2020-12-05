#pragma once

//////////////////////////////////////////
// For use by application using Neon
//////////////////////////////////////////

// Core
#include "Neon/Core/Application.h"
#include "Neon/Core/Assert.h"
#include "Neon/Core/Base.h"
#include "Neon/Core/Layer.h"
#include "Neon/Core/Logger.h"
#include "Neon/Core/TimeStep.h"
#include "Neon/Input/Input.h"
#include "Neon/Input/KeyCodes.h"
#include "Neon/Input/MouseButtonCodes.h"
#include "Neon/OrthographicCameraController.h"

// ImGui
#include "ImGui/ImGuiLayer.h"

// Events
#include "Neon/Event/ApplicationEvent.h"
#include "Neon/Event/Event.h"
#include "Neon/Event/KeyEvent.h"
#include "Neon/Event/MouseEvent.h"

// Renderer
#include "Neon/Graphics/Buffer.h"
#include "Neon/Graphics/Shader.h"
#include "Neon/Graphics/Texture.h"
#include "Neon/Graphics/VertexArray.h"
#include "Neon/Renderer/OrthographicCamera.h"
#include "Neon/Renderer/RenderCommand.h"
#include "Neon/Renderer/Renderer.h"
