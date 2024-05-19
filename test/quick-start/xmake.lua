-- languages
set_warnings("all")
set_languages("c++20")
set_encodings("source:utf-8")

-- allows
set_allowedarchs("x86")
set_allowedarchs("windows|x86")
set_allowedplats("windows", "mingw")
set_allowedmodes("debug", "release")

-- rules
add_rules("plugin.vsxmake.autoupdate")
add_rules("mode.debug", "mode.release")

-- lto
if is_mode("release") then
    set_warnings("all")
    set_policy("build.optimization.lto", true)
end

-- runtime
if is_plat("windows") then
    set_runtimes(is_mode("debug") and "MD" or "MT")
end

-- requires
add_repositories("Drepo https://github.com/Dir-A/Drepo.git")
add_requires("alpharom_crack")


-- targets
target("version")
    set_kind("shared")
    add_files("src/dllmain.cpp")
    add_packages("alpharom_crack")