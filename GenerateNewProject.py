# Copyright (C) Avnish Kirnalli 2025.
print("Copyright (C) Avnish Kirnalli 2025.")

import platform
import sys
import os
from io import BytesIO
import importlib
import subprocess

def yes_or_no(question):
    reply = str(input(question + ' (y/n): ')).lower().strip()
    if not reply:
        return yes_or_no(question)
    if reply[0] == 'y' or reply[0] == 'yes':
        return True
    if reply[0] == 'n' or reply[0] == 'no':
        return False
    return yes_or_no(question)

def is_windows():
    return platform.system() == 'Windows'
def is_mac():
    return platform.system() == 'Darwin'
def is_linux():
    return platform.system() == 'Linux'

def InstallModule(package):
    if yes_or_no(f'Package {package} not found. Do you want to install Python Package {package}?'):
        subprocess.check_call([sys.executable, "-m", "pip", "install", package])
        try:
            return importlib.import_module(package)
        except ImportError:
            print('Failed to import module after installation')
            exit()
    else:
        print('Exiting')
        exit()

try:
    import shutil
except ImportError:
    shutil = InstallModule('shutil')
try:
    import requests
except ImportError:
    requests = InstallModule('requests')
try:
    from tqdm import tqdm
except ImportError:
    tqdm = InstallModule('tqdm')
    
try:
    import zipfile
except ImportError:
    zipfile = InstallModule('zipfile')
if is_mac() or is_linux():
    try:
        import tarfile
    except ImportError:
        tarfile = InstallModule('tarfile')

def DownloadPremake():
    if os.path.exists(f'{os.getcwd()}/premake'):
        print('Premake Up-to date')
        return

    print('Downloading Premake.')

    url = ""
    if is_windows():
        url = "https://github.com/premake/premake-core/releases/download/v5.0.0-beta5/premake-5.0.0-beta5-windows.zip"
    elif is_mac():
        url = "https://github.com/premake/premake-core/releases/download/v5.0.0-beta5/premake-5.0.0-beta5-macosx.tar.gz"
    elif is_linux():
        url = "https://github.com/premake/premake-core/releases/download/v5.0.0-beta5/premake-5.0.0-beta5-linux.tar.gz"
    
    req = requests.get(url)

    filename = url.split('/')[-1]

    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded Premake.')

    print('Starting Premake Extraction')

    if is_windows():
        with zipfile.ZipFile(BytesIO(req.content)) as zf:
            zf.extract('premake5.exe', 'premake/')
    if is_mac() or is_linux():
        archive = tarfile.open(filename)
        archive.extract('premake5', 'premake/', filter='data')
        archive.close()
        os.chmod(f'{os.getcwd()}/premake/premake5', 0o755)

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

    if projName == 'default':
        print(f'Generating default project at {os.getcwd()}')
        if is_windows():
            os.system(f'{os.getcwd()}/premake/premake5 vs2022')
            print('Generated Visual Studio solution')
        if is_mac():
            os.system(f'{os.getcwd()}/premake/premake5 xcode4')
            print('Generated XCode project files.')
        if is_linux():
            os.system(f'{os.getcwd()}/premake/premake5 gmake')
            print('Generated GMake project files.')
        input('Press any key to continue....')
        return
    
    print("Generating project")

    shutil.copytree("ImGuiBorderlessWindow", f'{projName}/{projName}')

    shutil.copy('premake5.lua', f'{projName}/premake5.lua')

    replace_in_file(f'{projName}/premake5.lua', 'ImGuiBorderlessWindow', projName)

    os.chdir(f'{os.getcwd()}/{projName}')
    if is_windows():
            os.system(f'{os.getcwd()}/../premake/premake5 vs2022')
            print('Generated Visual Studio solution')
    if is_mac():
        os.system(f'{os.getcwd()}/../premake/premake5 xcode4')
        print('Generated XCode project files.')
    if is_linux():
        os.system(f'{os.getcwd()}/../premake/premake5 gmake')
        print('Generated GMake project files.')
    os.chdir(f'{os.getcwd()}/..')

    # os.remove(f'{projName}/premake5.lua')

    # Set App Name in Info-macOS.plist
    replace_in_file(f'{projName}/{projName}/Gui/Platform/Mac/Info-macOS.plist', "APP_NAME", projName)

    print(f'Project generated successfully at {os.getcwd()}\\{projName}')
    input('Press any key to continue....')

def DownloadDependencies():
    print('Fetching Dependencies')
    DownloadImGui()
    DownloadPremake()

def CheckInternetConnection():
    try:
        requests.get('https://google.com')
    except Exception as e:
        return False
    return True

if not CheckInternetConnection():
    print('No Internet Connection detected! Internet is required to run this script.')
    input('Press any key to continue....')
    exit()

DownloadDependencies()
main()


