//
// Created by Noah Campagne on 14/07/2024.
//

#include <CampEngine/Graphics/Screens/TestScreen.h>

#include <CampEngine/Game/Game.h>
#include <CampEngine/Graphics/Widgets/Button.h>
#include <CampEngine/Graphics/Widgets/TextInput.h>
#include <CampEngine/Graphics/Widgets/Tooltip.h>
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
    Button* open = gh.createButton("unlitShader.fs (open in Visual Studio Code)", 20)
    ->with_onRelease([](Widget* self) {
        system("open -a /Applications/Visual\\ Studio\\ Code.app /Applications/projets/projets_programmation/projets_C++/CampEngine++/resources/shaders/unlitShader.fs -F");
    })
    ->with_textAlign(ALIGN_LEFT)
    ->with_theme(primary);
    open->addTooltip(gh.createTooltip("Open fragment shader file in VS Code", 15)
        ->with_fadeOutTime(0.5f));

    Button* quit = gh.createButton("Quit", 20)
    ->with_onRelease([](Widget* self) {
        Game::activeGame->quit();
    })
    ->with_textAlign(ALIGN_LEFT)
    ->with_theme(danger);
    quit->addTooltip(gh.createTooltip("Hello world!", 15)
        ->with_fadeInTime(0.5f));

    gh.createTextInput(200, 25)
    ->with_floatingLabel(L"Type anything");

    float value = 0.8f;
    ProgressBar* pbar = gh.createProgressBar(200, 25, value)
    ->with_minValue(30.0f)
    ->with_maxValue(100.0f)
    ->with_hoverColorModifier(glm::vec4(1.0f));

    gh.setMargin(5);

    Slider* slider = gh.createSlider(200, 5, 0.5f)
    ->with_minValue(30.0f)
    ->with_maxValue(100.0f);

    gh.setMargin(0);

    TextBox* text = gh.createTextBox(L"Value: 0", 0, 20);

    slider->with_onValueChange([text, pbar](Widget* self) {
        Slider* slider = self->as<Slider>();
        int val = (int)slider->value;
        text->text = L"Value: "+std::to_wstring(val);
        pbar->value = slider->value;
    });
}
