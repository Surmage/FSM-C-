#include <iostream>
#include "Agent.h"
#include <SFML/Graphics.hpp>

const int videoX = 1280;
const int videoY = 720;

int main() {
	std::vector<Agent>agents;
	//create actor 1
	char txtAgent1[] = "Agent1";
	Agent a(txtAgent1, 0);
	//create actor 2
	char txtAgent2[] = "Agent2";
	Agent b(txtAgent2, 1);
	//create actor 3
	char txtAgent3[] = "Agent3";
	Agent c(txtAgent3, 2);
	//create actor 4
	char txtAgent4[] = "Agent4";
	Agent d(txtAgent4, 3);

	agents.push_back(a); agents.push_back(b); agents.push_back(c); agents.push_back(d);


	Telegram t(agents[0], agents[1], agents[2], agents[3]);
	StepManager sm;

	//Give agents a phone
	agents[0].setPhone(&t);
	agents[1].setPhone(&t);
	agents[2].setPhone(&t);
	agents[3].setPhone(&t);

	//Give agents a clock
	agents[0].setClock(&sm);
	agents[1].setClock(&sm);
	agents[2].setClock(&sm);
	agents[3].setClock(&sm);
	

	sf::RenderWindow window(sf::VideoMode(videoX, videoY), "FSM");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	srand(time(NULL));
	std::vector<sf::RectangleShape>agentShapes;
	for (int i = 0; i < 4; i++) {
		float r1 = (rand() % 255) - 1.f;
		float r2 = (rand() % 255) - 1.f;
		float r3 = (rand() % 255) - 1.f;

		sf::RectangleShape shape(sf::Vector2f(50.f, 50.f));
		shape.setFillColor(sf::Color(fabsf(r1), fabsf(r2), fabsf(r3)));
		shape.setPosition(sf::Vector2f(100, 100));
		agentShapes.push_back(shape);
	}
	
	std::vector<sf::CircleShape>shapes;
	std::vector<sf::Vector2f>locations;
	for (int i = 0; i < 6; i++) {
		sf::Vector2f loc = LocationC::getCoords(i, 0);
		locations.push_back(loc);

		sf::CircleShape shape(100.f);
		std::cout << "Shape size: " << shape.getRadius();
		shape.setFillColor(sf::Color::White);
		shape.setPosition(loc);
		shapes.push_back(shape);
	}

	//rect.setFillColor(sf::Color::Green);
	sf::Font font;
	if (!font.loadFromFile("tahoma.ttf"))
	{
		// error...
	}
	std::vector<sf::Text>texts;
	{
		sf::Text agentText;
		agentText.setString("Hello");
		agentText.setPosition(900, 10);
		texts.push_back(agentText);

		sf::Text timeText;
		timeText.setString("Hello");
		timeText.setPosition(300, 10);
		texts.push_back(timeText);

		sf::Text chat;
		chat.setString("");
		chat.setPosition(900, 400);
		texts.push_back(chat);

		sf::Text mines, home, restaurant, bar, field, graveyard;
		mines.setString("MINES"); home.setString("HOME"); restaurant.setString("RESTAURANT");
		bar.setString("BAR"); field.setString("FIELD"); graveyard.setString("GRAVEYARD");
		
		texts.push_back(mines); texts.push_back(home); texts.push_back(restaurant);
		texts.push_back(bar); texts.push_back(field); texts.push_back(graveyard);

		for (int i = 0; i < texts.size(); i++) {
			texts[i].setFont(font);
			texts[i].setCharacterSize(24);
			texts[i].setFillColor(sf::Color::Green);
		}
	}


	sf::Clock deltaClock;

	float prevStep = 0;
	float frames = 0;
	int i = 0;
	bool isPaused = true;
	int speed = 1;
	sf::Time start;
	sf::Time elapsed;
	start = deltaClock.getElapsedTime();
	
	srand((unsigned)time(NULL));

	sm.step = 8;
	int step = 0;
	sf::Vector2f oldPos;
	int selectedAgent = 0;
	
	while (window.isOpen()) {		
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(window, event);

			switch (event.type)
			{
				case sf::Event::Closed :
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Space)
					{
						isPaused = !isPaused;
					}
					else if (event.key.code == sf::Keyboard::Num0 || 
						event.key.code == sf::Keyboard::Numpad0)
					{
						isPaused = !isPaused;
					}
					else if (event.key.code == sf::Keyboard::Num1 ||
						event.key.code == sf::Keyboard::Numpad1)
					{
						speed = 1;
						isPaused = false;
					}
					else if (event.key.code == sf::Keyboard::Num2 ||
						event.key.code == sf::Keyboard::Numpad2)
					{
						speed = 2;
						isPaused = false;
					}
					else if (event.key.code == sf::Keyboard::Num3 ||
						event.key.code == sf::Keyboard::Numpad3)
					{
						speed = 3;
						isPaused = false;
					}
					else if (event.key.code == sf::Keyboard::Num4 ||
						event.key.code == sf::Keyboard::Numpad4)
					{
						speed = 4;
						isPaused = false;
					}
					else if (event.key.code == sf::Keyboard::Num5 ||
						event.key.code == sf::Keyboard::Numpad5)
					{
						speed = 5;
						isPaused = false;
					}
					else if (event.key.code == sf::Keyboard::Num6 ||
						event.key.code == sf::Keyboard::Numpad6)
					{
						speed = 6;
						isPaused = false;
					}
					else if (event.key.code == sf::Keyboard::Num7 ||
						event.key.code == sf::Keyboard::Numpad7)
					{
						speed = 7;
						isPaused = false;
					}
					else if (event.key.code == sf::Keyboard::Num8 ||
						event.key.code == sf::Keyboard::Numpad8)
					{
						speed = 8;
						isPaused = false;
					}
					else if (event.key.code == sf::Keyboard::Num9 ||
						event.key.code == sf::Keyboard::Numpad9)
					{
						speed = 9;
						isPaused = false;
						
					}

					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left) {
						oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
						for (int i = 0; i < agentShapes.size(); i++) {
							if (agentShapes[i].getGlobalBounds().contains(oldPos)) {
								selectedAgent = i;
								break;
							}
						}
					}
					break;		
			}
		}

		elapsed = deltaClock.getElapsedTime() - start;
		if (!isPaused) {
			//Update agents
			agents[0].Update(sm.getHour());
			agents[1].Update(sm.getHour());
			agents[2].Update(sm.getHour());
			agents[3].Update(sm.getHour());
			//t.printAgentStats();
			sf::sleep(sf::milliseconds(500 - speed * 50));
			sm.step = step;
			step++;

		}

		ImGui::SFML::Update(window, deltaClock.getElapsedTime());
		ImGui::Begin("FSM");
		ImGui::Checkbox("Pause", &isPaused);
		ImGui::SliderInt("speed", &speed, 0, 10);
		if (isPaused) {
			
			ImGui::BeginChild("Agent A", ImVec2(0, 0), true,
				ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);
			ImGui::SliderFloat("Energy", &agents[selectedAgent].stats.energy, 0, 100);
			ImGui::SliderFloat("Fullness", &agents[selectedAgent].stats.fullness, 0, 100);
			ImGui::SliderFloat("Happiness", &agents[selectedAgent].stats.happiness, 0, 100);
			ImGui::SliderFloat("Thirst", &agents[selectedAgent].stats.thirst, 0, 100);
			ImGui::SliderFloat("Money", &agents[selectedAgent].stats.money, 0, 100);
			ImGui::EndChild();
		}
		
		ImGui::End();

		//std::cout << isPaused << std::endl;
		
		texts[0].setString((std::string(1, (static_cast<char>(agents[selectedAgent].type)))) + "\n" +
			"Energy: " + std::to_string(agents[selectedAgent].stats.energy) + "\n" +
			"Money: " + std::to_string(agents[selectedAgent].stats.money) + "\n" +
			"Fullness: " + std::to_string(agents[selectedAgent].stats.fullness) + "\n" +
			"Thirst: " + std::to_string(agents[selectedAgent].stats.thirst) + "\n" +
			"Happiness: " + std::to_string(agents[selectedAgent].stats.happiness) + "\n" +
			"Counter: " + std::to_string(agents[selectedAgent].counter));

		texts[1].setString("Day: " + std::to_string(sm.getDay()) + 
			" Hour: " + std::to_string(sm.getHour()) +
			" Minute: " + std::to_string(sm.getMinute()));

		texts[2].setString(t.getMessageChat());

		for (int i = 3; i < texts.size(); i++) {
			texts[i].setPosition(sf::Vector2f(shapes[i - 3].getPosition().x,
				shapes[i - 3].getPosition().y + (shapes[i - 3].getRadius() * 2)));
		}
		
		window.clear();
		for (int i = 0; i < shapes.size(); i++) {
			window.draw(shapes[i]);
		}
		for (int i = 0; i < agentShapes.size(); i++) {
			agentShapes[i].setPosition(sf::Vector2f(agents[i].position.x, agents[i].position.y));
			window.draw(agentShapes[i]);
		}
		for (int i = 0; i < texts.size(); i++) {
			window.draw(texts[i]);
		}
		ImGui::SFML::Render(window);
		
		window.display();		
	}

	ImGui::SFML::Shutdown();

	return 0;
}