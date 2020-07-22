#ifndef Magnum_Trade_PhongMaterialData_h
#define Magnum_Trade_PhongMaterialData_h
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

/** @file
 * @brief Class @ref Magnum::Trade::PhongMaterialData
 */

#include "Magnum/Magnum.h"
#include "Magnum/Math/Color.h"
#include "Magnum/Math/Matrix3.h"
#include "Magnum/Trade/MaterialData.h"

namespace Magnum { namespace Trade {

/**
@brief Phong material data

@see @ref AbstractImporter::material()
*/
class MAGNUM_TRADE_EXPORT PhongMaterialData: public MaterialData {
    public:
        #ifdef MAGNUM_BUILD_DEPRECATED
        /**
         * @brief Material flag
         * @m_deprecated_since_latest The flags are no longer stored directly
         *      but generated on-the-fly from attribute data, which makes them
         *      less efficient than calling @ref hasAttribute(),
         *      @ref isDoubleSided(), @ref hasTextureTransformation(),
         *      @ref hasTextureCoordinateSets() etc.
         *
         * A superset of @ref MaterialData::Flag.
         * @see @ref Flags, @ref flags()
         */
        enum class CORRADE_DEPRECATED_ENUM("use hasAttribute() etc. instead") Flag: UnsignedInt {
            /** @copydoc MaterialData::Flag::DoubleSided */
            DoubleSided = 1 << 0,

            /** The material has an ambient texture */
            AmbientTexture = 1 << 1,

            /** The material has a diffuse texture */
            DiffuseTexture = 1 << 2,

            /** The material has a specular texture */
            SpecularTexture = 1 << 3,

            /**
             * The material has a normal texture
             * @m_since{2020,06}
             */
            NormalTexture = 1 << 4,

            /**
             * The material has a texture coordinate transformation
             * @m_since{2020,06}
             */
            TextureTransformation = 1 << 5,

            /**
             * The material uses non-default texture coordinate sets
             * @m_since{2020,06}
             */
            TextureCoordinateSets = 1 << 6
        };

        /**
         * @brief Material flags
         * @m_deprecated_since_latest The flags are no longer stored directly
         *      but generated on-the-fly from attribute data, which makes them
         *      less efficient than calling @ref hasAttribute(),
         *      @ref isDoubleSided(), @ref hasTextureTransformation(),
         *      @ref hasTextureCoordinateSets() etc.
         *
         * A superset of @ref MaterialData::Flags.
         * @see @ref flags()
         */
        CORRADE_IGNORE_DEPRECATED_PUSH /* GCC warns about Flags, ugh */
        typedef CORRADE_DEPRECATED("use hasAttribute() etc. instead") Containers::EnumSet<Flag> Flags;
        CORRADE_IGNORE_DEPRECATED_POP
        #endif

        /**
         * @brief Construction is not allowed
         * @m_since_latest
         *
         * This class is meant to be used only for convenience attribute access
         * with a cast from @ref MaterialData, never constructed directly.
         */
        PhongMaterialData() = delete;

