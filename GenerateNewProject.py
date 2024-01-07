# Copyright (C) Avnish Kirnalli 2023.

import os
import shutil

print("Copyright (C) Avnish Kirnalli 2023.")

projName = input("Enter project name: ")
print("Generating project")

os.mkdir(f"../{projName}")

shutil.copytree("ImGuiBorderlessWindow/Gui", f"../{projName}/ImGuiBorderlessWindow/Gui")
shutil.copyfile("ImGuiBorderlessWindow/ImGuiBorderlessWindow.vcxproj", f"../{projName}/ImGuiBorderlessWindow/ImGuiBorderlessWindow.vcxproj") # Is renamed later on.

for basename in os.listdir(f"{os.getcwd()}/ImGuiBorderlessWindow"):
    if basename.endswith('.h'):
        pathname = os.path.join(f"{os.getcwd()}/ImGuiBorderlessWindow", basename)
        if os.path.isfile(pathname):
            shutil.copy2(pathname, f"../{projName}/ImGuiBorderlessWindow/{basename}")

for basename in os.listdir(f"{os.getcwd()}/ImGuiBorderlessWindow"):
    if basename.endswith('.cpp'):
        pathname = os.path.join(f"{os.getcwd()}/ImGuiBorderlessWindow", basename)
        if os.path.isfile(pathname):
            shutil.copy2(pathname, f"../{projName}/ImGuiBorderlessWindow/{basename}")

shutil.copyfile("ImGuiBorderlessWindow.sln", f"../{projName}/ImGuiBorderlessWindow.sln")
shutil.copyfile("LICENSE", f"../{projName}/ImGuiBorderlessWindow/Gui/LICENSE.txt")

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