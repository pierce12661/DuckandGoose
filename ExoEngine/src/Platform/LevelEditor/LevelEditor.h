/*!*************************************************************************
****
\file LevelEditor.h
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 2
\date 28-9-2022
\brief  Header file for LevelEditor.cpp
****************************************************************************
***/
#pragma once
#include "Platform/Window/Window.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
#define p_Editor EM::LevelEditor::GetInstance()

namespace EM {
	class LevelEditor
	{
	public:
		//ctor and dtor
		LevelEditor() = default;
		~LevelEditor() = default;

		//main function for running
		void Init(Window* window);
		void Update();	//update loop
		void Draw();
		void End();

		void SceneViewer();
		void ContentBrowser();
		void Logger();
		void Profiler();
		void Hierarchy();
		void Inspector();
		void Audio();
	public:
		bool show_window = true;
		static std::unique_ptr<LevelEditor>& GetInstance();
		//for inspector and Hierarchy
		bool mDebugDraw{ false }; //to show debug/collision draw 
	private:
		void MainMenuBar();
		void Docking();
		bool FullScreenMode{};
		bool Pad{};

	private:
		
		ImGuiDockNodeFlags dock_space_flags{};
		Window* m_window{nullptr};
		static std::unique_ptr<LevelEditor> m_instance;
		
		//profiler
		bool b_profile = false;
		float m_SceneRuntime = 0.0f;
		float m_UpdateTimer = 0.0f;
		std::array<float, 5> mSystemRunTime = { 0.0f,0.0f,0.0f,0.0f };
		
		//inspector and Hierarchy
		Entity selectedEntity = {};
	
		//Content Browser
		std::filesystem::path mAssetsPath= "Assets";
		std::filesystem::path m_CurrentDirectory = mAssetsPath;
		
		//Scene/guizmo
		Camera2D camera{ -1.0f, 1.0f, -1.0f , 1.0f };
		ImVec2 mViewportSize = { 0.0f, 0.0f };
		ImVec2 mViewportBounds[2];
		int mGizmoType = -1;
		WinData mwindata;
		ImVec4 _gameWindowSpecs;
	};
}