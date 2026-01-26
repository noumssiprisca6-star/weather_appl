# build.py
import os
import subprocess
import sys

def build_project():
    # -----------------------------
    # Liste des fichiers à compiler
    # Remplace ces chemins par les fichiers que tu veux compiler
    # -----------------------------
    sources = [
        "src/main.cpp",
        "src/meteo.cpp",
        "src/style.cpp",
        "src/renderer.cpp",
        "libs/imgui/imgui.cpp",
        "libs/imgui/imgui_draw.cpp",
        "libs/imgui/imgui_demo.cpp",
        "libs/imgui/imgui_tables.cpp",
        "libs/imgui/imgui_widgets.cpp",
        "libs/imgui/backends/imgui_impl_sdl3.cpp",
        "libs/imgui/backends/imgui_impl_sdlrenderer3.cpp"
    ]

    # -----------------------------
    # Includes
    # -----------------------------
    include_dirs = [
        "-I./libs/imgui",
        "-I./libs/imgui/backends",
        "-I./src/SDL3/SDL_image",
        "-I./include",
        "-I./src/SDL3",
        "-I./libs/stb"
    ]

    # -----------------------------
    # Librairies selon OS
    # -----------------------------
    libraries = []
    if sys.platform == "win32":
        libraries = ["-lSDL3", "-lSDL3_image" ]
    elif sys.platform == "darwin":
        libraries = ["-lSDL3", "-lSDL3_image"]
    else:
        libraries = ["-lSDL3", "-ldl", "-lpthread"]

    # -----------------------------
    # Commande de compilation
    # -----------------------------
    cmd = [
        "clang++",
        *include_dirs,
        *sources,
        *libraries,
        "-o",
        "build/test.exe"   # Nom de l'exécutable final
    ]

    # -----------------------------
    # Affichage de la commande pour debug
    # -----------------------------
    print("Commande générée :")
    print(" ".join(cmd))

    # -----------------------------
    # Exécution de la compilation
    # -----------------------------
    subprocess.run(cmd)

if __name__ == "__main__":
    build_project()