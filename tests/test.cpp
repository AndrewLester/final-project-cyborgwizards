#include <catch2/catch_all.hpp>

#include <iostream>

#include "Entity.hpp"

TEST_CASE("EventListener", "[event-listener]") {
  class DerivedEntity : public Entity {
   private:
    std::string indicator_;
   public:
    DerivedEntity(std::string indicator): Entity({0, 0, 0}), indicator_(indicator) {}
    void OnNotify(Event event) override {
      std::string msg = this->indicator_ + ", " + event.GetType();
      throw std::runtime_error(msg);
    }
    void Draw(Coord center) override {}
  };
  class DerivedEvent : public Event {
   public:
    DerivedEvent(Entity* emitter): Event("DerivedEvent", emitter) {}
  };

  Entity* e1 = new DerivedEntity("e1");
  Entity* e2 = new DerivedEntity("e2");

  Event event("BaseEvent", e1);
  DerivedEvent devent(e2);
  REQUIRE(event.GetType() == "BaseEvent");
  REQUIRE(devent.GetType() == "DerivedEvent");

  EventListener::Instance().RegisterListener(e1, "BaseEvent");
  REQUIRE_THROWS_WITH(e1->UploadEvent(event), "e1, BaseEvent");
  REQUIRE_NOTHROW(e2->UploadEvent(devent));
  EventListener::Instance().RegisterListener(e2, "DerivedEvent");
  REQUIRE_THROWS_WITH(e1->UploadEvent(devent), "e2, DerivedEvent");
  
  
  delete e1; delete e2;
}
