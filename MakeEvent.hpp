#pragma once

#include <functional>
#include <vector>
#include <utility>

#define _MAKE_EVENT_DEF_SET(name, ...) \
        using name##Cb##_t = std::function<void(__VA_ARGS__)>; \
        private: \
        name##Cb##_t _cb##name; \

#define _MAKE_EVENT_FUN_SET(name, ...) \
        public: \
        inline void set##name##Cb(name##Cb##_t cb) { \
            _cb##name = std::move(cb); \
        } \

#define _MAKE_EVENT_TRI_SET(name, ...) \
        public: \
        template<typename... Args> \
        inline void on##name(Args&&... args) { \
            if (_cb##name) \
                _cb##name(std::forward<Args>(args)...); \
        } \

#define MAKE_EVENT_SET(name, ...) \
        _MAKE_EVENT_DEF_SET(name, __VA_ARGS__) \
        _MAKE_EVENT_FUN_SET(name, __VA_ARGS__) \
        _MAKE_EVENT_TRI_SET(name, __VA_ARGS__) \


#define _MAKE_EVENT_DEF_ADD(name, ...) \
        using name##Cb##_t = std::function<void(__VA_ARGS__)>; \
        private: \
        std::vector<name##Cb##_t> _cbs##name; \

#define _MAKE_EVENT_FUN_ADD(name, ...) \
        public: \
        inline void add##name##Cb(name##Cb##_t cb) { \
            _cbs##name.emplace_back(std::move(cb)); \
        } \

#define _MAKE_EVENT_TRI_ADD(name, ...) \
        public: \
        template<typename... Args> \
        inline void on##name(Args&&... args) { \
            for (const auto& cb : _cbs##name) { \
                cb(std::forward<Args>(args)...); \
            } \
        } \

#define MAKE_EVENT_ADD(name, ...) \
        _MAKE_EVENT_DEF_ADD(name, __VA_ARGS__) \
        _MAKE_EVENT_FUN_ADD(name, __VA_ARGS__) \
        _MAKE_EVENT_TRI_ADD(name, __VA_ARGS__) \


#define MAKE_EVENT MAKE_EVENT_SET

