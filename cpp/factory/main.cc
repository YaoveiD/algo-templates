#include "msg.h"
#include <cassert>
#include <map>
#include <memory>
#include <vector>

namespace msg_helper {
void load(StringMsg &msg) {
    std::cin >> msg.val;
}

void load(IntMsg &msg) {
    std::cin >> msg.val;
}
}

struct Msg {
    virtual void say() const = 0;
    virtual void load() = 0;
    virtual ~Msg() = default;

    using Ptr = std::shared_ptr<Msg>;
};

template<typename T>
struct MsgImpl : Msg {
    T msg;

    template<class ...Ts>
    MsgImpl(Ts &&...ts) : msg{std::forward<Ts>(ts)...} {
    }

    void say() const override {
        msg.say();
    }

    void load() {
        msg_helper::load(msg);
    }
};

// To store factories in a map, we need a base type
struct MsgFactory {
    virtual Msg::Ptr create() = 0;
    virtual ~MsgFactory() = default;

    using Ptr = std::shared_ptr<MsgFactory>;
};

template<typename T>
struct MsgFactoryImpl : MsgFactory {
    Msg::Ptr create() override {
        return std::make_shared<MsgImpl<T>>();
    }
};

template<typename T>
MsgFactory::Ptr make_factory() {
    return std::make_shared<MsgFactoryImpl<T>>();
}

static const std::map<std::string, MsgFactory::Ptr> factories = {
    // {"String", std::make_shared<MsgFactoryImpl<StringMsg>>()},
    // {"Int", std::make_shared<MsgFactoryImpl<IntMsg>>()}
    {"String", make_factory<StringMsg>()},
    {"Int", make_factory<IntMsg>()}
};

int main() {
    std::vector<Msg::Ptr> msgs;
    int T;
    std::cin >> T;
    msgs.reserve(T);

    for (int t = 0; t < T; ++t) {
        std::string type;
        std::cin >> type;
        auto &factory = factories.at(type);
        auto msg = factory->create();
        msg->load();
        msgs.push_back(msg);
    }


    for (const auto &msg : msgs) {
        msg->say();
    }
}
