import os
import shutil

print("Written by AvnishGameDev for ImGuiBorderlessWindow. https://github.com/avnishgamedev/ImGuiBorderlessWindow")

projName = input("Enter project name: ")
print("Generating project")

os.mkdir(f"../{projName}")

shutil.copytree("ImGuiBorderlessWindow/ImGui", f"../{projName}/ImGuiBorderlessWindow/ImGui")
shutil.copytree("ImGuiBorderlessWindow/MainApp", f"../{projName}/ImGuiBorderlessWindow/MainApp")
shutil.copyfile("ImGuiBorderlessWindow/ImGuiBorderlessWindow.vcxproj", f"../{projName}/ImGuiBorderlessWindow/ImGuiBorderlessWindow.vcxproj")

for basename in os.listdir(f"../ImGuiBorderlessWindow/ImGuiBorderlessWindow"):
    if basename.endswith('.h'):
        pathname = os.path.join("../ImGuiBorderlessWindow/ImGuiBorderlessWindow", basename)
        if os.path.isfile(pathname):
            shutil.copy2(pathname, f"../{projName}/ImGuiBorderlessWindow/{basename}")

for basename in os.listdir(f"../ImGuiBorderlessWindow/ImGuiBorderlessWindow"):
    if basename.endswith('.cpp'):
        pathname = os.path.join("../ImGuiBorderlessWindow/ImGuiBorderlessWindow", basename)
        if os.path.isfile(pathname):
            shutil.copy2(pathname, f"../{projName}/ImGuiBorderlessWindow/{basename}")

shutil.copyfile("ImGuiBorderlessWindow.sln", f"../{projName}/ImGuiBorderlessWindow.sln")
shutil.copyfile("LICENSE", f"../{projName}/LICENSE")

os.chdir(f"../{projName}")

data = ""
with open("ImGuiBorderlessWindow.sln", "r") as f:
    data = f.read()
    data = data.replace("ImGuiBorderlessWindow", projName)

with open("ImGuiBorderlessWindow.sln", "w") as f:
    f.write(data)

os.rename("ImGuiBorderlessWindow.sln", f"{projName}.sln")

os.chdir("ImGuiBorderlessWindow")

with open("ImGuiBorderlessWindow.vcxproj", "r") as f:
    data = f.read()
    data = data.replace("ImGuiBorderlessWindow", projName)

with open("ImGuiBorderlessWindow.vcxproj", "w") as f:
    f.write(data)

os.rename("ImGuiBorderlessWindow.vcxproj", f"{projName}.vcxproj")

os.chdir("../")
os.rename("ImGuiBorderlessWindow", projName)

print(f"Project generated successfully in {os.getcwd()}")