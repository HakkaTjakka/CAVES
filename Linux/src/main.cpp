#include <SFML/Graphics.hpp>

extern void launch_MCEDITOR();
extern int MCEDITOR_running;
extern int MCEDITOR_stop;
extern void terminate_MCEDITOR();


int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    launch_MCEDITOR();

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                terminate_MCEDITOR();
                app.close();
            }
            if (MCEDITOR_running==0)
                app.close();
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(sprite);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
