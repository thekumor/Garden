// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/events.h
//	Desc: Event system dispatcher and listener,
//	event types and event structure.
// 
//	Modified: 2026/02/04 5:47 PM
//	Created: 2026/01/16 8:20 PM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <functional>

#define GRD_EVDATA_CAST(data, type) *reinterpret_cast<type*>(data)
#define GRD_EVDATA_CREATE(value, type) reinterpret_cast<void*>(&value)

namespace grd
{
	class EventListener;
	class EventDispatcher;
	
	extern EventDispatcher g_EventDispatcher;

	enum class EventType : std::uint8_t
	{
		None = 0,
		WindowClose,
		WindowResize,
		KeyPressed,
		GridSizeChanged
	};

	using EventData = void*;

	struct Event
	{
		Event(EventType type, EventData data);
		Event() = default;

		EventType m_Type = EventType::None;
		EventData m_Data;
	};

	class EventDispatcher
	{
	public:
		friend class EventListener;

		EventDispatcher() = default;

		void CallEvent(Event ev);

	private:
		std::vector<EventListener*> m_Listeners;
	};

	using EventCallback = std::function<void(EventData)>;

	class EventListener
	{
	public:
		EventListener() = default;

		void Subscribe(EventDispatcher* dispatcher);
		void AddCallback(EventType type, EventCallback callback);
		void CallEvent(Event ev);

	private:
		EventDispatcher* m_Dispatcher = nullptr;
		std::unordered_map<EventType, EventCallback> m_Callbacks;
	};

}