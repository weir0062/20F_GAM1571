#pragma once
#include "Math/Vector.h"
#include "Objects/GameObject.h"
namespace fw {

class Event
{
public:
    Event();
    virtual ~Event();

    virtual const char* GetType() = 0;

protected:
};

class InputEvent : public Event
{
public:
    enum class DeviceType
    {
        Keyboard,
    };

    enum class DeviceState
    {
        Pressed,
        Released,
    };

    InputEvent(DeviceType deviceType, DeviceState deviceState, unsigned int keyCode)
    {
        m_DeviceType = deviceType;
        m_DeviceState = deviceState;
        m_KeyCode = keyCode;
    }
    virtual ~InputEvent() {}

    static const char* GetStaticEventType() { return "InputEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }

    DeviceType GetDeviceType() { return m_DeviceType; }
    DeviceState GetDeviceState() { return m_DeviceState; }
    unsigned int GetKeyCode() { return m_KeyCode; }

protected:
    DeviceType m_DeviceType;
    DeviceState m_DeviceState;
    unsigned int m_KeyCode;
};


class CollisionEvent : public Event
{
public:

    CollisionEvent( GameObject* firstobject, GameObject* secondobject)
    {
        m_firstobject = firstobject;
        m_secondobject = secondobject;

    }
    virtual ~CollisionEvent(){}
    static const char* GetStaticEventType() { return "CollisionEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }
    GameObject* GetfirstObject()
    {

        return m_firstobject;
    }
    GameObject* GetsecondObject()
    {

        return m_secondobject;
    }

    
protected:

    GameObject* m_firstobject;
    GameObject* m_secondobject;

};

} // namespace fw
