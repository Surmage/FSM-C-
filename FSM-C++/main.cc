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


	Telegram t(a, b, c, d);
	StepManager sm;

	//Give agents a phone
	a.setPhone(&t);
	b.setPhone(&t);
	c.setPhone(&t);
	d.setPhone(&t);

	//Give agents a clock
	a.setClock(&sm);
	b.setClock(&sm);
	c.setClock(&sm);
	d.setClock(&sm);

	agents.push_back(a); agents.push_back(b); agents.push_back(c); agents.push_back(d);

	
	

	sf::RenderWindow window(sf::VideoMode(videoX, videoY), "FSM");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	std::vector<sf::RectangleShape>agentShapes;
	for (int i = 0; i < 4; i++) {
		sf::RectangleShape shape(sf::Vector2f(50.f, 50.f));
		shape.setFillColor(sf::Color::Red);
		shape.setPosition(sf::Vector2f(100, 100));
		agentShapes.push_back(shape);
	}
	
	std::vector<sf::CircleShape>shapes;
	std::vector<sf::Vector2f>locations;
	for (int i = 0; i < 6; i++) {
		sf::Vector2f loc = LocationC::getCoords(i, 0);
		locations.push_back(loc);

		sf::CircleShape shape(100.f);
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
	sf::Text text;
	text.setString("Hello");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Green);
	text.setPosition(50,10);
	texts.push_back(text);

	sf::Text timeText;
	timeText.setString("Hello");
	timeText.setFont(font);
	timeText.setCharacterSize(24);
	timeText.setFillColor(sf::Color::White);
	timeText.setPosition(300, 10);
	texts.push_back(timeText);

	sf::Text chat;
	chat.setString("");
	chat.setFont(font);
	chat.setCharacterSize(24);
	chat.setFillColor(sf::Color::Green);
	chat.setPosition(400, 400);
	texts.push_back(chat);



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
		
		elapsed = deltaClock.getElapsedTime() - start;
		if (!isPaused) {
			//Update agents
			agents[0].Update(sm.getHour());
			agents[1].Update(sm.getHour());
			agents[2].Update(sm.getHour());
			agents[3].Update(sm.getHour());
			sf::sleep(sf::milliseconds(500 / speed));
			sm.step = step;
			step++;
			
		}
		
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
		ImGui::SFML::Update(window, deltaClock.getElapsedTime());
		
		//ImGui::ShowDemoWindow();
		ImGui::Begin("Hello, world!");
		ImGui::Checkbox("Pause", &isPaused);
		ImGui::SliderInt("speed", &speed, 0, 10);
		if (isPaused) {
			if (ImGui::InputInt("Step", &step, 1, 1)) {
				std::cout << "Pressed" << std::endl;
				agents[0].Update(sm.getHour());
				agents[1].Update(sm.getHour());
				agents[2].Update(sm.getHour());
				agents[3].Update(sm.getHour());
				prevStep = step--;
				sm.step = step;
			}
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
		
		texts[0].setString((std::string(1, (static_cast<char>(a.type)))) + "\n" +
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