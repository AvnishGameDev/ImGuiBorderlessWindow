# ImGuiBorderlessWindow
ImGui Borderless Window made by AvnishGameDev. Works on Windows, MacOS, and Linux.
Based on [Dear ImGui](https://github.com/ocornut/imgui).

ImGuiBorderlessWindow provides a easy ready-to-use template for a Borderless Windowed App, packed with multiple Themes, Fonts and easy Asset loading.

This is a perfect template for Apps like Mod Menus, Helper tools, Utility application etc.

[Documentation](https://docs.avnishgamedev.com/documentation/imguiborderlesswindow/)
 
# Steps to setup
1. Clone the repo using the following command or [download it as a zip](https://github.com/AvnishGameDev/ImGuiBorderlessWindow/archive/refs/heads/main.zip).\
```git clone https://github.com/AvnishGameDev/ImGuiBorderlessWindow```

2. Run the appropriate script for your platform:
   - Windows: Run `GenerateNewProject.bat`
   - MacOS: Run `GenerateNewProject.sh` (You'll need to run ```chmod +x GenerateNewProject.sh``` first)
   - Linux: Run `GenerateNewProject.sh` (You'll need to run ```chmod +x GenerateNewProject.sh``` first)

3. The Script should walk you through all the steps, you might be prompted to install missing Python packages, just type `y` whenever prompted.

4. For Linux users, you'll also need to install some additional dependencies:
   ```bash
   sudo apt-get update
   sudo apt-get install libx11-dev libxext-dev libgl1-mesa-dev libglu1-mesa-dev libglfw3-dev
   ```

5. Enter your Project Name (No spaces).

6. Your project should be generated and the script will tell you the location.

7. You will find the project's solution files in the solution folder.

# How to use Themes
Themes are available in Themes.h, in order to activate a theme, just include ```Themes.h``` and call ```Theme::AnyThemeOfYourChoice()``` to activate that theme.

# Available Themes
## 1. Default Dark
![image](https://user-images.githubusercontent.com/64523755/221153006-6c23f76f-3a4e-4df6-a091-2571da27e092.png)

## 2. Default Light
![image](https://user-images.githubusercontent.com/64523755/221153099-372f5f72-32a3-4a6c-b039-aef94f0d840d.png)

## 3. Embrace The Darkness
![image](https://user-images.githubusercontent.com/64523755/221153253-66d72b88-8c0e-4d1b-b535-ba5b52559186.png)

## 4. Game Dark
![image](https://user-images.githubusercontent.com/64523755/221153389-35e8e203-e41c-44e6-ae15-9b90eff38761.png)

## 5. Red Tint
![image](https://user-images.githubusercontent.com/64523755/221153503-9fcf2073-9ef8-4a1f-97a9-ea4d432a3b32.png)

## 6. The Great Dark
![image](https://user-images.githubusercontent.com/64523755/221153635-5dda5612-582e-4ad4-bc2b-134899aa36cb.png)

## 7. Material Flat
![image](https://user-images.githubusercontent.com/64523755/221153739-540cf5b5-afb4-4fc5-9543-58960541bf65.png)

## 8. Comfy (Default)
![image](https://user-images.githubusercontent.com/64523755/221153867-0232b47a-d7ad-4b27-9077-cdbff83e5d4a.png)
