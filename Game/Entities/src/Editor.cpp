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
      
      // ImGui::SeparatorText("Centroid direction");
      // ImGui::Text("X: %f", m_BoidManager->GetCentroidDirection().x);                    
      // ImGui::SameLine();
      // float dirx = m_BoidManager->GetCentroidDirection().x;
      // if(ImGui::SliderFloat("position x", &dirx,1., -1.f))
      // {
      //    m_BoidManager->SetCentroidDirection(glm::vec3(dirx, m_BoidManager->GetCentroidDirection().y, m_BoidManager->GetCentroidDirection().z));
      // }
      // ImGui::Text("Y: %f", m_BoidManager->GetCentroidDirection().y);
      // ImGui::SameLine();
      // float diry = m_BoidManager->GetCentroidDirection().y;
      // if(ImGui::SliderFloat("position y", &diry,1., -1.f))
      // {
      //    m_BoidManager->SetCentroidDirection(glm::vec3(m_BoidManager->GetCentroidDirection().x, diry, m_BoidManager->GetCentroidDirection().z));
      // }
      //
      // ImGui::Text("Z: %f", m_BoidManager->GetCentroidDirection().z);
      // ImGui::SameLine();
      // float dirz = m_BoidManager->GetCentroidDirection().z;
      // if(ImGui::SliderFloat("position z", &dirz,1., -1.f))
      // {
      //    m_BoidManager->SetCentroidDirection(glm::vec3(m_BoidManager->GetCentroidDirection().x, m_BoidManager->GetCentroidDirection().y, dirz));
      // }
      //
      // ImGui::SeparatorText("");
      // float centroidSpeed = m_BoidManager->GetCentroidSpeed();
      // if(ImGui::SliderFloat("Centroid Speed", &centroidSpeed,0, 30.f))
      // {
      //    m_BoidManager->SetCentroidSpeed(centroidSpeed);
      // }
      //
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
