#ifndef _MENU_SCENE_INCLUDE
#define _MENU_SCENE_INCLUDE

#include "Scene.h"
#include "Sprite.h"
#include "Texture.h"

class MenuScene : public Scene
{
public:
    MenuScene();
    ~MenuScene();
    void init() override;
    void update(int deltaTime) override;
    void render() override;

private:
    void initShaders();
    Sprite* menuQuad;   // Menu quad
    Texture menuTexture;
    ShaderProgram texProgram;
    glm::mat4 projection;
};

#endif // _MENU_SCENE_INCLUDE
