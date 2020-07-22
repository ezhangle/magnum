/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,
                2020 Vladimír Vondruš <mosra@centrum.cz>
    Copyright © 2020 Jonathan Hale <squareys@googlemail.com>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include "PhongMaterialData.h"

#include <Corrade/Containers/EnumSet.hpp>
#ifdef MAGNUM_BUILD_DEPRECATED
#include <Corrade/Containers/GrowableArray.h>
#endif

namespace Magnum { namespace Trade {

using namespace Math::Literals;

#ifdef MAGNUM_BUILD_DEPRECATED
CORRADE_IGNORE_DEPRECATED_PUSH
PhongMaterialData::PhongMaterialData(const Flags flags, const Color4& ambientColor, const UnsignedInt ambientTexture, const UnsignedInt ambientCoordinateSet, const Color4& diffuseColor, const UnsignedInt diffuseTexture, const UnsignedInt diffuseCoordinateSet, const Color4& specularColor, const UnsignedInt specularTexture, const UnsignedInt specularCoordinateSet, const UnsignedInt normalTexture, const UnsignedInt normalCoordinateSet, const Matrix3& textureMatrix, const MaterialAlphaMode alphaMode, const Float alphaMask, const Float shininess, const void* const importerState) noexcept: MaterialData{MaterialType::Phong, [&](){
    Containers::Array<MaterialAttributeData> data;

    if(flags & Flag::DoubleSided)
        arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::DoubleSided, true);
    if(alphaMode == MaterialAlphaMode::Blend)
        arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::AlphaBlend, true);
    /* Include a mask also if it has a non-default value to stay compatible
       with existing behavior */
    if(alphaMode == MaterialAlphaMode::Mask || alphaMask != 0.0f)
        arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::AlphaMask, alphaMask);

    CORRADE_ASSERT(!(flags & Flag::TextureTransformation) || (flags & (Flag::AmbientTexture|Flag::DiffuseTexture|Flag::SpecularTexture|Flag::NormalTexture)),
        "Trade::PhongMaterialData: texture transformation enabled but the material has no textures", data);
    CORRADE_ASSERT((flags & Flag::TextureTransformation) || textureMatrix == Matrix3{},
        "PhongMaterialData::PhongMaterialData: non-default texture matrix requires Flag::TextureTransformation to be enabled", data);
    CORRADE_ASSERT((flags & Flag::TextureCoordinateSets) || (ambientCoordinateSet == 0 && diffuseCoordinateSet == 0 && specularCoordinateSet == 0 && normalCoordinateSet == 0),
        "PhongMaterialData::PhongMaterialData: non-zero texture coordinate sets require Flag::TextureCoordinateSets to be enabled", data);

    arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::AmbientColor, ambientColor);
    if(flags & Flag::AmbientTexture) {
        arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::AmbientTexture, ambientTexture);
        if(ambientCoordinateSet)
            arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::AmbientCoordinateSet, ambientCoordinateSet);
    }

    arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::DiffuseColor, diffuseColor);
    if(flags & Flag::DiffuseTexture) {
        arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::DiffuseTexture, diffuseTexture);
        if(diffuseCoordinateSet)
            arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::DiffuseCoordinateSet, diffuseCoordinateSet);
    }

    arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::SpecularColor, specularColor);
    if(flags & Flag::SpecularTexture) {
        arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::SpecularTexture, specularTexture);
        if(specularCoordinateSet)
            arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::SpecularCoordinateSet, specularCoordinateSet);
    }

    if(flags & Flag::NormalTexture) {
        arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::NormalTexture, normalTexture);
        if(normalCoordinateSet)
            arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::NormalCoordinateSet, normalCoordinateSet);
    }

    if(flags & Flag::TextureTransformation)
        arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::TextureMatrix, textureMatrix);

    arrayAppend(data, Containers::InPlaceInit, MaterialAttribute::Shininess, shininess);

    return data;
}(), importerState} {
    /* The data can't be filled here because it won't be sorted correctly */
}

