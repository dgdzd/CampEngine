//
// Created by Noah Campagne on 14/07/2024.
//

#include <CampEngine/Graphics/Screens/TestScreen.h>

#include <CampEngine/Game/Game.h>
#include <CampEngine/Graphics/Widgets/Button.h>
#include <CampEngine/Graphics/Widgets/TextInput.h>
#include <CampEngine/Utils/GuiHelper.h>

TestScreen::TestScreen(GLFWwindow* window) : Screen(window) {
    this->init();
}

void TestScreen::init() {
    Screen::init();

    /* Initialize GUI Helper */
    GuiHelper gh(window, glm::vec2(0.0, 400.0), this);
    gh.setPadding(0);
    gh.setMargin(0);

    /* Create widgets */
    gh.createButton("unlitShader.fs (open in Visual Studio Code)", 20)
    ->with_onRelease([](Widget* self) {
        system("open -a /Applications/Visual\\ Studio\\ Code.app /Applications/projets/projets_programmation/projets_C++/CampEngine++/resources/shaders/unlitShader.fs -F");
    })
    ->with_textAlign(ALIGN_LEFT)
    ->with_theme(primary);

    gh.createButton("Quit", 20)
    ->with_onRelease([](Widget* self) {
        Game::activeGame->quit();
    })
    ->with_textAlign(ALIGN_LEFT)
    ->with_theme(danger);

    gh.createTextInput(200, 25)
    ->with_floatingLabel(L"Type anything");

    float value = 0.8f;
    gh.createProgressBar(200, 25, value)
    ->with_minValue(0.0f)
    ->with_maxValue(1.0f)
    ->with_hoverColorModifier(glm::vec4(1.0f));

    gh.setMargin(5);

    Slider* slider = gh.createSlider(200, 5, 0.5f)
    ->with_minValue(0.0f)
    ->with_maxValue(4.0f);

    gh.setMargin(0);

    TextBox* text = gh.createTextBox(L"Mode: creative", 0, 20);

    slider->with_onValueChange([text](Widget* self) {
        Slider* slider = self->as<Slider>();
        int val = (int)slider->value;
        switch(val) {
            case 0: {
                text->text = L"Mode: creative";
                break;
            }
            case 1: {
                text->text = L"Mode: survival";
                break;
            }
            case 2: {
                text->text = L"Mode: adventure";
                break;
            }
            case 3: {
                text->text = L"Mode: hardcode";
                break;
            }
            case 4: {
                text->text = L"Mode: spectator";
                break;
            }
            default: {
                text->text = L"Mode: "+std::to_wstring((int)slider->value);
            }
        }
    });
}
