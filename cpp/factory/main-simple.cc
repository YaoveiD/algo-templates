#include "msg.h"
#include <cassert>
#include <memory>
#include <vector>


struct Msg {
    virtual void say() const = 0;
    virtual ~Msg() = default;
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
};

template<typename T, class ...Ts>
std::shared_ptr<Msg> make_msg(Ts &&...ts) {
    // return std::shared_ptr<Msg>(new MsgImpl<T>(std::forward<Ts>(ts)...));
    return std::make_shared<MsgImpl<T>>(std::forward<Ts>(ts)...);
}

int main() {
    std::cout << "Hello" << std::endl;

    std::vector<std::shared_ptr<Msg>> msgs;
    int T;
    std::cin >> T;
    msgs.reserve(T);

    for (int t = 0; t < T; ++t) {
        int type;
        std::cin >> type;
        if (type == 1) {
            std::string s;
            std::cin >> s;
            msgs.push_back(make_msg<StringMsg>(std::move(s)));
        } else if (type == 2) {
            int x;
            std::cin >> x;
            msgs.push_back(make_msg<IntMsg>(x));
        } else assert(false);
    }


    for (const auto &msg : msgs) {
        msg->say();
    }
}
