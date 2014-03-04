//
//  RenderCapabilities.h
//  moFlow
//
//  Created by Ian Copland on 27/01/2014.
//  Copyright (c) 2014 Tag Games Ltd. All rights reserved.
//

#ifndef _MOFLOW_RENDERINGPLATFORM_OPENGL_RENDERCAPABILITIES_H_
#define _MOFLOW_RENDERINGPLATFORM_OPENGL_RENDERCAPABILITIES_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Backend/Rendering/OpenGL/ForwardDeclarations.h>
#include <ChilliSource/Rendering/Base/RenderCapabilities.h>

namespace ChilliSource
{
    namespace OpenGL
    {
        //========================================================
        /// Render Capabilities
        ///
        /// Describes the opengl rendering capabilities available
        /// on the running device. This cannot be used until
        /// Init() is called on the render system.
        //========================================================
        class RenderCapabilities : public Rendering::RenderCapabilities
        {
        public:
            CS_DECLARE_NAMEDTYPE(RenderCapabilities);
            //-------------------------------------------------
			/// Constructor
			//-------------------------------------------------
			RenderCapabilities();
            //-------------------------------------------------
			/// Is A
			///
			/// Query the interface type
            ///
			/// @param The interface to compare
			/// @return Whether the object implements that
            /// interface
			//-------------------------------------------------
			bool IsA(Core::InterfaceIDType inInterfaceID) const override;
            //-------------------------------------------------
			/// Calculate Capabilities
            ///
            /// Calculates each of the capabilities. This needs
            /// to be called after the render system has been
            /// initialised.
			//-------------------------------------------------
			void CalculateCapabilities();
            //-------------------------------------------------
            /// Is Shadow Mapping Supported
            ///
            /// @return Whether or not shadow mapping is
            /// supported.
            //-------------------------------------------------
            bool IsShadowMappingSupported() const;
            //-------------------------------------------------
            /// Are Depth Texture Supported
            ///
            /// @return Whether or not depth textures are
            /// supported.
            //-------------------------------------------------
            bool AreDepthTexturesSupported() const;
            //-------------------------------------------------
            /// Get Max Texture Size
            ///
            /// @return The maximum texture size available on
            /// this device.
            //-------------------------------------------------
            u32 GetMaxTextureSize() const;
            //-------------------------------------------------
            /// Get Num Texture Units
            ///
            /// @return The number of texture units supported
            /// by this device.
            //-------------------------------------------------
            u32 GetNumTextureUnits() const;
        private:
            bool mbShadowsSupported;
            bool mbDepthTexturesSupported;
            bool mbHighPrecisionInFragmentShaderSupported;
            u32 mudwMaxTextureSize;
            u32 mudwNumTextureUnits;
        };
    }
}

#endif
