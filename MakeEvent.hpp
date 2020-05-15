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
        using name##EventID_t = unsigned int; \
        using name##Cb##_t = std::function<void(__VA_ARGS__)>; \
        using name##Cb##Pair_t = std::pair<name##EventID_t, std::function<void(__VA_ARGS__)>>; \
        private: \
        name##EventID_t _cbs##name##ID##Count = 0; \
        std::vector<name##Cb##Pair_t> _cbs##name; \

#define _MAKE_EVENT_FUN_ADD(name, ...) \
        public: \
        inline name##EventID_t add##name##Cb(name##Cb##_t cb) { \
            auto id = ++_cbs##name##ID##Count; \
            _cbs##name.emplace_back(std::make_pair(id, std::move(cb))); \
            return id; \
        } \
        inline name##EventID_t remove##name##CbById(name##EventID_t id) { \
            for (auto it = _cbs##name.cbegin(); it != _cbs##name.cend();) { \
                const auto& item = *it; \
                if (item.first == id) { \
                    _cbs##name.erase(it); \
                    return id; \
                } else { \
                    it++; \
                } \
            } \
            return 0; \
        } \
        inline void removeAll##name##Cbs(){ \
            _cbs##name.clear(); \
        } \

#define _MAKE_EVENT_TRI_ADD(name, ...) \
        public: \
        template<typename... Args> \
        inline void on##name(Args&&... args) { \
            for (const auto& cb : _cbs##name) { \
                cb.second(std::forward<Args>(args)...); \
            } \
        } \

#define MAKE_EVENT_ADD(name, ...) \
        _MAKE_EVENT_DEF_ADD(name, __VA_ARGS__) \
        _MAKE_EVENT_FUN_ADD(name, __VA_ARGS__) \
        _MAKE_EVENT_TRI_ADD(name, __VA_ARGS__) \


#define MAKE_EVENT MAKE_EVENT_SET

