
# Rotating 3D Donut (x, y, z)

A colorful, rotating 3D donut rendered using modern OpenGL.
The donut rotates around the x, y, and z axes and dynamically changes color during rotation.

Built using:

* **GLFW** – Window/context management
* **GLAD** – OpenGL function loader (4.5 Core Profile)
* **GLM** – Matrix and vector math (for transformations)

---

## 📦 Requirements

Before building and running the project, ensure the following are installed and properly set up:

* [CMake](https://cmake.org/download/)
* `g++` (C++17 compatible compiler)
* **GLFW**
* **GLAD** (4.5 Core Profile)
* **GLM**

> ⚠️ Ensure these libraries are already compiled and available on your system.
> 📁 Update the paths to these dependencies in `CMakeLists.txt` as per the comments inside the file.

---

## 🚀 How to Run

### First Time Setup

Run the PowerShell script:

```powershell
./compile.ps1
```

This will:

* Configure the project using CMake
* Build the binary
* Launch the program

### Making Further Changes

If the `build/` folder already exists and you’re only modifying your source code (without adding new dependencies):

```powershell
./semicompile.ps1
```

This will:

* Recompile the modified files
* Re-run the program
* Skip full CMake reconfiguration

---

Let me know if you'd like to add a screenshot or GIF of the donut in action, or include license and contribution sections.
