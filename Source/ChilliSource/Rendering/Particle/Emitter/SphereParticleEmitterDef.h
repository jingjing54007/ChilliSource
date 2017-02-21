//
//  SphereParticleEmitterDef.h
//  ChilliSource
//  Created by Ian Copland on 19/10/2014.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2014 Tag Games Limited
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifndef _CHILLISOURCE_RENDERING_PARTICLE_EMITTER_SPHEREPARTICLEEMITTERDEF_H_
#define _CHILLISOURCE_RENDERING_PARTICLE_EMITTER_SPHEREPARTICLEEMITTERDEF_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Rendering/Particle/Emitter/ParticleEmitterDef.h>

namespace ChilliSource
{
    //-----------------------------------------------------------------------
    /// A particle emitter def describing the properties for a Sphere Particle
    /// Emitter and provides a means to create instances.
    ///
    /// As a particle emitter def's contents can potentially be read from 
    /// multiple threads, it is immutable after construction. The exception 
    /// to this is if it was created from a param dictionary with a 
    /// asynchronous delegate, in which case it is immutable after the
    /// delegate is called.
    ///
    /// The following are properties that a sphere particle emitter 
    /// contains in addition to the standard emitter properties:
    ///
    /// "EmitFromType": Where on the particle emitter particles can be
    /// emitted from. The possible values are "Inside" or "Surface".
    /// The default value is "Inside".
    ///
    /// "EmitDirectionType": Describes how the direction of an emitted
    /// particle will be generated. The possible values are "AwayFromCentre"
    /// and "Random". This defaults to "AwayFromCentre".
    ///
    /// "RadiusProperty": A property describing the radius of the emitter.
    ///
    /// @author Ian Copland
    //-----------------------------------------------------------------------
    class SphereParticleEmitterDef final : public ParticleEmitterDef
    {
    public:
        CS_DECLARE_NAMEDTYPE(SphereParticleEmitterDef);
        //----------------------------------------------------------------
        /// An enum describing where in the emitter a particle can be
        /// generated. If inside is used, the particle can be emitted from
        /// anywhere inside the sphere. If surface is used, particles will
        /// only be emitted from the surface of the sphere.
        /// 
        /// @author Ian Copland
        //----------------------------------------------------------------
        enum class EmitFromType
        {
            k_inside,
            k_surface
        };
        //----------------------------------------------------------------
        /// An enum describing the possible ways the emission direction
        /// of a particle can be generated. If Away From Centre is used the 
        /// particle will always move in a direction away from the centre
        /// of the emitter. If random is used, the direction will be
        /// entirely random.
        /// 
        /// @author Ian Copland
        //----------------------------------------------------------------
        enum class EmitDirectionType
        {
            k_awayFromCentre,
            k_random
        };
        //----------------------------------------------------------------
        /// Constructor
        ///
        /// @author Ian Copland
        ///
        /// @param The emission mode.
        /// @param The emission rate property. This is ignored for when in 
        /// burst emission mode.
        /// @param The property describing the number of particles in each
        /// emission.
        /// @param The property describing the chance that a particle will 
        /// actually emit each time an emission is attempted. This is used 
        /// to make an effect look more random.
        /// @param Where in the sphere a particle can be emitted from.
        /// @param Describes how the direction of a particle will be
        /// determined.
        /// @param The property describing the radius of the emitter.
        //----------------------------------------------------------------
        SphereParticleEmitterDef(EmissionMode in_emissionMode, ParticlePropertyUPtr<f32> in_emissionRateProperty, ParticlePropertyUPtr<u32> in_particlesPerEmissionProperty,
            ParticlePropertyUPtr<f32> in_emissionChanceProperty, EmitFromType in_emitFromType, EmitDirectionType in_emitDirectionType, ParticlePropertyUPtr<f32> in_radiusProperty);
        //----------------------------------------------------------------
        /// Constructor. Initialises with parameters read from the given 
        /// param dictionary. If the async delegate is not null, then any 
        /// resource loading will occur as a background task. Once complete 
        /// the delegate will be called. The parameters read from json are
        /// described in the class documentation.
        ///
        /// @author Ian Copland
        ///
        /// @param A json object describing the parameters for the particle
        /// emitter def.
        /// @param The loaded delegate. If this is supplied any resources
        /// will be loaded as a background task. Once complete, this
        /// delegate will be called.
        //----------------------------------------------------------------
        SphereParticleEmitterDef(const Json::Value& in_paramsJson, const LoadedDelegate& in_loadedDelegate = nullptr);
        //----------------------------------------------------------------
        /// Allows querying of whether or not this implements the interface
        /// described by the given Id.
        ///
        /// @author Ian Copland
        ///
        /// @param The interface Id.
        ///
        /// @return Whether or not the interface is implemented.
        //----------------------------------------------------------------
        bool IsA(InterfaceIDType in_interfaceId) const override;
        //----------------------------------------------------------------
        /// Creates a new instance of a Sphere Particle Emitter.
        ///
        /// @author Ian Copland.
        ///
        /// @param The particle array.
        ///
        /// @return the instance.
        //----------------------------------------------------------------
        ParticleEmitterUPtr CreateInstance(dynamic_array<Particle>* in_particleArray) const override;
        //----------------------------------------------------------------
        /// @author Ian Copland.
        ///
        /// @param Where in the sphere a particle can be emitted from.
        //----------------------------------------------------------------
        EmitFromType GetEmitFromType() const;
        //----------------------------------------------------------------
        /// @author Ian Copland.
        ///
        /// @param The emit direction type, i.e how the direction of a 
        /// particle will be  determined.
        //----------------------------------------------------------------
        EmitDirectionType GetEmitDirectionType() const;
        //----------------------------------------------------------------
        /// @author Ian Copland
        ///
        /// @return A property describing the radius of the particle
        /// emitter.
        //----------------------------------------------------------------
        const ParticleProperty<f32>* GetRadiusProperty() const;
    private:
        EmitFromType m_emitFromType = EmitFromType::k_inside;
        EmitDirectionType m_emitDirectionType = EmitDirectionType::k_awayFromCentre;
        ParticlePropertyUPtr<f32> m_radiusProperty = ParticlePropertyUPtr<f32>(new ConstantParticleProperty<f32>(1.0f));
    };
}

#endif
