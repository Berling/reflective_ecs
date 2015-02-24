solution "reflective_ecs"
    configurations {"debug", "release"}
    language "C++"

    includedirs "include"

    configuration "debug"
        flags "Symbols"
        optimize "Off"

    configuration "release"
        optimize "Full"

    project "reflective_ecs"
        kind "ConsoleApp"

        defines "GLM_FORCE_RADIANS"

        buildoptions "-std=c++1y"

        files "src/**.cpp"

        configuration {"gmake", "linux"}
            if _OPTIONS["cc"] == "clang" then
                toolset "clang"
                buildoptions "-stdlib=libc++"
                links "c++"
            end