        #ifdef MAGNUM_BUILD_DEPRECATED
        /**
         * @brief Constructor
         * @param flags             Material flags
         * @param ambientColor      Ambient color. Use
         *      @cpp 0x000000ff_rgbaf @ce for a default value for a
         *      non-textured material and @cpp 0xffffffff_rgbaf @ce for a
         *      default value for a textured material.
         * @param ambientTexture    Ambient texture ID. Ignored if @p flags
         *      doesn't have @ref Flag::AmbientTexture.
         * @param diffuseColor      Diffuse color. Use
         *      @cpp 0xffffffff_rgbaf @ce for a default value for both a
         *      non-textured and a textured material.
         * @param diffuseTexture    Diffuse texture ID. Ignored if @p flags
         *      doesn't have @ref Flag::DiffuseTexture.
         * @param specularColor     Specular color. Use
         *      @cpp 0xffffffff_rgbaf @ce for a default value for both a
         *      non-textured and a textured material.
         * @param specularTexture   Specular texture ID. Ignored if @p flags
         *      doesn't have @ref Flag::SpecularTexture.
         * @param normalTexture     Normal texture ID. Ignored if @p flags
         *      doesn't have @ref Flag::NormalTexture.
         * @param textureMatrix     Texture coordinate transformation
         * @param alphaMode         Alpha mode. Use
         *      @ref MaterialAlphaMode::Opaque for a default value.
         * @param alphaMask         Alpha mask value. Use @cpp 0.5f @ce for a
         *      default value.
         * @param shininess         Shininess. Use @cpp 80.0f @ce for a default
         *      value.
         * @param importerState     Importer-specific state
         *
         * All `*CoordinateSet` accessors are implicitly zero with this
         * constructor. If @p textureMatrix is not default-constructed, expects
         * @ref Flag::TextureTransformation to be enabled as well.
         *
         * @m_deprecated_since_latest Populate a @ref MaterialData instance
         *      using @ref MaterialData::MaterialData(MaterialTypes, Containers::Array<MaterialAttributeData>&&, const void*)
         *      instead. This class is not meant to be constructed directly
         *      anymore.
         */
        CORRADE_IGNORE_DEPRECATED_PUSH /* GCC warns about Flags, ugh */
        explicit CORRADE_DEPRECATED("use MaterialData::MaterialData(MaterialTypes, Containers::Array<MaterialAttributeData>&&, const void*) instead") PhongMaterialData(Flags flags, const Color4& ambientColor, UnsignedInt ambientTexture, const Color4& diffuseColor, UnsignedInt diffuseTexture, const Color4& specularColor, UnsignedInt specularTexture, UnsignedInt normalTexture, const Matrix3& textureMatrix, MaterialAlphaMode alphaMode, Float alphaMask, Float shininess, const void* importerState = nullptr) noexcept;
        CORRADE_IGNORE_DEPRECATED_POP

        /**
         * @brief Construct with non-zero texture coordinate sets
         * @param flags                 Material flags
         * @param ambientColor          Ambient color. Use
         *      @cpp 0x000000ff_rgbaf @ce for a default value for a
         *      non-textured material and @cpp 0xffffffff_rgbaf @ce for a
         *      default value for a textured material.
         * @param ambientTexture        Ambient texture ID. Ignored if @p flags
         *      doesn't have @ref Flag::AmbientTexture.
         * @param ambientCoordinateSet  Ambient texture coordinate set. Ignored
         *      if @p flags doesn't have @ref Flag::AmbientTexture
         * @param diffuseColor          Diffuse color. Use
         *      @cpp 0xffffffff_rgbaf @ce for a default value for both a
         *      non-textured and a textured material.
         * @param diffuseTexture        Diffuse texture ID. Ignored if @p flags
         *      doesn't have @ref Flag::DiffuseTexture.
         * @param diffuseCoordinateSet  Diffuse texture coordinate set. Ignored
         *      if @p flags doesn't have @ref Flag::DiffuseTexture
         * @param specularColor         Specular color. Use
         *      @cpp 0xffffffff_rgbaf @ce for a default value for both a
         *      non-textured and a textured material.
         * @param specularTexture       Specular texture ID. Ignored if
         *      @p flags doesn't have @ref Flag::SpecularTexture.
         * @param specularCoordinateSet Specular texture coordinate set.
         *      Ignored if @p flags doesn't have @ref Flag::SpecularTexture.
         * @param normalTexture         Normal texture ID. Ignored if @p flags
         *      doesn't have @ref Flag::NormalTexture.
         * @param normalCoordinateSet   Normal texture coordinate set. Ignored
         *      if @p flags doesn't have @ref Flag::NormalTexture.
         * @param textureMatrix         Texture coordinate transformation
         * @param alphaMode             Alpha mode. Use
         *      @ref MaterialAlphaMode::Opaque for a default value.
         * @param alphaMask             Alpha mask value. Use @cpp 0.5f @ce for
         *      a default value.
         * @param shininess             Shininess. Use @cpp 80.0f @ce for a
         *      default value.
         * @param importerState         Importer-specific state
         *
         * If @p textureMatrix is not default-constructed, expects
         * @ref Flag::TextureTransformation to be enabled as well. If any
         * `*CoordinateSet` is non-zero, expects @ref Flag::TextureCoordinateSets
         * to be enabled as well.
         *
         * @m_deprecated_since_latest Populate a @ref MaterialData instance
         *      using @ref MaterialData::MaterialData(MaterialTypes, Containers::Array<MaterialAttributeData>&&, const void*)
         *      instead. This class is not meant to be constructed directly
         *      anymore.
         */
        CORRADE_IGNORE_DEPRECATED_PUSH /* GCC warns about Flags, ugh */
        explicit CORRADE_DEPRECATED("use MaterialData::MaterialData(MaterialTypes, Containers::Array<MaterialAttributeData>&&, const void*) instead") PhongMaterialData(Flags flags, const Color4& ambientColor, UnsignedInt ambientTexture, UnsignedInt ambientCoordinateSet, const Color4& diffuseColor, UnsignedInt diffuseTexture, UnsignedInt diffuseCoordinateSet, const Color4& specularColor, UnsignedInt specularTexture, UnsignedInt specularCoordinateSet, UnsignedInt normalTexture, UnsignedInt normalCoordinateSet, const Matrix3& textureMatrix, MaterialAlphaMode alphaMode, Float alphaMask, Float shininess, const void* importerState = nullptr) noexcept;
        CORRADE_IGNORE_DEPRECATED_POP

