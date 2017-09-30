#include <functional>
namespace yin{
    template <typename F, typename G>
    struct _compose {
        F f;
        G g;

        template <typename Fun, typename ...Args>
        constexpr decltype(auto) operator()(Fun&& x, Args&& ...args) const& {
            return f(
                g(std::forward<Fun&&>(x)),
                std::forward<Args&&>(args)...
            );
        }
        template <typename Fun, typename ...Args>
        constexpr decltype(auto) operator()(Fun&& x, Args&& ...args) & {
            return f(
                g(std::forward<Fun&&>(x)),
                std::forward<Args&&>(args)...
            );
        }
        template <typename Fun, typename ...Args>
        constexpr decltype(auto) operator()(Fun&& x, Args&& ...args) && {
            return f(
                g(std::forward<Fun&&>(x)),
                std::forward<Args&&>(args)...
            );
        }
        _compose(F&& _f, G&& _g):f(_f), g(_g){}
    };

    template<typename F, typename G, typename ...Args>
    constexpr decltype(auto) make_compose(F&& f, G&& g, Args&& ...args){
        return _compose<F, G>(std::forward<F&&>(f), std::forward<G&&>(g))(std::forward<Args&&>(args)...);
    }
}
