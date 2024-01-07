// Copyright (C) 2023 Avnish Kirnalli.

#pragma once
#include <string>

class App
{
public:
    template <class T>
    static T* Create() { return new T(); };
    
    App(std::string _appName, int _width = 400, int _height = 140);
    virtual ~App();
    
    virtual void Update();

    virtual void BeginRender();
    virtual void Render() = 0;
    virtual void EndRender();
    
private:
    std::string appName;
    int windowWidth;
    int windowHeight;
};
