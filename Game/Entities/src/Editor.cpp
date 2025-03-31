#include "../include/Editor.h"

#include <imgui.h>

#include "Core/Application/include/Application.h"
// #include "Editor/include/ImGuiOpenGL.h"
#include "ImGuiContextProvider/include/ImGuiOpenGL.h"
#include "Utils/Timer.h"

void Editor::OnUpdate()
{
   Begin();
   if(ImGui::Begin("Settings"))
   {
      ImGui::SeparatorText("Forces");
      float separationWeight = m_BoidManager->GetSeparationWeight();
      if(ImGui::SliderFloat("Separation Force", &separationWeight,0, 10.f))
      {
         m_BoidManager->SetSeparationWeight(separationWeight);
      }
      float cohesionWeight = m_BoidManager->GetCohesionWeight();
      if(ImGui::SliderFloat("Cohesion Force", &cohesionWeight,0, 10.f))
      {
         m_BoidManager->SetCohesionWeight(cohesionWeight);
      }
      float alignmentWeight = m_BoidManager->GetAlignmentWeight();
      if(ImGui::SliderFloat("Alignment Force", &alignmentWeight,0, 10.f))
      {
         m_BoidManager->SetAlignmentWeight(alignmentWeight);
      }
      float inertiaWeight = m_BoidManager->GetInertiaWeight();
      if(ImGui::SliderFloat("Inertia Force", &inertiaWeight,0, 10.f))
      {
         m_BoidManager->SetInertiaWeight(inertiaWeight);
      }
      float avoidanceWeight = m_BoidManager->GetAvoidanceWeight();
      if(ImGui::SliderFloat("Avoidance Force", &avoidanceWeight,0, 10.f))
      {
         m_BoidManager->SetAvoidanceWeight(avoidanceWeight);
      }
      float boidSpeed = m_BoidManager->GetBoidSpeed();
      if(ImGui::SliderFloat("Boid Speed", &boidSpeed,0, 50.f))
      {
         m_BoidManager->SetBoidSpeed(boidSpeed);
      }
      
      ImGui::SeparatorText("");
      float maxDistance = m_BoidManager->GetMaxDistance();
      if(ImGui::SliderFloat("Max Distance", &maxDistance,0, 30.f))
      {
         m_BoidManager->SetMaxDistance(maxDistance);
      }
   }
   ImGui::End();
   End();
   HandleCameraMovement();
}
