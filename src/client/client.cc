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
#include <gf/ViewContainer.h>
#include <gf/Window.h>

#include <gf/Views.h>
#include <gf/Event.h>
#include <gf/Math.h>
#include <gf/RenderWindow.h>
#include <gf/Texture.h>
#include <gf/TileLayer.h>
#include <gf/VectorOps.h>
#include <gf/Views.h>
#include <gf/ViewContainer.h>
#include <gf/Window.h>


#include <set>
#include <string>

#include "LandSprite.h"

static constexpr float ZoomInFactor = 0.8f;
static constexpr float ZoomOutFactor = 1.25f;

int main() {
    // Create the main window and the renderer
    static constexpr gf::Vector2i ScreenSize(1080, 720);
    
    gf::Window window("FISK - Client", { 1280, 720 });
    gf::RenderWindow renderer(window);
    gf::Vector2f windows_size = window.getSize();

    // Create the views for the camera of the game
    
    gf::ViewContainer views;

    gf::ExtendView view;
    //view.setCenter({ 0.0f, 0.0f });
    view.setSize(ScreenSize);
    views.addView(view);

    views.setInitialFramebufferSize(ScreenSize);

    gf::ZoomingViewAdaptor adaptor(renderer, view);


    // Load a sprite to display
    
    
   

    // Testing a display for the map
    /* gf::Polygon america = gf::Polygon();
    america.addPoint(gf::Vector2f(50,50));
    america.addPoint(gf::Vector2f(300,50));
    america.addPoint(gf::Vector2f(275,150));
    america.addPoint(gf::Vector2f(400,175));
    america.addPoint(gf::Vector2f(450,100));
    america.addPoint(gf::Vector2f(500,175));
    america.addPoint(gf::Vector2f(450,300));
    america.addPoint(gf::Vector2f(275,350));
    america.addPoint(gf::Vector2f(300,375));
    america.addPoint(gf::Vector2f(150,350));
    america.addPoint(gf::Vector2f(125,175));
    america.addPoint(gf::Vector2f(112,150));
    america.addPoint(gf::Vector2f(85,175));
    america.addPoint(gf::Vector2f(50,125));
    america.addPoint(gf::Vector2f(25,100));

    fisk::LandShape land1 = fisk::La ndShape(1, "land1", std::vector<unsigned>(), 1, gf::Color::fromRgb(1,0,0), america); */

    // Testing a display for the map
    fisk::LandSprite land1 = fisk::LandSprite("Alaska", 1, gf::Color::fromRgb(1,0,0), "../data/sprites/lands/fisk_alaska_96_159.png", { 96, 159});


    gf::Sprite spr;
    gf::Texture text = gf::Texture("../data/sprites/lands/fisk_alaska_96_159.png");
    spr.setTexture(text);
    spr.setPosition({ 96, 159});

    renderer.clear(gf::Color::fromRgb((float)7/255, (float)24/255, (float)33/255));
        
    gf::Vector2f text_mov = { 1, 1 };
    srand(time(NULL));
    // Start the game loop

    while (window.isOpen()) {
        
        // Process events
        gf::Event event;
    
        while (window.pollEvent(event)) {
            switch (event.type) {
                case gf::EventType::Closed:
                window.close();
                break;
                
                //Events for the camera of the game (zoom, rotate, move)
                case gf::EventType::KeyPressed:
                    switch (event.key.scancode) {
                        //Events for the camera of the game (rotate, move)
                        case gf::Scancode::Up:
                        view.zoom(ZoomInFactor);
                        break;

                        case gf::Scancode::Down:
                        view.zoom(ZoomOutFactor);
                        break;

                        case gf::Scancode::Escape:
                        window.close();
                        break;

                        default:
                        break;
                    }

                default:
                break;
                }
            adaptor.processEvent(event);
            views.processEvent(event);
        }
        
    
        //Update the game

        // Draw the entities

        renderer.setView(view);
    
        renderer.clear();
        land1.draw(renderer);
       
        renderer.display();
    }
        
    return 0;
}