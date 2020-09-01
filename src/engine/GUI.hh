//
// Created by bparsy on 8/29/20.
//

#ifndef CELLS_GUI_HH
#define CELLS_GUI_HH

#include <SFML/Graphics.hpp>
#include "Engine.h"

using evt_func = std::function<void(sf::Event&)>;

class GUI {
public:
    GUI(Engine& e, sf::RenderWindow& w) : e_(e), w_(w) {}

    void draw() const;
    void handle_events(sf::Event& evt) const;

    auto add_event(sf::Event::EventType type, const evt_func& callback) -> GUI&;
    auto add_key_event(sf::Event::EventType key_event, sf::Keyboard::Key key, evt_func const& callback) -> GUI&;
    auto add_mb_event(sf::Event::EventType mb_event, sf::Mouse::Button button, evt_func const& callback) -> GUI&;
private:
    Engine& e_;
    sf::RenderWindow& w_;

    std::multimap<sf::Event::EventType, evt_func> events_;
    std::map<sf::Event::EventType, std::multimap<sf::Keyboard::Key, evt_func>> key_events_;
    std::map<sf::Event::EventType, std::multimap<sf::Mouse::Button, evt_func>> mb_events_;
};


#endif //CELLS_GUI_HH
