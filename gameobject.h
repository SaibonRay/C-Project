#pragma once

class GameObject
{
public:
    virtual ~GameObject() = default;

    virtual void init() {}
    virtual void update(float dt) {}
    virtual void draw() {}

    bool isActive() const { return active; }
    void setActive(bool a) { active = a; }

protected:
    bool active = true;
};

