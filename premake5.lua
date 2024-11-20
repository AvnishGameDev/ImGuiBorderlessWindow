workspace "ImGuiBorderlessWindow"
   configurations { "Debug", "Release" }

project "ImGuiBorderlessWindow"
   kind "WindowedApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   objdir "bin-int/%{cfg.buildcfg}"
   debugdir "bin/%{cfg.buildcfg}"
   architecture "x64"
   cppdialect "C++20"

   files { "**.h", "**.cpp" }

   includedirs { "ImGuiBorderlessWindow/Gui/ThirdParty/ImGui" }

   removefiles { "ImGuiBorderlessWindow/Gui/ThirdParty/ImGui/misc/**.h" }
   removefiles { "ImGuiBorderlessWindow/Gui/ThirdParty/ImGui/examples/**.h" }
   removefiles { "ImGuiBorderlessWindow/Gui/ThirdParty/ImGui/backends/**.h" }

   removefiles { "ImGuiBorderlessWindow/Gui/ThirdParty/ImGui/misc/**.cpp" }
   removefiles { "ImGuiBorderlessWindow/Gui/ThirdParty/ImGui/examples/**.cpp" }
   removefiles { "ImGuiBorderlessWindow/Gui/ThirdParty/ImGui/backends/**.cpp" }

   links { "d3d9" }

   postbuildcommands {
      "{COPYDIR} ImGuiBorderlessWindow/Assets %{cfg.targetdir}/Assets"
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"