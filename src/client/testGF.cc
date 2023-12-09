#include <cstdlib>
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/RenderWindow.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/Vector.h>
#include <gf/VectorOps.h>
#include <gf/Polygon.h>
#include <gf/Shapes.h>
#include <gf/Window.h>
#include <set>
#include <string>
#include "LandShape.h"

int main() {
    // Create the main window and the renderer
    
    gf::Window window("Testing GF", { 1080, 720 });
    gf::RenderWindow renderer(window);
    gf::Vector2f windows_size = window.getSize();
    
    // Load a sprite to display
    
    gf::Texture texture("../data/sprites/sprite.png");
    
    gf::Sprite sprite(texture);
    
    sprite.setPosition({ windows_size.x/2-(sprite.getScale().width/2), windows_size.y/2-(sprite.getScale().height/2) });
    
    // Create a graphical text to display
    
    gf::Font font("../data/font/Kaph-Regular.ttf");
    
    gf::Text text("DVD", font, 50);
    

    // Testing a display for the map
    gf::Polygon america = gf::Polygon();
    america.addPoint(gf::Vector2f(100,100));
    america.addPoint(gf::Vector2f(600,100));
    america.addPoint(gf::Vector2f(550,300));
    america.addPoint(gf::Vector2f(800,350));
    america.addPoint(gf::Vector2f(900,200));
    america.addPoint(gf::Vector2f(1000,350));
    america.addPoint(gf::Vector2f(900,600));
    america.addPoint(gf::Vector2f(550,700));
    america.addPoint(gf::Vector2f(600,750));
    america.addPoint(gf::Vector2f(300,700));
    america.addPoint(gf::Vector2f(250,350));
    america.addPoint(gf::Vector2f(225,300));
    america.addPoint(gf::Vector2f(170,350));
    america.addPoint(gf::Vector2f(100,250));
    america.addPoint(gf::Vector2f(50,200));

    fisk::LandShape land1 = fisk::LandShape(1, "land1", std::vector<unsigned>(), 1, gf::Color::fromRgb(1,0,0), america);


    renderer.clear(gf::Color::Black);
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        text.setColor(gf::Color::fromRgb(r,g,b));
    
    gf::Vector2f text_size = text.getLocalBounds().getSize();

    text.setPosition({ windows_size.x/2-(text_size.width/2), windows_size.y/2-(text_size.height/2) });
    
    gf::Vector2f text_mov = { 1, 1 };
    srand(time(NULL));
    // Start the game loop

    while (window.isOpen()) {
        
        // Process events
        gf::Vector2f text_pos = text.getPosition();
        text_pos.x += text_mov.x ;
        text_pos.y += text_mov.y ;

        if ((text_pos.x + text_size.x >= windows_size.x) || (text_pos.x <= 0)) {
        text_mov.x *= -1;
        text_pos.x += text_mov.x ;
        
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        text.setColor(gf::Color::fromRgb(r,g,b));
        }
        if ((text_pos.y + text_size.y >= windows_size.y) || (text_pos.y <= 0)) {
            text_mov.y *= -1;
            text_pos.y += text_mov.y ;
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            text.setColor(gf::Color::fromRgb(r,g,b));
        }

        text.setPosition(text_pos);

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
        gf::ConvexShape shape = land1.getShape();
        renderer.draw(shape);
        renderer.display();
    }
        
    return 0;
}