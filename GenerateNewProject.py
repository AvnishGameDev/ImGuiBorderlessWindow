# Copyright (C) Avnish Kirnalli 2024.

import platform
import sys
import os
from io import BytesIO

def is_windows():
    return platform.system() == 'Windows'
def is_mac():
    return platform.system() == 'Darwin'

os.system('cls' if is_windows() else 'clear')
print("Copyright (C) Avnish Kirnalli 2024.")

def in_venv():
    return sys.prefix != sys.base_prefix

def restart():
    os.system(f"{os.getcwd()}/.python/{ 'Scripts' if is_windows() else 'bin' }/python {__file__}")
    exit()

def create_venv():
    if not os.path.exists(f'{os.getcwd()}/.python'):
        print(f'Creating Python venv at {os.getcwd()}/.python')
        os.system('python3 -m venv ./.python')
    print(f'Activating Python venv at {os.getcwd()}/.python')
    if is_windows():
        os.system('.python/Scripts/activate')
    if is_mac():
        os.system('source ./.python/bin/activate')
    restart()

if not in_venv():
    create_venv()

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
        os.system(f"{os.getcwd()}/.python/{ 'Scripts' if is_windows() else 'bin' }/pip3 install {package}")
        restart()
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
    from tqdm import tqdm
except ImportError as e:
    InstallModule('tqdm')
    
try:
    import zipfile
except ImportError as e:
    InstallModule('zipfile')
if is_mac():
    try:
        import tarfile
    except ImportError as e:
        InstallModule('tarfile')

def DownloadPremake():
    if os.path.exists(f'{os.getcwd()}/premake'):
        print('Premake Up-to date')
        return

    print('Downloading Premake.')

    url = f'https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip' if is_windows() else f'https://github.com/premake/premake-core/releases/download/v5.0.0-beta3/premake-5.0.0-beta3-macosx.tar.gz'
        
    req = requests.get(url)

    filename = url.split('/')[-1]

    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded Premake.')

    print('Starting Premake Extraction')

    if is_windows():
        with zipfile.ZipFile(BytesIO(req.content)) as zf:
            zf.extract('premake5.exe', 'premake/')
    if is_mac():
        archive = tarfile.open(filename)
        archive.extract('premake5', 'premake/', filter='data')
        archive.close()
        os.system(f'chmod +x {os.getcwd()}/premake/premake5')

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

    if projName == 'default':
        os.system(f'{os.getcwd()}/premake/premake5 vs2022')
        os.system(f'{os.getcwd()}/premake/premake5 xcode4')
        return

    # Set App Name in Info-macOS.plist
    replace_in_file("ImGuiBorderlessWindow/Gui/Platform/Mac/Info-macOS.plist", "APP_NAME", projName)

    shutil.copytree("ImGuiBorderlessWindow", f'{projName}/{projName}')

    shutil.copy('premake5.lua', f'{projName}/premake5.lua')

    replace_in_file(f'{projName}/premake5.lua', 'ImGuiBorderlessWindow', projName)

    os.chdir(f'{os.getcwd()}/{projName}')
    os.system(f'{os.getcwd()}/../premake/premake5 vs2022')
    os.system(f'{os.getcwd()}/../premake/premake5 xcode4')
    os.chdir(f'{os.getcwd()}/..')

    os.remove(f'{projName}/premake5.lua')

    print(f'Project generated successfully at {os.getcwd()}\\{projName}')

def DownloadDependencies():
    DownloadImGui()
    DownloadPremake()

DownloadDependencies()
main()