        /**
         * @brief Constructor
         * @m_deprecated_since{2020,06} Populate a @ref MaterialData instance
         *      using @ref MaterialData::MaterialData(MaterialTypes, Containers::Array<MaterialAttributeData>&&, const void*)
         *      instead. This class is not meant to be constructed directly
         *      anymore.
         */
        CORRADE_IGNORE_DEPRECATED_PUSH /* GCC warns about Flags, ugh */
        explicit CORRADE_DEPRECATED("use MaterialData::MaterialData(MaterialTypes, Containers::Array<MaterialAttributeData>&&, const void*) instead") PhongMaterialData(Flags flags, MaterialAlphaMode alphaMode, Float alphaMask, Float shininess, const void* importerState = nullptr) noexcept;
        CORRADE_IGNORE_DEPRECATED_POP

        /** @brief Copying is not allowed */
        PhongMaterialData(const PhongMaterialData&) = delete;

        /**
         * @brief Move constructor
         * @m_deprecated_since{2020,06} Populate a @ref MaterialData instance
         *      using @ref MaterialData::MaterialData(MaterialTypes, Containers::Array<MaterialAttributeData>&&, const void*)
         *      instead. This class is not meant to be constructed directly
         *      anymore.
         */
        CORRADE_DEPRECATED("only MaterialData is meant to be constructed or moved") PhongMaterialData(PhongMaterialData&& other) noexcept = default;

        /** @brief Copying is not allowed */
        PhongMaterialData& operator=(const PhongMaterialData&) = delete;

        /**
         * @brief Move assignment
         * @m_deprecated_since{2020,06} Populate a @ref MaterialData instance
         *      using @ref MaterialData::MaterialData(MaterialTypes, Containers::Array<MaterialAttributeData>&&, const void*)
         *      instead. This class is not meant to be constructed directly
         *      anymore.
         */
        CORRADE_DEPRECATED("only MaterialData is meant to be constructed or moved") PhongMaterialData& operator=(PhongMaterialData&& other) noexcept = default;
        #endif