PhongMaterialData::PhongMaterialData(const Flags flags, const Color4& ambientColor, const UnsignedInt ambientTexture, const Color4& diffuseColor, const UnsignedInt diffuseTexture, const Color4& specularColor, const UnsignedInt specularTexture, const UnsignedInt normalTexture, const Matrix3& textureMatrix, const MaterialAlphaMode alphaMode, const Float alphaMask, const Float shininess, const void* const importerState) noexcept: PhongMaterialData{flags, ambientColor, ambientTexture, 0, diffuseColor, diffuseTexture, 0, specularColor, specularTexture, 0, normalTexture, 0, textureMatrix, alphaMode, alphaMask, shininess, importerState} {}

PhongMaterialData::PhongMaterialData(const Flags flags, const MaterialAlphaMode alphaMode, const Float alphaMask, const Float shininess, const void* const importerState) noexcept: PhongMaterialData{flags, 0x000000ff_rgbaf, {}, 0xffffffff_rgbaf, {}, 0xffffffff_rgbaf, {}, {}, {}, alphaMode, alphaMask, shininess, importerState} {}
CORRADE_IGNORE_DEPRECATED_POP
#endif

#ifdef MAGNUM_BUILD_DEPRECATED
CORRADE_IGNORE_DEPRECATED_PUSH
PhongMaterialData::Flags PhongMaterialData::flags() const {
    /* "Append" to flags recognized by the base class */
    Flags flags{Flag(UnsignedInt(MaterialData::flags()))};

    if(hasAttribute(MaterialAttribute::AmbientTexture))
        flags |= Flag::AmbientTexture;
    if(hasAttribute(MaterialAttribute::DiffuseTexture))
        flags |= Flag::DiffuseTexture;
    if(hasAttribute(MaterialAttribute::SpecularTexture))
        flags |= Flag::SpecularTexture;
    if(hasAttribute(MaterialAttribute::NormalTexture))
        flags |= Flag::NormalTexture;
    if(hasTextureTransformation())
        flags |= Flag::TextureTransformation;
    if(hasTextureCoordinateSets())
        flags |= Flag::TextureCoordinateSets;

    return flags;
}
CORRADE_IGNORE_DEPRECATED_POP
#endif

bool PhongMaterialData::hasTextureTransformation() const {
    return hasAttribute(MaterialAttribute::AmbientTextureMatrix) ||
       hasAttribute(MaterialAttribute::DiffuseTextureMatrix) ||
       hasAttribute(MaterialAttribute::SpecularTextureMatrix) ||
       hasAttribute(MaterialAttribute::NormalTextureMatrix) ||
       hasAttribute(MaterialAttribute::TextureMatrix);
}

bool PhongMaterialData::hasTextureCoordinateSets() const {
    return attributeOr(MaterialAttribute::AmbientCoordinateSet, 0u) ||
       attributeOr(MaterialAttribute::DiffuseCoordinateSet, 0u) ||
       attributeOr(MaterialAttribute::SpecularCoordinateSet, 0u) ||
       attributeOr(MaterialAttribute::NormalCoordinateSet, 0u) ||
       attributeOr(MaterialAttribute::CoordinateSet, 0u);
}

Color4 PhongMaterialData::ambientColor() const {
    return attributeOr(MaterialAttribute::AmbientColor,
        hasAttribute(MaterialAttribute::AmbientTexture) ? 0xffffffff_rgbaf : 0x000000ff_rgbaf);
}

UnsignedInt PhongMaterialData::ambientTexture() const {
    return attribute<UnsignedInt>(MaterialAttribute::AmbientTexture);
}

UnsignedInt PhongMaterialData::ambientCoordinateSet() const {
    CORRADE_ASSERT(hasAttribute(MaterialAttribute::AmbientTexture),
        "Trade::PhongMaterialData::ambientCoordinateSet(): the material doesn't have an ambient texture", {});
    if(Containers::Optional<UnsignedInt> set = tryAttribute<UnsignedInt>(MaterialAttribute::AmbientCoordinateSet))
        return *set;
    return attributeOr(MaterialAttribute::CoordinateSet, 0u);
}

