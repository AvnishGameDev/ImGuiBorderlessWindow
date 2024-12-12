workspace "ImGuiBorderlessWindow"
   configurations { "Debug", "Release" }
   architecture "x64"
   cppdialect "C++20"

project "ImGuiBorderlessWindow"
   kind "WindowedApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   objdir "bin-int/%{cfg.buildcfg}"
   debugdir "bin/%{cfg.buildcfg}"

   files { "**.h", "**.cpp" }

   includedirs { "ImGuiBorderlessWindow/Gui/ThirdParty/ImGui" }

   removefiles {
      "ImGuiBorderlessWindow/Gui/ThirdParty/ImGui/misc/**",
      "ImGuiBorderlessWindow/Gui/ThirdParty/ImGui/examples/**",
      "ImGuiBorderlessWindow/Gui/ThirdParty/ImGui/backends/**",
      "ImGuiBorderlessWindow/Gui/Platform/**/**" -- Exclude everything in any sub-folder of Platform, keep Platform.h and Platform.cpp
   }

   postbuildcommands {
      "{COPYDIR} ImGuiBorderlessWindow/Assets %{cfg.targetdir}/Assets"
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      
   filter "system:windows"
      defines { "PLATFORM_WINDOWS "}
      links { "d3d9" }
      files { "ImGuiBorderlessWindow/Gui/Platform/Windows/**" }

   filter "system:macosx"
      defines { "PLATFORM_MAC "}
      -- links { "" }
      files { "ImGuiBorderlessWindow/Gui/Platform/Mac/**" }

   