        /**
         * @brief Whether the material has texture transformation
         * @m_since_latest
         *
         * Returns @cpp true @ce if any of the
         * @ref MaterialAttribute::AmbientTextureMatrix,
         * @ref MaterialAttribute::DiffuseTextureMatrix,
         * @ref MaterialAttribute::SpecularTextureMatrix,
         * @ref MaterialAttribute::NormalTextureMatrix or
         * @ref MaterialAttribute::TextureMatrix attributes is present,
         * @cpp false @ce otherwise.
         */
        bool hasTextureTransformation() const;

        /**
         * @brief Whether the material uses extra texture coordinate sets
         * @m_since_latest
         *
         * Returns @cpp true @ce if any of the
         * @ref MaterialAttribute::AmbientCoordinateSet,
         * @ref MaterialAttribute::DiffuseCoordinateSet,
         * @ref MaterialAttribute::SpecularCoordinateSet,
         * @ref MaterialAttribute::NormalCoordinateSet or
         * @ref MaterialAttribute::CoordinateSet attributes is present and has
         * a non-zero value, @cpp false @ce otherwise.
         */
        bool hasTextureCoordinateSets() const;

        #ifdef MAGNUM_BUILD_DEPRECATED
        /**
         * @brief Material flags
         * @m_deprecated_since_latest The flags are no longer stored directly
         *      but generated on-the-fly from attribute data, which makes them
         *      less efficient than calling @ref hasAttribute(),
         *      @ref isDoubleSided(), @ref hasTextureTransformation(),
         *      @ref hasTextureCoordinateSets() etc.
         *
         * A superset of @ref MaterialData::flags().
         */
        CORRADE_IGNORE_DEPRECATED_PUSH /* GCC warns about Flags, ugh */
        CORRADE_DEPRECATED("use hasAttribute() instead") Flags flags() const;
        CORRADE_IGNORE_DEPRECATED_POP
        #endif

        /**
         * @brief Ambient color
         *
         * Convenience access to the @ref MaterialAttribute::AmbientColor
         * attribute. If not present, the default is either
         * @cpp 0xffffffff_rgbaf @ce if there's
         * @ref MaterialAttribute::AmbientTexture and @cpp 0x000000ff_rgbaf @ce
         * otherwise.
         *
         * If the material has @ref MaterialAttribute::AmbientTexture, the
         * color and texture is meant to be multiplied together.
         * @see @ref hasAttribute()
         */
        Color4 ambientColor() const;

        /**
         * @brief Ambient texture ID
         *
         * Available only if @ref MaterialAttribute::AmbientTexture is
         * present. Meant to be multiplied with @ref ambientColor().
         * @see @ref hasAttribute(), @ref AbstractImporter::texture()
         */
        UnsignedInt ambientTexture() const;

        /**
         * @brief Ambient texture coordinate set
         * @m_since{2020,06}
         *
         * Convenience access to the @ref MaterialAttribute::AmbientCoordinateSet
         * attribute. If not present, the default is @cpp 0 @ce. Available only
         * if the material has @ref MaterialAttribute::AmbientTexture.
         * @see @ref hasAttribute(), @ref AbstractImporter::texture()
         */
        UnsignedInt ambientCoordinateSet() const;

        /**
         * @brief Diffuse color
         *
         * Convenience access to the @ref MaterialAttribute::DiffuseColor
         * attribute. If not present, the default is @cpp 0xffffffff_rgbaf @ce.
         *
         * If the material has @ref MaterialAttribute::DiffuseTexture, the
         * color and texture is meant to be multiplied together.
         * @see @ref hasAttribute()
         */
        Color4 diffuseColor() const;

        /**
         * @brief Diffuse texture ID
         *
         * Available only if @ref MaterialAttribute::DiffuseTexture is
         * present. Meant to be multiplied with @ref diffuseColor().
         * @see @ref hasAttribute(), @ref AbstractImporter::texture()
         */
        UnsignedInt diffuseTexture() const;

