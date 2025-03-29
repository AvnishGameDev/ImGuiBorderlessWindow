#include "Platform.h"

#ifdef PLATFORM_WINDOWS
#include "Windows/WindowsPlatform.h"
#endif
#ifdef PLATFORM_MAC
#include "Mac/MacPlatform.h"
#endif
#ifdef PLATFORM_LINUX
#include "Linux/LinuxPlatform.h"
#endif

#if _DEBUG
#include <iostream>
#endif

Platform* Platform::m_CurrentPlatform = nullptr;

Platform* Platform::Get()
{
    if (m_CurrentPlatform)
        return m_CurrentPlatform;

#ifdef PLATFORM_WINDOWS
    m_CurrentPlatform = new WindowsPlatform();
#endif
#ifdef PLATFORM_MAC
    m_CurrentPlatform = new MacPlatform();
#endif
#ifdef PLATFORM_LINUX
    m_CurrentPlatform = new LinuxPlatform();
#endif

#if _DEBUG
    if (!m_CurrentPlatform)
        std::cerr << "Failed to create Platform!" << std::endl;
#endif

    return m_CurrentPlatform;
}
