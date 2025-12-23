#pragma once

// Helper macros for FOR_EACH

// Макрос для получения количества аргументов
#define GET_ARG_COUNT(...) GET_ARG_COUNT_IMPL(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define GET_ARG_COUNT_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N

// Конкатенация для создания имени макроса
#define CONCAT(a, b) CONCAT_IMPL(a, b)
#define CONCAT_IMPL(a, b) a##b

// Макросы для разного количества аргументов
#define FOR_EACH_0(macro, ...)
#define FOR_EACH_1(macro, a) macro(a)
#define FOR_EACH_2(macro, a, b) macro(a) macro(b)
#define FOR_EACH_3(macro, a, b, c) macro(a) macro(b) macro(c)
#define FOR_EACH_4(macro, a, b, c, d) macro(a) macro(b) macro(c) macro(d)
#define FOR_EACH_5(macro, a, b, c, d, e) macro(a) macro(b) macro(c) macro(d) macro(e)
#define FOR_EACH_6(macro, a, b, c, d, e, f) macro(a) macro(b) macro(c) macro(d) macro(e) macro(f)
#define FOR_EACH_7(macro, a, b, c, d, e, f, g) macro(a) macro(b) macro(c) macro(d) macro(e) macro(f) macro(g)
#define FOR_EACH_8(macro, a, b, c, d, e, f, g, h) macro(a) macro(b) macro(c) macro(d) macro(e) macro(f) macro(g) macro(h)
#define FOR_EACH_9(macro, a, b, c, d, e, f, g, h, i) macro(a) macro(b) macro(c) macro(d) macro(e) macro(f) macro(g) macro(h) macro(i)
#define FOR_EACH_10(macro, a, b, c, d, e, f, g, h, i, j) macro(a) macro(b) macro(c) macro(d) macro(e) macro(f) macro(g) macro(h) macro(i) macro(j)

// Основной макрос FOR_EACH
#define EXPAND(...) __VA_ARGS__

#define FOR_EACH(macro, ...) \
    FOR_EACH_DISPATCH(macro, GET_ARG_COUNT(EXPAND(__VA_ARGS__)), EXPAND(__VA_ARGS__))

#define FOR_EACH_DISPATCH(macro, count, ...) \
    CONCAT(FOR_EACH_, count)(macro, __VA_ARGS__)

//-------------------------------------------------------------------//

#define GENERATE_SIGNALS(topic) \
    void topic##Changed();

#define GENERATE_EMIT(topic) \
    case TopicType::topic: \
        emit topic##Changed(); \
        break;

// Topic declaration macros

// #define DECLARE_TOPICS(...) \
//     FOR_EACH(GENERATE_SIGNALS, __VA_ARGS__) \
//     private: \
//     enum class TopicType { __VA_ARGS__, _COUNT }; \
//     void _emitTopic(TopicType topic) { \
//         switch (topic) { \
//             FOR_EACH(GENERATE_EMIT, __VA_ARGS__) \
//         } \
//     }


#define DECLARE_TOPIC_ENUM(...) \
    enum class TopicType { __VA_ARGS__, _COUNT };

#define DECLARE_TOPIC_SIGNALS(...) \
    FOR_EACH(GENERATE_SIGNALS, __VA_ARGS__)

#define DECLARE_TOPIC_EMIT(...) \
    void _emitTopic(TopicType topic) { \
        switch (topic) { \
            FOR_EACH(GENERATE_EMIT, __VA_ARGS__) \
        } \
    }

#define DECLARE_TOPICS(...) \
    DECLARE_TOPIC_SIGNALS(__VA_ARGS__) \
    DECLARE_TOPIC_ENUM(__VA_ARGS__) \
    DECLARE_TOPIC_EMIT(__VA_ARGS__)

#define DECLARE_TOPIC_PARAM(type, name, jsonName, defaultValue, topic, toType) \
    private: \
        Q_PROPERTY(type name READ name WRITE set##name NOTIFY topic##Changed) \
    public: \
        type name() const { \
            const auto& msg = _topics[static_cast<int>(TopicType::topic)].message; \
            if (!msg.contains(jsonName)) { \
                return defaultValue; \
            } \
            return msg[jsonName].to##toType(); \
        } \
        void set##name(type value) { \
            const auto& msg = _topics[static_cast<int>(TopicType::topic)].message; \
            if (!msg.contains(jsonName) || msg[jsonName] != value) { \
                msg[jsonName] = value; \
                _topics[static_cast<int>(TopicType::topic)].isChanged = true; \
                emit topic##Changed(); \
            } \
        }

// Topic initialization macro
#define INIT_TOPIC(name, jsonPath) \
    _topics[static_cast<int>(TopicType::name)].path = jsonPath; \
    QObject::connect(this, &VehicleTelemetry::name##Changed, this, [this]() { _updateTelemetry(_topics[static_cast<int>(TopicType::name)]); }, Qt::AutoConnection);
