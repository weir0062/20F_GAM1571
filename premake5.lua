workspace "Game"
    configurations { "Debug", "Release" }
    location "build"

    platforms { "x64" }

project "Game"
    kind "WindowedApp"

    files {
     "Game/Source/**.cpp",
     "GenerateProjectFiles.bat",
     "premake5.lua",
     ".gitignore"
	}