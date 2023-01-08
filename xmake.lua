add_rules("mode.debug", "mode.release")

set_languages("cxx20")

if is_mode("release") then
    set_optimize("fastest")
end

set_warnings("allextra")

add_requires("libsdl", { configs = { shared = true }})
add_requires("libsdl_image")
add_requires("libsdl_mixer")
add_requires("libsdl_ttf")

rule("cp-dll")
    after_build(
        function(target)
            local sdl_dir = target:pkg("libsdl"):installdir()
            os.cp(path.join(sdl_dir, "bin", "SDL2.dll"), path.join(target:scriptdir(), "build", "$(plat)", "$(arch)", "$(mode)"))

            local sdl_image_dir = target:pkg("libsdl_image"):installdir()
            os.cp(path.join(sdl_image_dir, "bin", "SDL2_image.dll"), path.join(target:scriptdir(), "build", "$(plat)", "$(arch)", "$(mode)"))
            
            local sdl_mixer_dir = target:pkg("libsdl_mixer"):installdir()
            os.cp(path.join(sdl_mixer_dir, "bin", "SDL2_mixer.dll"), path.join(target:scriptdir(), "build", "$(plat)", "$(arch)", "$(mode)"))
            
            local sdl_ttf_dir = target:pkg("libsdl_ttf"):installdir()
            os.cp(path.join(sdl_ttf_dir, "bin", "SDL2_ttf.dll"), path.join(target:scriptdir(), "build", "$(plat)", "$(arch)", "$(mode)"))
        end
    )

target("boilerplate-sdl-game")
    set_kind("binary")
    add_rules("cp-dll")
    add_files("src/*.cpp")
    add_packages("libsdl", "libsdl_image", "libsdl_mixer", "libsdl_ttf")