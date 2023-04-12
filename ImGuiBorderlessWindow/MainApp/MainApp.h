#pragma once
#include "../App.h"

class MainApp : public App
{
public:
    MainApp();
    
    void Render() override;
    std::string text;
};
