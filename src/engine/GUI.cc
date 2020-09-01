//
// Created by bparsy on 8/29/20.
//

#include "GUI.hh"

static void multimap_call_all(auto& map, auto key, sf::Event& evt) {
    for (auto it = map.lower_bound(key); it != map.upper_bound(key); ++it)
        it->second(evt);
}

void GUI::draw() const {

}

void GUI::handle_events(sf::Event& evt) const {
    multimap_call_all(events_, evt.type, evt);

    if (auto kit = key_events_.find(evt.type); kit != key_events_.end())
        multimap_call_all(kit->second, evt.key.code, evt);
    if (auto mit = mb_events_.find(evt.type); mit != mb_events_.end())
        multimap_call_all(mit->second, evt.mouseButton.button, evt);
}

auto GUI::add_event(sf::Event::EventType type, evt_func const& callback) -> GUI& {
    events_.insert({type, callback});
    return *this;
}

auto GUI::add_key_event(sf::Event::EventType key_event, sf::Keyboard::Key key, evt_func const& callback) -> GUI& {
    key_events_[key_event].insert({key, callback});
    return *this;
}

auto GUI::add_mb_event(sf::Event::EventType mb_event, sf::Mouse::Button button, evt_func const& callback) -> GUI& {
    mb_events_[mb_event].insert({button, callback});
    return *this;
}
