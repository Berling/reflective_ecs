#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <ecs/typed_value.hpp>
#include <ecs/assign.hpp>
#include <utils/logger.hpp>

using namespace utils;

namespace ecs {
    std::string to_string(const Json::Value& value) {
        std::stringstream ss;
        if (value.type() == Json::ValueType::arrayValue) {
            ss << "[";
            for (auto& v : value) {
                ss << to_string(v) << ", ";
            }
            std::string string = ss.str();
            return std::string{string.substr(0, string.size() - 2) + "]"};
        } else if (value.type() == Json::ValueType::objectValue) {
            ss << "{";
            for (auto& v : value) {
                ss << to_string(v) << ", ";
            }
            ss.unget();
            ss.unget();
            std::string string = ss.str();
            return std::string{string.substr(0, string.size() - 2) + "}"};
        }
        return value.asString();
    }

    std::unique_ptr<value_pack> assign_values(const std::string& name, const Json::Value& object, const rtti::property_list& properties) {
        if (object.size() != properties.size()) {
            utils::log(LOG_ERROR) << "expected " << properties.size() << " properties at " << name << " but got " << object.size() << std::endl;
            return nullptr;
        }
        auto value_pack = std::make_unique<ecs::value_pack>(name);
        for (auto& p : properties) {
            auto wrapped_value = object[p->name()];
            auto value = assign_value(p.get(), wrapped_value);
            if (!value) {
                utils::log(LOG_ERROR) << "conversion from json value to type of property " << p->name() << " at " << name << " failed" << std::endl;
                return nullptr;
            }
            value_pack->emplace_back(std::move(value));
        }
        return value_pack;
    }

    std::unique_ptr<abstract_value> assign_value(abstract_property* property, const Json::Value& wrapped_value) {
        auto type = property->type();
        if (type == property_type<bool>::type_id()) {
            return assign_bool(property, wrapped_value);
        } else if (type == property_type<int>::type_id()) {
            return assign_int(property, wrapped_value);
        } else if (type == property_type<glm::ivec2>::type_id()) {
            return assign_ivec2(property, wrapped_value);
        } else if (type ==property_type<glm::ivec3>::type_id()) {
            return assign_ivec3(property, wrapped_value);
        } else if (type == property_type<glm::ivec4>::type_id()) {
            return assign_ivec4(property, wrapped_value);
        } else if (type == property_type<float>::type_id()) {
            return assign_float(property, wrapped_value);
        } else if (type == property_type<glm::vec2>::type_id()) {
            return assign_vec2(property, wrapped_value);
        } else if (type == property_type<glm::vec3>::type_id()) {
            return assign_vec3(property, wrapped_value);
        } else if (type == property_type<glm::vec4>::type_id()) {
            return assign_vec4(property, wrapped_value);
        } else if (type == property_type<glm::quat>::type_id()) {
            return assign_quat(property, wrapped_value);
        } else if (type == property_type<std::string>::type_id()) {
            return assign_string(property, wrapped_value);
        } else {
            return nullptr;
        }
    }

