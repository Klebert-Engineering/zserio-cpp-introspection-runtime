#include "zsr/introspectable.hpp"

namespace zsr {

Introspectable::Introspectable(const Compound* meta,
                               std::shared_ptr<impl::InstanceBase> obj)
    : obj(std::move(obj))
{
    this->obj->meta = meta;
}

Introspectable::Introspectable(const Introspectable& o) : obj(o.obj) {}

Introspectable& Introspectable::operator=(const Introspectable& o)
{
    obj = o.obj;
    return *this;
}

Introspectable::Introspectable(Introspectable&& o) : obj(std::move(o.obj)) {}

Introspectable& Introspectable::operator=(Introspectable&& o)
{
    obj = std::move(o.obj);
    return *this;
}

Introspectable::~Introspectable() {}

bool Introspectable::isOwning() const { return obj && obj->isOwning(); }

const Compound* Introspectable::meta() const
{
    return obj ? obj->meta : nullptr;
}

} // namespace zsr