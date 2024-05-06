-- project
set_project("AlphaRom_Crack")
set_xmakever("2.9.1")
set_version("1.0.0")

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
add_requires("microsoft-detours")


-- targets
target("version")
    set_kind("shared")
    add_syslinks("user32")
    add_files("src/dllmain.cpp")
    add_headerfiles("include/(**.h)")
    add_includedirs("include", {public = true})
    add_packages("microsoft-detours")