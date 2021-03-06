#include "base.hpp"

namespace {

PKG;

TEST_CASE("check_bitmask_values", "[BitmaskTest::check_bitmask_values]") {
    auto* meta_bitmask = zsr::find<zsr::Bitmask>(pkg, "Mask");

    REQUIRE(meta_bitmask);
    REQUIRE(&meta_bitmask->parent == &pkg);
    REQUIRE(meta_bitmask->values.size() == 3);

    auto ASSERT_VALUE = [&](auto ident, unsigned val) {
        auto* meta_value = zsr::find<zsr::BitmaskValue>(
            *meta_bitmask, ident);

        REQUIRE(meta_value);
        REQUIRE(&meta_value->parent == meta_bitmask);
        ASSERT_VARIANT_EQ(meta_value->value, val);
    };

    ASSERT_VALUE("A", 1);
    ASSERT_VALUE("B", 2);
    ASSERT_VALUE("C", 0xff);
}

TEST_CASE("bitmask_member", "[BitmaskTest::bitmask_member]") {
    auto* meta_struct = zsr::find<zsr::Compound>(pkg, "Owner");
    REQUIRE(meta_struct);

    auto* meta_field = zsr::find<zsr::Field>(*meta_struct, "a");
    REQUIRE(meta_field);

    auto type = meta_field->type;
    REQUIRE(type);
    REQUIRE(type->ctype.type == zsr::CType::UInt);
    REQUIRE(!type->ctype.array);
}

}
