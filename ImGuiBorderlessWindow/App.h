#pragma once

class App
{
public:
    static App* Create() { return new App(); };

    App();
    
    void Update();

    void Render();
    
private:
    
};