    std::unique_ptr<abstract_value> assign_bool(abstract_property* property, const Json::Value& wrapped_value) {
        auto type = wrapped_value.type();
        if (type != Json::ValueType::booleanValue) {
            utils::log(LOG_ERROR) << "expected type bool at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        return std::unique_ptr<abstract_value>(new typed_value<bool>{*static_cast<typed_property<bool>*>(property), wrapped_value.asBool()});
    }

    std::unique_ptr<abstract_value> assign_int(abstract_property* property, const Json::Value& wrapped_value) {
        auto type = wrapped_value.type();
        if (type != Json::ValueType::intValue) {
            utils::log(LOG_ERROR) << "expected type int at property " << property->name() << " : " + to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        return std::unique_ptr<abstract_value>(new typed_value<int>{*static_cast<typed_property<int>*>(property), wrapped_value.asInt()});
    }

    std::unique_ptr<abstract_value> assign_ivec2(abstract_property* property, const Json::Value& wrapped_value) {
        auto type = wrapped_value.type();
        if (type != Json::ValueType::arrayValue) {
            utils::log(LOG_ERROR) << "expected type ivec2 at property " << property->name() << " : " + to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value.size() != 3) {
            utils::log(LOG_ERROR) << "expected size 2 at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value[0].asString() != "i") {
            utils::log(LOG_ERROR) << "expected type ivec2 at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        glm::ivec2 vec;
        for (auto i = 1; i < 3; ++i) {
            auto& elem = wrapped_value[i];
            if (elem.type() != Json::ValueType::intValue) {
                utils::log(LOG_ERROR) << "expected element type int at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
                return nullptr;
            }
            vec[i - 1] = elem.asInt();
        }
        return std::unique_ptr<abstract_value>(new typed_value<glm::ivec2>{*static_cast<typed_property<glm::ivec2>*>(property), vec});
    }

    std::unique_ptr<abstract_value> assign_ivec3(abstract_property* property, const Json::Value& wrapped_value) {
        auto type = wrapped_value.type();
        if (type != Json::ValueType::arrayValue) {
            utils::log(LOG_ERROR) << "expected type ivec3 at property " << property->name() << " : " + to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value.size() != 4) {
            utils::log(LOG_ERROR) << "expected size 3 at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value[0].asString() != "i") {
            utils::log(LOG_ERROR) << "expected type ivec3 at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        glm::ivec3 vec;
        for (auto i = 1; i < 4; ++i) {
            auto& elem = wrapped_value[i];
            if (elem.type() != Json::ValueType::intValue) {
                utils::log(LOG_ERROR) << "expected element type int at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
                return nullptr;
            }
            vec[i - 1] = elem.asInt();
        }
        return std::unique_ptr<abstract_value>(new typed_value<glm::ivec3>{*static_cast<typed_property<glm::ivec3>*>(property), vec});
    }

    std::unique_ptr<abstract_value> assign_ivec4(abstract_property* property, const Json::Value& wrapped_value) {
        auto type = wrapped_value.type();
        if (type != Json::ValueType::arrayValue) {
            utils::log(LOG_ERROR) << "expected type ivec4 at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value.size() != 5) {
            utils::log(LOG_ERROR) << "expected size 4 at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value[0].asString() != "i") {
            utils::log(LOG_ERROR) << "expected type ivec4 at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        glm::ivec4 vec;
        for (auto i = 1; i < 5; ++i) {
            auto& elem = wrapped_value[i];
            if (elem.type() != Json::ValueType::intValue) {
                utils::log(LOG_ERROR) << "expected element type int at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
                return nullptr;
            }
            vec[i - 1] = elem.asInt();
        }
        return std::unique_ptr<abstract_value>(new typed_value<glm::ivec4>{*static_cast<typed_property<glm::ivec4>*>(property), vec});
    }

    std::unique_ptr<abstract_value> assign_float(abstract_property* property, const Json::Value& wrapped_value) {
        auto type = wrapped_value.type();
        if (type != Json::ValueType::realValue) {
            utils::log(LOG_ERROR) << "expected type float at property " << property->name() << " : " + to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        return std::unique_ptr<abstract_value>(new typed_value<float>{*static_cast<typed_property<float>*>(property),
            wrapped_value.asFloat()});
    }

    std::unique_ptr<abstract_value> assign_vec2(abstract_property* property, const Json::Value& wrapped_value) {
        auto type = wrapped_value.type();
        if (type != Json::ValueType::arrayValue) {
            utils::log(LOG_ERROR) << "expected type vec2 at property " << property->name() << " : " + to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value.size() != 3) {
            utils::log(LOG_ERROR) << "expected size 2 at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value[0].asString() != "f") {
            utils::log(LOG_ERROR) << "expected type vec2 at property " << property->name() << " : " + to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        glm::vec2 vec;
        for (auto i = 1; i < 3; ++i) {
            auto& elem = wrapped_value[i];
            if (elem.type() != Json::ValueType::realValue) {
                utils::log(LOG_ERROR) << "expected element type float at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
                return nullptr;
            }
            vec[i - 1] = elem.asFloat();
        }
        return std::unique_ptr<abstract_value>(new typed_value<glm::vec2>{*static_cast<typed_property<glm::vec2>*>(property), vec});
    }

    std::unique_ptr<abstract_value> assign_vec3(abstract_property* property, const Json::Value& wrapped_value) {
        auto type = wrapped_value.type();
        if (type != Json::ValueType::arrayValue) {
            utils::log(LOG_ERROR) << "expected type vec3 at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value.size() != 4) {
            utils::log(LOG_ERROR) << "expected size 3 at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value[0].asString() != "f") {
            utils::log(LOG_ERROR) << "expected type vec3 at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        glm::vec3 vec;
        for (auto i = 1; i < 4; ++i) {
            auto& elem = wrapped_value[i];
            if (elem.type() != Json::ValueType::realValue) {
                utils::log(LOG_ERROR) << "expected element type float at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
                return nullptr;
            }
            vec[i - 1] = elem.asFloat();
        }
        return std::unique_ptr<abstract_value>(new typed_value<glm::vec3>{*static_cast<typed_property<glm::vec3>*>(property), vec});
    }

    std::unique_ptr<abstract_value> assign_vec4(abstract_property* property, const Json::Value& wrapped_value) {
        auto type = wrapped_value.type();
        if (type != Json::ValueType::arrayValue) {
            utils::log(LOG_ERROR) << "expected type vec4 at property " << property->name() << " : " + to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value.size() != 5) {
            utils::log(LOG_ERROR) << "expected size 4 at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value[0].asString() != "f") {
            utils::log(LOG_ERROR) << "expected type vec4 at property " << property->name() << " : " + to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        glm::vec4 vec;
        for (auto i = 1; i < 5; ++i) {
            auto& elem = wrapped_value[i];
            if (elem.type() != Json::ValueType::realValue) {
                utils::log(LOG_ERROR) << "expected element type float at property " << property->name() + " : " << to_string(wrapped_value) << std::endl;
                return nullptr;
            }
            vec[i - 1] = elem.asFloat();
        }
        return std::unique_ptr<abstract_value>(new typed_value<glm::vec4>{*static_cast<typed_property<glm::vec4>*>(property), vec});
    }

    std::unique_ptr<abstract_value> assign_quat(abstract_property* property, const Json::Value& wrapped_value) {
        auto type = wrapped_value.type();
        if (type != Json::ValueType::arrayValue) {
            utils::log(LOG_ERROR) << "expected type quat at property " << property->name() << " : " + to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value.size() != 5) {
            utils::log(LOG_ERROR) << "expected size 4 at property " << property->name() << " : " + to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        if (wrapped_value[0].asString() != "q") {
            utils::log(LOG_ERROR) << "expected type quat at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        glm::vec4 vec;
        for (auto i = 1; i < 5; ++i) {
            auto& elem = wrapped_value[i];
            if (elem.type() != Json::ValueType::realValue) {
                utils::log(LOG_ERROR) << "expected element type float at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
                return nullptr;
            }
            vec[i - 1] = elem.asFloat();
        }
        glm::quat quat = glm::angleAxis(vec[0], glm::vec3{vec[1], vec[2], vec[3]});
        return std::unique_ptr<abstract_value>(new typed_value<glm::quat>{*static_cast<typed_property<glm::quat>*>(property), glm::normalize(quat)});
    }

    std::unique_ptr<abstract_value> assign_string(abstract_property* property, const Json::Value& wrapped_value) {
        auto type = wrapped_value.type();
        if (type != Json::ValueType::stringValue) {
            utils::log(LOG_ERROR) << "expected type string at property " << property->name() << " : " << to_string(wrapped_value) << std::endl;
            return nullptr;
        }
        return std::unique_ptr<abstract_value>(new typed_value<std::string>{*static_cast<typed_property<std::string>*>(property), wrapped_value.asString()});
    }
}