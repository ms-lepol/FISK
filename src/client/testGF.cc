#include <cstdlib>
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/RenderWindow.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/Vector.h>
#include <gf/Window.h>
#include <set>

int main() {
    // Create the main window and the renderer
    
    gf::Window window("Testing GF", { 1080, 720 });
    gf::RenderWindow renderer(window);
    gf::Vector2f windows_size = window.getSize();
    
    // Load a sprite to display
    
    gf::Texture texture("../data/sprites/sprite.png");
    
    gf::Sprite sprite(texture);
    
    sprite.setPosition({ windows_size.x/2-(sprite.getScale().x/2), windows_size.y/2-(sprite.getScale().y/2) });
    
    // Create a graphical text to display
    
    gf::Font font("../data/font/Kaph-Regular.ttf");
    
    gf::Text text("DVD", font, 50);
    
    
    renderer.clear(gf::Color::Black);
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        text.setColor(gf::Color::fromRgb(r,g,b));
    
    gf::Vector2f text_size = text.getLocalBounds().getSize();

    text.setPosition({ windows_size.x/2-(text_size.x/2), windows_size.y/2-(text_size.y/2) });
    
    gf::Vector2f text_mov = { 1, 1 };
    srand(time(NULL));
    // Start the game loop

    while (window.isOpen()) {
        
        // Process events
        gf::Vector2f text_pos = text.getPosition();
        text_pos.x += text_mov.x ;
        text_pos.y += text_mov.y ;
        text.setPosition(text_pos);

        if ((text_pos.x + text_size.x >= windows_size.x) || (text_pos.x <= 0)) {
        text_mov.x *= -1;
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        text.setColor(gf::Color::fromRgb(r,g,b));
        }
        if ((text_pos.y + text_size.y >= windows_size.y) || (text_pos.y <= 0)) {
            text_mov.y *= -1;
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            text.setColor(gf::Color::fromRgb(r,g,b));
        }

        gf::Event event;
    
        while (window.pollEvent(event)) {
        switch (event.type) {
            case gf::EventType::Closed:
            window.close();
            break;
    
            default:
            break;
        }
        }
    
        // Draw the entities
    
        renderer.clear();
        renderer.draw(sprite);
        renderer.draw(text);
        renderer.display();
    }
        
    return 0;
}