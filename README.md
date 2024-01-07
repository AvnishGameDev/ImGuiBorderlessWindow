# ImGuiBorderlessWindow
 ImGui Borderless Window made by AvnishGameDev. Uses DirectX, Windows API and ImGui. This project currently only supports Windows.
 
 # Steps to setup
 1. Clone the project with the following command
    ```git clone https://github.com/AvnishGameDev/ImGuiBorderlessWindow.git```
 2. In the cloned folder, Run GenerateNewProject.bat

      ![image](https://github.com/AvnishGameDev/ImGuiBorderlessWindow/assets/64523755/6f02c32c-2606-4778-8a4c-950893d2763a)
 3. Enter your project name (Don't leave any spaces in the name)

      ![image](https://github.com/AvnishGameDev/ImGuiBorderlessWindow/assets/64523755/bc1b532a-7c4f-42bf-bb38-a1b580e8c396)
 4. You should see this output, if not, make sure you have Python and shutil module installed.
    
      ![image](https://github.com/AvnishGameDev/ImGuiBorderlessWindow/assets/64523755/fb346fde-ec15-4a33-a5f6-b6e6ad15c06c)
 5. You will find YourProject.sln in the newly generated project folder as displayed in above output.

# Troubleshooting
 1. If the project fails to compile, make sure to set C++ standard to C++17 or above in the project properties as shown below.

    ![image](https://github.com/AvnishGameDev/ImGuiBorderlessWindow/assets/64523755/43d4c693-56de-4bf9-bf5d-4764b0787824)
 2. Make sure Subsystem is set to Windows by going to Project Properties -> Linker -> System

    ![image](https://github.com/AvnishGameDev/ImGuiBorderlessWindow/assets/64523755/0e873ff9-11b5-4f8f-b0b6-645ed05ac385)

# How to use Themes
Themes are available in Themes.h, in order to activate a theme, just include Themes.h and call Theme::AnyThemeOfYourChoice() to activate that theme.

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

## 8. Comfy
![image](https://user-images.githubusercontent.com/64523755/221153867-0232b47a-d7ad-4b27-9077-cdbff83e5d4a.png)
