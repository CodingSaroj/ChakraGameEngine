#ifndef CHAKRA_IRENDERER_HPP
#define CHAKRA_IRENDERER_HPP

namespace Chakra
{
    class IRenderer
    {
        protected:
            virtual ~IRenderer() = default;

            virtual void Initialize() = 0;
            virtual void Render()     = 0;
    };
}

#endif
