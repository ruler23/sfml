////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <memory>
#include <string>
#include "random.cpp"
#include "texturecodex.h"
#include "character.h"

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////


std::string character_normal = "resources/professor_walk_cycle_no_hat.png";
std::string character_green = "resources/green.png";
const int npc_max = 20;

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> TextureCodex::texturePtrs;

int main()
{
	// Create the main window
	const int gameWidth = 1000;
	const int gameHeight = 800;

	//sf::RenderWindow window(sf::VideoMode(800, 600), "Version 0.1");
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Version 0.1",
		sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	// Load the text font
	sf::Font font;
	if (!font.loadFromFile("resources/sansation.ttf"))
		return EXIT_FAILURE;

	// Initialize message
	sf::Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(12);
	/*pauseMessage.setPosition(170.f, 150.f);*/
	pauseMessage.setFillColor(sf::Color::White);
	//pauseMessage.setString("TEST");

	/*{
		Character fucker({ 100.0f,100.0f });
		Character fucker2({ 100.0f,200.0f });
	}*/

	TextureCodex::MurderOrphans();

	Character player({ 100.0f,100.0f }, character_normal);

	//Hauptspeicher fuer NPCs
	std::vector<Character> npc;
	std::vector<sf::Vector2f> npc_direction_vector; //Moeglichkeiten: { 0.0f,0.0f } / { 1.0f,0.0f } / { 0.0f,1.0f } / { -1.0f,0.0f } / { 0.0f,-1.0f }
	std::vector<int> npc_how_many_moves_until_direction_change;//Moeglichkeiten: 1 - 10
	//ENDE Hauptspeicher

	float y_coord = 100.0f;
	float x_coord = 100.0f;
	int i;

	//Initiale Erstellung der NPCs
	for (i = 0; i < npc_max; i++) {
		
		y_coord = y_coord + 10;
	/*	x_coord = x_coord + 10;*/
	
		x_coord = x_coord + Zufall::random(0, 100);
		Character fucker3({ x_coord,y_coord }, character_green);
		npc.push_back(fucker3);
		//Wieviele Schritte soll der NPC in eine Richtung machen? Per Zufall ermitteln lassen.
		npc_how_many_moves_until_direction_change.push_back(Zufall::random(0, 10));
		//In welche Richtung soll der NPC laufen? Soll erstmal den Player verfolgen.

		float npc_x = npc[i].getPostion().x;
		float npc_y = npc[i].getPostion().y;
		float player_x = player.getPostion().x;
		float player_y = player.getPostion().y;

		int y_oder_x = Zufall::random(0, 1);

			if (y_oder_x == 1) {
				if (player_x > npc_x) {
					npc_direction_vector.push_back({ -1.0f,0.0f });
				}
				else {
					npc_direction_vector.push_back({ 1.0f,0.0f });
				}
			}
			else
			{
				if (player_y > npc_y) {
					npc_direction_vector.push_back({ 0.0f,1.0f });
				}
				else {
					npc_direction_vector.push_back({ 0.0f,-1.0f });
				}
			}

	}
	//Character fucker2({ 100.0f,200.0f }, character_normal);
	

	// timepoint for delta time measurement
	auto tp = std::chrono::steady_clock::now();

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// get dt
		float dt;
		{
			const auto new_tp = std::chrono::steady_clock::now();
			dt = std::chrono::duration<float>(new_tp - tp).count();
			tp = new_tp;
		}

		// handle input
		sf::Vector2f dir = { 0.0f,0.0f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			dir.y -= 1.0f;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			dir.y += 1.0f;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			dir.x -= 1.0f;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dir.x += 1.0f;
			
		}
		player.SetDirection(dir);
		
		// update model
		player.Update(dt);
		//fucker2.Update(dt);
	/*	fucker3.Update(dt);*/

		// Clear screen
		window.clear();

		int a;
		for (a = 0; a < npc.size(); a++) {
			/*float x = Zufall::random(-1, 1);
			float y = Zufall::random(-1, 1);*/
		/*	sf::Vector2f richtung = {x, y};*/

			if (npc_how_many_moves_until_direction_change[a] > 0) {

				npc_how_many_moves_until_direction_change[a]--;
				
			}
			else
			{

				float npc_x = npc[a].getPostion().x;
				float npc_y = npc[a].getPostion().y;
				float player_x = player.getPostion().x;
				float player_y = player.getPostion().y;
				int y_oder_x = Zufall::random(0, 1);

				if (y_oder_x == 1) {
					if (player_x > npc_x) {
						npc_direction_vector[a] = {1.0f,0.0f};
					}
					else {
						npc_direction_vector[a] = {-1.0f,0.0f};
					}
				}
				else
				{
					if (player_y > npc_y) {
						npc_direction_vector[a] = {0.0f,1.0f};
					}
					else {
						npc_direction_vector[a] = {0.0f,-1.0f};
					}
				}

				//Wieviele Schritte soll der NPC in eine Richtung machen? Per Zufall ermitteln lassen.
				npc_how_many_moves_until_direction_change[a] = Zufall::random(0, 10);
				

			}

			npc[a].SetDirection(npc_direction_vector[a]);
			npc[a].Update(dt);
			// Draw the sprite	
			npc[a].Draw(window);
		}

		player.Draw(window);

		//Koordinaten einblenden ueber dem Player
		std::string num_text = std::to_string(player.getPostion().x);
		std::string rounded_x = num_text.substr(0, num_text.find(".") + 0);
		std::string num_text2 = std::to_string(player.getPostion().y);
		std::string rounded_y = num_text2.substr(0, num_text2.find(".") + 0);
		pauseMessage.setString("x" + rounded_x + "y" + rounded_y);
		//pauseMessage.setPosition(character_x, character_y);
		pauseMessage.setPosition(player.getPostion());
		window.draw(pauseMessage);

		// Update the window
		window.display();
	}


	return EXIT_SUCCESS;
}









// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
