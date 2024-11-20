# Copyright (C) Avnish Kirnalli 2024.
print("Copyright (C) Avnish Kirnalli 2024.")

import os
import subprocess

from io import BytesIO

# Module checks with Install option
def yes_or_no(question):
    reply = str(input(question + ' (y/n): ')).lower().strip()
    if reply[0] == 'y' or reply[0] == 'yes':
        return True
    if reply[0] == 'n' or reply[0] == 'no':
        return False
    return yes_or_no(question)

def InstallModule(package):
    if yes_or_no(f'Package {package} not found. Do you want to install Python Package {package}?'):
        subprocess.call(['pip', 'install', package])
        os.system('cls')
        os.system(f'python {os.getcwd()}/{__file__}')
        exit()
    else:
        print('Exiting')
        exit()

try:
    import shutil
except ImportError as e:
    InstallModule('shutil')
try:
    import requests
except ImportError as e:
    InstallModule('requests')
try:
    import zipfile
except ImportError as e:
    InstallModule('zipfile')
try:
    from tqdm import tqdm
except ImportError as e:
    InstallModule('tqdm')

def DownloadPremake():
    if os.path.exists(f'{os.getcwd()}/premake'):
        print('Premake Up-to date')
        return

    print('Downloading Premake.')

    url = f'https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip'
    req = requests.get(url)

    filename = url.split('/')[-1]

    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded Premake.')

    print('Starting Premake Extraction')

    with zipfile.ZipFile(BytesIO(req.content)) as zf:
        zf.extract('premake5.exe', 'premake/')

    print('Premake extracted Successfully')

    print('Deleting Premake Residual Files')

    os.remove(f'{os.getcwd()}/{filename}')

    print('Downloading Premake License')

    url = f'https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt'
    req = requests.get(url)

    with open('premake/LICENSE.txt', 'wb') as output_file:
        output_file.write(req.content)

    print('Premake License downloaded.')

    print('Premake installed successfully!')

def DownloadImGui():
    response = requests.get("https://api.github.com/repos/ocornut/imgui/releases/latest")
    versionNo = response.json()["name"]
    versionNo = versionNo.replace('v', '').strip()

    if os.path.exists(f'{os.getcwd()}/ImGuiBorderlessWindow/Gui/ThirdParty/ImGui'):
        f = open(f'{os.getcwd()}/ImGuiBorderlessWindow/Gui/ThirdParty/ImGui/version.txt')
        if f.read() == versionNo:
            print('ImGui Up-to date')
            return
        else:
            if yes_or_no(f'ImGui is outdated, current version: {f.read()}, latest version: {versionNo}, do you want to update it?'):
                print(f'Deleting current version of ImGui ({f.read()})')
                shutil.rmtree(f'{os.getcwd()}/ImGuiBorderlessWindow/Gui/ThirdParty/ImGui')
                print(f'Downloading latest version of ImGui ({versionNo})')
                DownloadImGui()
                return
            else:
                print(f'Continuing with current version of ImGui ({f.read()})')
                return

    print('Downloading ImGui.')

    print(f"ImGui Version: {versionNo}")

    url = f'https://github.com/ocornut/imgui/archive/refs/tags/v{versionNo}.zip'
    req = requests.get(url)

    filename = url.split('/')[-1]

    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded ImGui.')

    print('Starting ImGui Extraction')

    with zipfile.ZipFile(BytesIO(req.content)) as zf:
        for member in tqdm(zf.infolist(), desc='Extracting ImGui '):
            try:
                zf.extract(member, os.getcwd())
            except zipfile.error as e:
                print(f'Error while extracting ImGui: {e}')
                pass

    print('ImGui extracted Successfully')

    print('Deleting ImGui Residual Files')

    os.remove(f'{os.getcwd()}/{filename}')

    print('Finalizing ImGui Setup')

    if os.path.exists(f'{os.getcwd()}/ImGui'):
        shutil.rmtree(f'{os.getcwd()}/ImGui')

    os.rename(f'imgui-{versionNo}', 'ImGui')

    # writing version.txt
    with open('ImGui/version.txt', "w") as f:
        f.write(versionNo)

    shutil.copy('ImGui/backends/imgui_impl_dx9.h', 'ImGui/imgui_impl_dx9.h')
    shutil.copy('ImGui/backends/imgui_impl_dx9.cpp', 'ImGui/imgui_impl_dx9.cpp')
    shutil.copy('ImGui/backends/imgui_impl_win32.h', 'ImGui/imgui_impl_win32.h')
    shutil.copy('ImGui/backends/imgui_impl_win32.cpp', 'ImGui/imgui_impl_win32.cpp')
    shutil.copy('ImGui/misc/cpp/imgui_stdlib.h', 'ImGui/imgui_stdlib.h')
    shutil.copy('ImGui/misc/cpp/imgui_stdlib.cpp', 'ImGui/imgui_stdlib.cpp')

    shutil.move(f'{os.getcwd()}/ImGui', f'{os.getcwd()}/ImGuiBorderlessWindow/Gui/ThirdParty/ImGui')

    print('ImGui installed successfully!')

def replace_in_file(file_path, target_string, replacement_string):
    # Read the file content
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
    
    # Replace occurrences of the target string
    modified_content = content.replace(target_string, replacement_string)
    
    # Write the modified content back to the file
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(modified_content)

def main():
    projName = input("Enter project name: ")
    print("Generating project")

    shutil.copytree("ImGuiBorderlessWindow", f'{projName}/{projName}')

    shutil.copy('premake5.lua', f'{projName}/premake5.lua')

    replace_in_file(f'{projName}/premake5.lua', 'ImGuiBorderlessWindow', projName)

    subprocess.run(["cmd", "/c", f'{os.getcwd()}/premake/premake5.exe vs2022'], cwd=f'{os.getcwd()}/{projName}')

    os.remove(f'{projName}/premake5.lua')

    print(f'Project generated successfully at {os.getcwd()}\{projName}')

def DownloadDependencies():
    DownloadImGui()
    DownloadPremake()

DownloadDependencies()
main()