        /**
         * @brief Diffuse texture coordinate set
         * @m_since{2020,06}
         *
         * Convenience access to the @ref MaterialAttribute::DiffuseCoordinateSet
         * attribute. If not present, the default is @cpp 0 @ce. Available only
         * if the material has @ref MaterialAttribute::DiffuseTexture.
         * @see @ref hasAttribute(), @ref AbstractImporter::texture()
         */
        UnsignedInt diffuseCoordinateSet() const;

        /**
         * @brief Specular color
         *
         * Convenience access to the @ref MaterialAttribute::SpecularColor
         * attribute. If not present, the default is @cpp 0xffffffff_rgbaf @ce.
         *
         * If the material has @ref MaterialAttribute::SpecularTexture, the
         * color and texture is meant to be multiplied together.
         * @see @ref hasAttribute()
         */
        Color4 specularColor() const;

        /**
         * @brief Specular texture ID
         *
         * Available only if @ref MaterialAttribute::SpecularTexture is
         * present. Meant to be multiplied with @ref specularColor().
         * @see @ref hasAttribute(), @ref AbstractImporter::texture()
         */
        UnsignedInt specularTexture() const;

        /**
         * @brief Specular texture coordinate set
         * @m_since{2020,06}
         *
         * Convenience access to the @ref MaterialAttribute::SpecularCoordinateSet
         * attribute. If not present, the default is @cpp 0 @ce. Available only
         * if the material has @ref MaterialAttribute::SpecularTexture.
         * @see @ref hasAttribute(), @ref AbstractImporter::texture()
         */
        UnsignedInt specularCoordinateSet() const;

        /**
         * @brief Normal texture ID
         * @m_since{2020,06}
         *
         * Available only if the material has @ref Flag::NormalTexture.
         * @see @ref hasAttribute(), @ref AbstractImporter::texture()
         */
        UnsignedInt normalTexture() const;

        /**
         * @brief Normal texture coordinate set
         * @m_since{2020,06}
         *
         * Available only if the material has @ref Flag::NormalTexture.
         * @see @ref hasAttribute(), @ref AbstractImporter::texture()
         */
        UnsignedInt normalCoordinateSet() const;

        /**
         * @brief Texture coordinate transformation matrix
         * @m_since{2020,06}
         *
         * Convenience access to the @ref MaterialAttribute::TextureMatrix
         * attribute. If not present, the default is an identity matrix.
         * @see @ref hasAttribute()
         */
        Matrix3 textureMatrix() const;

        /**
         * @brief Shininess
         *
         * Convenience access to the @ref MaterialAttribute::Shininess
         * attribute. If not present, the default is @cpp 80.0f @ce.
         */
        Float shininess() const;
};

#ifdef MAGNUM_BUILD_DEPRECATED
CORRADE_IGNORE_DEPRECATED_PUSH
CORRADE_ENUMSET_OPERATORS(PhongMaterialData::Flags)

/**
@debugoperatorclassenum{PhongMaterialData,PhongMaterialData::Flag}
@m_deprecated_since_latest The flags are no longer stored directly but
    generated on-the-fly from attribute data, which makes them less efficient
    than calling @ref MaterialData::hasAttribute(),
    @ref MaterialData::isDoubleSided(),
    @ref PhongMaterialData::hasTextureTransformation(),
    @ref PhongMaterialData::hasTextureCoordinateSets() etc.
*/
MAGNUM_TRADE_EXPORT Debug& operator<<(Debug& debug, PhongMaterialData::Flag value);

/**
@debugoperatorclassenum{PhongMaterialData,PhongMaterialData::Flags}
@m_deprecated_since_latest The flags are no longer stored directly but
    generated on-the-fly from attribute data, which makes them less efficient
    than calling @ref MaterialData::hasAttribute(),
    @ref MaterialData::isDoubleSided(),
    @ref PhongMaterialData::hasTextureTransformation(),
    @ref PhongMaterialData::hasTextureCoordinateSets() etc.
*/
MAGNUM_TRADE_EXPORT Debug& operator<<(Debug& debug, PhongMaterialData::Flags value);
CORRADE_IGNORE_DEPRECATED_POP
#endif

}}

#endif