Color4 PhongMaterialData::diffuseColor() const {
    return attributeOr(MaterialAttribute::DiffuseColor, 0xffffffff_rgbaf);
}

UnsignedInt PhongMaterialData::diffuseTexture() const {
    return attribute<UnsignedInt>(MaterialAttribute::DiffuseTexture);
}

UnsignedInt PhongMaterialData::diffuseCoordinateSet() const {
    CORRADE_ASSERT(hasAttribute(MaterialAttribute::DiffuseTexture),
        "Trade::PhongMaterialData::diffuseCoordinateSet(): the material doesn't have a diffuse texture", {});
    if(Containers::Optional<UnsignedInt> set = tryAttribute<UnsignedInt>(MaterialAttribute::DiffuseCoordinateSet))
        return *set;
    return attributeOr(MaterialAttribute::CoordinateSet, 0u);
}

Color4 PhongMaterialData::specularColor() const {
    return attributeOr(MaterialAttribute::SpecularColor, 0xffffffff_rgbaf);
}

UnsignedInt PhongMaterialData::specularTexture() const {
    return attribute<UnsignedInt>(MaterialAttribute::SpecularTexture);
}

UnsignedInt PhongMaterialData::specularCoordinateSet() const {
    CORRADE_ASSERT(hasAttribute(MaterialAttribute::SpecularTexture),
        "Trade::PhongMaterialData::specularCoordinateSet(): the material doesn't have a specular texture", {});
    if(Containers::Optional<UnsignedInt> set = tryAttribute<UnsignedInt>(MaterialAttribute::SpecularCoordinateSet))
        return *set;
    return attributeOr(MaterialAttribute::CoordinateSet, 0u);
}

UnsignedInt PhongMaterialData::normalTexture() const {
    return attribute<UnsignedInt>(MaterialAttribute::NormalTexture);
}

UnsignedInt PhongMaterialData::normalCoordinateSet() const {
    CORRADE_ASSERT(hasAttribute(MaterialAttribute::NormalTexture),
        "Trade::PhongMaterialData::normalCoordinateSet(): the material doesn't have a normal texture", {});
    if(Containers::Optional<UnsignedInt> set = tryAttribute<UnsignedInt>(MaterialAttribute::NormalCoordinateSet))
        return *set;
    return attributeOr(MaterialAttribute::CoordinateSet, 0u);
}

Matrix3 PhongMaterialData::textureMatrix() const {
    return attributeOr(MaterialAttribute::TextureMatrix, Matrix3{});
}

Float PhongMaterialData::shininess() const {
    return attributeOr(MaterialAttribute::Shininess, 80.0f);
}

#ifdef MAGNUM_BUILD_DEPRECATED
CORRADE_IGNORE_DEPRECATED_PUSH
Debug& operator<<(Debug& debug, const PhongMaterialData::Flag value) {
    debug << "Trade::PhongMaterialData::Flag" << Debug::nospace;

    switch(value) {
        /* LCOV_EXCL_START */
        #define _c(v) case PhongMaterialData::Flag::v: return debug << "::" #v;
        _c(DoubleSided)
        _c(AmbientTexture)
        _c(DiffuseTexture)
        _c(SpecularTexture)
        _c(NormalTexture)
        _c(TextureTransformation)
        _c(TextureCoordinateSets)
        #undef _c
        /* LCOV_EXCL_STOP */
    }

    return debug << "(" << Debug::nospace << reinterpret_cast<void*>(UnsignedByte(value)) << Debug::nospace << ")";
}

Debug& operator<<(Debug& debug, const PhongMaterialData::Flags value) {
    return Containers::enumSetDebugOutput(debug, value, "Trade::PhongMaterialData::Flags{}", {
        PhongMaterialData::Flag::DoubleSided,
        PhongMaterialData::Flag::AmbientTexture,
        PhongMaterialData::Flag::DiffuseTexture,
        PhongMaterialData::Flag::SpecularTexture,
        PhongMaterialData::Flag::NormalTexture,
        PhongMaterialData::Flag::TextureTransformation,
        PhongMaterialData::Flag::TextureCoordinateSets});
}
CORRADE_IGNORE_DEPRECATED_POP
#endif

}}
